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
	// ��ʤ��
	// �����
	// �ܻ�ܰ
	// ��ɺ��
	// �ڷ�
	//
	int  choice = 0;

	while (true) {
	wm.showMenu();
	cin >> choice;

		switch (choice)
		{
		case 0://�˳�ϵͳ
			wm.exist();
			break;
		case 1://���ְ��
			wm.addWorker();
			break;
		case 2://��ʾְ��
			wm.showWorker();
			break;
		case 3://ɾ��ְ��
			wm.deleteWorker();
			break;
		case 4://�޸�ְ��
			wm.modifyWorker();
			break;
		case 5://����ְ��
			wm.findWorker();
			break;
		case 6://����
			wm.sort();
			break;
		case 7://����ļ�
			wm.deleteAll();
			break;
		default:
			system("cls");//�����Ļ
			break;
		}
	}

	
	return 0;
}
