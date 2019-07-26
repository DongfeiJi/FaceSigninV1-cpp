
// FaceSignInDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FaceSignIn.h"
#include "FaceSignInDlg.h"
#include "afxdialogex.h"
#include "Sort_method.h"
#include<cmath>




#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CFaceSignInDlg �Ի���



CFaceSignInDlg::CFaceSignInDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_FACESIGNIN_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFaceSignInDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_RESULT, m_regResult);
}

BEGIN_MESSAGE_MAP(CFaceSignInDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_VIDEOOPEN, &CFaceSignInDlg::OnBnClickedBtnVideoopen)
	ON_BN_CLICKED(IDC_BTN_VIDEOCLOSE, &CFaceSignInDlg::OnBnClickedBtnVideoclose)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BTN_GETIMAGE, &CFaceSignInDlg::OnBnClickedBtnGetimage)
	ON_BN_CLICKED(IDC_BTN_DETECT, &CFaceSignInDlg::OnBnClickedBtnDetect)
	ON_BN_CLICKED(IDC_BTN_FACEALG, &CFaceSignInDlg::OnBnClickedBtnFacealg)

	ON_BN_CLICKED(IDC_BTN_TRAIN, &CFaceSignInDlg::OnBnClickedBtnTrain)
	ON_BN_CLICKED(IDC_BTN_FACECMP, &CFaceSignInDlg::OnBnClickedBtnFacecmp)
	ON_BN_CLICKED(IDC_BTN_FACEALIGN, &CFaceSignInDlg::OnBnClickedBtnFacealign)
	ON_BN_CLICKED(IDC_BTN_FACETRACE, &CFaceSignInDlg::OnBnClickedBtnFacetrace)
	ON_BN_CLICKED(IDC_BTN_FACEREG, &CFaceSignInDlg::OnBnClickedBtnFacereg)
	ON_BN_CLICKED(IDC_BTN_FACEEYE, &CFaceSignInDlg::OnBnClickedBtnFaceeye)
	ON_BN_CLICKED(IDC_BTN_FACEMOUSE, &CFaceSignInDlg::OnBnClickedBtnFacemouse)
END_MESSAGE_MAP()


// CFaceSignInDlg ��Ϣ�������

BOOL CFaceSignInDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:��ƵԤ������
	cv::namedWindow("view", cv::WINDOW_AUTOSIZE);
	HWND hWnd = (HWND)cvGetWindowHandle("view");
	HWND hParent = ::GetParent(hWnd);
	::SetParent(hWnd, GetDlgItem(IDC_PICHTURE)->m_hWnd);
	::ShowWindow(hParent, SW_HIDE);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CFaceSignInDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CFaceSignInDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CFaceSignInDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CFaceSignInDlg::OnBnClickedBtnVideoopen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_flag = 1;//����ͷ�򿪱�־
	m_bdetect = 0;
	m_brectangle = 0;
	m_btrack = 0;
	m_brecognition = 0;
	m_beye = 0;//գ�ۼ��
	m_bmouth = 0; //

	CRect rect;
	CWnd *pWnd = GetDlgItem(IDC_PICHTURE);//��ȡ����ͼƬ���ڼ���ռ��С
	pWnd->GetClientRect(&rect);
	int x = rect.Width();
	int y = rect.Height();
	//��������������
	m_capture.release();
	//��ʼ������ͷ
	m_capture = VideoCapture(0);//��opencv��һ����

	if (!m_capture.isOpened())
	{
		fprintf(stderr, "Can not open camera.\n");
		return;
	}
	// Load face detection and pose estimation models.
	frontal_face_detector detector = get_frontal_face_detector();
	//image_window win;
	//face_recognition_model_v1

	shape_predictor pose_model;

	deserialize("D:\\FaceVer\\model\\shape_predictor_68_face_landmarks.dat") >> pose_model;
	//deserialize("E:\\project\\faceid\\model\\dlib_face_recognition_resnet_model_v1.dat") >> pose_model; 

	//
	bool bFirst = 1;
	while (m_flag)
	{
		cv::Mat frame;//Mat�൱��ȡһ֡
		m_capture >> frame;//����ȡ������д��֡��������
		cv::resize(frame, m_dst, cv::Size(x, y), 0, 0, 1);//�Դ���֡��С���ã����뵽��m_dst���������ֱ��imshow��m_dst��
		//ע�⣺��Ϊ����ͷ����ԭ�򣬴˴���Ҫ���з�ת
		cv::Mat image_fliped;
		cv::flip(frame,image_fliped, 1);
		frame = image_fliped;
		//-----------------------------------------------
		
		cv_image<bgr_pixel> cimg(frame); //opencv��ͼ���ʽ
		//01-Ŀ�����
		if (m_btrack)
		{
			//ע�⣺����Ŀ�����ʱע�͵�����һ��
			image_window m_win;

			if (bFirst)//ѡȡ��һ֡��ʶ����ѡȡ����Ҫ�÷�
			{
				m_tracker.start_track(cimg, centered_rect(point(200, 110), 86, 86));//��һ֡ѡ��Ŀ��
				m_win.set_image(cimg);
				m_win.add_overlay(m_tracker.get_position());
				bFirst = 0;
			}
			m_tracker.update(cimg);//����
			m_win.set_image(cimg);//������ʾ
			m_win.clear_overlay();
			m_win.add_overlay(m_tracker.get_position());//�ٻ���
		}

		//02-�������
		if (m_bdetect)
		{
			// Detect faces 
			std::vector<dlib::rectangle> faces = detector(cimg);//dlibʵ�ֵ�ģ�ͣ������һ֡ͼƬ�������
			//����һ��face vector ����dlib�����rectangle�������Ϊһ�����ο򣬾��ǽ��������������

			// Find the pose of each face.�п�����һ�������߶����
			std::vector<full_object_detection> shapes;//������״
			for (unsigned long i = 0; i < faces.size(); ++i) {//ѭ�����������ҵ�������������㣬���䳤��
				//������⣬�����ƾ��ο�
				if (m_brectangle)
				{
					cv::rectangle(frame, Rect(faces[i].left(),faces[i].top(), faces[i].width(),faces[i].height()), Scalar(0,0,255), 1, 1, 0);
				}
				shapes.push_back(pose_model(cimg, faces[i]));//ʵ���Ͼ���68����λ��ģ�ͼ�⵽��68���������shape
			}
			//������궨��68����λ��	
			if (!shapes.empty()) {
				//��������ǽ���⵽������������shapes������ǿ���ô����������
				for (int i = 0; i < 68; i++) {
					//cv::rectangle(frame, Rect(100, 300, 20, 200), Scalar(255, 0, 0), 1, 1, 0);
					if (!m_brectangle)
					{
						cv::circle(frame, cvPoint(shapes[0].part(i).x(), shapes[0].part(i).y()), 3, cv::Scalar(0, 0, 255), -1);
						//��ÿһ֡����cvcircle��cvpoint�������еĵ�
						//	shapes[0].part(i).x();//68��
						putText(frame, to_string(i), cvPoint(shapes[0].part(i).x(), shapes[0].part(i).y()), CV_FONT_HERSHEY_PLAIN, 1, cv::Scalar(255, 0, 0), 1, 4);
						// ��ʾ�����������
					}
				}
				//գ�ۼ��
				if (m_beye)
				{
					//գ����Ϊ���:����-�����ĸ���
					int y37 = shapes[0].part(37).y();
					int y38 = shapes[0].part(38).y();
					int y40 = shapes[0].part(40).y();
					int y41 = shapes[0].part(41).y();
					int x36 = shapes[0].part(36).x();
					int x39 = shapes[0].part(39).x();

					//1 / 2 * [(y41 + y40) - (y37 + y38)] / (x39 - x36)
					//float flg = 1/2* [(y41 + y40) - (y37 + y48)]/(x39 - x36);
					int y1 = abs(y37 - y41);
					int y2 = abs(y38 - y40);
					int x1 = abs(x39 - x36);
					//�����
					float flg = (y1 + y2) / (2.0 * x1);

					CString str;
					str.Format("EAR��%.2f", flg);
					m_regResult.SetWindowText(str);
				}
				//�����⣺Abs(Y50 �C Y58) + Abs(Y52-56) /(2.0 * ABS(x48-x54))
				if (m_bmouth)
				{
					int y50 = shapes[0].part(50).y();
					int y52 = shapes[0].part(52).y();
					int y56 = shapes[0].part(56).y();
					int y58 = shapes[0].part(58).y();
					
					int x48 = shapes[0].part(48).x();
					int x54 = shapes[0].part(54).x();

					int y1 = abs(y50 - y58);
					int y2 = abs(y52 - y56);
					int x1 = abs(x48 - x54);

					//�����
					float flg = (y1 + y2) / (2.0 * x1);

					CString str;
					str.Format("Mouth EAR��%.2f", flg);
					m_regResult.SetWindowText(str);
				}

			}
			
			//����һ�ݳ���
			std::vector<matrix<rgb_pixel>> vect_faces;

			//04-�������룺face_chipsΪ������Ŀ��
			dlib::array<matrix<rgb_pixel> > face_chips;
			dlib::extract_image_chips(cimg, get_face_chip_details(shapes), face_chips);
			for (size_t i = 0; i < face_chips.size(); i++)
			{
				//����һ��������������
				vect_faces.push_back(move(face_chips[i]));

				cv::Mat img = dlib::toMat(face_chips[i]);
				string picpath;				
				stringstream stream;
				stream << i;
				picpath = stream.str(); 
				picpath += ".jpg";
				imwrite(picpath, img);	
				//��ʾ�ڿؼ���
				ShowImage2(picpath,0,0);
			}

			//05-�����Աȣ�
			//ʵʱ��׽�������ע���������жԱȣ�����÷�
			if (m_brecognition)
			{


			}
		}
		cv::imshow("view", frame);
		cv::waitKey(30);
	}
	
}


void CFaceSignInDlg::OnBnClickedBtnVideoclose()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_flag = 0;

}




void CFaceSignInDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_flag = 0;

	CDialogEx::OnClose();
}

//����������Ƭ
void CFaceSignInDlg::OnBnClickedBtnGetimage()
{
	string picpath = "d://FaceVer//code//take_photo//001.jpg";
	imwrite(picpath, m_dst);

	//��ʾ���Ҳര��
	CWnd *pWnd = GetDlgItem(IDC_IMAGE);
	//showMatImgToWnd(pWnd,image);
	CDC *pDC = NULL;
	//���þ�̬�ؼ�����ʽ��ʹ�����ʹ��λͼ����ʹλͼ��ʾ����  
	((CStatic*)GetDlgItem(IDC_IMAGE))->ModifyStyle(0xF, SS_BITMAP | SS_CENTERIMAGE);

	pDC = GetDlgItem(IDC_IMAGE)->GetDC();		
	ShowImage(pDC, picpath, 0, 0);
	ReleaseDC(pDC); //�ͷ���Դ

}
//��ʾ������Ƭ������
void CFaceSignInDlg::showMatImgToWnd(CWnd* pWnd, const cv::Mat& img)
{
	if (img.empty())
		return;
	static BITMAPINFO *bitMapinfo = NULL;
	static bool First = TRUE;
	if (First)
	{
		BYTE *bitBuffer = new BYTE[40 + 4 * 256];//����һ���ڴ�����
		if (bitBuffer == NULL)
		{
			return;
		}

		First = FALSE;
		memset(bitBuffer, 0, 40 + 4 * 256);
		bitMapinfo = (BITMAPINFO *)bitBuffer;
		bitMapinfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bitMapinfo->bmiHeader.biPlanes = 1;
		for (int i = 0; i < 256; i++)
		{ //��ɫ��ȡֵ��Χ (0-255)
			bitMapinfo->bmiColors[i].rgbBlue = bitMapinfo->bmiColors[i].rgbGreen = bitMapinfo->bmiColors[i].rgbRed = (BYTE)i;
		}
	}

	bitMapinfo->bmiHeader.biHeight = -img.rows;
	bitMapinfo->bmiHeader.biWidth = img.cols;
	bitMapinfo->bmiHeader.biBitCount = img.channels() * 8;
	CRect drect;
	pWnd->GetClientRect(drect);    //pWndָ��CWnd���һ��ָ�� 

	CClientDC dc(pWnd);
	HDC hDC = dc.GetSafeHdc();     //HDC��Windows��һ���������ͣ����豸
	SetStretchBltMode(hDC, COLORONCOLOR);
	StretchDIBits(hDC,
		0,
		0,
		drect.right,  //��ʾ���ڿ��
		drect.bottom,  //��ʾ���ڸ߶�
		0,
		0,
		img.cols,     //ͼ����
		img.rows,     //ͼ��߶�
		img.data,
		bitMapinfo,
		DIB_RGB_COLORS,
		SRCCOPY
	);
}
//��ʾͼƬ-�Ҳ�
BOOL CFaceSignInDlg::ShowImageRight(string strPath, int x, int y)
{
	//
	//strPath = "d:\\001.jpg";
	CWnd *pWnd = GetDlgItem(IDC_IMAGE);
	//showMatImgToWnd(pWnd,image);
	CDC *pDC = NULL;
	//���þ�̬�ؼ�����ʽ��ʹ�����ʹ��λͼ����ʹλͼ��ʾ����  
	((CStatic*)GetDlgItem(IDC_IMAGE))->ModifyStyle(0xF, SS_BITMAP | SS_CENTERIMAGE);

	pDC = GetDlgItem(IDC_IMAGE)->GetDC();
	ShowImage(pDC, strPath, 0, 0);


	//
	IPicture *pPic = NULL;
	OleLoadPicturePath(CComBSTR(strPath.c_str()), (LPUNKNOWN)NULL, 0, 0, IID_IPicture, (LPVOID*)&pPic);
	if (NULL == pPic)
	{
		return FALSE;
	}
	// ���+�߶�
	OLE_XSIZE_HIMETRIC hmWidth;
	OLE_YSIZE_HIMETRIC hmHeight;
	pPic->get_Width(&hmWidth);
	pPic->get_Height(&hmHeight);
	//��Ⱥ͸߶�  
	RECT rtWnd;
	pDC->GetWindow()->GetWindowRect(&rtWnd);
	int iWndWidth = rtWnd.right - rtWnd.left;
	int iWndHeight = rtWnd.bottom - rtWnd.top;

	if (FAILED(pPic->Render(*pDC, x, y, iWndWidth, iWndHeight, 0, hmHeight, hmWidth, -hmHeight, NULL)))
	{
		pPic->Release();
		return false;
	}
	//�ͷ���Դ
	pPic->Release();

	ReleaseDC(pDC); //�ͷ���Դ
	return true;


}
//��ʾͼƬ-���
BOOL CFaceSignInDlg::ShowImageLeft(string strPath, int x, int y)
{
	
	//strPath = "d:\\001.jpg";
	CWnd *pWnd = GetDlgItem(IDC_PICHTURE);
	//showMatImgToWnd(pWnd,image);
	CDC *pDC = NULL;
	//���þ�̬�ؼ�����ʽ��ʹ�����ʹ��λͼ����ʹλͼ��ʾ����  
	((CStatic*)GetDlgItem(IDC_PICHTURE))->ModifyStyle(0xF, SS_BITMAP | SS_CENTERIMAGE);

	pDC = GetDlgItem(IDC_PICHTURE)->GetDC();
	ShowImage(pDC, strPath, 0, 0);


	//
	IPicture *pPic = NULL;
	OleLoadPicturePath(CComBSTR(strPath.c_str()), (LPUNKNOWN)NULL, 0, 0, IID_IPicture, (LPVOID*)&pPic);
	if (NULL == pPic)
	{
		return FALSE;
	}
	// ���+�߶�
	OLE_XSIZE_HIMETRIC hmWidth;
	OLE_YSIZE_HIMETRIC hmHeight;
	pPic->get_Width(&hmWidth);
	pPic->get_Height(&hmHeight);
	//��Ⱥ͸߶�  
	RECT rtWnd;
	pDC->GetWindow()->GetWindowRect(&rtWnd);
	int iWndWidth = rtWnd.right - rtWnd.left;
	int iWndHeight = rtWnd.bottom - rtWnd.top;

	if (FAILED(pPic->Render(*pDC, x, y, iWndWidth, iWndHeight, 0, hmHeight, hmWidth, -hmHeight, NULL)))
	{
		pPic->Release();
		return false;
	}
	//�ͷ���Դ
	pPic->Release();

	ReleaseDC(pDC); //�ͷ���Դ
	return true;


}
//��ʾͼƬ
BOOL CFaceSignInDlg::ShowImage2(string strPath,int x, int y)
{
	//
	//strPath = "d:\\001.jpg";
	CWnd *pWnd = GetDlgItem(IDC_IMAGE);
	//showMatImgToWnd(pWnd,image);
	CDC *pDC = NULL;
	//���þ�̬�ؼ�����ʽ��ʹ�����ʹ��λͼ����ʹλͼ��ʾ����  
	((CStatic*)GetDlgItem(IDC_IMAGE))->ModifyStyle(0xF, SS_BITMAP | SS_CENTERIMAGE);

	pDC = GetDlgItem(IDC_IMAGE)->GetDC();
	ShowImage(pDC, strPath, 0, 0);


	//
	IPicture *pPic = NULL;
	OleLoadPicturePath(CComBSTR(strPath.c_str()), (LPUNKNOWN)NULL, 0, 0, IID_IPicture, (LPVOID*)&pPic);
	if (NULL == pPic)
	{
		return FALSE;
	}
	// ���+�߶�
	OLE_XSIZE_HIMETRIC hmWidth;
	OLE_YSIZE_HIMETRIC hmHeight;
	pPic->get_Width(&hmWidth);
	pPic->get_Height(&hmHeight);
	//��Ⱥ͸߶�  
	RECT rtWnd;
	pDC->GetWindow()->GetWindowRect(&rtWnd);
	int iWndWidth = rtWnd.right - rtWnd.left;
	int iWndHeight = rtWnd.bottom - rtWnd.top;

	if (FAILED(pPic->Render(*pDC, x, y, iWndWidth, iWndHeight, 0, hmHeight, hmWidth, -hmHeight, NULL)))
	{
		pPic->Release();
		return false;
	}
	//�ͷ���Դ
	pPic->Release();

	ReleaseDC(pDC); //�ͷ���Դ
	return true;


}
//��ʾͼƬ
BOOL CFaceSignInDlg::ShowImage(CDC* pDC, string strPath, int x, int y)//��ץ������ ��ץ�ĵ���ͼƬ�����ڱ��غ� �ٹ����Ҳ�ͼƬ�ؼ�����ʾ�ĺ���
{
	IPicture *pPic = NULL;//IPicture����һ������
	OleLoadPicturePath(CComBSTR(strPath.c_str()), (LPUNKNOWN)NULL, 0, 0, IID_IPicture, (LPVOID*)&pPic);//��OleLoadPicturePath����ؼ�
	if (NULL == pPic)
	{
		return FALSE;
	}
	// ���+�߶�
	OLE_XSIZE_HIMETRIC hmWidth;
	OLE_YSIZE_HIMETRIC hmHeight;
	pPic->get_Width(&hmWidth);
	pPic->get_Height(&hmHeight);
	//��Ⱥ͸߶�  
	RECT rtWnd;
	pDC->GetWindow()->GetWindowRect(&rtWnd);
	int iWndWidth = rtWnd.right - rtWnd.left;
	int iWndHeight = rtWnd.bottom - rtWnd.top;

	if (FAILED(pPic->Render(*pDC, x, y, iWndWidth, iWndHeight, 0, hmHeight, hmWidth, -hmHeight, NULL)))//��������һ����Ⱦ�Ĵ���
	{
		pPic->Release();
		return false;
	}
	//�ͷ���Դ
	pPic->Release();
	return true;
}



//������⣺�������ο������Ƭ
void CFaceSignInDlg::OnBnClickedBtnDetect()
{
	m_bdetect = 1;
	if (m_brectangle)//��ʵʱ��Ƶ���������У�Ҫ��Ҫ���ƾ��ο�ı�ʶ��Ҫ��.h�ļ���������
	{
		m_brectangle = 0;
	}
	else
	{
		m_brectangle = 1;
	}

}

//����������궨��68
void CFaceSignInDlg::OnBnClickedBtnFacealg()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_bdetect)
	{
		m_bdetect = 0;
	}
	else
	{
		m_bdetect = 1;
	}
}


void CFaceSignInDlg::OnBnClickedBtnTrain()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_bdetect)
	{
		m_bdetect = 0;
	}
	else
	{
		m_bdetect = 1;
	}
}

//�����ȶԣ�������Ա�
void CFaceSignInDlg::OnBnClickedBtnFacecmp()
{
	//�������
	//dlib_face_recognition_resnet_model_v1.dat
	
	if (m_brecognition)
	{
		m_brecognition = 0;
	}
	else
	{
		m_brecognition = 1;
	}



}


//�������룺λ��У��
void CFaceSignInDlg::OnBnClickedBtnFacealign()
{
	//ͼƬ�ļ�·��
	string filePath = "D:\\FaceVer\\code\\take_photo\\001.jpg";
	//01-����һ��ͼƬ
	ShowImageLeft(filePath,0,0);
	//array2d<rgb_pixel> img;   //�ر�ע�⣺ת�����ʧ��
	//bgr_pixel
	array2d<bgr_pixel> img;
	load_image(img, filePath);
	pyramid_up(img);

	//02����ʼ������
	frontal_face_detector detector = get_frontal_face_detector();
	shape_predictor pose_model;
	deserialize("D:\\FaceVer\\model\\shape_predictor_68_face_landmarks.dat") >> pose_model;

	//03-�������
	std::vector<dlib::rectangle> faces = detector(img);

	//���ÿһ������
	std::vector<full_object_detection> shapes;
	for (unsigned long i = 0; i < faces.size(); ++i) {
		//������⣬�����ƾ��ο� 
		// Key1:ע��ת��ʧ�����⣺bgr_pixel
		cv::Mat img2 = dlib::toMat(img);
		cv::rectangle(img2, Rect(faces[i].left(), faces[i].top(), faces[i].width(), faces[i].height()), Scalar(0, 0, 255), 1, 1, 0);
		shapes.push_back(pose_model(img, faces[i]));
	}
	//04-������궨��68	
	if (!shapes.empty()) {

		for (int i = 0; i < 68; i++) {
			cv::Mat img2 = dlib::toMat(img);
			//cv::rectangle(frame, Rect(100, 300, 20, 200), Scalar(255, 0, 0), 1, 1, 0);
			cv::circle(img2,cvPoint(shapes[0].part(i).x(), shapes[0].part(i).y()), 3, cv::Scalar(0, 0, 255), -1);
			//shapes[0].part(i).x();//68��
			// zhanzl:��ʾ�����������
			putText(img2, to_string(i), cvPoint(shapes[0].part(i).x(), shapes[0].part(i).y()), CV_FONT_HERSHEY_PLAIN, 1, cv::Scalar(255, 0, 0), 1, 4);
		}
	}

	//05-�������룺face_chipsΪ������Ŀ��
	dlib::array<array2d<bgr_pixel> > face_chips;
	dlib::extract_image_chips(img,get_face_chip_details(shapes), face_chips);//���뺯����ִ�У�������󱣴���face_chips
	for (size_t i = 0; i < face_chips.size(); i++)//���������ʾ����
	{
		cv::Mat img = dlib::toMat(face_chips[i]);
		string picpath;
		stringstream stream;
		stream << i;
		picpath = stream.str();
		picpath += ".jpg";//���ж���������ı��棬�����ж���������Ĭ��d��·�����������Ϊ����
		picpath = "d://FaceVer//code//facechips_photo//" + picpath;
		imwrite(picpath, img);
		//��ʾ�ڿؼ���
		ShowImageRight(picpath, 0, 0);
	}
}


void CFaceSignInDlg::OnBnClickedBtnFacetrace()
{
	/*
	//01-Ŀ�����
	//ͼƬ�ļ�·��
	string filePath = "d://001.jpg";
	//01-����һ��ͼƬ
	ShowImageLeft(filePath, 0, 0);
	//array2d<rgb_pixel> img;   //�ر�ע�⣺ת�����ʧ��
	//bgr_pixel
	array2d<bgr_pixel> img;
	load_image(img, filePath);
	pyramid_up(img);

	
	correlation_tracker tracker;
	tracker.start_track(img, centered_rect(point(93, 110), 60, 86));
	tracker.update(img);
	win.set_image(img);
	win.clear_overlay();
	win.add_overlay(tracker.get_position());
	*/
	if (m_btrack)
	{
		m_btrack = 0;
	}
	else
	{
		m_btrack = 1;
	}

}

//���߶Ա�
void CFaceSignInDlg::OnBnClickedBtnFacereg()
{
	//01-��ʼ�������+ͼƬ
	frontal_face_detector detector = get_frontal_face_detector();
	//����ģ�ͣ�������궨
	shape_predictor sp;
	deserialize("D:\\FaceVer\\model\\shape_predictor_68_face_landmarks.dat") >> sp;
	
	//����ģ�ͣ�������������������ʾ
	anet_type net;
	//dlib_face_recognition_resnet_model_v1.dat
	deserialize("D:\\FaceVer\\model\\dlib_face_recognition_resnet_model_v1.dat") >> net;//���ģ��������������������ʾ
	//bald_guys.jpg
	//string path = "E:\\project\\faceid\\code\\FaceSignIn\\faces\\bald_guys.jpg";
	string path1 = "D:\\FaceVer\\code\\FaceSignIn\\faces\\001.jpg";//��������Ϊʵʱ��ȡ��ͼƬ
	string path2 = "D:\\FaceVer\\code\\FaceSignIn\\faces\\002.jpg";//��������Ϊ�洢���ͼƬ
	matrix<rgb_pixel> img1;
	load_image(img1, path1);

	matrix<rgb_pixel> img2;
	load_image(img2, path2);

	//ShowImageLeft(path,0,0);
	// Display the raw image on the screen
	//image_window win(img);
	ShowImageLeft(path1,0,0);
	ShowImageRight(path2, 0, 0);//�ֱ���ʾ��ȥ��ʵʱ����ȥ����
	//02-���������
	std::vector<matrix<rgb_pixel>> faces1;
	std::vector<matrix<rgb_pixel>> faces2;


	//02-�������img1:
	//ע�⣺����������ʱ���ᴥ���ж�
	for (auto face : detector(img1))
	{
		//001-��������
		auto shape = sp(img1, face);
		//0002-���������
		matrix<rgb_pixel> face_chip;
		extract_image_chip(img1, get_face_chip_details(shape, 150, 0.25), face_chip);
		//003-������洢�������ĵ㣩
		faces1.push_back(move(face_chip));
	}
	if (faces1.size() == 0)
	{
		cout << "No faces found in image!" << endl;
		//return 1;
	}
	//02-�������img2
	for (auto face : detector(img2))
	{
		//001-��������
		auto shape = sp(img2, face);
		//0002-���������
		matrix<rgb_pixel> face_chip;
		extract_image_chip(img2, get_face_chip_details(shape, 150, 0.25), face_chip);
		//003-������洢�������ĵ㣩
		faces2.push_back(move(face_chip));
	}
	if (faces2.size() == 0)
	{
		cout << "No faces found in image!" << endl;
		//return 1;
	}

	//03-��������������
	std::vector<matrix<float, 0, 1>> face_descriptors1 = net(faces1);
	std::vector<matrix<float, 0, 1>> face_descriptors2 = net(faces2);

	//04-�������
	float f = length(face_descriptors1[0] - face_descriptors2[0]);
	CString str;
	str.Format("ŷʽ���룺%.2f", f);
	m_regResult.SetWindowText(str);
	AfxMessageBox(str);//���ǵ����Ի���
	

}

//գ�ۼ��
void CFaceSignInDlg::OnBnClickedBtnFaceeye()
{
	if (m_beye)
	{
		m_beye = 0;
	}
	else
	{
		m_beye = 1;
	}

}

void CFaceSignInDlg::OnBnClickedBtnFacemouse()
{
	if (m_bmouth)
	{
		m_bmouth = 0;
	}
	else
	{
		m_bmouth = 1;
	}
}
