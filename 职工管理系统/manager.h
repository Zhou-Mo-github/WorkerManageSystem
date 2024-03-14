#pragma once
#include <iostream>
#include"worker.h"

using namespace std;

class Manager :public Worker {
public:
	Manager(int idIn, string nameIn, int depIdIn);
	void showInfo();
	string getDep();
};
