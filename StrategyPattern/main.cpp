#include <stdio.h>
#include <iostream>

// 策略模式: 定义了算法簇，分别封装起来，让它们之间可以相互替换，此模式让算法的变化独立于使用算法的客户。
// 原则：
// 1. 封装变化，找出变化，独立出来，不要和不需要变化的代码混在一起；
// 2. 针对接口编程，而不是针对实现变成；
// 3. 多用组合，少用继承；
 
using namespace std;

class FlyBehavior {
public:
    virtual void fly() = 0;
};

class FlyWithWings : public FlyBehavior {
public:
    virtual void fly() {
        cout << "i can fly" << endl;
    }
};

class FlyNoWay : public FlyBehavior {
public:
    virtual void fly() {
        cout << "i can't fly" << endl;
    }
};

class QuackBehavior {
public:
    virtual void quack() = 0;
};

class Quack : public QuackBehavior {
public:
    virtual void quack() {
        cout << "i quack" << endl;
    }
};

class MuteQuack : public QuackBehavior {
public:
    virtual void quack() {
        cout << "i silence" << endl;
    }
};

class Duck {
public:
    void setFlyBehavior(FlyBehavior *fb)
    {
        flyBehavior = fb;
    }
    void setQuackBevior(QuackBehavior *qb) 
    {
        quackBehavior = qb;
    }

    void performFly()
    {
        flyBehavior->fly();
    }
    void performQuack()
    {
        quackBehavior->quack();
    }
protected:
    FlyBehavior *flyBehavior;
    QuackBehavior *quackBehavior;
};

class MallardDuck : public Duck {
public:
  MallardDuck() {
    flyBehavior = new FlyWithWings;
    quackBehavior = new Quack;
  }
  
};


int main(int argc, char ** argv)
{
    Duck * duck = new MallardDuck;
    duck->performFly();
    duck->performQuack();
    duck->setFlyBehavior(new FlyNoWay);
    duck->performFly();
    return 0;
}