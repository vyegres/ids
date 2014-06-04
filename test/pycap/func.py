#!/usr/bin/env python3.2

import ctypes
from ctypes.util import find_library

pcap = None

if(find_library("libpcap") == None):
    pcap = ctypes.cdll.LoadLibrary("libpcap.so")
else:
    pcap = ctypes.cdll.LoadLibrary(find_library("libpcap"))

# int pcap_compile_nopcap(int snaplen, int linktype, struct bpf_program *program,
# const char *buf, int optimize, bpf_u_int32 mask);

pcap_close = pcap.pcap_close
pcap_lookupdev = pcap.pcap_lookupdev
pcap_lookupdev.restype = ctypes.c_char_p
#pcap_lookupnet(dev, &net, &mask, errbuf)
pcap_lookupnet = pcap.pcap_lookupnet
#pcap_t *pcap_open_live(const char *device, int snaplen,int promisc, int to_ms,
#char *errbuf
pcap_open_live = pcap.pcap_open_live
#int pcap_compile(pcap_t *p, struct bpf_program *fp,const char *str, int optimize,
#bpf_u_int32 netmask)
pcap_compile = pcap.pcap_compile
#int pcap_setfilter(pcap_t *p, struct bpf_program *fp);
pcap_setfilter = pcap.pcap_setfilter
#const u_char *pcap_next(pcap_t *p, struct pcap_pkthdr *h);
pcap_next = pcap.pcap_next
# int pcap_compile_nopcap(int snaplen, int linktype, struct bpf_program *program,
# const char *buf, int optimize, bpf_u_int32 mask);
pcap_geterr = pcap.pcap_geterr
pcap_geterr.restype = ctypes.c_char_p
#int pcap_loop(pcap_t *p, int cnt, pcap_handler callback, u_char *user)
pcap_loop = pcap.pcap_loop


#int	pcap_stats(pcap_t *, struct pcap_stat *);
pcap_stats = pcap.pcap_stats
#int    pcap_set_buffer_size(pcap_t *, int);
pcap_set_buffer_size=pcap.pcap_set_buffer_size
pcap_set_promisc=pcap.pcap_set_promisc
#int    pcap_set_timeout(pcap_t *, int);
pcap_set_timeout=pcap.pcap_set_timeout
#int pcap_next_ex(pcap_t *p, struct pcap_pkthdr **pkt_header,const u_char **pkt_data);
pcap_next_ex=pcap.pcap_next_ex
#pcap_next_ex.argtypes=[ctypes.POINTER(ctypes.c_char_p),ctypes.POINTER(ctypes.POINTER(ctypes.c_ubyte)),ctypes.POINTER(ctypes.POINTER(ctypes.c_ubyte))]
#const u_char *pcap_next(pcap_t *p, struct pcap_pkthdr *h);
pcap_next = pcap.pcap_next


# lets have some fun with files! 
pcap_dump_file=pcap.pcap_dump_file
pcap_dump_file.restype = ctypes.c_void_p

pcap_open_offline=pcap.pcap_open_offline
pcap_open_offline.restype = ctypes.c_void_p

#pcap_t *pcap_fopen_offline(FILE *, char *);
pcap_fopen_offline=pcap.pcap_fopen_offline
pcap_fopen_offline.restype = ctypes.c_void_p

pcap_open_dead = pcap.pcap_open_dead
pcap_open_dead.restype = ctypes.c_void_p

pcap_dump_open = pcap.pcap_dump_open
pcap_dump_open.restype = ctypes.c_void_p

pcap_dump = pcap.pcap_dump
pcap_dump_close = pcap.pcap_dump_close
