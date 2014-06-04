import sys
import zmq

port = "8089"
if len(sys.argv) > 1:
    port =  sys.argv[1]
    int(port)
    
if len(sys.argv) > 2:
    port1 =  sys.argv[2]
    int(port1)

# Socket to talk to server
context = zmq.Context()
socket = context.socket(zmq.SUB)

#print "Collecting updates from weather server..."
socket.connect ("tcp://127.0.0.1:%s" % port)

if len(sys.argv) > 2:
    socket.connect ("tcp://localhost:%s" % port1)

topicfilter = "10001"
socket.setsockopt(zmq.SUBSCRIBE, b'')

# Process 5 updates
total_value = 0
for update_nbr in range (5000000000000000000):
    string = socket.recv()
    #topic, messagedata = string.split()
    #total_value += int(messagedata)
    print (string)

#print "Average messagedata value for topic '%s' was %dF" % (topicfilter, total_value / update_nbr)
      