
#include "view.h"

using namespace std;

void HeadquartersView::showLeftElements() const
{
    cout << _headquarters->getElements() << " elements in " 
        << toString(_headquarters->getColor()) << " headquarters" <<endl;
}

void HeadquartersView::showBeTaken() const
{
    cout << toString(_headquarters->getColor()) << " headquarters is token" <<endl; 
}

void BattleView::showAttack() const
{
    cout << toString(_warrior1->getColor()) << " " << toString(_warrior1->getType()) << " "
    << _warrior1->getId() << " attacked " 
    << toString(_warrior2->getColor()) << " " << toString(_warrior2->getType()) << " "
    <<"in city " << _warrior1->getCityId() << " with " 
    << _warrior1->getElements() << " and force " << _warrior1->getForces() << endl;
}

void BattleView::showDefense() const
{
    cout << toString(_warrior2->getColor()) << " " << toString(_warrior2->getType()) 
        << " " << _warrior2->getId() << " fought back against "
        << toString(_warrior1->getColor()) << " " << toString(_warrior1->getType())
        << " " << _warrior1->getId() << " in city " << _warrior1->getCityId()<<endl;
}

void WarriorView::showBorn() const
{
    cout << toString(_warrior->getColor()) << " " 
        << toString(_warrior->getType()) <<" " << _warrior->getId()
        << " born"  << endl;
}

void WarriorView::showMarch() const
{
    cout << toString(_warrior->getColor()) <<" " << toString(_warrior->getType()) << " "
        << _warrior->getId() << " marched to city " << _warrior->getCityId()
        << " with " << _warrior->getElements() << " elements and force "
        << _warrior->getForces() << endl;
}

void WarriorView::showEarnElements() const
{
    cout << toString(_warrior->getColor()) << " " << toString(_warrior->getType()) 
        << " " << _warrior->getId() << " earned " << _warrior->getEarnElements()
        << " for his headquarter" << endl;
}

void WarriorView::showReachDestination() const
{
    cout << toString(_warrior->getColor()) << " " << toString(_warrior->getType())
        << " " << _warrior->getId() << " reached " 
        << (_warrior->getColor() == BLUE ? toString(RED) : toString(BLUE))
        << " with " << _warrior->getElements() 
        << " and force " << _warrior->getForces() << endl;
}

void WarriorView::showDeath() const
{
    cout << toString(_warrior->getColor()) << " " << toString(_warrior->getType())
        << " " << _warrior->getId() << " was killed in city " << _warrior->getCityId() << endl;
}


void DragonView::showYell() const
{
    cout << toString(_warrior->getColor()) << " " << toString(_warrior->getType())
        << " " << _warrior->getId() << " yelled in city " << _warrior->getCityId() << endl;
}


void CityView::showFlag() const
{
    cout << _city->getFlag() << " flag raised in city "
        << _city->getId() << endl;
}
