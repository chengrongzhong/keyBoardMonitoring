// ketthProjectDlg.cpp : 实现文件
#include "stdafx.h"
#include "ketthProject.h"
#include "ketthProjectAction.h"
#include "ketthProjectDlg.h"
#include "afxdialogex.h"
#include <iostream> 
#include <stdlib.h> 
#include <stdio.h> 
#include <list>
#include <map>
#include <array>
#include <list>
#include <string>
#include <numeric>
#include <algorithm>
#include <fstream>
#include <iomanip>

using namespace std;

#define WM_SHOWTASK WM_USER+101
#define ID_END      0x4000
#define ID_START    0x4001
#define ID_START_2    0x4002

#define ID_SORTCUT			0x5001
#define ID_SORTCUT_STOP		0x5002
#define ID_SORTCUT_FS		0x5003
#define ID_SORTCUT_HZ		0x5004
#define ID_SORTCUT_5		0x5005
#define ID_SORTCUT_GX		0x5006
#define ID_SORTCUT_SWITCH	0x5007
#define ID_SORTCUT_SWITCH_1	0x5008
#define ID_SORTCUT_SWITCH_2	0x5009
#define ID_SORTCUT_SWITCH_3	0x5010
#define ID_SORTCUT_BK1		0x5011
#define ID_SORTCUT_BK2		0x5012
#define ID_SORTCUT_BK3		0x5013
#define ID_YICILURU		0x5014
#define ID_DISANFANG	0x5015


#define ID_ACTION1	 0X9001
#define ID_ACTION2   0X9002
#define ID_ACTION3   0X9003
#define ID_ACTION4   0X9004
#define ID_ACTION5   0X9005
#define ID_ACTION6   0X9006
#define ID_ACTION7   0X9007
#define ID_ACTION8   0X9008
#define ID_ACTION9   0X9009
#define ID_ACTION10  0X9010
#define ID_ACTION11  0X9011
#define ID_ACTION12  0X9012
#define ID_ACTION13  0X9013
#define ID_ACTION14  0X9014
#define ID_ACTION15  0X9015
#define ID_ACTION16  0X9016
#define ID_ACTION17  0X9017
#define ID_ACTION18  0X9018
#define ID_ACTION19  0X9019
#define ID_ACTION20  0X9020
#define ID_ACTION21  0X9021
#define ID_ACTION22  0X9022
#define ID_ACTION23  0X9023
#define ID_ACTION24  0X9024
#define ID_ACTION25  0X9025
#define ID_ACTION26  0X9026
#define ID_ACTION27  0X9027
#define ID_ACTION28  0X9028
#define ID_ACTION29  0X9029

#define ID_AUTOREM1 0X3001
#define ID_AUTOREM2 0X3002
#define ID_AUTOREM3 0X3003

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

boolean isStart = true;
boolean lock = false;
boolean shiftDown = false;
boolean ctrlDown = false;
boolean altDown = false;
boolean numSortCut = false;
boolean yiciSortCut = false;
boolean disanfang = false;
boolean saveNum = false;
boolean switching = false;
boolean switchin9key = false;
int nowAction = 10;//默认脚本号码  默认脚本号码默认脚本号码默认脚本号码默认脚本号码默认脚本号码默认脚本号码默认脚本号码默认脚本号码默认脚本号码默认脚本号码默认脚本号码默认脚本号码默认脚本号码默认脚本号码
int nowSortCut = 2;//默认开启的月结10就是没有 2就是佛山
int autoRem = 0;//电话这里要改1 月结改2
boolean passConfrim = false;
KetthProjectAction *action;
boolean hasSwitch9 = false;
int hasSwitch9value = 10;

// 下面开始按键功能
//-------------------------------------------------------------------
HHOOK m_hkeyboard;    //键盘底层钩子句柄
HWND topWnd;
HWND ketthWnd;
NOTIFYICONDATA m_nid;

HMODULE GetCurrentModule()
{
#if _MSC_VER < 1300    // earlier than .NET compiler (VC 6.0)

	// Here's a trick that will get you the handle of the module
	// you're running in without any a-priori knowledge:
	MEMORY_BASIC_INFORMATION mbi;
	static int dummy;
	VirtualQuery(&dummy, &mbi, sizeof(mbi));

	return reinterpret_cast<HMODULE>(mbi.AllocationBase);
#else    // VC 7.0
	// from ATL 7.0 sources
	return reinterpret_cast<HMODULE>(&__ImageBase);
#endif
}

bool isNumCode(int keyValue) {
	if (keyValue >= 0x30 && keyValue <= 0x39) {
		return true;
	}

	if (keyValue >= VK_NUMPAD0 && keyValue <= VK_NUMPAD9) {
		return true;
	}
	return false;
}

// _判断二次月结启动按键
boolean isSortCutStartKey(int keyValue) {//这里下面是加月结二次的按键4位的
	boolean result = false;
	if (keyValue == VK_ADD || keyValue == VK_OEM_PERIOD || keyValue == VK_OEM_COMMA || keyValue == 0x45 || keyValue == 0x47 || keyValue == 0x4B || keyValue == 0x53 || keyValue == VK_OEM_4 || keyValue == VK_MULTIPLY || keyValue == 0x46 || keyValue == 0x5A || keyValue == VK_F2 || keyValue == VK_F9 || keyValue == VK_NEXT || keyValue == 0x43) {
		result = true;
	}
	return result;
}


// _判断二次月结启动分类
BOOLEAN isSortCutType(int nowSortCut) {
	if (nowSortCut == 2) {
		return true;
	}
	return false;
}

// _判断月结启动
void isSortCutStart(int nowSortCut, int keyValue) {
	if (numSortCut) {
		return;
	}
	if (isSortCutStartKey(keyValue)) {
		numSortCut = isSortCutType(nowSortCut);
	}
}

// _判断一次启动按键
boolean isYiciStartKey(int keyValue) {//这里下面是加月结一次的按键4位的
	boolean result = false;
	/*if (keyValue == VK_ADD || keyValue == VK_OEM_PERIOD || keyValue == VK_OEM_COMMA || keyValue == 0x45 || keyValue == 0x47 || keyValue == 0x4B || keyValue == 0x53 || keyValue == VK_OEM_4 || keyValue == VK_MULTIPLY || keyValue == 0x46 || keyValue == 0x5A || keyValue == VK_F2 || keyValue == VK_F9 || keyValue == VK_NEXT || keyValue == 0x43) {
		result = true;
	}*/
	return result;
}

// _判断一次启动分类
BOOLEAN isYiciStartType(int nowSortCut) {
	if (nowSortCut == 8) {
		return true;
	}
	return false;
}

void isYiciluru(int nowSortCut, int KeyValue) {
	if (yiciSortCut) {
		return;
	}
	if (isYiciStartKey(KeyValue)) {
		yiciSortCut = isYiciStartType(nowSortCut);
	}
}

// _判断第三方启动按键
boolean isDisanfangStartKey(int keyValue) {//这里下面是加月结三方的按键4位的
	boolean result = false;
	if (keyValue == 0x42) {
		result = true;
	}
	return result;
}

// _判断第三方启动分类
BOOLEAN isDisanfangStartType(int numSortCut) {
	if (numSortCut == 9) {
		return true;;
	}
	return false;
}

void isDisanfang(int nowSortCut, int KeyValue) {
	if (disanfang) {
		return;
	}

	if (isDisanfangStartKey(KeyValue)) {
		disanfang = isDisanfangStartType(nowSortCut);
	}
}

int getNumByCode(int keyValue) {
	switch (keyValue) {
	case 0x30:return 0;
	case 0x31:return 1;
	case 0x32:return 2;
	case 0x33:return 3;
	case 0x34:return 4;
	case 0x35:return 5;
	case 0x36:return 6;
	case 0x37:return 7;
	case 0x38:return 8;
	case 0x39:return 9;
	case VK_NUMPAD0:return 0;
	case VK_NUMPAD1:return 1;
	case VK_NUMPAD2:return 2;
	case VK_NUMPAD3:return 3;
	case VK_NUMPAD4:return 4;
	case VK_NUMPAD5:return 5;
	case VK_NUMPAD6:return 6;
	case VK_NUMPAD7:return 7;
	case VK_NUMPAD8:return 8;
	case VK_NUMPAD9:return 9;
	}
	return NULL;
}

void isSaveNumStart(int keyValue) {
	if (!isNumCode(keyValue) && keyValue != VK_BACK) {
		saveNum = false;
		action->saveNum.clear();
		return;
	}
	if (saveNum && action->fitToWrite()) {
		return;
	}
	int num = getNumByCode(keyValue);
	action->saveNum.push_back(num);
	if (action->saveNum.size() == 3) {
		if (action->fitToWrite()) {
			saveNum = true;
			action->saveNum.pop_back();
			return;
		}
		else {
			saveNum = false;
			action->saveNum.pop_front();
			return;
		}
	}
	else {
		saveNum = false;
		return;
	}
}

BOOL phoneNumAction(int keyValue) {
	if (!isNumCode(keyValue) && keyValue != VK_BACK) {
		action->phoneNum.clear();
		return TRUE;
	}
	if (keyValue == VK_BACK) {
		if (action->phoneNum.size() > 0) {
			action->phoneNum.pop_back();
			return TRUE;
		}
	}
	int num = getNumByCode(keyValue);
	action->phoneNum.push_back(num);
	if (action->isMobilePhoneNum()) {
		if (action->phoneNum.size() == 11) {
			action->mobilePhoneAction(keyValue);
			action->phoneNum.clear();
			return FALSE;
		}
	}

	else if (action->is400PhoneNum()) {
	}

	//下面是固话打8位修改7就是7位自动带出☆☆★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★
	else {
		if (action->phoneNum.size() == 8) {
			if (action->is7TelPhoneNum()) {
				action->shortTelPhoneAction(keyValue);
				action->phoneNum.clear();
			}
			else {
				action->telPhoneAction(keyValue);
				action->phoneNum.clear();
			}
			return FALSE;
		}
	}
	if (action->phoneNum.size() > 11) {
		action->phoneNum.clear();
	}
	return TRUE;
}

LRESULT CketthProjectDlg::OnHotKey(WPARAM wParam, LPARAM lParam)
{
	KetthProjectAction::resetMutikey();
	if (wParam == ID_START || wParam == ID_START_2) {
		if (isStart) {
			StopText();
			isStart = false;
		}
		else {
			isStart = true;
		}
	}
	if (wParam == ID_SORTCUT) {
		numSortCut = true;
		
	}
	if (wParam == ID_SORTCUT_STOP) {
		nowSortCut = 10;
		SortCutStopText();
	}
	if (wParam == ID_SORTCUT_GX) {
		nowSortCut = 1;
		SortCutStartText();
	}
	if (wParam == ID_SORTCUT_FS) {
		nowSortCut = 2;
		SortCutStartText();
	}
	if (wParam == ID_SORTCUT_HZ) {
		nowSortCut = 3;
		SortCutStartText();
	}
	if (wParam == ID_SORTCUT_BK1) {
		nowSortCut = 4;
		SortCutStartText();
	}
	if (wParam == ID_SORTCUT_BK2) {
		nowSortCut = 5;
		SortCutStartText();
	}
	if (wParam == ID_SORTCUT_BK3) {
		nowSortCut = 6;
		SortCutStartText();
	}
	if (wParam == ID_SORTCUT_5) {
		nowSortCut = 7;
		SortCutStartText();
	}
	if (wParam == ID_YICILURU) {
		nowSortCut = 8;
		SortCutStartText();
	}
	if (wParam == ID_DISANFANG) {
		nowSortCut = 9;
		SortCutStartText();
	}
	if (wParam == ID_SORTCUT_SWITCH || wParam == ID_SORTCUT_SWITCH_1 || wParam == ID_SORTCUT_SWITCH_2 || wParam == ID_SORTCUT_SWITCH_3) {
		switchin9key = true;
		if (isSortCutType(nowSortCut)) {
			action->switchSortCut(nowSortCut);
		}
		switchin9key = false;
		return 0;
	}
	if (wParam == ID_AUTOREM1) {
		if (autoRem == 1) {
			autoRem = 0;
		}
		else {
			autoRem = 1;
		}
		autoRemText();
	}
	if (wParam == ID_AUTOREM2) {
		if (autoRem == 2) {
			autoRem = 0;
		}
		else {
			autoRem = 2;
		}
		autoRemText();
	}
	if (wParam == ID_AUTOREM3) {
		if (autoRem == 3) {
			autoRem = 0;
		}
		else {
			autoRem = 3;
		}
		autoRemText();
	}
	if (wParam == ID_END) {
		StopText();
		isStart = false;
	}
	if (wParam == ID_ACTION1) {
		nowAction = 1;
		isStart = true;
		nowSortCut = 2;
		SortCutStartText();
		autoRem = 2;
		autoRemText();
	}
	if (wParam == ID_ACTION2) {
		nowAction = 2;
		isStart = true;
		autoRem = 0;
		autoRemText();
		nowSortCut = 10;
		SortCutStopText();
	}
	if (wParam == ID_ACTION3) {
		nowAction = 3;
		isStart = true;
		nowSortCut = 1;
		SortCutStartText();
		autoRem = 2;
		autoRemText();
	}
	if (wParam == ID_ACTION4) {
		nowAction = 4;
		isStart = true;
		nowSortCut = 2;
		SortCutStartText();
		autoRem = 2;
		autoRemText();
	}
	if (wParam == ID_ACTION5) {
		nowAction = 5;
		isStart = true;
		autoRem = 2;
		autoRemText();
		nowSortCut = 10;
		SortCutStopText();
	}
	if (wParam == ID_ACTION6) {
		nowAction = 6;
		isStart = true;
		autoRem = 1;
		autoRemText();
		nowSortCut = 10;
		SortCutStopText();
	}
	if (wParam == ID_ACTION7) {
		nowAction = 7;
		isStart = true;
		autoRem = 2;
		autoRemText();
		nowSortCut = 10;
		SortCutStopText();
	}
	if (wParam == ID_ACTION8) {
		nowAction = 8;
		isStart = true;
		autoRem = 2;
		autoRemText();
		nowSortCut = 8;
		SortCutStartText();
	}
	if (wParam == ID_ACTION9) {
		nowAction = 9;
		isStart = true;
		autoRem = 0;
		autoRemText();
		nowSortCut = 10;
		SortCutStopText();
	}
	if (wParam == ID_ACTION10) {
		nowAction = 10;
		isStart = true;
     	nowSortCut = 2;
		SortCutStartText();
		autoRem = 2;
		autoRemText();
	}
	if (wParam == ID_ACTION11) {
		nowAction = 11;
		isStart = true;
		nowSortCut = 3;
		SortCutStartText();
		autoRem = 2;
		autoRemText();
	}
	if (wParam == ID_ACTION12) {
		nowAction = 12;
		isStart = true;
		autoRem = 2;
		autoRemText();
	}
	if (wParam == ID_ACTION13) {
		nowAction = 13;
		isStart = true;
		autoRem = 2;
		autoRemText();
	}
	if (wParam == ID_ACTION14) {
		nowAction = 14;
		isStart = true;
		autoRem = 2;
		autoRemText();
		nowSortCut = 2;
		SortCutStartText();
	}
	if (wParam == ID_ACTION15) {
		nowAction = 15;
		isStart = true;
		autoRem = 2;
		autoRemText();
		nowSortCut = 2;
		SortCutStartText();
	}
	if (wParam == ID_ACTION16) {
		nowAction = 16;
		isStart = true;
		nowSortCut = 10;
		SortCutStartText();
		autoRem = 1;
		autoRemText();
	}
	if (wParam == ID_ACTION17) {
		nowAction = 17;
		isStart = true;
		autoRem = 2;
		autoRemText();

//17是附加整单 18是文字
	}
	if (wParam == ID_ACTION18) {
		nowAction = 18;
		isStart = true;
		autoRem = 1;
		autoRemText();
	}
	if (wParam == ID_ACTION19) {
		nowAction = 19;
		isStart = true;
		autoRem = 2;
		autoRemText();
	}
	if (wParam == ID_ACTION20) {
		nowAction = 20;
		isStart = true;
		autoRem = 2;
		autoRemText();
	}
	if (wParam == ID_ACTION21) {
		nowAction = 21;
		isStart = true;
		nowSortCut = 10;
		SortCutStopText();
		autoRem = 0;
		autoRemText();
	}
	if (wParam == ID_ACTION22) {
		nowAction = 22;
		isStart = true;
		nowSortCut = 1;
		SortCutStartText();
		autoRem = 2;
		autoRemText();
	}
	if (wParam == ID_ACTION23) {
		nowAction = 23;
		isStart = true;
		nowSortCut = 2;
		SortCutStartText();
		autoRem = 2;
		autoRemText();
	}
	if (wParam == ID_ACTION24) {
		nowAction = 24;
		isStart = true;
		nowSortCut = 2;
		SortCutStartText();
		autoRem = 2;
		autoRemText();
	}
	if (wParam == ID_ACTION25) {
		nowAction = 25;
		isStart = true;
		nowSortCut = 2;
		SortCutStartText();
		autoRem = 2;
		autoRemText();
	}
	if (wParam == ID_ACTION26) {
		nowAction = 26;
		isStart = true;
		nowSortCut = 2;
		SortCutStartText();
		autoRem = 2;
		autoRemText();
	}
	if (wParam == ID_ACTION27) {
		nowAction = 27;
		isStart = true;
		nowSortCut = 2;
		SortCutStartText();
		autoRem = 2;
		autoRemText();
	}
	if (wParam == ID_ACTION28) {
		nowAction = 28;
		isStart = true;
		autoRem = 1;
		autoRemText();
		nowSortCut = 10;
		SortCutStopText();
	}
	if (wParam == ID_ACTION29) {
		nowAction = 29;
		isStart = true;
		nowSortCut = 2;
		SortCutStartText();
		autoRem = 2;
		autoRemText();
	}
	if (isStart) {
		switch (nowAction) {
		case 1:status.SetWindowText(L"回单");break;
		case 2:status.SetWindowText(L"公共");break;
		case 3:status.SetWindowText(L"清ニ");break;//广西二次
		case 4:status.SetWindowText(L"清ニ");break;//佛山二次
		case 5:status.SetWindowText(L"QC");break;
		case 6:status.SetWindowText(L"寄方");break;
		case 7:status.SetWindowText(L"_整z_");break;
		case 8:status.SetWindowText(L"没有脚本");break;
		case 9:status.SetWindowText(L"香港");break;
		case 10:status.SetWindowText(L"ketth");break;
		case 11:status.SetWindowText(L"ニ2");break;//清二iko
		case 12:status.SetWindowText(L"托一");break;
		case 13:status.SetWindowText(L"托二");break;
		case 14:status.SetWindowText(L"回单");break;
		case 15:status.SetWindowText(L"回ニ");break;//回二iko
		case 16:status.SetWindowText(L"K文");break;
		case 17:status.SetWindowText(L"整公");break;
		case 18:status.SetWindowText(L"整文_");break;
		case 19:status.SetWindowText(L"Ye");break;//文字
		case 20:status.SetWindowText(L"Ye");break;//附加
		case 21:status.SetWindowText(L"第三方内");break;
		case 22:status.SetWindowText(L"第三方月结");break;
		case 23:status.SetWindowText(L"收方");break;//嘉明他们用的收方
		case 24:status.SetWindowText(L"附加"); break;//嘉明他们用的附加
		case 25:status.SetWindowText(L"10 16 29一起的增值 "); break;
		case 26:status.SetWindowText(L"☆附"); break;//附加
		case 27:status.SetWindowText(L"☆附"); break;//文字
		case 28:status.SetWindowText(L"穷哥"); break;
		case 29:status.SetWindowText(L"换附加一直"); break;

		}
	}
	return 0;
}
int remSort = 0;


void switchAction(int keyValue) {
	//HWND hWnd = ::FindWindow(NULL, _T("ketth"));
	//CketthProjectDlg dlg = CketthProjectDlg::FromHandle(hWnd);
	//CketthProjectDlg dlg = AfxGetMainWnd();
	if (nowAction == 10) {
		// K +VK_ADD keyValue == 0x57 || keyValue == 0x4F || keyValue == 0x55 || keyValue == 0x49 || keyValue == 0x45 || keyValue == 0x4B || 
		if (keyValue == 0x4B || keyValue == 0x50 || keyValue == 0x57 || keyValue == 0x4F || keyValue == 0x55 || keyValue == 0x49 || keyValue == 0x45 || keyValue == VK_F1 || keyValue == VK_ADD || keyValue == VK_OEM_2)
		{
			KetthProjectAction::resetMutikey();
			nowAction = 16;
			isStart = true;
			// 切换月结(10关闭 1广西 2佛山 3惠州	nowSortCut = 10;
			autoRem = 1;   //(0关 1电话 2月结
			return;
		}
		// 当10分类按到F（0x46）键的时候，月结跳转到一次
		//if (keyValue == 0x46 || keyValue == VK_F2 || keyValue == VK_OEM_PERIOD) {
			//nowSortCut = 8;
	//	}
		// 当10分类按到B（0x42）键的时候，月结跳转到3方
		if (keyValue == 0x42) {
			nowSortCut = 9;
		}
		if (keyValue == 0x46) {
			nowSortCut = 2;
		}
	}
	if (nowAction == 16) {
		if (keyValue == VK_F10)
		{
			KetthProjectAction::resetMutikey();
			nowAction = 29;
			isStart = true;
			// 切换月结(10关闭 1广西 2佛山 3惠州	nowSortCut = 10;
			autoRem = 2;   //(0关 1电话 2月结
			return;
		}
	}
	if (nowAction == 29) {
		if (keyValue == VK_F1)
		{
			KetthProjectAction::resetMutikey();
			nowAction = 16;
			isStart = true;
			// 切换月结(10关闭 1广西 2佛山 3惠州	nowSortCut = 10;
			autoRem = 1;   //(0关 1电话 2月结
			return;
		}
	}
	if (nowAction == 10) {
		// N键4E
		if (keyValue == 0x4E)
		{
			KetthProjectAction::resetMutikey();
			nowAction = 25;
			isStart = true;
			// 切换月结(10关闭 1广西 2佛山 3惠州	nowSortCut = 10;
			autoRem = 2;   //(0关 1电话 2月结
			return;
		}
	}
	if (nowAction == 25) {
		// K +VK_ADD
		if (keyValue == 0x34 || keyValue == 0x36 || keyValue == 0x41 || keyValue == 0x33 || keyValue == 0x32 || keyValue == 0x53 || keyValue == 0x31 || keyValue == 0x35 || keyValue == VK_F1 || keyValue == 0x30 || keyValue == 0x57 || keyValue == 0x59 || keyValue == 0x46 || keyValue == 0x55 || keyValue == 0x45 || keyValue == 0x52)

		{
			KetthProjectAction::resetMutikey();
			nowAction = 10;
			isStart = true;
			// 切换月结(10关闭 1广西 2佛山 3惠州	nowSortCut = 10;
			autoRem = 2;   //(0关 1电话 2月结
			return;
		}
	}
	if (nowAction == 25) {
		if (keyValue == VK_F1)

		{
			KetthProjectAction::resetMutikey();
			nowAction = 16;
			isStart = true;
			// 切换月结(10关闭 1广西 2佛山 3惠州	nowSortCut = 10;
			autoRem = 1;   //(0关 1电话 2月结
			return;
		}
	}
	if (nowAction == 10) {
		// K +VK_ADD
		if (keyValue == 0x58)
		{
			KetthProjectAction::resetMutikey();
			nowAction = 8;
			isStart = true;
			// 切换月结(10关闭 1广西 2佛山 3惠州	nowSortCut = 10;
			autoRem = 2;   //(0关 1电话 2月结
			return;
		}
	}
	if (nowAction == 8) {
		// K +VK_ADD
		if (keyValue == VK_F5 || keyValue == VK_RETURN || keyValue == VK_F2 || keyValue == VK_OEM_PERIOD || keyValue == VK_OEM_1 || keyValue == 0x5A || keyValue == VK_NUMPAD0 || keyValue == VK_NUMPAD1 || keyValue == VK_NUMPAD2 || keyValue == VK_NUMPAD3 || keyValue == VK_NUMPAD4 || keyValue == VK_NUMPAD5 || keyValue == VK_NUMPAD6 | keyValue == VK_NUMPAD7 || keyValue == VK_NUMPAD8 || keyValue == VK_NUMPAD9)
			
		{
			KetthProjectAction::resetMutikey();
			nowAction = 10;
			isStart = true;
			// 切换月结(10关闭 1广西 2佛山 3惠州	nowSortCut = 10;
			autoRem = 2;   //(0关 1电话 2月结
			return;
		}
	}
	if (nowAction == 8) {
		// K +VK_ADD
		if (keyValue == VK_F1 )

		{
			KetthProjectAction::resetMutikey();
			nowAction = 16;
			isStart = true;
			// 切换月结(10关闭 1广西 2佛山 3惠州	nowSortCut = 10;
			autoRem = 1;   //(0关 1电话 2月结
			return;
		}
	}

    if (nowAction == 16) {
		if (keyValue == VK_OEM_PERIOD || keyValue == VK_F9 || keyValue == VK_OEM_COMMA || keyValue == VK_F2 || keyValue == VK_F6 || keyValue == VK_OEM_1)
		{
			KetthProjectAction::resetMutikey();
			nowAction = 10;
			isStart = true;
			autoRem = 2;
			return;
	//	}
		//if (keyValue == 0x46 || keyValue == VK_F2 || keyValue == VK_OEM_PERIOD) {
			//nowSortCut = 8;
		}
	}
	//转内件三★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★
	if (nowAction == 16) {
		// K +VK_ADD
		if (keyValue == VK_F1 )
		{
			KetthProjectAction::resetMutikey();
			nowAction = 21;
			isStart = true;
			autoRem = 2;
			return;
		}
	}
	if (nowAction == 10) {
		// K +VK_ADD
		if (keyValue == VK_F5)
		{
			KetthProjectAction::resetMutikey();
			nowAction = 21;
			isStart = true;
			autoRem = 2;
			return;
		}
	}
	if (nowAction == 21) {
		if (keyValue == VK_F1 || keyValue == 0x4D || keyValue == 0x51 || keyValue == 0x44 || keyValue == VK_NUMPAD9 || keyValue == VK_NUMPAD8 || keyValue == 0x31 || keyValue == VK_NUMPAD4|| keyValue == 0x34 || keyValue == 0x38 || keyValue == 0x39 || keyValue == 0x48 || keyValue == 0x32 || keyValue == 0x4B || keyValue == 0x41 || keyValue == 0x4A || keyValue == 0x45 || keyValue == 0x4E || keyValue == 0x47 || keyValue == 0x46|| keyValue == 0x4C)
		{
			KetthProjectAction::resetMutikey();
			nowAction = 10;
			isStart = true;
			autoRem = 2;
			return;
		}
	}
	if (nowAction == 21) {
			if (keyValue == VK_F1)
			{
				KetthProjectAction::resetMutikey();
				nowAction = 16;
				isStart = true;
				autoRem = 2;
				return;
			}
	}
	//转内件三★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★
	//转第三方ままままままままままままままままままままままままままままままままままままままままままままままままままままままままままままままままままままままま
	if (nowAction == 16) {
		// K +VK_ADD
		if (keyValue == 0x5A)
		{
			KetthProjectAction::resetMutikey();
			nowAction = 22;
			isStart = true;
			autoRem = 2;
			return;
		}
	}

	if (nowAction == 10) {
		// K +VK_ADD
		if (keyValue == 0x5A)
		{
			KetthProjectAction::resetMutikey();
			nowAction = 22;
			isStart = true;
			autoRem = 2;
			return;
		}
	}
	if (nowAction == 22) {
		if (keyValue == 0x48 || keyValue == 0x51 || keyValue == 0x4D || keyValue == VK_NUMPAD1 ||keyValue == 0x38 || keyValue == VK_F6 || keyValue == VK_NUMPAD6 || keyValue == 0x56 || keyValue == 0x4B || keyValue == VK_NUMPAD9 || keyValue == 0x36 || keyValue == 0x4D || keyValue == VK_NUMPAD0 || keyValue == VK_F2 || keyValue == 0x4A || keyValue == VK_NUMPAD3 || keyValue == VK_NUMPAD2 || keyValue == 0x42 || keyValue == 0x41 || keyValue == 0x39 || keyValue == 0x50 || keyValue == 0x46 || keyValue == 0x45 || keyValue == 0x31 || keyValue == 0x33 || keyValue == 0x30 || keyValue == 0x43 || keyValue == 0x34 || keyValue == 0x32 || keyValue == 0x35 || keyValue == 0x51 || keyValue == 0x54 || keyValue == 0x44)
		{
			KetthProjectAction::resetMutikey();
			nowAction = 10;
			isStart = true;
			autoRem = 2;
			return;
		}
	}
	if (nowAction == 22) {
		if (keyValue == VK_F1)
		{
			KetthProjectAction::resetMutikey();
			nowAction = 16;
			isStart = true;
			autoRem = 1;
			return;
		}
	}
	//转第三方まままままままままままままままままままままままままままままままままままままままままままままままままままままままままままままままままま
	//下面是YEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYE
	if (nowAction == 20) {
		// W 0x57 S 0x53 X 0x58  /  VK_DIVIDE  *  VK_MULTIPLY   D 0x44   Z 0x5A   

		if (keyValue == VK_F1 || keyValue == 0x57 || keyValue == 0x53 || keyValue == 0x58 || keyValue == 0x44 || keyValue == 0x49 || keyValue == 0x4F || keyValue == 0x50)
		{
			KetthProjectAction::resetMutikey();
			nowAction = 19;
			isStart = true;
			autoRem = 2;
			return;


		}
	}
	if (nowAction == 19) {
		//  + VK_ADD  F2 VK_F2  F1 VK_F1 VK_OEM_1 
		if (keyValue == VK_F2 || keyValue == VK_F1 || keyValue == VK_ADD || keyValue == 0x5A || keyValue == VK_OEM_1)
		{
			KetthProjectAction::resetMutikey();
			nowAction = 20;
			isStart = true;
			autoRem = 2;
			return;


		}
	}
	//YEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYEYE
	if (nowAction == 17) {
		// W  O  U  I  E  K +VK_ADD公共
		if (keyValue == VK_F1 || keyValue == 0x57 || keyValue == 0x4F || keyValue == 0x55 || keyValue == 0x49 || keyValue == 0x45 || keyValue == 0x4B || keyValue == VK_ADD || keyValue == VK_OEM_2)
		{
			KetthProjectAction::resetMutikey();
			nowAction = 18;
			isStart = true;
			autoRem = 0;
			return;
			//dlg.SortCutStopText();
			//dlg.autoRemText();
			//dlg.status.SetWindowText(L"_G_");下面是文字
		}
	}
    if (nowAction == 18) {
		if (keyValue == VK_OEM_PERIOD || keyValue == VK_OEM_COMMA || keyValue == VK_F2 ||keyValue == VK_OEM_1 || keyValue == 0x5A)
		{
			KetthProjectAction::resetMutikey();
			nowAction = 17;
			isStart = true;
			autoRem = 2;
			return;

		}
	}
	//新H的
	if (nowAction == 27) {
		// R  P
		if (keyValue == VK_MULTIPLY || keyValue == VK_DIVIDE || keyValue == VK_OEM_COMMA || keyValue == 0x31 || keyValue == VK_F2 || keyValue == VK_ADD || keyValue == VK_OEM_3)
		{
			KetthProjectAction::resetMutikey();
			nowAction = 26;
			isStart = true;
			autoRem = 2;
			return;
			//dlg.SortCutStopText();
			//dlg.autoRemText();
			//dlg.status.SetWindowText(L"_G_");
		}
	}
	if (nowAction == 26) {
		if (keyValue == VK_OEM_PERIOD || keyValue == VK_F1 || keyValue == VK_DIVIDE || keyValue == VK_ADD || keyValue == 0x41 || keyValue == 0x51 || keyValue == 0x43 ||  keyValue == VK_MULTIPLY)
		{
			KetthProjectAction::resetMutikey();
			nowAction = 27;
			isStart = true;
			autoRem = 2;
			return;
			//dlg.SortCutStartText();
			//dlg.autoRemText();
			//dlg.status.SetWindowText(L"_X_");
		}
	}
	//下面是嘉明和叼丝他们用的
	if (nowAction == 24) {
		// R  P
		if (keyValue == VK_F1 || keyValue == VK_ADD || keyValue == VK_DOWN)
		{
			KetthProjectAction::resetMutikey();
			nowAction = 23;
			isStart = true;
			autoRem = 2;
			return;
			//dlg.SortCutStopText();
			//dlg.autoRemText();
			//dlg.status.SetWindowText(L"_G_");
		}
	}
	if (nowAction == 23) {
		if ( keyValue == VK_F9 || keyValue == VK_OEM_4 || keyValue == VK_DIVIDE || keyValue == VK_MULTIPLY || keyValue == VK_OEM_2 || keyValue == VK_OEM_3 || keyValue == VK_F2)
		{
			KetthProjectAction::resetMutikey();
			nowAction = 24;
			isStart = true;
			autoRem = 2;
			return;
			//dlg.SortCutStartText();
			//dlg.autoRemText();
			//dlg.status.SetWindowText(L"_X_");
		}
	}
	//上面是嘉明和叼丝他 们用的.....................
	//6是寄方别动她
	if (nowAction == 6) {
		// R  P
		if (keyValue == VK_F1 || keyValue == VK_OEM_1 || keyValue == VK_OEM_2 || keyValue == VK_ADD || keyValue == VK_DOWN)
		{
			KetthProjectAction::resetMutikey();
			nowAction = 6;
			isStart = true;
			autoRem = 1;
			nowSortCut = 10;
			return;
			//dlg.SortCutStopText();
			//dlg.autoRemText();
			//dlg.status.SetWindowText(L"_G_");
		}
	}
	//下面托寄物12...13类
	if (nowAction == 12) {
		if (keyValue == VK_F1 || keyValue == VK_OEM_3)
		{
			KetthProjectAction::resetMutikey();
			nowAction = 13;
			isStart = true;
			autoRem = 2;
			return;
			//dlg.SortCutStopText();
			//dlg.autoRemText();
			//dlg.status.SetWindowText(L"_G_");
		}
	}
	if (nowAction == 12) {
		if (keyValue == VK_F2)
		{
			KetthProjectAction::resetMutikey();
			nowAction = 9;
			isStart = true;
			autoRem = 2;
			return;
			//dlg.SortCutStopText();
			//dlg.autoRemText();
			//dlg.status.SetWindowText(L"_G_");
		}
	}
	if (nowAction == 13) {
		if (keyValue == VK_F2)
		{
			KetthProjectAction::resetMutikey();
			nowAction = 9;
			isStart = true;
			autoRem = 2;
			return;
			//dlg.SortCutStopText();
			//dlg.autoRemText();
			//dlg.status.SetWindowText(L"_G_");
		}
	}
	if (nowAction == 9) {
		if (keyValue == VK_F9)
		{
			KetthProjectAction::resetMutikey();
			nowAction = 12;
			isStart = true;
			autoRem = 2;
			return;
			//dlg.SortCutStopText();
			//dlg.autoRemText();
			//dlg.status.SetWindowText(L"_G_");
		}
	}

    if (nowAction == 13) {
		if (keyValue == VK_F1)
		{
			KetthProjectAction::resetMutikey();
			nowAction = 12;
			isStart = true;
			autoRem = 2;
			return;
			//dlg.SortCutStartText();
			//dlg.autoRemText();
			//dlg.status.SetWindowText(L"_X_");
		}
	}
}

boolean isContentWindows() {
	//获取最前端窗口
	HWND hWnd1 = NULL;
	HWND hWnd2 = NULL;
	HWND hWnd3 = NULL;
	HWND hWnd4 = NULL;
	HWND hWnd5 = NULL;
	HWND hWnd6 = NULL;
	HWND hWnd7 = NULL;
	HWND hWnd8 = NULL;
	HWND hWnd9 = NULL;
	hWnd1 = ::FindWindow(NULL, _T("图片打单系统-生产环境-6.9.1"));
	hWnd2 = ::FindWindow(NULL, _T("查询未打印图片"));
	hWnd3 = ::FindWindow(NULL, _T("增值服务录入 F8 退出"));
	hWnd4 = ::FindWindow(NULL, _T("提示"));
	hWnd5 = ::FindWindow(NULL, _T("图片输单系统"));
	hWnd6 = ::FindWindow(NULL, _T("消息"));
	hWnd7 = ::FindWindow(NULL, _T("责任界定"));
	hWnd8 = ::FindWindow(NULL, _T("Microsoft Excel - Book1.xls"));
	hWnd9 = ::GetForegroundWindow();
	if (hWnd1 != hWnd9 && hWnd2 != hWnd9 && hWnd3 != hWnd9 && hWnd4 != hWnd9 && hWnd5 != hWnd9 && hWnd6 != hWnd9 && hWnd7 != hWnd9 && hWnd8 != hWnd9) {
		return false;
	}
	return true;
}

boolean statusCheckStep1(WPARAM wParam, LPARAM lParam) {
	PKBDLLHOOKSTRUCT kbstruct;
	if (!isStart || !passConfrim) {
		return false;
	}
	if (WM_KEYUP == wParam && shiftDown)
	{
		kbstruct = (PKBDLLHOOKSTRUCT)lParam;
		if (kbstruct->vkCode == VK_LSHIFT || kbstruct->vkCode == VK_RSHIFT) {
			shiftDown = false;
		}
		return false;
	}
	if (WM_KEYUP == wParam && ctrlDown)
	{
		kbstruct = (PKBDLLHOOKSTRUCT)lParam;
		if (kbstruct->vkCode == VK_LCONTROL || kbstruct->vkCode == VK_RCONTROL) {
			ctrlDown = false;
		}
		return false;
	}
	if (WM_KEYUP == wParam && altDown)
	{
		kbstruct = (PKBDLLHOOKSTRUCT)lParam;
		if (kbstruct->vkCode == VK_MENU) {
			altDown = false;
		}
		return false;
	}
	return true;
}

boolean statusCheckStep2(WPARAM wParam, LPARAM lParam) {
	PKBDLLHOOKSTRUCT kbstruct = (PKBDLLHOOKSTRUCT)lParam;
	if (kbstruct->vkCode == VK_LSHIFT || kbstruct->vkCode == VK_RSHIFT) {
		lock = false;
		shiftDown = true;
		return false;
	}
	if (kbstruct->vkCode == VK_LCONTROL || kbstruct->vkCode == VK_RCONTROL) {
		lock = false;
		ctrlDown = true;
		return false;
	}
	if (kbstruct->vkCode == VK_MENU) {
		lock = false;
		altDown = true;
		return false;
	}
	return true;
}

void numSortCutSwitch(int nowAction, int numSortCut, int nowSortCut, int keyCode) {
	boolean sortcutnumA = !numSortCut && isSortCutType(nowSortCut);
	boolean yiciluruA = !yiciSortCut && isYiciStartType(nowSortCut);
	boolean disanfangA = !disanfang && isDisanfangStartType(nowSortCut);
	if ((yiciluruA || sortcutnumA || disanfangA) && !switchin9key && action->isSwitching(nowSortCut)) {
		boolean goSwitch = false;
		int goSwitchChoice = 0;
		if (keyCode == 0x32 || keyCode == VK_NUMPAD2) {
			goSwitch = true;
			goSwitchChoice = 1;
		}
		else if (keyCode == 0x33 || keyCode == VK_NUMPAD3) {
			goSwitch = true;
			goSwitchChoice = 2;
		}
		else if (keyCode == 0x34 || keyCode == VK_NUMPAD4) {
			goSwitch = true;
			goSwitchChoice = 3;
		}
		else if (keyCode == 0x35 || keyCode == VK_NUMPAD5) {
			goSwitch = true;
			goSwitchChoice = 4;
		}
		else if (keyCode == 0x36 || keyCode == VK_NUMPAD6) {
			goSwitch = true;
			goSwitchChoice = 5;
		}
		else if (keyCode == 0x37 || keyCode == VK_NUMPAD7) {
			goSwitch = true;
			goSwitchChoice = 6;
		}
		else if (keyCode == 0x38 || keyCode == VK_NUMPAD8) {
			goSwitch = true;
			goSwitchChoice = 7;
		}
		else if (keyCode == 0x39 || keyCode == VK_NUMPAD9) {
			goSwitch = true;
			goSwitchChoice = 8;
		}

		if (goSwitch) {
			hasSwitch9 = true;
			switchin9key = true;
			action->saveNum.clear();
			hasSwitch9value = 10;
			lock = false;
			switchin9key = action->choiceSortCut(nowSortCut, goSwitchChoice);
		}
	}
}

void autoRemNumFunction(int keyValue) {
	// 监控电话
	if (autoRem == 1)
	{
		lock = phoneNumAction(keyValue);
	}
	// 监控月结
	if (autoRem == 2)
	{
		// 月结号自动保存
		isSaveNumStart(keyValue);
		if (saveNum && !hasSwitch9) {
			if (isNumCode(keyValue)) {
				int num = getNumByCode(keyValue);
				action->saveNum.push_back(num);
				if (action->saveNum.size() == 10) {
					lock = action->writeNumber();
					saveNum = false;
				}
			}
			if (keyValue == VK_BACK) {
				if (action->saveNum.size() > 0) {
					action->saveNum.pop_back();
				}
				if (action->saveNum.size() == 0) {
					saveNum = false;
				}
			}
		}
	}
	// 监控一次录入
	if (autoRem == 3)
	{
		// 月结号自动保存
		isSaveNumStart(keyValue);
		if (saveNum && !hasSwitch9) {
			if (isNumCode(keyValue)) {
				int num = getNumByCode(keyValue);
				action->saveNum.push_back(num);
				if (action->saveNum.size() == 10) {
					lock = action->writeYiciluru(keyValue);
					saveNum = false;
				}
			}
			if (keyValue == VK_BACK) {
				if (action->saveNum.size() > 0) {
					action->saveNum.pop_back();
				}
				if (action->saveNum.size() == 0) {
					saveNum = false;
				}
			}
		}
	}
}

void keyboardStartSortCut(int keyValue) {
	if (keyValue == VK_BACK) {
		if (action->numlist.size() > 0) {
			action->numlist.pop_back();
		}
	}
	else if (isNumCode(keyValue)) {
		int key = 0;
		int num = getNumByCode(keyValue);
		if (action->numlist.size() == 4) {
			action->numlist.pop_front();
		}
		action->numlist.push_back(num);
		if (action->numlist.size() == 4) {
			action->switchList.clear();
			for (list<int>::iterator i = action->numlist.begin(); i != action->numlist.end(); i++) {
				action->switchList.push_back(*i);
			}
			lock = action->sortCut(nowSortCut);
			if (!lock) {
				action->numlist.clear();
				numSortCut = false;
			}
		}
	}
	else {
		action->numlist.clear();
		numSortCut = false;
	}
}

void keyboardStartYiciluru(int keyValue) {
	if (keyValue == VK_BACK) {
		if (action->yiciluru.size() > 0) {
			action->yiciluru.pop_back();
		}
	}
	else if (isNumCode(keyValue)) {
		int key = 0;
		int num = getNumByCode(keyValue);
		if (action->yiciluru.size() == 4) {
			action->yiciluru.pop_front();
		}
		action->yiciluru.push_back(num);
		if (action->yiciluru.size() == 4) {
			action->switchList.clear();
			for (list<int>::iterator i = action->yiciluru.begin(); i != action->yiciluru.end(); i++) {
				action->switchList.push_back(*i);
			}
			lock = action->yiciKeySortCut();
			if (!lock) {
				action->yiciluru.clear();
				yiciSortCut = false;
			}
		}
	}
	else {
		action->yiciluru.clear();
		yiciSortCut = false;
	}
}

void keyboardStartDisanfang(int keyValue) {
	if (keyValue == VK_BACK) {
		if (action->disanfang.size() > 0) {
			action->disanfang.pop_back();
		}
	}
	else if (isNumCode(keyValue)) {
		int key = 0;
		int num = getNumByCode(keyValue);
		if (action->disanfang.size() == 4) {
			action->disanfang.pop_front();
		}
		action->disanfang.push_back(num);
		if (action->disanfang.size() == 4) {
			action->switchList.clear();
			for (list<int>::iterator i = action->disanfang.begin(); i != action->disanfang.end(); i++) {
				action->switchList.push_back(*i);
			}
			lock = action->disanfangKeySortCut();
			if (!lock) {
				action->disanfang.clear();
				disanfang = false;

			
			}
		}
	}
	else {
		action->disanfang.clear();
		disanfang = false;
	}
}

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	PKBDLLHOOKSTRUCT kbstruct = (PKBDLLHOOKSTRUCT)lParam;
	/*if (!isContentWindows()) {
		return CallNextHookEx(m_hkeyboard, nCode, wParam, lParam);
	}*/

	if (!statusCheckStep1(wParam, lParam)) {
		return CallNextHookEx(m_hkeyboard, nCode, wParam, lParam);
	}

	if (WM_KEYDOWN == wParam && !lock && !shiftDown && !ctrlDown)
	{
		lock = true;
		if (!statusCheckStep2(wParam, lParam)) {
			return CallNextHookEx(m_hkeyboard, nCode, wParam, lParam);
		}
		
 		autoRemNumFunction(kbstruct->vkCode);
		
		numSortCutSwitch(nowAction, numSortCut, nowSortCut, kbstruct->vkCode);

		// 一次录入模块_
		if (yiciSortCut && isYiciStartType(nowSortCut) && !switchin9key && autoRem != 1) {
			keyboardStartYiciluru(kbstruct->vkCode);
		}
		else {
			action->yiciluru.clear();
			yiciSortCut = false;
		}

		// 第三方模块_
		if (disanfang && isDisanfangStartType(nowSortCut) && !switchin9key && autoRem != 1) {
			keyboardStartDisanfang(kbstruct->vkCode);
		}
		else {
			action->disanfang.clear();
			disanfang = false;
		}

		// 快捷输入上面是加侯选字母月结的1
		// 月结输入模块_
		if (numSortCut && isSortCutType(nowSortCut) && !switchin9key && autoRem != 1) {
			keyboardStartSortCut(kbstruct->vkCode);
		}
		else {
			action->numlist.clear();
			numSortCut = false;
		}

		if (hasSwitch9 && hasSwitch9value < 1)
		{
			action->saveNum.clear();
			hasSwitch9 = false;
		}
		else if (hasSwitch9) {
			hasSwitch9value--;
		}

		switch (nowAction) {
		case 1:lock = KetthProjectAction::keyAction1(kbstruct, lock);break;
		case 2:lock = KetthProjectAction::keyAction2(kbstruct, lock);break;
		case 3:lock = KetthProjectAction::keyAction3(kbstruct, lock);break;
		case 4:lock = KetthProjectAction::keyAction4(kbstruct, lock);break;
		case 5:lock = KetthProjectAction::keyAction5(kbstruct, lock);break;
		case 6:lock = KetthProjectAction::keyAction6(kbstruct, lock);break;
		case 7:lock = KetthProjectAction::keyAction7(kbstruct, lock);break;
		case 8:lock = KetthProjectAction::keyAction8(kbstruct, lock);break;
		case 9:lock = KetthProjectAction::keyAction9(kbstruct, lock);break;
		case 10:lock = KetthProjectAction::keyAction10(kbstruct, lock);break;
		case 11:lock = KetthProjectAction::keyAction11(kbstruct, lock);break;
		case 12:lock = KetthProjectAction::keyAction12(kbstruct, lock);break;
		case 13:lock = KetthProjectAction::keyAction13(kbstruct, lock);break;
		case 14:lock = KetthProjectAction::keyAction14(kbstruct, lock);break;
		case 15:lock = KetthProjectAction::keyAction15(kbstruct, lock);break;
		case 16:lock = KetthProjectAction::keyAction16(kbstruct, lock);break;
		case 17:lock = KetthProjectAction::keyAction17(kbstruct, lock);break;
		case 18:lock = KetthProjectAction::keyAction18(kbstruct, lock);break;
		case 19:lock = KetthProjectAction::keyAction19(kbstruct, lock);break;
		case 20:lock = KetthProjectAction::keyAction20(kbstruct, lock);break;
		case 21:lock = KetthProjectAction::keyAction21(kbstruct, lock);break;
		case 22:lock = KetthProjectAction::keyAction22(kbstruct, lock);break;
		case 23:lock = KetthProjectAction::keyAction23(kbstruct, lock);break;
		case 24:lock = KetthProjectAction::keyAction24(kbstruct, lock); break;
		case 25:lock = KetthProjectAction::keyAction25(kbstruct, lock); break;
		case 26:lock = KetthProjectAction::keyAction26(kbstruct, lock); break;
		case 27:lock = KetthProjectAction::keyAction27(kbstruct, lock); break;
		case 28:lock = KetthProjectAction::keyAction28(kbstruct, lock); break;
		case 29:lock = KetthProjectAction::keyAction29(kbstruct, lock); break;
		}

		switchAction(kbstruct->vkCode);
		isSortCutStart(nowSortCut, kbstruct->vkCode);
		isYiciluru(nowSortCut, kbstruct->vkCode);
		isDisanfang(nowSortCut, kbstruct->vkCode);
		if (lock) {
			lock = false;
			return CallNextHookEx(m_hkeyboard, nCode, wParam, lParam);
		}
		else {
			return 1;
		}
	}
	return CallNextHookEx(m_hkeyboard, nCode, wParam, lParam);
}

//void CketthProjectDlg::delWritenLine() {
//	string line;
//	// open input file
//	ifstream in("NewAddYueJie.txt");
//	if (!in.is_open())
//	{
//		cout << "Input file failed to open\n";
//		return;
//	}
//	// now open temp output file
//	ofstream out("outfile.txt");
//	// loop to read/write the file.  Note that you need to add code here to check
//	// if you want to write the line
//	while (getline(in, line))
//	{
//		if (line != "I want to delete this line")
//			out << line << "\n";
//	}
//	in.close();
//	out.close();
//	// delete the original file
//	remove("NewAddYueJie.txt");
//	// rename old to new
//	rename("outfile.txt", "NewAddYueJie.txt");
//	// all done!
//}

void CketthProjectDlg::StopText()
{
	status.SetWindowText(L"OFF");
}

void CketthProjectDlg::SortCutStopText()
{
	CStatic *pStatic = (CStatic*)GetDlgItem(IDC_STATIC1);
	pStatic->SetWindowText(L"暂停ALT+1");
	numSortCut = false;
}

void CketthProjectDlg::SortCutStartText()
{
	CStatic *pStatic = (CStatic*)GetDlgItem(IDC_STATIC1);
	if (nowSortCut == 1) {
		pStatic->SetWindowText(L"№广西※");
	}
	if (nowSortCut == 2) {
		pStatic->SetWindowText(L"№佛山※");
	}
	if (nowSortCut == 3) {
		pStatic->SetWindowText(L"№惠州※");
	}
	if (nowSortCut == 4) {
		pStatic->SetWindowText(L"№深圳※");
	}
	if (nowSortCut == 5) {
		pStatic->SetWindowText(L"№云南※");
	}
	if (nowSortCut == 6) {
		pStatic->SetWindowText(L"№574※");
	}
	if (nowSortCut == 7) {
		pStatic->SetWindowText(L"月结五位");
	}
	if (nowSortCut == 8) {
		pStatic->SetWindowText(L"一次录入");
	}
	if (nowSortCut == 9) {
		pStatic->SetWindowText(L"第三方");
	}
	// numSortCut = true;
}

void CketthProjectDlg::autoRemText()
{
	CStatic *pStatic = (CStatic*)GetDlgItem(IDC_STATIC2);
	if (autoRem == 0) {
		pStatic->SetWindowText(L"监控：OFF");
	}
	if (autoRem == 1) {
		pStatic->SetWindowText(L"固话：手机");
	}
	if (autoRem == 2) {
		pStatic->SetWindowText(L"监控：月结");
	}
	if (autoRem == 3) {
		pStatic->SetWindowText(L"监控：一次");
	}
	// numSortCut = true;
}


HBRUSH CketthProjectDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if (pWnd->m_hWnd == status.m_hWnd && !isStart)
	{
		//pDC->SetBkColor(RGB(0,0,0));
		pDC->SetTextColor(RGB(255, 0, 0));
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)brush;
	}
	return   hbr;

}

LRESULT CketthProjectDlg::OnShowTask(WPARAM wParam, LPARAM lParam)

{

	if (wParam != IDR_MAINFRAME)
		return 1;

	switch (lParam)
	{
	case WM_RBUTTONUP: // 右键起来时弹出菜单
	{
		LPPOINT lpoint = new tagPOINT;
		::GetCursorPos(lpoint); // 得到鼠标位置
		CMenu menu;
		menu.CreatePopupMenu(); // 声明一个弹出式菜单
		menu.AppendMenu(MF_STRING, WM_DESTROY, L"关闭");
		menu.TrackPopupMenu(TPM_LEFTALIGN, lpoint->x, lpoint->y, this);
		HMENU hmenu = menu.Detach();
		menu.DestroyMenu();
		delete lpoint;
	}
	break;

	case WM_LBUTTONDBLCLK: // 双击左键的处理

	{
		this->ShowWindow(SW_SHOWNORMAL); // 显示主窗口
		SetForegroundWindow();
	}
	break;
	}

	return 0;

}
BOOL CketthProjectDlg::DestroyWindow()
{

	// TODO: Add your specialized code here and/or call the base class

	// 在托盘区删除图标

	Shell_NotifyIcon(NIM_DELETE, &m_nid);

	return CDialog::DestroyWindow();

}

void CketthProjectDlg::OnSize(UINT nType, int cx, int cy)
{

	CDialog::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here

	if (nType == SIZE_MINIMIZED)
	{
		ShowWindow(SW_HIDE); // 当最小化市，隐藏主窗口 
	}

}

//-------------------------------------------------------------------

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

														// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

}


BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CketthProjectDlg 对话框



CketthProjectDlg::CketthProjectDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_KETTHPROJECT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hkeyboard = NULL;
}

void CketthProjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATUS, status);
	DDX_Control(pDX, IDC_EDIT2, m_edit);
}

BEGIN_MESSAGE_MAP(CketthProjectDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
	ON_MESSAGE(WM_SHOWTASK, OnShowTask)
	ON_WM_SIZE()

	//ON_BN_CLICKED(IDC_BUTTON1, &CketthProjectDlg::OnBnClickedOk)

	ON_MESSAGE(WM_HOTKEY, OnHotKey)
	ON_BN_CLICKED(IDC_BUTTON1, &CketthProjectDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON1, &CketthProjectDlg::OnOK)
//	ON_EN_CHANGE(IDC_EDIT2, &CketthProjectDlg::OnEnChangeEdit2)
ON_STN_CLICKED(IDC_STATUS, &CketthProjectDlg::OnStnClickedStatus)
ON_STN_CLICKED(IDC_STATIC1, &CketthProjectDlg::OnStnClickedStatic1)
END_MESSAGE_MAP()


// CketthProjectDlg 消息处理程序

BOOL CketthProjectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	viewControl(false);
	m_edit.SetPasswordChar('*');

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	// TODO: 在此添加额外的初始化代码
	//---------------------------托盘显示---------------------------------//

	m_nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
	m_nid.hWnd = this->m_hWnd;
	m_nid.uID = IDR_MAINFRAME;
	m_nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	m_nid.uCallbackMessage = WM_SHOWTASK; // 自定义的消息名称
	m_nid.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
	Shell_NotifyIcon(NIM_ADD, &m_nid); // 在托盘区添加图标
	//设置timer时间，监控启动状态
	SetTimer(1, 10, NULL);
	autoRemText();

	// 注册热键
	RegisterHotKey(m_hWnd, ID_END, MOD_CONTROL, 0x54);	//关闭   T键
	RegisterHotKey(m_hWnd, ID_START, MOD_CONTROL, 0x31);//启动	RegisterHotKey(m_hWnd, ID_START,0, VK_SCROLL);//启动

	/*RegisterHotKey(m_hWnd, ID_START_2, MOD_ALT, 0x31);*///启动

	RegisterHotKey(m_hWnd, ID_ACTION1, MOD_CONTROL, VK_NUMPAD7);//回单	7键
	RegisterHotKey(m_hWnd, ID_ACTION2, MOD_CONTROL, 0x44);//公共信息		D键
	RegisterHotKey(m_hWnd, ID_ACTION3, MOD_CONTROL, 0x32);//二次		2键
	RegisterHotKey(m_hWnd, ID_ACTION4, MOD_CONTROL, 0x45);//二次757		E键
	RegisterHotKey(m_hWnd, ID_ACTION5, MOD_CONTROL, 0x51);//QC			Q键
	RegisterHotKey(m_hWnd, ID_ACTION6, MOD_CONTROL, 0x4A);//寄方		J键
	RegisterHotKey(m_hWnd, ID_ACTION7, MOD_CONTROL, 0x5A);//清单整		Z键
	RegisterHotKey(m_hWnd, ID_ACTION8, MOD_CONTROL, 0x42);//		B键
	RegisterHotKey(m_hWnd, ID_ACTION9, MOD_CONTROL, 0x52);//		R键
	RegisterHotKey(m_hWnd, ID_ACTION10, MOD_CONTROL, 0x39);//		9键
	RegisterHotKey(m_hWnd, ID_ACTION11, MOD_CONTROL, VK_NUMPAD2);//	2键小键盘VK_NUMPAD6
	RegisterHotKey(m_hWnd, ID_ACTION12, MOD_CONTROL, 0x57);//		W键 托寄物
	RegisterHotKey(m_hWnd, ID_ACTION13, MOD_CONTROL, 0x4F);//		O键 托寄物2
	RegisterHotKey(m_hWnd, ID_ACTION14, MOD_CONTROL, 0x34);//		4键  回单
	RegisterHotKey(m_hWnd, ID_ACTION15, MOD_CONTROL, 0x48);//		H键  回单2次
	RegisterHotKey(m_hWnd, ID_ACTION16, MOD_CONTROL, 0x46);//		F键
	RegisterHotKey(m_hWnd, ID_ACTION17, MOD_CONTROL, VK_NUMPAD8);//	8键 小键盘 公共整单
	RegisterHotKey(m_hWnd, ID_ACTION18, MOD_CONTROL, 0x47);//		H键
	RegisterHotKey(m_hWnd, ID_ACTION19, MOD_CONTROL, 0x59);//		Y键
	RegisterHotKey(m_hWnd, ID_ACTION20, MOD_CONTROL, 0x35);//		5键
	//RegisterHotKey(m_hWnd, ID_ACTION21, MOD_CONTROL, 0x36);//		6键
	//RegisterHotKey(m_hWnd, ID_ACTION22, MOD_CONTROL, VK_NUMPAD6);//		6键小键盘
	RegisterHotKey(m_hWnd, ID_ACTION23, MOD_CONTROL, 0x53);//		S 嘉明他们的收
	RegisterHotKey(m_hWnd, ID_ACTION24, MOD_CONTROL, VK_NUMPAD4);//		4键小键盘
	RegisterHotKey(m_hWnd, ID_ACTION27, MOD_CONTROL, 0x33);//		3键
	RegisterHotKey(m_hWnd, ID_ACTION28, MOD_CONTROL, 0x4B);//		K键
	RegisterHotKey(m_hWnd, ID_SORTCUT_STOP, MOD_ALT, 0x54);//		T键
	RegisterHotKey(m_hWnd, ID_SORTCUT, MOD_ALT, 0x37);//			7键
	RegisterHotKey(m_hWnd, ID_SORTCUT_FS, MOD_ALT, 0x46);//			F键
	RegisterHotKey(m_hWnd, ID_SORTCUT_HZ, MOD_ALT, 0x44);//			D键
	RegisterHotKey(m_hWnd, ID_SORTCUT_GX, MOD_ALT, 0x58);//			X键广西月结
	RegisterHotKey(m_hWnd, ID_SORTCUT_5, MOD_ALT, 0x35);//			5键
	RegisterHotKey(m_hWnd, ID_YICILURU, MOD_ALT, 0x38);  //			一次录入月结
	RegisterHotKey(m_hWnd, ID_SORTCUT_BK1, MOD_ALT, 0x53);//			S键 深圳
	RegisterHotKey(m_hWnd, ID_SORTCUT_BK2, MOD_ALT, 0x39);//			9键 云南月结
	RegisterHotKey(m_hWnd, ID_SORTCUT_BK3, MOD_ALT, 0x30);//			0键 574月结
	//RegisterHotKey(m_hWnd, ID_SORTCUT_SWITCH_1, 0, VK_F5);//	   F5    切换月结
	RegisterHotKey(m_hWnd, ID_SORTCUT_SWITCH_1, 0, VK_OEM_7);//	   回车左边    切换月结
	RegisterHotKey(m_hWnd, ID_SORTCUT_SWITCH_2, 0, VK_SUBTRACT);//			小键-     切换月结
	//RegisterHotKey(m_hWnd, ID_SORTCUT_SWITCH_3, 0, VK_F11);//			F11键     切换月结

	RegisterHotKey(m_hWnd, ID_AUTOREM1, MOD_ALT, 0x31);//			1键开关电话
	RegisterHotKey(m_hWnd, ID_AUTOREM2, MOD_ALT, 0x32);//			2键开关月结
	RegisterHotKey(m_hWnd, ID_AUTOREM3, MOD_ALT, 0x34);//			4键开关一次
	RegisterHotKey(m_hWnd, ID_DISANFANG, MOD_ALT, 0x33);  //	第三方月结

	HWND hWnd = NULL;
	hWnd = ::FindWindow(NULL, _T("图片打单系统-生产环境-6.9.1"));
	/*if (hWnd == NULL) {
		MessageBox(_T("生产环境未匹配，将推出程序。"), _T("警告"), MB_OK);
		SendMessage(WM_CLOSE);
	}*/

	action = new KetthProjectAction();
	if (action->dsfnum > 0) {
		CString msg1 = _T("第三方月结数据重复！！！重复个数：");
		CString msg2;
		msg2.Format(_T("%d"), action->dsfnum);
		CString msg3 = _T("重复的月结数据：");
		CString msg4;
		msg4.Format(_T("%s"), action->dsfstr);;

		MessageBox((msg1 + msg2), _T("警告"), MB_OK);
		SendMessage(WM_CLOSE);
	}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

//void CketthProjectDlg::OnBnClickedOk() {
//	CEdit* pBoxOne;
//	pBoxOne = (CEdit*)GetDlgItem(IDC_EDIT1);
//	//赋值
//	//pBoxOne-> SetWindowText( _T("FOO ") );
//	//取值
//	CString str;
//	pBoxOne->GetWindowText(str);
//	MessageBox(str, _T("程序运行结果"), MB_OK);
//	str.ReleaseBuffer();
//
//}

void CketthProjectDlg::viewControl(bool canSee) {
	if (canSee) {
		GetDlgItem(IDC_STATUS)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC3)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON1)->ShowWindow(SW_HIDE);
		passConfrim = true;
	}
	else {
		GetDlgItem(IDC_STATUS)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC2)->ShowWindow(SW_HIDE);
		passConfrim = false;
	}
}

void CketthProjectDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CketthProjectDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CketthProjectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CketthProjectDlg::PreTranslateMessage(MSG* pMsg)
{
	//if (WM_KEYDOWN == pMsg->message && VK_RETURN == pMsg->wParam)
	//{
	//	if (GetFocus() == GetDlgItem(IDC_EDIT2))  //根据不同控件焦点判断是那个在执行
	//	{
	//		MessageBox(_T("ad111sf"));
	//	}

	//	MessageBox(_T("adsf"));
	//	return 0; //这里必须返回0 否则运行报错
	//}
	if (pMsg->message == WM_KEYDOWN&&pMsg->wParam == VK_ESCAPE)
		return TRUE;
	return CDialog::PreTranslateMessage(pMsg);
}

void CketthProjectDlg::OnBnClickedButton1()
{
	OnOK();
}
void CketthProjectDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_hkeyboard)
	{
		CDialog::OnTimer(nIDEvent);
		return;
	}

	m_font.CreateFont(22, 0, 0, 0, FW_BLACK, FALSE, FALSE,
		FALSE, GB2312_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		FIXED_PITCH | FF_MODERN, _T("宋体"));
	status.SetWindowText(L"寄方");
	status.SetFont(&m_font);
	m_hkeyboard = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, GetCurrentModule(), 0);
	if (NULL == m_hkeyboard)
	{
		AfxMessageBox(L"失败！");
	}
	CDialog::OnTimer(nIDEvent);
}
void CketthProjectDlg::OnOK()
{
	// TODO: 在此添加控件通知处理程序代码
	CEdit* pBoxOne;
	pBoxOne = (CEdit*)GetDlgItem(IDC_EDIT2);
	//赋值
	//pBoxOne-> SetWindowText( _T("FOO ") );
	//取值
	CString str;

	pBoxOne->GetWindowText(str);
	if (str == "ketth") {
		/*
		//______________________________________________________
		//获取活动窗口的坐标

		topWnd = ::GetActiveWindow();
		LPRECT lParam = new RECT;
		::GetWindowRect(topWnd, lParam);
		
		//ScreenToClient(lParam);
		int zuo = lParam->left;
		int you = lParam->right;
		int shang = lParam->top;
		int xia = lParam->bottom;
		you = you - 20; //减就是向左,加是向右
		shang = shang + 10;//加是向下,减是向上
		SetCursorPos(you, shang);
		//mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
		//mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		//--------------------------------------------------------
		
		//MessageBox(_T("验证成功！1" + l), _T("11"), MB_OK);
		//MessageBox(_T("验证成功！2" + r), _T("22"), MB_OK);
		*/
		viewControl(true);
	}
	else {
		MessageBox(_T("验证失败，请重新验证。"), _T("验证结果"), MB_OK);
	}
	str.ReleaseBuffer();
}

//void CketthProjectDlg::OnEnChangeEdit2()
//{
//	// TODO:  如果该控件是 RICHEDIT 控件，它将不
//	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
//	// 函数并调用 CRichEditCtrl().SetEventMask()，
//	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
//
//	// TODO:  在此添加控件通知处理程序代码
//}


void CketthProjectDlg::OnStnClickedStatus()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CketthProjectDlg::OnStnClickedStatic1()
{
	// TODO: 在此添加控件通知处理程序代码
}
