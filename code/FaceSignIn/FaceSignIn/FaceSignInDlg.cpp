
// FaceSignInDlg.cpp : 实现文件
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


// CFaceSignInDlg 对话框



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


// CFaceSignInDlg 消息处理程序

BOOL CFaceSignInDlg::OnInitDialog()
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:视频预览窗口
	cv::namedWindow("view", cv::WINDOW_AUTOSIZE);
	HWND hWnd = (HWND)cvGetWindowHandle("view");
	HWND hParent = ::GetParent(hWnd);
	::SetParent(hWnd, GetDlgItem(IDC_PICHTURE)->m_hWnd);
	::ShowWindow(hParent, SW_HIDE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CFaceSignInDlg::OnPaint()
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
HCURSOR CFaceSignInDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CFaceSignInDlg::OnBnClickedBtnVideoopen()
{
	// TODO: 在此添加控件通知处理程序代码
	m_flag = 1;//摄像头打开标志
	m_bdetect = 0;
	m_brectangle = 0;
	m_btrack = 0;
	m_brecognition = 0;
	m_beye = 0;//眨眼检测
	m_bmouth = 0; //

	CRect rect;
	CWnd *pWnd = GetDlgItem(IDC_PICHTURE);//获取左侧的图片窗口及其空间大小
	pWnd->GetClientRect(&rect);
	int x = rect.Width();
	int y = rect.Height();
	//避免连续打开两次
	m_capture.release();
	//初始化摄像头
	m_capture = VideoCapture(0);//是opencv的一个类

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
		cv::Mat frame;//Mat相当于取一帧
		m_capture >> frame;//将获取的内容写到帧对象里面
		cv::resize(frame, m_dst, cv::Size(x, y), 0, 0, 1);//对储存帧大小重置，存入到了m_dst，后面可以直接imshow（m_dst）
		//注意：因为摄像头镜像原因，此处需要进行反转
		cv::Mat image_fliped;
		cv::flip(frame,image_fliped, 1);
		frame = image_fliped;
		//-----------------------------------------------
		
		cv_image<bgr_pixel> cimg(frame); //opencv的图像格式
		//01-目标跟踪
		if (m_btrack)
		{
			//注意：调试目标跟踪时注释掉下面一行
			image_window m_win;

			if (bFirst)//选取第一帧标识符，选取过后要置反
			{
				m_tracker.start_track(cimg, centered_rect(point(200, 110), 86, 86));//第一帧选定目标
				m_win.set_image(cimg);
				m_win.add_overlay(m_tracker.get_position());
				bFirst = 0;
			}
			m_tracker.update(cimg);//更新
			m_win.set_image(cimg);//窗口显示
			m_win.clear_overlay();
			m_win.add_overlay(m_tracker.get_position());//再绘制
		}

		//02-人脸检测
		if (m_bdetect)
		{
			// Detect faces 
			std::vector<dlib::rectangle> faces = detector(cimg);//dlib实现的模型，检测这一帧图片里的人脸
			//声明一个face vector 属于dlib里面的rectangle对象，理解为一个矩形框，就是将人脸存入框里面

			// Find the pose of each face.有可能是一个脸或者多个脸
			std::vector<full_object_detection> shapes;//人脸形状
			for (unsigned long i = 0; i < faces.size(); ++i) {//循环各个脸，找到脸左和上两个点，及其长宽
				//人脸检测，并绘制矩形框
				if (m_brectangle)
				{
					cv::rectangle(frame, Rect(faces[i].left(),faces[i].top(), faces[i].width(),faces[i].height()), Scalar(0,0,255), 1, 1, 0);
				}
				shapes.push_back(pose_model(cimg, faces[i]));//实际上就是68个点位姿模型检测到的68个点存入了shape
			}
			//特征点标定：68个点位的	
			if (!shapes.empty()) {
				//人脸检测是将检测到的人脸存入了shapes，如果非空那么绘制特征点
				for (int i = 0; i < 68; i++) {
					//cv::rectangle(frame, Rect(100, 300, 20, 200), Scalar(255, 0, 0), 1, 1, 0);
					if (!m_brectangle)
					{
						cv::circle(frame, cvPoint(shapes[0].part(i).x(), shapes[0].part(i).y()), 3, cv::Scalar(0, 0, 255), -1);
						//对每一帧，用cvcircle，cvpoint绘制所有的点
						//	shapes[0].part(i).x();//68个
						putText(frame, to_string(i), cvPoint(shapes[0].part(i).x(), shapes[0].part(i).y()), CV_FONT_HERSHEY_PLAIN, 1, cv::Scalar(255, 0, 0), 1, 4);
						// 显示特征点的数字
					}
				}
				//眨眼检测
				if (m_beye)
				{
					//眨眼行为检测:左眼-上下四个点
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
					//长宽比
					float flg = (y1 + y2) / (2.0 * x1);

					CString str;
					str.Format("EAR：%.2f", flg);
					m_regResult.SetWindowText(str);
				}
				//张嘴检测：Abs(Y50 – Y58) + Abs(Y52-56) /(2.0 * ABS(x48-x54))
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

					//长宽比
					float flg = (y1 + y2) / (2.0 * x1);

					CString str;
					str.Format("Mouth EAR：%.2f", flg);
					m_regResult.SetWindowText(str);
				}

			}
			
			//复制一份出来
			std::vector<matrix<rgb_pixel>> vect_faces;

			//04-人脸对齐：face_chips为对齐后的目标
			dlib::array<matrix<rgb_pixel> > face_chips;
			dlib::extract_image_chips(cimg, get_face_chip_details(shapes), face_chips);
			for (size_t i = 0; i < face_chips.size(); i++)
			{
				//复制一份人脸特征出来
				vect_faces.push_back(move(face_chips[i]));

				cv::Mat img = dlib::toMat(face_chips[i]);
				string picpath;				
				stringstream stream;
				stream << i;
				picpath = stream.str(); 
				picpath += ".jpg";
				imwrite(picpath, img);	
				//显示在控件上
				ShowImage2(picpath,0,0);
			}

			//05-人脸对比：
			//实时捕捉对象和已注册人脸进行对比，计算得分
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
	// TODO: 在此添加控件通知处理程序代码
	m_flag = 0;

}




void CFaceSignInDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_flag = 0;

	CDialogEx::OnClose();
}

//保存人脸照片
void CFaceSignInDlg::OnBnClickedBtnGetimage()
{
	string picpath = "d://FaceVer//code//take_photo//001.jpg";
	imwrite(picpath, m_dst);

	//显示到右侧窗口
	CWnd *pWnd = GetDlgItem(IDC_IMAGE);
	//showMatImgToWnd(pWnd,image);
	CDC *pDC = NULL;
	//设置静态控件的样式，使其可以使用位图，并使位图显示居中  
	((CStatic*)GetDlgItem(IDC_IMAGE))->ModifyStyle(0xF, SS_BITMAP | SS_CENTERIMAGE);

	pDC = GetDlgItem(IDC_IMAGE)->GetDC();		
	ShowImage(pDC, picpath, 0, 0);
	ReleaseDC(pDC); //释放资源

}
//显示人脸照片到窗口
void CFaceSignInDlg::showMatImgToWnd(CWnd* pWnd, const cv::Mat& img)
{
	if (img.empty())
		return;
	static BITMAPINFO *bitMapinfo = NULL;
	static bool First = TRUE;
	if (First)
	{
		BYTE *bitBuffer = new BYTE[40 + 4 * 256];//开辟一个内存区域
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
		{ //颜色的取值范围 (0-255)
			bitMapinfo->bmiColors[i].rgbBlue = bitMapinfo->bmiColors[i].rgbGreen = bitMapinfo->bmiColors[i].rgbRed = (BYTE)i;
		}
	}

	bitMapinfo->bmiHeader.biHeight = -img.rows;
	bitMapinfo->bmiHeader.biWidth = img.cols;
	bitMapinfo->bmiHeader.biBitCount = img.channels() * 8;
	CRect drect;
	pWnd->GetClientRect(drect);    //pWnd指向CWnd类的一个指针 

	CClientDC dc(pWnd);
	HDC hDC = dc.GetSafeHdc();     //HDC是Windows的一种数据类型，是设备
	SetStretchBltMode(hDC, COLORONCOLOR);
	StretchDIBits(hDC,
		0,
		0,
		drect.right,  //显示窗口宽度
		drect.bottom,  //显示窗口高度
		0,
		0,
		img.cols,     //图像宽度
		img.rows,     //图像高度
		img.data,
		bitMapinfo,
		DIB_RGB_COLORS,
		SRCCOPY
	);
}
//显示图片-右侧
BOOL CFaceSignInDlg::ShowImageRight(string strPath, int x, int y)
{
	//
	//strPath = "d:\\001.jpg";
	CWnd *pWnd = GetDlgItem(IDC_IMAGE);
	//showMatImgToWnd(pWnd,image);
	CDC *pDC = NULL;
	//设置静态控件的样式，使其可以使用位图，并使位图显示居中  
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
	// 宽度+高度
	OLE_XSIZE_HIMETRIC hmWidth;
	OLE_YSIZE_HIMETRIC hmHeight;
	pPic->get_Width(&hmWidth);
	pPic->get_Height(&hmHeight);
	//宽度和高度  
	RECT rtWnd;
	pDC->GetWindow()->GetWindowRect(&rtWnd);
	int iWndWidth = rtWnd.right - rtWnd.left;
	int iWndHeight = rtWnd.bottom - rtWnd.top;

	if (FAILED(pPic->Render(*pDC, x, y, iWndWidth, iWndHeight, 0, hmHeight, hmWidth, -hmHeight, NULL)))
	{
		pPic->Release();
		return false;
	}
	//释放资源
	pPic->Release();

	ReleaseDC(pDC); //释放资源
	return true;


}
//显示图片-左侧
BOOL CFaceSignInDlg::ShowImageLeft(string strPath, int x, int y)
{
	
	//strPath = "d:\\001.jpg";
	CWnd *pWnd = GetDlgItem(IDC_PICHTURE);
	//showMatImgToWnd(pWnd,image);
	CDC *pDC = NULL;
	//设置静态控件的样式，使其可以使用位图，并使位图显示居中  
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
	// 宽度+高度
	OLE_XSIZE_HIMETRIC hmWidth;
	OLE_YSIZE_HIMETRIC hmHeight;
	pPic->get_Width(&hmWidth);
	pPic->get_Height(&hmHeight);
	//宽度和高度  
	RECT rtWnd;
	pDC->GetWindow()->GetWindowRect(&rtWnd);
	int iWndWidth = rtWnd.right - rtWnd.left;
	int iWndHeight = rtWnd.bottom - rtWnd.top;

	if (FAILED(pPic->Render(*pDC, x, y, iWndWidth, iWndHeight, 0, hmHeight, hmWidth, -hmHeight, NULL)))
	{
		pPic->Release();
		return false;
	}
	//释放资源
	pPic->Release();

	ReleaseDC(pDC); //释放资源
	return true;


}
//显示图片
BOOL CFaceSignInDlg::ShowImage2(string strPath,int x, int y)
{
	//
	//strPath = "d:\\001.jpg";
	CWnd *pWnd = GetDlgItem(IDC_IMAGE);
	//showMatImgToWnd(pWnd,image);
	CDC *pDC = NULL;
	//设置静态控件的样式，使其可以使用位图，并使位图显示居中  
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
	// 宽度+高度
	OLE_XSIZE_HIMETRIC hmWidth;
	OLE_YSIZE_HIMETRIC hmHeight;
	pPic->get_Width(&hmWidth);
	pPic->get_Height(&hmHeight);
	//宽度和高度  
	RECT rtWnd;
	pDC->GetWindow()->GetWindowRect(&rtWnd);
	int iWndWidth = rtWnd.right - rtWnd.left;
	int iWndHeight = rtWnd.bottom - rtWnd.top;

	if (FAILED(pPic->Render(*pDC, x, y, iWndWidth, iWndHeight, 0, hmHeight, hmWidth, -hmHeight, NULL)))
	{
		pPic->Release();
		return false;
	}
	//释放资源
	pPic->Release();

	ReleaseDC(pDC); //释放资源
	return true;


}
//显示图片
BOOL CFaceSignInDlg::ShowImage(CDC* pDC, string strPath, int x, int y)//在抓拍人脸 将抓拍到的图片保存在本地后 再挂在右侧图片控件上显示的函数
{
	IPicture *pPic = NULL;//IPicture这是一个对象
	OleLoadPicturePath(CComBSTR(strPath.c_str()), (LPUNKNOWN)NULL, 0, 0, IID_IPicture, (LPVOID*)&pPic);//用OleLoadPicturePath这个控件
	if (NULL == pPic)
	{
		return FALSE;
	}
	// 宽度+高度
	OLE_XSIZE_HIMETRIC hmWidth;
	OLE_YSIZE_HIMETRIC hmHeight;
	pPic->get_Width(&hmWidth);
	pPic->get_Height(&hmHeight);
	//宽度和高度  
	RECT rtWnd;
	pDC->GetWindow()->GetWindowRect(&rtWnd);
	int iWndWidth = rtWnd.right - rtWnd.left;
	int iWndHeight = rtWnd.bottom - rtWnd.top;

	if (FAILED(pPic->Render(*pDC, x, y, iWndWidth, iWndHeight, 0, hmHeight, hmWidth, -hmHeight, NULL)))//这是做了一次渲染的窗口
	{
		pPic->Release();
		return false;
	}
	//释放资源
	pPic->Release();
	return true;
}



//人脸检测：画出矩形框，针对照片
void CFaceSignInDlg::OnBnClickedBtnDetect()
{
	m_bdetect = 1;
	if (m_brectangle)//在实时视频流监测过程中，要不要绘制矩形框的标识，要在.h文件里面声明
	{
		m_brectangle = 0;
	}
	else
	{
		m_brectangle = 1;
	}

}

//人脸特征点标定：68
void CFaceSignInDlg::OnBnClickedBtnFacealg()
{
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
	if (m_bdetect)
	{
		m_bdetect = 0;
	}
	else
	{
		m_bdetect = 1;
	}
}

//人脸比对：特征点对比
void CFaceSignInDlg::OnBnClickedBtnFacecmp()
{
	//人脸别对
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


//人脸对齐：位姿校正
void CFaceSignInDlg::OnBnClickedBtnFacealign()
{
	//图片文件路径
	string filePath = "D:\\FaceVer\\code\\take_photo\\001.jpg";
	//01-导入一张图片
	ShowImageLeft(filePath,0,0);
	//array2d<rgb_pixel> img;   //特别注意：转换后会失真
	//bgr_pixel
	array2d<bgr_pixel> img;
	load_image(img, filePath);
	pyramid_up(img);

	//02：初始化环境
	frontal_face_detector detector = get_frontal_face_detector();
	shape_predictor pose_model;
	deserialize("D:\\FaceVer\\model\\shape_predictor_68_face_landmarks.dat") >> pose_model;

	//03-人脸检测
	std::vector<dlib::rectangle> faces = detector(img);

	//检测每一张人脸
	std::vector<full_object_detection> shapes;
	for (unsigned long i = 0; i < faces.size(); ++i) {
		//人脸检测，并绘制矩形框 
		// Key1:注意转换失真问题：bgr_pixel
		cv::Mat img2 = dlib::toMat(img);
		cv::rectangle(img2, Rect(faces[i].left(), faces[i].top(), faces[i].width(), faces[i].height()), Scalar(0, 0, 255), 1, 1, 0);
		shapes.push_back(pose_model(img, faces[i]));
	}
	//04-特征点标定：68	
	if (!shapes.empty()) {

		for (int i = 0; i < 68; i++) {
			cv::Mat img2 = dlib::toMat(img);
			//cv::rectangle(frame, Rect(100, 300, 20, 200), Scalar(255, 0, 0), 1, 1, 0);
			cv::circle(img2,cvPoint(shapes[0].part(i).x(), shapes[0].part(i).y()), 3, cv::Scalar(0, 0, 255), -1);
			//shapes[0].part(i).x();//68个
			// zhanzl:显示特征点的数字
			putText(img2, to_string(i), cvPoint(shapes[0].part(i).x(), shapes[0].part(i).y()), CV_FONT_HERSHEY_PLAIN, 1, cv::Scalar(255, 0, 0), 1, 4);
		}
	}

	//05-人脸对齐：face_chips为对齐后的目标
	dlib::array<array2d<bgr_pixel> > face_chips;
	dlib::extract_image_chips(img,get_face_chip_details(shapes), face_chips);//对齐函数的执行，将对齐后保存在face_chips
	for (size_t i = 0; i < face_chips.size(); i++)//对齐后在显示出来
	{
		cv::Mat img = dlib::toMat(face_chips[i]);
		string picpath;
		stringstream stream;
		stream << i;
		picpath = stream.str();
		picpath += ".jpg";//进行对齐后人脸的保存，可能有多张人脸，默认d盘路径加上序号作为保存
		picpath = "d://FaceVer//code//facechips_photo//" + picpath;
		imwrite(picpath, img);
		//显示在控件上
		ShowImageRight(picpath, 0, 0);
	}
}


void CFaceSignInDlg::OnBnClickedBtnFacetrace()
{
	/*
	//01-目标跟踪
	//图片文件路径
	string filePath = "d://001.jpg";
	//01-导入一张图片
	ShowImageLeft(filePath, 0, 0);
	//array2d<rgb_pixel> img;   //特别注意：转换后会失真
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

//离线对比
void CFaceSignInDlg::OnBnClickedBtnFacereg()
{
	//01-初始化检测器+图片
	frontal_face_detector detector = get_frontal_face_detector();
	//导入模型：特征点标定
	shape_predictor sp;
	deserialize("D:\\FaceVer\\model\\shape_predictor_68_face_landmarks.dat") >> sp;
	
	//导入模型：用于人脸特征向量表示
	anet_type net;
	//dlib_face_recognition_resnet_model_v1.dat
	deserialize("D:\\FaceVer\\model\\dlib_face_recognition_resnet_model_v1.dat") >> net;//这个模型用于人脸特征向量表示
	//bald_guys.jpg
	//string path = "E:\\project\\faceid\\code\\FaceSignIn\\faces\\bald_guys.jpg";
	string path1 = "D:\\FaceVer\\code\\FaceSignIn\\faces\\001.jpg";//可以设置为实时获取的图片
	string path2 = "D:\\FaceVer\\code\\FaceSignIn\\faces\\002.jpg";//可以设置为存储库的图片
	matrix<rgb_pixel> img1;
	load_image(img1, path1);

	matrix<rgb_pixel> img2;
	load_image(img2, path2);

	//ShowImageLeft(path,0,0);
	// Display the raw image on the screen
	//image_window win(img);
	ShowImageLeft(path1,0,0);
	ShowImageRight(path2, 0, 0);//分别显示上去，实时可以去掉的
	//02-特征点对齐
	std::vector<matrix<rgb_pixel>> faces1;
	std::vector<matrix<rgb_pixel>> faces2;


	//02-人脸检测img1:
	//注意：检测多张人脸时，会触发中断
	for (auto face : detector(img1))
	{
		//001-特征点检测
		auto shape = sp(img1, face);
		//0002-特征点对齐
		matrix<rgb_pixel> face_chip;
		extract_image_chip(img1, get_face_chip_details(shape, 150, 0.25), face_chip);
		//003-特征点存储（对齐后的点）
		faces1.push_back(move(face_chip));
	}
	if (faces1.size() == 0)
	{
		cout << "No faces found in image!" << endl;
		//return 1;
	}
	//02-人脸检测img2
	for (auto face : detector(img2))
	{
		//001-特征点检测
		auto shape = sp(img2, face);
		//0002-特征点对齐
		matrix<rgb_pixel> face_chip;
		extract_image_chip(img2, get_face_chip_details(shape, 150, 0.25), face_chip);
		//003-特征点存储（对齐后的点）
		faces2.push_back(move(face_chip));
	}
	if (faces2.size() == 0)
	{
		cout << "No faces found in image!" << endl;
		//return 1;
	}

	//03-人脸特征向量化
	std::vector<matrix<float, 0, 1>> face_descriptors1 = net(faces1);
	std::vector<matrix<float, 0, 1>> face_descriptors2 = net(faces2);

	//04-距离计算
	float f = length(face_descriptors1[0] - face_descriptors2[0]);
	CString str;
	str.Format("欧式距离：%.2f", f);
	m_regResult.SetWindowText(str);
	AfxMessageBox(str);//这是弹出对话框
	

}

//眨眼检测
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
