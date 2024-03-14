#pragma once //防止头文件重复包含
#include <iostream>
#include "worker.h"

using namespace std;

class WorkerManager {
public:
	WorkerManager();
	~WorkerManager();

	//保存文件
	void save();
	//统计文件中的人数
	int getNum();
	//从文件中读取数据并初始化员工数组
	void initialize();

	//显示菜单
	void showMenu();
	//退出程序（0）
	void exist();
	//添加职工信息（1）
	void addWorker();
	//显示职工信息（2）
	void showWorker();
	//删除职工信息（3）
	void deleteWorker();
	//修改职工信息（4）
	void modifyWorker();
	//查找职工（5）
	void findWorker();
	//排序（6）
	void sort();
	//清空文件（7）
	void deleteAll();

	//职工人数
	int workerNum = 0;
	
	//创建指针数组，数组中存放虚基类指针，可以通过子类对象指向虚基类指针，实现员工信息的存放
	//int* a=new int(3);可以参考这种语法，只不过把数组里存放的数据变成了Worker*，即虚基类指针
	//把数组放在堆中，便于管理和保存
	//Worker** workerArr = new Worker * [workerNum];
	Worker** workerArr = nullptr;

	//判断文件是否为空
	bool fileIsEmpty = true;


};