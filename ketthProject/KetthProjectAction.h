#include <map>
#include <list>
#include <array>
using namespace std;

#pragma once
class KetthProjectAction
{
public:
	KetthProjectAction();
	~KetthProjectAction();
	static BOOL keyAction1(PKBDLLHOOKSTRUCT kbstruct, boolean lock);
	static BOOL keyAction2(PKBDLLHOOKSTRUCT kbstruct, boolean lock);
	static BOOL keyAction3(PKBDLLHOOKSTRUCT kbstruct, boolean lock);
	static BOOL keyAction4(PKBDLLHOOKSTRUCT kbstruct, boolean lock);
	static BOOL keyAction5(PKBDLLHOOKSTRUCT kbstruct, boolean lock);
	static BOOL keyAction6(PKBDLLHOOKSTRUCT kbstruct, boolean lock);
	static BOOL keyAction7(PKBDLLHOOKSTRUCT kbstruct, boolean lock);
	static BOOL keyAction8(PKBDLLHOOKSTRUCT kbstruct, boolean lock);
	static BOOL keyAction9(PKBDLLHOOKSTRUCT kbstruct, boolean lock);
	static BOOL keyAction10(PKBDLLHOOKSTRUCT kbstruct, boolean lock);
	static BOOL keyAction11(PKBDLLHOOKSTRUCT kbstruct, boolean lock);
	static BOOL keyAction12(PKBDLLHOOKSTRUCT kbstruct, boolean lock);
	static BOOL keyAction13(PKBDLLHOOKSTRUCT kbstruct, boolean lock);
	static BOOL keyAction14(PKBDLLHOOKSTRUCT kbstruct, boolean lock);
	static BOOL keyAction15(PKBDLLHOOKSTRUCT kbstruct, boolean lock);
	static BOOL keyAction16(PKBDLLHOOKSTRUCT kbstruct, boolean lock);
	static BOOL keyAction17(PKBDLLHOOKSTRUCT kbstruct, boolean lock);
	static BOOL keyAction18(PKBDLLHOOKSTRUCT kbstruct, boolean lock);
	static BOOL keyAction19(PKBDLLHOOKSTRUCT kbstruct, boolean lock);
	static BOOL keyAction20(PKBDLLHOOKSTRUCT kbstruct, boolean lock);
	static BOOL keyAction21(PKBDLLHOOKSTRUCT kbstruct, boolean lock);
	static BOOL keyAction22(PKBDLLHOOKSTRUCT kbstruct, boolean lock);
	static BOOL keyAction23(PKBDLLHOOKSTRUCT kbstruct, boolean lock);
	static BOOL keyAction24(PKBDLLHOOKSTRUCT kbstruct, boolean lock);
	static BOOL keyAction25(PKBDLLHOOKSTRUCT kbstruct, boolean lock);
	static BOOL keyAction26(PKBDLLHOOKSTRUCT kbstruct, boolean lock);
	static BOOL keyAction27(PKBDLLHOOKSTRUCT kbstruct, boolean lock);
	static BOOL keyAction28(PKBDLLHOOKSTRUCT kbstruct, boolean lock);
	static BOOL keyAction29(PKBDLLHOOKSTRUCT kbstruct, boolean lock);
	BOOL sortCut(int sortCutType);
	BOOL isSwitching(int sortCutType);
	void switchSortCut(int sortCutType);
	BOOL choiceSortCut(int sortCutType, int choice);
	BOOL writeNumber();
	BOOL writeYiciluru(int keyValue);
	BOOL fitToWrite();
	BOOL isMobilePhoneNum();
	BOOL is400PhoneNum();
	BOOL is7TelPhoneNum();
	BOOL yiciKeySortCut();
	BOOL disanfangKeySortCut();
	static void resetMutikey();
	void mobilePhoneAction(int keyValue);
	void telPhoneAction(int keyValue);
	void shortTelPhoneAction(int keyValue);
	void inputShortPhoneNum();

	map<int, string> new_foshanSortCut;
	map<int, string> new_guangxiSortCut;
	map<int, string> HZSortCut;
	map<int, string> BackupSortCut1;
	map<int, string> BackupSortCut2;
	map<int, string> BackupSortCut3;
	map<int, string> tempOneAndThree;
	map<string, string> tempDiSanFang;
	//{"757ak":{321:"7577654321"}, "757bd":{432:"7578765432,7579876432"}}
	map<string, map<int, string>> oneAndThreeSortCut;
	//{321:{"7577677321":"757ak"}, 432:{"7578765432":"757ak", "7579876432":"757bd"}}
	map<int, map<string, string>> diSanFangSortCut;
	string dsfstr = "";
	int dsfnum = 0;
	list<int> switchList;
	list<int> numlist;
	list<int> yiciluru;
	list<int> disanfang;
	list<int> saveNum;
	list<int> phoneNum;
};

static array<int, 25> writeHead = {
	757,
	10,
	20,
	21,
	871,
	879,
	878,
	877,
	876,
	873,
	874,
	752,
	755,
	760,
	769,
	771,
	772,
	773,
	775,
	776,
	762,
	852,
	774,
	574,
	571,
};
