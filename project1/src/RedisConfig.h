#pragma once
#include <string>


namespace ll
{


class RedisConfig
{
public:
    RedisConfig() {}
    ~RedisConfig() {}
    std::string getRedisIP()
    {
        return "127.0.0.1";
    }
    int getRedisPort()
    {
        return 6379;
    }

};



}
