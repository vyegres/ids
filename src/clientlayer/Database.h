#ifndef __ids_head__Database__
#define __ids_head__Database__

#include "../Config.h"
#include "../logiclayer/STrafficManager.h"


class Database {
public:
    virtual int insert(tMessage2s message) = 0;
    virtual void get() = 0;
    virtual int remove() = 0;
};

#endif /* defined(__ids_head__Database__) */
