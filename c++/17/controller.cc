
#include "controller.h"
#include <algorithm>

using namespace std;


/* vector<WarriorType> types1 = { */
/*     DRAGON_TYPE, */
/*     DRAGON_TYPE, */
/*     DRAGON_TYPE, */
/*     DRAGON_TYPE, */
/*     DRAGON_TYPE, */
/* }; */

/* vector<WarriorType> types1 = { */
/*     DRAGON_TYPE, */
/*     NINJA_TYPE, */
/*     ICEMAN_TYPE, */
/*     LION_TYPE, */
/*     WOLF_TYPE */
/* }; */

void WarcraftWorld::init()
{
    vector<WarriorType> types1 = {
        DRAGON_TYPE,
        DRAGON_TYPE,
        DRAGON_TYPE,
        DRAGON_TYPE,
        DRAGON_TYPE,
    };
    GameConfig *conf = GameConfig::getInstance();
    _time = GameTime::getInstance();
    conf->readFromFile("file");
    /* _redHeadquarters->setWarriorCreatingOrder(types1.begin(),types1.end()); */
    /* _blueHeadquarters->setWarriorCreatingOrder(types1.begin(),types1.end()); */
    _redHeadquarters = new RedHeadquarters(conf->headquartersInitialElements());
    _blueHeadquarters = new BlueHeadquarters(conf->headquartersInitialElements());
    _redHeadquarters->setOrder(types1);
    _blueHeadquarters->setOrder(types1);
    //0代表红色司令部。N+1代表蓝色司令部
    City tmp(0);
    _cities.push_back(tmp); //第一个位置不用
    for(int i=1;i <= conf->cityCount();i++) //一次性将所有城市建好
    {
        City city(i);
        _cities.push_back(city);
    }
}


void WarcraftWorld::createWarrior()
{
    GameConfig *conf = GameConfig::getInstance();
    WarriorPtr redwarr = _redHeadquarters->create();
    redwarr->setCity(1);
    redwarr->setHeadquarters(_redHeadquarters);  //设置warrior的属性
    //每制造一个武士都会消耗生命元
    _redHeadquarters->setElements(_redHeadquarters->getElements() - redwarr->getHp());

    WarriorPtr bluewarr = _blueHeadquarters->create();
    bluewarr->setCity(conf->cityCount());
    bluewarr->setHeadquarters(_blueHeadquarters);
    _blueHeadquarters->setElements(_redHeadquarters->getElements() - redwarr->getHp());

    //每次创建完，要将warriorId加1
    _redHeadquarters->addwarriorId();
    _blueHeadquarters->addwarriorId();

    /* redwarr->show(); */
    WarriorView redwa(redwarr);
    WarriorView bluewa(bluewarr);

    showTime();
    redwa.showBorn();
    showTime();
    bluewa.showBorn();
    updateTime();
}

bool WarcraftWorld::warriorMarch()
{
    for(auto &s : _redHeadquarters->getWarriors())
    {
        if(s->redmarch())  //判断是否抵达司令部
        {
            _redHeadquarters->addTokenerCount();
            WarriorView view(s);
            showTime();
            view.showReachDestination();
        }
        WarriorView warr(s);
        showTime();
        warr.showMarch();
        _cities[s->getCityId()].attach(s); //武士进入城市，告诉城市一声
    }

    for(auto &s : _blueHeadquarters->getWarriors())
    {
        if(s->bluemarch())  //判断是否抵达司令部
        {
            _blueHeadquarters->addTokenerCount();
            WarriorView view(s);
            showTime();
            view.showReachDestination();
        }
        WarriorView warr(s);
        showTime();
        warr.showMarch();
        _cities[s->getCityId()].attach(s); //武士进入城市，告诉城市一声
    }

    updateTime();

    if(checkRedHeadquartersBeTaken())
    {
        cout << "*************************" <<endl;
        HeadquartersView view(_redHeadquarters);
        showTime();
        view.showBeTaken();
        return true;
    }
    if(checkBlueHeadquartersBeTaken())
    {
        HeadquartersView view(_blueHeadquarters);
        showTime();
        view.showBeTaken();
        return true;
    }
    return false;
}


bool WarcraftWorld::checkRedHeadquartersBeTaken()
{
    if(_redHeadquarters->getTokenerCount() == 2)
    {
        return true;
    }else{
        return false;
    }
}

bool WarcraftWorld::checkBlueHeadquartersBeTaken()
{
    if(_blueHeadquarters->getTokenerCount() == 2)
    {
        return true;
    }else{
        return false;
    }
}

void WarcraftWorld::cityProduceElements()
{
    for(auto &city : _cities)
    {
        city.produceElements(); //每一个城市生产10个生命元
    }
    updateTime();
}

void WarcraftWorld::takeCityElements()
{

    for(auto &s : _redHeadquarters->getWarriors())
    {
        s->setEarnelement(_cities[s->getCityId()].getelement());
        WarriorView view(s);
        showTime();
        view.showEarnElements();
        s->sentElementsToHeadquarters();
        s->setEarnelement(0);

    }
    for(auto &s : _blueHeadquarters->getWarriors())
    {
        s->getEarnElements() += _cities[s->getCityId()].getelement();
        WarriorView view(s);
        showTime();
        view.showEarnElements();
        s->sentElementsToHeadquarters();
    }
    updateTime();
}

void WarcraftWorld::battle()
{
    for(auto &s : _cities)
    {
        if(s.getRedWarriors().size() && s.getBlueWarriors().size())
        {
            WarriorPtr warrior1 = s.getRedWarriors()[0];
            WarriorPtr warrior2 = s.getBlueWarriors()[0];
            showTime();
            BattleView view(warrior1,warrior2);
            view.showAttack();
            s.startBattle();
            if(s.getWinner() == NULL)
            {
                showTime();
                view.showDefense();
            }

            //打完之后即可将其扔出城外
            s.detach();
        }
    }
    updateTime();
}

void WarcraftWorld::headquartersReportElements()
{
    HeadquartersView redhead(_redHeadquarters);
    HeadquartersView bluehead(_blueHeadquarters);

    showTime();
    redhead.showLeftElements();
    showTime();
    bluehead.showLeftElements();
    updateTime();
}



