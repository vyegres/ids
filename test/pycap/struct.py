#!/usr/bin/env python3.2

import ctypes
from ctypes.util import find_library

"""
struct bpf_program {
	u_int bf_len;
	struct bpf_insn *bf_insns;}
"""
class bpf_program(ctypes.Structure):
    _fields_ = [("bf_len", ctypes.c_int),("bf_insns", ctypes.c_void_p)]

class sockaddr(ctypes.Structure):
    _fields_=[("sa_family",ctypes.c_uint16),("sa_data",ctypes.c_char*14)]

class pcap_pkthdr(ctypes.Structure):
    _fields_ = [("tv_sec", ctypes.c_long), ("tv_usec", ctypes.c_long), ("caplen", ctypes.c_uint), ("len", ctypes.c_uint)]
"""
    struct pcap_stat {
	u_int ps_recv;		/* number of packets received */
	u_int ps_drop;		/* number of packets dropped */
	u_int ps_ifdrop;	/* drops by interface XXX not yet supported */
"""
class pcap_stat(ctypes.Structure):
    _fields_ = [("ps_recv",ctypes.c_uint), ("ps_drop",ctypes.c_uint), ("ps_ifdrop", ctypes.c_int)]
    
# Something for user data
class User(ctypes.Structure):
    _fields_ = [
        ('one',ctypes.c_uint),
        ('two',ctypes.c_uint),
        ('three',ctypes.c_char_p)]
def pkthandler(param,pkthdr,packet):
    #print("pkthdr[0:7]:",pkthdr.contents.len)
    #print(param.contents.three)
    print("Got Packet with length of {0}".format(pkthdr.contents.len))
    #print(packet.contents[:10])
 


CALLBACK = ctypes.CFUNCTYPE(None,ctypes.POINTER(User),ctypes.POINTER(pcap_pkthdr),ctypes.POINTER(ctypes.c_ubyte*65536))
got_packet=CALLBACK(pkthandler)
user = User(1,2,b"hello")

pkthdr = pcap_pkthdr()
program = bpf_program()
pcap_stat_struct = pcap_stat()