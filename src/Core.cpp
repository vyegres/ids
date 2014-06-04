#include "Core.h"


void Monitor::stop(int exit_code) {
    LOG(INFO) << "[Monitor] IDS Demon shutdown";
    google::ShutdownGoogleLogging();
	exit(exit_code);
}

void Monitor::SetPidFile(int pid) {
	FILE *f;
	
	f = fopen(".ids_head.pid", "w+");
	
	if (f) {
		fprintf(f, "%u", pid);
		fclose(f);
	} else {
        LOG(ERROR) << "[Monitor] Error save .pid file";
		exit(EXIT_FAILURE);
	}
}

void Monitor::RemovePidFile() {
    if (!remove(".ids_head.pid")) //success
        LOG(INFO) << "[Monitor] remove .pid file";
     else
        LOG(ERROR) << "[Monitor] Error remove .pid file";
}


int Monitor::GetPidFile() {
    return 0;
	FILE *f;
	pid = 0;
	
	f = fopen(".ids_head.pid", "r+");
	
	if (f) {
		fscanf(f, "%d", &pid);
		fclose(f);
		
		return pid;
	} else {
        LOG(ERROR) << "[Monitor] Error read .pid file";
        //exit(EXIT_FAILURE);
	}
	
	return 0;
}

Monitor::Monitor(const char *argv[]) {
	std::string key = argv[1];
	
	if(key == "stop") {
        if (int pid = GetPidFile()){
            RemovePidFile();
            kill(pid, SIGTERM);
        }
		
		exit(0);
	} else {
        if (GetPidFile()){
            std::cout << "Program already run";
            exit(0);
        }

		config_file = argv[1];
	}
	
}

int Monitor::start() {

  /*  signal(SIGTERM, stop);
    pid = fork();
	if (pid == -1) {
        LOG(ERROR) << "[Monitor] Start IDS Daemon failed" << strerror(errno);
		return -1;
		
	} else if(!pid) {
        SetPidFile(getpid());
        umask(0);
        setsid();
*/
        //Load config
        Config config(this->config_file);
		
		if(!config.debug) {
			close(STDIN_FILENO);
			close(STDOUT_FILENO);
			close(STDERR_FILENO);
        }else {
            FLAGS_logbufsecs = 0; //switch off logger buffer
        }

        //initialize logger
        google::SetLogDestination(google::GLOG_INFO, config.log_file);
        google::InitGoogleLogging("IDS");

		{
            LOG(INFO) << "[Core] Init Storage...";
            Storage storage(&config.storage);

            zmq::context_t context(1);

            LOG(INFO) << "[Core] Init SolverBroker...";
            SolverBroker solverBroker(&config.solv_lisn, &context);


            LOG(INFO) << "[Core] Init DumpListener...";
            DumpListener dumpLisn(&config.dump_lisn, &storage, &context);

            dumpLisn.wait();
		}



         LOG(ERROR) << "PROGRAM CLOSE" << strerror(errno);
         google::ShutdownGoogleLogging();
		
/*		return 0;
		
	} else {

		return 0;
    }*/
}
