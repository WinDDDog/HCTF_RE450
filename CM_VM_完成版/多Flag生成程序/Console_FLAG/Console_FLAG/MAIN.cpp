#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstring>
#include <cstdlib>
char stringIn[] = "HCTF{S1FALS1R1Fa9123489}";
int M_Rand(void);
int main()
{
	char xx1 = '6';//�޸ĵ��µ�Flag  6��
	char xx2 = '5';
	char xx3 = '4';
	char xx4 = '3';
	char xx5 = '2';
	char xx6 = '1';

	int AimportantNum = 0;

	const char* SourceFile = "C_easy_VMP.exe";	//�ļ�Դλ��
	const char* FlagList = "OUT//FlagList.txt";	//FlagList
	const int	Offset = 0x1A190;				//ƫ��
	const int	FileNum = 1000;					//�����ļ�����
	char NewFile[20] = "OUT//";				//���ļ�λ��

	std::ifstream in;
	std::ofstream out;
	std::ofstream FList;
	int num = 0;

	srand((int)time(NULL));

	FList.open(FlagList, std::ios::binary);//�����ƴ�FlagTable
	if (FList.fail())//��Դ�ļ�ʧ��
	{
		printf("��Flag��ʧ��");
		return 1;
	}
	in.open(SourceFile, std::ios::binary);//�����ƴ�Դ�ļ�

	if (in.fail())//��Դ�ļ�ʧ��
	{
		printf("���ļ�ʧ��");
		return 1;
	}
	for (; num < FileNum; num++)
	{
		char change1[20];
		char change2[20];
		_itoa(num, change1, 10);
		strcat(change1, ".exe");
		//ָ���ļ�
		strcpy(change2, NewFile);
		strcat(change2, change1);
		//
		out.open(change2, std::ios::binary);//����Ŀ���ļ� 
		if (out.fail())//�����ļ�ʧ��
		{
			printf("�����ļ�:%s	��������>Fail��\n", change2);
			out.close();
			in.close();
			return 1;
		}
		else				//�����ļ�
		{
			out << in.rdbuf();
			in.seekg(0, std::ios::beg);
			printf("�����ļ�:%s	��������>OK\n", change2);
		}

		out.seekp(Offset, std::ios::beg);//��ָ��λ��
		//flag�����
		xx6 = (AimportantNum % 10) + 'A';
		xx5 = ((AimportantNum / 10) % 10) + 'a';
		xx4 = ((AimportantNum / 100) % 10) + '0';
		xx3 = M_Rand();
		xx2 = M_Rand();
		xx1 = M_Rand();

		AimportantNum++;
		//���
		out << (char)(xx6 ^ 0x22);
		out << (char)(xx5 ^ 0x22);
		out << (char)(xx4 ^ 0x22);
		out << (char)(xx3 ^ 0x22);
		out << (char)(xx2 ^ 0x22);
		out << (char)(xx1 ^ 0x22);
		//�����flagList
		FList << change1 << ":" << "HCTF{S1FALS1R1Fa9" << xx1 << xx2 << xx3 << xx4 << xx5 << xx6 <<"}"<< "\r\n";

		out.close();
	}
	//release
	in.close();
	FList.close();
	/*
	for (int i = 0; i < 100;i++)
	printf("%x\n", M_Rand());
	*/
	return 0;
}
int M_Rand()
{
	const int RandMax = 0x39;
	const int RandMin = 0x30;
	int ret = 0;
	
	for (; ret < RandMin;)
		ret = (int)(rand() % (RandMax + 1));
	return ret;
}