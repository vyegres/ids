#ifndef __ids_head__Core__
#define __ids_head__Core__

#include "Config.h"
#include "clientlayer/Storage.h"

#include "serverlayer/DumpListener.h"
#include "serverlayer/SolverBroker.h"

#include <signal.h>
#include <sys/stat.h>
#include <glog/logging.h>
#include <iostream>

class Monitor {
public:
	Monitor(const char *argv[]);
	int start();
	static void stop(int exit_code);
	
	void SetPidFile(int pid);
	int GetPidFile();
    void RemovePidFile();


private:
	const char *config_file;
	int pid;
};

#endif /* defined(__ids_head__Core__) */
