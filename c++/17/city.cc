#include "city.h"

using namespace std;

void City::produceElements()
{
    _elements += 10;
}

void City::attach(WarriorPtr warrior)
{
    if(warrior->getColor() == RED)
    {
        _redWarriors.push_back(warrior);
    }else{
        _blueWarriors.push_back(warrior);
    }
}

void City::detach()
{
    if(_redWarriors[0] != NULL)
    {
        _redWarriors.pop_back();
    }
    if(_blueWarriors[0] != NULL)
    {
        _blueWarriors.pop_back();
    }
}

void City::startBattle()
{
    WarriorPtr redwarr = _redWarriors.front();
    WarriorPtr bluewarr = _blueWarriors.front();
    if(_flag == RED)
    {
        redwarr->attack(bluewarr);
        if(bluewarr->getHp() > 0)
        {
            bluewarr->defense(redwarr);
            if(redwarr->getHp() <= 0)
            {
                _winer = bluewarr;
            }
        }else{
            _winer = redwarr;
        }
    }else {
        if(_flag == BLUE)
        {
            bluewarr->attack(redwarr);
            if(redwarr->getHp() > 0)
            {
                redwarr->defense(bluewarr);
                if(bluewarr->getHp() <= 0)
                {
                    _winer = redwarr;
                }
            }else{
                _winer = bluewarr;
            }
        }else{
            if(_id%2 == 1) //奇数
            {
                redwarr->attack(bluewarr);
                if(bluewarr->getHp() > 0)
                {
                    bluewarr->defense(redwarr);
                    if(redwarr->getHp() <= 0)
                    {
                        _winer = bluewarr;
                    }
                }else{
                    _winer = redwarr;
                }
            }else{
                bluewarr->attack(redwarr);
                if(redwarr->getHp() > 0)
                {
                    redwarr->defense(bluewarr);
                    if(bluewarr->getHp() <= 0)
                    {
                        _winer = redwarr;
                    }
                }else{
                    _winer = bluewarr;
                }
            }
        }
    }
}

/* void City::takenBy() */
/* { */
/*     _winer->sentElementsToHeadquarters(_elements); */
/*     _elements = 0; //城市生命元被武士全部取走 */
/* } */
