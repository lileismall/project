
#include "Headquarters.h"
/* #include "warrior.h" */

using namespace std;
#if 1
WarriorPtr Headquarters::create()
{
    GameConfig *conf = GameConfig::getInstance();
    WarriorType type = getNextWarriorType();
    /* WarriorType type = DRAGON_TYPE; */
    switch(type){
    case DRAGON_TYPE:
    {
        /* cout << _warriorId << endl; */
        WarriorPtr tmp = createDragon(_warriorId,conf->warriorInitalLife(DRAGON_TYPE),
                            conf->warriorInitalAttack(DRAGON_TYPE));
        /* cout << _warriorId << endl; */
        _warriors.push_back(tmp);
        return tmp;
    }
    //case NINJA_TYPE:
    //    return createNinja(_id,conf->warriorInitalLife(NINJA_TYPE),
    //                        conf->warriorInitalAttack(NINJA_TYPE));
    //case ICEMAN_TYPE:
    //    return createIceman(_id,conf->warriorInitalLife(ICEMAN_TYPE),
    //                        conf->warriorInitalAttack(ICEMAN_TYPE));
    //case LION_TYPE:
    //    return createLion(_id,conf->warriorInitalLife(LION_TYPE),
    //                        conf->warriorInitalAttack(LION_TYPE));
    //case WOLF_TYPE:
    //    return createDragon(_id,conf->warriorInitalLife(WOLF_TYPE),
    //                        conf->warriorInitalAttack(WOLF_TYPE));
    default:
        return NULL;
    }
}
#endif

WarriorPtr Headquarters::createDragon(int id, int hp, int forces)
{
    Dragon *dragon = new Dragon(_color,id,hp,forces,float(_elements/hp));
    /* dragon->show(); */
    return (WarriorPtr)dragon;
}

/* WarriorPtr createNinja(int id, int hp, int forces); */

/* WarriorPtr createIceman(int id, int hp, int forces); */
//WarriorPtr createLion(int id, int hp, int forces);
//
//WarriorPtr createWolf(int id, int hp, int forces);
