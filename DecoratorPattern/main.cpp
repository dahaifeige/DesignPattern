#include <stdio.h>
#include <iostream>
#include <string>
#include <list>


using namespace std;

 // 装饰者模式：动态地将责任附加到对象上。 若要扩展功能，装饰者提供了比继承更有弹性的替代方案。
 // 原则： 对扩展开放，对修改关闭（开放-关闭原则）
 // 内容： 1. 装饰者和被装饰者对象具有相同的类型；
 //        2. 可以用一个或多个装饰者包装一个对象；
 //        3. 既然装饰者和被装饰者对象具有相同的类型，所以在任何需要原始对象（被包装的）的场合，可以用装饰过的对象代替它；
 //        4. 对象可以在任何时候被装饰，所有可以在运行时动态地，不限量地用你喜欢的装饰者来装饰对象。
  
class Beverage {

public:ddd
    virtual string description() const
    {
        return _description;
    }

    virtual double cost() = 0;

protected:
    string _description = "";
};

class Espresso : public Beverage {

public:
    Espresso()
    {
        _description = "Espresso";
    }
    double cost() 
    {
        return 1.99;
    }
};

class HouseBlend : public Beverage {

public:
    HouseBlend() 
    {
        _description = "House Blend Coffee";
    }
    double cost()
    {
        return 0.99;
    }
};

class Decorator : public Beverage {

public:
    virtual string description() const = 0;
};

class Mocha : public Decorator {

public:
    Mocha(Beverage *beverage) {
        _beverage = beverage;
    }

    virtual string description() const 
    {
        return _beverage->description() + ", Mocha";
    }
    
    virtual double cost() 
    {
        return 0.20 + _beverage->cost();
    }
private:
    Beverage *_beverage;
};

class Soy : public Decorator {

public:
    Soy(Beverage *beverage) {
        _beverage = beverage;
    }

    virtual string description() const 
    {
        return _beverage->description() + ", Soy";
    }
    
    virtual double cost() 
    { 
        return 0.20 + _beverage->cost();
    }
private:
    Beverage *_beverage;
};

class Whip : public Decorator {

public:
    Whip(Beverage *beverage) {
        _beverage = beverage;
    }

    virtual string description() const 
    {
        return _beverage->description() + ", Whip";
    }
    
    virtual double cost() 
    {
        return 0.05 + _beverage->cost();
    }
private:
    Beverage *_beverage;
};

int main(int argc, char ** argv)
{
    Beverage *beverage = new Espresso;
    cout << beverage->description() << " $" << beverage->cost() << endl;

    Beverage *beverage1 = new HouseBlend;
    beverage1 = new Mocha(beverage1);
    beverage1 = new Mocha(beverage1);
    beverage1 = new Whip(beverage1);
    cout << beverage1->description() << " $" << beverage1->cost() << endl;

    return 0;
}