#ifndef __ids_head__Storage__
#define __ids_head__Storage__
#include <glog/logging.h>
#include "../logiclayer/STrafficManager.h"
#include "MongoStorage.h"

class Storage {
public:
    Storage(storage_cfg* storage_cfg);
    virtual int insert(tMessage2s message);
    void get(){}
    int remove(){}
private:
    Database *eventDB;
    Database *tafficDB;
};

#endif /* defined(__ids_head__Storage__) */
