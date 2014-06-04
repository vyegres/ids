#/usr/bin/python

import zmq
import sys 
import ctypes
import msgpack

from io import BytesIO
from time import time, sleep

from pycap import *


from ctypes import *


def init_zmq(address):
    zcontext = zmq.Context()
    zsocket = zcontext.socket(zmq.PUSH)
    zsocket.connect("tcp://" + address)
    return zcontext, zsocket

def init_pcap(filename):
    errbuf = ctypes.create_string_buffer(512)
    handle = pcap_open_offline(filename.encode(), errbuf)
    if not handle:
        print(errbuf.value.decode())
        exit(0)
    return handle

def mocksensor(filename, address, interval_sec):
    zcontext, zsocket = init_zmq(address)
    pcap = init_pcap(filename)

    packetData = ctypes.POINTER(ctypes.c_ubyte*65536)()
    pkthdrPointer = ctypes.POINTER(pcap_pkthdr)()
    


    try:
    
        timestamp = 0
        buf = BytesIO()
        count = 0
        # reading single packet from file
        while pcap_next_ex(pcap, ctypes.byref(pkthdrPointer),  ctypes.byref(packetData)) > 0:
            count += 1
            pktheader = pkthdrPointer.contents
            t = pktheader.tv_sec + pktheader.tv_usec // 100000
            # first packet
            if timestamp == 0:
                timestamp = t
            # interval passed -> send to head
            elif t - timestamp >= interval_sec:
                timestamp = t
                zsocket.send(buf.getbuffer().tobytes())
                sleep(interval_sec/1000)
            # just put serialized packet with header to buffer
            else:
                header = (pktheader.tv_sec, pktheader.tv_usec, pktheader.caplen, pktheader.len)

                class timeval(Structure):
                    _fields_ = [("tv_sec", c_long), ("tv_usec", c_long)]

                class POINT(Structure):
                    _fields_ = [("timestamp", timeval),
                        ("length", c_int),
                        ("original_length", c_int)]


                point = POINT(timeval(pktheader.tv_sec,pktheader.tv_usec),  pktheader.caplen, pktheader.len)
                print(pktheader.tv_sec, " : ",pktheader.caplen, " : ",pktheader.len , ":- ", len(msgpack.packb(packetData.contents[:pktheader.len])))

                #buf.write(msgpack.packb(header))
                buf.write(point)
                buf.write(bytearray(packetData.contents[:pktheader.len]))
                #buf.write(msgpack.packb(header))
                #buf.write(packetData.contents[:pktheader.len])

                #print(msgpack.packb(header))


        # last send
        zsocket.send(buf.getbuffer().tobytes())
        print(count)

    except KeyboardInterrupt:
        pass
    
    finally:
        print('Shutting down')
        pcap_close(pcap)
        zcontext.destroy()



if __name__ == "__main__":
    mocksensor("test1.pcap", "localhost:8088", 5)




