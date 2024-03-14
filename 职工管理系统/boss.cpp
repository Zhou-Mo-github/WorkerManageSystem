#include <iostream>
#include "boss.h"

using namespace std;

Boss::Boss(int idIn, string nameIn, int depIdIn) {
	id = idIn;
	name = nameIn;
	depId = depIdIn;
};
void Boss::showInfo() {
	cout << "职工编号为：" << id \
		<< "\t职工姓名为：" << name
		<< "\t岗位为：" << getDep() 
		<< "\t工作内容为：统筹公司各项事务" << endl;
};
string Boss::getDep() {
	return "总裁";
};