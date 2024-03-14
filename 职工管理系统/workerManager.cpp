#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>

#include "workerManager.h"
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"

#define FILENAME "empInfo.txt"

using namespace std;

WorkerManager::WorkerManager() {
	//构造函数初始化有三种情况：
	//1.文件未创建
	//2.文件存在，但内容被清空
	//3.文件存在，且保存了数据

	ifstream ifs;//读取文件
	ifs.open(FILENAME, ios::in);

	//1.文件未创建
	if (!ifs.is_open()) {
		//ifs.is_open函数用于判断文件打开是否成功
		//若打开失败说明不存在这个文件，需要初始化
		//cout << "文件不存在" << endl;
		//设置文件为空标志
		fileIsEmpty = true;
		//初始化人数和数组指针
		workerNum = 0;
		workerArr = nullptr;
		ifs.close();
		return;
	}

	//2.文件存在，但内容被清空
	char ch;
	ifs >> ch;//读取一个字符
	if (ifs.eof()) {
		//ifs.eof()函数用于测试文件是否为空
		//若文件为空则需要初始化
		//cout << "文件为空" << endl;
		//设置文件为空标志
		fileIsEmpty = true;
		//初始化人数和数组指针
		workerNum = 0;
		workerArr = nullptr;
		ifs.close();
		return;
	}

	//3.文件存在，且保存了数据
	//函数getNum()统计文件中的人数
	//函数initialize()从文件中读取数据并初始化员工数组
	int num = getNum();
	//cout << "职工人数为：" << num << endl;
	workerNum = num;

	//开辟空间
	workerArr = new Worker * [num];
	//将文件中数据存到数组中
	initialize();
	fileIsEmpty = false;

	//int id;
	//string name;
	//int depId;

	//int num = 0;
	//while (ifs >> id && ifs >> name && ifs >> depId) {
	//	num++;//每读取一行，数量+1
	//}

	//workerNum = num;
	////开辟空间
	//workerArr = new Worker * [num];

	//int i = 0;
	//while (ifs >> id && ifs >> name && ifs >> depId) {
	//	//每读取文件中的一行数据就创建一个新的Worker对象
	//	Worker* worker = nullptr;
	//	switch (depId) {
	//	case 1:
	//		worker = new Employee(id, name, depId);
	//		break;
	//	case 2:
	//		worker = new Manager(id, name, depId);
	//		break;
	//	case 3:
	//		worker = new Boss(id, name, depId);
	//		break;
	//	}
	//	workerArr[i] = worker;
	//	i++;
	//}

	//ifs.close();

	//fileIsEmpty = false;

}

WorkerManager::~WorkerManager() {
	//手动释放堆区数据
	//删除数组中的指针以及指向该数组的指针
	if (workerArr != nullptr) {//判断指向数组的指针是否为空
		for (int i = 0; i < workerNum; i++) {
			if (workerArr[i] != nullptr) {//判断数组内存放的指针是否为空
				delete workerArr[i];//释放每一个对象
			}
		}

		workerNum = 0;
		delete[]workerArr;//释放堆区的数组
		workerArr = nullptr;
		fileIsEmpty = true;
	}
}

void WorkerManager::save() {//保存文件
	ofstream ofs;
	ofs.open(FILENAME,ios::out);

	for (int i = 0; i < workerNum; i++) {
		ofs << workerArr[i]->id
			<< " " << workerArr[i]->name
			<< " " << workerArr[i]->depId << endl;
	}

	ofs.close();
}

int WorkerManager::getNum() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int depid;

	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> depid) {
		//读取文件中的数据
		num++;
		//每读取一行，数量+1
	}

	return num;
}

void WorkerManager::initialize() {

	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int depId;

	int i = 0;
	while (ifs >> id && ifs >> name && ifs >> depId) {
		//每读取文件中的一行数据就创建一个新的Worker对象
		Worker* worker = nullptr;
		switch (depId) {
		case 1:
			worker = new Employee(id, name, depId);
			break;
		case 2:
			worker = new Manager(id, name, depId);
			break;
		case 3:
			worker = new Boss(id, name, depId);
			break;
		}
		workerArr[i] = worker;
		i++;
	}

	//功能测试
	/*for (int i = 0; i < workerNum; i++) {
		workerArr[i]->showInfo();
	}*/

	ifs.close();
	
}


void WorkerManager::showMenu() {
	cout << "欢迎使用职工管理系统" << endl;
	cout << "0.退出" << endl;
	cout << "1.增加职工信息" << endl;
	cout << "2.显示职工信息" << endl;
	cout << "3.删除离职职工" << endl;
	cout << "4.修改职工信息" << endl;
	cout << "5.查找职工信息" << endl;
	cout << "6.按照编号排序" << endl;
	cout << "7.清空所有文档" << endl;
	cout << endl;
	cout << "请输入您的选择" << endl;
}

void WorkerManager::exist() {
	cout << "感谢使用！" << endl;
	system("pause");//暂停一下，展示输出
	exit(0);//退出程序
}

//添加职工
void WorkerManager::addWorker() {
	int addNum = 0;
	cout << "请输入需要添加的人数：";
	
	while (true) {
		cin >> addNum;
		if (addNum > 0) {
			int newSize = workerNum + addNum;
			//创建扩容后的新数组
			Worker** newArr = new Worker * [newSize];
			//复制原来数组中的元素
			for (int i = 0; i < workerNum; i++) {
				newArr[i] = workerArr[i];
			}
			//添加新的数组元素
			for (int i = 0; i < addNum; i++) {
				Worker* worker = nullptr;
				int idIn;
				cout << "请输入第" << i + 1 << "个新职工编号：";

				while (true) {
					cin >> idIn;

					//判断该编号是否已经存在
					int i = 0;
					for (i = 0; i < workerNum; i++) {
						if (workerArr[i]->id == idIn) {
							cout << "该编号已存在！请重新输入编号：";
							break;//跳出for循环
						}
					}
					if (i == workerNum) {
						break;//跳出while循环
					}
				}
				

				string nameIn;
				cout << "请输入第" << i + 1 << "个新职工姓名：";
				cin >> nameIn;

				int depIdIn;
				cout << "请选择第" << i + 1 << "个新职工的职位：" << endl
					<< "1.普通员工" << endl
					<< "2.经理" << endl
					<< "3.总裁" << endl;
				cin >> depIdIn;
				cout << endl;
				switch (depIdIn)
				{
				case 1:
					worker = new Employee(idIn, nameIn, depIdIn);
					newArr[workerNum + i] = worker;
					break;
				case 2:
					worker = new Manager(idIn, nameIn, depIdIn);
					newArr[workerNum + i] = worker;
					break;
				case 3:
					worker = new Boss(idIn, nameIn, depIdIn);
					newArr[workerNum + i] = worker;
				default:
					break;
				}
			}
			//释放原有空间
			delete[] workerArr;

			//更改新空间指向
			workerArr = newArr;

			//更新员工个数
			workerNum = newSize;

			cout << "新职工信息已成功写入！"<<endl<<endl;
			
			//将信息保存到文件中
			save();

			fileIsEmpty = false;
			break;
		}
		else {
			cout << "输入的数字有误！请重新输入：";
		}
	}
	//按任意键后清屏
		system("pause");
		system("cls");
}

//显示职工信息
void WorkerManager::showWorker() {
	if (fileIsEmpty) {
		cout << "文件不存在或内容为空！" << endl;
	}
	else {
		for (int i = 0; i < workerNum; i++) {
			workerArr[i]->showInfo();
		}
		cout << endl;
	}
	
	//按任意键后清屏
	system("pause");
	system("cls");
}

//删除职工信息
void WorkerManager::deleteWorker() {
	if (fileIsEmpty) {
		cout << "文件不存在或内容为空！" << endl;
	}
	else {
		cout << "请输入需要删除的职工编号：";

		while(true){
			int idIn;
			cin >> idIn;

			//遍历数组，寻找待删除的职工编号
			//由于删除、修改、查找中都需要根据编号寻找职工，可以把这个操作封装成一个函数
			int count = 0;
			for (int i = 0; i < workerNum; i++, count++) {
				if (workerArr[i]->id == idIn) {
					cout << "确定删除下列职工？y/n" << endl;
					workerArr[i]->showInfo();
					char choice;
					cin >> choice;

					switch (choice)
					{
					case 'y':
						//delete workerArr[i];
						//为什么一旦有了上面这条语句编译就不通过？
						// 
						//数组中删除元素的做法
						//把后面的数据依次向前移，覆盖掉下标为i的元素
						//别忘了把数组中最后一个元素删除！
						for (int j = i+1; j < workerNum; j++,i++) {
							workerArr[i] = workerArr[j];
						}
						workerArr[workerNum - 1] = 0;
						workerNum--;
						cout << "该职工信息已成功删除"<<endl<<endl;

						//把数据保存到文件中
						save();

						break;
					case 'n':
						break;
					default:
						break;
					}
				goto label;//跳出整个while循环
				//不用break，因为无法做到连续跳出两个循环（？）
				}
			}
			if (count == workerNum) {
				cout << "查无此人！请重新输入需要删除的职工编号：";
			}
		}label:;

		//按任意键清屏
		system("pause");
		system("cls");
	}
	
}

//修改职工信息
void WorkerManager::modifyWorker() {
	if (fileIsEmpty) {
		cout << "文件不存在或内容为空！" << endl;
	}
	else{
		cout << "请输入需要修改的职工编号：";

		while (true) {
			int idIn;
			cin >> idIn;

			//遍历数组，寻找待修改的职工编号
			int count = 0;
			for (int i = 0; i < workerNum; i++, count++) {
				if (workerArr[i]->id == idIn) {
					cout << "确定修改下列职工？y/n" << endl;
					workerArr[i]->showInfo();
					char choice;
					cin >> choice;

					switch (choice)
						//switch语句报错：控制传输跳过的实例化nameIn
						//解决：在nameIn所定义的case加上{}限定变量作用域
					{
					case 'y': {
						//先删除原先的职工信息
						delete workerArr[i];
						Worker* worker;
						string nameIn;
						cout << "请输入职工姓名：";
						cin >> nameIn;

						int depIdIn;
						cout << "请选择职工职位：" << endl
							<< "1.普通员工" << endl
							<< "2.经理" << endl
							<< "3.总裁" << endl;
						cin >> depIdIn;
						cout << endl;
						switch (depIdIn)
						{
						case 1:
							worker = new Employee(idIn, nameIn, depIdIn);
							workerArr[i] = worker;
							break;
						case 2:
							worker = new Manager(idIn, nameIn, depIdIn);
							workerArr[i] = worker;
							break;
						case 3:
							worker = new Boss(idIn, nameIn, depIdIn);
							workerArr[i] = worker;
						default:
							break;
						}
						cout << "该职工信息已成功修改" << endl << endl;

						//把数据保存到文件中
						save();

						break;
					}
					case 'n':
						break;
					default:
						break;
					}
					goto label;//跳出整个while循环
					//不用break，因为无法做到连续跳出两个循环（？）
				}
			}
			if (count == workerNum) {
				cout << "查无此人！请重新输入需要删除的职工编号：";
			}
		}label:;

		//按任意键清屏
		system("pause");
		system("cls");
	}
}

//查找员工
void WorkerManager::findWorker() {
	if (fileIsEmpty) {
		cout << "文件不存在或内容为空！" << endl;
	}
	else {
		while(true){
		cout << "请选择查找方式：" << endl
			<< "1.按照编号查找" << endl
			<< "2.按照姓名查找" << endl;
		int choice;
		cin >> choice;

		switch (choice) {
		case 1: {
			cout << "请输入待查找编号：";
			int idIn;
			cin >> idIn;

			int count = 0;
			for (int i = 0; i < workerNum; i++,count++) {
				if (workerArr[i]->id == idIn) {
					workerArr[i]->showInfo();
					cout << endl;
					goto label;//跳出while循环
				}
			}
			
			if (count == workerNum) {
				cout << "查无此人！请重新查找"<<endl;
				break;//跳出switch，进入下一轮while循环
			}
		}
		case 2:{
			cout << "请输入待查找姓名：";
			string nameIn;
			cin >> nameIn;

			bool have_found = false;
			for (int i = 0; i < workerNum; i++) {
				if (workerArr[i]->name == nameIn) {
					workerArr[i]->showInfo();
					//cout << endl;
					have_found = true;
					//goto label;//跳出while循环
					//这里查找到后不要立即退出，因为有可能存在同名情况
					//要继续for循环遍历，直到把所有姓名相同的员工找出再退出
					//
					//如何区分“没找到”和“找到并已经输出”？
					//可以设置一个bool have_found标志
					//
					//判断是否查找到的方法：
					//1.用查找次数count和数组长度做比较
					//2.用have_found标签

				}
			}
			if (!have_found) {
				cout << "查无此人！请重新查找"<<endl;
				break;//跳出switch，进入下一轮while循环
			}
			goto label;//跳出while循环
		}
		default:
			cout << "请重新选择！";
			break;//跳出switch，进入下一轮while循环
		}
		}label:;
	}
	
	//按任意键清屏
	system("pause");
	system("cls");
}

//按照编号排序
bool smaller(Worker* w1, Worker* w2) {
	return w1->id < w2->id;
}

bool larger(Worker* w1, Worker* w2) {
	return w1->id > w2->id;
}

void WorkerManager::sort() {
	if (fileIsEmpty) {
		cout << "文件不存在或内容为空！" << endl;
	}
	else {
		while(true){
			cout << "请选择排序方式：" << endl
			<< "1.升序排列" << endl
			<< "2.降序排列" << endl;
		int choice = 0;
		cin >> choice;
	
		if (choice != 1 && choice != 2) {
			cout << "请重新选择！";
			continue;//进入下一轮while循环
		}
		
		//分清冒泡排序和选择排序
		//冒泡排序的i是轮数，代表已经排完序的个数；j与j+1或j-1比大小，每次交换数据
		//选择排序的i是假定最大或最小的下标；j与max或min比大小，找出每轮中最大或最小的下标，与i交换数据
		
		//冒泡排序
		//if (workerArr) {
		//	if (choice == 1) {
		//		for (int i = 0; i < workerNum - 1; i++) {
		//			for (int j = 0; j < workerNum - 1 - i; j++) {
		//				Worker* temp = nullptr;
		//				if (workerArr[j]->id > workerArr[j+1]->id) {
		//					temp = workerArr[j];
		//					//C6011:取消对NULL指针"__"的引用
		//					workerArr[j] = workerArr[j + 1];
		//					workerArr[j + 1] = temp;
		//				}
		//			}
		//		}
		//	}
		//	if (choice == 2) {
		//		for (int i = 0; i < workerNum - 1; i++) {
		//			for (int j = workerNum - 1 ; j > i; j--) {
		//				Worker* temp = nullptr;
		//				if (workerArr[j - 1]->id < workerArr[j]->id) {
		//						temp = workerArr[j];
		//						//C6011:取消对NULL指针"__"的引用
		//						workerArr[j] = workerArr[j - 1];
		//						workerArr[j - 1] = temp;
		//				}
		//			}
		//		}
		//	}
		//}

		//选择排序
		/*if (workerArr) {
			if (choice == 1) {
				for (int i = 0; i < workerNum; i++) {
					int min = i;
					for (int j = i + 1; j < workerNum; j++) {
						if (workerArr[j]->id < workerArr[min]->id) {
							min = j;
						}
					}
					if (min != i) {
						Worker* temp = nullptr;
						temp = workerArr[i];
						workerArr[i] = workerArr[min];
						workerArr[min] = temp;
					}
				}
			}
			if (choice == 2) {
				for (int i = 0; i < workerNum; i++) {
					int max = i;
					for (int j = i + 1; j < workerNum; j++) {
						if (workerArr[j]->id > workerArr[max]->id) {
							max = j;
						}
					}
					if (max != i) {
						Worker* temp = nullptr;
						temp = workerArr[i];
						workerArr[i] = workerArr[max];
						workerArr[max] = temp;
					}
				}
			}
		}*/

		//使用vector
		//将数组内容复制到vector中
		//方法一：vector构造函数
		vector<Worker*> tempArr(workerArr,workerArr+workerNum);

		//方法二：push_back函数
		/*vector<Worker*> tempArr;
		for (int i = 0; i < workerNum; i++) {
			tempArr.push_back(workerArr[i]);
		}*/

		//方法三：memcpy函数
		//这个方法报错:vector subscript out of range
		//原因是未对vector初始化
		//解决：先用workerNum对vector初始化
		//好像还是不行，原因未知
		/*vector<Worker*> tempArr(workerNum);
		memcpy(&tempArr[0], workerArr, workerNum);*/

		if (choice == 1)
			std::sort(tempArr.begin(), tempArr.end(), smaller);
		//vector中的sort函数与本类中定义的sort函数重名，需要用std限定
		if (choice == 2)
			std::sort(tempArr.begin(), tempArr.end(), larger);

		//将vector中排序好的内容复制到数组中
		memcpy(workerArr, &tempArr[0], tempArr.size() * sizeof(tempArr[0]));


		//#include <vector>
		//#include <algorithm>
		//#include <cstdlib>
		//#include <time.h>
		//#include <iostream>
		//using namespace std;
		//struct Student {
		//	int id;
		//	int age;
		//	bool sex;
		//	char name[64];
		//};
		/*bool comparestudent(student& s1, student& s2) {
			return s1.id < s2.id;
		}*/
		//Student arr[40000];
		//int main() {
		//	vector<Student> v;
		//	clock_t time0, time1, time2, time3;
		//	time0 = clock();
		//	for (int i = 0; i < 40000; i++) {
		//		arr[i].id = rand();
		//		arr[i].age = 20;
		//		arr[i].sex = (arr[i].id & 1) ? true : false;
		//		v.push_back(arr[i]);
		//	}
		//	time1 = clock();
		//	vector自带的排序
		//	sort(v.begin(), v.end(), compareStudent);
		//	time2 = clock();
		//	选择排序
		//	for (int i = 0; i < 39999; i++) {
		//		Student tmp;
		//		int max = 0;
		//		for (int j = 0; j < 39999 - i; j++) {
		//			if (!compareStudent(arr[j], arr[max]))
		//				max = j;
		//		}
		//		tmp = arr[39999 - i];
		//		arr[39999 - i] = arr[max];
		//		arr[max] = tmp;
		//	}
		//	time3 = clock();
		//	cout << "Create and insert: " << time1 - time0 << "ms" << endl;
		//	cout << "Sort by vector: " << time2 - time1 << "ms" << endl;
		//	cout << "Sort by selection: " << time3 - time2 << "ms" << endl;
		//	return 0;
		//}



			cout << "排序已完成，排序后的员工信息如下" << endl;

			for (int i = 0; i < workerNum; i++) {
				workerArr[i]->showInfo();
			}
			cout << endl;

			//把数据保存到文件中
			save();

			break;//跳出while循环
		}
	}

	//按任意键清屏
	system("pause");
	system("cls");
}

void WorkerManager::deleteAll() {
		cout << "确定删除所有员工信息？y/n"<<endl;
		char choice;
		cin >> choice;

		switch (choice) {
		case 'y': {
			//ios::trunc如果存在，则删除该文件并重新创建
			ofstream ofs;
			ofs.open(FILENAME, ios::trunc);
			ofs.close();

			//删除数组中的指针以及指向该数组的指针
			if (workerArr != nullptr) {//判断指向数组的指针是否为空
				for (int i = 0; i < workerNum; i++) {
					if (workerArr[i] != nullptr) {//判断数组内存放的指针是否为空
						delete workerArr[i];//释放每一个对象
					}
				}

				workerNum = 0;
				delete[]workerArr;//释放堆区的数组
				workerArr = nullptr;
				fileIsEmpty = true;
			}
			cout << "员工信息已全部清空！" << endl;
			break;
		}
			
		case 'n':
			break;
		}

		//按任意键清屏
		system("pause");
		system("cls");
}