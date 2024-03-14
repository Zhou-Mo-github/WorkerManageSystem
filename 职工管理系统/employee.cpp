#include <iostream>
#include "employee.h"

using namespace std;

Employee::Employee(int idIn, string nameIn, int depIdIn) {
	id = idIn;
	name = nameIn;
	depId = depIdIn;
};
void Employee::showInfo() {
	cout << "职工编号为：" << id
		<< "\t职工姓名为：" << name 
		<< "\t岗位为：" << getDep() 
		<< "\t工作内容为：完成经理分配的任务，勤勤恳恳996" << endl;
};
string Employee::getDep() {
	return "员工";
};