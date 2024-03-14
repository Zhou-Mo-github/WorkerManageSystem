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
	//���캯����ʼ�������������
	//1.�ļ�δ����
	//2.�ļ����ڣ������ݱ����
	//3.�ļ����ڣ��ұ���������

	ifstream ifs;//��ȡ�ļ�
	ifs.open(FILENAME, ios::in);

	//1.�ļ�δ����
	if (!ifs.is_open()) {
		//ifs.is_open���������ж��ļ����Ƿ�ɹ�
		//����ʧ��˵������������ļ�����Ҫ��ʼ��
		//cout << "�ļ�������" << endl;
		//�����ļ�Ϊ�ձ�־
		fileIsEmpty = true;
		//��ʼ������������ָ��
		workerNum = 0;
		workerArr = nullptr;
		ifs.close();
		return;
	}

	//2.�ļ����ڣ������ݱ����
	char ch;
	ifs >> ch;//��ȡһ���ַ�
	if (ifs.eof()) {
		//ifs.eof()�������ڲ����ļ��Ƿ�Ϊ��
		//���ļ�Ϊ������Ҫ��ʼ��
		//cout << "�ļ�Ϊ��" << endl;
		//�����ļ�Ϊ�ձ�־
		fileIsEmpty = true;
		//��ʼ������������ָ��
		workerNum = 0;
		workerArr = nullptr;
		ifs.close();
		return;
	}

	//3.�ļ����ڣ��ұ���������
	//����getNum()ͳ���ļ��е�����
	//����initialize()���ļ��ж�ȡ���ݲ���ʼ��Ա������
	int num = getNum();
	//cout << "ְ������Ϊ��" << num << endl;
	workerNum = num;

	//���ٿռ�
	workerArr = new Worker * [num];
	//���ļ������ݴ浽������
	initialize();
	fileIsEmpty = false;

	//int id;
	//string name;
	//int depId;

	//int num = 0;
	//while (ifs >> id && ifs >> name && ifs >> depId) {
	//	num++;//ÿ��ȡһ�У�����+1
	//}

	//workerNum = num;
	////���ٿռ�
	//workerArr = new Worker * [num];

	//int i = 0;
	//while (ifs >> id && ifs >> name && ifs >> depId) {
	//	//ÿ��ȡ�ļ��е�һ�����ݾʹ���һ���µ�Worker����
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
	//�ֶ��ͷŶ�������
	//ɾ�������е�ָ���Լ�ָ��������ָ��
	if (workerArr != nullptr) {//�ж�ָ�������ָ���Ƿ�Ϊ��
		for (int i = 0; i < workerNum; i++) {
			if (workerArr[i] != nullptr) {//�ж������ڴ�ŵ�ָ���Ƿ�Ϊ��
				delete workerArr[i];//�ͷ�ÿһ������
			}
		}

		workerNum = 0;
		delete[]workerArr;//�ͷŶ���������
		workerArr = nullptr;
		fileIsEmpty = true;
	}
}

void WorkerManager::save() {//�����ļ�
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
		//��ȡ�ļ��е�����
		num++;
		//ÿ��ȡһ�У�����+1
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
		//ÿ��ȡ�ļ��е�һ�����ݾʹ���һ���µ�Worker����
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

	//���ܲ���
	/*for (int i = 0; i < workerNum; i++) {
		workerArr[i]->showInfo();
	}*/

	ifs.close();
	
}


void WorkerManager::showMenu() {
	cout << "��ӭʹ��ְ������ϵͳ" << endl;
	cout << "0.�˳�" << endl;
	cout << "1.����ְ����Ϣ" << endl;
	cout << "2.��ʾְ����Ϣ" << endl;
	cout << "3.ɾ����ְְ��" << endl;
	cout << "4.�޸�ְ����Ϣ" << endl;
	cout << "5.����ְ����Ϣ" << endl;
	cout << "6.���ձ������" << endl;
	cout << "7.��������ĵ�" << endl;
	cout << endl;
	cout << "����������ѡ��" << endl;
}

void WorkerManager::exist() {
	cout << "��лʹ�ã�" << endl;
	system("pause");//��ͣһ�£�չʾ���
	exit(0);//�˳�����
}

//���ְ��
void WorkerManager::addWorker() {
	int addNum = 0;
	cout << "��������Ҫ��ӵ�������";
	
	while (true) {
		cin >> addNum;
		if (addNum > 0) {
			int newSize = workerNum + addNum;
			//�������ݺ��������
			Worker** newArr = new Worker * [newSize];
			//����ԭ�������е�Ԫ��
			for (int i = 0; i < workerNum; i++) {
				newArr[i] = workerArr[i];
			}
			//����µ�����Ԫ��
			for (int i = 0; i < addNum; i++) {
				Worker* worker = nullptr;
				int idIn;
				cout << "�������" << i + 1 << "����ְ����ţ�";

				while (true) {
					cin >> idIn;

					//�жϸñ���Ƿ��Ѿ�����
					int i = 0;
					for (i = 0; i < workerNum; i++) {
						if (workerArr[i]->id == idIn) {
							cout << "�ñ���Ѵ��ڣ������������ţ�";
							break;//����forѭ��
						}
					}
					if (i == workerNum) {
						break;//����whileѭ��
					}
				}
				

				string nameIn;
				cout << "�������" << i + 1 << "����ְ��������";
				cin >> nameIn;

				int depIdIn;
				cout << "��ѡ���" << i + 1 << "����ְ����ְλ��" << endl
					<< "1.��ͨԱ��" << endl
					<< "2.����" << endl
					<< "3.�ܲ�" << endl;
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
			//�ͷ�ԭ�пռ�
			delete[] workerArr;

			//�����¿ռ�ָ��
			workerArr = newArr;

			//����Ա������
			workerNum = newSize;

			cout << "��ְ����Ϣ�ѳɹ�д�룡"<<endl<<endl;
			
			//����Ϣ���浽�ļ���
			save();

			fileIsEmpty = false;
			break;
		}
		else {
			cout << "����������������������룺";
		}
	}
	//�������������
		system("pause");
		system("cls");
}

//��ʾְ����Ϣ
void WorkerManager::showWorker() {
	if (fileIsEmpty) {
		cout << "�ļ������ڻ�����Ϊ�գ�" << endl;
	}
	else {
		for (int i = 0; i < workerNum; i++) {
			workerArr[i]->showInfo();
		}
		cout << endl;
	}
	
	//�������������
	system("pause");
	system("cls");
}

//ɾ��ְ����Ϣ
void WorkerManager::deleteWorker() {
	if (fileIsEmpty) {
		cout << "�ļ������ڻ�����Ϊ�գ�" << endl;
	}
	else {
		cout << "��������Ҫɾ����ְ����ţ�";

		while(true){
			int idIn;
			cin >> idIn;

			//�������飬Ѱ�Ҵ�ɾ����ְ�����
			//����ɾ�����޸ġ������ж���Ҫ���ݱ��Ѱ��ְ�������԰����������װ��һ������
			int count = 0;
			for (int i = 0; i < workerNum; i++, count++) {
				if (workerArr[i]->id == idIn) {
					cout << "ȷ��ɾ������ְ����y/n" << endl;
					workerArr[i]->showInfo();
					char choice;
					cin >> choice;

					switch (choice)
					{
					case 'y':
						//delete workerArr[i];
						//Ϊʲôһ��������������������Ͳ�ͨ����
						// 
						//������ɾ��Ԫ�ص�����
						//�Ѻ��������������ǰ�ƣ����ǵ��±�Ϊi��Ԫ��
						//�����˰����������һ��Ԫ��ɾ����
						for (int j = i+1; j < workerNum; j++,i++) {
							workerArr[i] = workerArr[j];
						}
						workerArr[workerNum - 1] = 0;
						workerNum--;
						cout << "��ְ����Ϣ�ѳɹ�ɾ��"<<endl<<endl;

						//�����ݱ��浽�ļ���
						save();

						break;
					case 'n':
						break;
					default:
						break;
					}
				goto label;//��������whileѭ��
				//����break����Ϊ�޷�����������������ѭ��������
				}
			}
			if (count == workerNum) {
				cout << "���޴��ˣ�������������Ҫɾ����ְ����ţ�";
			}
		}label:;

		//�����������
		system("pause");
		system("cls");
	}
	
}

//�޸�ְ����Ϣ
void WorkerManager::modifyWorker() {
	if (fileIsEmpty) {
		cout << "�ļ������ڻ�����Ϊ�գ�" << endl;
	}
	else{
		cout << "��������Ҫ�޸ĵ�ְ����ţ�";

		while (true) {
			int idIn;
			cin >> idIn;

			//�������飬Ѱ�Ҵ��޸ĵ�ְ�����
			int count = 0;
			for (int i = 0; i < workerNum; i++, count++) {
				if (workerArr[i]->id == idIn) {
					cout << "ȷ���޸�����ְ����y/n" << endl;
					workerArr[i]->showInfo();
					char choice;
					cin >> choice;

					switch (choice)
						//switch��䱨�����ƴ���������ʵ����nameIn
						//�������nameIn�������case����{}�޶�����������
					{
					case 'y': {
						//��ɾ��ԭ�ȵ�ְ����Ϣ
						delete workerArr[i];
						Worker* worker;
						string nameIn;
						cout << "������ְ��������";
						cin >> nameIn;

						int depIdIn;
						cout << "��ѡ��ְ��ְλ��" << endl
							<< "1.��ͨԱ��" << endl
							<< "2.����" << endl
							<< "3.�ܲ�" << endl;
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
						cout << "��ְ����Ϣ�ѳɹ��޸�" << endl << endl;

						//�����ݱ��浽�ļ���
						save();

						break;
					}
					case 'n':
						break;
					default:
						break;
					}
					goto label;//��������whileѭ��
					//����break����Ϊ�޷�����������������ѭ��������
				}
			}
			if (count == workerNum) {
				cout << "���޴��ˣ�������������Ҫɾ����ְ����ţ�";
			}
		}label:;

		//�����������
		system("pause");
		system("cls");
	}
}

//����Ա��
void WorkerManager::findWorker() {
	if (fileIsEmpty) {
		cout << "�ļ������ڻ�����Ϊ�գ�" << endl;
	}
	else {
		while(true){
		cout << "��ѡ����ҷ�ʽ��" << endl
			<< "1.���ձ�Ų���" << endl
			<< "2.������������" << endl;
		int choice;
		cin >> choice;

		switch (choice) {
		case 1: {
			cout << "����������ұ�ţ�";
			int idIn;
			cin >> idIn;

			int count = 0;
			for (int i = 0; i < workerNum; i++,count++) {
				if (workerArr[i]->id == idIn) {
					workerArr[i]->showInfo();
					cout << endl;
					goto label;//����whileѭ��
				}
			}
			
			if (count == workerNum) {
				cout << "���޴��ˣ������²���"<<endl;
				break;//����switch��������һ��whileѭ��
			}
		}
		case 2:{
			cout << "�����������������";
			string nameIn;
			cin >> nameIn;

			bool have_found = false;
			for (int i = 0; i < workerNum; i++) {
				if (workerArr[i]->name == nameIn) {
					workerArr[i]->showInfo();
					//cout << endl;
					have_found = true;
					//goto label;//����whileѭ��
					//������ҵ���Ҫ�����˳�����Ϊ�п��ܴ���ͬ�����
					//Ҫ����forѭ��������ֱ��������������ͬ��Ա���ҳ����˳�
					//
					//������֡�û�ҵ����͡��ҵ����Ѿ��������
					//��������һ��bool have_found��־
					//
					//�ж��Ƿ���ҵ��ķ�����
					//1.�ò��Ҵ���count�����鳤�����Ƚ�
					//2.��have_found��ǩ

				}
			}
			if (!have_found) {
				cout << "���޴��ˣ������²���"<<endl;
				break;//����switch��������һ��whileѭ��
			}
			goto label;//����whileѭ��
		}
		default:
			cout << "������ѡ��";
			break;//����switch��������һ��whileѭ��
		}
		}label:;
	}
	
	//�����������
	system("pause");
	system("cls");
}

//���ձ������
bool smaller(Worker* w1, Worker* w2) {
	return w1->id < w2->id;
}

bool larger(Worker* w1, Worker* w2) {
	return w1->id > w2->id;
}

void WorkerManager::sort() {
	if (fileIsEmpty) {
		cout << "�ļ������ڻ�����Ϊ�գ�" << endl;
	}
	else {
		while(true){
			cout << "��ѡ������ʽ��" << endl
			<< "1.��������" << endl
			<< "2.��������" << endl;
		int choice = 0;
		cin >> choice;
	
		if (choice != 1 && choice != 2) {
			cout << "������ѡ��";
			continue;//������һ��whileѭ��
		}
		
		//����ð�������ѡ������
		//ð�������i�������������Ѿ�������ĸ�����j��j+1��j-1�ȴ�С��ÿ�ν�������
		//ѡ�������i�Ǽٶ�������С���±ꣻj��max��min�ȴ�С���ҳ�ÿ����������С���±꣬��i��������
		
		//ð������
		//if (workerArr) {
		//	if (choice == 1) {
		//		for (int i = 0; i < workerNum - 1; i++) {
		//			for (int j = 0; j < workerNum - 1 - i; j++) {
		//				Worker* temp = nullptr;
		//				if (workerArr[j]->id > workerArr[j+1]->id) {
		//					temp = workerArr[j];
		//					//C6011:ȡ����NULLָ��"__"������
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
		//						//C6011:ȡ����NULLָ��"__"������
		//						workerArr[j] = workerArr[j - 1];
		//						workerArr[j - 1] = temp;
		//				}
		//			}
		//		}
		//	}
		//}

		//ѡ������
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

		//ʹ��vector
		//���������ݸ��Ƶ�vector��
		//����һ��vector���캯��
		vector<Worker*> tempArr(workerArr,workerArr+workerNum);

		//��������push_back����
		/*vector<Worker*> tempArr;
		for (int i = 0; i < workerNum; i++) {
			tempArr.push_back(workerArr[i]);
		}*/

		//��������memcpy����
		//�����������:vector subscript out of range
		//ԭ����δ��vector��ʼ��
		//���������workerNum��vector��ʼ��
		//�����ǲ��У�ԭ��δ֪
		/*vector<Worker*> tempArr(workerNum);
		memcpy(&tempArr[0], workerArr, workerNum);*/

		if (choice == 1)
			std::sort(tempArr.begin(), tempArr.end(), smaller);
		//vector�е�sort�����뱾���ж����sort������������Ҫ��std�޶�
		if (choice == 2)
			std::sort(tempArr.begin(), tempArr.end(), larger);

		//��vector������õ����ݸ��Ƶ�������
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
		//	vector�Դ�������
		//	sort(v.begin(), v.end(), compareStudent);
		//	time2 = clock();
		//	ѡ������
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



			cout << "��������ɣ�������Ա����Ϣ����" << endl;

			for (int i = 0; i < workerNum; i++) {
				workerArr[i]->showInfo();
			}
			cout << endl;

			//�����ݱ��浽�ļ���
			save();

			break;//����whileѭ��
		}
	}

	//�����������
	system("pause");
	system("cls");
}

void WorkerManager::deleteAll() {
		cout << "ȷ��ɾ������Ա����Ϣ��y/n"<<endl;
		char choice;
		cin >> choice;

		switch (choice) {
		case 'y': {
			//ios::trunc������ڣ���ɾ�����ļ������´���
			ofstream ofs;
			ofs.open(FILENAME, ios::trunc);
			ofs.close();

			//ɾ�������е�ָ���Լ�ָ��������ָ��
			if (workerArr != nullptr) {//�ж�ָ�������ָ���Ƿ�Ϊ��
				for (int i = 0; i < workerNum; i++) {
					if (workerArr[i] != nullptr) {//�ж������ڴ�ŵ�ָ���Ƿ�Ϊ��
						delete workerArr[i];//�ͷ�ÿһ������
					}
				}

				workerNum = 0;
				delete[]workerArr;//�ͷŶ���������
				workerArr = nullptr;
				fileIsEmpty = true;
			}
			cout << "Ա����Ϣ��ȫ����գ�" << endl;
			break;
		}
			
		case 'n':
			break;
		}

		//�����������
		system("pause");
		system("cls");
}