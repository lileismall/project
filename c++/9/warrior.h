#pragma once

#include <iostream>
#include <string>


using namespace std;

string RB[2]={"red","blue"};
string POS[5]={"dragon","ninja","iceman","lion","wolf"};
string WEA[3]={"sword","bomb","arrow"};
enum position{
    dragon,ninja,iceman,lion,wolf
};

enum rb{
    red,blue
};

enum weapon{
    sword,bomb,arrow
};

class Warrior
{
private:
    int _num;
    int _life;
    rb _rb;
    position _position;
public:
    Warrior() {}

    Warrior(int num,int life,rb rb,position position) // 编号，生命值，红蓝方(red 0  blue 1)
    : _num(num)
    , _life(life)
    , _rb(rb)
    , _position(position)
    {}

    ~Warrior(){}

    void show()
    {
        cout << "num:" << _num<<endl;
        cout << "life:" << _life<<endl;
    }

    void display()
    {
        cout << _num << RB[_rb] <<"出生了一名编号为:" << _num <<"的" << POS[_position] <<endl;
    }

protected:

    int getNum()
    {
        return _num;
    }
    int getLife() {return _life;}
    int getRb() {return _rb;}

};


class Dragon
:public Warrior
{
private:
    weapon _weapon;  //武器sword, bomb,和arrow，编号分别为0,1,2
    double _morale; // 士气值
public:
    Dragon(int num,int life,rb rb,position position,weapon weapon,double morale)
    : Warrior(num,life,rb,position)
    , _weapon(weapon)
    , _morale(morale)
    {}

    void display()
    {
        Warrior::display();
        cout << "it have a" << WEA[_weapon] << "and its is " << _morale<<endl; 
    }


};



int main()
{
    int ccase=0,i=0;
    cin >> ccase;
    int num = 0;  //时间
    int lifedragon=50,lifesum=200;


    //测试几次
    for(i=0;i < ccase;i++)
    {
        while(lifesum > 50) 
        {
            Dragon dragontest1(num,lifedragon,red,dragon,arrow,lifesum/lifedragon);
            dragontest1.display();
            lifesum -= 50;
        }


    }

    return 0;
}
