#include <iostream>
#include <string>
using namespace std;

class Person
{
private:
    string _name;
    int _age;
public:
    Person()
    : _age(0)
    {}

    Person(const string name,int age)
    : _name(name)
    , _age(age)
    {}

    void display()
    {
        cout << "name:" <<_name<<endl;
        cout << "age :" <<_age<<endl;
    }
    
};

class Employee
:public Person
{
private:
     string _department;
     int _salary;
public:
     Employee()
     : _department()
     , _salary(0)
    {}

     Employee(string name,int age,string department,int salary)
     : Person(name,age)    
     , _department(department)
     , _salary(salary)
    {}

     void display()
     {
         Person::display();
         cout << "department:" <<_department<<endl;
         cout << "salary:    "<< _salary<<endl;
     }

     int getSalary()
     {
         return _salary;
     }
};

int main()
{
    Employee test1("lieli",23,"cxy",10000);
    Employee test2("li",24,"jixie",5000);
    Employee test3("ll",22,"jixie",7000);

    test1.display();
    test2.display();
    test3.display();

    cout << "平均工资为：" << (test1.getSalary()+test2.getSalary()+test3.getSalary())/3 <<endl;

    return 0;
}

