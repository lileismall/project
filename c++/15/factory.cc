
#include <iostream>

using namespace std;
//单核  
class SingleCore   
{  
public:  
    virtual void Show() = 0;
};  
class SingleCoreA: public SingleCore    
{  
public:  
    void Show() { cout<<"Single Core A"<<endl;  }  
};  
class SingleCoreB :public SingleCore  
{  
public:  
    void Show() { cout<<"Single Core B"<<endl;  }  
};  
//多核  
class MultiCore    
{  
public:  
    virtual void Show() = 0;
};  
class MultiCoreA : public MultiCore    
{  
public:  
    void Show() { cout<<"Multi Core A"<<endl;  }  

};  
class MultiCoreB : public MultiCore    
{  
public:  
    void Show() { cout<<"Multi Core B"<<endl;  }  
};  
//工厂  
class CoreFactory    
{  
public:  
    int da;
    virtual SingleCore* CreateSingleCore() ;
    virtual MultiCore* CreateMultiCore() ;
};  
//工厂A，专门用来生产A型号的处理器  
class FactoryA :public CoreFactory  
{  
public:  
    SingleCore* CreateSingleCore() { return new SingleCoreA();  }  
    MultiCore* CreateMultiCore() { return new MultiCoreA();  }  
};  
//工厂B，专门用来生产B型号的处理器  
class FactoryB : public CoreFactory  
{  
public:  
    SingleCore* CreateSingleCore() { return new SingleCoreB();  }  
    MultiCore* CreateMultiCore() { return new MultiCoreB();  }  
}; 

class FactoryC : public CoreFactory
{
public:
    SingleCore* CreateSingleCore() { return new SingleCoreB();  }  
    MultiCore* CreateMultiCore() { return new MultiCoreB();  }  
};

int main()
{
    CoreFactory *tt = new FactoryA();

    tt->CreateMultiCore()->Show();

    FactoryA test;
    test.CreateSingleCore()->Show();
}

