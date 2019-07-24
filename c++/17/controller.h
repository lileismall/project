#pragma once
#include "OpenJudge.h"
#include "Headquarters.h"
#include "view.h"
#include "city.h"
#include "view.h"

class WarcraftWorld
{
public:
    explicit
        WarcraftWorld()
        : _redHeadquarters(nullptr)
          , _blueHeadquarters(nullptr)
    { init();  }

    void start()//游戏开始
    {
        /* int i=0; */
        while(1) {
            createWarrior();
            if(warriorMarch())
            { break;  }
            cityProduceElements();
            takeCityElements();
            battle();
            headquartersReportElements();
            cout << "-----------------------" <<endl;
            /* i++; */
        }
    }
    template <typename Iterator>
        void setRedWarriorCreatingOrder(Iterator beg, Iterator end);
    template <typename Iterator>
        void setBlueWarriorCreatingOrder(Iterator beg, Iterator end);
    ~WarcraftWorld()
    {
        if(_redHeadquarters) delete _redHeadquarters;
        if(_blueHeadquarters) delete _blueHeadquarters;
        
    }
/* private: */
public:
    void init();
    //------------事件begin-----------
    void createWarrior(); //整点：创建武士
    bool warriorMarch(); //第10分: 武士行军
    void cityProduceElements(); //第20分：城市生产生命元
    void takeCityElements(); //第30分：武士取走城市中的生命元

    void battle(); //第40分：战斗
    void headquartersReportElements(); //第50分：司令部报告情况
    //------------事件end ------------
    bool createWarrior(Headquarters *);//某个司令部开始创建武士
    void warriorMarch(Headquarters * headquarters);//某个司令部中的武士行
    bool checkRedHeadquartersBeTaken();//判断红司令部是否被占领
    bool checkBlueHeadquartersBeTaken();//判断蓝司令部是否被占领

    void showTime() { _time->showTime(); }
    void updateTime() { _time->updateTime(); }
    private:
    RedHeadquarters * _redHeadquarters;//红色司令部
    BlueHeadquarters * _blueHeadquarters;//蓝色司令部
    vector<City> _cities;//所有的城市,其中 0号代表红色司令部， size - 1 代表蓝色司令部
    GameTime *_time;
};

