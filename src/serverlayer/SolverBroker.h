#ifndef __ids_head__SolverBroker__
#define __ids_head__SolverBroker__

#include "../Config.h"
#include <boost/thread.hpp>
#include <zmq.hpp>
#include <glog/logging.h>

class SolverBroker {
public:
    SolverBroker(solv_lisn_cfg *cfg, zmq::context_t *context);


private:
    zmq::context_t* context;
    zmq::socket_t receivers;
    zmq::socket_t analyzers;

    static void start(void *arg);
    boost::thread starter;
};


#endif /* defined(__ids_head__SolverBroker__) */
