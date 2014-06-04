#include "Storage.h"

int Storage::insert(tMessage2s message){
    this->tafficDB->insert(message);
}
Storage::Storage(storage_cfg* storage_cfg){
    LOG(INFO) << "[Storage] DataProvider tafficDB" << storage_cfg->trafficDB.provider;
    LOG(INFO) << "[Storage] DataProvider eventDB" << storage_cfg->eventDB.provider;

    if (strcasecmp(storage_cfg->eventDB.provider,"MongoDB") == 0)
       this->eventDB = new  MongoStorage(storage_cfg->eventDB);

    if (strcasecmp(storage_cfg->trafficDB.provider,"MongoDB") == 0)
       this->tafficDB = new MongoStorage(storage_cfg->trafficDB);

}
