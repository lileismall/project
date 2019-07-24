
#include "OpenJudge.h"
#include "Headquarters.h"
#include "city.h"
#include "view.h"
#include "controller.h"

using namespace std;

/* vector<WarriorType> types1 = { */
/*     DRAGON_TYPE, */
/*     NINJA_TYPE, */
/*     ICEMAN_TYPE, */
/*     LION_TYPE, */
/*     WOLF_TYPE */
/* }; */

/* void test0() */
/* { */
/*     GameConfig *conf = GameConfig::getInstance(); */
/*     /1* cout << conf->cityCount() <<endl; *1/ */
/*     /1* cout << conf->headquartersInitialElements() <<endl; *1/ */
/*     Headquarters test1(RED,conf->headquartersInitialElements()); */
/*     Headquarters test2(BLUE,conf->headquartersInitialElements()); */
/*     test1.setOrder(types1); */
/*     cout << " rer " <<endl; */
/*     /1* Headquarters test(RED,200); *1/ */
/*     /1* RedHeadquarters test(conf->headquartersInitialElements()); *1/ */
/*     WarriorPtr aa = test1.create(); */
/*     aa->show(); */
/* } */

/* void test1() */
/* { */
/*     GameConfig *conf = GameConfig::getInstance(); */
/*     Headquarters test1(RED,conf->headquartersInitialElements()); */
/*     Headquarters test2(BLUE,conf->headquartersInitialElements()); */
/*     test1.setOrder(types1); */
/*     test2.setOrder(types1); */
/*     WarriorPtr aa = test1.create(); */
/*     WarriorPtr bb = test2.create(); */
/*     aa->show(); */
/*     bb->show(); */
/*     City city(1,10); */
/*     city.attach(aa); */
/*     city.attach(bb); */
/*     city.startBattle(); */
/*     aa->show(); */
/*     bb->show(); */
/* } */

#if 0
void test2()
{
    GameConfig *conf = GameConfig::getInstance();
    Headquarters test1(RED,conf->headquartersInitialElements());
    Headquarters test2(BLUE,conf->headquartersInitialElements());
    test1.setOrder(types1);
    test2.setOrder(types1);
    WarriorPtr aa = test1.create();
    WarriorPtr bb = test2.create();
    City city(1,10);
    city.attach(aa);
    city.attach(bb);

    HeadquartersView headview(&test1); 
    headview.showLeftElements();
    headview.showBeTaken();

    BattleView battleview(aa,bb);
    battleview.showAttack();
    battleview.showDefense();

    WarriorView warriorview(aa);
    warriorview.showBorn();
    warriorview.showDeath();
    warriorview.showMarch();
    warriorview.showEarnElements();
    warriorview.showReachDestination();
    
    DragonView drview(aa);
    drview.showBorn();

    CityView cityview(&city);
    cityview.showFlag();



}

void test3()
{
    GameConfig *conf = GameConfig::getInstance();
    Headquarters test1(RED,conf->headquartersInitialElements());
    Headquarters test2(BLUE,conf->headquartersInitialElements());
    test1.setOrder(types1);
    test2.setOrder(types1);
    WarriorPtr aa = test1.create();
    WarriorPtr bb = test2.create();
    City city(1,10);
    city.attach(aa);
    city.attach(bb);

    WarcraftWorld test;
    test.start();
}
#endif

int main()
{
    /* GameConfig *test = GameConfig::getInstance(); */
    /* test->readFromFile("file"); */
    WarcraftWorld test;
    test.start();
    cout << " 游戏结束" <<endl;
}
