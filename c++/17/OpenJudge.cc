
#include "OpenJudge.h"
#include "Headquarters.h"

//配置文件读取
GameConfig *GameConfig::getInstance()
{
    if(_pInstance == NULL)
    {
        _pInstance = new GameConfig();
    }
    return _pInstance;
}

void GameConfig::destroy()
{
    if(_pInstance)
    {
        delete _pInstance;
        _pInstance = NULL;
    }
}

void GameConfig::readFromConsole()
{
}

void GameConfig::readFromFile(const string &filename)
{
    /* FILE *fp = fopen(filename.c_str(),"r+"); */  
    vector<WarriorType> types1 = {
        DRAGON_TYPE,
        NINJA_TYPE,
        ICEMAN_TYPE,
        LION_TYPE,
        WOLF_TYPE
    };
    setOrder(types1);
    /* _initWarriorOrder = types1; */
    ifstream in(filename);
    int tmp;
    in >> _groupsNum;
    vector<int> tmp_conf;
    InitData config;
    for(int j=0;j<_groupsNum;j++)
    {
        in >> config._initElements;
        in >> config._cityCount;
        in >> config._minutes;
        for(int i=0;i<5;i++)
        {
            in >> tmp;
            config._initLifes[_initWarriorOrder[i]] = tmp;
        }
        for(int i=0;i<5;i++)
        {
            in >> tmp;
            config._initAttacks[_initWarriorOrder[i]] = tmp;
        }
        _groups.push_back(config);
    }

    for(int i=0;i<_groupsNum;i++)
    {
        cout << _groups[i]._initElements<<" " <<_groups[i]._cityCount<<" " <<_groups[i]._minutes <<endl;
        for(int j=0;j<5;j++)
        {
            cout<<_groups[i]._initLifes[_initWarriorOrder[j]] <<" ";
        }
        cout << endl;
        for(int j=0;j<5;j++)
        {
            cout<<_groups[i]._initAttacks[_initWarriorOrder[j]] <<" ";
        }
        cout << endl;
    }
}

int GameConfig::cityCount()const
{
    return _groups[_currentGroupId]._cityCount;
}

int GameConfig::headquartersInitialElements()const
{
    /* cout << "_initElements:" << _groups[_currentGroupId]._initElements <<endl; */
    return _groups[_currentGroupId]._initElements;
}
int GameConfig::warriorInitalLife(WarriorType key) 
{
     /* cout <<toString(key)<< "类型初始生命值：" <<_groups[_currentGroupId]._initLifes[key] <<endl; */
    return _groups[_currentGroupId]._initLifes[key];
}

int GameConfig::warriorInitalAttack(WarriorType key)
{
    return _groups[_currentGroupId]._initAttacks[key];
}


//游戏时间控制
GameTime *GameTime::getInstance()
{
    if(_pInstance == NULL)
    {
        _pInstance = new GameTime();
    }
    return _pInstance;
}

void GameTime::destroy()
{
    if(_pInstance)
    {
        delete _pInstance;
        _pInstance = NULL;
    }
}

void GameTime::updateTime()
{
    _end = time(NULL);
    if(_end - _start < _end)
    {
        _start = time(NULL);
        _minute += 10;
        if(_minute == 60)
        {
            _minute = 0;
            _hour++;
        }
    }

}

void GameTime::showTime() const
{
    cout << _hour << "h " << _minute << "m " ;
}

GameTime *GameTime::_pInstance = getInstance(); //饱汗模式
GameConfig *GameConfig::_pInstance = getInstance();

#if 1
bool Dragon::redmarch()
{
    GameConfig *conf = GameConfig::getInstance();
    if(_cityId < conf->cityCount()) 
    {
        _cityId++;
        if(_cityId == conf->cityCount())
        {
            return true;
        }
    }
    return false;
}

bool Dragon::bluemarch()
{
    /* GameConfig *conf = GameConfig::getInstance(); */
    if(_cityId > 0)
    {
        _cityId--;
        if(_cityId == 0) 
        {
            return true;
        }
    }
    return false;
}

void Dragon::attack(WarriorPtr warrior)
{
    GameConfig *conf = GameConfig::getInstance();
    int hp = warrior->getHp();
    warrior->setHp(hp-conf->warriorInitalAttack(warrior->getType()));
}

void Dragon::defense(WarriorPtr warrior)
{
    GameConfig *conf = GameConfig::getInstance();
    int hp = warrior->getHp();
    warrior->setHp(hp-conf->warriorInitalAttack(warrior->getType())/2);
}

void Warrior::beRewarded()
{
    // 被奖励，从司令部获得8个生命元,司令部减去8个
    _hp += 8;
    
}

void Warrior::sentElementsToHeadquarters()
{
    _headquarters->increaseElements(_earnElements);
    _earnElements = 0;
}

#endif
