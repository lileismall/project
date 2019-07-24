#pragma once
#include "OpenJudge.h"
#include "Headquarters.h"
#include "city.h"

class HeadquartersView
{
public:
    HeadquartersView(Headquarters *headquarters) : _headquarters(headquarters) {}
    ~HeadquartersView() {}

    //司令部报告情况时
    void showLeftElements() const;
    //司令部被占领时
    void showBeTaken() const;
private:
    Headquarters *_headquarters;
};

class BattleView
{
public:
    BattleView(WarriorPtr warrior1, WarriorPtr warrior2)
        : _warrior1(warrior1)
          , _warrior2(warrior2)
    {}
    //武士主动攻击时
    void showAttack() const;
    //武士反击时
    void showDefense() const;
private:
    WarriorPtr _warrior1; //主动攻击者
    WarriorPtr _warrior2; //反击者
};

class WarriorView
{
public:
    WarriorView(WarriorPtr warrior)
        : _warrior(warrior)
    {}
    void showBorn() const;//武士出生时
    void showMarch() const;//武士行军时
    void showEarnElements() const;//武士取走城市生命元时
    void showReachDestination() const;//武士到达敌方司令部时
    void showDeath() const ; //武士战死

/* protected: */
/*     void showName() const; */
/*     void showToCity() const; */
/*     void showInCity() const; */
/*     void showDeath() const; */
/*     void showElementsAndForces() const; */

protected:
    WarriorPtr _warrior;
};

class DragonView
: public WarriorView
{
public:
    DragonView(WarriorPtr warrior)
        : WarriorView(warrior)
    {}
    //dragon 在一次在它主动进攻的战斗结束后，如果还没有战死，就会欢呼。
    void showYell() const;
};

class CityView
{
public:
    CityView(City * city) : _city(city) {}
    //城市更换旗子时
    void showFlag() const;
    private:
    City * _city;
};
