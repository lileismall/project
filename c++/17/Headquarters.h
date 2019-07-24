#pragma once
#include "OpenJudge.h"
/* #include "warrior.h" */

#if 1
class Headquarters
{
public:
    Headquarters(Color color, int elements)
        : _color(color)
          , _elements(elements)
          , _earnElements(0)
          , _nextWarriorIndex(0)
          , _warriorId(1)
    {}
    virtual ~Headquarters() { }
    //创建武士
    WarriorPtr create();
    //奖励胜利者
    void reward() { _elements -= 8;} //司令部减8个生命元，被奖赏者加8生命值
    //统计从城市获取的生命元
    void increaseElements(int elements) { _elements +=
        elements;}
    //设置所剩生命元的数量
    void setElements(int elements) { _elements = elements;  }
    template <typename Iterator>
        void setWarriorCreatingOrder(Iterator beg, Iterator end)
        { //设置武士生产顺序
            for(; beg != end; ++beg) {
                _warriorCreatingOrder.push_back(*beg);
            }
        }
    int getId() const { return _id;  }
    void setId(int id) { _id = id;  }
    Color getColor() const { return _color;  }
    int getElements() const { return _elements;  }
    vector<WarriorPtr> & getWarriors() { return _warriors;  }
/* private: */
public:
    //生产各种武士
    WarriorPtr createIceman(int id, int hp, int forces);
    WarriorPtr createLion(int id, int hp, int forces);
    WarriorPtr createWolf(int id, int hp, int forces);
    WarriorPtr createNinja(int id, int hp, int forces);
    WarriorPtr createDragon(int id, int hp, int forces);
    void nextWarriorType() { _nextWarriorIndex = (_nextWarriorIndex+1)%5; }
    WarriorType getNextWarriorType()
    {  return _warriorCreatingOrder[_nextWarriorIndex];  }

    void setOrder(vector<WarriorType> order)
        { _warriorCreatingOrder = order; }
    int getTokenerCount() { return _tokenerCount; }
    void addTokenerCount() { _tokenerCount++; }
    int getWarriorsId() { return _warriorId; }
    void addwarriorId() { _warriorId++; }
protected:
    Color _color;//红或者蓝
    int _id = 1;//编号, 0代表红色司令部, N+1 代表蓝色司令部
    int _elements;//当前司令部所剩的生命元
    int _earnElements;//一次战斗时刻结束后，所有武士获取的生命元
    int _nextWarriorIndex;//下次带生产的武士下标
    int _warriorId;  //制造的武士的编号
    vector<WarriorType> _warriorCreatingOrder;//武士生产顺序
    //一次战斗时间结束后，胜利的所有武士
    priority_queue<WarriorPtr, vector<WarriorPtr>>
        _winners;
    vector<WarriorPtr> _warriors;//生产的所有武士
    int _tokenerCount; //已经占领的武士数
    //各种类型武士的数量
    unordered_map<WarriorType, int> _warriorTypeAmounts;
};

class RedHeadquarters
: public Headquarters
{
public:
    RedHeadquarters(int elements)
        : Headquarters(RED, elements)
    {}
    
};

class BlueHeadquarters
: public Headquarters
{
public:
    BlueHeadquarters(int elements)
        : Headquarters(BLUE, elements)
    {}
};
#endif
