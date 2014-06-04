#include "DumpListener.h"
#include "../clientlayer/Database.h"
#include "../logiclayer/STrafficManager.h"
#include <glog/logging.h>
#include <net/ethernet.h>
#include <linux/ip.h>
#include <linux/udp.h>
#include <linux/tcp.h>

void receiver(zmq::context_t *context, class Storage *storage) {
    try
    {
        zmq::socket_t socket(*context, ZMQ_PULL);
        socket.connect("inproc://receivers");
        zmq::socket_t publisher(*context, ZMQ_PUSH);
        //publisher.bind("tcp://127.0.0.1:5233");
        publisher.connect("inproc://solver_broker");

        tMessage2s message;

        while(true)
        {
            uint8_t *payload;
            pcap_pkthdr* hdr;
            zmq::message_t request;
            socket.recv(&request);
            uint8_t buf[24];

            LOG(INFO) << "Size of request.dat: " << request.size();

            int i = 0;
            while( i <request.size() ) {
                memcpy(buf, request.data()+i, sizeof(pcap_pkthdr));
                i += sizeof(pcap_pkthdr);
                hdr = (struct pcap_pkthdr *) buf;

                LOG(INFO) << "end: " << hdr->ts.tv_sec << ":" <<  hdr->caplen;

                payload = (uint8_t *)request.data()+i;

//http://stackoverflow.com/questions/12999538/read-from-a-pcap-file-and-print-out-ip-addresses-and-port-numbers-in-c-but-my-r
                message.len = hdr->len;
                storage->insert(message);
                i += hdr->caplen;

                publisher.send(payload, hdr->caplen);
            }

        }

    }
    catch(const zmq::error_t& ze)
    {
        LOG(ERROR) << "[DumpListener] Worker exception:" << ze.what();
    }
}





void DumpListener::start(void *arg) {
    LOG(INFO) << "[DumpListener] Starting...";

    DumpListener *self = static_cast<DumpListener *>(arg);

    zmq_proxy(self->clients, self->workers, NULL);
}

void DumpListener::wait() {
    starter.join();
}

void DumpListener::stop() {

    //context.close();
}

DumpListener::DumpListener(struct dump_lisn_cfg *dlc_, class Storage *storage, zmq::context_t* context)
    :clients(*context, ZMQ_PULL),
     workers(*context, ZMQ_PUSH)
{
    this->context = context;

    config = dlc_;
    boost::thread_group threads;

    try
    {
        char addr[255];
        sprintf(addr, "%s://%s:%d", config->protocol, config->ip, config->port);
        this->clients.bind(addr);

        LOG(INFO) << "[DumpListener] Listner sensor: " << addr;

        this->workers.bind("inproc://receivers");

        for(int i=0; i<config->threads_cnt; i++) {
            threads.create_thread(boost::bind(receiver, context, storage));
            LOG(INFO) << "[DumpListener] Thread " << i+1 << " created";
        }
        starter = boost::thread(boost::bind(start, this));
    }
    catch(const zmq::error_t& ze)
    {
        LOG(ERROR) << "[DumpListener] Listner exception: " << ze.what();
    }
}
