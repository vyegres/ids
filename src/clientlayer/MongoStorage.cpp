#include "MongoStorage.h"
#include <mongo/client/dbclient.h>


MongoStorage::MongoStorage(db_cfg &dbc){
    this->dbc = &dbc;
    sprintf(this->addr, "%s:%d",this->dbc->ip, this->dbc->port);
    sprintf(this->collection, "%s.%s", this->dbc->db_name, this->dbc->dump_collection);

    LOG(INFO) << "[Database] Configured...";
}

int MongoStorage::insert(tMessage2s message){
    try {
        //boost::scoped_ptr<mongo::ScopedDbConnection> conn(mongo::ScopedDbConnection::getScopedDbConnection(addr));
        mongo::ScopedDbConnection conn(this->addr);

        mongo::BSONObjBuilder builder;
        builder
               //.append("ts",  message.ts)
               .append("len", message.len)
               .append("ip_src", message.ip_src)
               .append("ip_dst", message.ip_dst)
               .append("port_src", message.port_src)
               .append("port_dst", message.port_dst)
               .append("protokol1", message.protokol1)
               .append("protokol2", message.protokol2)
               .append("protokol3", message.protokol3);
               //.append("ip_src", message.ip_src)
               //.append("ip_src", message.ip_src);
           //    .appendBinData("payload",len, mongo::BinDataGeneral, payload);

       // uint8_t* packet1[];
      //  uint8_t* packet2[];
       // uint8_t* packet3[];

        conn->insert(this->collection, builder.obj());
        LOG(INFO) << "[Database] Insert dump to collection";

    } catch( const mongo::DBException &e ) {
        LOG(ERROR) << "[Database] Dump exception:" << e.what();
    }
}

void MongoStorage::get(){

}

int MongoStorage::remove(){

}


