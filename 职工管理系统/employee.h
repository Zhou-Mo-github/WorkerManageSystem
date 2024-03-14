#pragma once
#include <iostream>
#include"worker.h"

using namespace std;

class Employee :public Worker {
public:
	Employee(int idIn, string nameIn, int depIdIn);
	void showInfo();
	string getDep();
};
