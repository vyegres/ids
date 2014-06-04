#include "Config.h"
#include <iostream>

Config::Config(const char *cfg_file)
{
	try {
		file.readFile((cfg_file ? cfg_file : "config.cfg"));
	}
	catch (const libconfig::FileIOException &fioex)
	{
		std::cerr << "I/O error while reading file. (config.cfg)";
		exit (EXIT_FAILURE);
	}
	catch(const libconfig::ParseException &pex)
	{
		std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine() << " - " << pex.getError() << std::endl;
		exit (EXIT_FAILURE);
	}
	
	const libconfig::Setting &config_root = file.getRoot();

	const libconfig::Setting &config_app          = config_root["app"];
	const libconfig::Setting &config_dump_listner = config_root["dump_listner"];
    const libconfig::Setting &config_solv_listner = config_root["solver_listner"];
    const libconfig::Setting &config_traffic_db   = config_root["traffic_db"];
    const libconfig::Setting &config_event_db     = config_root["event_db"];

	
	// App config
	if(!config_app.lookupValue("log_file", this->log_file)) {
		this->log_file = "log.txt";
	}
	config_app.lookupValue("debug", this->debug);
	
	// DumpLisn config
	config_dump_listner.lookupValue("protocol", this->dump_lisn.protocol);
	config_dump_listner.lookupValue("ip", this->dump_lisn.ip);
	config_dump_listner.lookupValue("port", this->dump_lisn.port);
    config_dump_listner.lookupValue("threads_cnt", this->dump_lisn.threads_cnt);




    // SolvLisn config
    config_solv_listner.lookupValue("protocol", this->solv_lisn.protocol);
    config_solv_listner.lookupValue("ip", this->solv_lisn.ip);
    config_solv_listner.lookupValue("port", this->solv_lisn.port);


	// DB config
    config_event_db.lookupValue("provider", this->storage.eventDB.provider);
    config_event_db.lookupValue("ip", this->storage.eventDB.ip);
    config_event_db.lookupValue("port", this->storage.eventDB.port);
    config_event_db.lookupValue("db_name", this->storage.eventDB.db_name);
    config_event_db.lookupValue("user", this->storage.eventDB.user);
    config_event_db.lookupValue("password", this->storage.eventDB.password);
    config_event_db.lookupValue("dump_collection", this->storage.eventDB.dump_collection);

    config_traffic_db.lookupValue("provider", this->storage.trafficDB.provider);
    config_traffic_db.lookupValue("ip", this->storage.trafficDB.ip);
    config_traffic_db.lookupValue("port", this->storage.trafficDB.port);
    config_traffic_db.lookupValue("db_name", this->storage.trafficDB.db_name);
    config_traffic_db.lookupValue("user", this->storage.trafficDB.user);
    config_traffic_db.lookupValue("password", this->storage.trafficDB.password);
    config_traffic_db.lookupValue("dump_collection", this->storage.trafficDB.dump_collection);


}
