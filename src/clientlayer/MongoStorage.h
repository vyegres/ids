#ifndef __ids_head__MongoStorage__
#define __ids_head__MongoStorage__

#include "Database.h"
#include <glog/logging.h>

class MongoStorage : public Database{
public:
    MongoStorage(db_cfg &dbc);
    int insert(tMessage2s message);
    void get();
    int remove();
private:
    struct db_cfg *dbc;
    char addr[255];
    char collection[255];
};

#endif /* defined(__ids_head__MongoStorage__) */

