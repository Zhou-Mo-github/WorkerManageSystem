#pragma once
#include <iostream>
#include <string>

using namespace std;

//抽象类，不需要.cpp文件，因为不需要做任何实现
class Worker {
public:
	virtual void showInfo() = 0;//纯虚函数
	virtual string getDep() = 0;

	int id;
	string name;
	int depId;
};
