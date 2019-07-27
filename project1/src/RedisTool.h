#ifndef _H_REDIS_TOOLS_
#define _H_REDIS_TOOLS_
#include <iostream>
#include <vector>
#include <hiredis/hiredis.h>
#include "RedisConfig.h"

using namespace std;

namespace ll
{


class RedisTool
{
public:
    RedisTool();
    ~RedisTool();
    int setString(string key, string value);
    string getString(string key);

    int setList(string key,vector<int> value);
    vector<int> getList(string key);

private:
    void init();
    redisContext *m_redis;
    RedisConfig m_config;

};

}
#endif
