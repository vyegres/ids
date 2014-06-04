#ifndef __ids_head__Config__
#define __ids_head__Config__

#include <libconfig.h++>

struct dump_lisn_cfg {
	const char *protocol;
	const char *ip;
	int port;
    int threads_cnt;
};

struct solv_lisn_cfg {
    const char *protocol;
    const char *ip;
    int port;
};

struct db_cfg {
    const char *provider;
	const char *ip;
    int port;
	const char *db_name;
    const char *user;
    const char *password;
	const char *dump_collection;
};


struct storage_cfg{
    db_cfg trafficDB;
    db_cfg eventDB;
};


class Config {	
public:
	Config(const char *cfg_file);
	
	const char *log_file;
	bool debug;
	
	dump_lisn_cfg dump_lisn;
    solv_lisn_cfg solv_lisn;
    storage_cfg storage;

	
private:
	libconfig::Config file;
};

#endif /* defined(__ids_head__Config__) */
