#include <iostream>
#include "manager.h"

using namespace std;

Manager::Manager(int idIn, string nameIn, int depIdIn) {
	id = idIn;
	name = nameIn;
	depId = depIdIn;
};
void Manager::showInfo() {
	cout << "ְ�����Ϊ��" << id
		<< "\tְ������Ϊ��" << name 
		<< "\t��λΪ��" << getDep() 
		<< "\t��������Ϊ�������ܲ�ָ�ɵ����񣬷����Ա��" << endl;
};
string Manager::getDep() {
	return "����";
};