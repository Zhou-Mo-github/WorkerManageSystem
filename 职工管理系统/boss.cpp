#include <iostream>
#include "boss.h"

using namespace std;

Boss::Boss(int idIn, string nameIn, int depIdIn) {
	id = idIn;
	name = nameIn;
	depId = depIdIn;
};
void Boss::showInfo() {
	cout << "ְ�����Ϊ��" << id \
		<< "\tְ������Ϊ��" << name
		<< "\t��λΪ��" << getDep() 
		<< "\t��������Ϊ��ͳ�﹫˾��������" << endl;
};
string Boss::getDep() {
	return "�ܲ�";
};