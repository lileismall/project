#pragma once

namespace ll
{

class NonCopy
{
public:
    NonCopy() {}
    ~NonCopy() {}

    NonCopy(const NonCopy &) = delete;
    NonCopy &operator=(const NonCopy &) = delete;
private:

};

}
