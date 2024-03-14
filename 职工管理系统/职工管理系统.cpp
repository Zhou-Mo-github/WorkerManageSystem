#include <iostream>
#include "workerManager.h"
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"
using namespace std;

int main() {
	WorkerManager wm;
	//
	// 赵胜德
	// 张艺骞
	// 周卉馨
	// 王珊凌
	// 于峰
	//
	int  choice = 0;

	while (true) {
	wm.showMenu();
	cin >> choice;

		switch (choice)
		{
		case 0://退出系统
			wm.exist();
			break;
		case 1://添加职工
			wm.addWorker();
			break;
		case 2://显示职工
			wm.showWorker();
			break;
		case 3://删除职工
			wm.deleteWorker();
			break;
		case 4://修改职工
			wm.modifyWorker();
			break;
		case 5://查找职工
			wm.findWorker();
			break;
		case 6://排序
			wm.sort();
			break;
		case 7://清空文件
			wm.deleteAll();
			break;
		default:
			system("cls");//清空屏幕
			break;
		}
	}

	
	return 0;
}
