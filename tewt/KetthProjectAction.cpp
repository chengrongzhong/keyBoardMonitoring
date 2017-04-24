#include "stdafx.h"
#include "KetthProjectAction.h"
#include <string>  
#include <stdlib.h> 
#include <stdio.h> 
#include <iostream>
#include <map>
#include <array>
#include <list>
#include <numeric>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include "Foshan.h"
#include "Guangxi.h"
#include "Huizhou.h"
#include "Backup.h"
#include "Backup2.h"
#include "Backup3.h"
#include "Yiciluru.h"
#include "Disanfang.h"
using namespace std;

KetthProjectAction::KetthProjectAction()
{
	/*
		int to string
		char *itoa( int value, char *string,int radix);
		ԭ��˵����
		value����ת�������ݡ�
		string��Ŀ���ַ����ĵ�ַ��
		radix��ת����Ľ�������������10���ơ�16���Ƶȡ�
		����ָ��string����ַ�����ָ��

		string to int
		atoi
	*/
	for (int n = 0; n < new_foshan.size(); n++) {
		string temp = new_foshan[n];
		string tempk = temp.substr(temp.length() - 4, temp.length());
		int key = atoi(tempk.c_str()) % 10000;
		KetthProjectAction::new_foshanSortCut.insert(pair<int, string>(key, temp));
	}

	for (int n = 0; n < new_guangxi.size(); n++) {
		string temp = new_guangxi[n];
		string tempk = temp.substr(temp.length() - 4, temp.length());
		int key = atoi(tempk.c_str()) % 10000;
		KetthProjectAction::new_guangxiSortCut.insert(pair<int, string>(key, temp));
	}

	for (int n = 0; n < HZ.size(); n++) {
		string temp = HZ[n];
		string tempk = temp.substr(temp.length() - 4, temp.length());
		int key = atoi(tempk.c_str()) % 10000;
		KetthProjectAction::HZSortCut.insert(pair<int, string>(key, temp));
	}

	for (int n = 0; n < Backup1.size(); n++) {
		string temp = Backup1[n];
		string tempk = temp.substr(temp.length() - 4, temp.length());
		int key = atoi(tempk.c_str()) % 10000;
		KetthProjectAction::BackupSortCut1.insert(pair<int, string>(key, temp));
	}

	for (int n = 0; n < Backup2.size(); n++) {
		string temp = Backup2[n];
		string tempk = temp.substr(temp.length() - 4, temp.length());
		int key = atoi(tempk.c_str()) % 10000;
		KetthProjectAction::BackupSortCut2.insert(pair<int, string>(key, temp));
	}

	for (int n = 0; n < Backup3.size(); n++) {
		string temp = Backup3[n];
		string tempk = temp.substr(temp.length() - 4, temp.length());
		int key = atoi(tempk.c_str()) % 10000;
		KetthProjectAction::BackupSortCut3.insert(pair<int, string>(key, temp));
	}

	// һ��¼�����ݳ�ʼ��
	std::map<string, std::list<string>>::iterator it;
	std::map<string, map<int, string>>::iterator temp;
	for (it = oneAndThree.begin(); it != oneAndThree.end(); ++it) {
		string str_key = it->first;
		std::list<string> value = it->second;
		list<string>::iterator itor = value.begin();
		//string * p = value.get_allocator().allocate(value.size());
		for (int n = 0; n < value.size(); n++, itor++) {
			string keke = *itor;
			string tempk = keke.substr(keke.length() - 4, keke.length());
			const char * c = tempk.c_str();
			int key = atoi(c) % 10000;
			temp = KetthProjectAction::oneAndThreeSortCut.find(str_key);
			if (temp != KetthProjectAction::oneAndThreeSortCut.end()) {
				map<int, string> mapping = KetthProjectAction::oneAndThreeSortCut.find(str_key)->second;
				if (mapping.find(key) != mapping.end())
				{
					string keyToValue = mapping.find(key)->second;
					keyToValue.append(",");
					keyToValue.append(keke);
					KetthProjectAction::oneAndThreeSortCut[str_key][key] = keyToValue;
				}
				else
				{
					KetthProjectAction::oneAndThreeSortCut.find(str_key)->second.insert(pair<int, string>(key, keke));
				}
				//mapping.insert(pair<int, string>(key, keke));
				//KetthProjectAction::oneAndThreeSortCut.insert(std::make_pair(str_key, mapping));
			}
			else {
				KetthProjectAction::oneAndThreeSortCut[str_key][key] = keke;
				//KetthProjectAction::oneAndThreeSortCut[str_key].insert(std::make_pair(key, p[n]));
			}
		}
	}

	// ������¼�����ݳ�ʼ��
	std::map<string, std::list<string>>::iterator dsf;
	std::map<int, map<string, string>>::iterator dsfTmp;
	for (dsf = Disanfang.begin(); dsf != Disanfang.end(); ++dsf) {
		string str_key = dsf->first;
		std::list<string> value = dsf->second;
		list<string>::iterator itor = value.begin();
		//string * p = value.get_allocator().allocate(value.size());
		for (int n = 0; n < value.size(); n++, itor++) {
			string keke = *itor;
			string tempk = keke.substr(keke.length() - 4, keke.length());
			const char * c = tempk.c_str();
			int key = atoi(c) % 10000;
			dsfTmp = KetthProjectAction::diSanFangSortCut.find(key);
			if (dsfTmp != KetthProjectAction::diSanFangSortCut.end()) {
				map<string, string> mapping = KetthProjectAction::diSanFangSortCut.find(key)->second;
				if (mapping.find(keke) == mapping.end())
				{
					//KetthProjectAction::diSanFangSortCut[key][str_key] = keke;
					KetthProjectAction::diSanFangSortCut.find(key)->second.insert(pair<string, string>(keke, str_key));
				}
				else
				{
					dsfnum++;
					dsfstr.append(keke);
					dsfstr.append(",");
				}
			}
			else {
				KetthProjectAction::diSanFangSortCut[key][keke] = str_key;
			}
		}
	}
}

KetthProjectAction::~KetthProjectAction()
{
}

bool mutiKey[20] = { 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0 };
void KetthProjectAction::resetMutikey() {
	for (int i = 0; i < 20; i++) {
		mutiKey[i] = 0;
	}
}	


void keyEvent(int keyValue, int time) {
	if (time <= 0) return;
	for (int i = 0;i < time;i++) {
		keybd_event(keyValue, 0, 0, 0);keybd_event(keyValue, 0, KEYEVENTF_KEYUP, 0);
	}
}

void textKeyEven(int keyValue, int up) {
	if (up > 0) {
		keybd_event(VK_LSHIFT, 0, 0, 0);
		keyEvent(keyValue, 1);
		keybd_event(VK_LSHIFT, 0, KEYEVENTF_KEYUP, 0);
	}
	else {
		keyEvent(keyValue, 1);
	}
}

void kkk(char k) {
	int keyValue;
	switch (k) {
	case '0':keyValue = 0x30;break;
	case '1':keyValue = 0x31;break;
	case '2':keyValue = 0x32;break;
	case '3':keyValue = 0x33;break;
	case '4':keyValue = 0x34;break;
	case '5':keyValue = 0x35;break;
	case '6':keyValue = 0x36;break;
	case '7':keyValue = 0x37;break;
	case '8':keyValue = 0x38;break;
	case '9':keyValue = 0x39;break;
	}
	keyEvent(keyValue, 1);
}

void switchKey(char k) {
	int keyValue;
	int up = 0;
	switch (k) {
	case '0':keyValue = 0x30;up = 0;break;
	case '1':keyValue = 0x31;up = 0;break;
	case '2':keyValue = 0x32;up = 0;break;
	case '3':keyValue = 0x33;up = 0;break;
	case '4':keyValue = 0x34;up = 0;break;
	case '5':keyValue = 0x35;up = 0;break;
	case '6':keyValue = 0x36;up = 0;break;
	case '7':keyValue = 0x37;up = 0;break;
	case '8':keyValue = 0x38;up = 0;break;
	case '9':keyValue = 0x39;up = 0;break;

	case 'a':keyValue = 0x41;up = 0;break;
	case 'A':keyValue = 0x41;up = 1;break;
	case 'b':keyValue = 0x42;up = 0;break;
	case 'B':keyValue = 0x42;up = 1;break;
	case 'c':keyValue = 0x43;up = 0;break;
	case 'C':keyValue = 0x43;up = 1;break;
	case 'd':keyValue = 0x44;up = 0;break;
	case 'D':keyValue = 0x44;up = 1;break;
	case 'e':keyValue = 0x45;up = 0;break;
	case 'E':keyValue = 0x45;up = 1;break;
	case 'f':keyValue = 0x46;up = 0;break;
	case 'F':keyValue = 0x46;up = 1;break;
	case 'g':keyValue = 0x47;up = 0;break;
	case 'G':keyValue = 0x47;up = 1;break;
	case 'h':keyValue = 0x48;up = 0;break;
	case 'H':keyValue = 0x48;up = 1;break;
	case 'i':keyValue = 0x49;up = 0;break;
	case 'I':keyValue = 0x49;up = 1;break;

	case 'j':keyValue = 0x4A;up = 0;break;
	case 'J':keyValue = 0x4A;up = 1;break;
	case 'k':keyValue = 0x4B;up = 0;break;
	case 'K':keyValue = 0x4B;up = 1;break;
	case 'l':keyValue = 0x4C;up = 0;break;
	case 'L':keyValue = 0x4C;up = 1;break;
	case 'm':keyValue = 0x4D;up = 0;break;
	case 'M':keyValue = 0x4D;up = 1;break;
	case 'n':keyValue = 0x4E;up = 0;break;
	case 'N':keyValue = 0x4E;up = 1;break;
	case 'o':keyValue = 0x4F;up = 0;break;
	case 'O':keyValue = 0x4F;up = 1;break;
	case 'p':keyValue = 0x50;up = 0;break;
	case 'P':keyValue = 0x50;up = 1;break;
	case 'q':keyValue = 0x51;up = 0;break;
	case 'Q':keyValue = 0x51;up = 1;break;
	case 'r':keyValue = 0x52;up = 0;break;
	case 'R':keyValue = 0x52;up = 1;break;

	case 's':keyValue = 0x53;up = 0;break;
	case 'S':keyValue = 0x53;up = 1;break;
	case 't':keyValue = 0x54;up = 0;break;
	case 'T':keyValue = 0x54;up = 1;break;
	case 'u':keyValue = 0x55;up = 0;break;
	case 'U':keyValue = 0x55;up = 1;break;
	case 'v':keyValue = 0x56;up = 0;break;
	case 'V':keyValue = 0x56;up = 1;break;
	case 'w':keyValue = 0x57;up = 0;break;
	case 'W':keyValue = 0x57;up = 1;break;
	case 'x':keyValue = 0x58;up = 0;break;
	case 'X':keyValue = 0x58;up = 1;break;
	case 'y':keyValue = 0x59;up = 0;break;
	case 'Y':keyValue = 0x59;up = 1;break;
	case 'z':keyValue = 0x5A;up = 0;break;
	case 'Z':keyValue = 0x5A;up = 1;break;
	}
	textKeyEven(keyValue, up);
}

void inputText(const char str[]) {
	int size = strlen(str);
	for (int i = 0;i < size;i++) {
		switchKey(str[i]);
	}
}

void inputTextKK(const char str[]) {
	int size = strlen(str);
	for (int i = 0;i < size;i++) {
		kkk(str[i]);
	}
}

// �������ģ�codeΪ�ú��ֵ�ASCII��
void testChinese(long code) {
	KEYBDINPUT kb = { 0 };
	INPUT Input = { 0 };

	// down
	kb.wScan = code;
	kb.dwFlags = KEYEVENTF_UNICODE;
	Input.type = INPUT_KEYBOARD;
	Input.ki = kb;
	::SendInput(1, &Input, sizeof(Input));

	// up
	kb.wScan = code;
	kb.dwFlags = KEYEVENTF_UNICODE | KEYEVENTF_KEYUP;
	Input.type = INPUT_KEYBOARD;
	Input.ki = kb;
	::SendInput(1, &Input, sizeof(Input));
}

void copyUpline() {
	keyEvent(VK_UP, 1);
	// ����
	keybd_event(VK_CONTROL, 0, 0, 0);
	keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);

	keyEvent(VK_DOWN, 1);
	// ճ��
	keybd_event(VK_CONTROL, 0, 0, 0);
	keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
}

void copyUpTwoline() {
	keyEvent(VK_UP, 1);
	keyEvent(VK_UP, 1);
	// ����
	keybd_event(VK_CONTROL, 0, 0, 0);
	keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);

	keyEvent(VK_DOWN, 1);
	keyEvent(VK_DOWN, 1);
	// ճ��
	keybd_event(VK_CONTROL, 0, 0, 0);
	keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
}

void copyUpThreeline() {
	keyEvent(VK_UP, 1);
	keyEvent(VK_UP, 1);
	keyEvent(VK_UP, 1);
	// ����
	keybd_event(VK_CONTROL, 0, 0, 0);
	keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);

	keyEvent(VK_DOWN, 1);
	keyEvent(VK_DOWN, 1);
	keyEvent(VK_DOWN, 1);
	// ճ��
	keybd_event(VK_CONTROL, 0, 0, 0);
	keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
}

static int sortCutStart = 11;
static string sortCutStr = "";
static bool switchSortCutStatus = false;

BOOL KetthProjectAction::sortCut(int sortCutType) {
	list<int>::iterator i;
	int xx = 1000;
	int key = 0;
	for (i = numlist.begin();i != numlist.end();i++) {
		key = key + *i * xx;
		xx = xx / 10;
	}
	map<int, string>::iterator iter;
	map<int, string> tampMap;
	switch (sortCutType)
	{
	case 1:tampMap = new_guangxiSortCut;
		break;
	case 2:tampMap = new_foshanSortCut;
		break;
	case 3:tampMap = HZSortCut;
		break;
	case 4:tampMap = BackupSortCut1;
		break;
	case 5:tampMap = BackupSortCut2;
		break;
	case 6:tampMap = BackupSortCut3;
		break;
	}
	iter = tampMap.find(key);
	if (iter != tampMap.end()) {
		string tvalue = iter->second;
		sortCutStr = tvalue;
		if (sortCutStr.length() == 10) {
			string tempv = tvalue.substr(0, 10);
			keyEvent(VK_BACK, 9);
			keyEvent(VK_ESCAPE, 1);
			inputTextKK(tempv.c_str());
			numlist.clear();
		}
		else {
			switchSortCutStatus = true;
			sortCutStart = 11;
			string tempv = tvalue.substr(0, 9);
			keyEvent(VK_BACK, 9);
			keyEvent(VK_ESCAPE, 1);
			inputTextKK(tempv.c_str());
		}
		return FALSE;

	}
	else {
		sortCutStr = "";
		return TRUE;
	}
}

BOOL KetthProjectAction::writeNumber() {
	ofstream inFile;
	/*
	ios::in ��
	ios::out д
	ios::app ���ļ�ĩβ��ʼд
	ios::binary ������ģʽ
	ios::nocreate ��һ���ļ�ʱ������ļ������ڣ��������ļ���
	ios::noreplace ��һ���ļ�ʱ������ļ������ڣ��������ļ�
	ios::trunc ��һ���ļ���Ȼ���������
	ios::ate ��һ���ļ�ʱ����λ���ƶ����ļ�β
	*/
	if (saveNum.size() == 10) {
		list<int>::iterator i;
		inFile.open("NewAddYueJie.ket", ios::app);
		for (i = saveNum.begin();i != saveNum.end();i++) {
			inFile << *i;
		}
		inFile << "\n";
		saveNum.clear();
		inFile.close();//�ر��ļ�  
	}
	return TRUE;
}

BOOL KetthProjectAction::writeYiciluru(int keyValue) {
	ofstream inFile;
	if (saveNum.size() == 10) {
		keyEvent(keyValue, 1);
		keyEvent(VK_LEFT, 1);
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0); keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_TAB, 1);


		//���ƶ����½�����λ��
		/*keyEvent(VK_DOWN, 1);
		keyEvent(VK_END, 1);*/
		::OpenClipboard(AfxGetMainWnd()->m_hWnd); //�򿪼��а� 
		if (IsClipboardFormatAvailable(CF_TEXT)) //������а������ı����͵����� 
		{
			HANDLE h = GetClipboardData(CF_TEXT); // ��ü��а����� ���ڵ��ڴ���� 
			char *p = (char*)GlobalLock(h); //ͨ�������ڴ���� ��ü��а建������ָ�� 

			GlobalUnlock(h); //�����ڴ���� ���� �ڴ�������������
			string str_key(p);
			inFile << str_key;
			inFile << ",";
		}
		::CloseClipboard();

		list<int>::iterator i;
		inFile.open("NewAddYueJie.ket", ios::app);
		for (i = saveNum.begin(); i != saveNum.end(); i++) {
			inFile << *i;
		}
		inFile << "\n";
		saveNum.clear();
		inFile.close();//�ر��ļ�  
	}
	return FALSE;
}

BOOL KetthProjectAction::fitToWrite() {
	if (saveNum.size() >= 3) {
		list<int>::iterator i;
		int xx = 100;
		int key = 0;
		int j = 0;
		for (i = saveNum.begin();i != saveNum.end() && j < 3;i++,j++) {
			key = key + *i * xx;
			xx = xx / 10;
		}
		for (int n = 0; n < writeHead.size(); n++) {
			int temp = writeHead[n];
			if (temp == key) {
				return TRUE;
			}
		}
		return FALSE;
	}
	else {
		return FALSE;
	}
}

BOOL KetthProjectAction::isMobilePhoneNum() {
	list<int>::iterator i;
	int key = 0;
	int j = 0;
	for (i = phoneNum.begin();i != phoneNum.end() && j < 1;i++, j++) {
		key = *i;
	}
	if (key == 1) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}

BOOL KetthProjectAction::is400PhoneNum() {
	list<int>::iterator i;
	int value = 0;
	int key = 100;
	int j = 0;
	for (i = phoneNum.begin(); i != phoneNum.end() && j < 3; i++, j++) {
		value += key * *i;
		key = key / 10;
	}
	if (value == 400) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}

void KetthProjectAction::inputShortPhoneNum() {
	list<int>::iterator i;
	int key = 0;
	int j = 0;
	for (i = phoneNum.begin();i != phoneNum.end() && j < 8;i++, j++) {
		key = key * 10 + *i;
	}
	/*
	int to string
	char *itoa( int value, char *string,int radix);
	ԭ��˵����
	value����ת�������ݡ�
	string��Ŀ���ַ����ĵ�ַ��
	radix��ת����Ľ�������������10���ơ�16���Ƶȡ�
	����ָ��string����ַ�����ָ��

	string to int
	atoi
	*/
	char str[25];
	_itoa_s(key, str, 10);
	inputTextKK(str);
}

BOOL KetthProjectAction::is7TelPhoneNum() {
	list<int>::iterator i;
	int key = 0;
	int j = 0;
	for (i = phoneNum.begin();i != phoneNum.end() && j < 1;i++, j++) {
		key = *i;
	}
	if (key == 0) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}

BOOL KetthProjectAction::yiciKeySortCut() {
	BOOL result = FALSE;
	//��ȥ���������������
	/*keyEvent(VK_UP, 1);
	keyEvent(VK_HOME, 1);
	keybd_event(VK_SHIFT, 0, 0, 0);
	keyEvent(VK_END, 1);
	keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);*/

	keyEvent(VK_ESCAPE, 1);
	keyEvent(VK_LEFT, 1);
	keybd_event(VK_CONTROL, 0, 0, 0);
	keybd_event(0x43, 0, 0, 0); keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
	keyEvent(VK_TAB, 1);

	
	//���ƶ����½�����λ��
	/*keyEvent(VK_DOWN, 1);
	keyEvent(VK_END, 1);*/
	::OpenClipboard(AfxGetMainWnd()->m_hWnd); //�򿪼��а� 
	if (IsClipboardFormatAvailable(CF_TEXT)) //������а������ı����͵����� 
	{
		HANDLE h = GetClipboardData(CF_TEXT); // ��ü��а����� ���ڵ��ڴ���� 
		char *p = (char*)GlobalLock(h); //ͨ�������ڴ���� ��ü��а建������ָ�� 

		GlobalUnlock(h); //�����ڴ���� ���� �ڴ�������������
		string str_key(p);
		std::map<string, map<int, string>>::iterator temp;
		temp = KetthProjectAction::oneAndThreeSortCut.find(str_key);
		if (temp != KetthProjectAction::oneAndThreeSortCut.end()) {
			list<int>::iterator i;
			int xx = 1000;
			int key = 0;
			for (i = yiciluru.begin(); i != yiciluru.end(); i++) {
				key = key + *i * xx;
				xx = xx / 10;
			}
			map<int, string>::iterator iter;
			map<int, string> tampMap = KetthProjectAction::oneAndThreeSortCut.find(str_key)->second;
			
			iter = tampMap.find(key);
			if (iter != tampMap.end()) {
				string tvalue = iter->second;
				sortCutStr = tvalue;
				if (sortCutStr.length() == 10) {
					string tempv = tvalue.substr(0, 10);
					keyEvent(VK_BACK, 3);
					keyEvent(VK_ESCAPE, 1);
					inputTextKK(tempv.c_str());
					yiciluru.clear();
				}
				else {
					KetthProjectAction::tempOneAndThree = tampMap;
					switchSortCutStatus = true;
					sortCutStart = 11;
					string tempv = tvalue.substr(0, 9);
					keyEvent(VK_BACK, 3);
					keyEvent(VK_ESCAPE, 1);
					inputTextKK(tempv.c_str());
				}
				result = FALSE;
			}
			else {
				sortCutStr = "";
				result = TRUE;
			}
		}
		else {
			sortCutStr = "";
			result = TRUE;
		}
	}
	CloseClipboard(); // �رռ��а�_ �ڵ���Open֮�� ������_
	return result;
}

BOOL KetthProjectAction::disanfangKeySortCut() {
	BOOL result = FALSE;
	list<int>::iterator i;
	int xx = 1000;
	int key = 0;
	for (i = disanfang.begin();i != disanfang.end();i++) {
		key = key + *i * xx;
		xx = xx / 10;
	}
	map<string, string>::iterator valueMap;
	std::map<int, map<string, string>>::iterator temp;
	temp = KetthProjectAction::diSanFangSortCut.find(key);
	if (temp != KetthProjectAction::diSanFangSortCut.end()) {
		map<string, string> valueMap = diSanFangSortCut.find(key)->second;

		string sortK = valueMap.begin()->first;
		string sortV = valueMap.begin()->second;
		
		if (valueMap.size() > 1) {
			tempDiSanFang = valueMap;
			sortCutStr = sortK;
			sortK = sortK.substr(0, 9);
			switchSortCutStatus = true;
		}

		keyEvent(VK_ESCAPE, 1);

		inputText(sortV.c_str());
		keyEvent(VK_RIGHT, 1);
		inputTextKK(sortK.c_str());
	}
	else {
		sortCutStr = "";
		result = TRUE;
	}
	return result;
}

BOOL KetthProjectAction::isSwitching(int sortCutType) {
	if (sortCutType == 9 && sortCutStr.length() == 10) {
		return TRUE;
	}
	if (sortCutStr.length() <= 10) {
		return FALSE;
	}
	list<int>::iterator i;
	int xx = 1000;
	map<int, string>::iterator iter;
	map<int, string> tampMap;
	string tvalue;
	switch (sortCutType)
	{
	case 1:tampMap = new_guangxiSortCut;
		break;
	case 2:tampMap = new_foshanSortCut;
		break;
	case 3:tampMap = HZSortCut;
		break;
	case 4:tampMap = BackupSortCut1;
		break;
	case 5:tampMap = BackupSortCut2;
		break;
	case 6:tampMap = BackupSortCut3;
		break;
	case 8:tampMap = tempOneAndThree;
		break;
	}
	int key = 0;
	for (i = switchList.begin(); i != switchList.end(); i++) {
		key = key + *i * xx;
		xx = xx / 10;
	}
	iter = tampMap.find(key);
	if (iter != tampMap.end()) {
		tvalue = iter->second;
		sortCutStr = tvalue.c_str();
		return TRUE;
	}
	else {
		return FALSE;
	}
}

int disanfangSwitchNum = 0;
void KetthProjectAction::switchSortCut(int sortCutType) {
	if (sortCutStr.length() == 0) {
		return;
	}
	list<int>::iterator i;
	int xx = 1000;
	
	map<int, string>::iterator iter;
	map<int, string> tampMap;
	string tvalue;
	switch (sortCutType)
	{
	case 1:tampMap = new_guangxiSortCut;
		break;
	case 2:tampMap = new_foshanSortCut;
		break;
	case 3:tampMap = HZSortCut;
		break;
	case 4:tampMap = BackupSortCut1;
		break;
	case 5:tampMap = BackupSortCut2;
		break;
	case 6:tampMap = BackupSortCut3;
		break;
	case 8:tampMap = tempOneAndThree;
		break;
	}
	if (sortCutType == 9) {
		map<string, string> valueMap = tempDiSanFang;
		std::map<string, string>::iterator nT;
		disanfangSwitchNum += 1;
		if (disanfangSwitchNum >= tempDiSanFang.size())
		{
			disanfangSwitchNum = disanfangSwitchNum % tempDiSanFang.size();
		}
		int tempWhile = disanfangSwitchNum;
		for (nT = tempDiSanFang.begin(); nT != tempDiSanFang.end() && disanfangSwitchNum > 0; --tempWhile, ++nT) {

		}
		string sortK = nT->first;
		string sortV = nT->second;

		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_LEFT, 1);

		inputTextKK(sortV.c_str());
		keyEvent(VK_RIGHT, 1);
		inputTextKK(sortK.substr(0, 9).c_str());

		sortCutStr = sortK.c_str();
		return;
	}
	int key = 0;
	for (i = switchList.begin(); i != switchList.end(); i++) {
		key = key + *i * xx;
		xx = xx / 10;
	}
	iter = tampMap.find(key);
	if (iter != tampMap.end()) {
		tvalue = iter->second;
		if (sortCutStart + 10 <= tvalue.length()) {
			keyEvent(VK_BACK, 9);
			keyEvent(VK_ESCAPE, 1);
			string temp = tvalue.c_str();
			string tempv = temp.substr(sortCutStart, 9);
			inputTextKK(tempv.c_str());
			sortCutStart = sortCutStart + 11;
		}
		else {
			keyEvent(VK_BACK, 9);
			keyEvent(VK_ESCAPE, 1);
			string temp = tvalue.c_str();
			string tempv = tvalue.substr(0, 9);
			inputTextKK(tempv.c_str());
			sortCutStart = 11;
		}
		sortCutStr = tvalue.c_str();
	}
}

BOOL KetthProjectAction::choiceSortCut(int sortCutType, int choice) {
	if (sortCutStr.length() == 0) {
		return FALSE;
	}
	list<int>::iterator i;
	int xx = 1000;
	
	map<int, string>::iterator iter;
	map<int, string> tampMap;
	string tvalue;
	switch (sortCutType)
	{
	case 1:tampMap = new_guangxiSortCut;
		break;
	case 2:tampMap = new_foshanSortCut;
		break;
	case 3:tampMap = HZSortCut;
		break;
	case 4:tampMap = BackupSortCut1;
		break;
	case 5:tampMap = BackupSortCut2;
		break;
	case 6:tampMap = BackupSortCut3;
		break;
	case 8:tampMap = tempOneAndThree;
		break;
	}
	if (sortCutType == 8) {
		::OpenClipboard(AfxGetMainWnd()->m_hWnd); //�򿪼��а� 
		if (IsClipboardFormatAvailable(CF_TEXT)) //������а������ı����͵����� 
		{
			HANDLE h = GetClipboardData(CF_TEXT); // ��ü��а����� ���ڵ��ڴ���� 
			char *p = (char*)GlobalLock(h); //ͨ�������ڴ���� ��ü��а建������ָ�� 

			GlobalUnlock(h); //�����ڴ���� ���� �ڴ�������������
			string str_key(p);
			std::map<string, map<int, string>>::iterator temp;
			temp = KetthProjectAction::oneAndThreeSortCut.find(str_key);
			if (temp != KetthProjectAction::oneAndThreeSortCut.end()) {
				list<int>::iterator i;
				int xx = 1000;
				int key = 0;
				for (i = switchList.begin(); i != switchList.end(); i++) {
					key = key + *i * xx;
					xx = xx / 10;
				}
				map<int, string>::iterator iter;
				map<int, string> tampMap = KetthProjectAction::oneAndThreeSortCut.find(str_key)->second;

				iter = tampMap.find(key);
				if (iter != tampMap.end()) {
					string tvalue = iter->second;
					sortCutStr = tvalue;
					int start = 11 * choice;
					while (start > tvalue.length() - 10) {
						start = start - 11;
					}
					keyEvent(VK_BACK, 9);
					keyEvent(VK_ESCAPE, 1);
					string temp = tvalue.c_str();
					string tempv = temp.substr(start, 10);
					inputTextKK(tempv.c_str());
					switchSortCutStatus = false;
					sortCutStr = "";
					return FALSE;
				}
			}
		}
		CloseClipboard(); // �رռ��а�_ �ڵ���Open֮�� ������_
		switchSortCutStatus = false;
		sortCutStr = "";
		return FALSE;
	}
	if (sortCutType == 9) {
		map<string, string> valueMap = tempDiSanFang;
		std::map<string, string>::iterator nT;
		disanfangSwitchNum += 1;
		if (disanfangSwitchNum >= tempDiSanFang.size())
		{
			disanfangSwitchNum = disanfangSwitchNum % tempDiSanFang.size();
		}
		int tempWhile = disanfangSwitchNum;
		for (nT = tempDiSanFang.begin(); nT != tempDiSanFang.end() && tempWhile > 0; --tempWhile, ++nT) {

		}
		string sortK = nT->first;
		string sortV = nT->second;

		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_LEFT, 1);

		inputText(sortV.c_str());
		keyEvent(VK_RIGHT, 1);
		inputTextKK(sortK.c_str());
		switchSortCutStatus = false;
		sortCutStr = "";
		return FALSE;
	}
	int key = 0;
	for (i = switchList.begin(); i != switchList.end(); i++) {
		key = key + *i * xx;
		xx = xx / 10;
	}
	iter = tampMap.find(key);
	if (iter != tampMap.end()) {
		tvalue = iter->second;
		int start = 11 * choice;
		while (start > tvalue.length() - 10) {
			start = start - 11;
		}
		
		keyEvent(VK_BACK, 9);
		keyEvent(VK_ESCAPE, 1);
		string temp = tvalue.c_str();
		string tempv = temp.substr(start, 10);
		inputTextKK(tempv.c_str());
		switchSortCutStatus = false;
		sortCutStr = "";
	}
	return FALSE;
}

void confirmSwitch() {
	keyEvent(VK_BACK, 9);
	keyEvent(VK_ESCAPE, 1);
	if (sortCutStr.length() == 10) {
		inputText(sortCutStr.c_str());
	}
	else {
		string tempv = sortCutStr.substr(sortCutStart - 11, 10);
		inputText(tempv.c_str());
	}
	switchSortCutStatus = false;
	sortCutStr = "";
}

void KetthProjectAction::mobilePhoneAction(int keyValue) {
	keyEvent(keyValue, 1);
	keyEvent(VK_RETURN, 1);
	keyEvent(VK_LEFT, 1);
	keybd_event(VK_CONTROL, 0, 0, 0);
	keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
	keyEvent(VK_RETURN, 1);
	keybd_event(VK_CONTROL, 0, 0, 0);
	keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
	keyEvent(VK_RETURN, 1);
	keyEvent(VK_RETURN, 1);
}

void KetthProjectAction::telPhoneAction(int keyValue) {
	keyEvent(keyValue, 1);
	keyEvent(VK_RETURN, 1);
	keyEvent(VK_LEFT, 1);
	keyEvent(VK_RETURN, 1);
	keyEvent(0x30, 1);
	keyEvent(VK_RETURN, 1);
	keyEvent(VK_RETURN, 1);
}
//�����ǹ̻���6���Ǵ�7λ����7���Ǵ�8λ���������������������������������������
void KetthProjectAction::shortTelPhoneAction(int keyValue) {
	keyEvent(VK_BACK, 7);
	inputShortPhoneNum();
	Sleep(99);
	keyEvent(VK_RETURN, 1);
	keyEvent(VK_LEFT, 1);
	keyEvent(VK_RETURN, 1);
	keyEvent(0x30, 1);
	keyEvent(VK_RETURN, 1);
	keyEvent(VK_RETURN, 1);
}

// �ص��ҵ�
BOOL KetthProjectAction::keyAction1(PKBDLLHOOKSTRUCT kbstruct, boolean lock) {
	HWND hWnd = GetFocus(); // �õ���ǰ���̹�����ڵĴ��� 
	LPRECT lParam = new RECT;
	int zuo = 0;
	int you = 0;
	int shang = 0;
	int xia = 0;
							// ���������鿴 https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx
	switch (kbstruct->vkCode) {
	case VK_SCROLL://�ر�ϵͳ
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			keyEvent(VK_RETURN, 1);
		}
		lock = false;
		break;
	case VK_F3:
		if (mutiKey[3] == 0) { //�����л�
			hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
			if (hWnd != NULL) {
				::GetWindowRect(hWnd, lParam);
				//int zuo = lParam->left;
				you = lParam->right;
				shang = lParam->top;
				//int xia = lParam->bottom;
				you = you - 20; //����������,��������
				shang = shang + 10;//��������,��������
				SetCursorPos(you, shang);
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			}
			hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
			if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
				::GetWindowRect(hWnd, lParam);
				//int zuo = lParam->left;
				you = lParam->right;
				shang = lParam->top;
				//int xia = lParam->bottom;
				you = you - 20; //����������,��������
				shang = shang + 10;//��������,��������
				SetCursorPos(you, shang);
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			}
			//*  �µ�
			//��ȡ����ڵ�����
			//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
			hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
			if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
				::GetWindowRect(hWnd, lParam);
				zuo = lParam->left;
				//int you = lParam->right;
				shang = lParam->top;
				//int xia = lParam->bottom;
				zuo = zuo + 20; //����������,��������
				shang = shang + 40;//��������,��������
				SetCursorPos(zuo, shang);
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
				shang = shang + 20;//��������,��������
				SetCursorPos(zuo, shang);
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			}
			Sleep(200);
			hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
			if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
				::GetWindowRect(hWnd, lParam);
				//int zuo = lParam->left;
				you = lParam->right;
				shang = lParam->top;
				//int xia = lParam->bottom;
				you = you - 300; //����������,��������
				shang = shang + 200;//��������,��������
				SetCursorPos(you, shang);
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			}
			mutiKey[3] = 1;  //�л����ڶ�������
		}
		else {
			hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
			if (hWnd != NULL) {
				::GetWindowRect(hWnd, lParam);
				//int zuo = lParam->left;
				you = lParam->right;
				shang = lParam->top;
				//int xia = lParam->bottom;
				you = you - 20; //����������,��������
				shang = shang + 10;//��������,��������
				SetCursorPos(you, shang);
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			}
			hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
			if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
				::GetWindowRect(hWnd, lParam);
				//int zuo = lParam->left;
				you = lParam->right;
				shang = lParam->top;
				//int xia = lParam->bottom;
				you = you - 20; //����������,��������
				shang = shang + 10;//��������,��������
				SetCursorPos(you, shang);
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			}
			//*  �µ�
			//��ȡ����ڵ�����
			//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
			hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
			if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
				::GetWindowRect(hWnd, lParam);
				zuo = lParam->left;
				//int you = lParam->right;
				shang = lParam->top;
				//int xia = lParam->bottom;
				zuo = zuo + 20; //����������,��������
				shang = shang + 40;//��������,��������
				SetCursorPos(zuo, shang);
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
				shang = shang + 20;//��������,��������
				SetCursorPos(zuo, shang);
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			}
			Sleep(200);
			hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
			if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
				::GetWindowRect(hWnd, lParam);
				//int zuo = lParam->left;
				you = lParam->right;
				shang = lParam->top;
				//int xia = lParam->bottom;
				you = you - 300; //����������,��������
				shang = shang + 200;//��������,��������
				SetCursorPos(you, shang);
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			}
			mutiKey[3] = 0;   //�л��ص�һ������
		}
		lock = false;
		break;
	case VK_F4:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 20;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 300; //����������,��������
			shang = shang + 200;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			Sleep(600);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_ESCAPE:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_ESCAPE, 1);
		SetCursorPos(198, 685);
		lock = false;
		break;
	case VK_PRIOR:// F8			'\|' key
		keyEvent(VK_F8, 1);
		lock = false;
		break;
	case VK_OEM_COMMA:// ����Ҫ�Ĵ򵥽�			For any country/region, the ',' key
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x49:// 	I key
		keyEvent(VK_UP, 1);
		lock = false;
		break;
	case 0x4A:// 	J key
		keyEvent(VK_LEFT, 1);
		lock = false;
		break;
	case 0x50://		P key
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case 0x48:// ��ȡ	0x48��H key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 8);
		keyEvent(0x31, 1);
		keyEvent(VK_LEFT, 1);
		lock = false;
		break;
	case 0x57:// ����	0x48��W key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(66);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 7);
		keyEvent(0x32, 1);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x55:// �ҵĽű�4	0x54��U key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(66);
		keyEvent(VK_F6, 2);
		lock = false;
		break;
	case 0x45:// ������			E key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(66);
		keyEvent(VK_HOME, 1);
		keyEvent(0x33, 1);
		keyEvent(VK_TAB, 1);
		lock = false;
		break;
	case 0x46:// 			F key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(66);
		keyEvent(VK_HOME, 1);
		keyEvent(0x32, 1);
		keyEvent(VK_TAB, 3);
		lock = false;
		break;
	case VK_MULTIPLY:// 			F key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(66);
		keyEvent(VK_HOME, 1);
		keyEvent(0x32, 1);
		keyEvent(VK_TAB, 2);
		lock = false;
		break;
	case VK_OEM_PERIOD:// �ҵĽű�1		VK_OEM_PERIOD ��'.' key	
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(66);
		keyEvent(VK_OEM_PERIOD, 1);
		keyEvent(0x35, 1);
		lock = false;
		break;
	case VK_OEM_5:// ɾ��			'\|' key
		keyEvent(VK_BACK, 1);
		lock = false;
		break;
	case VK_SPACE:// �ո�
		if (switchSortCutStatus) {
			confirmSwitch();
		}
		else {
			keyEvent(VK_RETURN, 1);
		}
		lock = false;
		break;
	case VK_RETURN:// �س�
		if (switchSortCutStatus) {
			confirmSwitch();
		}
		else {
			keyEvent(VK_RETURN, 1);
		}
		lock = false;
		break;
	case VK_F7:
		keyEvent(VK_ESCAPE, 1);
		copyUpline();
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x43:// ����			C key
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		lock = false;
		break;
	case 0x56:// ճ��			V key
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		lock = false;
		break;
	case 0x4F://O		ǩ�ص�5
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(66);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 8);
		Sleep(100);
		keyEvent(0x35, 1);
		Sleep(100);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_F8, 1);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_F1://O		ǩ�ص�5
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(66);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 8);
		Sleep(100);
		keyEvent(0x35, 1);
		Sleep(100);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_F8, 1);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_OEM_1:// ����		US standard keyboard, the ';:' key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(66);
		keyEvent(VK_HOME, 1);
		keyEvent(0x32, 1);
		keyEvent(0x31, 1);
		keyEvent(VK_TAB, 3);
		lock = false;
		break;
	case VK_ADD:// ����		С���̼Ӻ�
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(66);
		keyEvent(VK_HOME, 1);
		keyEvent(0x32, 1);
		keyEvent(0x31, 1);
		keyEvent(VK_TAB, 3);
		lock = false;
		break;
	case VK_OEM_3:// esc					For the US standard keyboard, the '`~' key
		keyEvent(VK_ESCAPE, 1);
		lock = false;
		break;
	case 0x53:// 			S KEY
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_HOME, 1);
		keyEvent(0x31, 1);
		keyEvent(VK_TAB, 4);
		lock = false;
		break;
	case VK_DIVIDE:// 			/ KEY
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 7);
		Sleep(100);
		keyEvent(0x35, 1);
		Sleep(100);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_F8, 1);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x47:// 			G KEY;
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(66);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keybd_event(0x32, 0, 0, 0);keybd_event(0x32, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RETURN, 2);
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x42:// 			B KEY ����
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(66);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 7);
		keyEvent(0x31, 1);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x4B:// 	K key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(66);
		keyEvent(VK_DOWN, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(0x32, 1);
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case 0x58:// 			X KEY 
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(66);
		keyEvent(VK_DOWN, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(0x32, 1);
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case 0x4C:// 			����L KEY ����
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(66);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 7);
		keyEvent(0x31, 1);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x59:// 			����Y KEY ����
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(66);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 7);
		inputText("AU");
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x54:// 			����T KEY ����
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(66);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 7);
		inputText("AU");
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x41:// 			A���Ի���װKEY ����
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(66);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 7);
		inputText("AY");
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x44:// 			D���շ�
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(66);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 7);
		inputText("X");
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x51:// 			��װQ
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(66);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 7);
		inputText("0");
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x52:// 			R KEY ȼ��
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(66);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 7);
		inputText("K");
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_TAB://TAB��
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_DOWN, 1);
		lock = false;
		break;
	case VK_F11://����̼Ӻ�+++++++++�ͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½�
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 200; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 120; //����������,��������
			shang = shang + 130;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(100);
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		Sleep(100);
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 260; //����������,��������
			shang = shang + 130;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_OEM_6://]]  }}}����̼�++�������  ���ǳ���
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 60;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 1220; //����������,��������
			shang = shang + 700;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	}
	return lock;
}

// ������Ϣ
BOOL KetthProjectAction::keyAction2(PKBDLLHOOKSTRUCT kbstruct, boolean lock) {
	HWND hWnd = GetFocus(); // �õ���ǰ���̹�����ڵĴ��� 
	LPRECT lParam = new RECT;
	int zuo = 0;
	int you = 0;
	int shang = 0;
	int xia = 0;
							// ���������鿴 https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx
	switch (kbstruct->vkCode) {
	case VK_SCROLL://�ر�ϵͳ
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			keyEvent(VK_RETURN, 1);
		}
		lock = false;
		break;
	case 0x4B:// ��			K key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		// ����
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		// ճ��
		keyEvent(VK_RETURN, 1);
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_ESCAPE, 1);
		Sleep(60);
		keyEvent(VK_DOWN, 2);
		keyEvent(VK_ESCAPE, 1);
		lock = false;
		break;
	case VK_F7:// ������1��O		F7
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_UP, 1);
		// ����
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);

		keyEvent(VK_DOWN, 1);
		// ճ��
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_OEM_3:// esc					For the US standard keyboard, the '`~' key
		keyEvent(VK_ESCAPE, 1);
		lock = false;
		break;
	case VK_ESCAPE:
		hWnd = ::FindWindow(NULL, _T("��ʾ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 130; //����������,��������
			shang = shang + 100;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_ESCAPE, 1);
		SetCursorPos(198, 685);
		lock = false;
		break;
	case VK_F3:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 20;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 300; //����������,��������
			shang = shang + 200;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_F5:// ���ڼӵ绰����ǰ��
		hWnd = ::FindWindow(NULL, _T("��ʾ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 50; //����������,��������
			shang = shang + 100;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_PRIOR:// F8			'\|' key
		keyEvent(VK_F8, 1);
		lock = false;
		break;
	case VK_SPACE:// �ո�
		hWnd = ::FindWindow(NULL, _T("��ʾ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 50;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_RETURN:// �س�
		if (switchSortCutStatus) {
			confirmSwitch();
		}
		else {
			keyEvent(VK_RETURN, 1);
		}
		lock = false;
		break;
	case 0x48:// H			H key
		keyEvent(VK_DOWN, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 2);
		keyEvent(0x30, 1);
		keyEvent(VK_LEFT, 1);
		// ����
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		// ճ��
		keyEvent(VK_RETURN, 1);
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_ESCAPE, 1);
		lock = false;
		break;
	case VK_MULTIPLY:// ������һ��
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_UP, 1);
		// ����
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);

		keyEvent(VK_DOWN, 1);
		// ճ��
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_ADD:// ��			С���̳˺� key
		keyEvent(VK_DOWN, 1);
		keyEvent(VK_ESCAPE, 1);
		Sleep(80);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		// ����
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		// ճ��
		keyEvent(VK_RETURN, 1);
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_ESCAPE, 1);
		Sleep(60);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_DOWN, 1);
		keyEvent(VK_ESCAPE, 1);
		lock = false;
		break;
	case 0x4C:// L		½�� KEY
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 3);
		keyEvent(0x32, 1);
		keyEvent(0x39, 1);
		keyEvent(VK_TAB, 1);
		keyEvent(0x32, 1);
		keyEvent(0x32, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case 0x4E:// L		½�� KEY
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 3);
		keyEvent(0x32, 1);
		keyEvent(0x39, 1);
		keyEvent(VK_TAB, 1);
		keyEvent(0x32, 1);
		keyEvent(0x32, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case 0x58:// X			С��KEY
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 3);
		keyEvent(0x31, 1);
		keyEvent(0x34, 1);
		keyEvent(0x30, 1);
		keyEvent(VK_TAB, 1);
		keyEvent(0x33, 1);
		keyEvent(0x33, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case 0x41://A����	A KEY
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 3);
		keyEvent(0x31, 1);
		keyEvent(VK_TAB, 1);
		keyEvent(0x32, 1);
		keyEvent(0x32, 1);
		keyEvent(VK_TAB, 1);
		keyEvent(0x31, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case 0x4F://Ч���� 	O KEY
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 6);
		keyEvent(0x33, 1);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x42://26	B  KEY����
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 3);
		keyEvent(0x32, 1);
		keyEvent(0x36, 1);
		keyEvent(VK_TAB, 1);
		keyEvent(0x32, 1);
		keyEvent(0x32, 1);
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case 0x53://S  ��������
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 3);
		keyEvent(0x31, 1);
		keyEvent(0x30, 1);
		keyEvent(0x32, 1);
		keyEvent(VK_TAB, 1);
		keyEvent(0x32, 1);
		keyEvent(0x32, 1);
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case 0x5A://Z	107 36	
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 3);
		keyEvent(0x31, 1);
		keyEvent(0x30, 1);
		keyEvent(0x37, 1);
		keyEvent(VK_TAB, 1);
		keyEvent(0x33, 1);
		keyEvent(0x36, 1);
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case 0x43://26	Y KEY�γ�
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 3);
		keyEvent(0x31, 1);
		keyEvent(VK_TAB, 1);
		keyEvent(0x32, 1);
		keyEvent(0x36, 1);
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case 0x57://26	E KEY�γ�
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 3);
		keyEvent(0x31, 1);
		keyEvent(VK_TAB, 1);
		keyEvent(0x32, 1);
		keyEvent(0x36, 1);
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case 0x56://V	�γ����
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 3);
		keyEvent(0x31, 1);
		keyEvent(VK_TAB, 1);
		keyEvent(0x32, 1);
		keyEvent(0x36, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_LEFT, 1);
		lock = false;
		break;
	case 0x50:// P�ջ�		P key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 5);
		keyEvent(0x32, 1);
		keyEvent(VK_LEFT, 1);
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	//case 0x55:// I11			U key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 3);
		keyEvent(0x31, 1);
		keyEvent(VK_TAB, 1);
		keyEvent(0x31, 1);
		keyEvent(0x31, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_LEFT, 1);
		keyEvent(VK_DOWN, 1);
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	//case 0x48:// H25			H key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 3);
		keyEvent(0x31, 1);
		keyEvent(VK_TAB, 1);
		keyEvent(0x32, 1);
		keyEvent(0x35, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_LEFT, 1);
		keyEvent(VK_DOWN, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 2);
		keyEvent(0x30, 1);
		keyEvent(VK_LEFT, 1);
		// ����
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		// ճ��
		keyEvent(VK_RETURN, 1);
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_ESCAPE, 1);
		lock = false;
		break;
	case 0x54:// T2824			T KEY
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 3);
		keyEvent(0x32, 1);
		keyEvent(0x38, 1);
		keyEvent(VK_TAB, 1);
		keyEvent(0x32, 1);
		keyEvent(0x34, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_LEFT, 1);
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case 0x45:// T2824	�ػ�		E KEY
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 3);
		keyEvent(0x32, 1);
		keyEvent(0x38, 1);
		keyEvent(VK_TAB, 1);
		keyEvent(0x32, 1);
		keyEvent(0x34, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_LEFT, 1);
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case 0x4A:// 2000			J KEY
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 3);
		keyEvent(0x31, 1);
		keyEvent(VK_TAB, 1);
		keyEvent(0x31, 1);
		keyEvent(0x31, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_LEFT, 1);
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case 0x51:// ����			Q KEY
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 3);
		keyEvent(0x31, 1);
		keyEvent(VK_TAB, 1);
		keyEvent(0x32, 1);
		keyEvent(0x32, 1);
		keyEvent(VK_TAB, 1);
		keyEvent(0x31, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case VK_OEM_1:// �ҵĽű�1			US standard keyboard, the ';:' key
		keyEvent(VK_LEFT, 1);
		lock = false;
		break;
	case 0x49:// ��			I key
		keyEvent(VK_UP, 1);
		lock = false;
		break;
	case VK_OEM_5:// ɾ��			'\|' key
		keyEvent(VK_BACK, 1);
		lock = false;
		break;
	case VK_OEM_4:// ����һ��		US standard keyboard, the '[{' key
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		// ����
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		// ճ��
		keyEvent(VK_RETURN, 1);
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_DIVIDE:// ����һ��		US standard keyboard, the '[{' key
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		// ����
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		// ճ��
		keyEvent(VK_RETURN, 1);
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;

	case VK_OEM_PERIOD:
		keyEvent(VK_DOWN, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(0x30, 1);
		keyEvent(VK_LEFT, 1);
		// ����
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		// ճ��
		keyEvent(VK_RETURN, 1);
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_OEM_COMMA:
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_OEM_2:
		keyEvent(VK_DOWN, 1);
		lock = false;
		break;	
	case VK_OEM_PLUS:// ���ڼӵ绰����ǰ��
		keyEvent(VK_SPACE, 1);
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		Sleep(300);
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case VK_INSERT:// ��0
		keyEvent(VK_END, 1);
		keyEvent(0x30, 1);
		lock = false;
		break;
	case VK_F4:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 20;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 300; //����������,��������
			shang = shang + 200;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			Sleep(600);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_F11://����̼Ӻ�+++++++++�ͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½�
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 200; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 120; //����������,��������
			shang = shang + 130;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(100);
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		Sleep(100);
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 260; //����������,��������
			shang = shang + 130;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_OEM_6://]]  }}}����̼�++�������  ���ǳ���
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 60;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 1220; //����������,��������
			shang = shang + 700;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	}
	return lock;
}

// ��������ͽ
BOOL KetthProjectAction::keyAction3(PKBDLLHOOKSTRUCT kbstruct, boolean lock) {
	HWND hWnd = GetFocus(); // �õ���ǰ���̹�����ڵĴ��� 
	LPRECT lParam = new RECT;
	int zuo = 0;
	int you = 0;
	int shang = 0;
	int xia = 0;
	// ���������鿴 https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx
	switch (kbstruct->vkCode) {
	case VK_SCROLL://�ر�ϵͳ
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			keyEvent(VK_RETURN, 1);
		}
		lock = false;
		break;
	case VK_OEM_3:// esc					For the US standard keyboard, the '`~' key
		keyEvent(VK_ESCAPE, 1);
		lock = false;
		break;
	case VK_ESCAPE:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_ESCAPE, 1);
		SetCursorPos(198, 685);
		lock = false;
		break;
	case VK_F3:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 20;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 300; //����������,��������
			shang = shang + 200;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_F4:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 20;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 300; //����������,��������
			shang = shang + 200;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			Sleep(600);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_OEM_COMMA:// ����Ҫ�Ĵ򵥽�			For any country/region, the ',' key

		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x49:// 	I key
		keyEvent(VK_UP, 1);
		lock = false;
		break;
	case 0x4A:// 	J key
		keyEvent(VK_LEFT, 1);
		lock = false;
		break;
	case 0x44:// 	K key
		keyEvent(VK_DOWN, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(0x31, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case 0x4C:// 	L key
		keyEvent(VK_RIGHT, 1);
		lock = false;
		break;
	case 0x50://		P key
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case 0x52:// ��ȡ	0x48��R key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 6);
		keyEvent(0x31, 1);
		keyEvent(VK_LEFT, 1);
		lock = false;
		break;
	case 0x59:// �Լ�	0x54��Y key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 5);
		keyEvent(0x31, 1);
		keyEvent(VK_LEFT, 1);
		lock = false;
		break;
	case 0x55:// �ҵĽű�4	0x54��U key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_F6, 2);
		lock = false;
		break;
	case 0x45:// ������			E key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_END, 1);
		keyEvent(VK_LEFT, 2);
		keyEvent(0x33, 1);
		lock = false;
		break;
	case 0x46:// 			F key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_END, 1);
		keyEvent(VK_LEFT, 2);
		keyEvent(0x31, 1);
		lock = false;
		break;
	case VK_OEM_PERIOD:// �ҵĽű�1		VK_OEM_PERIOD ��'.' key	
		keyEvent(VK_OEM_PERIOD, 1);
		keyEvent(0x35, 1);
		lock = false;
		break;
	case VK_OEM_5:// ɾ��			'\|' key
		keyEvent(VK_BACK, 1);
		lock = false;
		break;
	case VK_F1:// ɾ��			'\|' key
		keyEvent(VK_DELETE, 1);
		lock = false;
		break;
	case VK_F7:// ������1��O		F7
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_UP, 1);
		// ����
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);

		keyEvent(VK_DOWN, 1);
		// ճ��
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_SPACE:// �ո�
		if (switchSortCutStatus) {
			confirmSwitch();
		}
		else {
			keyEvent(VK_RETURN, 1);
		}
		lock = false;
		break;
	case VK_RETURN:// �س�
		if (switchSortCutStatus) {
			confirmSwitch();
		}
		else {
			keyEvent(VK_RETURN, 1);
		}
		lock = false;
		break;
	case VK_MULTIPLY:
		keyEvent(VK_ESCAPE, 1);
		copyUpline();
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x43:// ����			C key
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		lock = false;
		break;
	case 0x56:// ճ��			V key
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		lock = false;
		break;
	case VK_ADD:// ����		С���̼Ӻ�
		keyEvent(VK_HOME, 1);
		keyEvent(VK_END, 1);
		keyEvent(VK_LEFT, 2);
		keyEvent(0x32, 1);
		keyEvent(VK_DOWN, 1);
		keyEvent(0x31, 1);
		keyEvent(VK_LEFT, 1);
		lock = false;
		break;
	case 0x4E:// �����			N k3ey		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		keyEvent(VK_END, 1);
		keyEvent(VK_LEFT, 15);
		lock = false;
		break;
	case VK_NEXT:// ����			PGDN key
		keyEvent(VK_END, 1);
		keyEvent(VK_LEFT, 17);
		lock = false;
		break;
	case 0x57:// ����1000			W KEY
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(0x31, 1);
		keyEvent(0x30, 3);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x54:// ����500			T KEY
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(0x35, 1);
		keyEvent(0x30, 2);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_LEFT, 1);
		lock = false;
		break;
	case 0x42:// ����1000			B KEY
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(0x31, 1);
		keyEvent(0x30, 3);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x53:// ����2000			S KEY
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(0x32, 1);
		keyEvent(0x30, 3);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_TAB:// 					TAB key
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x41:// 			A KEY�ĸ�
		keyEvent(VK_HOME, 1);
		keyEvent(VK_END, 1);
		keyEvent(VK_LEFT, 2);
		keyEvent(0x31, 1);
		keyEvent(VK_DOWN, 1);
		keyEvent(0x31, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_LEFT, 1);
		lock = false;
		break;
	case 0x47:// 			G KEY
		keyEvent(VK_HOME, 1);
		keyEvent(VK_END, 1);
		keyEvent(VK_LEFT, 2);
		keyEvent(0x31, 1);
		// ճ��
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);

		keyEvent(VK_DOWN, 1);
		keyEvent(0x31, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_LEFT, 1);
		lock = false;
		break;
	case VK_INSERT:// ��0
		keyEvent(VK_END, 1);
		keyEvent(0x30, 1);
		lock = false;
		break;
	case VK_F11://����̼Ӻ�+++++++++�ͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½�
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 200; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 120; //����������,��������
			shang = shang + 130;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(100);
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		Sleep(100);
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 260; //����������,��������
			shang = shang + 130;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_OEM_6://]]  }}}����̼�++�������  ���ǳ���
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 60;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 1220; //����������,��������
			shang = shang + 700;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	//case VK_OEM_MINUS:// 7550355168			5 KEY
	//	keyEvent(0x30, 4);
	//	lock = false;
	//	break;
	}
	return lock;
}

// ����¼���ɽ
BOOL KetthProjectAction::keyAction4(PKBDLLHOOKSTRUCT kbstruct, boolean lock) {
	HWND hWnd = GetFocus(); // �õ���ǰ���̹�����ڵĴ��� 
	LPRECT lParam = new RECT;
	int zuo = 0;
	int you = 0;
	int shang = 0;
	int xia = 0;
	// ���������鿴 https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx
	switch (kbstruct->vkCode) {
	case VK_SCROLL://�ر�ϵͳ
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			keyEvent(VK_RETURN, 1);
		}
		lock = false;
		break;
	case VK_OEM_3:// esc					For the US standard keyboard, the '`~' key
		keyEvent(VK_ESCAPE, 1);
		lock = false;
		break;
	case VK_ESCAPE:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_ESCAPE, 1);
		SetCursorPos(198, 685);
		lock = false;
		break;
	case VK_F3:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 20;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 300; //����������,��������
			shang = shang + 200;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_F4:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 20;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 300; //����������,��������
			shang = shang + 200;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			Sleep(600);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_PRIOR:// F8			'\|' key
		keyEvent(VK_F8, 1);
		lock = false;
		break;
	case VK_OEM_COMMA:// ����Ҫ�Ĵ򵥽�			For any country/region, the ',' key
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x49:// 	I key
		keyEvent(VK_UP, 1);
		lock = false;
		break;
	case 0x4A:// 	J key
		keyEvent(VK_LEFT, 1);
		lock = false;
		break;
	case 0x4B:// 	K key
		keyEvent(VK_DOWN, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(0x31, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case 0x41:// 	A key
		keyEvent(VK_DOWN, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(0x31, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case VK_OEM_2:
		keyEvent(VK_DOWN, 1);
		lock = false;
		break;
	case 0x4C:// 	L key
		keyEvent(VK_END, 1);
		lock = false;
		break;
	case 0x50://		P key
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case 0x48:// ��ȡ	0x48��H key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 6);
		keyEvent(0x31, 1);
		keyEvent(VK_LEFT, 1);
		lock = false;
		break;
	case 0x54:// �Լ�	0x54��T key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 5);
		keyEvent(0x31, 1);
		keyEvent(VK_LEFT, 1);
		lock = false;
		break;
	case 0x55:// �ҵĽű�4	0x54��U key
		keyEvent(VK_F6, 2);
		lock = false;
		break;
	case 0x45:// ������			E key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_END, 1);
		keyEvent(VK_LEFT, 2);
		keyEvent(0x33, 1);
		lock = false;
		break;
	case 0x46:// 			F key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_END, 1);
		keyEvent(VK_LEFT, 2);
		keyEvent(0x31, 1);
		lock = false;
		break;
	case VK_OEM_PERIOD:// �ҵĽű�1		VK_OEM_PERIOD ��'.' key	
		keyEvent(VK_OEM_PERIOD, 1);
		keyEvent(0x35, 1);
		lock = false;
		break;
	case VK_OEM_5:// ɾ��			'\|' key
		keyEvent(VK_BACK, 1);
		lock = false;
		break;
	case VK_SPACE:// �ո�
		if (switchSortCutStatus) {
			confirmSwitch();
		}
		else {
			keyEvent(VK_RETURN, 1);
		}
		lock = false;
		break;
	case VK_RETURN:// �س�
		if (switchSortCutStatus) {
			confirmSwitch();
		}
		else {
			keyEvent(VK_RETURN, 1);
		}
		lock = false;
		break;
	case VK_F7:
		keyEvent(VK_ESCAPE, 1);
		copyUpline();
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_MULTIPLY:
		keyEvent(VK_ESCAPE, 1);
		copyUpline();
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x43:// ����			C key
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		lock = false;
		break;
	case 0x56:// ճ��			V key
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		lock = false;
		break;
	case VK_OEM_1:// ����		US standard keyboard, the ';:' key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_END, 1);
		keyEvent(VK_LEFT, 2);
		keyEvent(0x32, 1);
		keyEvent(VK_DOWN, 1);
		keyEvent(0x31, 1);
		keyEvent(VK_LEFT, 1);
		lock = false;
		break;
	case VK_ADD:// ����		US standard keyboard, the '+' key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_END, 1);
		keyEvent(VK_LEFT, 2);
		keyEvent(0x32, 1);
		keyEvent(VK_DOWN, 1);
		keyEvent(0x31, 1);
		keyEvent(VK_LEFT, 1);
		lock = false;
		break;
	case 0x58:// �����			X key
		keyEvent(VK_END, 1);
		keyEvent(VK_LEFT, 15);
		lock = false;
		break;
	case 0x5A:// ����			X key
		keyEvent(VK_END, 1);
		keyEvent(VK_LEFT, 12);
		lock = false;
		break;
	case 0x52:// ����5000			R KEY
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(0x35, 1);
		keyEvent(0x30, 3);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x57:// ����1000			W KEY
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(0x31, 1);
		keyEvent(0x30, 3);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_LEFT, 1);
		lock = false;
		break;
	case 0x51:// ����500			O KEY
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(0x35, 1);
		keyEvent(0x30, 2);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_LEFT, 1);
		lock = false;
		break;
	case 0x42:// ��װ1			O KEY
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 2);
		keyEvent(0x31, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_LEFT, 1);
		lock = false;
		break;
	case 0x59:// ί��20			O KEY
		keyEvent(VK_END, 1);
		keyEvent(VK_LEFT, 15);
		keyEvent(0x32, 1);
		keyEvent(0x30, 1);
		lock = false;
		break;
	case 0x4E:// ����20000			N KEY
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(0x32, 1);
		keyEvent(0x30, 4);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_LEFT, 1);
		lock = false;
		break;
	case 0x4D:// ����2000			M KEY
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(0x32, 1);
		keyEvent(0x30, 3);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_LEFT, 1);
		lock = false;
		break;
	case 0x53:// 			S KEY
		keyEvent(VK_HOME, 1);
		keyEvent(VK_END, 1);
		keyEvent(VK_LEFT, 2);
		keyEvent(0x31, 1);
		keyEvent(VK_DOWN, 1);
		keyEvent(0x31, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_LEFT, 1);
		lock = false;
		break;
	case 0x47:// 			G KEY
		keyEvent(VK_HOME, 1);
		keyEvent(VK_END, 1);
		keyEvent(VK_LEFT, 2);
		keyEvent(0x31, 1);
		// ճ��
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);

		keyEvent(VK_DOWN, 1);
		keyEvent(0x31, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_LEFT, 1);
		lock = false;
		break;
	case VK_INSERT:// ��0
		keyEvent(VK_END, 1);
		keyEvent(0x30, 1);
		lock = false;
		break;

	//case VK_OEM_MINUS:// 7550355168			5 KEY
	//	keyEvent(0x30, 4);
	//	lock = false;
	//	break;
	}
	return lock;
}

// QC
BOOL KetthProjectAction::keyAction5(PKBDLLHOOKSTRUCT kbstruct, boolean lock) {
	HWND hWnd = GetFocus(); // �õ���ǰ���̹�����ڵĴ��� 
	LPRECT lParam = new RECT;
	int zuo = 0;
	int you = 0;
	int shang = 0;
	int xia = 0;
	// ���������鿴 https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx
	switch (kbstruct->vkCode) {
	case VK_SCROLL://�ر�ϵͳ
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			keyEvent(VK_RETURN, 1);
		}
		lock = false;
		break;
	case VK_OEM_3:// esc					For the US standard keyboard, the '`~' key
		keyEvent(VK_ESCAPE, 1);
		lock = false;
		break;
	case VK_F1:
		hWnd = ::FindWindow(NULL, _T("���ν綨"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_F7, 1);
		lock = false;
		break;
	case 0x53://SSS
		hWnd = ::FindWindow(NULL, _T("���ν綨"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_F7, 1);
		lock = false;
		break;
	case VK_F3:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 20;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 300; //����������,��������
			shang = shang + 200;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_F4:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 20;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 300; //����������,��������
			shang = shang + 200;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			Sleep(600);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_OEM_PERIOD:// �ҵĽű�1		VK_OEM_PERIOD ��'.' key	
		keyEvent(VK_OEM_PERIOD, 1);
		keyEvent(0x35, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_SPACE:// �ո�
		hWnd = ::FindWindow(NULL, _T("���ν綨"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x43:// ����			C key
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		lock = false;
		break;
	case 0x56:// ճ��			V key
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		lock = false;
		break;
	case 0x46:// F   �ո�һ����
		hWnd = ::FindWindow(NULL, _T("���ν綨"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_F11://����̼Ӻ�+++++++++�ͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½�
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 200; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 120; //����������,��������
			shang = shang + 130;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(100);
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		Sleep(100);
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 260; //����������,��������
			shang = shang + 130;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_OEM_6://]]  }}}����̼�++�������  ���ǳ���
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 60;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 1220; //����������,��������
			shang = shang + 700;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	}
	return lock;
}

// �ķ�
BOOL KetthProjectAction::keyAction6(PKBDLLHOOKSTRUCT kbstruct, boolean lock) {
	HWND hWnd = GetFocus(); // �õ���ǰ���̹�����ڵĴ��� 
	LPRECT lParam = new RECT;
	int zuo = 0;
	int you = 0;
	int shang = 0;
	int xia = 0;
	// ���������鿴 https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx
	switch (kbstruct->vkCode) {
	case VK_SCROLL://�ر�ϵͳ
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			keyEvent(VK_RETURN, 1);
		}
		lock = false;
		break;
	case VK_OEM_3:// esc					For the US standard keyboard, the '`~' key
		keyEvent(VK_ESCAPE, 1);
		lock = false;
		break;
	case VK_OEM_MINUS:// ���ڼӵ绰����ǰ��
		keyEvent(VK_SPACE, 1);
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		Sleep(300);
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case VK_ESCAPE:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_ESCAPE, 1);
		SetCursorPos(198, 685);
		lock = false;
		break;
	case VK_F3:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 20;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 300; //����������,��������
			shang = shang + 200;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_F4:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 20;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 300; //����������,��������
			shang = shang + 200;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			Sleep(600);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_OEM_6:// ���ڼӵ绰����ǰ��
		keyEvent(VK_SPACE, 1);
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		lock = false;
		break;
	case VK_RETURN:// �س�
		if (switchSortCutStatus) {
			confirmSwitch();
		}
		else {
			keyEvent(VK_RETURN, 1);
		}
		lock = false;
		break;
	case VK_PRIOR:// F8			'\|' key
		keyEvent(VK_F8, 1);
		lock = false;
		break;
	case VK_OEM_COMMA:// ����Ҫ�Ĵ򵥽�			For any country/region, the ',' key
		keyEvent(VK_DOWN, 1);
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case VK_OEM_4://		For any country/region, the '[' key
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_LEFT, 1);
		// ����
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		// ճ��
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_OEM_5:// ɾ��			'\|' key
		keyEvent(VK_BACK, 1);
		lock = false;
		break;
	case VK_F1:// 	�ķ���ַ
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 5);
		testChinese(20315);
		testChinese(23665);
		keyEvent(VK_DOWN, 1);
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case VK_OEM_1:// 	�ķ���ַ0
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 5);
		keyEvent(0x30, 1);
		keyEvent(VK_DOWN, 1);
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case VK_OEM_PERIOD:// 	�ķ���ַ0
		keyEvent(0x30, 1);
		lock = false;
		break;
	case VK_DIVIDE:// �϶�������			F9
		keybd_event(VK_ESCAPE, 0, 0, 0);keybd_event(VK_HOME, 0, KEYEVENTF_KEYUP, 0);
		copyUpTwoline();
		keybd_event(VK_TAB, 0, 0, 0);keybd_event(VK_TAB, 0, KEYEVENTF_KEYUP, 0);
		copyUpTwoline();
		keybd_event(VK_TAB, 0, 0, 0);keybd_event(VK_TAB, 0, KEYEVENTF_KEYUP, 0);
		copyUpTwoline();
		keybd_event(VK_TAB, 0, 0, 0);keybd_event(VK_TAB, 0, KEYEVENTF_KEYUP, 0);
		copyUpTwoline();
		keybd_event(VK_TAB, 0, 0, 0);keybd_event(VK_TAB, 0, KEYEVENTF_KEYUP, 0);
		copyUpTwoline();
		keybd_event(VK_TAB, 0, 0, 0);keybd_event(VK_TAB, 0, KEYEVENTF_KEYUP, 0);
		copyUpTwoline();
		keyEvent(VK_DOWN, 1);
		lock = false;
		break;
	case VK_F9:// �϶�������			F9
		keybd_event(VK_ESCAPE, 0, 0, 0);keybd_event(VK_HOME, 0, KEYEVENTF_KEYUP, 0);
		copyUpTwoline();
		keybd_event(VK_TAB, 0, 0, 0);keybd_event(VK_TAB, 0, KEYEVENTF_KEYUP, 0);
		copyUpTwoline();
		keybd_event(VK_TAB, 0, 0, 0);keybd_event(VK_TAB, 0, KEYEVENTF_KEYUP, 0);
		copyUpTwoline();
		keybd_event(VK_TAB, 0, 0, 0);keybd_event(VK_TAB, 0, KEYEVENTF_KEYUP, 0);
		copyUpTwoline();
		keybd_event(VK_TAB, 0, 0, 0);keybd_event(VK_TAB, 0, KEYEVENTF_KEYUP, 0);
		copyUpTwoline();
		keybd_event(VK_TAB, 0, 0, 0);keybd_event(VK_TAB, 0, KEYEVENTF_KEYUP, 0);
		copyUpTwoline();
		keyEvent(VK_DOWN, 1);
		lock = false;
		break;
	case VK_PAUSE:// ����ר�ø�������			F10
		keyEvent(VK_HOME, 1);
		copyUpThreeline();
		keyEvent(VK_RETURN, 1);
		copyUpThreeline();
		keyEvent(VK_RETURN, 1);
		copyUpThreeline();
		keyEvent(VK_RETURN, 1);
		copyUpThreeline();
		keyEvent(VK_RETURN, 1);
		copyUpThreeline();
		keyEvent(VK_RETURN, 1);
		copyUpThreeline();
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_DOWN, 1);
		lock = false;
		break;
	case VK_F10:// ����ר�ø�������			F10
		keyEvent(VK_HOME, 1);
		copyUpThreeline();
		keyEvent(VK_RETURN, 1);
		copyUpThreeline();
		keyEvent(VK_RETURN, 1);
		copyUpThreeline();
		keyEvent(VK_RETURN, 1);
		copyUpThreeline();
		keyEvent(VK_RETURN, 1);
		copyUpThreeline();
		keyEvent(VK_RETURN, 1);
		copyUpThreeline();
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_DOWN, 1);
		lock = false;
		break;
	case VK_F7:// ������1��O		F7
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_UP, 1);
		// ����
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);

		keyEvent(VK_DOWN, 1);
		// ճ��
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_MULTIPLY:// ȫ������һ��	Z key0x5A 
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		copyUpline();
		keyEvent(VK_RETURN, 1);
		copyUpline();
		keyEvent(VK_RETURN, 1);
		copyUpline();
		keyEvent(VK_RETURN, 1);
		copyUpline();
		keyEvent(VK_RETURN, 1);
		copyUpline();
		keyEvent(VK_RETURN, 1);
		copyUpline();
		keyEvent(VK_DOWN, 1);
		lock = false;
		break;
	case VK_F5:// ȫ������һ��	Z key0x5A 
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		copyUpline();
		keyEvent(VK_RETURN, 1);
		copyUpline();
		keyEvent(VK_RETURN, 1);
		copyUpline();
		keyEvent(VK_RETURN, 1);
		copyUpline();
		keyEvent(VK_RETURN, 1);
		copyUpline();
		keyEvent(VK_RETURN, 1);
		copyUpline();
		keyEvent(VK_DOWN, 1);
		lock = false;
		break;
	case VK_F2:// MGS1111111		Add key
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_LEFT, 1);
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_OEM_2:// For the US standard keyboard, the '/?' key
		keyEvent(VK_DOWN, 1);
		lock = false;
		break;
	case VK_ADD:// For the US standard keyboard, the '/?' key
		keyEvent(VK_DOWN, 1);
		lock = false;
		break;
	case VK_INSERT:// ��0
		keyEvent(VK_END, 1);
		keyEvent(0x30, 1);
		lock = false;
		break;
	case VK_F11://����̼Ӻ�+++++++++�ͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½�
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 200; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 120; //����������,��������
			shang = shang + 130;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(100);
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		Sleep(100);
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 260; //����������,��������
			shang = shang + 130;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	}
	return lock;
}
	
// ����
BOOL KetthProjectAction::keyAction7(PKBDLLHOOKSTRUCT kbstruct, boolean lock) {
	HWND hWnd = GetFocus(); // �õ���ǰ���̹�����ڵĴ��� 
	LPRECT lParam = new RECT;
	int zuo = 0;
	int you = 0;
	int shang = 0;
	int xia = 0;
	// ���������鿴 https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx
	switch (kbstruct->vkCode) {
	case VK_SCROLL://�ر�ϵͳ
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			keyEvent(VK_RETURN, 1);
		}
		lock = false;
		break;
	case VK_OEM_3:// esc					For the US standard keyboard, the '`~' key
		keyEvent(VK_ESCAPE, 1);
		lock = false;
		break;
	case VK_ESCAPE:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_ESCAPE, 1);
		SetCursorPos(198, 685);
		lock = false;
		break;
	case VK_F3:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 20;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 300; //����������,��������
			shang = shang + 200;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_F4:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 20;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 300; //����������,��������
			shang = shang + 200;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			Sleep(600);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_RETURN:// �س�
		if (switchSortCutStatus) {
			confirmSwitch();
		}
		else {
			keyEvent(VK_RETURN, 1);
		}
		lock = false;
		break;
	case VK_OEM_COMMA:// ����Ҫ�Ĵ򵥼�   For any country/region, the ',' key
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_OEM_PERIOD:// �ҵĽű�1		VK_OEM_PERIOD ��'.' key	
		keyEvent(VK_OEM_PERIOD, 1);
		keyEvent(0x35, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_OEM_5:// ɾ��			'\|' key
		keyEvent(VK_BACK, 1);
		lock = false;
		break;
	case VK_F7:// ������1��O		F7
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_UP, 1);
		// ����
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);

		keyEvent(VK_DOWN, 1);
		// ճ��
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_OEM_1:// ����			US standard keyboard, the ';:' key
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 12);
		keyEvent(0x32, 1);
		keyEvent(VK_RETURN, 3);
		lock = false;
		break;
	case VK_F1:// s
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 12);
		keyEvent(0x31, 2);
		keyEvent(VK_RETURN, 2);
		lock = false;
		break;
	case VK_OEM_4:// MGS1111111		US standard keyboard, the '[{' key
		keyEvent(VK_RETURN, 1);
		keyEvent(0x30, 1);
		keyEvent(VK_LEFT, 1);
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_ESCAPE, 1);

		keyEvent(VK_NEXT, 1);
		keyEvent(0x30, 1);
		keyEvent(VK_LEFT, 1);
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_ESCAPE, 1);
		lock = false;
		break;
	case VK_F2:// FFFF
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 12);
		keyEvent(0x31, 1);
		keyEvent(VK_RETURN, 2);
		keyEvent(0x37, 1);
		keyEvent(0x35, 1);
		keyEvent(0x37, 1);
		lock = false;
		break;
	case VK_OEM_2:
		keyEvent(VK_DOWN, 1);
		lock = false;
		break;
	case VK_F11://����̼Ӻ�+++++++++�ͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½�
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 200; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 120; //����������,��������
			shang = shang + 130;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(100);
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		Sleep(100);
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 260; //����������,��������
			shang = shang + 130;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_OEM_6://]]  }}}����̼�++�������  ���ǳ���
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 60;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 1220; //����������,��������
			shang = shang + 700;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	}
	return lock;
}

BOOL KetthProjectAction::keyAction8(PKBDLLHOOKSTRUCT kbstruct, boolean lock) {
	HWND hWnd = GetFocus(); // �õ���ǰ���̹�����ڵĴ��� 
	LPRECT lParam = new RECT;
	int zuo = 0;
	int you = 0;
	int shang = 0;
	int xia = 0;
	// ���������鿴 https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx
	switch (kbstruct->vkCode) {
	case VK_SCROLL://�ر�ϵͳ
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			keyEvent(VK_RETURN, 1);
		}
		lock = false;
		break;
	case VK_OEM_3:// esc					For the US standard keyboard, the '`~' key
		keyEvent(VK_ESCAPE, 1);
		lock = false;
		break;
	case VK_ESCAPE:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_ESCAPE, 1);
		SetCursorPos(198, 685);
		lock = false;
		break;
	case VK_F3:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 20;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 300; //����������,��������
			shang = shang + 200;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_F4:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 20;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 300; //����������,��������
			shang = shang + 200;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			Sleep(600);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_RETURN:// �س�
		if (switchSortCutStatus) {
			confirmSwitch();
		}
		else {
			keyEvent(VK_RETURN, 1);
		}
		lock = false;
		break;
	case VK_OEM_PERIOD:// ���
		keyEvent(VK_RETURN, 2);
		lock = false;
		break;
	case VK_OEM_5:// ɾ��			'\|' key
		keyEvent(VK_BACK, 1);
		lock = false;
		break;
	case VK_PRIOR:// F8			'\|' key
		keyEvent(VK_F8, 1);
		lock = false;
		break;
	case VK_F1:
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case VK_INSERT:// ��0
		keyEvent(VK_END, 1);
		keyEvent(0x30, 1);
		lock = false;
		break;
	case VK_F11://����̼Ӻ�+++++++++�ͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½�
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 200; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 120; //����������,��������
			shang = shang + 130;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(100);
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		Sleep(100);
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 260; //����������,��������
			shang = shang + 130;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_OEM_6://]]  }}}����̼�++�������  ���ǳ���
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 60;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 1220; //����������,��������
			shang = shang + 700;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;

	}
	return lock;
	
}

// R HKG
BOOL KetthProjectAction::keyAction9(PKBDLLHOOKSTRUCT kbstruct, boolean lock) {
	HWND hWnd = GetFocus(); // �õ���ǰ���̹�����ڵĴ��� 
	LPRECT lParam = new RECT;
	int zuo = 0;
	int you = 0;
	int shang = 0;
	int xia = 0;
	// ���������鿴 https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx
	switch (kbstruct->vkCode) {
	case VK_OEM_3:// esc					For the US standard keyboard, the '`~' key
		keyEvent(VK_ESCAPE, 1);
		lock = false;
		break;
	case VK_ESCAPE:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_ESCAPE, 1);
		SetCursorPos(198, 685);
		lock = false;
		break;
	case VK_F3:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 20;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 300; //����������,��������
			shang = shang + 200;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_F4:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 20;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 300; //����������,��������
			shang = shang + 200;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			Sleep(600);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_NUMPAD0:// ��������	  VK_SUBTRACT ��С���̼���
		inputText("asdf054132");
		keyEvent(VK_OEM_PERIOD, 1);
		Sleep(100);
		keyEvent(VK_RETURN, 1); 
		lock = false;
		break;
	case VK_NUMPAD1:// ��������	  VK_SUBTRACT ��С���̼���
		inputText("966859");
		Sleep(200);
		keyEvent(VK_TAB, 1);
		Sleep(200); 
		inputText("sf8520963");
		Sleep(200);
		keyEvent(VK_OEM_PERIOD, 1);
		Sleep(200);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_NUMPAD2:// ��������	  VK_SUBTRACT ��С���̼���
		inputText("crg8520963");
		keyEvent(VK_OEM_PERIOD, 1);
		Sleep(100);
		keyEvent(VK_RETURN, 1);
		break;
	case VK_NUMPAD9:// ��������	  VK_SUBTRACT ��С���̼���
		inputText("cjh8520963");
		keyEvent(VK_OEM_PERIOD, 1);
		Sleep(100);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_F1:// ��������	  VK_SUBTRACT ��С���̼���
		inputText("sf8520963");
		keyEvent(VK_OEM_PERIOD, 1);
		Sleep(200);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_F2:// ��������	  VK_SUBTRACT ��С���̼���
		inputText("crg8520963");
		keyEvent(VK_OEM_PERIOD, 1);
		Sleep(100);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_PRIOR:// F8			'\|' key
		keyEvent(VK_F8, 1);
		lock = false;
		break;
	case VK_RETURN:// �س�
		if (switchSortCutStatus) {
			confirmSwitch();
		}
		else {
			keyEvent(VK_RETURN, 1);
		}
		lock = false;
		break;
	case VK_OEM_COMMA:// ����Ҫ�Ĵ򵥼�   For any country/region, the ',' key
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_OEM_1://			US standard keyboard, the ';:' key
		keybd_event(VK_LEFT, 0, 0, 0);keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_LEFT, 0, 0, 0);keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);
		lock = false;
		break;
	case VK_OEM_5:// ɾ��			'\|' key
		keyEvent(VK_BACK, 1);
		lock = false;
		break;
	case VK_OEM_2:// ��   /
		keyEvent(VK_DOWN, 1);
		lock = false;
		break;
	case VK_F9:// ��   /
		keyEvent(VK_DOWN, 1);
		lock = false;
		break;

	case VK_F7: // ������һ��
		keyEvent(VK_ESCAPE, 1);
		copyUpline();
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_OEM_4://  ���ڼӵ绰����ǰ��
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_LEFT, 1);
		// ����
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		// ճ��
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_F5:// ���ڼӵ绰����ǰ��
		keyEvent(VK_SPACE, 1);
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		Sleep(300);
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case VK_INSERT:// ��0
		keyEvent(VK_END, 1);
		keyEvent(0x30, 1);
		lock = false;
		break;
	case VK_F11://����̼Ӻ�+++++++++�ͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½�
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 200; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 120; //����������,��������
			shang = shang + 130;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(100);
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		Sleep(100);
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 260; //����������,��������
			shang = shang + 130;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_SCROLL://�ر�ϵͳ
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			keyEvent(VK_RETURN, 1);
		}
		lock = false;
		break;
	case VK_OEM_6://]]  }}}����̼�++�������  ���ǳ���
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 60;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 1220; //����������,��������
			shang = shang + 700;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;

	}
	return lock;
}

BOOL KetthProjectAction::keyAction10(PKBDLLHOOKSTRUCT kbstruct, boolean lock) {
	HWND hWnd = GetFocus(); // �õ���ǰ���̹�����ڵĴ��� 
	LPRECT lParam = new RECT;
	int zuo = 0;
	int you = 0;
	int shang = 0;
	int xia = 0;
							// ���������鿴 https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx
	switch (kbstruct->vkCode) {
	case VK_SCROLL://�ر�ϵͳ
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			keyEvent(VK_RETURN, 1);
		}
		lock = false;
		break;
	case VK_F12:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_F8, 1);
		SetCursorPos(198, 685);
		lock = false;
		break;
	case VK_F8:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_ESCAPE, 1);
		SetCursorPos(198, 685);
		lock = false;
		break;
	case VK_OEM_3:// esc					For the US standard keyboard, the '`~' key
		keyEvent(VK_ESCAPE, 11);
		lock = false;
		break;
	case VK_ESCAPE:
		keyEvent(VK_ESCAPE, 11);
		Sleep(66);
		keyEvent(VK_ESCAPE, 11);
		lock = false;
		break;
	case VK_F3:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 20;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 300; //����������,��������
			shang = shang + 200;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_F4:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 20;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 300; //����������,��������
			shang = shang + 200;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			Sleep(600);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock= false;
		break;
	case VK_F1:
		keyEvent(VK_RETURN, 1);
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case VK_F2:// FFF757			F key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RETURN, 1);
		SetCursorPos(198, 685);
		lock = false;
		break;
	case VK_OEM_2:// ��			? key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_DOWN, 1);
		keyEvent(VK_ESCAPE, 1);
		lock = false;
		break;
	case VK_OEM_4:// ��	
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_LEFT, 1);
		lock = false;
		break;
	case 0x48:// ��ȡ	0x48��H key
			hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
			if (hWnd != NULL) {
				::GetWindowRect(hWnd, lParam);
				//int zuo = lParam->left;
				you = lParam->right;
				shang = lParam->top;
				//int xia = lParam->bottom;
				you = you - 20; //����������,��������
				shang = shang + 10;//��������,��������
				SetCursorPos(you, shang);
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			}

			keyEvent(VK_RETURN, 1);
			keyEvent(VK_ESCAPE, 1);
			keyEvent(VK_HOME, 1);
			keyEvent(VK_TAB, 12);
			keyEvent(VK_NUMPAD1, 1);
			keyEvent(VK_LEFT, 1);
		lock = false;
		break;
	case 0x54:// �Լ�	0x54��T key
			hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
			if (hWnd != NULL) {
				::GetWindowRect(hWnd, lParam);
				//int zuo = lParam->left;
				you = lParam->right;
				shang = lParam->top;
				//int xia = lParam->bottom;
				you = you - 20; //����������,��������
				shang = shang + 10;//��������,��������
				SetCursorPos(you, shang);
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			}
			keyEvent(VK_RETURN, 1);
			keyEvent(VK_ESCAPE, 1);
			keyEvent(VK_HOME, 1);
			keyEvent(VK_TAB, 13);
			keyEvent(VK_NUMPAD1, 1);
			keyEvent(VK_LEFT, 1);
			lock = false;
			break;
	case VK_OEM_PERIOD:// FFF757			F key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		Sleep(100);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RETURN, 1);
		SetCursorPos(198, 685);
		lock = false;
		break;
	case 0x4D:// M��0.5
			keyEvent(VK_OEM_PERIOD, 1);
			keyEvent(0x35, 1);
			keyEvent(VK_RETURN, 2);

		lock = false;
		break;
	case VK_OEM_MINUS:// M��0.5
		if (mutiKey[0] == 0) { //�����л�
			keyEvent(VK_ESCAPE, 1);
			keyEvent(0x30, 1);
			keyEvent(VK_OEM_PERIOD, 1);
			keyEvent(0x31, 1);
			mutiKey[0] = 1;  //�л����ڶ�������
		}
		else {
			keyEvent(VK_ESCAPE, 1);
			keyEvent(0x30, 1);
			keyEvent(VK_OEM_PERIOD, 1);
			keyEvent(0x35, 1);
			mutiKey[0] = 0;   //�л��ص�һ������
		}
		lock = false;
		break;
	case 0x4C:// ����1000			L key
		if (mutiKey[3]==0) { //�����л�
			hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
			if (hWnd != NULL) {
				::GetWindowRect(hWnd, lParam);
				//int zuo = lParam->left;
				you = lParam->right;
				shang = lParam->top;
				//int xia = lParam->bottom;
				you = you - 20; //����������,��������
				shang = shang + 10;//��������,��������
				SetCursorPos(you, shang);
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			}
			keyEvent(VK_RETURN, 1);
			keyEvent(VK_HOME, 1);
			keyEvent(VK_RETURN, 1);
			keyEvent(VK_TAB, 10);
			keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
			keyEvent(VK_RETURN, 1);
			SetCursorPos(198, 685);
			mutiKey[3] = 1;  //�л����ڶ�������
		}
		else {
			hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
			if (hWnd != NULL) {
				::GetWindowRect(hWnd, lParam);
				//int zuo = lParam->left;
				you = lParam->right;
				shang = lParam->top;
				//int xia = lParam->bottom;
				you = you - 20; //����������,��������
				shang = shang + 10;//��������,��������
				SetCursorPos(you, shang);
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			}
			keyEvent(VK_RETURN, 1);
			keyEvent(VK_HOME, 1);
			keyEvent(VK_RIGHT, 11);
			inputText("0");
			keyEvent(VK_RETURN, 1);
			SetCursorPos(198, 685);
			mutiKey[3] = 0;   //�л��ص�һ������
		}
		lock = false;
		break;
	case VK_OEM_5:// ɾ��			'\|' key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_BACK, 1);
		lock = false;
		break;
	case 0x58:// �ڼ�				X key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 16);
		keyEvent(VK_NUMPAD1, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keybd_event(0x33, 0, 0, 0);keybd_event(0x33, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_SPACE:// �ո�
		if (switchSortCutStatus) {
			confirmSwitch();
		}
		else {
			keyEvent(VK_RETURN, 1);
		}
		lock = false;
		break;
	case VK_RETURN:// �س�
		if (switchSortCutStatus) {
			confirmSwitch();
		}
		else {
			keyEvent(VK_RETURN, 1);
		}
		lock = false;
		break;
	case 0x4B:// ��		K	 key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_DOWN, 1);
		keyEvent(VK_HOME, 1);
		SetCursorPos(198, 685);
		lock = false;
		break;
	case 0x4E:// 			N key
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		SetCursorPos(198, 685);
		lock = false;
		break;
	case 0x5A:// ������			Z key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_RETURN, 2);
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keybd_event(0x33, 0, 0, 0);keybd_event(0x33, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
		
	case VK_OEM_COMMA:// ���żĸ�
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_PAUSE, 1);
		keyEvent(VK_RETURN, 3);

		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RETURN, 1);
		SetCursorPos(198, 685);
		lock = false;
		break;
	case VK_F9:// ����ר�ø����϶�			F9
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			keyEvent(VK_RETURN, 1);
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		copyUpTwoline();
		keyEvent(VK_RETURN, 1);
		copyUpTwoline();
		keyEvent(VK_RETURN, 1);
		copyUpTwoline();
		keyEvent(VK_RETURN, 1);
		copyUpTwoline();
		keyEvent(VK_RETURN, 1);
		copyUpTwoline();
		keyEvent(VK_RETURN, 1);
		copyUpTwoline();
		keyEvent(VK_RETURN, 1);
		copyUpTwoline();
		keyEvent(VK_RETURN, 1);
		copyUpTwoline();
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_LEFT, 4);
		lock = false;
		break;
	case VK_F10:// ����ר�ø�������			F10
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			keyEvent(VK_RETURN, 1);
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		copyUpThreeline();
		keyEvent(VK_RETURN, 1);
		copyUpThreeline();
		keyEvent(VK_RETURN, 1);
		copyUpThreeline();
		keyEvent(VK_RETURN, 1);
		copyUpThreeline();
		keyEvent(VK_RETURN, 1);
		copyUpThreeline();
		keyEvent(VK_RETURN, 1);
		copyUpThreeline();
		keyEvent(VK_RETURN, 1);
		copyUpThreeline();
		keyEvent(VK_RETURN, 1);
		copyUpThreeline();
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_LEFT, 4);
		lock = false;
		break;
	case 0x4A:// ������һ�й���ר	J key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		copyUpline();
		keyEvent(VK_RETURN, 1);
		copyUpline();
		keyEvent(VK_RETURN, 1);
		copyUpline();
		keyEvent(VK_RETURN, 1);
		copyUpline();
		keyEvent(VK_RETURN, 1);
		copyUpline();
		keyEvent(VK_RETURN, 1);
		copyUpline();
		keyEvent(VK_RETURN, 1);
		copyUpline();
		keyEvent(VK_RETURN, 1);
		copyUpline();
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_LEFT, 4);
		lock = false;
		break;
	case 0x43:// ����			C key

		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		lock = false;
		break;
	case 0x56:// ճ��			V key
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		lock = false;
		break;
	case 0x42:// ������			B key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keybd_event(0x33, 0, 0, 0);keybd_event(0x33, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x44:// �����			D key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_END, 1);
		keyEvent(VK_LEFT, 1);
		keyEvent(VK_LEFT, 2);
		SetCursorPos(198, 685);
		lock = false;
		break;
	case 0x59:// ����	
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RIGHT, 11);
		inputText("AU");
		keyEvent(VK_RETURN, 1);
		Sleep(100);
		keyEvent(0x31, 1);
		keyEvent(VK_RETURN, 1);
		SetCursorPos(198, 685);
		lock = false;
		break;
	case 0x41:// A			A KEY
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 14);
		SetCursorPos(198, 685);
		lock = false;
		break;
	case 0x57:// W1212			W key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_TAB, 6);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);

		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x32, 0, 0, 0);keybd_event(0x32, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x32, 0, 0, 0);keybd_event(0x32, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_DOWN, 1);
		SetCursorPos(198, 685);
		lock = false;
		break;
	case VK_OEM_1:// ����		US standard keyboard, the ';:' key
			hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
			if (hWnd != NULL) {
				::GetWindowRect(hWnd, lParam);
				//int zuo = lParam->left;
				you = lParam->right;
				shang = lParam->top;
				//int xia = lParam->bottom;
				you = you - 20; //����������,��������
				shang = shang + 10;//��������,��������
				SetCursorPos(you, shang);
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			}
			keyEvent(VK_RETURN, 1);
			keyEvent(VK_ESCAPE, 1);
			keyEvent(VK_HOME, 1);
			keyEvent(VK_TAB, 3);
			keyEvent(0x32, 1);
			keyEvent(VK_RETURN, 3);
			SetCursorPos(198, 685);
		lock = false;
		break;
	case 0x46:// FFF757			F key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RETURN, 1);
		SetCursorPos(198, 685);
		lock = false;
		break;
	case 0x53:// S			S key�ĸ�
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_PAUSE, 1);
		keyEvent(VK_RETURN, 3);

		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RETURN, 1);
		SetCursorPos(198, 685);

		lock = false;
		break;
	case 0x4F:// O2323			O KEY
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_TAB, 6);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);

		keybd_event(0x32, 0, 0, 0);keybd_event(0x32, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x33, 0, 0, 0);keybd_event(0x33, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x32, 0, 0, 0);keybd_event(0x32, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x33, 0, 0, 0);keybd_event(0x33, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_DOWN, 1);
		SetCursorPos(198, 685);
		lock = false;
		break;
	case VK_F7:// ������1��O		F7
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_UP, 1);
		// ����
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);

		keyEvent(VK_DOWN, 1);
		// ճ��
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x55:// U2323			U KEY
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_TAB, 6);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);

		keybd_event(0x32, 0, 0, 0);keybd_event(0x32, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x32, 0, 0, 0);keybd_event(0x32, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x32, 0, 0, 0);keybd_event(0x32, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x32, 0, 0, 0);keybd_event(0x32, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_DOWN, 1);
		SetCursorPos(198, 685);
		lock = false;
		break;
	case 0x50:// P1818			P key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_TAB, 6);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);

		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x38, 0, 0, 0);keybd_event(0x38, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x38, 0, 0, 0);keybd_event(0x38, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_DOWN, 1);
		SetCursorPos(198, 685);
		lock = false;

		break;
	case 0x51:// qq3030			Q key
		if (mutiKey[4] == 0) { //�����л�
			hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
			if (hWnd != NULL) {
				::GetWindowRect(hWnd, lParam);
				//int zuo = lParam->left;
				you = lParam->right;
				shang = lParam->top;
				//int xia = lParam->bottom;
				you = you - 20; //����������,��������
				shang = shang + 10;//��������,��������
				SetCursorPos(you, shang);
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			}
			keyEvent(VK_HOME, 1);
			keyEvent(VK_RETURN, 1);
			keyEvent(VK_TAB, 6);
			keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
			keyEvent(VK_RETURN, 1);
			keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
			keyEvent(VK_RETURN, 1);

			keybd_event(0x33, 0, 0, 0);keybd_event(0x33, 0, KEYEVENTF_KEYUP, 0);
			keybd_event(0x30, 0, 0, 0);keybd_event(0x30, 0, KEYEVENTF_KEYUP, 0);
			keyEvent(VK_RETURN, 1);
			keybd_event(0x33, 0, 0, 0);keybd_event(0x33, 0, KEYEVENTF_KEYUP, 0);
			keybd_event(0x30, 0, 0, 0);keybd_event(0x30, 0, KEYEVENTF_KEYUP, 0);
			mutiKey[4] = 1;  //�л����ڶ�������
		}
		else {
			hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
			if (hWnd != NULL) {
				::GetWindowRect(hWnd, lParam);
				//int zuo = lParam->left;
				you = lParam->right;
				shang = lParam->top;
				//int xia = lParam->bottom;
				you = you - 20; //����������,��������
				shang = shang + 10;//��������,��������
				SetCursorPos(you, shang);
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			}
			keyEvent(VK_HOME, 1);
			keyEvent(VK_RETURN, 1);
			keyEvent(VK_TAB, 6);
			keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
			keyEvent(VK_RETURN, 1);
			keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
			keyEvent(VK_RETURN, 1);

			keybd_event(0x31, 0, 0, 0);keybd_event(0x33, 0, KEYEVENTF_KEYUP, 0);
			keybd_event(0x36, 0, 0, 0);keybd_event(0x30, 0, KEYEVENTF_KEYUP, 0);
			keyEvent(VK_RETURN, 1);
			keybd_event(0x31, 0, 0, 0);keybd_event(0x33, 0, KEYEVENTF_KEYUP, 0);
			keybd_event(0x36, 0, 0, 0);keybd_event(0x30, 0, KEYEVENTF_KEYUP, 0);
			mutiKey[4] = 0;   //�л��ص�һ������
		}
		lock = false;
		break;
	case 0x49:// I1111			I key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_TAB, 6);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);

		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_DOWN, 1);
		SetCursorPos(198, 685);
		lock = false;
		break;
	case 0x45:// E1313			E key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_TAB, 6);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);

		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x33, 0, 0, 0);keybd_event(0x33, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x33, 0, 0, 0);keybd_event(0x33, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_DOWN, 1);
		SetCursorPos(198, 685);
		lock = false;
		break;

	case 0x47:// GGGG			G key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RETURN, 1);
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		SetCursorPos(198, 685);
		lock = false;
		break;
	case 0x52:// R477			R KEY
		if (mutiKey[1]==0) { //�����л�
			hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
			if (hWnd != NULL) {
				::GetWindowRect(hWnd, lParam);
				//int zuo = lParam->left;
				you = lParam->right;
				shang = lParam->top;
				//int xia = lParam->bottom;
				you = you - 20; //����������,��������
				shang = shang + 10;//��������,��������
				SetCursorPos(you, shang);
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			};
			keyEvent(VK_RETURN, 1);
			keyEvent(VK_ESCAPE, 1);
			Sleep(100);
			keyEvent(VK_HOME, 1);
			keyEvent(VK_TAB, 17);
			keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
			keybd_event(0x34, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
			keybd_event(0x37, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
			keybd_event(0x37, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
			mutiKey[1] = 1;  //�л����ڶ�������
		}
		else {
			keyEvent(VK_ESCAPE, 1);
			keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
			keybd_event(0x32, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
			keybd_event(0x33, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
			mutiKey[1] = 0;   //�л��ص�һ������
		}
		lock = false;
		break;
	case VK_INSERT:// ��0
		keyEvent(VK_END, 1);
		keyEvent(0x30, 1);
		lock = false;
		break;
	case VK_F11://����̼Ӻ�+++++++++�ͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½�
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 200; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 120; //����������,��������
			shang = shang + 130;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(100);
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		Sleep(100);
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 260; //����������,��������
			shang = shang + 130;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_OEM_6://]]  }}}����̼�++�������  ���ǳ���
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 60;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 1220; //����������,��������
			shang = shang + 700;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	}
	return lock;
}

BOOL KetthProjectAction::keyAction11(PKBDLLHOOKSTRUCT kbstruct, boolean lock) {
	HWND hWnd = GetFocus(); // �õ���ǰ���̹�����ڵĴ��� 
	LPRECT lParam = new RECT;
	int zuo = 0;
	int you = 0;
	int shang = 0;
	int xia = 0;
	// ���������鿴 https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx
	switch (kbstruct->vkCode) {
	case VK_SCROLL://�ر�ϵͳ
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			keyEvent(VK_RETURN, 1);
		}
		lock = false;
		break;
	case VK_ESCAPE:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_ESCAPE, 1);
		SetCursorPos(198, 685);
		lock = false;
		break;
	case VK_F3:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 20;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 300; //����������,��������
			shang = shang + 200;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_F4:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 20;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 300; //����������,��������
			shang = shang + 200;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			Sleep(600);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_OEM_3:// esc					For the US standard keyboard, the '`~' key
		keyEvent(VK_ESCAPE, 1);
		lock = false;
		break;
	case VK_PRIOR:// F8			'\|' key
		keyEvent(VK_F8, 1);
		lock = false;
		break;
	case VK_OEM_COMMA:// ����Ҫ�Ĵ򵥽�			For any country/region, the ',' key
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x42:// 			B keyͼƬ��
		keyEvent(VK_END, 1);
		keyEvent(VK_LEFT, 2);
		keyEvent(0x30, 1);
		lock = false;
		break;
	case 0x49:// 	I key
		keyEvent(VK_UP, 1);
		lock = false;
		break;
	case 0x4A:// 	J key
		keyEvent(VK_LEFT, 1);
		lock = false;
		break;
	case 0x4B:// 	K key
		keyEvent(VK_DOWN, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(0x31, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case 0x58:// 	X key
		keyEvent(VK_DOWN, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(0x31, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case VK_OEM_2:
		keyEvent(VK_DOWN, 1);
		lock = false;
		break;
	case 0x4C:// 	L key
		keyEvent(VK_END, 1);
		lock = false;
		break;
	case 0x50://		P key
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case 0x48:// ��ȡ	0x48��H key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 6);
		keyEvent(0x31, 1);
		keyEvent(VK_LEFT, 1);
		lock = false;
		break;
	case 0x54:// �Լ�	0x54��T key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 5);
		keyEvent(0x31, 1);
		keyEvent(VK_LEFT, 1);
		lock = false;
		break;
	case VK_DIVIDE:// ��ȡ	0x48��H key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 6);
		keyEvent(0x31, 1);
		keyEvent(VK_LEFT, 1);
		lock = false;
		break;
	case VK_MULTIPLY:// �Լ�	0x54��T key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 5);
		keyEvent(0x31, 1);
		keyEvent(VK_LEFT, 1);
		lock = false;
		break;
	case 0x55:// �ҵĽű�4	0x54��U key
		keyEvent(VK_F6, 2);
		lock = false;
		break;
	case 0x45:// ������			E key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_END, 1);
		keyEvent(VK_LEFT, 2);
		keyEvent(0x33, 1);
		lock = false;
		break;
	case 0x46:// 			F key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_END, 1);
		keyEvent(VK_LEFT, 2);
		keyEvent(0x31, 1);
		lock = false;
		break;
	case VK_OEM_PERIOD:// �ҵĽű�1		VK_OEM_PERIOD ��'.' key	
		keyEvent(VK_OEM_PERIOD, 1);
		keyEvent(0x35, 1);
		lock = false;
		break;
	case VK_OEM_5:// ɾ��			'\|' key
		keyEvent(VK_BACK, 1);
		lock = false;
		break;
	case VK_SPACE:// �ո�
		if (switchSortCutStatus) {
			confirmSwitch();
		}
		else {
			keyEvent(VK_RETURN, 1);
		}
		lock = false;
		break;
	case VK_RETURN:// �س�
		if (switchSortCutStatus) {
			confirmSwitch();
		}
		else {
			keyEvent(VK_RETURN, 1);
		}
		lock = false;
		break;
	case VK_F7:
		keyEvent(VK_ESCAPE, 1);
		copyUpline();
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x43:// ����			C key
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		lock = false;
		break;
	case 0x56:// ճ��			V key
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		lock = false;
		break;
	case VK_OEM_1:// ����		US standard keyboard, the ';:' key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_END, 1);
		keyEvent(VK_LEFT, 2);
		keyEvent(0x32, 1);
		keyEvent(VK_DOWN, 1);
		keyEvent(0x31, 1);
		keyEvent(VK_LEFT, 1);
		lock = false;
		break;
	case VK_ADD:// ����		US standard keyboard, the ';:' key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_END, 1);
		keyEvent(VK_LEFT, 2);
		keyEvent(0x32, 1);
		keyEvent(VK_DOWN, 1);
		keyEvent(0x31, 1);
		keyEvent(VK_LEFT, 1);
		lock = false;
		break;
	case 0x41:// �����			A key
		keyEvent(VK_END, 1);
		keyEvent(VK_LEFT, 15);
		lock = false;
		break;
	case 0x52:// ����5000			R KEY
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(0x35, 1);
		keyEvent(0x30, 3);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_LEFT, 1);
		lock = false;
		break;
	case 0x57:// ����1000			W KEY
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(0x31, 1);
		keyEvent(0x30, 3);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_LEFT, 1);
		lock = false;
		break;
	case 0x4F:// ����500			O KEY
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(0x35, 1);
		keyEvent(0x30, 2);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x51:// ����500			Q KEY
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(0x35, 1);
		keyEvent(0x30, 2);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_LEFT, 1);
		lock = false;
		break;
	case 0x4E:// ����20000			N KEY
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(0x32, 1);
		keyEvent(0x30, 4);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x4D:// ����2000			M KEY
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(0x32, 1);
		keyEvent(0x30, 3);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_LEFT, 1);
		lock = false;
		break;
	case 0x59:// ����10000			Y KEY
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(0x31, 1);
		keyEvent(0x30, 4);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_LEFT, 1);
		lock = false;
		break;
	case 0x53:// 			S KEY
		keyEvent(VK_HOME, 1);
		keyEvent(VK_END, 1);
		keyEvent(VK_LEFT, 2);
		keyEvent(0x31, 1);
		keyEvent(VK_DOWN, 1);
		keyEvent(0x31, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_LEFT, 1);
		lock = false;
		break;
	case 0x47:// 			G KEY
		keyEvent(VK_HOME, 1);
		keyEvent(VK_END, 1);
		keyEvent(VK_LEFT, 2);
		keyEvent(0x31, 1);
		// ճ��
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);

		keyEvent(VK_DOWN, 1);
		keyEvent(0x31, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_LEFT, 1);
		lock = false;
		break;
	case 0x44:// 	D key
		keyEvent(VK_DOWN, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(0x31, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case VK_INSERT:// ��0
		keyEvent(VK_END, 1);
		keyEvent(0x30, 1);
		lock = false;
		break;
	case VK_F11://����̼Ӻ�+++++++++�ͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½�
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 200; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 120; //����������,��������
			shang = shang + 130;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(100);
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		Sleep(100);
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 260; //����������,��������
			shang = shang + 130;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_OEM_6://]]  }}}����̼�++�������  ���ǳ���
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 60;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 1220; //����������,��������
			shang = shang + 700;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
		//case VK_OEM_MINUS:// 7550355168			5 KEY
		//	keyEvent(0x30, 4);
		//	lock = false;
		//	break;
	}
	return lock;
}

BOOL KetthProjectAction::keyAction12(PKBDLLHOOKSTRUCT kbstruct, boolean lock) {
	HWND hWnd = GetFocus(); // �õ���ǰ���̹�����ڵĴ��� 
	LPRECT lParam = new RECT;
	int zuo = 0;
	int you = 0;
	int shang = 0;
	int xia = 0;
	// ���������鿴 https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx
	switch (kbstruct->vkCode) {
	case VK_SCROLL://�ر�ϵͳ
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			keyEvent(VK_RETURN, 1);
		}
		lock = false;
		break;
	case 0x43:// ����			C key

		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		lock = false;
		break;
	case 0x56:// ճ��			V key
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		lock = false;
		break;
	case VK_OEM_2:// ��   /
		keyEvent(VK_DOWN, 1);
		lock = false;
		break;
	case VK_F3:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 20;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 300; //����������,��������
			shang = shang + 200;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_F4:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 20;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 300; //����������,��������
			shang = shang + 200;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			Sleep(600);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_ESCAPE:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_ESCAPE, 1);
		SetCursorPos(198, 685);
		lock = false;
		break;
	case VK_OEM_3:// esc					For the US standard keyboard, the '`~' key
		keyEvent(VK_ESCAPE, 1);
		lock = false;
		break;
	case VK_F1:
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case 0x34:// 	֤��
		keyEvent(VK_HOME, 1);
		testChinese(35777);
		testChinese(20214);
		keyEvent(VK_DOWN, 1);
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case 0x35:// 	����
		keyEvent(VK_HOME, 1);
		testChinese(36164);
		testChinese(26009);
		keyEvent(VK_DOWN, 1);
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case 0x57:// 	�ļ�
		keyEvent(VK_HOME, 1);
		testChinese(25991);
		testChinese(20214);
		keyEvent(VK_DOWN, 1);
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case 0x45:// 	��
		keyEvent(VK_HOME, 1);
		testChinese(24067);
		keyEvent(VK_DOWN, 1);
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case 0x52:// 	��Ʊ
		keyEvent(VK_HOME, 1);
		testChinese(21457);
		testChinese(31080);
		keyEvent(VK_DOWN, 1);
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case 0x54:// 	��ͬ
		keyEvent(VK_HOME, 1);
		testChinese(21512);
		testChinese(21516);
		keyEvent(VK_DOWN, 1);
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case 0x51:// 	Ŀ¼
		keyEvent(VK_HOME, 1);
		testChinese(30446);
		testChinese(24405);
		keyEvent(VK_DOWN, 1);
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case 0x32:// 	����
		keyEvent(VK_HOME, 1);
		testChinese(20869);
		testChinese(34915);
		keyEvent(VK_DOWN, 1);
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case 0x33:// 	Ь��
		keyEvent(VK_HOME, 1);
		testChinese(38795);
		testChinese(23376);
		keyEvent(VK_DOWN, 1);
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case 0x31:// 	�·�
		keyEvent(VK_HOME, 1);
		testChinese(34915);
		testChinese(26381);
		keyEvent(VK_DOWN, 1);
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case 0x5A:// 	����Ʒ
		keyEvent(VK_HOME, 1);
		testChinese(25252);
		testChinese(32932);
		testChinese(21697);
		keyEvent(VK_DOWN, 1);
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case 0x58:// 	��ױƷ
		keyEvent(VK_HOME, 1);
		testChinese(21270);
		testChinese(22918);
		testChinese(21697);
		keyEvent(VK_DOWN, 1);
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case 0x36:// 	������
		keyEvent(VK_HOME, 1);
		testChinese(39532);
		testChinese(36187);
		testChinese(20811);
		keyEvent(VK_DOWN, 1);
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case 0x37:// 	����Ʒ
		keyEvent(VK_HOME, 1);
		testChinese(24037);
		testChinese(33402);
		testChinese(21697);
		keyEvent(VK_DOWN, 1);
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case 0x42:// 	����
		keyEvent(VK_HOME, 1);
		testChinese(25163);
		testChinese(38255);
		keyEvent(VK_DOWN, 1);
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case 0x47:// 	���
		keyEvent(VK_HOME, 1);
		testChinese(20116);
		testChinese(37329);
		keyEvent(VK_DOWN, 1);
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case 0x46:// 	δʶ��
		keyEvent(VK_HOME, 1);
		testChinese(26410);
		testChinese(35782);
		testChinese(21035);
		keyEvent(VK_DOWN, 1);
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case 0x53:// 	����
		keyEvent(VK_HOME, 1);
		testChinese(26679);
		testChinese(26495);
		keyEvent(VK_DOWN, 1);
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case 0x44:// 	���
		keyEvent(VK_HOME, 1);
		testChinese(37197);
		testChinese(20214);
		keyEvent(VK_DOWN, 1);
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case 0x41:// 	��Ʒ�ͺ�
		keyEvent(VK_HOME, 1);
		testChinese(29289);
		testChinese(21697);
		testChinese(22411);
		testChinese(21495);
		keyEvent(VK_DOWN, 1);
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case 0x4F:// 	����O
		keyEvent(VK_HOME, 1);
		testChinese(39033);
		testChinese(38142);
		keyEvent(VK_DOWN, 1);
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case VK_OEM_PERIOD:// 	��Ʒ
		keyEvent(VK_HOME, 1);
		testChinese(39280);
		testChinese(21697);
		keyEvent(VK_DOWN, 1);
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case VK_OEM_COMMA:// 	�����
		keyEvent(VK_HOME, 1);
		testChinese(29289);
		testChinese(21697);
		testChinese(22411);
		keyEvent(VK_DOWN, 1);
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case 0x4A:// 	�ֻ�
		keyEvent(VK_HOME, 1);
		testChinese(25163);
		testChinese(26426);
		keyEvent(VK_DOWN, 1);
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case 0x4C:// 	����
		keyEvent(VK_HOME, 1);
		testChinese(25163);
		testChinese(38142);
		keyEvent(VK_DOWN, 1);
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case 0x48:// 	�±�
		keyEvent(VK_HOME, 1);
		testChinese(26376);
		testChinese(39292);
		keyEvent(VK_DOWN, 1);
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case 0x4B:// 	ʳƷ
		keyEvent(VK_HOME, 1);
		testChinese(39135);
		testChinese(21697);
		keyEvent(VK_DOWN, 1);
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case 0x4E:// 	��Ҷ
		keyEvent(VK_HOME, 1);
		testChinese(33590);
		testChinese(21494);
		keyEvent(VK_DOWN, 1);
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case 0x4D:// 	����Ʒ
		keyEvent(VK_HOME, 1);
		testChinese(20445);
		testChinese(20581);
		testChinese(21697);
		keyEvent(VK_DOWN, 1);
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case VK_F7:// ������1��O		F7
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_UP, 1);
		// ����
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);

		keyEvent(VK_DOWN, 1);
		// ճ��
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_OEM_1:// 	ҩƷ
		keyEvent(VK_HOME, 1);
		testChinese(33647);
		testChinese(21697);
		keyEvent(VK_DOWN, 1);
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case 0x30:// 	0
		keyEvent(VK_HOME, 1);
		keyEvent(0x30, 1);
		keyEvent(VK_DOWN, 1);
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	}
	return lock;
}

BOOL KetthProjectAction::keyAction13(PKBDLLHOOKSTRUCT kbstruct, boolean lock) {
	HWND hWnd = GetFocus(); // �õ���ǰ���̹�����ڵĴ��� 
	LPRECT lParam = new RECT;
	int zuo = 0;
	int you = 0;
	int shang = 0;
	int xia = 0;
	// ���������鿴 https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx
	switch (kbstruct->vkCode) {
	case VK_SCROLL://�ر�ϵͳ
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			keyEvent(VK_RETURN, 1);
		}
		lock = false;
		break;

	case VK_ESCAPE:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_ESCAPE, 1);
		SetCursorPos(198, 685);
		lock = false;
		break;
	case VK_OEM_2:// ��   /
		keyEvent(VK_DOWN, 1);
		lock = false;
		break;
	case VK_OEM_3:// esc					For the US standard keyboard, the '`~' key
		keyEvent(VK_ESCAPE, 1);
		lock = false;
		break;
	case VK_F3:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 20;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 300; //����������,��������
			shang = shang + 200;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_F4:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 20;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 300; //����������,��������
			shang = shang + 200;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			Sleep(600);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_RETURN:// �س�
		if (switchSortCutStatus) {
			confirmSwitch();
		}
		else {
			keyEvent(VK_RETURN, 1);
		}
		lock = false;
		break;
	case VK_PRIOR:// F8			'\|' key
		keyEvent(VK_F8, 1);
		lock = false;
		break;
	case VK_F1:// F1					For the US standard keyboard, the '`~' key
		keyEvent(VK_DOWN, 1);
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case VK_F7:// ������1��O		F7
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_UP, 1);
		// ����
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);

		keyEvent(VK_DOWN, 1);
		// ճ��
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_OEM_5:// ɾ��			'\|' key
		keyEvent(VK_BACK, 1);
		lock = false;
		break;
	case VK_OEM_PERIOD://��			For any country / region, the '.' key
		keyEvent(VK_DOWN, 1);
		lock = false;
		break;
	}
	return lock;
}
//�ص�
BOOL KetthProjectAction::keyAction14(PKBDLLHOOKSTRUCT kbstruct, boolean lock) {//�ص�
	HWND hWnd = GetFocus(); // �õ���ǰ���̹�����ڵĴ��� 
	LPRECT lParam = new RECT;
	int zuo = 0;
	int you = 0;
	int shang = 0;
	int xia = 0;
	// ���������鿴 https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx
	switch (kbstruct->vkCode) {
	case VK_SCROLL://�ر�ϵͳ
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			keyEvent(VK_RETURN, 1);
		}
		lock = false;
		break;
	case VK_ESCAPE:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_ESCAPE, 1);
		SetCursorPos(198, 685);
		lock = false;
		break;
	case VK_F3:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 20;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 300; //����������,��������
			shang = shang + 200;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_F4:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 20;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 300; //����������,��������
			shang = shang + 200;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			Sleep(600);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_OEM_3:// esc					For the US standard keyboard, the '`~' key
		keyEvent(VK_ESCAPE, 1);
		lock = false;
		break;
	case VK_PRIOR:// F8			'\|' key
		keyEvent(VK_F8, 1);
		lock = false;
		break;
	case VK_OEM_COMMA:// �ĸ�region, the ',' key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_HOME, 1);
		keyEvent(0x31, 1);
		keyEvent(VK_TAB, 4);
		lock = false;
		break;
	case 0x4A:// 	J key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 5);
		lock = false;
		break;
	case 0x50://		P key
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case 0x48:// ��ȡ	0x48��H key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 8);
		keyEvent(0x31, 1);
		keyEvent(VK_LEFT, 1);
		lock = false;
		break;
	case 0x4D:// �ҵĽű�4	M
		keyEvent(VK_F6, 2);
		lock = false;
		break;
	case VK_OEM_PERIOD:// �ҵĽű�1		VK_OEM_PERIOD ��'.' key	
		keyEvent(VK_OEM_PERIOD, 1);
		keyEvent(0x35, 1);
		lock = false;
		break;
	case VK_OEM_5:// ɾ��			'\|' key
		keyEvent(VK_BACK, 1);
		lock = false;
		break;
	case VK_SPACE:// �ո�
		if (switchSortCutStatus) {
			confirmSwitch();
		}
		else {
			keyEvent(VK_RETURN, 1);
		}
		lock = false;
		break;
	case VK_RETURN:// �س�
		if (switchSortCutStatus) {
			confirmSwitch();
		}
		else {
			keyEvent(VK_RETURN, 1);
		}
		lock = false;
		break;
	case VK_F7:
		keyEvent(VK_ESCAPE, 1);
		copyUpline();
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x52://R		ǩ�ص�
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 8);
		Sleep(100);
		keyEvent(0x35, 1);
		Sleep(100);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_F8, 1);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_F1://F1		ǩ�ص�5
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keybd_event(0x32, 0, 0, 0);keybd_event(0x32, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RETURN, 2);
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		Sleep(100);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 8);
		Sleep(100);
		keyEvent(0x35, 1);
		Sleep(100);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_F8, 1);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x46:// 			F key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(50);
		keyEvent(VK_HOME, 1);
		keyEvent(0x32, 1);
		keyEvent(VK_TAB, 3);
		lock = false;
		break;
	case VK_MULTIPLY:// 			F key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(50);
		keyEvent(VK_HOME, 1);
		keyEvent(0x32, 1);
		keyEvent(VK_TAB, 3);
		lock = false;
		break;
	case VK_OEM_1:// ����		US standard keyboard, the ';:' key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(50);
		keyEvent(VK_HOME, 1);
		keyEvent(0x32, 1);
		keyEvent(VK_RETURN, 2);
		keyEvent(0x31, 1);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_ADD:// ����		С���̼Ӻ�
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_HOME, 1);
		keyEvent(0x32, 1);
		keyEvent(VK_RETURN, 2);
		keyEvent(0x31, 1);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;

	case 0x53:// 			�ĸ�S KEY
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(50);
		keyEvent(VK_HOME, 1);
		keyEvent(0x31, 1);
		keyEvent(VK_RETURN, 4);
		lock = false;
		break;
	case VK_DIVIDE:// 			/ KEY
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 7);
		Sleep(100);
		keyEvent(0x35, 1);
		Sleep(100);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_F8, 1);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x47:// 			G KEY;
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keybd_event(0x32, 0, 0, 0);keybd_event(0x32, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 3);
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x4B:// 	K key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(50);
		keyEvent(VK_DOWN, 1);
		keyEvent(0x32, 1);
		keyEvent(VK_RETURN, 2);
		keyEvent(0x31, 1);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x4C:// 			����L KEY ����
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(50);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 7);
		keyEvent(0x31, 1);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x59:// 			����Y KEY ����
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(50);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 7);
		inputText("AU");
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x5A:// 			��װZ KEY ����
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(50);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 7);
		inputText("0");
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x41:// 			A���Ի���װKEY ����
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(50);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 7);
		inputText("AY");
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_NUMPAD1:// 			A���Ի���װKEY ����
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(50);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 7);
		inputText("AA");
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_NUMPAD2:// 			A���Ի���װKEY ����
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(50);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 7);
		inputText("AE");
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x58:// 			X���շ�
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(50);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 7);
		inputText("X");
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x54:// 			T KEY 
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(50);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 7);
		inputText("K");
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x42:// ������			B key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(50);
		keyEvent(VK_HOME, 1);
		keyEvent(0x33, 1);
		keyEvent(VK_TAB, 1);
		keyEvent(0x31, 1);
		keyEvent(0x31, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 1);
		lock = false;
		break;
	case 0x4E:// ������			N key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(50);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 10);
		keyEvent(0x31, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(0x33, 1);
		lock = false;
		break;
	case VK_INSERT:// ��0
		keyEvent(VK_END, 1);
		keyEvent(0x30, 1);
		lock = false;
		break;
	case 0x45:// 		E
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(50);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 5);
		keyEvent(0x31, 1);
		keyEvent(0x33, 1);
		keyEvent(VK_DOWN, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(0x32, 1);
		keyEvent(VK_RETURN, 2);
		keyEvent(0x31, 1);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x44:// ����	0x48��D key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(50);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 7);
		keyEvent(0x32, 1);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_OEM_MINUS:// 			����ֵ
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 7);
		lock = false;
		break;
	case 0x4F:// ճ��			O key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(50);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 5);
		keyEvent(0x32, 1);
		keyEvent(0x33, 1);
		keyEvent(VK_DOWN, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(0x32, 1);
		keyEvent(VK_RETURN, 2);
		keyEvent(0x31, 1);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x51:// 			18 key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(50);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 5);
		keyEvent(0x31, 1);
		keyEvent(0x38, 1);
		keyEvent(VK_DOWN, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(0x32, 1);
		keyEvent(VK_RETURN, 2);
		keyEvent(0x31, 1);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x49:// ճ��		11	I key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(50);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 5);
		keyEvent(0x31, 1);
		keyEvent(0x31, 1);
		keyEvent(VK_DOWN, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(0x32, 1);
		keyEvent(VK_RETURN, 2);
		keyEvent(0x31, 1);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x57:// ճ��			W key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(50);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 5);
		keyEvent(0x31, 1);
		keyEvent(0x32, 1);
		keyEvent(VK_DOWN, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(0x32, 1);
		keyEvent(VK_RETURN, 2);
		keyEvent(0x31, 1);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x55:// ճ��			U key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(50);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 5);
		keyEvent(0x32, 1);
		keyEvent(0x32, 1);
		keyEvent(VK_DOWN, 1);
		keyEvent(0x32, 1);
		keyEvent(VK_RETURN, 2);
		keyEvent(0x31, 1);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_OEM_2:// For the US standard keyboard, the '/?' key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_DOWN, 1);
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case 0x43:// ����			C key
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		lock = false;
		break;
	case 0x56:// ճ��			V key
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		lock = false;
		break;
	case VK_OEM_4:// ��	
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 5);
		lock = false;
		break;
	case VK_F11://����̼Ӻ�+++++++++�ͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½�
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 200; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 120; //����������,��������
			shang = shang + 130;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(100);
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		Sleep(100);
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 260; //����������,��������
			shang = shang + 130;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_OEM_6://]]  }}}����̼�++�������  ���ǳ���
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 60;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 1220; //����������,��������
			shang = shang + 700;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	//case VK_OEM_MINUS:// 7550355168			5 KEY
	//	keyEvent(0x30, 4);
	//	lock = false;
	//	break;
	}
	return lock;
}
//�ص�����
BOOL KetthProjectAction::keyAction15(PKBDLLHOOKSTRUCT kbstruct, boolean lock) {
	HWND hWnd = GetFocus(); // �õ���ǰ���̹�����ڵĴ��� 
	LPRECT lParam = new RECT;
	int zuo = 0;
	int you = 0;
	int shang = 0;
	int xia = 0;
	// ���������鿴 https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx
	switch (kbstruct->vkCode) {
	case VK_SCROLL://�ر�ϵͳ
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			keyEvent(VK_RETURN, 1);
		}
		lock = false;
		break;
	case VK_ESCAPE:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_ESCAPE, 1);
		SetCursorPos(198, 685);
		lock = false;
		break;
	case VK_F3:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 20;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 300; //����������,��������
			shang = shang + 200;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_F4:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 20;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 300; //����������,��������
			shang = shang + 200;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			Sleep(600);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_MULTIPLY:// ������һ��
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_UP, 1);
		// ����
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);

		keyEvent(VK_DOWN, 1);
		// ճ��
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_F7:// ������һ��
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_UP, 1);
		// ����
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);

		keyEvent(VK_DOWN, 1);
		// ճ��
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_OEM_3:// esc					For the US standard keyboard, the '`~' key
		keyEvent(VK_ESCAPE, 1);
		lock = false;
		break;
	case VK_OEM_5:// ɾ��			'\|' key
		keyEvent(VK_BACK, 1);
		lock = false;
		break;
	case VK_SPACE:// �ո�
		if (switchSortCutStatus) {
			confirmSwitch();
		}
		else {
			keyEvent(VK_RETURN, 1);
		}
		lock = false;
		break;
	case VK_RETURN:// �س�
		if (switchSortCutStatus) {
			confirmSwitch();
		}
		else {
			keyEvent(VK_RETURN, 1);
		}
		lock = false;
		break;
	case 0x4D:
		keyEvent(VK_F6, 2);
		lock = false;
		break;
	case VK_PRIOR:// F8			'\|' key
		keyEvent(VK_F8, 1);
		lock = false;
		break;
	case 0x48:// 	K key
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_DOWN, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(0x32, 1);
		lock = false;
		break;
	case 0x4B:// 	H key
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_DOWN, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(0x32, 1);
		lock = false;
		break;
	case 0x58:// 	X key
		keyEvent(VK_DOWN, 1);
		keyEvent(0x32, 1);
		keyEvent(VK_HOME, 1);
		lock = false;
		break;	
	case 0x44:// 	D key
		keyEvent(VK_DOWN, 1);
		keyEvent(0x32, 1);
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case VK_OEM_2:// 	�� key
		keyEvent(VK_DOWN, 1);
		lock = false;
		break;
	case 0x53:// 	�ĸ�		S KEY
		keyEvent(VK_HOME, 1);
		keyEvent(0x31, 1);
		keyEvent(VK_RETURN, 3);
		keyEvent(0x32, 1);
		lock = false;
		break;
	case 0x57:// 			W KEY
		keyEvent(VK_UP, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(0x31, 1);
		keyEvent(VK_RETURN, 3);
		keyEvent(0x32, 1);
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case 0x55:// 			U KEY
		keyEvent(VK_UP, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(0x32, 1);
		lock = false;
		break;
	case VK_DIVIDE:// 			С����/ KEY
		keyEvent(VK_HOME, 1);
		keyEvent(0x31, 1);
		keyEvent(VK_DOWN, 1);
		keyEvent(0x32, 1);
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case 0x45:// ������			E key
		keyEvent(VK_HOME, 1);
		keyEvent(0x33, 1);
		lock = false;
		break;
	case 0x46:// 			F key
		keyEvent(VK_HOME, 1);
		keyEvent(0x32, 1);
		lock = false;
		break;
	case VK_OEM_1:// ����		US standard keyboard, the ';:' key
		keyEvent(VK_HOME, 1);
		keyEvent(0x32, 1);
		keyEvent(VK_RETURN, 3);
		keyEvent(0x32, 1);
		lock = false;
		break;
	case VK_ADD:// ����		С����+ key
		keyEvent(VK_HOME, 1);
		keyEvent(0x32, 1);
		keyEvent(VK_RETURN, 3);
		keyEvent(0x32, 1);
		lock = false;
		break;
	case 0x43:// ����			C key
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		lock = false;
		break;
	case 0x56:// ճ��			V key
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		lock = false;
		break;
	case 0x47:// GGGG			G key
		keyEvent(VK_HOME, 1);
		keyEvent(0x32, 1);
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_DOWN, 1);
		keyEvent(0x32, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x49:// 	I key
		keyEvent(VK_UP, 1);
		lock = false;
		break;
	case 0x4A:// 	J key
		keyEvent(VK_LEFT, 1);
		lock = false;
		break;
	case VK_INSERT:// ��0
		keyEvent(VK_END, 1);
		keyEvent(0x30, 1);
		lock = false;
		break;
	case VK_F11://����̼Ӻ�+++++++++�ͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½�
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 200; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 120; //����������,��������
			shang = shang + 130;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(100);
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		Sleep(100);
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 260; //����������,��������
			shang = shang + 130;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_OEM_6://]]  }}}����̼�++�������  ���ǳ���
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 60;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 1220; //����������,��������
			shang = shang + 700;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	}
	return lock;
}
BOOL KetthProjectAction::keyAction16(PKBDLLHOOKSTRUCT kbstruct, boolean lock) {
	HWND hWnd = GetFocus(); // �õ���ǰ���̹�����ڵĴ��� 
	LPRECT lParam = new RECT;
	int zuo = 0;
	int you = 0;
	int shang = 0;
	int xia = 0;
	// ���������鿴 https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx
	switch (kbstruct->vkCode) {
	case VK_SCROLL://�ر�ϵͳ
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			keyEvent(VK_RETURN, 1);
		}
		lock = false;
		break;
	case VK_ESCAPE:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��Ϣ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			keyEvent(VK_RETURN, 5);
			keyEvent(VK_ESCAPE, 10);
		}
		keyEvent(VK_ESCAPE, 10);
		SetCursorPos(198, 685);
		lock = false;
		break;

	case VK_OEM_3:// esc					For the US standard keyboard, the '`~' key
		keyEvent(VK_ESCAPE, 1);
		lock = false;
		break;
	case VK_F3:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 20;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 300; //����������,��������
			shang = shang + 200;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_F4:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 20;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 300; //����������,��������
			shang = shang + 200;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			Sleep(600);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_INSERT:// ��0
		keyEvent(VK_END, 1);
		keyEvent(0x30, 1);
		lock = false;
		break;
	case VK_OEM_1:// ����		US standard keyboard, the ';:' key
		keyEvent(VK_RETURN, 2);
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		Sleep(100);
		keyEvent(0x32, 1);
		keyEvent(VK_RETURN, 3);
		lock = false;
		break;
	case VK_OEM_COMMA://        �ĸ�
		keyEvent(VK_RETURN, 2);
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		Sleep(100);
		keyEvent(0x31, 1);
		keyEvent(0x31, 1);
		keyEvent(VK_RETURN, 2);
		lock = false;
		break;
	case VK_F2:// FFF757			F key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		Sleep(100);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RETURN, 1);
		SetCursorPos(198, 685);
		lock = false;
		break;
	case VK_OEM_PERIOD:// FFF757			F key
		keyEvent(VK_RETURN, 2);
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		Sleep(100);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RETURN, 1);
		SetCursorPos(198, 685);
		lock = false;
		break;
	case VK_OEM_2:// For the US standard keyboard, the '/?' key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_DOWN, 1);
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case VK_F7:// ������1��O		F7
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_UP, 1);
		// ����
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);

		keyEvent(VK_DOWN, 1);
		// ճ��
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_OEM_5:// ɾ��			'\|' key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_BACK, 1);
		lock = false;
		break;
	case VK_F9:// GGGG		�����½�����	F9 key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RETURN, 1);
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_ESCAPE, 1);
		SetCursorPos(198, 685);
		lock = false;
		break;
	case VK_DIVIDE:// �ĸ�
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 3);
		Sleep(100);
		keyEvent(0x31, 1);
		keyEvent(0x31, 1);
		keyEvent(VK_RETURN, 2);
		SetCursorPos(198, 685);
		lock = false;
		break;
	case VK_MULTIPLY:// С����*��
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_ADD://			����С���̼Ӻ�
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 3);
		Sleep(100);
		keyEvent(0x32, 1);
		keyEvent(VK_RETURN, 3);
		SetCursorPos(198, 685);
		lock = false;
		break;
	case VK_F1:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 16);
		keyEvent(VK_NUMPAD1, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keybd_event(0x33, 0, 0, 0);keybd_event(0x33, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_F11://����̼Ӻ�+++++++++�ͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½�
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 200; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 120; //����������,��������
			shang = shang + 130;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(100);
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		Sleep(100);
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 260; //����������,��������
			shang = shang + 130;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_OEM_4://		For any country/region, the '[' key
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_LEFT, 1);
		// ����
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		// ճ��
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x5A:
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_ESCAPE, 1);
		SetCursorPos(198, 685);
		lock = false;
		break;
	}
	return lock;
}

BOOL KetthProjectAction::keyAction17(PKBDLLHOOKSTRUCT kbstruct, boolean lock) {
	HWND hWnd = GetFocus(); // �õ���ǰ���̹�����ڵĴ��� 
	LPRECT lParam = new RECT;
	int zuo = 0;
	int you = 0;
	int shang = 0;
	int xia = 0;
	//������
	// ���������鿴 https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx
	switch (kbstruct->vkCode) {
	case VK_SCROLL://�ر�ϵͳ
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			keyEvent(VK_RETURN, 1);
		}
		lock = false;
		break;
	case VK_F8:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_ESCAPE, 1);
		SetCursorPos(198, 685);
		lock = false;
		break;
	case VK_ESCAPE:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_ESCAPE, 1);
		SetCursorPos(198, 685);
		lock = false;
		break;
	case VK_OEM_3:// esc					For the US standard keyboard, the '`~' key
		keyEvent(VK_ESCAPE, 1);
		lock = false;
		break;
	case VK_F3:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 20;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 300; //����������,��������
			shang = shang + 200;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_F4:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 20;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 300; //����������,��������
			shang = shang + 200;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			Sleep(600);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_OEM_1:// ����		US standard keyboard, the ';:' key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 12);
		keyEvent(0x32, 1);
		keyEvent(VK_RETURN, 3);
		lock = false;
		break;
	case VK_PRIOR:// F8			'\|' key
		keyEvent(VK_F8, 1);
		lock = false;
		break;
	case 0x48:// ��ȡ	0x48��H key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 23);
		keyEvent(VK_NUMPAD1, 1);
		lock = false;
		break;
	case 0x54:// �Լ�	0x54��T key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 24);
		keyEvent(VK_NUMPAD1, 1);
		lock = false;
		break;
	case 0x4D:// M			.5
		keyEvent(VK_OEM_PERIOD, 1);
		keyEvent(0x35, 1);
		lock = false;
		break;
	case VK_OEM_5:// ɾ��			'\|' key
		keyEvent(VK_BACK, 1);
		lock = false;
		break;
	case 0x58:// �ڼ�				X key�ڼ��ڼ��ڼ��ڼ��ڼ��ڼ��ڼ��ڼ��ڼ��ڼ��ڼ��ڼ��ڼ��ڼ��ڼ��ڼ��ڼ��ڼ�
		keyEvent(VK_END, 1);
		keyEvent(VK_LEFT, 1);
		keyEvent(VK_NUMPAD1, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 12);
		keyEvent(0x33, 1);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_SPACE:// �ո�
		if (switchSortCutStatus) {
			confirmSwitch();
		}
		else {
			keyEvent(VK_RETURN, 1);
		}
		lock = false;
		break;
	case VK_RETURN:// �س�
		if (switchSortCutStatus) {
			confirmSwitch();
		}
		else {
			keyEvent(VK_RETURN, 1);
		}
		lock = false;
		break;
	case 0x4B:// ��			K key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		};
		keyEvent(VK_DOWN, 1);
		lock = false;
		break;
	case VK_OEM_2:// ��			K key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		};
		keyEvent(VK_DOWN, 1);
		lock = false;
		break;
	case VK_OEM_4:// ����һ��		US standard keyboard, the '[{' key
		keyEvent(VK_LEFT, 1);
		lock = false;
		break;
	case VK_F7:// ������1��O		F7
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_UP, 1);
		// ����
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);

		keyEvent(VK_DOWN, 1);
		// ճ��
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_F9:// ����ר�ø����϶�			F9
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 12);
		copyUpTwoline();
		keyEvent(VK_RETURN, 1);
		copyUpTwoline();
		keyEvent(VK_RETURN, 1);
		copyUpTwoline();
		keyEvent(VK_RETURN, 1);
		copyUpTwoline();
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_F10:// ����ר�ø�������			F10
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 12);
		copyUpThreeline();
		keyEvent(VK_RETURN, 1);
		copyUpThreeline();
		keyEvent(VK_RETURN, 1);
		copyUpThreeline();
		keyEvent(VK_RETURN, 1);
		copyUpThreeline();
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x4A:// ������һ�й���ר	J key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 12);
		copyUpline();
		keyEvent(VK_RETURN, 1);
		copyUpline();
		keyEvent(VK_RETURN, 1);
		copyUpline();
		keyEvent(VK_RETURN, 1);
		copyUpline();
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x43:// ����			C key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		};
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		lock = false;
		break;
	case 0x56:// ճ��			V key
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		lock = false;
		break;
	case 0x42:// ������			B key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 12);
		keybd_event(0x33, 0, 0, 0);keybd_event(0x33, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x37, 0, 0, 0);keybd_event(0x37, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x35, 0, 0, 0);keybd_event(0x35, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x37, 0, 0, 0);keybd_event(0x37, 0, KEYEVENTF_KEYUP, 0);
		lock = false;
		break;
	case VK_OEM_COMMA://        �ĸ�
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 12);
		keyEvent(0x31, 1);
		keyEvent(0x31, 1);
		keyEvent(VK_RETURN, 2);
		lock = false;
		break;
	case 0x44:// �����			D key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		};
		keyEvent(VK_END, 1);
		keyEvent(VK_LEFT, 4);
		lock = false;
		break;
	case 0x4C:// ����1000			L key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		};
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 20);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x59:// ����			 Y
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		};
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 20);
		inputText("AU");
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x57:// W1212			W key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_TAB, 15);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);

		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x32, 0, 0, 0);keybd_event(0x32, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x32, 0, 0, 0);keybd_event(0x32, 0, KEYEVENTF_KEYUP, 0);
		lock = false;
		break;
	case 0x53:// S			S key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 12);

		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x4F:// O2323			O KEY
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 16);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);

		keybd_event(0x32, 0, 0, 0);keybd_event(0x32, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x33, 0, 0, 0);keybd_event(0x33, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x32, 0, 0, 0);keybd_event(0x32, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x33, 0, 0, 0);keybd_event(0x33, 0, KEYEVENTF_KEYUP, 0);
		lock = false;
		break;
	case 0x55:// U2222			U KEY
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 16);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);

		keybd_event(0x32, 0, 0, 0);keybd_event(0x32, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x32, 0, 0, 0);keybd_event(0x32, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x32, 0, 0, 0);keybd_event(0x32, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x32, 0, 0, 0);keybd_event(0x32, 0, KEYEVENTF_KEYUP, 0);
		lock = false;
		break;
	case 0x50:// P1818			P key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 16);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);

		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x38, 0, 0, 0);keybd_event(0x38, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x38, 0, 0, 0);keybd_event(0x38, 0, KEYEVENTF_KEYUP, 0);
		lock = false;
		break;
	case 0x51:// qq3030			Q key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_TAB, 16);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);

		keybd_event(0x33, 0, 0, 0);keybd_event(0x33, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x30, 0, 0, 0);keybd_event(0x30, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x33, 0, 0, 0);keybd_event(0x33, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x30, 0, 0, 0);keybd_event(0x30, 0, KEYEVENTF_KEYUP, 0);
		lock = false;
		break;
	case 0x49:// I1111	
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 16);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		lock = false;
		break;
	case 0x45:// E1313			E key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 16);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x33, 0, 0, 0);keybd_event(0x33, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x33, 0, 0, 0);keybd_event(0x33, 0, KEYEVENTF_KEYUP, 0);
		lock = false;
		break;
	case 0x47:// GGGG			G key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 12);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RETURN, 1);
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x46:// FFF757			F key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 12);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_OEM_PERIOD:// FFF757			F key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 12);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_F2:// FFF757			F key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 12);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_NUMPAD4:// 7573722214			4 key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 12);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x37, 0, 0, 0);keybd_event(0x37, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x35, 0, 0, 0);keybd_event(0x35, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x37, 0, 0, 0);keybd_event(0x37, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x33, 0, 0, 0);keybd_event(0x33, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x37, 0, 0, 0);keybd_event(0x37, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x32, 0, 0, 0);keybd_event(0x32, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x32, 0, 0, 0);keybd_event(0x32, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x32, 0, 0, 0);keybd_event(0x32, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x34, 0, 0, 0);keybd_event(0x34, 0, KEYEVENTF_KEYUP, 0);
		lock = false;
		break;
	case VK_NUMPAD7:// 7570200072			7 key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 12);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x37, 0, 0, 0);keybd_event(0x37, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x35, 0, 0, 0);keybd_event(0x35, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x37, 0, 0, 0);keybd_event(0x37, 0, KEYEVENTF_KEYUP, 0);

		keybd_event(0x30, 0, 0, 0);keybd_event(0x30, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x32, 0, 0, 0);keybd_event(0x32, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x30, 0, 0, 0);keybd_event(0x30, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x30, 0, 0, 0);keybd_event(0x30, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x30, 0, 0, 0);keybd_event(0x30, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x37, 0, 0, 0);keybd_event(0x37, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x32, 0, 0, 0);keybd_event(0x32, 0, KEYEVENTF_KEYUP, 0);
		lock = false;
		break;
	case 0x52:// R477			R KEY
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		};
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 27);

		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x34, 0, 0, 0);keybd_event(0x34, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x37, 0, 0, 0);keybd_event(0x37, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x37, 0, 0, 0);keybd_event(0x37, 0, KEYEVENTF_KEYUP, 0);
		lock = false;
		break;
	case VK_NUMPAD1:// 7573030811			1 KEY
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 12);
		keyEvent(0x33, 1);
		keyEvent(VK_RETURN, 1);

		inputText("757EF");
		keyEvent(VK_RETURN, 1);
		keyEvent(0x37, 1);
		keyEvent(0x35, 1);
		keyEvent(0x37, 1);

		keyEvent(0x33, 1);
		keyEvent(0x30, 1);
		keyEvent(0x33, 1);
		keyEvent(0x30, 1);
		keyEvent(0x38, 1);
		keyEvent(0x31, 2);
		lock = false;
		break;
	case VK_NUMPAD0:// 1 1 0.1 0.1			0 KEY
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 16);

		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);

		keybd_event(0x30, 0, 0, 0);keybd_event(0x30, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_OEM_PERIOD, 1);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x30, 0, 0, 0);keybd_event(0x30, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_OEM_PERIOD, 1);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_NUMPAD3:// 0209488053			3 KEY
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 12);
		keyEvent(0x33, 1);
		keyEvent(VK_RETURN, 1);
		inputText("020JH");
		keyEvent(VK_RETURN, 1);
		keyEvent(0x30, 1);
		keyEvent(0x32, 1);
		keyEvent(0x30, 1);
		keyEvent(0x39, 1);
		keyEvent(0x34, 1);
		keyEvent(0x38, 2);
		keyEvent(0x30, 1);
		keyEvent(0x35, 1);
		keyEvent(0x33, 1);

		lock = false;
		break;
	case VK_NUMPAD2:// 0215115383			2 KEY
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 12);
		keyEvent(0x33, 1);
		keyEvent(VK_RETURN, 1);

		inputText("021EC");
		keyEvent(VK_RETURN, 1);
		keyEvent(0x30, 1);
		keyEvent(0x32, 1);
		keyEvent(0x31, 1);
		keyEvent(0x35, 1);
		keyEvent(0x31, 2);
		keyEvent(0x35, 1);
		keyEvent(0x33, 1);
		keyEvent(0x38, 1);
		keyEvent(0x33, 1);
		lock = false;
		break;
	case VK_NUMPAD9:// 0100100299			F2 KEY
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 12);
		keyEvent(0x33, 1);
		keyEvent(VK_RETURN, 1);

		inputText("010AO");
		keyEvent(VK_RETURN, 1);
		keyEvent(0x30, 1);
		keyEvent(0x31, 1);
		keyEvent(0x30, 2);
		keyEvent(0x31, 1);

		keyEvent(0x30, 2);
		keyEvent(0x32, 1);
		keyEvent(0x39, 2);
		lock = false;
		break;
	case VK_NUMPAD6:// 7560582509			6 KEY
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 12);
		keyEvent(0x33, 1);
		keyEvent(VK_RETURN, 1);

		inputText("E756A");
		keyEvent(VK_RETURN, 1);
		keyEvent(0x37, 1);
		keyEvent(0x35, 1);
		keyEvent(0x36, 1);
		keyEvent(0x30, 1);
		keyEvent(0x35, 1);
		keyEvent(0x38, 1);
		keyEvent(0x32, 1);
		keyEvent(0x35, 1);
		keyEvent(0x30, 1);
		keyEvent(0x39, 1);
		lock = false;
		break;
	case VK_NUMPAD5:// 7550355168			5 KEY
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 12);
		keyEvent(0x33, 1);
		keyEvent(VK_RETURN, 1);

		keyEvent(0x37, 1);
		keyEvent(0x35, 1);
		inputText("5JDP");
		keyEvent(VK_RETURN, 1);
		keyEvent(0x37, 1);
		keyEvent(0x35, 1);
		keyEvent(0x35, 1);
		keyEvent(0x30, 1);
		keyEvent(0x33, 1);
		keyEvent(0x35, 1);
		keyEvent(0x35, 1);
		keyEvent(0x31, 1);
		keyEvent(0x36, 1);
		keyEvent(0x38, 1);
		lock = false;
		break;
		//case VK_OEM_MINUS:// 7550355168			5 KEY
		//	keyEvent(0x30, 4);
		//	lock = false;
		//	break;
	case VK_NUMPAD8:// 021FC			8 key
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 12);
		keyEvent(0x33, 1);
		keyEvent(VK_RETURN, 1);
		inputText("021FC");
		keyEvent(VK_RETURN, 1);
		keyEvent(0x30, 1);
		keyEvent(0x32, 1);
		keyEvent(0x31, 1);
		keyEvent(0x36, 1);
		keyEvent(0x37, 4);
		keyEvent(0x35, 1);
		keyEvent(0x38, 1);
		keyEvent(VK_TAB, 8);
		keyEvent(0x32, 1);
		keyEvent(0x35, 1);
		keyEvent(VK_DOWN, 1);
		lock = false;
		break;
	case 0x5A:// 1		�ĸ�	Z key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 12);
		keyEvent(0x31, 1);
		keyEvent(0x31, 1);
		keyEvent(VK_RETURN, 2);
		lock = false;
		break;
	case VK_F1:
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case VK_F11://����̼Ӻ�+++++++++�ͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½�
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 200; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 120; //����������,��������
			shang = shang + 130;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(100);
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		Sleep(100);
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 260; //����������,��������
			shang = shang + 130;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_OEM_6://]]  }}}����̼�++�������  ���ǳ���
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 60;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 1220; //����������,��������
			shang = shang + 700;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	}
	return lock;
}

BOOL KetthProjectAction::keyAction18(PKBDLLHOOKSTRUCT kbstruct, boolean lock) {
	HWND hWnd = GetFocus(); // �õ���ǰ���̹�����ڵĴ��� 
	LPRECT lParam = new RECT;
	int zuo = 0;
	int you = 0;
	int shang = 0;
	int xia = 0;
	// ���������鿴 https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx
	switch (kbstruct->vkCode) {
	case VK_SCROLL://�ر�ϵͳ
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			keyEvent(VK_RETURN, 1);
		}
		lock = false;
		break;
	case VK_ESCAPE:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_ESCAPE, 1);
		SetCursorPos(198, 685);
		lock = false;
		break;
	case VK_OEM_3:// esc					For the US standard keyboard, the '`~' key
		keyEvent(VK_ESCAPE, 1);
		lock = false;
		break;
	case VK_F3:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 20;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 300; //����������,��������
			shang = shang + 200;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_OEM_PERIOD:// FFF757			F key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 12);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_F4:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 20;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 300; //����������,��������
			shang = shang + 200;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			Sleep(600);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_RETURN:// �س�
		if (switchSortCutStatus) {
			confirmSwitch();
		}
		else {
			keyEvent(VK_RETURN, 1);
		}
		lock = false;
		break;
	case VK_OEM_COMMA://        �ĸ�
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 12);
		keyEvent(0x31, 1);
		keyEvent(0x31, 1);
		keyEvent(VK_RETURN, 2);
		lock = false;
		break;
	case VK_OEM_1:// ����		US standard keyboard, the ';:' key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 12);
		keyEvent(0x32, 1);
		keyEvent(VK_RETURN, 3);
		lock = false;
		break;

	case 0x5A:// 1		�ĸ�	Z key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 12);
		keyEvent(0x31, 1);
		keyEvent(0x31, 1);
		keyEvent(VK_RETURN, 2);
		lock = false;
		break;
	case VK_F2:// FFF757			F key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 12);;
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_OEM_2:// For the US standard keyboard, the '/?' key
		keyEvent(VK_DOWN, 1);
		lock = false;
		break;
	case VK_F7:// ������1��O		F7
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_UP, 1);
		// ����
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);

		keyEvent(VK_DOWN, 1);
		// ճ��
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_OEM_5:// ɾ��			'\|' key
		keyEvent(VK_BACK, 1);
		lock = false;
		break;
	case VK_OEM_4:// ���ֻ�		US standard keyboard, the '[{' key
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_LEFT, 1);
		// ����
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		// ճ��
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_INSERT:// ��0
		keyEvent(VK_END, 1);
		keyEvent(0x30, 1);
		lock = false;
		break;
	case VK_F11://����̼Ӻ�+++++++++�ͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½�
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 200; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 120; //����������,��������
			shang = shang + 130;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(100);
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		Sleep(100);
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 260; //����������,��������
			shang = shang + 130;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_OEM_6://]]  }}}����̼�++�������  ���ǳ���
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 60;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 1220; //����������,��������
			shang = shang + 700;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	}
	return lock;
}


BOOL KetthProjectAction::keyAction19(PKBDLLHOOKSTRUCT kbstruct, boolean lock) {
	HWND hWnd = GetFocus(); // �õ���ǰ���̹�����ڵĴ��� 
	LPRECT lParam = new RECT;
	int zuo = 0;
	int you = 0;
	int shang = 0;
	int xia = 0;
	// ���������鿴 https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx
	switch (kbstruct->vkCode) {
	case VK_SCROLL://�ر�ϵͳ
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			keyEvent(VK_RETURN, 1);
		}
		lock = false;
		break;
	case VK_ESCAPE:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_ESCAPE, 1);
		SetCursorPos(198, 685);
		lock = false;
		break;
	case VK_OEM_3:// esc					For the US standard keyboard, the '`~' key
		keyEvent(VK_ESCAPE, 1);
		lock = false;
		break;
	case VK_F3:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 20;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 300; //����������,��������
			shang = shang + 200;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_F4:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 20;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 300; //����������,��������
			shang = shang + 200;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			Sleep(600);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_F2:// FFF757			F key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_RETURN:// �س�
		if (switchSortCutStatus) {
			confirmSwitch();
		}
		else {
			keyEvent(VK_RETURN, 1);
		}
		lock = false;
		break;
	case VK_PRIOR:// ɾ��			'\|' key
		keyEvent(VK_F8, 1);
		lock = false;
		break;
	case 0x5A:// 		�ĸ�	Z key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 3);
		keyEvent(0x31, 1);
		keyEvent(0x31, 1);
		keyEvent(VK_RETURN, 2);
		lock = false;
		break;
	case VK_ADD:// ����		US standard keyboard, the '+' key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 3);
		keyEvent(0x32, 1);
		keyEvent(VK_RETURN, 3);
		lock = false;
		break;
	case VK_NEXT:// ������1��O		PGDN
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_UP, 1);
		// ����
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);

		keyEvent(VK_DOWN, 1);
		// ճ��
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_OEM_5:// ɾ��			'\|' key
		keyEvent(VK_BACK, 1);
		lock = false;
		break;
	case VK_OEM_4://        [{' key
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case VK_F1:// F1					For the US standard keyboard, the '`~' key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		lock = false;
		break;
	case VK_DIVIDE:// �ĸ�
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 3);
		keyEvent(0x31, 1);
		keyEvent(0x31, 1);
		keyEvent(VK_RETURN, 2);
		lock = false;
		break;
	case VK_MULTIPLY:// С����*��
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_OEM_1:// 			����; key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 3);
		keyEvent(0x32, 1);
		keyEvent(VK_RETURN, 3);
		lock = false;
		break;
	case VK_OEM_COMMA:// 			; key
		keyEvent(VK_SPACE, 1);
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		lock = false;
		break;
	case VK_F11://����̼Ӻ�+++++++++�ͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½�
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 200; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 120; //����������,��������
			shang = shang + 130;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(100);
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		Sleep(100);
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 260; //����������,��������
			shang = shang + 130;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_OEM_6://]]  }}}����̼�++�������  ���ǳ���
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 60;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 1220; //����������,��������
			shang = shang + 700;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	}
	return lock;
}
//����Ũ��
BOOL KetthProjectAction::keyAction20(PKBDLLHOOKSTRUCT kbstruct, boolean lock) {
	HWND hWnd = GetFocus(); // �õ���ǰ���̹�����ڵĴ��� 
	LPRECT lParam = new RECT;
	int zuo = 0;
	int you = 0;
	int shang = 0;
	int xia = 0;
	// ���������鿴 https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx
	switch (kbstruct->vkCode) {
	case VK_SCROLL://�ر�ϵͳ
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			keyEvent(VK_RETURN, 1);
		}
		lock = false;
		break;
	case VK_F8:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_ESCAPE, 1);
		SetCursorPos(198, 685);
		lock = false;
		break;
	case VK_ESCAPE:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_ESCAPE, 1);
		SetCursorPos(198, 685);
		lock = false;
		break;
	case VK_OEM_3:// esc					For the US standard keyboard, the '`~' key
		keyEvent(VK_ESCAPE, 1);
		lock = false;
		break;
	case VK_F3:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 20;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 300; //����������,��������
			shang = shang + 200;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_F4:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 20;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 300; //����������,��������
			shang = shang + 200;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			Sleep(600);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case 0x41:// 1		�ĸ�	A key
			hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
			if (hWnd != NULL) {
				::GetWindowRect(hWnd, lParam);
				//int zuo = lParam->left;
				you = lParam->right;
				shang = lParam->top;
				//int xia = lParam->bottom;
				you = you - 20; //����������,��������
				shang = shang + 10;//��������,��������
				SetCursorPos(you, shang);
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			}
			keyEvent(VK_RETURN, 1);
			keyEvent(VK_ESCAPE, 1);
			keyEvent(VK_HOME, 1);
			keyEvent(VK_TAB, 3);
			keyEvent(0x31, 1);
			keyEvent(0x31, 1);
			keyEvent(VK_RETURN, 2);
			SetCursorPos(198, 685);
		lock = false;
		break;
	case VK_PRIOR:// ɾ��			'\|' key
		keyEvent(VK_F8, 1);
		lock = false;
		break;

	case 0x5A:// 1		�ĸ�	Z key
			hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
			if (hWnd != NULL) {
				::GetWindowRect(hWnd, lParam);
				//int zuo = lParam->left;
				you = lParam->right;
				shang = lParam->top;
				//int xia = lParam->bottom;
				you = you - 20; //����������,��������
				shang = shang + 10;//��������,��������
				SetCursorPos(you, shang);
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			}
			keyEvent(VK_RETURN, 1);
			keyEvent(VK_ESCAPE, 1);
			keyEvent(VK_HOME, 1);
			keyEvent(VK_TAB, 3);
			keyEvent(0x31, 1);
			keyEvent(0x31, 1);
			keyEvent(VK_RETURN, 2);
			SetCursorPos(198, 685);
		lock = false;
		break;
	case 0x54:// T				000
		keyEvent(0x30, 1);
		lock = false;
		break;
	case 0x52:// ��ȡ	0x48��R key
			keyEvent(VK_RETURN, 1);
			keyEvent(VK_ESCAPE, 1);
			keyEvent(VK_HOME, 1);
			keyEvent(VK_TAB, 12);
			keyEvent(VK_NUMPAD1, 1);
			keyEvent(VK_LEFT, 1);
		lock = false;
		break;
	case 0x59:// �Լ�	0x54��Y key
			keyEvent(VK_RETURN, 1);
			keyEvent(VK_ESCAPE, 1);
			keyEvent(VK_HOME, 1);
			keyEvent(VK_TAB, 13);
			keyEvent(VK_NUMPAD1, 1);
			keyEvent(VK_LEFT, 1);
		lock = false;
		break;
	case VK_OEM_5:// ɾ��			'\|' key
		keyEvent(VK_BACK, 1);
		lock = false;
		break;
	case 0x48:// �ڼ�				H key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 16);
		keyEvent(VK_NUMPAD1, 1);
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case VK_SPACE:// �ո�
		if (switchSortCutStatus) {
			confirmSwitch();
		}
		else {
			keyEvent(VK_RETURN, 1);
		}
		lock = false;
		break;
	case VK_RETURN:// �س�
		if (switchSortCutStatus) {
			confirmSwitch();
		}
		else {
			keyEvent(VK_RETURN, 1);
		}
		lock = false;
		break;
	case 0x44:// ��			D key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_DOWN, 1);
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case VK_OEM_4:// ����һ��		US standard keyboard, the '[{' key
		keyEvent(VK_LEFT, 1);
		lock = false;
		break;
	case VK_F7:// ������1��O		F7
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_UP, 1);
		// ����
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);

		keyEvent(VK_DOWN, 1);
		// ճ��
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_F9:// ����ר�ø����϶�			F9
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		copyUpTwoline();
		keyEvent(VK_RETURN, 1);
		copyUpTwoline();
		keyEvent(VK_RETURN, 1);
		copyUpTwoline();
		keyEvent(VK_RETURN, 1);
		copyUpTwoline();
		keyEvent(VK_RETURN, 1);
		copyUpTwoline();
		keyEvent(VK_RETURN, 1);
		copyUpTwoline();
		keyEvent(VK_RETURN, 1);
		copyUpTwoline();
		keyEvent(VK_RETURN, 1);
		copyUpTwoline();
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_F10:// ����ר�ø�������			F10
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		copyUpThreeline();
		keyEvent(VK_RETURN, 1);
		copyUpThreeline();
		keyEvent(VK_RETURN, 1);
		copyUpThreeline();
		keyEvent(VK_RETURN, 1);
		copyUpThreeline();
		keyEvent(VK_RETURN, 1);
		copyUpThreeline();
		keyEvent(VK_RETURN, 1);
		copyUpThreeline();
		keyEvent(VK_RETURN, 1);
		copyUpThreeline();
		keyEvent(VK_RETURN, 1);
		copyUpThreeline();
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x4A:// ������һ�й���ר	J key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		copyUpline();
		keyEvent(VK_RETURN, 1);
		copyUpline();
		keyEvent(VK_RETURN, 1);
		copyUpline();
		keyEvent(VK_RETURN, 1);
		copyUpline();
		keyEvent(VK_RETURN, 1);
		copyUpline();
		keyEvent(VK_RETURN, 1);
		copyUpline();
		keyEvent(VK_RETURN, 1);
		copyUpline();
		keyEvent(VK_RETURN, 1);
		copyUpline();
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x43:// ����			C key
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		lock = false;
		break;
	case 0x56:// ճ��			V key
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		lock = false;
		break;
	case 0x45:// ������			E key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keybd_event(0x33, 0, 0, 0);keybd_event(0x33, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_ADD:// ����		US standard keyboard, the '+' key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 3);
		keyEvent(0x32, 1);
		keyEvent(VK_RETURN, 3);
		SetCursorPos(198, 685);
		lock = false;
		break;
	case VK_OEM_1:// ����		US standard keyboard, the '+' key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 3);
		keyEvent(0x32, 1);
		keyEvent(VK_RETURN, 3);
		SetCursorPos(198, 685);
		lock = false;
		break;
	case 0x4E:// �����			N key
		keyEvent(VK_RETURN, 1);
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		};
		Sleep(69);
		keyEvent(VK_END, 1);
		keyEvent(VK_LEFT, 1);
		keyEvent(VK_LEFT, 1);
		lock = false;
		break;
	case 0x51:// ����			Q key
		if (mutiKey[2] == 0) { //�����л�
			hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
			if (hWnd != NULL) {
				::GetWindowRect(hWnd, lParam);
				//int zuo = lParam->left;
				you = lParam->right;
				shang = lParam->top;
				//int xia = lParam->bottom;
				you = you - 20; //����������,��������
				shang = shang + 10;//��������,��������
				SetCursorPos(you, shang);
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			}
			keyEvent(VK_RETURN, 1);
			keyEvent(VK_HOME, 1);
			keyEvent(VK_RETURN, 1);
			keyEvent(VK_TAB, 10);
			keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
			keyEvent(VK_RETURN, 1);
			SetCursorPos(198, 685);
			mutiKey[2] = 1;  //�л����ڶ�������
		}
		else {
			hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
			if (hWnd != NULL) {
				::GetWindowRect(hWnd, lParam);
				//int zuo = lParam->left;
				you = lParam->right;
				shang = lParam->top;
				//int xia = lParam->bottom;
				you = you - 20; //����������,��������
				shang = shang + 10;//��������,��������
				SetCursorPos(you, shang);
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			}
			keyEvent(VK_RETURN, 1);
			keyEvent(VK_HOME, 1);
			keyEvent(VK_RIGHT, 11);
			inputText("0");
			keyEvent(VK_RETURN, 1);
			SetCursorPos(198, 685);
			mutiKey[2] = 0;   //�л��ص�һ������
		}
		lock = false;
		break;
	case 0x42:// ��װ			B key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(69);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_TAB, 10);
		keyEvent(0x30, 1);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x55:// ����  U
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(69);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RIGHT, 10);
		inputText("AU");
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_MULTIPLY:// ����  U
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(69);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RIGHT, 10);
		inputText("AU");
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x4C:// ���԰�װ  L
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(69);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RIGHT, 10);
		inputText("AY");
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_DIVIDE:// ���� N
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(69);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RIGHT, 10);
		inputText("AA");
		keyEvent(VK_RETURN, 1);
		Sleep(200);
		lock = false;
		break;
	case VK_INSERT:// AU����			INS
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(69);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RIGHT, 8);

		keybd_event(VK_CAPITAL, 0, 0, 0);
		keybd_event(0x41, 0, 0, 0);keybd_event(0x41, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x55, 0, 0, 0);keybd_event(0x55, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CAPITAL, 0, KEYEVENTF_KEYUP, 0);

		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x57:// W1212			W key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_TAB, 6);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);

		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x32, 0, 0, 0);keybd_event(0x32, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x32, 0, 0, 0);keybd_event(0x32, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_DOWN, 1);
		lock = false;
		break;
	case 0x49:// 13			I key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_TAB, 6);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);

		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x36, 0, 0, 0);keybd_event(0x33, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x36, 0, 0, 0);keybd_event(0x33, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_DOWN, 1);
		lock = false;
		break;
	case 0x53:// O2323			S KEY
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}

		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_TAB, 6);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);

		keybd_event(0x32, 0, 0, 0);keybd_event(0x32, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x33, 0, 0, 0);keybd_event(0x33, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x32, 0, 0, 0);keybd_event(0x32, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x33, 0, 0, 0);keybd_event(0x33, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_DOWN, 1);
		lock = false;
		break;
	case 0x50:// 1818			P key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_TAB, 6);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x38, 0, 0, 0);keybd_event(0x38, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x38, 0, 0, 0);keybd_event(0x38, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_DOWN, 1);
		lock = false;
		break;
	case 0x58:// 22			X key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_TAB, 6);
		keyEvent(0x31, 1);
		keyEvent(VK_RETURN, 2);
		keyEvent(0x32, 1);
		keyEvent(0x32, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(0x32, 1);
		keyEvent(0x32, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_DOWN, 1);
		lock = false;
		break;
	case 0x4F:// O111			O key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_TAB, 6);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_DOWN, 1);
		lock = false;
		break;

	case 0x47:// GGGG			G key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RETURN, 1);
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x46:// FFF757			F key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_F2:// FFF757			F key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x4D:// R477			R KEY
		if (mutiKey[2] == 0) { //�����л�
			hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
			if (hWnd != NULL) {
				::GetWindowRect(hWnd, lParam);
				//int zuo = lParam->left;
				you = lParam->right;
				shang = lParam->top;
				//int xia = lParam->bottom;
				you = you - 20; //����������,��������
				shang = shang + 10;//��������,��������
				SetCursorPos(you, shang);
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			};
			keyEvent(VK_RETURN, 1);
			keyEvent(VK_ESCAPE, 1);
			Sleep(100);
			keyEvent(VK_HOME, 1);
			keyEvent(VK_TAB, 17);
			keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
			keybd_event(0x34, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
			keybd_event(0x37, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
			keybd_event(0x37, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
			mutiKey[2] = 1;  //�л����ڶ�������
		}
		else {
			keyEvent(VK_ESCAPE, 1);
			keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
			keybd_event(0x32, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
			keybd_event(0x33, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
			mutiKey[2] = 0;   //�л��ص�һ������
		}
		lock = false;
		break;
	case VK_F1:// F1					For the US standard keyboard, the '`~' key
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case VK_F11://����̼Ӻ�+++++++++�ͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½�
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 200; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 120; //����������,��������
			shang = shang + 130;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(100);
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		Sleep(100);
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 260; //����������,��������
			shang = shang + 130;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_F12:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_F8, 1);
		SetCursorPos(198, 685);
		lock = false;
		break;
	case VK_OEM_6://]]  }}}����̼�++�������  ���ǳ���
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 60;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 1220; //����������,��������
			shang = shang + 700;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	}
	return lock;
}
//�������ڼ�
BOOL KetthProjectAction::keyAction21(PKBDLLHOOKSTRUCT kbstruct, boolean lock) {
	HWND hWnd = GetFocus(); // �õ���ǰ���̹�����ڵĴ��� 
	LPRECT lParam = new RECT;
	int zuo = 0;
	int you = 0;
	int shang = 0;
	int xia = 0;
	// ���������鿴 https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx
	switch (kbstruct->vkCode) {
	case VK_SCROLL://�ر�ϵͳ
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			keyEvent(VK_RETURN, 1);
		}
		lock = false;
		break;
	case VK_F8:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_ESCAPE, 1);
		SetCursorPos(198, 685);
		lock = false;
		break;
	case VK_OEM_3:// esc					For the US standard keyboard, the '`~' key
		keyEvent(VK_ESCAPE, 1);
		lock = false;
		break;
	case VK_ESCAPE:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_ESCAPE, 1);
		SetCursorPos(198, 685);
		lock = false;
		break;
	case VK_F3:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 20;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 300; //����������,��������
			shang = shang + 200;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_F4:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 20;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 300; //����������,��������
			shang = shang + 200;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			Sleep(600);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_RETURN:// �س�
		if (switchSortCutStatus) {
			confirmSwitch();
		}
		else {
			keyEvent(VK_RETURN, 1);
		}
		lock = false;
		break;
	case VK_PRIOR:// F8			'\|' key
		keyEvent(VK_F8, 1);
		lock = false;
		break;

	case VK_OEM_5:// ɾ��			'\|' key
		keyEvent(VK_BACK, 1);
		lock = false;
		break;
	case 0x38:// 7574640798			8 key
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keyEvent(0x33, 1);
		keyEvent(VK_RETURN, 1);
		inputText("757BH");
		keyEvent(VK_RETURN, 1);
		inputText("7574640798");
		lock = false;
		break;
	case 0x34:// 7575448344			4 key
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keyEvent(0x33, 1);
		keyEvent(VK_RETURN, 1);
		inputText("757BJ");
		keyEvent(VK_RETURN, 1);
		inputText("7575448344");
		lock = false;
		break;
	case 0x39:// 7575685299			9 key
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keyEvent(0x33, 1);
		keyEvent(VK_RETURN, 1);
		inputText("757BH");
		keyEvent(VK_RETURN, 1);
		inputText("7575685299");
		lock = false;
		break;
	case 0x48:// 7572002161			H key
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keyEvent(0x33, 1);
		keyEvent(VK_RETURN, 1);
		inputText("757BH");
		keyEvent(VK_RETURN, 1);
		inputText("7572002161");
		lock = false;
		break;
	case 0x32:// 7574524412			2 key
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keyEvent(0x33, 1);
		keyEvent(VK_RETURN, 1);
		inputText("757BK");
		keyEvent(VK_RETURN, 1);
		inputText("7574524412");
		lock = false;
		break;
	case 0x4B:// 7573120325			K key
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keyEvent(0x33, 1);
		keyEvent(VK_RETURN, 1);
		inputText("757BK");
		keyEvent(VK_RETURN, 1);
		inputText("7573120325");
		lock = false;
		break;
	case 0x41:// 7571223338			A key
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keyEvent(0x33, 1);
		keyEvent(VK_RETURN, 1);
		inputText("757BA");
		keyEvent(VK_RETURN, 1);
		inputText("7571223338");
		lock = false;
		break;

	case 0x4A:// 7571535069			J key
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keyEvent(0x33, 1);
		keyEvent(VK_RETURN, 1);
		inputText("757BJ");
		keyEvent(VK_RETURN, 1);
		inputText("7571535069");
		lock = false;
		break;
	case 0x45:// 0210370765			E key
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keyEvent(0x33, 1);
		keyEvent(VK_RETURN, 1);
		inputText("021KKE");
		keyEvent(VK_RETURN, 1);
		inputText("0210370765");
		lock = false;
		break;
	case 0x4E:// 7572108311		N key
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keyEvent(0x33, 1);
		keyEvent(VK_RETURN, 1);
		inputText("757BN");
		keyEvent(VK_RETURN, 1);
		inputText("7572108311");
		lock = false;
		break;
	case 0x47:// 7573301858		G key
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keyEvent(0x33, 1);
		keyEvent(VK_RETURN, 1);
		inputText("757BG");
		keyEvent(VK_RETURN, 1);
		inputText("7573301858");
		lock = false;
		break;
	case 0x46:// 7575584616		F key
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keyEvent(0x33, 1);
		keyEvent(VK_RETURN, 1);
		inputText("757BF");
		keyEvent(VK_RETURN, 1);
		inputText("7575584616");
		lock = false;
		break;
	case 0x4C:// 7573616720		Lkey
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keyEvent(0x33, 1);
		keyEvent(VK_RETURN, 1);
		inputText("757BL");
		keyEvent(VK_RETURN, 1);
		inputText("7573616720");
		lock = false;
		break;
	case VK_NUMPAD4:// 7574123294		С����4key
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keyEvent(0x33, 1);
		keyEvent(VK_RETURN, 1);
		inputText("757BF");
		keyEvent(VK_RETURN, 1);
		inputText("7574123294");
		lock = false;
		break;
	case 0x31:// 7573594371		1key
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keyEvent(0x33, 1);
		keyEvent(VK_RETURN, 1);
		inputText("757BG");
		keyEvent(VK_RETURN, 1);
		inputText("7573594371");
		lock = false;
		break;
	case VK_NUMPAD8:// 7574403398		С����8key
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keyEvent(0x33, 1);
		keyEvent(VK_RETURN, 1);
		inputText("757BH");
		keyEvent(VK_RETURN, 1);
		inputText("7574403398");
		lock = false;
		break;
	case VK_NUMPAD9:// 7571868509		С����9key
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keyEvent(0x33, 1);
		keyEvent(VK_RETURN, 1);
		inputText("757BK");
		keyEvent(VK_RETURN, 1);
		inputText("7571868509");
		lock = false;
		break;
	case 0x44:// 7571120097		Dkey
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keyEvent(0x33, 1);
		keyEvent(VK_RETURN, 1);
		inputText("757BD");
		keyEvent(VK_RETURN, 1);
		inputText("7571120097");
		lock = false;
		break;
	case VK_NUMPAD1:// 0205655381		С����1key
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keyEvent(0x33, 1);
		keyEvent(VK_RETURN, 1);
		inputText("020JN");
		keyEvent(VK_RETURN, 1);
		inputText("0205655381");
		lock = false;
		break;
	case 0x4D:// 7571112445		Mkey
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keyEvent(0x33, 1);
		keyEvent(VK_RETURN, 1);
		inputText("757BM");
		keyEvent(VK_RETURN, 1);
		inputText("7573868081");
		lock = false;
		break;
	case 0x51:// 7574048059		Qkey
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keyEvent(0x33, 1);
		keyEvent(VK_RETURN, 1);
		inputText("757BQ");
		keyEvent(VK_RETURN, 1);
		inputText("7575835859");
		lock = false;
		break;
	case VK_F1:
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case VK_F11://����̼Ӻ�+++++++++�ͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½�
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 200; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 120; //����������,��������
			shang = shang + 130;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(100);
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		Sleep(100);
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 260; //����������,��������
			shang = shang + 130;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_OEM_6://]]  }}}����̼�++�������  ���ǳ���
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 60;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 1220; //����������,��������
			shang = shang + 700;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	}
	return lock;
}
//�����ǵ������½�ķ��ӷ���
BOOL KetthProjectAction::keyAction22(PKBDLLHOOKSTRUCT kbstruct, boolean lock) {
	HWND hWnd = GetFocus(); // �õ���ǰ���̹�����ڵĴ��� 
	LPRECT lParam = new RECT;
	int zuo = 0;
	int you = 0;
	int shang = 0;
	int xia = 0;
	// ���������鿴 https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx
	switch (kbstruct->vkCode) {
	case VK_SCROLL://�ر�ϵͳ
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			keyEvent(VK_RETURN, 1);
		}
		lock = false;
		break;
	case VK_F8:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_ESCAPE, 1);
		SetCursorPos(198, 685);
		lock = false;
		break;
	case VK_OEM_3:// esc					For the US standard keyboard, the '`~' key
		keyEvent(VK_ESCAPE, 1);
		lock = false;
		break;
	case VK_ESCAPE:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_ESCAPE, 1);
		SetCursorPos(198, 685);
		lock = false;
		break;
	case VK_F3:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 20;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 300; //����������,��������
			shang = shang + 200;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_F4:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 20;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 300; //����������,��������
			shang = shang + 200;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			Sleep(600);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case 0x39:// 0100100299		
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keyEvent(0x33, 1);
		keyEvent(VK_RETURN, 1);

		inputText("010AO");
		keyEvent(VK_RETURN, 1);
		keyEvent(0x30, 1);
		keyEvent(0x31, 1);
		keyEvent(0x30, 2);
		keyEvent(0x31, 1);

		keyEvent(0x30, 2);
		keyEvent(0x32, 1);
		keyEvent(0x39, 2);
		lock = false;
		break;
	case 0x46:// 021FC			F key
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keyEvent(0x33, 1);
		keyEvent(VK_RETURN, 1);
		inputText("021FC");
		keyEvent(VK_RETURN, 1);
		keyEvent(0x30, 1);
		keyEvent(0x32, 1);
		keyEvent(0x31, 1);
		keyEvent(0x36, 1);
		keyEvent(0x37, 4);
		keyEvent(0x35, 1);
		keyEvent(0x38, 1);
		lock = false;
		break;
	case 0x38:// 7550355168			8 KEY
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keyEvent(0x33, 1);
		keyEvent(VK_RETURN, 1);
		inputText("755CEE");
		keyEvent(VK_RETURN, 1);
		inputText("7550355168");
		lock = false;
		break;
	case 0x41:// 7560582509			A KEY
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keyEvent(0x33, 1);
		keyEvent(VK_RETURN, 1);

		inputText("756AEE");
		keyEvent(VK_RETURN, 1);
		keyEvent(0x37, 1);
		keyEvent(0x35, 1);
		keyEvent(0x36, 1);
		keyEvent(0x30, 1);
		keyEvent(0x35, 1);
		keyEvent(0x38, 1);
		keyEvent(0x32, 1);
		keyEvent(0x35, 1);
		keyEvent(0x30, 1);
		keyEvent(0x39, 1);
		lock = false;
		break;
	case 0x31:// 7573030811			1 KEY
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 3);
		keyEvent(0x33, 1);
		keyEvent(VK_RETURN, 1);

		inputText("757EF");
		keyEvent(VK_RETURN, 1);
		keyEvent(0x37, 1);
		keyEvent(0x35, 1);
		keyEvent(0x37, 1);
		keyEvent(0x33, 1);
		keyEvent(0x30, 1);
		keyEvent(0x33, 1);
		keyEvent(0x30, 1);
		keyEvent(0x38, 1);
		keyEvent(0x31, 2);
		lock = false;
		break;
	case 0x30:// 1 1 0.1 0.1			0 KEY
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 7);

		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);

		keybd_event(0x30, 0, 0, 0);keybd_event(0x30, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_OEM_PERIOD, 1);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x30, 0, 0, 0);keybd_event(0x30, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_OEM_PERIOD, 1);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x33:// 0209488053			3 KEY
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keyEvent(0x33, 1);
		keyEvent(VK_RETURN, 1);

		inputText("020JH");
		keyEvent(VK_RETURN, 1);
		keyEvent(0x30, 1);
		keyEvent(0x32, 1);
		keyEvent(0x30, 1);
		keyEvent(0x39, 1);
		keyEvent(0x34, 1);
		keyEvent(0x38, 2);
		keyEvent(0x30, 1);
		keyEvent(0x35, 1);
		keyEvent(0x33, 1);

		lock = false;
		break;
	case 0x45:// 0215115383			E KEY
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keyEvent(0x33, 1);
		keyEvent(VK_RETURN, 1);
		inputText("021EC");
		keyEvent(VK_RETURN, 1);
		keyEvent(0x30, 1);
		keyEvent(0x32, 1);
		keyEvent(0x31, 1);
		keyEvent(0x35, 1);
		keyEvent(0x31, 2);
		keyEvent(0x35, 1);
		keyEvent(0x33, 1);
		keyEvent(0x38, 1);
		keyEvent(0x33, 1);
		lock = false;
		break;
	case 0x34:// 7573722214			4 key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RETURN, 1);
		inputText("7573722214");
		lock = false;
		break;
	case 0x35:// 0210370765			5 key
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keyEvent(0x33, 1);
		keyEvent(VK_RETURN, 1);
		inputText("021KKE");
		keyEvent(VK_RETURN, 1);
		inputText("0210370765");
		lock = false;
		break;
	case 0x51:// 7693066831			Q key
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keyEvent(0x33, 1);
		keyEvent(VK_RETURN, 1);
		inputText("769AQ");
		keyEvent(VK_RETURN, 1);
		inputText("7693066831");
		lock = false;
		break;
	case 0x43:// 0215671323			C key
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keyEvent(0x33, 1);
		keyEvent(VK_RETURN, 1);
		inputText("021CD");
		keyEvent(VK_RETURN, 1);
		inputText("0215671323");
		lock = false;
		break;
	case 0x36:// 0212454066			C key
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keyEvent(0x33, 1);
		keyEvent(VK_RETURN, 1);
		inputText("021CF");
		keyEvent(VK_RETURN, 1);
		inputText("0212454066");
		lock = false;
		break;
	case 0x54:// 0251101628			T key
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keyEvent(0x33, 1);
		keyEvent(VK_RETURN, 1);
		inputText("025TM");
		keyEvent(VK_RETURN, 1);
		inputText("0251101628");
		lock = false;
		break;
	case 0x32:// 7570200072			7 key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x37, 0, 0, 0);keybd_event(0x37, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x35, 0, 0, 0);keybd_event(0x35, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x37, 0, 0, 0);keybd_event(0x37, 0, KEYEVENTF_KEYUP, 0);

		keybd_event(0x30, 0, 0, 0);keybd_event(0x30, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x32, 0, 0, 0);keybd_event(0x32, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x30, 0, 0, 0);keybd_event(0x30, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x30, 0, 0, 0);keybd_event(0x30, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x30, 0, 0, 0);keybd_event(0x30, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x37, 0, 0, 0);keybd_event(0x37, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x32, 0, 0, 0);keybd_event(0x32, 0, KEYEVENTF_KEYUP, 0);
		lock = false;
		break;
	case 0x42:// 7570510866			B key
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keyEvent(0x33, 1);
		keyEvent(VK_RETURN, 1);
		inputText("757FB");
		keyEvent(VK_RETURN, 1);
		inputText("7570510866");
		lock = false;
		break;
	case VK_NUMPAD3:// 0211587923			С����3key
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keyEvent(0x33, 1);
		keyEvent(VK_RETURN, 1);
		inputText("021DD");
		keyEvent(VK_RETURN, 1);
		inputText("0211587923");
		lock = false;
		break;
	case 0x4A:// 7574454593			J key
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keyEvent(0x33, 1);
		keyEvent(VK_RETURN, 1);
		inputText("757AJ");
		keyEvent(VK_RETURN, 1);
		inputText("7574454593");
		lock = false;
		break;
	case VK_F2:// 7573705112		F2 key
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keyEvent(0x33, 1);
		keyEvent(VK_RETURN, 1);
		inputText("757BJ");
		keyEvent(VK_RETURN, 1);
		inputText("7573705112");
		lock = false;
		break;
	case VK_NUMPAD0:// 7571137720		С����0 key
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keyEvent(0x33, 1);
		keyEvent(VK_RETURN, 1);
		inputText("758BA");
		keyEvent(VK_RETURN, 1);
		inputText("7571137720");
		lock = false;
		break;
	case VK_NUMPAD9:// 7554408499		С����9 key
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keyEvent(0x33, 1);
		keyEvent(VK_RETURN, 1);
		inputText("755AR");
		keyEvent(VK_RETURN, 1);
		inputText("7554408499");
		lock = false;
		break;
	case 0x4B:// 7571123848		K key
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keyEvent(0x33, 1);
		keyEvent(VK_RETURN, 1);
		inputText("757BK");
		keyEvent(VK_RETURN, 1);
		inputText("7571123848");
		lock = false;
		break;
	case 0x56:// 7571124649		 V key
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keyEvent(0x33, 1);
		keyEvent(VK_RETURN, 1);
		inputText("757VA");
		keyEvent(VK_RETURN, 1);
		inputText("7571124649");
		lock = false;
		break;
	case VK_NUMPAD6:// 7570510866		С����6 key
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keyEvent(0x33, 1);
		keyEvent(VK_RETURN, 1);
		inputText("757FB");
		keyEvent(VK_RETURN, 1);
		inputText("7570510866");
		lock = false;
		break;
	case VK_F6:// 7556820816		F6 key
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keyEvent(0x33, 1);
		keyEvent(VK_RETURN, 1);
		inputText("755BEE");
		keyEvent(VK_RETURN, 1);
		inputText("7556820816");
		lock = false;
		break;
	case VK_NUMPAD1:// 0205655381		С����1key
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keyEvent(0x33, 1);
		keyEvent(VK_RETURN, 1);
		inputText("020JN");
		keyEvent(VK_RETURN, 1);
		inputText("0205655381");
		lock = false;
		break;
	case 0x48:// 757BH	С����H key
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keyEvent(0x33, 1);
		keyEvent(VK_RETURN, 1);
		inputText("757BH");
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x4D:// 757BM	С����M key
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keyEvent(0x33, 1);
		keyEvent(VK_RETURN, 1);
		inputText("757BM");
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x44:// 757BD	С����D key
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keyEvent(0x33, 1);
		keyEvent(VK_RETURN, 1);
		inputText("757BD");
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_NUMPAD2:// 7573397312			5 key
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keyEvent(0x33, 1);
		keyEvent(VK_RETURN, 1);
		inputText("757AA");
		keyEvent(VK_RETURN, 1);
		inputText("7573397312");
		lock = false;
		break;
	case VK_F1:
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case VK_F11://����̼Ӻ�+++++++++�ͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½�
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 200; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 120; //����������,��������
			shang = shang + 130;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(100);
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		Sleep(100);
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 260; //����������,��������
			shang = shang + 130;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_OEM_6://]]  }}}����̼�++�������  ���ǳ���
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 60;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 1220; //����������,��������
			shang = shang + 700;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;

	}
	return lock;
}
//���������õĸ�������
BOOL KetthProjectAction::keyAction23(PKBDLLHOOKSTRUCT kbstruct, boolean lock) {
	HWND hWnd = GetFocus(); // �õ���ǰ���̹�����ڵĴ��� 
	LPRECT lParam = new RECT;
	int zuo = 0;
	int you = 0;
	int shang = 0;
	int xia = 0;
	// ���������鿴 https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx
	switch (kbstruct->vkCode) {
	case VK_ESCAPE:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��Ϣ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			keyEvent(VK_RETURN, 5);
			keyEvent(VK_ESCAPE, 10);
		}
		keyEvent(VK_ESCAPE, 10);
		SetCursorPos(198, 685);
		lock = false;
		break;

	case VK_OEM_3:// �ĸ�				For the US standard keyboard, the '`~' key
		keyEvent(VK_RETURN, 2);
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		Sleep(100);
		keyEvent(0x31, 1);
		keyEvent(0x31, 1);
		keyEvent(VK_RETURN, 2);
		lock = false;
		break;
	case VK_F3:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 20;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 300; //����������,��������
			shang = shang + 200;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_F4:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 20;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 300; //����������,��������
			shang = shang + 200;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			Sleep(600);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_ADD://��
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_DOWN, 1);
		keyEvent(VK_HOME, 1);
		SetCursorPos(198, 685);
		lock = false;
		break;
	case VK_TAB:// �س�// ���ڼӵ绰����ǰ��
		if (mutiKey[4] == 0) { //�����л�
			keyEvent(VK_TAB, 1);
			mutiKey[4] = 1;  //�л����ڶ�������
		}
		else {
			keyEvent(VK_RETURN, 1);
			keyEvent(VK_ESCAPE, 1);
			keyEvent(VK_HOME, 1);
			keyEvent(VK_RETURN, 2);
			keyEvent(VK_SPACE, 1);
			keybd_event(VK_CONTROL, 0, 0, 0);
			keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
			keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
			keybd_event(VK_CONTROL, 0, 0, 0);
			keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
			keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
			mutiKey[4] = 0;   //�л��ص�һ������
		}
		lock = false;
		break;
	case VK_INSERT:// ��0
		keyEvent(VK_END, 1);
		keyEvent(0x30, 1);
		lock = false;
		break;
	case VK_OEM_2:// ����		US standard keyboard, the '?' key
		keyEvent(VK_RETURN, 2);
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		Sleep(100);
		keyEvent(0x32, 1);
		keyEvent(VK_RETURN, 3);
		lock = false;
		break;
	case VK_F2:// FFF757			F key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		Sleep(100);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RETURN, 1);
		SetCursorPos(198, 685);
		lock = false;
		break;
	case VK_F7:// ������1��O		F7
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_UP, 1);
		// ����
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);

		keyEvent(VK_DOWN, 1);
		// ճ��
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_F9:// GGGG		�����½�����	F9 key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RETURN, 1);
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_ESCAPE, 1);
		SetCursorPos(198, 685);
		lock = false;
		break;
	case VK_DIVIDE:// ����
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(100);
		keyEvent(VK_RETURN, 2);
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keyEvent(0x32, 1);
		keyEvent(VK_RETURN, 3);
		lock = false;
		break;
	case VK_MULTIPLY:// С����*�żĸ��½�
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_F11://����̼Ӻ�+++++++++�ͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½�
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 200; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 120; //����������,��������
			shang = shang + 130;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(100);
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		Sleep(100);
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 260; //����������,��������
			shang = shang + 130;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_OEM_4:// ������
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keybd_event(0x33, 0, 0, 0);keybd_event(0x33, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	}
	return lock;
}

BOOL KetthProjectAction::keyAction24(PKBDLLHOOKSTRUCT kbstruct, boolean lock) {
	HWND hWnd = GetFocus(); // �õ���ǰ���̹�����ڵĴ��� 
	LPRECT lParam = new RECT;
	int zuo = 0;
	int you = 0;
	int shang = 0;
	int xia = 0;
	// ���������鿴 https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx
	switch (kbstruct->vkCode) {
	case VK_F12:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_F8, 1);
		SetCursorPos(198, 685);
		lock = false;
		break;
	case VK_F8:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_ESCAPE, 1);
		SetCursorPos(198, 685);
		lock = false;
		break;
	case VK_ESCAPE:
		keyEvent(VK_ESCAPE, 10);
		lock = false;
		break;
	case VK_F3:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 20;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 300; //����������,��������
			shang = shang + 200;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_F4:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 20;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 300; //����������,��������
			shang = shang + 200;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			Sleep(600);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_F1:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_DOWN, 1);
		keyEvent(VK_HOME, 1);
		SetCursorPos(198, 685);
		lock = false;
		break;
	case VK_F2:// FFF757			F key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(66);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RETURN, 1);
		SetCursorPos(198, 685);
		lock = false;
		break;
	case 0x47:// ��ȡ	0x48��H key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(66);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 12);
		keyEvent(VK_NUMPAD1, 1);
		keyEvent(VK_LEFT, 1);
		lock = false;
		break;
	case 0x54:// �Լ�	0x54��T key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(66);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 13);
		keyEvent(VK_NUMPAD1, 1);
		keyEvent(VK_LEFT, 1);
		lock = false;
		break;
	case 0x42:// ����1000			B key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(66);
			keyEvent(VK_RETURN, 2);
			keyEvent(VK_HOME, 1);
			keyEvent(VK_RETURN, 1);
			keyEvent(VK_TAB, 10);
			keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
			keyEvent(VK_RETURN, 1);
			SetCursorPos(198, 685);
		lock = false;
		break;
	case 0x58:// �ڼ�				X key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 16);
		keyEvent(VK_NUMPAD1, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keybd_event(0x33, 0, 0, 0);keybd_event(0x33, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_SPACE:// �ո�
		if (switchSortCutStatus) {
			confirmSwitch();
		}
		else {
			keyEvent(VK_RETURN, 1);
		}
		lock = false;
		break;
	case VK_ADD://��
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(66);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_DOWN, 1);
		keyEvent(VK_HOME, 1);
		SetCursorPos(198, 685);
		lock = false;
		break;
	case VK_RETURN:// �س�
		if (switchSortCutStatus) {
			confirmSwitch();
		}
		else {
			keyEvent(VK_RETURN, 1);
		}
		lock = false;
		break;
	case 0x4B:// ����ר�ø����϶�			K
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			keyEvent(VK_RETURN, 1);
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(66);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		copyUpTwoline();
		keyEvent(VK_RETURN, 1);
		copyUpTwoline();
		keyEvent(VK_RETURN, 1);
		copyUpTwoline();
		keyEvent(VK_RETURN, 1);
		copyUpTwoline();
		keyEvent(VK_RETURN, 1);
		copyUpTwoline();
		keyEvent(VK_RETURN, 1);
		copyUpTwoline();
		keyEvent(VK_RETURN, 1);
		copyUpTwoline();
		keyEvent(VK_RETURN, 1);
		copyUpTwoline();
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_LEFT, 4);
		lock = false;
		break;
	case 0x4C:// ����ר�ø�������			L
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			keyEvent(VK_RETURN, 1);
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		copyUpThreeline();
		keyEvent(VK_RETURN, 1);
		copyUpThreeline();
		keyEvent(VK_RETURN, 1);
		copyUpThreeline();
		keyEvent(VK_RETURN, 1);
		copyUpThreeline();
		keyEvent(VK_RETURN, 1);
		copyUpThreeline();
		keyEvent(VK_RETURN, 1);
		copyUpThreeline();
		keyEvent(VK_RETURN, 1);
		copyUpThreeline();
		keyEvent(VK_RETURN, 1);
		copyUpThreeline();
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_LEFT, 4);
		lock = false;
		break;
	case 0x4A:// ������һ�й���ר	J key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(66);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		copyUpline();
		keyEvent(VK_RETURN, 1);
		copyUpline();
		keyEvent(VK_RETURN, 1);
		copyUpline();
		keyEvent(VK_RETURN, 1);
		copyUpline();
		keyEvent(VK_RETURN, 1);
		copyUpline();
		keyEvent(VK_RETURN, 1);
		copyUpline();
		keyEvent(VK_RETURN, 1);
		copyUpline();
		keyEvent(VK_RETURN, 1);
		copyUpline();
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_LEFT, 4);
		lock = false;
		break;
	case 0x43:// ����			C key

		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		lock = false;
		break;
	case 0x56:// ճ��			V key
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		lock = false;
		break;
	case 0x48:// �����			D key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(66);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_END, 1);
		keyEvent(VK_LEFT, 1);
		keyEvent(VK_LEFT, 2);
		SetCursorPos(198, 685);
		lock = false;
		break;
	case 0x59:// ����	
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(66);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RIGHT, 11);
		keyEvent(VK_ESCAPE, 1);
		inputText("AU");
		keyEvent(VK_RETURN, 1);
		Sleep(100);
		keyEvent(0x31, 1);
		keyEvent(VK_RETURN, 1);
		SetCursorPos(198, 685);
		lock = false;
		break;
	case VK_DOWN:// ��	
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(66);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_DOWN, 1);
		keyEvent(VK_HOME, 1);
		SetCursorPos(198, 685);
		lock = false;
		break;
	case 0x57:// W1212			W key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_TAB, 6);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);

		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x32, 0, 0, 0);keybd_event(0x32, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x32, 0, 0, 0);keybd_event(0x32, 0, KEYEVENTF_KEYUP, 0);
		SetCursorPos(198, 685);
		lock = false;
		break;
	case 0x44:// O2323			D KEY
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_TAB, 6);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);

		keybd_event(0x32, 0, 0, 0);keybd_event(0x32, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x33, 0, 0, 0);keybd_event(0x33, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x32, 0, 0, 0);keybd_event(0x32, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x33, 0, 0, 0);keybd_event(0x33, 0, KEYEVENTF_KEYUP, 0);
		SetCursorPos(198, 685);
		lock = false;
		break;
	case VK_F7:// ������1��O		F7
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_UP, 1);
		// ����
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);

		keyEvent(VK_DOWN, 1);
		// ճ��
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_MULTIPLY:// ������1��O		F7
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_UP, 1);
		// ����
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);

		keyEvent(VK_DOWN, 1);
		// ճ��
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;

	case 0x53:// U2222			S KEY
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_TAB, 6);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);

		keybd_event(0x32, 0, 0, 0);keybd_event(0x32, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x32, 0, 0, 0);keybd_event(0x32, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x32, 0, 0, 0);keybd_event(0x32, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x32, 0, 0, 0);keybd_event(0x32, 0, KEYEVENTF_KEYUP, 0);
		SetCursorPos(198, 685);
		lock = false;
		break;
	case 0x41:// P1818			A key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_TAB, 6);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);

		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x38, 0, 0, 0);keybd_event(0x38, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x38, 0, 0, 0);keybd_event(0x38, 0, KEYEVENTF_KEYUP, 0);
		SetCursorPos(198, 685);
		lock = false;
		break;
	case 0x51:// I1111			Q key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_TAB, 6);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);

		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		SetCursorPos(198, 685);
		lock = false;
		break;
	case 0x45:// E1313			E key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_TAB, 6);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);

		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x33, 0, 0, 0);keybd_event(0x33, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x33, 0, 0, 0);keybd_event(0x33, 0, KEYEVENTF_KEYUP, 0);
		SetCursorPos(198, 685);
		lock = false;
		break;
	case 0x52:// R477			R KEY
		if (mutiKey[1] == 0) { //�����л�
			hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
			if (hWnd != NULL) {
				::GetWindowRect(hWnd, lParam);
				//int zuo = lParam->left;
				you = lParam->right;
				shang = lParam->top;
				//int xia = lParam->bottom;
				you = you - 20; //����������,��������
				shang = shang + 10;//��������,��������
				SetCursorPos(you, shang);
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			};
			Sleep(66);
			keyEvent(VK_RETURN, 1);
			keyEvent(VK_ESCAPE, 1);
			Sleep(100);
			keyEvent(VK_HOME, 1);
			keyEvent(VK_TAB, 17);
			keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
			keybd_event(0x34, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
			keybd_event(0x37, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
			keybd_event(0x37, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
			mutiKey[1] = 1;  //�л����ڶ�������
		}
		else {
			keyEvent(VK_ESCAPE, 1);
			keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
			keybd_event(0x32, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
			keybd_event(0x33, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
			mutiKey[1] = 0;   //�л��ص�һ������
		}
		lock = false;
		break;
	case VK_INSERT:// ��0
		keyEvent(VK_END, 1);
		keyEvent(0x30, 1);
		lock = false;
		break;
	case VK_F11://����̼Ӻ�+++++++++�ͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½�
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 200; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 120; //����������,��������
			shang = shang + 130;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(100);
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		Sleep(100);
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 260; //����������,��������
			shang = shang + 130;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_OEM_3:// �ĸ�				For the US standard keyboard, the '`~' key
		keyEvent(VK_RETURN, 2);
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		Sleep(100);
		keyEvent(0x31, 1);
		keyEvent(0x31, 1);
		keyEvent(VK_RETURN, 2);
		lock = false;
		break;
	case VK_OEM_2:// ����		US standard keyboard, the '?' key
		keyEvent(VK_RETURN, 2);
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		Sleep(100);
		keyEvent(0x32, 1);
		keyEvent(VK_RETURN, 3);
		lock = false;
		break;
	case VK_OEM_4:// ������
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(66);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keybd_event(0x33, 0, 0, 0);keybd_event(0x33, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_F9:// GGGG		�����½�����	F9 key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RETURN, 1);
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_ESCAPE, 1);
		SetCursorPos(198, 685);
		lock = false;
		break;
	case 0x55:// 	����
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(66);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RIGHT, 10);
		keyEvent(VK_ESCAPE, 1);
		inputText("AA");
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x49:// 	F
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(66);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RIGHT, 10);
		inputText("F");
		keyEvent(VK_RETURN, 1);
		Sleep(200);
		lock = false;
		break;
	case 0x4F:// 			AS
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(66);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RIGHT, 10);
		keyEvent(VK_ESCAPE, 1);
		inputText("AS");
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x4E:// ����	
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(66);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RIGHT, 10);
		keyEvent(VK_ESCAPE, 1);
		inputText("AY");
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x50:// ����	
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(66);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RIGHT, 10);
		inputText("2");
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;

	case 0x5A:// Z		
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(66);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RIGHT, 10);
		inputText("0");
		keyEvent(VK_RETURN, 1);
		Sleep(100);
		keyEvent(0x31, 1);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	}
	return lock;
}


BOOL KetthProjectAction::keyAction25(PKBDLLHOOKSTRUCT kbstruct, boolean lock) {
	HWND hWnd = GetFocus(); // �õ���ǰ���̹�����ڵĴ��� 
	LPRECT lParam = new RECT;
	int zuo = 0;
	int you = 0;
	int shang = 0;
	int xia = 0;
	// ���������鿴 https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx
	switch (kbstruct->vkCode) {
	case VK_SCROLL://�ر�ϵͳ
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			keyEvent(VK_RETURN, 1);
		}
		lock = false;
		break;
	case VK_OEM_3:// esc					For the US standard keyboard, the '`~' key
		keyEvent(VK_ESCAPE, 1);
		lock = false;
		break;
	case VK_ESCAPE:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_ESCAPE, 1);
		SetCursorPos(198, 685);
		lock = false;
		break;
	case VK_F3:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 20;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 300; //����������,��������
			shang = shang + 200;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_F4:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 20;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 300; //����������,��������
			shang = shang + 200;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			Sleep(600);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_F1:
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case 0x45:// 	
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RIGHT, 10);
		inputText("AE");
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x41:// 	
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RIGHT, 10);
		inputText("AA");
		keyEvent(VK_RETURN, 1);
		Sleep(200);

		lock = false;
		break;
	case 0x55:// ����		
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RIGHT, 10);
		inputText("AU");
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x46:// 	
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RIGHT, 10);
		inputText("F");
		keyEvent(VK_RETURN, 1);
		Sleep(200);
		lock = false;
		break;
	case 0x53:// 			S
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RIGHT, 10);
		inputText("AS");
		keyEvent(VK_RETURN, 1);
		Sleep(200);
		lock = false;
		break;
	case 0x59:// Y		
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}	
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RIGHT, 10);
		inputText("AY");
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x57:// 2		
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RIGHT, 10);
		inputText("2");
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x35:// 5		
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RIGHT, 10);
		inputText("1");
		keyEvent(VK_RETURN, 1);
		Sleep(100);
		inputText("500");
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x36:// 5		
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RIGHT, 10);
		inputText("1");
		keyEvent(VK_RETURN, 1);
		Sleep(100);
		inputText("5000");
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x31:// 1			����1000
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RIGHT, 10);
		inputText("1");
		keyEvent(VK_RETURN, 1);
		Sleep(100);
		inputText("1000");
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x33:// 3			����10000
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RIGHT, 10);
		inputText("1");
		keyEvent(VK_RETURN, 1);
		Sleep(200);
		inputText("10000");
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x34:// 4			����20000 
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RIGHT, 10);
		inputText("1");
		keyEvent(VK_RETURN, 1);
		Sleep(100);
		inputText("20000");
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x32:// 2		����2000
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RIGHT, 10);
		inputText("1");
		keyEvent(VK_RETURN, 1);
		Sleep(100);
		inputText("2000");
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x30:// 0		
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RIGHT, 10);
		inputText("0");
		keyEvent(VK_RETURN, 1);
		Sleep(100);
		keyEvent(0x31, 1);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_F11://����̼Ӻ�+++++++++�ͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½�
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 200; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 120; //����������,��������
			shang = shang + 130;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(100);
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		Sleep(100);
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 260; //����������,��������
			shang = shang + 130;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_OEM_6://]]  }}}����̼�++�������  ���ǳ���
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 60;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 1220; //����������,��������
			shang = shang + 700;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	}
	return lock;
}

//��������
BOOL KetthProjectAction::keyAction26(PKBDLLHOOKSTRUCT kbstruct, boolean lock) {
	HWND hWnd = GetFocus(); // �õ���ǰ���̹�����ڵĴ��� 
	LPRECT lParam = new RECT;
	int zuo = 0;
	int you = 0;
	int shang = 0;
	int xia = 0;
	// ���������鿴 https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx
	switch (kbstruct->vkCode) {
	case VK_SCROLL://�ر�ϵͳ
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			keyEvent(VK_RETURN, 1);
		}
		lock = false;
		break;
	case VK_F8:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_ESCAPE, 1);
		SetCursorPos(198, 685);
		lock = false;
		break;
	case VK_OEM_3:// esc					For the US standard keyboard, the '`~' key
		keyEvent(VK_ESCAPE, 1);
		lock = false;
		break;
	case VK_ESCAPE:
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_ESCAPE, 1);
		SetCursorPos(198, 685);
		lock = false;
		break;
	case VK_F3:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 20;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 300; //����������,��������
			shang = shang + 200;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_F4:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 20;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 300; //����������,��������
			shang = shang + 200;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			Sleep(600);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_F1:
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case VK_TAB://TAB��
		keyEvent(VK_DOWN, 1);
		lock = false;
		break;
	case 0x57:// ��ȡ	W key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 12);
		keyEvent(VK_NUMPAD1, 1);
		keyEvent(VK_LEFT, 1);
		lock = false;
		break;
	case 0x5A:// �Լ�	Z key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 13);
		keyEvent(VK_NUMPAD1, 1);
		keyEvent(VK_LEFT, 1);
		lock = false;
		break;

	case VK_OEM_PERIOD:// �ҵĽű�1		VK_OEM_PERIOD ��'.' key	
		keyEvent(VK_OEM_PERIOD, 1);
		keyEvent(0x35, 1);
		keyEvent(VK_RETURN, 2);
		lock = false;
		break;
	case 0x4D:// �ҵĽű�1		VK_OEM_PERIOD ��'.' key	
		keyEvent(VK_OEM_PERIOD, 1);
		keyEvent(0x35, 1);
		lock = false;
		break;
	case VK_OEM_5:// ɾ��			'\|' key
		keyEvent(VK_BACK, 1);
		lock = false;
		break;
	case 0x42:// �ڼ�				B key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 16);
		keyEvent(VK_NUMPAD1, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keybd_event(0x33, 0, 0, 0);keybd_event(0x33, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_SPACE:// �ո�
		if (switchSortCutStatus) {
			confirmSwitch();
		}
		else {
			keyEvent(VK_RETURN, 1);
		}
		lock = false;
		break;
	case VK_RETURN:// �س�
		if (switchSortCutStatus) {
			confirmSwitch();
		}
		else {
			keyEvent(VK_RETURN, 1);
		}
		lock = false;
		break;
	case 0x58:// ��			X key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_DOWN, 1);
		lock = false;
		break;
	case VK_OEM_4:// ����һ��		����
		keyEvent(VK_LEFT, 1);
		lock = false;
		break;
	case VK_F9:// ������1��O		F7
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_UP, 1);
		// ����
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);

		keyEvent(VK_DOWN, 1);
		// ճ��
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_F6:// ����ר�ø����϶�			F9
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		copyUpTwoline();
		keyEvent(VK_RETURN, 1);
		copyUpTwoline();
		keyEvent(VK_RETURN, 1);
		copyUpTwoline();
		keyEvent(VK_RETURN, 1);
		copyUpTwoline();
		keyEvent(VK_RETURN, 1);
		copyUpTwoline();
		keyEvent(VK_RETURN, 1);
		copyUpTwoline();
		keyEvent(VK_RETURN, 1);
		copyUpTwoline();
		keyEvent(VK_RETURN, 1);
		copyUpTwoline();
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_LEFT, 4);
		lock = false;
		break;
	case VK_F7:// ����ר�ø�������			F10
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		copyUpThreeline();
		keyEvent(VK_RETURN, 1);
		copyUpThreeline();
		keyEvent(VK_RETURN, 1);
		copyUpThreeline();
		keyEvent(VK_RETURN, 1);
		copyUpThreeline();
		keyEvent(VK_RETURN, 1);
		copyUpThreeline();
		keyEvent(VK_RETURN, 1);
		copyUpThreeline();
		keyEvent(VK_RETURN, 1);
		copyUpThreeline();
		keyEvent(VK_RETURN, 1);
		copyUpThreeline();
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_LEFT, 4);
		lock = false;
		break;
	case VK_F5:// ������һ�й���ר	J key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		copyUpline();
		keyEvent(VK_RETURN, 1);
		copyUpline();
		keyEvent(VK_RETURN, 1);
		copyUpline();
		keyEvent(VK_RETURN, 1);
		copyUpline();
		keyEvent(VK_RETURN, 1);
		copyUpline();
		keyEvent(VK_RETURN, 1);
		copyUpline();
		keyEvent(VK_RETURN, 1);
		copyUpline();
		keyEvent(VK_RETURN, 1);
		copyUpline();
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_LEFT, 4);
		lock = false;
		break;

	case 0x45:// ������			E key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keybd_event(0x33, 0, 0, 0);keybd_event(0x33, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x59:// �����			Y key
		keyEvent(VK_END, 1);
		keyEvent(VK_LEFT, 1);
		keyEvent(VK_LEFT, 2);
		lock = false;
		break;
		Sleep(66);
	case 0x56:// ����		V key
		if (mutiKey[2] == 0) { //�����л�
			hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
			if (hWnd != NULL) {
				::GetWindowRect(hWnd, lParam);
				//int zuo = lParam->left;
				you = lParam->right;
				shang = lParam->top;
				//int xia = lParam->bottom;
				you = you - 20; //����������,��������
				shang = shang + 10;//��������,��������
				SetCursorPos(you, shang);
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			}
			keyEvent(VK_RETURN, 1);
			keyEvent(VK_HOME, 1);
			keyEvent(VK_RETURN, 1);
			keyEvent(VK_TAB, 10);
			keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
			keyEvent(VK_RETURN, 1);
			SetCursorPos(198, 685);
			mutiKey[2] = 1;  //�л����ڶ�������
		}
		else {
			hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
			if (hWnd != NULL) {
				::GetWindowRect(hWnd, lParam);
				//int zuo = lParam->left;
				you = lParam->right;
				shang = lParam->top;
				//int xia = lParam->bottom;
				you = you - 20; //����������,��������
				shang = shang + 10;//��������,��������
				SetCursorPos(you, shang);
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			}
			keyEvent(VK_RETURN, 1);
			keyEvent(VK_HOME, 1);
			keyEvent(VK_RIGHT, 11);
			inputText("0");
			keyEvent(VK_RETURN, 1);
			SetCursorPos(198, 685);
			mutiKey[2] = 0;   //�л��ص�һ������
		}
		lock = false;
		break;
	case 0x54:// ����		T	
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(66);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RIGHT, 10);
		inputText("AU");
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x4A:// ����		����	
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(66);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RIGHT, 10);
		inputText("AE");
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x55://		U ����
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(66);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RIGHT, 10);
		inputText("AY");
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x52://		��װ
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(66);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RIGHT, 10);
		inputText("0");
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_DIVIDE:// W1212			W key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_TAB, 6);
		keyEvent(0x31, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(0x31, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(0x31, 1);
		keyEvent(0x32, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(0x31, 1);
		keyEvent(0x32, 1);
		keyEvent(VK_DOWN, 1);
		lock = false;
		break;
	case VK_OEM_COMMA:// 	case 0x44:// ����		D		For any country/region, the ',' key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 3);
		keyEvent(0x32, 1);
		keyEvent(VK_RETURN, 3);
		SetCursorPos(198, 685);
		lock = false;
		break;
	case 0x44:// ����		D
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
				//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 3);
		keyEvent(0x32, 1);
		keyEvent(VK_RETURN, 3);
		SetCursorPos(198, 685);
		lock = false;
		break;
	case VK_F2:// FFF757			F key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x46:// FFF757			F key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x53:// S			S key�ĸ�
		keyEvent(VK_HOME, 1);
		keyEvent(VK_PAUSE, 1);
		keyEvent(VK_RETURN, 3);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_ADD:// O2323			+ KEY
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_TAB, 6);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x32, 0, 0, 0);keybd_event(0x32, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x33, 0, 0, 0);keybd_event(0x33, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x32, 0, 0, 0);keybd_event(0x32, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x33, 0, 0, 0);keybd_event(0x33, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_DOWN, 1);
		lock = false;
		break;
	case 0x41:// 2222			A KEY
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_TAB, 6);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x32, 0, 0, 0);keybd_event(0x32, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x32, 0, 0, 0);keybd_event(0x32, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x32, 0, 0, 0);keybd_event(0x32, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x32, 0, 0, 0);keybd_event(0x32, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_DOWN, 1);
		lock = false;
		break;
	case 0x51:// P1818			Q key
		keyEvent(VK_ESCAPE, 1);
		SetCursorPos(598, 485);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_TAB, 6);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x38, 0, 0, 0);keybd_event(0x38, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x38, 0, 0, 0);keybd_event(0x38, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_DOWN, 1);
		lock = false;
		break;

	case 0x43:// I1111			C key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_TAB, 6);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);

		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_DOWN, 1);
		lock = false;
		break;
	case VK_MULTIPLY:// E1313			*key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_TAB, 6);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);

		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x33, 0, 0, 0);keybd_event(0x33, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x33, 0, 0, 0);keybd_event(0x33, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_DOWN, 1);
		lock = false;
		break;

	case 0x47:// GGGG			G key
		keyEvent(VK_ESCAPE, 1);
		SetCursorPos(598, 485);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RETURN, 1);
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x48:// R477			R KEY
		if (mutiKey[0] == 0) { //�����л�
			hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
			if (hWnd != NULL) {
				::GetWindowRect(hWnd, lParam);
				//int zuo = lParam->left;
				you = lParam->right;
				shang = lParam->top;
				//int xia = lParam->bottom;
				you = you - 20; //����������,��������
				shang = shang + 10;//��������,��������
				SetCursorPos(you, shang);
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			};
			keyEvent(VK_RETURN, 1);
			keyEvent(VK_ESCAPE, 1);
			Sleep(100);
			keyEvent(VK_HOME, 1);
			keyEvent(VK_TAB, 17);
			keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
			keybd_event(0x34, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
			keybd_event(0x37, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
			keybd_event(0x37, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
			mutiKey[0] = 1;  //�л����ڶ�������
		}
		else {
			keyEvent(VK_ESCAPE, 1);
			keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
			keybd_event(0x32, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
			keybd_event(0x33, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
			mutiKey[0] = 0;   //�л��ص�һ������
		}
		lock = false;
		break;
	case VK_PRIOR:// qq3030			Q key
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_TAB, 6);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);

		keybd_event(0x31, 0, 0, 0);keybd_event(0x33, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x36, 0, 0, 0);keybd_event(0x30, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x33, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x36, 0, 0, 0);keybd_event(0x30, 0, KEYEVENTF_KEYUP, 0);
		lock = false;
		break;
	case VK_F11://����̼Ӻ�+++++++++�ͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½�
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 200; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 120; //����������,��������
			shang = shang + 130;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(100);
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		Sleep(100);
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 260; //����������,��������
			shang = shang + 130;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_OEM_6://]]  }}}����̼�++�������  ���ǳ���
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 60;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 1220; //����������,��������
			shang = shang + 700;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;

	}
	return lock;
}


BOOL KetthProjectAction::keyAction27(PKBDLLHOOKSTRUCT kbstruct, boolean lock) {
	HWND hWnd = GetFocus(); // �õ���ǰ���̹�����ڵĴ��� 
	LPRECT lParam = new RECT;
	int zuo = 0;
	int you = 0;
	int shang = 0;
	int xia = 0;
	// ���������鿴 https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx
	switch (kbstruct->vkCode) {
	case VK_SCROLL://�ر�ϵͳ
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			keyEvent(VK_RETURN, 1);
		}
		lock = false;
		break;
	case VK_F12:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_F8, 1);
		SetCursorPos(198, 685);
		lock = false;
		break;
	case VK_ESCAPE:
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_ESCAPE, 1);
		SetCursorPos(198, 685);
		lock = false;
		break;
	case VK_F3:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 20;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 300; //����������,��������
			shang = shang + 200;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_F4:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 20;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 300; //����������,��������
			shang = shang + 200;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			Sleep(600);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_PRIOR:// F8			'\|' key
		keyEvent(VK_F8, 1);
		lock = false;
		break;
	case VK_OEM_1:// 1		����	Z key
		keyEvent(VK_SPACE, 1);
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		lock = false;
		break;
	case VK_F1:
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case VK_RETURN:// �س�
		if (switchSortCutStatus) {
			confirmSwitch();
		}
		else {
			keyEvent(VK_RETURN, 1);
		}
		lock = false;
		break;
	case VK_OEM_COMMA:// 	case 0x44:// ����		D		For any country/region, the ',' key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 3);
		keyEvent(0x32, 1);
		keyEvent(VK_RETURN, 3);
		lock = false;
		break;
	case VK_OEM_PERIOD:// 	case 0x44:// ����		D		For any country/region, the ',' key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 3);
		keyEvent(0x32, 1);
		keyEvent(VK_RETURN, 3);
		lock = false;
		break;
	case VK_OEM_3:// 	case 0x44:// ����		D		For any country/region, the ',' key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 3);
		keyEvent(0x32, 1);
		keyEvent(VK_RETURN, 3);
		lock = false;
		break;
	case 0x31:// �ĸ�
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 3);
		keyEvent(0x31, 1);
		keyEvent(0x31, 1);
		keyEvent(VK_RETURN, 2);
		lock = false;
		break;
	case VK_DIVIDE:// ��
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 3);
		keyEvent(0x31, 1);
		keyEvent(0x31, 1);
		keyEvent(VK_RETURN, 2);
		lock = false;
		break;
	case VK_F2:// FFF757			F key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_MULTIPLY:// С����*��
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_TAB://TAB��
		keyEvent(VK_DOWN, 1);
		lock = false;
		break;
	case 0x5A:// Z					For the US standard keyboard, the '`~' ke
		keyEvent(0x30, 1);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_F7:// ������1��O		F7
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_UP, 1);
		// ����
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);

		keyEvent(VK_DOWN, 1);
		// ճ��
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_OEM_5:// ɾ��			'\|' key
		keyEvent(VK_BACK, 1);
		lock = false;
		break;
	case VK_OEM_4:// ���ֻ�		US standard keyboard, the '[{' k
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_LEFT, 1);
		// ����
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		// ճ��
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);

		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_ADD://			����С���̼Ӻ�
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 3);
		keyEvent(0x32, 1);
		keyEvent(VK_RETURN, 3);
		lock = false;
		break;
	case VK_F11://����̼Ӻ�+++++++++�ͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½�
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 200; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 120; //����������,��������
			shang = shang + 130;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(100);
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		Sleep(100);
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 260; //����������,��������
			shang = shang + 130;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_OEM_6://]]  }}}����̼�++�������  ���ǳ���
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 60;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 1220; //����������,��������
			shang = shang + 700;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;

	}
	return lock;
}


BOOL KetthProjectAction::keyAction28(PKBDLLHOOKSTRUCT kbstruct, boolean lock) {
	HWND hWnd = GetFocus(); // �õ���ǰ���̹�����ڵĴ��� 
	LPRECT lParam = new RECT;
	int zuo = 0;
	int you = 0;
	int shang = 0;
	int xia = 0;
	// ���������鿴 https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx
	switch (kbstruct->vkCode) {
		// ���������鿴 https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx
	case VK_SCROLL://�ر�ϵͳ
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			keyEvent(VK_RETURN, 1);
		}
		lock = false;
		break;
	case VK_ESCAPE:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_ESCAPE, 1);
		SetCursorPos(198, 685);
		lock = false;
		break;
	case VK_F3:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 20;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 300; //����������,��������
			shang = shang + 200;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_F4:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 20;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 300; //����������,��������
			shang = shang + 200;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			Sleep(600);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
		case VK_RETURN:// �س�
			if (switchSortCutStatus) {
				confirmSwitch();
			}
			else {
				keyEvent(VK_RETURN, 1);
			}
			lock = false;
			break;
		case VK_PRIOR:// F8			'\|' key
			keyEvent(VK_F8, 1);
			lock = false;
			break;
		case VK_OEM_COMMA:// ����Ҫ�Ĵ򵥽�			For any country/region, the ',' key
			hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
			if (hWnd != NULL) {
				::GetWindowRect(hWnd, lParam);
				//int zuo = lParam->left;
				you = lParam->right;
				shang = lParam->top;
				//int xia = lParam->bottom;
				you = you - 20; //����������,��������
				shang = shang + 10;//��������,��������
				SetCursorPos(you, shang);
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			}
			hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
			if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
				::GetWindowRect(hWnd, lParam);
				//int zuo = lParam->left;
				you = lParam->right;
				shang = lParam->top;
				//int xia = lParam->bottom;
				you = you - 20; //����������,��������
				shang = shang + 10;//��������,��������
				SetCursorPos(you, shang);
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			}
			keyEvent(VK_RETURN, 1);
			lock = false;
			break;
		case VK_OEM_1://		For any country/region, the '.' key
			hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
			if (hWnd != NULL) {
				::GetWindowRect(hWnd, lParam);
				//int zuo = lParam->left;
				you = lParam->right;
				shang = lParam->top;
				//int xia = lParam->bottom;
				you = you - 20; //����������,��������
				shang = shang + 10;//��������,��������
				SetCursorPos(you, shang);
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			}
			hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
			if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
				::GetWindowRect(hWnd, lParam);
				//int zuo = lParam->left;
				you = lParam->right;
				shang = lParam->top;
				//int xia = lParam->bottom;
				you = you - 20; //����������,��������
				shang = shang + 10;//��������,��������
				SetCursorPos(you, shang);
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			}
			keyEvent(VK_DOWN, 1);
			lock = false;
			break;
		case VK_OEM_4:// �ҵĽű�1			����
			hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
			if (hWnd != NULL) {
				::GetWindowRect(hWnd, lParam);
				//int zuo = lParam->left;
				you = lParam->right;
				shang = lParam->top;
				//int xia = lParam->bottom;
				you = you - 20; //����������,��������
				shang = shang + 10;//��������,��������
				SetCursorPos(you, shang);
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			}
			hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
			if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
				::GetWindowRect(hWnd, lParam);
				//int zuo = lParam->left;
				you = lParam->right;
				shang = lParam->top;
				//int xia = lParam->bottom;
				you = you - 20; //����������,��������
				shang = shang + 10;//��������,��������
				SetCursorPos(you, shang);
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			}
			keyEvent(VK_LEFT, 1);
			lock = false;
			break;
		case VK_OEM_5:// ɾ��			'\|' key
			keyEvent(VK_BACK, 1);
			lock = false;
			break;
		case VK_F6:// 	�ӵ绰��
			keyEvent(VK_HOME, 1);
			keyEvent(VK_SPACE, 1);
			Sleep(79);
			keybd_event(VK_CONTROL, 0, 0, 0);
			Sleep(79);
			keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
			Sleep(79);
			keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
			Sleep(79);
			keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
			Sleep(79);
			keyEvent(VK_LEFT, 10);
			lock = false;
			break;
		case VK_DIVIDE:// ��һ������			F9
			keybd_event(VK_ESCAPE, 0, 0, 0);keybd_event(VK_HOME, 0, KEYEVENTF_KEYUP, 0);
			copyUpTwoline();
			keybd_event(VK_TAB, 0, 0, 0);keybd_event(VK_TAB, 0, KEYEVENTF_KEYUP, 0);
			copyUpTwoline();
			keybd_event(VK_TAB, 0, 0, 0);keybd_event(VK_TAB, 0, KEYEVENTF_KEYUP, 0);
			copyUpTwoline();
			keybd_event(VK_TAB, 0, 0, 0);keybd_event(VK_TAB, 0, KEYEVENTF_KEYUP, 0);
			copyUpTwoline();
			keybd_event(VK_TAB, 0, 0, 0);keybd_event(VK_TAB, 0, KEYEVENTF_KEYUP, 0);
			copyUpTwoline();
			keybd_event(VK_TAB, 0, 0, 0);keybd_event(VK_TAB, 0, KEYEVENTF_KEYUP, 0);
			copyUpTwoline();
			keyEvent(VK_DOWN, 1);
			lock = false;
			break;
			break;
		case VK_PAUSE:// ����ר�ø�������			F10
			keyEvent(VK_HOME, 1);
			copyUpThreeline();
			keyEvent(VK_RETURN, 1);
			copyUpThreeline();
			keyEvent(VK_RETURN, 1);
			copyUpThreeline();
			keyEvent(VK_RETURN, 1);
			copyUpThreeline();
			keyEvent(VK_RETURN, 1);
			copyUpThreeline();
			keyEvent(VK_RETURN, 1);
			copyUpThreeline();
			keyEvent(VK_RETURN, 1);
			keyEvent(VK_DOWN, 1);
			lock = false;
			break;
		case VK_F7:// ������1��O		F7
			keyEvent(VK_ESCAPE, 1);
			keyEvent(VK_UP, 1);
			// ����
			keybd_event(VK_CONTROL, 0, 0, 0);
			keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
			keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);

			keyEvent(VK_DOWN, 1);
			// ճ��
			keybd_event(VK_CONTROL, 0, 0, 0);
			keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
			keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
			keyEvent(VK_RETURN, 1);
			lock = false;
			break;
		case VK_MULTIPLY:// ȫ������һ��	Z key0x5A 
			hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
			if (hWnd != NULL) {
				::GetWindowRect(hWnd, lParam);
				//int zuo = lParam->left;
				you = lParam->right;
				shang = lParam->top;
				//int xia = lParam->bottom;
				you = you - 20; //����������,��������
				shang = shang + 10;//��������,��������
				SetCursorPos(you, shang);
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			}
			hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
			if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
				::GetWindowRect(hWnd, lParam);
				//int zuo = lParam->left;
				you = lParam->right;
				shang = lParam->top;
				//int xia = lParam->bottom;
				you = you - 20; //����������,��������
				shang = shang + 10;//��������,��������
				SetCursorPos(you, shang);
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			}
			keyEvent(VK_ESCAPE, 1);
			keyEvent(VK_HOME, 1);
			copyUpline();
			keyEvent(VK_RETURN, 1);
			copyUpline();
			keyEvent(VK_RETURN, 1);
			copyUpline();
			keyEvent(VK_RETURN, 1);
			copyUpline();
			keyEvent(VK_RETURN, 1);
			copyUpline();
			keyEvent(VK_RETURN, 1);
			copyUpline();
			keyEvent(VK_DOWN, 1);
			lock = false;
			break;

		case VK_OEM_3:// esc					For the US standard keyboard, the '`~' key
			keyEvent(VK_BACK, 1);
			lock = false;
			break;
		case VK_F2:// MGS1111111		Add key
			keyEvent(VK_RETURN, 1);
			keyEvent(VK_LEFT, 1);
			keybd_event(VK_CONTROL, 0, 0, 0);
			keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
			keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
			keyEvent(VK_RETURN, 1);
			keybd_event(VK_CONTROL, 0, 0, 0);
			keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
			keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
			keyEvent(VK_RETURN, 1);
			lock = false;
			break;
		case VK_OEM_2:// For the US standard keyboard, the '/?' key
			keyEvent(VK_DOWN, 1);
			lock = false;
			break;
		case VK_F11://����̼Ӻ�+++++++++�ͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½�
			keybd_event(VK_CONTROL, 0, 0, 0);
			keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
			keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
			hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
			if (hWnd != NULL) {
				::GetWindowRect(hWnd, lParam);
				//int zuo = lParam->left;
				you = lParam->right;
				shang = lParam->top;
				//int xia = lParam->bottom;
				you = you - 20; //����������,��������
				shang = shang + 10;//��������,��������
				SetCursorPos(you, shang);
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			}
			hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
			if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
				::GetWindowRect(hWnd, lParam);
				//int zuo = lParam->left;
				you = lParam->right;
				shang = lParam->top;
				//int xia = lParam->bottom;
				you = you - 20; //����������,��������
				shang = shang + 10;//��������,��������
				SetCursorPos(you, shang);
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			}
			//*  �µ�
			//��ȡ����ڵ�����
			//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
			hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
			if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
				::GetWindowRect(hWnd, lParam);
				zuo = lParam->left;
				//int you = lParam->right;
				shang = lParam->top;
				//int xia = lParam->bottom;
				zuo = zuo + 200; //����������,��������
				shang = shang + 40;//��������,��������
				SetCursorPos(zuo, shang);
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
				shang = shang + 40;//��������,��������
				SetCursorPos(zuo, shang);
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			}
			Sleep(200);
			hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
			if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
				::GetWindowRect(hWnd, lParam);
				zuo = lParam->left;
				//int you = lParam->right;
				shang = lParam->top;
				//int xia = lParam->bottom;
				zuo = zuo + 120; //����������,��������
				shang = shang + 130;//��������,��������
				SetCursorPos(zuo, shang);
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			}
			Sleep(100);
			keybd_event(VK_CONTROL, 0, 0, 0);
			keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
			keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
			Sleep(100);
			hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
			if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
				::GetWindowRect(hWnd, lParam);
				zuo = lParam->left;
				//int you = lParam->right;
				shang = lParam->top;
				//int xia = lParam->bottom;
				zuo = zuo + 260; //����������,��������
				shang = shang + 130;//��������,��������
				SetCursorPos(zuo, shang);
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			}
			lock = false;
			break;
		case VK_OEM_6://]]  }}}����̼�++�������  ���ǳ���
			hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
			if (hWnd != NULL) {
				::GetWindowRect(hWnd, lParam);
				//int zuo = lParam->left;
				you = lParam->right;
				shang = lParam->top;
				//int xia = lParam->bottom;
				you = you - 20; //����������,��������
				shang = shang + 10;//��������,��������
				SetCursorPos(you, shang);
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			}
			hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
			if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
				::GetWindowRect(hWnd, lParam);
				//int zuo = lParam->left;
				you = lParam->right;
				shang = lParam->top;
				//int xia = lParam->bottom;
				you = you - 20; //����������,��������
				shang = shang + 10;//��������,��������
				SetCursorPos(you, shang);
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			}
			//*  �µ�
			//��ȡ����ڵ�����
			//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
			hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
			if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
				::GetWindowRect(hWnd, lParam);
				zuo = lParam->left;
				//int you = lParam->right;
				shang = lParam->top;
				//int xia = lParam->bottom;
				zuo = zuo + 20; //����������,��������
				shang = shang + 40;//��������,��������
				SetCursorPos(zuo, shang);
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
				shang = shang + 60;//��������,��������
				SetCursorPos(zuo, shang);
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			}
			Sleep(200);
			hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
			if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
				::GetWindowRect(hWnd, lParam);
				//int zuo = lParam->left;
				you = lParam->right;
				shang = lParam->top;
				//int xia = lParam->bottom;
				you = you - 1220; //����������,��������
				shang = shang + 700;//��������,��������
				SetCursorPos(you, shang);
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			}
			lock = false;
			break;
	}
	return lock;
}


BOOL KetthProjectAction::keyAction29(PKBDLLHOOKSTRUCT kbstruct, boolean lock) {
	HWND hWnd = GetFocus(); // �õ���ǰ���̹�����ڵĴ��� 
	LPRECT lParam = new RECT;
	int zuo = 0;
	int you = 0;
	int shang = 0;
	int xia = 0;
	// ���������鿴 https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx
	switch (kbstruct->vkCode) {
	case VK_SCROLL://�ر�ϵͳ
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			keyEvent(VK_RETURN, 1);
		}
		lock = false;
		break;
	case VK_OEM_3:// esc					For the US standard keyboard, the '`~' key
		keyEvent(VK_ESCAPE, 1);
		lock = false;
		break;
	case VK_ESCAPE:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		keyEvent(VK_ESCAPE, 1);
		SetCursorPos(198, 685);
		lock = false;
		break;
	case VK_F3:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 20;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 300; //����������,��������
			shang = shang + 200;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_F4:
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 20;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 300; //����������,��������
			shang = shang + 200;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			Sleep(600);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_F1:
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case VK_OEM_2:// ��			? key
		keyEvent(VK_DOWN, 1);
		lock = false;
		break;
	case VK_OEM_4:// ��			
		keyEvent(VK_LEFT, 1);
		lock = false;
		break;
	case 0x48:// ��ȡ	0x48��H key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 12);
		keyEvent(VK_NUMPAD1, 1);
		keyEvent(VK_LEFT, 1);
		lock = false;
		break;
	case 0x54:// �Լ�	0x54��T key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 13);
		keyEvent(VK_NUMPAD1, 1);
		keyEvent(VK_LEFT, 1);
		lock = false;
		break;
	case VK_INSERT:// ��0
		keyEvent(VK_END, 1);
		keyEvent(0x30, 1);
		lock = false;
		break;

	case VK_OEM_PERIOD:// �ҵĽű�1		VK_OEM_PERIOD ��'.' key	
		keyEvent(VK_OEM_PERIOD, 1);
		keyEvent(0x35, 1);
		keyEvent(VK_RETURN, 2);
		lock = false;
		break;
	case 0x4D:// �ҵĽű�1		VK_OEM_PERIOD ��'.' key	
		keyEvent(VK_OEM_PERIOD, 1);
		keyEvent(0x35, 1);
		lock = false;
		break;
	case VK_OEM_5:// ɾ��			'\|' key
		keyEvent(VK_BACK, 1);
		lock = false;
		break;
	case 0x58:// �ڼ�				X key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 16);
		keyEvent(VK_NUMPAD1, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keybd_event(0x33, 0, 0, 0);keybd_event(0x33, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_SPACE:// �ո�
		if (switchSortCutStatus) {
			confirmSwitch();
		}
		else {
			keyEvent(VK_RETURN, 1);
		}
		lock = false;
		break;
	case VK_RETURN:// �س�
		if (switchSortCutStatus) {
			confirmSwitch();
		}
		else {
			keyEvent(VK_RETURN, 1);
		}
		lock = false;
		break;
	case 0x4B:// ��		K	 key
		keyEvent(VK_DOWN, 1);
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		lock = false;
		break;
	case 0x4E:// 			E key
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		lock = false;
		break;


	case VK_OEM_COMMA:// ����һ��		US standard keyboard, the '[{' key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 3);
		keyEvent(0x31, 1);
		keyEvent(0x31, 1);
		keyEvent(VK_RETURN, 2);
		lock = false;
		break;
	case VK_F7:// ������1��O		F7
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_UP, 1);
		// ����
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);

		keyEvent(VK_DOWN, 1);
		// ճ��
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_F9:// ����ר�ø����϶�			F9
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		copyUpTwoline();
		keyEvent(VK_RETURN, 1);
		copyUpTwoline();
		keyEvent(VK_RETURN, 1);
		copyUpTwoline();
		keyEvent(VK_RETURN, 1);
		copyUpTwoline();
		keyEvent(VK_RETURN, 1);
		copyUpTwoline();
		keyEvent(VK_RETURN, 1);
		copyUpTwoline();
		keyEvent(VK_RETURN, 1);
		copyUpTwoline();
		keyEvent(VK_RETURN, 1);
		copyUpTwoline();
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_LEFT, 4);
		lock = false;
		break;
	case VK_F10:// ����ר�ø�������			F10
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		copyUpThreeline();
		keyEvent(VK_RETURN, 1);
		copyUpThreeline();
		keyEvent(VK_RETURN, 1);
		copyUpThreeline();
		keyEvent(VK_RETURN, 1);
		copyUpThreeline();
		keyEvent(VK_RETURN, 1);
		copyUpThreeline();
		keyEvent(VK_RETURN, 1);
		copyUpThreeline();
		keyEvent(VK_RETURN, 1);
		copyUpThreeline();
		keyEvent(VK_RETURN, 1);
		copyUpThreeline();
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_LEFT, 4);
		lock = false;
		break;
	case 0x4A:// ������һ�й���ר	J key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		copyUpline();
		keyEvent(VK_RETURN, 1);
		copyUpline();
		keyEvent(VK_RETURN, 1);
		copyUpline();
		keyEvent(VK_RETURN, 1);
		copyUpline();
		keyEvent(VK_RETURN, 1);
		copyUpline();
		keyEvent(VK_RETURN, 1);
		copyUpline();
		keyEvent(VK_RETURN, 1);
		copyUpline();
		keyEvent(VK_RETURN, 1);
		copyUpline();
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_LEFT, 4);
		lock = false;
		break;
	case 0x43:// ����			C key
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		lock = false;
		break;
	case 0x56:// ճ��			V key
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		lock = false;
		break;
	case 0x42:// ������			B key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keybd_event(0x33, 0, 0, 0);keybd_event(0x33, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x44:// �����			D key
		keyEvent(VK_END, 1);
		keyEvent(VK_LEFT, 1);
		keyEvent(VK_LEFT, 2);
		lock = false;
		break;
	case 0x4C:// ����1000			L key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_TAB, 10);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x59:// ����			
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RIGHT, 10);
		inputText("AU");
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x41:// A			A KEY
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 14);
		lock = false;
		break;
	case 0x57:// W1212			W key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_TAB, 6);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);

		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x32, 0, 0, 0);keybd_event(0x32, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x32, 0, 0, 0);keybd_event(0x32, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_DOWN, 1);
		lock = false;
		break;
	case VK_OEM_1:// ����		US standard keyboard, the ';:' key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 3);
		keyEvent(0x32, 1);
		keyEvent(VK_RETURN, 3);
		lock = false;
		break;
	case VK_F2:// FFF757			F key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x46:// FFF757			F key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x5A:// 1		�ĸ�	Z key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 3);
		keyEvent(0x31, 1);
		keyEvent(0x31, 1);
		keyEvent(VK_RETURN, 2);
		lock = false;
		break;
	case 0x53:// S			S key�ĸ�
		keyEvent(VK_HOME, 1);
		keyEvent(VK_PAUSE, 1);
		keyEvent(VK_RETURN, 3);

		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x4F:// O2323			O KEY
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_TAB, 6);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);

		keybd_event(0x32, 0, 0, 0);keybd_event(0x32, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x33, 0, 0, 0);keybd_event(0x33, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x32, 0, 0, 0);keybd_event(0x32, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x33, 0, 0, 0);keybd_event(0x33, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_DOWN, 1);
		lock = false;
		break;
	case 0x55:// U2323			U KEY
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_TAB, 6);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);

		keybd_event(0x32, 0, 0, 0);keybd_event(0x32, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x32, 0, 0, 0);keybd_event(0x32, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x32, 0, 0, 0);keybd_event(0x32, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x32, 0, 0, 0);keybd_event(0x32, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_DOWN, 1);
		lock = false;
		break;
	case 0x50:// P1818			P key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_TAB, 6);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);

		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x38, 0, 0, 0);keybd_event(0x38, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x38, 0, 0, 0);keybd_event(0x38, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_DOWN, 1);
		lock = false;

		break;
	case 0x51:// qq3030			Q key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_TAB, 6);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);

		keybd_event(0x33, 0, 0, 0);keybd_event(0x33, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x30, 0, 0, 0);keybd_event(0x30, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x33, 0, 0, 0);keybd_event(0x33, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x30, 0, 0, 0);keybd_event(0x30, 0, KEYEVENTF_KEYUP, 0);
		lock = false;
		break;
	case 0x49:// I1111			I key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_TAB, 6);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);

		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_DOWN, 1);
		lock = false;
		break;
	case 0x45:// E1313			E key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_TAB, 6);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);

		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x33, 0, 0, 0);keybd_event(0x33, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x33, 0, 0, 0);keybd_event(0x33, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_DOWN, 1);
		lock = false;
		break;

	case 0x47:// GGGG			G key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RETURN, 1);
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case 0x52:// R477			R KEY
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 17);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x34, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x37, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x37, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		lock = false;
		break;
	case VK_NUMPAD9:// 0100100299			F2 KEY
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keyEvent(0x33, 1);
		keyEvent(VK_RETURN, 1);

		inputText("010AO");
		keyEvent(VK_RETURN, 1);
		keyEvent(0x30, 1);
		keyEvent(0x31, 1);
		keyEvent(0x30, 2);
		keyEvent(0x31, 1);

		keyEvent(0x30, 2);
		keyEvent(0x32, 1);
		keyEvent(0x39, 2);
		lock = false;
		break;
	case VK_NUMPAD8:// 021FC			8 key
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keyEvent(0x33, 1);
		keyEvent(VK_RETURN, 1);
		inputText("021FC");
		keyEvent(VK_RETURN, 1);
		keyEvent(0x30, 1);
		keyEvent(0x32, 1);
		keyEvent(0x31, 1);
		keyEvent(0x36, 1);
		keyEvent(0x37, 4);
		keyEvent(0x35, 1);
		keyEvent(0x38, 1);
		lock = false;
		break;
	case VK_NUMPAD5:// 7550355168			5 KEY
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keyEvent(0x33, 1);
		keyEvent(VK_RETURN, 1);

		keyEvent(0x37, 1);
		keyEvent(0x35, 1);
		inputText("5JDP");
		keyEvent(VK_RETURN, 1);
		keyEvent(0x37, 1);
		keyEvent(0x35, 1);
		keyEvent(0x35, 1);
		keyEvent(0x30, 1);
		keyEvent(0x33, 1);
		keyEvent(0x35, 1);
		keyEvent(0x35, 1);
		keyEvent(0x31, 1);
		keyEvent(0x36, 1);
		keyEvent(0x38, 1);
		lock = false;
		break;
	case VK_NUMPAD6:// 7560582509			6 KEY
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keyEvent(0x33, 1);
		keyEvent(VK_RETURN, 1);

		inputText("E756A");
		keyEvent(VK_RETURN, 1);
		keyEvent(0x37, 1);
		keyEvent(0x35, 1);
		keyEvent(0x36, 1);
		keyEvent(0x30, 1);
		keyEvent(0x35, 1);
		keyEvent(0x38, 1);
		keyEvent(0x32, 1);
		keyEvent(0x35, 1);
		keyEvent(0x30, 1);
		keyEvent(0x39, 1);
		lock = false;
		break;
	case VK_NUMPAD1:// 7573030811			1 KEY
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 3);
		keyEvent(0x33, 1);
		keyEvent(VK_RETURN, 1);

		inputText("757EF");
		keyEvent(VK_RETURN, 1);
		keyEvent(0x37, 1);
		keyEvent(0x35, 1);
		keyEvent(0x37, 1);

		keyEvent(0x33, 1);
		keyEvent(0x30, 1);
		keyEvent(0x33, 1);
		keyEvent(0x30, 1);
		keyEvent(0x38, 1);
		keyEvent(0x31, 2);
		lock = false;
		break;
	case VK_NUMPAD0:// 1 1 0.1 0.1			0 KEY
		keyEvent(VK_HOME, 1);
		keyEvent(VK_TAB, 7);

		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);

		keybd_event(0x30, 0, 0, 0);keybd_event(0x30, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_OEM_PERIOD, 1);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x30, 0, 0, 0);keybd_event(0x30, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_OEM_PERIOD, 1);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		lock = false;
		break;
	case VK_NUMPAD3:// 0209488053			3 KEY
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keyEvent(0x33, 1);
		keyEvent(VK_RETURN, 1);

		inputText("020JH");
		keyEvent(VK_RETURN, 1);
		keyEvent(0x30, 1);
		keyEvent(0x32, 1);
		keyEvent(0x30, 1);
		keyEvent(0x39, 1);
		keyEvent(0x34, 1);
		keyEvent(0x38, 2);
		keyEvent(0x30, 1);
		keyEvent(0x35, 1);
		keyEvent(0x33, 1);

		lock = false;
		break;
	case VK_NUMPAD2:// 0215115383			2 KEY
		keyEvent(VK_ESCAPE, 1);
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keyEvent(0x33, 1);
		keyEvent(VK_RETURN, 1);

		inputText("021EC");
		keyEvent(VK_RETURN, 1);
		keyEvent(0x30, 1);
		keyEvent(0x32, 1);
		keyEvent(0x31, 1);
		keyEvent(0x35, 1);
		keyEvent(0x31, 2);
		keyEvent(0x35, 1);
		keyEvent(0x33, 1);
		keyEvent(0x38, 1);
		keyEvent(0x33, 1);
		lock = false;
		break;
	case VK_NUMPAD4:// 7573722214			4 key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x37, 0, 0, 0);keybd_event(0x37, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x35, 0, 0, 0);keybd_event(0x35, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x37, 0, 0, 0);keybd_event(0x37, 0, KEYEVENTF_KEYUP, 0);

		keybd_event(0x33, 0, 0, 0);keybd_event(0x33, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x37, 0, 0, 0);keybd_event(0x37, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x32, 0, 0, 0);keybd_event(0x32, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x32, 0, 0, 0);keybd_event(0x32, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x32, 0, 0, 0);keybd_event(0x32, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x34, 0, 0, 0);keybd_event(0x34, 0, KEYEVENTF_KEYUP, 0);

		lock = false;
		break;
	case VK_NUMPAD7:// 7570200072			7 key
		keyEvent(VK_HOME, 1);
		keyEvent(VK_RETURN, 3);
		keybd_event(0x31, 0, 0, 0);keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);
		keyEvent(VK_RETURN, 1);
		keyEvent(VK_RETURN, 1);
		keybd_event(0x37, 0, 0, 0);keybd_event(0x37, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x35, 0, 0, 0);keybd_event(0x35, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x37, 0, 0, 0);keybd_event(0x37, 0, KEYEVENTF_KEYUP, 0);

		keybd_event(0x30, 0, 0, 0);keybd_event(0x30, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x32, 0, 0, 0);keybd_event(0x32, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x30, 0, 0, 0);keybd_event(0x30, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x30, 0, 0, 0);keybd_event(0x30, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x30, 0, 0, 0);keybd_event(0x30, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x37, 0, 0, 0);keybd_event(0x37, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x32, 0, 0, 0);keybd_event(0x32, 0, KEYEVENTF_KEYUP, 0);
		lock = false;
		break;
	case VK_F11://����̼Ӻ�+++++++++�ͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½��ҿͻ��½�
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x43, 0, 0, 0);keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 200; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 120; //����������,��������
			shang = shang + 130;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(100);
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(0x56, 0, 0, 0);keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		Sleep(100);
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 260; //����������,��������
			shang = shang + 130;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	case VK_OEM_6://]]  }}}����̼�++�������  ���ǳ���
		hWnd = ::FindWindow(NULL, _T("��ֵ����¼�� F8 �˳�"));
		if (hWnd != NULL) {
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		hWnd = ::FindWindow(NULL, _T("��ѯδ��ӡͼƬ"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 20; //����������,��������
			shang = shang + 10;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		//*  �µ�
		//��ȡ����ڵ�����
		//CWnd *pwnd = ::FindWindow(_T("ExploreWClass"), NULL); //ϣ���ҵ���Դ������
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			zuo = lParam->left;
			//int you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			zuo = zuo + 20; //����������,��������
			shang = shang + 40;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			shang = shang + 60;//��������,��������
			SetCursorPos(zuo, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		Sleep(200);
		hWnd = ::FindWindow(NULL, _T("ͼƬ��ϵͳ-��������-6.9.1"));
		if (hWnd != NULL) {  //hWnd != NULL��ʾ���ڴ��ڡ������ڵ��ж���hWnd == NULL
			::GetWindowRect(hWnd, lParam);
			//int zuo = lParam->left;
			you = lParam->right;
			shang = lParam->top;
			//int xia = lParam->bottom;
			you = you - 1220; //����������,��������
			shang = shang + 700;//��������,��������
			SetCursorPos(you, shang);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		lock = false;
		break;
	}
	return lock;
}