#/usr/bin/python

import zmq
import sys 
import random

from io import BytesIO
from time import time, sleep



def init_zmq(address):
    zcontext = zmq.Context(1)
    zsocket = zcontext.socket(zmq.PUB)
    zsocket.connect("tcp://" + address)
    return zcontext, zsocket




def analyser(address):
    try:
        zcontext, zsocket = init_zmq(address)


        publisher_id = random.randrange(0,9999)
        while True:
            topic = random.randrange(1,10)
            messagedata = "server#%s" % publisher_id
           # print "%s %s" % (topic, messagedata)
           # zsocket.send("%d %s" % (topic, messagedata))
            zsocket.send_string("%d %s" % (topic, messagedata))
            



    except KeyboardInterrupt:
        pass
    
    finally:
        print('Shutting down')

        zcontext.destroy()




if __name__ == "__main__":
    analyser("localhost:8089")




