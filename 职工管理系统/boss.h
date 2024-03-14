#pragma once
#include <iostream>
#include"worker.h"

using namespace std;

class Boss :public Worker {
public:
	Boss(int idIn, string nameIn, int depIdIn);
	void showInfo();
	string getDep();
};

