#include <iostream>
#include "manager.h"

using namespace std;

Manager::Manager(int idIn, string nameIn, int depIdIn) {
	id = idIn;
	name = nameIn;
	depId = depIdIn;
};
void Manager::showInfo() {
	cout << "职工编号为：" << id
		<< "\t职工姓名为：" << name 
		<< "\t岗位为：" << getDep() 
		<< "\t工作内容为：接受总裁指派的任务，分配给员工" << endl;
};
string Manager::getDep() {
	return "经理";
};