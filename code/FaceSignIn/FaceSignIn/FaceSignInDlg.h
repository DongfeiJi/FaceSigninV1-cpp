
// FaceSignInDlg.h : ͷ�ļ�
//

#pragma once
#include <opencv2/core/core.hpp>  
#include <opencv2/imgproc/imgproc.hpp>  
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include "afxwin.h"

#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include <dlib/opencv.h>

#include <iostream>

#include "face_recognition_lib.h"

using namespace dlib;
using namespace cv;
using namespace std;


// CFaceSignInDlg �Ի���
class CFaceSignInDlg : public CDialogEx
{
// ����
public:
	CFaceSignInDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FACESIGNIN_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:

	afx_msg void OnBnClickedBtnVideoopen();
	afx_msg void OnBnClickedBtnVideoclose();
	bool m_flag;
	bool m_bdetect;
	bool m_brectangle;
	bool m_btrack;
	bool m_brecognition;
	bool m_beye;
	bool m_bmouth;
	VideoCapture m_capture;
	cv::Mat m_dst;
	//



	//������������ε�
	//image_window m_win;
	correlation_tracker m_tracker;


	afx_msg void OnClose();
	afx_msg void OnBnClickedBtnGetimage();

	void showMatImgToWnd(CWnd* pWnd, const cv::Mat& img);
	BOOL ShowImage(CDC* pDC, string strPath, int x, int y); 
	BOOL ShowImage2(string strPath, int x, int y);
	BOOL ShowImageLeft(string strPath, int x, int y); 
	BOOL ShowImageRight(string strPath, int x, int y);

	afx_msg void OnBnClickedBtnDetect();
	afx_msg void OnBnClickedBtnFacealg();

	afx_msg void OnBnClickedBtnTrain();
	afx_msg void OnBnClickedBtnFacecmp();
	afx_msg void OnBnClickedBtnFacealign();
	afx_msg void OnBnClickedBtnFacetrace();
	afx_msg void OnBnClickedBtnFacereg();
	CStatic m_regResult;
	afx_msg void OnBnClickedBtnFaceeye();
	afx_msg void OnBnClickedBtnFacemouse();
};
