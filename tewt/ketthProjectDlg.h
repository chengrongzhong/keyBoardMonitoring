
// ketthProjectDlg.h : 头文件
//
#include "KetthProjectAction.h"
#include <list>
#pragma once

using namespace std;
// CketthProjectDlg 对话框
class CketthProjectDlg : public CDialogEx
{
// 构造
public:
	CketthProjectDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_KETTHPROJECT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	LRESULT OnShowTask(WPARAM wParam, LPARAM lParam);
	BOOL DestroyWindow();
	void viewControl(bool canSee);

public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void StopText();
	void SortCutStopText();
	void SortCutStartText();
	void autoRemText();
	//void switchAction(int keyValue);
	afx_msg LRESULT OnHotKey(WPARAM wParam, LPARAM lParam);
	//LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
	CStatic status;
	CStatic status1;
	CBrush brush;
	CFont m_font;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnOK();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	char* password = "XXX";//密码在那边DLG.CPP那里了1123行
	// this is m_edit// this is m_edit
	CEdit m_edit;
	afx_msg void OnStnClickedStatus();
	afx_msg void OnStnClickedStatic1();
};
