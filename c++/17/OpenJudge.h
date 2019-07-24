#pragma once

/* #include "Headquarters.h" */

#include <ctime>
#include <iostream>
#include <string>
#include <stdio.h>
#include <map>
#include <vector>
#include <unistd.h>
#include <fstream>
#include <memory>
#include <queue>
#include <unordered_map>


#define TIME 1 //现实1秒游戏时间10分钟
using namespace std;
#define WarriorPtr Warrior*

#define WARRIOR 1
#define HEAD 0

enum Color {
    RED,
    BLUE,
    NOTSET
};
enum WarriorType {
    DRAGON_TYPE,
    NINJA_TYPE,
    ICEMAN_TYPE,
    LION_TYPE,
    WOLF_TYPE
};

//为了通过某种颜色或者武士类型，得到字符串，所以实现了以下inline函数.
inline string toString(Color color)
{
    return (color == RED) ? string("red"): string("blue");
}
inline string toString(WarriorType type)
{
    switch(type) {
    case DRAGON_TYPE: return "dragon";
    case NINJA_TYPE: return "ninja";
    case ICEMAN_TYPE: return "iceman";
    case LION_TYPE: return "lion";
    case WOLF_TYPE: return "wolf";
    default:
                    return string();
    }
}

class GameConfig
{
public:
    static GameConfig * getInstance();
    static void destroy();
    void readFromConsole();//从控制台终端获取测试数据
    void readFromFile(const string & filename);//从配置文件中获取测试数据
    void nextGroupId() { ++_currentGroupId;  }//测试下一组数据
    int groups() const { return _groups.size();  }
    int currentGroupId() const { return _currentGroupId;  }
    int cityCount() const;
    int headquartersInitialElements() const;
    int warriorInitalLife(WarriorType key);
    int warriorInitalAttack(WarriorType key);

    void setOrder(vector<WarriorType> order) 
        { _initWarriorOrder = order; }
private:
    GameConfig() : _currentGroupId(0){ cout << "GameConfig()" <<
        endl; }
    ~GameConfig(){ cout << "~GameConfig()" << endl;  }
    void readFromStream(istream & is);
    struct InitData
    {
        int _initElements;
        int _cityCount;
        int _minutes;
        map<WarriorType, int> _initLifes;
        map<WarriorType, int> _initAttacks;

    };
public:
    vector<InitData> _groups;//N组数据
private:
    static GameConfig * _pInstance;
    int _currentGroupId;//当前正在测试的一组数据
    vector<WarriorType> _initWarriorOrder;//输入时武士的生命值和攻击力的设置顺序
    int _groupsNum; //一共测试组数
};


class GameTime
{
public:
    static GameTime * getInstance();
    static void destroy();
    void showTime() const;//打印时间
    void updateTime();//更新时间
    void reset() { _hour = 0; _minute = 0;  }
private:
    GameTime(int hour = 0, int minute = 0)
        : _hour(hour)
          , _minute(minute)
    {}
private:
    static GameTime * _pInstance;
    int _hour;
    int _minute;
    long _start = time(NULL); //用来控制多长时间刷新一次
    long _end = time(NULL);
};

#if 1
//武士类
class Headquarters;
class Warrior
/* : public std::enable_shared_from_this<Warrior> */
{
public:
    Warrior(){}
    Warrior(Color color,
            const string & name,
            int id,
            int hp,
            int forces,
            WarriorType type)
        : _color(color)
          , _name(name)
          , _id(id)
          , _hp(hp)
          , _forces(forces)
          , _type(type)
    {}
    virtual ~Warrior(){ }
    virtual bool redmarch();//行军
    virtual bool bluemarch();//行军
    virtual void attack(WarriorPtr warrior){}//攻击另一个武士
    virtual void defense(WarriorPtr warrior){}//反击另一个武士
    void beWinner();//成为胜利者
    void beRewarded();//被奖励
    void sentElementsToHeadquarters();//将获得的生命元发给司令部
    void setHp(int hp) { _hp = hp;  }
    void setCity(int id) { _cityId = id;  }
    void setEarnelement(int earn) { _earnElements = earn; }
    void setHeadquarters(Headquarters * headquarters)
    { _headquarters = headquarters;  }
    Color getColor() const { return _color;  }
    string getName() { return _name;  }
    int getId() const { return _id;  }
    int getHp() const { return _hp;  }
    int getCityId() const { return _cityId;  }
    /* int getElements() const { return _hp;  } */
    int &getEarnElements() { return _earnElements;  }
    int getForces() const { return _forces;  }
    WarriorType getType() const { return _type;  }
    void show()
    {
        cout << "color:" << toString(_color)<<" ";
        cout << "hp:" << _hp << " "  << "forces:" <<_forces << " " 
            <<"cityId:" <<_cityId <<endl;
    } 

protected:
    Color _color = RED;
    string _name = "test";
    int _id;//编号
    int _hp;//生命值
    int _forces;//攻击力
    int _cityId;//位于某个城市
    int _earnElements;//从某个城市中获取的生命元
    WarriorType _type = DRAGON_TYPE;
    Headquarters *_headquarters;
};

class Dragon
: public Warrior
{
public:
    Dragon(){}
    Dragon(Color color, int id, int hp, int forces, float
           morale)
        : Warrior(color, "dragon", id, hp, forces,DRAGON_TYPE)
          , _morale(morale)
    {}
    float getMorale() const { return _morale;  }
    bool redmarch();//行军
    bool bluemarch();//行军
    void attack(WarriorPtr warrior);//攻击另一个武士
    void defense(WarriorPtr warrior);//反击另一个武士
    void show()
    {
        cout << "color:" << toString(_color) << " " 
            << "id:" << _id <<endl;
    }
private:
    float _morale;

};
class Ninja
: public Warrior
{
public:
    Ninja(Color color, int id, int hp, int forces)
        : Warrior(color, "ninja", id, hp, forces, NINJA_TYPE)
    {}
    //ninja 挨打了也从不反击敌人，需覆盖
    virtual void defense(WarriorPtr warrior) override
    {
        warrior->getType(); //只是为了不报未使用
    }
};
class Iceman
: public Warrior
{
public:
    Iceman(Color color, int id, int hp, int forces)
        : Warrior(color, "iceman", id, hp, forces, ICEMAN_TYPE)
          , _steps(0)
    {}
    //iceman 每前进两步，在第2步完成的时候，生命值会减少9，攻击力会增加20。
    ////但是若生命值减9后会小于等于0，则生命值不减9,而是变为1。即iceman不会因走多了
    //而死。
    ////需覆盖
    /* virtual bool redmarch() override; */
    /* virtual bool bluemarch() override; */
private:
        int _steps;//前进的步数

};

class Lion
: public Warrior
{
public:
    Lion(Color color, int id, int hp, int forces, int loyalty)
        : Warrior(color, "lion", id, hp, forces, LION_TYPE)
          , _loyalty(loyalty)
    {}

    int getLoyalty() const { return _loyalty;  }
private:
    int _loyalty;

};

class Wolf
: public Warrior
{
public:
    Wolf(Color color, int id, int hp, int forces)
        : Warrior(color, "wolf", id, hp, forces, WOLF_TYPE)
          , _killTimes(0)
    {}
    /*
     * 在一个wolf 通过主动攻击杀死敌人的次数达到偶数的时刻（次数从1开始算），在战斗完
     * 成后，该 wolf 生命 值和攻击力都增加1倍。如果其杀死的敌人是lion,则攻击力和生命
     * 值先加倍，然后才吸取lion的生命值。获取 总部的生命元奖励，发生在加倍之后。只有在
     * 主动攻击杀死敌人时才能有加倍的事情，反击杀死敌人则不不会发 生加倍。
     * 需覆盖
     * */
    virtual void attack(WarriorPtr warrior) override;
private:
    int _killTimes;//击杀次数

};
#endif
