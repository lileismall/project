#pragma once
#include "OpenJudge.h"

class City
{
public:
    City(size_t id, size_t elements = 0)
        : _flag(Color::NOTSET)
          , _id(id)
          , _elements(elements)
          , _redWinCount(0)
          , _blueWinCount(0)
    {}
    void produceElements();//城市生产生命元
    void attach(WarriorPtr);//某武士进入该城市
    void detach();//某武士离开该城市
    void startBattle();//开始战斗
    void takenBy();//生命元被某武士取走
    size_t getId() const { return _id;  }
    int getelement() { int tmp = _elements;_elements = 0;
        return tmp; } //返回生命元后置为0
    Color getFlag() const { return _flag;  }
    size_t getWarriorAmount() const //用来判断是否决斗
    { return _redWarriors.size() + _blueWarriors.size();  }
    vector<WarriorPtr> & getRedWarriors() { return _redWarriors;  }
    vector<WarriorPtr> & getBlueWarriors() { return _blueWarriors;
    }
    WarriorPtr &getWinner() { return _winer;  }
private:
    void battle(WarriorPtr warrior1, WarriorPtr warrior2);//2名武士的具
    bool isChangingFlag(WarriorPtr warrior);//是否更换旗子
private:
    Color _flag;//城市旗子的颜色
    size_t _id;//城市编号
    size_t _elements;//城市生命元
    size_t _redWinCount;//红魔军连续胜利次数
    size_t _blueWinCount;//蓝魔军连续胜利次数
    vector<WarriorPtr> _redWarriors; //存放进入城市的武士
    vector<WarriorPtr> _blueWarriors;
    WarriorPtr _winer = 0;  // 胜利者,或者城市只有一个武士
};
