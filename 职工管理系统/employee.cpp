#include <iostream>
#include "employee.h"

using namespace std;

Employee::Employee(int idIn, string nameIn, int depIdIn) {
	id = idIn;
	name = nameIn;
	depId = depIdIn;
};
void Employee::showInfo() {
	cout << "ְ�����Ϊ��" << id
		<< "\tְ������Ϊ��" << name 
		<< "\t��λΪ��" << getDep() 
		<< "\t��������Ϊ����ɾ��������������ڿҿ�996" << endl;
};
string Employee::getDep() {
	return "Ա��";
};