#ifndef __ids_head__STrafficManager__
#define __ids_head__STrafficManager__

#include <iostream>


struct tMessage2s {
    timeval ts;
    uint32_t len;
    uint32_t ip_src;
    uint32_t ip_dst;
    uint32_t port_src;
    uint32_t port_dst;
    uint32_t protokol1;
    uint32_t protokol2;
    uint32_t protokol3;
    uint8_t* packet1[];
    uint8_t* packet2[];
    uint8_t* packet3[];
};

struct tMessage {
    timeval ts;
    uint32_t len;
    uint32_t ip_src;
    uint32_t ip_dst;
    uint32_t port_src;
    uint32_t port_dst;
    uint32_t protokol1;
    uint32_t protokol2;
    uint32_t protokol3;
    uint8_t packet1[];
    uint8_t packet2[];
    uint8_t packet3[];
};


struct __attribute__ ((__packed__)) pcap_pkthdr{
    timeval ts;
    uint32_t caplen;
    uint32_t len;
};



#endif /* defined(__ids_head__STrafficManager__) */
