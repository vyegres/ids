#include "SolverBroker.h"


SolverBroker::SolverBroker(solv_lisn_cfg *cfg, zmq::context_t *context)
    :receivers(*context, ZMQ_PULL),
    analyzers(*context, ZMQ_PUB)
{
    this->context = context;

    try
    {
        char addr[255];
        sprintf(addr, "%s://%s:%d", cfg->protocol, cfg->ip, cfg->port);

        this->analyzers.bind(addr);
        LOG(INFO) << "[SolverBroker] Listner analyzers: " << addr;

        this->receivers.bind("inproc://solver_broker");

        starter = boost::thread(boost::bind(start, this));
    }
    catch(const zmq::error_t& ze)
    {
        LOG(ERROR) << "[SolverBroker] Listner exception: " << ze.what();
    }
}


void SolverBroker::start(void *arg) {

    LOG(INFO) << "[SolverBroker] Starting...";

    SolverBroker *self = static_cast<SolverBroker *>(arg);

    zmq_proxy(self->receivers, self->analyzers, NULL);
}
