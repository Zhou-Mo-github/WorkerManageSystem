#pragma once //��ֹͷ�ļ��ظ�����
#include <iostream>
#include "worker.h"

using namespace std;

class WorkerManager {
public:
	WorkerManager();
	~WorkerManager();

	//�����ļ�
	void save();
	//ͳ���ļ��е�����
	int getNum();
	//���ļ��ж�ȡ���ݲ���ʼ��Ա������
	void initialize();

	//��ʾ�˵�
	void showMenu();
	//�˳�����0��
	void exist();
	//���ְ����Ϣ��1��
	void addWorker();
	//��ʾְ����Ϣ��2��
	void showWorker();
	//ɾ��ְ����Ϣ��3��
	void deleteWorker();
	//�޸�ְ����Ϣ��4��
	void modifyWorker();
	//����ְ����5��
	void findWorker();
	//����6��
	void sort();
	//����ļ���7��
	void deleteAll();

	//ְ������
	int workerNum = 0;
	
	//����ָ�����飬�����д�������ָ�룬����ͨ���������ָ�������ָ�룬ʵ��Ա����Ϣ�Ĵ��
	//int* a=new int(3);���Բο������﷨��ֻ�������������ŵ����ݱ����Worker*���������ָ��
	//��������ڶ��У����ڹ���ͱ���
	//Worker** workerArr = new Worker * [workerNum];
	Worker** workerArr = nullptr;

	//�ж��ļ��Ƿ�Ϊ��
	bool fileIsEmpty = true;


};