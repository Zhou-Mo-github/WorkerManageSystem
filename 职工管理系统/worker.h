#pragma once
#include <iostream>
#include <string>

using namespace std;

//�����࣬����Ҫ.cpp�ļ�����Ϊ����Ҫ���κ�ʵ��
class Worker {
public:
	virtual void showInfo() = 0;//���麯��
	virtual string getDep() = 0;

	int id;
	string name;
	int depId;
};
