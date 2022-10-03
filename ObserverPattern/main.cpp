#include <stdio.h>
#include <iostream>
#include <list>
using namespace std;

// 观察者模式: 定义了对象之间的一对多依赖，当一个对象改变状态时，它的所有依赖者都会收到通知并自动更新。
// 原则：
// 1. 为了交互对象之间的松耦合而努力；

class Observer {
public:
    virtual void update(float temp, float humidity, float pressure) = 0;
};

class Subject {
public:
    virtual void registerObserver(Observer*) = 0;
    virtual void removeObserver(Observer*) = 0;
    virtual void notifyObserver() = 0;
};

class DisplayElement {
    virtual void display() = 0;
};

class WeatherData : public Subject {
public:
    void registerObserver(Observer *o) override {
        observers.push_back(o);
    }
    void removeObserver(Observer *o) override {
        observers.remove(o);
    }
    void notifyObserver() override {
        for (auto o : observers) {
            o->update(temperature, humidity, pressure);
        }
    }
    void measurementsChanged() {
        notifyObserver();
    }
    void setMeasurements(float temp, float humidity, float pressure) {
        this->temperature = temp;
        this->humidity = humidity;
        this->pressure = pressure;
        measurementsChanged();
    }
private:
    list<Observer *> observers;
    float temperature;
    float humidity;
    float pressure;
};


class CurrentConditionsDisplay : public Observer, public DisplayElement {
public: 
    CurrentConditionsDisplay(Subject *weatherData) {
        this->weatherData = weatherData;
        this->weatherData->registerObserver(this);
    }
    void update(float temp, float humidity, float pressure) override {
        this->temperature = temp;
        this->humidity = humidity;
        display();
    }
    void display() override {
        cout << "temperature:" << temperature << " humidity:" << humidity << endl;
    }
private:
    float temperature;
    float humidity;
    Subject *weatherData;

};




int main(int argc, char ** argv)
{
    WeatherData *weatherData = new WeatherData;
    Observer *currentConditionsDisplay = new CurrentConditionsDisplay(weatherData);
    weatherData->setMeasurements(30, 34, 44);
    weatherData->setMeasurements(23, 33, 44);
    weatherData->setMeasurements(23, 22, 44);

    return 0;
}