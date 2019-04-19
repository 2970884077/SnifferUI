// SnifferUIDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SnifferUI.h"
#include "SnifferUIDlg.h"

//#include "packet_header.h"
#include "Global.h"
//#include "string.h"
#include "ctype.h"
//#include "remote-ext.h"
//#include "winsock2.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNMClickSyslink1(NMHDR *pNMHDR, LRESULT *pResult);
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
	ON_NOTIFY(NM_CLICK, IDC_SYSLINK1, &CAboutDlg::OnNMClickSyslink1)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSnifferUIDlg dialog

CSnifferUIDlg::CSnifferUIDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSnifferUIDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSnifferUIDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSnifferUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSnifferUIDlg)
	DDX_Control(pDX, IDC_START, btnStart_);
	DDX_Control(pDX, IDC_PAUSE, btnPause_);
	DDX_Control(pDX, IDC_STOP, btnStop_);
	DDX_Control(pDX, IDC_FILTER, btnFilter_);
	DDX_Control(pDX, IDC_CLEAR, btnClear_);
	DDX_Control(pDX, IDC_COMBO1, comboBoxDevlist_);
	DDX_Control(pDX, IDC_LIST1, listCtrlPacketList_);
	DDX_Control(pDX, IDC_TREE1, treeCtrlPacketInfo_);
	DDX_Control(pDX, IDC_EDIT1, editCtrlPacketData_);
	//DDX_Control(pDX, IDC_RICHEDIT21, richEditCtrlFilterInput_);
	DDX_Control(pDX, IDC_COMBO2, comboBoxFilterInput_);
	//}}AFX_DATA_MAP

	
}

BEGIN_MESSAGE_MAP(CSnifferUIDlg, CDialog)
	//{{AFX_MSG_MAP(CSnifferUIDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_START, OnClickedStart)
	ON_BN_CLICKED(IDC_PAUSE, OnClickedPause)
	ON_BN_CLICKED(IDC_STOP, OnClickedStop)
	ON_BN_CLICKED(IDC_FILTER, &CSnifferUIDlg::OnClickedFilter)
	ON_BN_CLICKED(IDC_CLEAR, &CSnifferUIDlg::OnClickedClear)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnClickedList1)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST1, &CSnifferUIDlg::OnCustomdrawList1)

	//}}AFX_MSG_MAP

//	ON_NOTIFY(NM_KILLFOCUS, IDC_LIST1, &CSnifferUIDlg::OnKillfocusList1)
//	ON_NOTIFY(NM_SETFOCUS, IDC_LIST1, &CSnifferUIDlg::OnSetfocusList1)
ON_NOTIFY(LVN_KEYDOWN, IDC_LIST1, &CSnifferUIDlg::OnKeydownList1)
ON_COMMAND(ID_32775, &CSnifferUIDlg::On32775)
ON_COMMAND(ID_32776, &CSnifferUIDlg::On32776)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSnifferUIDlg message handlers

/**
*	@brief UI�����ʼ��
*	@param
*	@return
*/
BOOL CSnifferUIDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	/* �˵�����ʼ�� */
	m_Menu.LoadMenu(IDR_MENU1);		
	SetMenu(&m_Menu);
		

	/* �ؼ�ָ���ʼ�� */
	g_pBtnStart = &btnStart_;
	g_pBtnPause = &btnPause_;
	g_pBtnStop = &btnStop_;
	g_pBtnFilter = &btnFilter_;
	g_pBtnClear = &btnClear_;
	g_pComboBoxDevList = &comboBoxDevlist_;
	g_pListCtrlPacketList = &listCtrlPacketList_;
	g_pTreeCtrlPacketInfo = &treeCtrlPacketInfo_;
	g_pEditCtrlPacketData = &editCtrlPacketData_;
	//g_pRichEditCtrlFilterInput = &richEditCtrlFilterInput_;
	g_pComboBoxlFilterInput = &comboBoxFilterInput_;
	///* ��ť��ʼ�� */
	//g_pBtnStart->SetIcon(LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON1)));
	//g_pBtnPause->SetIcon(LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON2)));
	//g_pBtnStop->SetIcon(LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON3)));

	// ���ÿؼ�����
	//m_font.CreatePointFont(100, _T("Consolas"));
	//g_pListCtrlPacketList->SetFont(&m_font);
	//g_pTreeCtrlPacketInfo->SetFont(&m_font);
	//g_pEditCtrlPacketData->SetFont(&m_font);

	/* �б�ؼ���ʼ�� */
	initialListCtrlPacketList();

	/* �����б��ʼ������ʾ�����б�*/
	initialComboBoxDevList();

	/* �������б��ʼ�� */
	initialComboBoxFilterList();

	/* ���ļ���ʼ�� */
	g_dumpfile = NULL;
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSnifferUIDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSnifferUIDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSnifferUIDlg::OnQueryDragIcon()
{

	return (HCURSOR) m_hIcon;
}

/**
*	@brief	���¿�ʼ��ť����ʼץ��
*	@param	-
*	@return	-
*/
void CSnifferUIDlg::OnClickedStart()
{
	/* ��û��ѡ������������ʾ��Ϣ�����򣬴����߳�ץ�� */
	if (g_pComboBoxDevList->GetCurSel() == CB_ERR || g_pComboBoxDevList->GetCurSel() == 0)
	{
		AfxMessageBox(_T("��ѡ������"), MB_OK);
	}
	else
	{
		g_pBtnStart->EnableWindow(FALSE);
		g_pBtnPause->EnableWindow(TRUE);
		g_pBtnStop->EnableWindow(TRUE);
		g_pComboBoxDevList->EnableWindow(FALSE);
		myWinThread = AfxBeginThread(capture_thread, NULL, 0, NULL, 0, NULL);
		//myWinThread->m_bAutoDelete = false;
	}
}

/**
*	@brief	������ͣ��ť����ͣץ��
*	@param	-
*	@return -
*/
void CSnifferUIDlg::OnClickedPause()
{
	if (g_pBtnStart->IsWindowEnabled() == false && g_pBtnPause->IsWindowEnabled() == true && g_pBtnStop->IsWindowEnabled() == true)
	{
		g_pBtnStart->EnableWindow(TRUE);
		g_pBtnPause->EnableWindow(FALSE);
		g_pBtnStop->EnableWindow(TRUE);
		g_pComboBoxDevList->EnableWindow(FALSE);
		if (g_pAdhandle != NULL)
		{
			pcap_breakloop(g_pAdhandle);
		}

		myWinThread = NULL;
	}
}

/**
*	@brief	���½�����ť��ֹͣץ����ɾ����ӡ�����ݰ������Ϣ��������ݰ�����,�����¿�ʼץ��
*	@param	-
*	@return -
*/
void CSnifferUIDlg::OnClickedStop() 
{
	g_pBtnStart->EnableWindow(TRUE);
	g_pBtnPause->EnableWindow(FALSE);
	g_pBtnStop->EnableWindow(FALSE);
	g_pComboBoxDevList->EnableWindow(TRUE);
	if (g_pAdhandle != NULL)
	{
		pcap_breakloop(g_pAdhandle);
		pcap_close(g_pAdhandle);
		g_pAdhandle = NULL;
	}

	g_pListCtrlPacketList->DeleteAllItems();
	g_pTreeCtrlPacketInfo->DeleteAllItems();
	g_pEditCtrlPacketData->SetWindowTextA("");

	//g_listctrlPacketListRows = -1;
	//g_listctrlPacketListCols = 0;
	//g_listctrlPacketListCount = 0;

	// ��ϵ㿴�Ƿ��������
	if (!g_packetLinkList.IsEmpty())
	{
		g_packetLinkList.RemoveAll();
		//CString strDebug;
		//strDebug = "removeAll finish!";
		//AfxMessageBox(strDebug);
	}
	myWinThread = NULL;
	g_packetCaptureSum = 0;
}

/**
*	@brief	�жϹ����������Ƿ��ڹ������б���
*	@param	filterInput	����������
*	@return	true ����	false	������
*/
bool isFilterInputInFilterList(CString filterInput)
{
	// ��һ��Filter�࣬��filterList����Ϊ��Ա������isFilterInputInFilterList������Ϊ�䷽��
	CList<CString, CString> filterList;
	filterList.AddTail("Ethernet");
	filterList.AddTail("IP");
	filterList.AddTail("ARP");
	filterList.AddTail("ICMP");
	filterList.AddTail("TCP");
	filterList.AddTail("UDP");
	filterList.AddTail("DNS");
	filterList.AddTail("DHCP");
	filterList.AddTail("HTTP");

	POSITION pos = filterList.GetHeadPosition();
	for(int i = 0; i < filterList.GetCount(); ++i)
	{
		const CString &filter = filterList.GetNext(pos);
		if (filterInput == filter)
		{
			return true;
		}
	}
	return false;
}
/**
*	@brief	���¹��˰�ť�����ݹ����������Э�����������ݰ�
*	@param	-
*	@return -
*/
void CSnifferUIDlg::OnClickedFilter()
{
	// ������������RichEditCtrlʱ
	//if (g_pEditCtrlFilterInput->GetWindowTextLengthA() == 0)
	//	return;

	//CString strInput;
	//g_pEditCtrlFilterInput->GetWindowTextA(strInput);

	//if (isFilterInputInFilterList(strInput))
	//{
	//	// ��ʾ����������ɫΪ��ɫ����ʾ������ȷ
	//	g_pEditCtrlFilterInput->SetBackgroundColor(true, RGB(144, 238, 144));
	//	g_pListCtrlPacketList->DeleteAllItems();

	//	printListCtrlPacketList(g_packetLinkList, strInput);
	//}
	//else
	//{
	//	// ��ʾ����������ɫΪ��ɫ����ʾ�������
	//	g_pEditCtrlFilterInput->SetBackgroundColor(true, RGB(255, 182, 193));
	//}
	int selIndex = g_pComboBoxlFilterInput->GetCurSel();
	if (selIndex == CB_ERR || selIndex == 0)
		return;
	CString strFilter;
	g_pComboBoxlFilterInput->GetLBText(selIndex, strFilter);
	if (isFilterInputInFilterList(strFilter))
	{
		g_pListCtrlPacketList->DeleteAllItems();

		printListCtrlPacketList(g_packetLinkList, strFilter);
	}
}

/**
*	@brief	���������ť���������������ʾ�������ݰ�
*	@param	-
*	@return -
*/
void CSnifferUIDlg::OnClickedClear()
{
	//if (g_pEditCtrlFilterInput->GetWindowTextLengthA() == 0)
		//return;
	if (g_pComboBoxlFilterInput->GetWindowTextLengthA() == 0)
		return;
	g_pListCtrlPacketList->DeleteAllItems();
	printListCtrlPacketList(g_packetLinkList);

}
/**
*	@brief �������ݰ��߳���ں�����ȫ�ֺ��� 
*	@param pParam �����̵߳Ĳ���
*	@return 0 ��ʾץ���ɹ�	-1 ��ʾץ��ʧ��
*/	
UINT capture_thread(LPVOID pParam)
{
	/* ��ȡ����ѡ�е����� */
	int selIndex = g_pComboBoxDevList->GetCurSel();
	if(selIndex == CB_ERR || selIndex == 0)
	{
		AfxMessageBox(_T("��ѡ������"),MB_OK);
		return -1;
	}		
	int count = 0, selDevIndex = selIndex - 1;

	// ��׽ʵ��������Ϊ��ʱ���Ŵ������Ͷ��ļ�
	if (g_pAdhandle == NULL)
	{
		for (g_pDev = g_pAllDevs; count < selDevIndex; g_pDev = g_pDev->next, ++count);
		if ((g_pAdhandle = pcap_open_live(g_pDev->name,
			65535,
			PCAP_OPENFLAG_PROMISCUOUS,
			1000,
			g_errbuf)) == NULL)
		{
			AfxMessageBox(_T("pcap_open_live����!"), MB_OK);
		}


		/* �жϽӿڵ���·�������Ƿ�Ϊ��̫��*/
		if (pcap_datalink(g_pAdhandle) != DLT_EN10MB)
			AfxMessageBox(_T("������·�㲻����̫��"), MB_OK);


		/* �򿪶��ļ� */

		CString savePath(".\\packets\\");
		/* ��ȡ��ǰʱ�� */
		time_t tt = time(NULL);	// ��䷵�ص�ֻ��һ��ʱ���
		localtime(&tt);
		CTime currentTime(tt);

		CString dumpFileName = savePath + currentTime.Format("%Y%m%d%H%M%S") + ".cap";

		g_dumpfile = pcap_dump_open(g_pAdhandle, dumpFileName);
	}



	/* ��ʼ�������ݰ� */
	pcap_loop(g_pAdhandle, -1, packet_handler, (unsigned char *)g_dumpfile);	
}

/**
*	@brief	�������ݰ���������ȫ�ֻص�����
*	@param	dumpfile	���ڴ洢���ݰ��Ķ��ļ�	
*	@param	header		���ݰ��ײ�
*	@param	pkt_data	���ݰ���֡��
*	@return	
*/
void packet_handler(u_char *dumpfile, const struct pcap_pkthdr *header, const u_char *pkt_data)
{
	/* д����ļ� */
	pcap_dump(dumpfile, header, pkt_data);
	
	/* ��־�ļ� 
	char *path = "E:\\Code\\Sniffer\\pkt_cap_log.txt";
	FILE *save_file;
	save_file = fopen(path,"a");	//��׷����ʽд��
	*/
	
	/* �洢���ݰ������� */
	Packet pkt(pkt_data, header, ++g_packetCaptureSum);

	g_packetLinkList.AddTail(pkt);
	Packet &pkt1 = g_packetLinkList.GetTail();
	/* ���������Ƿ��������������ˣ��򲻴�ӡ���²�������ݰ� */
	int selIndexOfFilter = g_pComboBoxlFilterInput->GetCurSel();
	if (selIndexOfFilter > 0 && selIndexOfFilter != CB_ERR)
	{
		CString strFilter;
		g_pComboBoxlFilterInput->GetLBText(selIndexOfFilter, strFilter);
		if (strFilter == pkt1.protocol)
		{
			printListCtrlPacketList(pkt1);
		}
	}
	else
	{
		printListCtrlPacketList(pkt1);
	}
	
	
	
	//fclose(save_file);
}

/**
*	@brief	��ȡ���ػ��������б�,����ӡ���������������б���
*	@param	-
*	@return -
*/
void initialComboBoxDevList()
{
	g_pComboBoxDevList->AddString("ѡ������");
	g_pComboBoxDevList->SetCurSel(0);

	if (pcap_findalldevs(&g_pAllDevs, g_errbuf) == -1)
	{
		fprintf(stderr, "pcap_findalldevs()����: %s\n", g_errbuf);
		exit(1);
	}
	for (g_pDev = g_pAllDevs; g_pDev != NULL; g_pDev = g_pDev->next)
	{
		if (g_pDev->description != NULL)
		{
			g_pComboBoxDevList->AddString(g_pDev->description);
		}			
	}
}

/**
*	@brief	�������б��ʼ��
*	@param	-
*	@return -
*/
void initialComboBoxFilterList()
{
	CList<CString, CString> filterList;
	filterList.AddTail("Ethernet");
	filterList.AddTail("IP");
	filterList.AddTail("ARP");
	filterList.AddTail("ICMP");
	filterList.AddTail("TCP");
	filterList.AddTail("UDP");
	filterList.AddTail("DNS");
	filterList.AddTail("DHCP");
	filterList.AddTail("HTTP");

	g_pComboBoxlFilterInput->AddString("ѡ�����������ѡ��");
	g_pComboBoxlFilterInput->SetCurSel(0);

	POSITION pos = filterList.GetHeadPosition();
	for(int i = 0; i < filterList.GetCount(); ++i)
	{
		g_pComboBoxlFilterInput->AddString(filterList.GetNext(pos));
	}
}

/**
*	@brief	�б�ؼ���ʼ��
*	@param	-
*	@return -
*/
void initialListCtrlPacketList()
{
	DWORD dwStyle = g_pListCtrlPacketList->GetExtendedStyle();	// ����б�ؼ���������
	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_GRIDLINES;

	g_pListCtrlPacketList->SetExtendedStyle(dwStyle);
	g_pListCtrlPacketList->InsertColumn(0, "���", LVCFMT_CENTER, 40);
	g_pListCtrlPacketList->InsertColumn(1, "ʱ��", LVCFMT_CENTER, 140);
	g_pListCtrlPacketList->InsertColumn(2, "Э��", LVCFMT_CENTER, 60);
	g_pListCtrlPacketList->InsertColumn(3, "����", LVCFMT_CENTER, 50);
	g_pListCtrlPacketList->InsertColumn(4, "ԴMAC��ַ", LVCFMT_CENTER, 180);
	g_pListCtrlPacketList->InsertColumn(5, "Ŀ��MAC��ַ", LVCFMT_CENTER, 180);
	g_pListCtrlPacketList->InsertColumn(6, "ԴIP��ַ", LVCFMT_CENTER, 120);
	g_pListCtrlPacketList->InsertColumn(7, "Ŀ��IP��ַ", LVCFMT_CENTER, 120);

}


/**
*	@brief	��ӡ���ݰ���Ҫ��Ϣ���б�ؼ�
*	@param	���ݰ�
*	@return	0 ��ӡ�ɹ�	-1 ��ӡʧ��
*/
int printListCtrlPacketList(const Packet &pkt)
{
	if (pkt.isEmpty())
	{
		return -1;
	}
	int listctrlPacketListCols = 0;
	/* ��ӡ��� */
	CString	strNum;
	strNum.Format("%d", pkt.num);
//	int row = g_pListCtrlPacketList->InsertItem(g_pListCtrlPacketList->GetItemCount(), strNum);

	UINT mask = 0;
	mask |= LVIF_PARAM;
	mask |= LVIF_TEXT;
	int row = g_pListCtrlPacketList->InsertItem(mask, g_pListCtrlPacketList->GetItemCount(), strNum, 0, 0, 0, (LPARAM)&(pkt.protocol));

	/* ��ӡʱ�� */
	CTime pktArrivalTime( (time_t)(pkt.header->ts.tv_sec) ) ;
	CString strPktArrivalTime = pktArrivalTime.Format("%Y/%m/%d %H:%M:%S");
	g_pListCtrlPacketList->SetItemText(row, ++listctrlPacketListCols, strPktArrivalTime);

	/* ��ӡЭ�� */	
	if (!pkt.protocol.IsEmpty())
	{
		g_pListCtrlPacketList->SetItemText(row, ++listctrlPacketListCols, pkt.protocol);
	
	}
	else
	{
		++listctrlPacketListCols;
	}

	/* ��ӡ���� */
	CString strCaplen;
	strCaplen.Format("%d", pkt.header->caplen);
	g_pListCtrlPacketList->SetItemText(row, ++listctrlPacketListCols, strCaplen);

	/* ��ӡԴĿMAC��ַ */
	if (pkt.ethh != NULL)
	{
		CString strSrcMAC = MACAddr2CString(pkt.ethh->srcaddr);
		CString strDstMAC = MACAddr2CString(pkt.ethh->dstaddr);

		g_pListCtrlPacketList->SetItemText(row, ++listctrlPacketListCols, strSrcMAC);
		g_pListCtrlPacketList->SetItemText(row, ++listctrlPacketListCols, strDstMAC);
	}
	else
	{
		listctrlPacketListCols += 2;
	}

	/* ��ӡԴĿIP��ַ */
	if (pkt.iph != NULL)
	{
		CString strSrcIP = IPAddr2CString(pkt.iph->srcaddr);
		CString strDstIP = IPAddr2CString(pkt.iph->dstaddr);

		g_pListCtrlPacketList->SetItemText(row, ++listctrlPacketListCols, strSrcIP);
		g_pListCtrlPacketList->SetItemText(row, ++listctrlPacketListCols, strDstIP);
	}
	else
	{
		//g_listctrlPacketListCols += 2;
		listctrlPacketListCols += 2;
	}
	//g_listctrlPacketListCols = 0;		// �и�λ 

	return 0;
}

/**
*	@brief	��ӡ���ݰ���Ҫ��Ϣ���б�ؼ�
*	@param	���ݰ�����
*	@return	0 ��ӡ�ɹ�	-1 ��ӡʧ��
*/
int printListCtrlPacketList(const CList<Packet, Packet> &packetLinkList)
{
	if (packetLinkList.IsEmpty())
	{
		return -1;
	}
	//for (int i = 0; i < packetLinkList.GetCount(); ++i)
	//{
	//	POSITION pos = packetLinkList.FindIndex(i);
	//	printListCtrlPacketList(g_packetLinkList.GetAt(pos));
	//}

	POSITION pos = packetLinkList.GetHeadPosition();
	/*while (pos != NULL)*/
	for (int i = 0; i < packetLinkList.GetCount(); ++i)
	{
		printListCtrlPacketList(g_packetLinkList.GetNext(pos));
	}
	return 0;
}

/**
*	@brief	�������ݰ��������ݹ��������ƴ�ӡ���ݰ����б�ؼ�
*	@param	packetLinkList	���ݰ�����
*	@param	filter	����������
*	@return	0 ��ӡ�ɹ�	-1	��ӡʧ��
*/
int printListCtrlPacketList(const CList<Packet, Packet> &packetLinkList, const CString &filter)
{
	if (packetLinkList.IsEmpty() || filter.IsEmpty())
	{
		return -1;
	}
		
	POSITION pos = packetLinkList.GetHeadPosition();
	for (int i = 0; i < packetLinkList.GetCount(); ++i)
	{
		const Packet &pkt = packetLinkList.GetNext(pos);
		if (pkt.protocol == filter)
		{
			printListCtrlPacketList(pkt);
		}
	}
	return 0;
}

/**
*	@brief ��ӡ���ݰ��ֽ������༭��16������������
*	@param	pkt	���ݰ�
*	@return 0 ��ӡ�ɹ�	-1 ��ӡʧ��
*/
int printEditCtrlPacketData(const Packet & pkt)
{
	if (pkt.isEmpty())
	{
		return -1;
	}

	CString strPacketData, strTmp;
	u_char* pHexPacketData = pkt.pkt_data;
	u_char* pASCIIPacketData = pkt.pkt_data;
	for (int byteCount = 0,  byteCount16=0, offset = 0; byteCount < pkt.header->caplen && pHexPacketData != NULL; ++byteCount)
	{
		/* ����ǰ�ֽ������ף���ӡ����ƫ���� */
		if (byteCount % 16 == 0)
		{
			strTmp.Format("%04X:", offset);
			strPacketData += strTmp + " ";
		}

		/* ��ӡ16�����ֽ� */
		strTmp.Format("%02X", *pHexPacketData);
		strPacketData += strTmp + " ";
		++pHexPacketData;
		++byteCount16;
		
		switch (byteCount16)
		{
		case 8:
		{
			/* ÿ��ȡ8���ֽڴ�ӡһ���Ʊ�� */
			strPacketData += "\t";
			//strPacketData += "#";
		}
		break;
		case 16:
		{
			/* ÿ��ȡ16���ֽڴ�ӡ��Ӧ�ֽڵ�ASCII�ַ���ֻ��ӡ��ĸ���� */
			if (byteCount16 == 16)
			{
				strPacketData += " ";
				for (int charCount = 0; charCount < 16; ++charCount, ++pASCIIPacketData)
				{
					strTmp.Format("%c", isalnum(*pASCIIPacketData) ? *pASCIIPacketData : '.');
					strPacketData += strTmp;
				}
				strPacketData += "\r\n";
				offset += 16;
				byteCount16 = 0;
			}
		}
		break;
		default:break;
		}
	}
	/* �����ݰ��ܳ��Ȳ���16�ֽڶ���ʱ����ӡ���һ���ֽڶ�Ӧ��ASCII�ַ� */
	if (pkt.header->caplen % 16 != 0)
	{
		/* �ո���䣬��֤�ֽ���16�ֽڶ��� */
		for (int spaceCount = 0, byteCount16 = (pkt.header->caplen % 16); spaceCount < 16 - (pkt.header->caplen % 16); ++spaceCount)
		{
			strPacketData += "  ";
			strPacketData += " ";
			++byteCount16;
			if (byteCount16 == 8)
			{
				strPacketData += "\t";
				//strPacketData += "#";
			}
		}
		strPacketData += " ";
		/* ��ӡ���һ���ֽڶ�Ӧ��ASCII�ַ� */
		for (int charCount = 0; charCount < (pkt.header->caplen % 16); ++charCount, ++pASCIIPacketData)
		{
			strTmp.Format("%c", isalnum(*pASCIIPacketData) ? *pASCIIPacketData : '.');
			strPacketData += strTmp;
		}
		strPacketData += "\r\n";
	}
	
	g_pEditCtrlPacketData->SetWindowTextA(strPacketData);

	return 0;
}

/**
*	@brief	��ӡ���ݰ��ײ�������������οؼ�
*	@param	pkt	���ݰ�
*	@return	0 ��ӡ�ɹ�	-1 ��ӡʧ��
*/
int printTreeCtrlPacketInfo(const Packet &pkt)
{
	if (pkt.isEmpty())
	{
		return -1;
	}
	g_pTreeCtrlPacketInfo->DeleteAllItems();

	/* ������Ž�� */
	CString strText;

	CTime pktArrivalTime((time_t)(pkt.header->ts.tv_sec));
	CString strPktArrivalTime = pktArrivalTime.Format("%Y/%m/%d %H:%M:%S");

	strText.Format("��%d�����ݰ���%s, �� %hu �ֽ�, ���� %hu �ֽڣ�",  pkt.num, strPktArrivalTime, pkt.header->len, pkt.header->caplen);

	HTREEITEM rootNode = g_pTreeCtrlPacketInfo->InsertItem(strText, TVI_ROOT);
	if (pkt.ethh != NULL)
	{
		printEthernet2TreeCtrl(pkt, rootNode);
	}

	g_pTreeCtrlPacketInfo->Expand(rootNode, TVE_EXPAND);
	return 0;
}

/**
*	@brief	��ӡ��̫��֡�ײ������οؼ�
*	@param	pkt ���ݰ�
*	@param	parentNode ���ڵ�
*	@return	0 ����ɹ�	-1 ����ʧ��
*/
int printEthernet2TreeCtrl(const Packet &pkt, HTREEITEM &parentNode)
{
	if (pkt.isEmpty() || pkt.ethh == NULL || parentNode == NULL)
	{
		return -1;
	}
	/* ��ȡԴĿMAC��ַ */
	CString strSrcMAC = MACAddr2CString(pkt.ethh->srcaddr);
	CString	strDstMAC = MACAddr2CString(pkt.ethh->dstaddr);
	CString strEthType;
	strEthType.Format("0x%04X", ntohs(pkt.ethh->eth_type));

	HTREEITEM	EthNode = g_pTreeCtrlPacketInfo->InsertItem( "��̫����" + strSrcMAC + " -> " + strDstMAC + "��", parentNode, 0);

	g_pTreeCtrlPacketInfo->InsertItem("Ŀ��MAC��ַ��" + strDstMAC, EthNode, 0);
	g_pTreeCtrlPacketInfo->InsertItem("ԴMAC��ַ��" + strSrcMAC, EthNode, 0);
	g_pTreeCtrlPacketInfo->InsertItem("���ͣ�" + strEthType, EthNode, 0);

	if (pkt.iph != NULL)
	{
		printIP2TreeCtrl(pkt, parentNode);
	}
	else if (pkt.arph != NULL)
	{
		printARP2TreeCtrl(pkt, parentNode);
	}
	return 0;
}

/**
*	@brief	��ӡIP�ײ������οؼ�
*	@param	pkt ���ݰ�
*	@param	parentNode ���ڵ�
*	@return	0 ����ɹ�	-1 ����ʧ��
*/
int printIP2TreeCtrl(const Packet & pkt, HTREEITEM & parentNode)
{
	if (pkt.isEmpty() || pkt.iph == NULL || parentNode == NULL)
	{
		return -1;
	}
	HTREEITEM IPNode = g_pTreeCtrlPacketInfo->InsertItem("IP��" + IPAddr2CString(pkt.iph->srcaddr) + " -> " + IPAddr2CString(pkt.iph->dstaddr) + "��", parentNode, 0);
	CString strText;

	strText.Format("�汾�ţ�%d", pkt.iph->ver_headerlen >> 4);
	g_pTreeCtrlPacketInfo->InsertItem(strText, IPNode, 0);
	
	strText.Format("�ײ����ȣ�%d �ֽڣ�%d��", pkt.getIPHeaderLegnth(), pkt.getIPHeaderLengthRaw());
	g_pTreeCtrlPacketInfo->InsertItem(strText, IPNode, 0);
	
	strText.Format("����������0x%02X", pkt.iph->tos);
	g_pTreeCtrlPacketInfo->InsertItem(strText, IPNode, 0);
	
	strText.Format("�ܳ��ȣ�%hu", ntohs(pkt.iph->totallen));
	g_pTreeCtrlPacketInfo->InsertItem(strText, IPNode, 0);
	
	strText.Format("��ʶ��0x%04hX��%hu��", ntohs(pkt.iph->identifier), ntohs(pkt.iph->identifier));
	g_pTreeCtrlPacketInfo->InsertItem(strText, IPNode, 0);
				
	strText.Format("��־��0x%02X", pkt.getIPFlags());
	HTREEITEM IPFlagNode = g_pTreeCtrlPacketInfo->InsertItem(strText, IPNode, 0);
	
	strText = "RSV��0";
	g_pTreeCtrlPacketInfo->InsertItem(strText, IPFlagNode, 0);
	
	strText.Format("DF��%d", pkt.getIPFlagDF());
	g_pTreeCtrlPacketInfo->InsertItem(strText, IPFlagNode, 0);

	strText.Format("MF��%d", pkt.getIPFlagsMF());
	g_pTreeCtrlPacketInfo->InsertItem(strText, IPFlagNode, 0);
	
	strText.Format("Ƭƫ�ƣ�%d", pkt.getIPOffset());
	g_pTreeCtrlPacketInfo->InsertItem(strText, IPNode, 0);
	
	strText.Format("TTL��%u", pkt.iph->ttl);
	g_pTreeCtrlPacketInfo->InsertItem(strText, IPNode, 0);
	
	switch(pkt.iph->protocol)
	{
	case PROTOCOL_ICMP:	strText = "Э�飺ICMP��1��";	break;
	case PROTOCOL_TCP:	strText = "Э�飺TCP��6��";	break;
	case PROTOCOL_UDP:	strText = "Э�飺UDP��17��";	break;
	default:			strText.Format("Э�飺δ֪��%d��", pkt.iph->protocol);	break;
	}
	g_pTreeCtrlPacketInfo->InsertItem(strText, IPNode, 0);
	
	strText.Format("У��ͣ�0x%02hX", ntohs(pkt.iph->checksum));
	g_pTreeCtrlPacketInfo->InsertItem(strText, IPNode, 0);
	
	strText = "ԴIP��ַ��" + IPAddr2CString(pkt.iph->srcaddr);
	g_pTreeCtrlPacketInfo->InsertItem(strText, IPNode, 0);
	
	strText = "Ŀ��IP��ַ��" + IPAddr2CString(pkt.iph->dstaddr);
	g_pTreeCtrlPacketInfo->InsertItem(strText, IPNode, 0);
	
	if (pkt.icmph != NULL)
	{
		printICMP2TreeCtrl(pkt, parentNode);
	}
	else if (pkt.tcph != NULL)
	{
		printTCP2TreeCtrl(pkt, parentNode);
	}
	else if (pkt.udph != NULL)
	{
		printUDP2TreeCtrl(pkt, parentNode);
	}
	return 0;
}

/**
*	@brief	��ӡARP�ײ������οؼ�
*	@param	pkt ���ݰ�
*	@param	parentNode ���ڵ�
*	@return	0 ����ɹ�	-1 ����ʧ��
*/
int printARP2TreeCtrl(const Packet & pkt, HTREEITEM & parentNode)
{
	if (pkt.isEmpty() || pkt.arph == NULL || parentNode == NULL)
	{
		return -1;
	}
	HTREEITEM ARPNode;
	CString strText, strTmp;

	switch(ntohs(pkt.arph->opcode))
	{
	case ARP_OPCODE_REQUET:	strText.Format("ARP������)");	break;
	case ARP_OPCODE_REPLY:	strText.Format("ARP����Ӧ)");	break;
	default:				strText.Format("ARP");			break;
	}	
	ARPNode= g_pTreeCtrlPacketInfo->InsertItem(strText, 0, 0, parentNode, 0);
	
	strText.Format("Ӳ�����ͣ�%hu", ntohs(pkt.arph->hwtype));
	g_pTreeCtrlPacketInfo->InsertItem(strText, ARPNode, 0);
	
	strText.Format("Э�����ͣ�0x%04hx (%hu)", ntohs(pkt.arph->ptype), ntohs(pkt.arph->ptype));
	g_pTreeCtrlPacketInfo->InsertItem(strText, ARPNode, 0);
	
	strText.Format("Ӳ����ַ���ȣ�%u", pkt.arph->hwlen);
	g_pTreeCtrlPacketInfo->InsertItem(strText, ARPNode, 0);
	
	strText.Format("Э���ַ���ȣ�%u", pkt.arph->plen);
	g_pTreeCtrlPacketInfo->InsertItem(strText, ARPNode, 0);
	
	switch(ntohs(pkt.arph->opcode))
	{
	case ARP_OPCODE_REQUET:	strText.Format("OP�룺����%hu��", ntohs(pkt.arph->opcode));	break;
	case ARP_OPCODE_REPLY:	strText.Format("OP�룺��Ӧ��%hu��", ntohs(pkt.arph->opcode));	break;
	default:				strText.Format("OP�룺δ֪��%hu��", ntohs(pkt.arph->opcode));	break;
	}
	g_pTreeCtrlPacketInfo->InsertItem(strText, ARPNode, 0);
	
	strText = "ԴMAC��ַ��" + MACAddr2CString(pkt.arph->srcmac);
	g_pTreeCtrlPacketInfo->InsertItem(strText, ARPNode, 0);
	
	strText = "ԴIP��ַ��" + IPAddr2CString(pkt.arph->srcip);
	g_pTreeCtrlPacketInfo->InsertItem(strText, ARPNode, 0);
			
	strText = "Ŀ��MAC��ַ��" + MACAddr2CString(pkt.arph->dstmac);
	g_pTreeCtrlPacketInfo->InsertItem(strText, ARPNode, 0);
	
	strText = "Ŀ��IP��ַ��" + IPAddr2CString(pkt.arph->dstip);
	g_pTreeCtrlPacketInfo->InsertItem(strText, ARPNode, 0);
	
	return 0;
}

/**
*	@brief	��ӡICMP�ײ������οؼ�
*	@param	pkt ���ݰ�
*	@param	parentNode ���ڵ�
*	@return	0 ����ɹ�	-1 ����ʧ��
*/
int printICMP2TreeCtrl(const Packet & pkt, HTREEITEM & parentNode)
{
	if (pkt.isEmpty() || pkt.icmph == NULL || parentNode == NULL)
	{
		return -1;
	}
	HTREEITEM ICMPNode;
	CString strText, strTmp;
	
	strText = "ICMP";
	switch(pkt.icmph->type)
	{
		case ICMP_TYPE_ECHO_REPLY:					strTmp = "����ӦӦ�𱨸棩";		break;
		case ICMP_TYPE_DESTINATION_UNREACHABLE:		strTmp = "�����޲��ɴﱨ�棩";		break;
		case ICMP_TYPE_SOURCE_QUENCH:				strTmp = "��Դ�����Ʊ��棩";		break;
		case ICMP_TYPE_REDIRECT:					strTmp = "���ض��򱨸棩";			break;
		case ICMP_TYPE_ECHO:						strTmp = "����Ӧ���󱨸棩";		break;
		case ICMP_TYPE_ROUTER_ADVERTISEMENT:		strTmp = "��·����ͨ�汨�棩";		break;
		case ICMP_TYPE_ROUTER_SOLICITATION:			strTmp = "��·����ѯ�ʱ��棩";		break;
		case ICMP_TYPE_TIME_EXCEEDED:				strTmp = "����ʱ���棩";			break;
		case ICMP_TYPE_PARAMETER_PROBLEM:			strTmp = "�����ݱ��������󱨸棩";	break;
		case ICMP_TYPE_TIMESTAMP:					strTmp = "��ʱ������󱨸棩";		break;
		case ICMP_TYPE_TIMESTAMP_REPLY:				strTmp = "��ʱ�����Ӧ���棩";		break;
		default:									strTmp.Format("��δ֪��");			break;
	}
	strText += strTmp;
	ICMPNode = g_pTreeCtrlPacketInfo->InsertItem(strText, parentNode, 0);
	
	IP_Address addr = *(IP_Address*)&(pkt.icmph->others);
	u_short id = pkt.getICMPID();
	u_short seq = pkt.getICMPSeq();
	
	strText.Format("���ͣ�%u", pkt.icmph->type);
	g_pTreeCtrlPacketInfo->InsertItem(strText, ICMPNode, 0);

	switch(pkt.icmph->type)
	{
		case ICMP_TYPE_ECHO_REPLY:
		{
			strText = "���룺0";
			g_pTreeCtrlPacketInfo->InsertItem(strText, ICMPNode, 0);

			strText.Format("У���:0x%04hX", ntohs(pkt.icmph->chksum));
			g_pTreeCtrlPacketInfo->InsertItem(strText, ICMPNode, 0);

			strText.Format("��ʶ��%hu", id);
			g_pTreeCtrlPacketInfo->InsertItem(strText, ICMPNode, 0);

			strText.Format("��ţ�%hu", seq);
			g_pTreeCtrlPacketInfo->InsertItem(strText, ICMPNode, 0);

			break;
		}


		case ICMP_TYPE_DESTINATION_UNREACHABLE: 
			strText = "���룺";
			switch(pkt.icmph->code)
			{
				case ICMP_TYPE_DESTINATION_UNREACHABLE_CODE_NET_UNREACHABLE: 
					strText.Format("���粻�ɴ� ��%d��", pkt.icmph->code);
					break;

				case ICMP_TYPE_DESTINATION_UNREACHABLE_CODE_HOST_UNREACHABLE: 
					strText.Format("�������ɴ� ��%d��", pkt.icmph->code);
					break;

				case ICMP_TYPE_DESTINATION_UNREACHABLE_CODE_PROTOCOL_UNREACHABLE: 
					strText.Format("Э�鲻�ɴ� ��%d��", pkt.icmph->code);
					break;

				case ICMP_TYPE_DESTINATION_UNREACHABLE_CODE_PORT_UNREACHABLE: 
					strText.Format("�˿ڲ��ɴ� ��%d��", pkt.icmph->code);
					break;

				case 6: 
					strTmp = "��������δ֪ ��6��"; 
					break;

				case 7: 
					strTmp = "��������δ֪ ��7��"; 
					break;

				default: 
					strText.Format("δ֪ ��%d��", pkt.icmph->code); break;
			}
			strText += strTmp;
			g_pTreeCtrlPacketInfo->InsertItem(strText, ICMPNode, 0);
	
			strText.Format("У��ͣ�0x%04hX", ntohs(pkt.icmph->chksum));
			g_pTreeCtrlPacketInfo->InsertItem(strText, ICMPNode, 0);
			break;
	
		case ICMP_TYPE_SOURCE_QUENCH : 
			strText.Format("���룺%d", ICMP_TYPE_SOURCE_QUENCH_CODE);
			g_pTreeCtrlPacketInfo->InsertItem(strText, ICMPNode, 0);
				
			strText.Format("У��ͣ�0x%04hX", ntohs(pkt.icmph->chksum));
			g_pTreeCtrlPacketInfo->InsertItem(strText, ICMPNode, 0);
			break;
	
		case ICMP_TYPE_REDIRECT: 
				strText = "���룺";
				switch(pkt.icmph->code)
				{
				case ICMP_TYPE_REDIRECT_CODE_REDIRECT_DATAGRAMS_FOR_THE_NETWORK:	
					strText.Format("���ض������ض���%d)", pkt.icmph->code);
					break;

				case ICMP_TYPE_REDIRECT_CODE_REDIRECT_DATAGRAMS_FOR_THE_HOST: 
					strText.Format("���ض������ض��� ��%d)", pkt.icmph->code);
					break;

				case ICMP_TYPE_REDIRECT_CODE_REDIRECT_DATAGRAMS_FOR_THE_TOS_AND_NETWORK: 
					strText.Format("����ָ���ķ������Ͷ��ض������ض��� ��%d��", pkt.icmph->code);
					break;

				case ICMP_TYPE_REDIRECT_CODE_REDIRECT_DATAGRAMS_FOR_THE_TOS_AND_HOST: 
					strText.Format("����ָ���ķ������Ͷ��ض������ض��� ��%d��", pkt.icmph->code); 
					break;
				}
				strText += strTmp;
				g_pTreeCtrlPacketInfo->InsertItem(strText, ICMPNode, 0);
	
				strText.Format("У��ͣ�0x%04hx", ntohs(pkt.icmph->chksum));
				g_pTreeCtrlPacketInfo->InsertItem(strText, ICMPNode, 0);
	
				strText = "Ŀ��·������IP��ַ��" + IPAddr2CString(addr);
				g_pTreeCtrlPacketInfo->InsertItem(strText, ICMPNode, 0);
				break;

		case ICMP_TYPE_ECHO:
			strText.Format("���룺%d", pkt.icmph->code);
			g_pTreeCtrlPacketInfo->InsertItem(strText, ICMPNode, 0);

			strText.Format("У��ͣ�0x%04hX", ntohs(pkt.icmph->chksum));
			g_pTreeCtrlPacketInfo->InsertItem(strText, ICMPNode, 0);

			strText.Format("��ʶ��%hu", id);
			g_pTreeCtrlPacketInfo->InsertItem(strText, ICMPNode, 0);

			strText.Format("��ţ�%hu", seq);
			g_pTreeCtrlPacketInfo->InsertItem(strText, ICMPNode, 0);
			break;

		case ICMP_TYPE_TIME_EXCEEDED: 
			strText = "���룺";
			switch(pkt.icmph->code)
			{
				case ICMP_TYPE_TIME_EXCEEDED_CODE_TTL_EXCEEDED_IN_TRANSIT: 
					strText.Format("TTL��ʱ ��%d��", pkt.icmph->code);	
					break;
				case ICMP_TYPE_TIME_EXCEEDED_CODE_FRAGMENT_REASSEMBLY_TIME_EXCEEDE: 
					strText.Format("��Ƭ���鳬ʱ ��%d��", pkt.icmph->code);
					break;
			}
			strText += strTmp;
			g_pTreeCtrlPacketInfo->InsertItem(strText, ICMPNode, 0);
	
			strText.Format("У��ͣ�0x%04hx", ntohs(pkt.icmph->chksum));
			g_pTreeCtrlPacketInfo->InsertItem(strText, ICMPNode, 0);
	
			break;
	
		default: 
			strText.Format("���룺%d", pkt.icmph->code);
			g_pTreeCtrlPacketInfo->InsertItem(strText, 0, 0, ICMPNode, 0);

			strText.Format("У��ͣ�0x%04hX", pkt.icmph->chksum);
			g_pTreeCtrlPacketInfo->InsertItem(strText, 0, 0, ICMPNode, 0);

			break;
		}
	return 0;
}

/**
*	@brief	��ӡTCP�ײ������οؼ�
*	@param	pkt ���ݰ�
*	@param	parentNode ���ڵ�
*	@return	0 ����ɹ�	-1 ����ʧ��
*/
int printTCP2TreeCtrl(const Packet & pkt, HTREEITEM & parentNode)
{
	if (pkt.isEmpty() || pkt.tcph == NULL || parentNode == NULL)
	{
		return -1;
	}
	HTREEITEM TCPNode;
	CString strText, strTmp;
							
	strText.Format("TCP��%hu -> %hu��", ntohs(pkt.tcph->srcport), ntohs(pkt.tcph->dstport));
	TCPNode = g_pTreeCtrlPacketInfo->InsertItem(strText,parentNode, 0);
							
	strText.Format("Դ�˿ڣ�%hu", ntohs(pkt.tcph->srcport));
	g_pTreeCtrlPacketInfo->InsertItem(strText, TCPNode, 0);
							
	strText.Format("Ŀ�Ķ˿ڣ�%hu", ntohs(pkt.tcph->dstport));
	g_pTreeCtrlPacketInfo->InsertItem(strText, TCPNode, 0);
							
	strText.Format("���кţ�0x%0lX", ntohl(pkt.tcph->seq));
	g_pTreeCtrlPacketInfo->InsertItem(strText, TCPNode, 0);
							
	strText.Format("ȷ�Ϻţ�0x%0lX", ntohl(pkt.tcph->ack));
	g_pTreeCtrlPacketInfo->InsertItem(strText, TCPNode, 0);
							
	strText.Format("�ײ����ȣ�%d �ֽڣ�%d��", pkt.getTCPHeaderLength(), pkt.getTCPHeaderLengthRaw());
	g_pTreeCtrlPacketInfo->InsertItem(strText, TCPNode, 0);
							
	strText.Format("��־��0x%03X", pkt.getTCPFlags());
	HTREEITEM TCPFlagNode = g_pTreeCtrlPacketInfo->InsertItem(strText, TCPNode, 0);
							
	strText.Format("URG��%d", pkt.getTCPFlagsURG());
	g_pTreeCtrlPacketInfo->InsertItem(strText, TCPFlagNode, 0);
							
	strText.Format("ACK��%d", pkt.getTCPFlagsACK());
	g_pTreeCtrlPacketInfo->InsertItem(strText, TCPFlagNode, 0);
							
	strText.Format("PSH��%d", pkt.getTCPFlagsPSH());
	g_pTreeCtrlPacketInfo->InsertItem(strText, TCPFlagNode, 0);
							
	strText.Format("RST��%d", pkt.getTCPFlagsRST());
	g_pTreeCtrlPacketInfo->InsertItem(strText, TCPFlagNode, 0);

	strText.Format("SYN��%d", pkt.getTCPFlagsSYN());
	g_pTreeCtrlPacketInfo->InsertItem(strText, TCPFlagNode, 0);
							
	strText.Format("FIN��%d", pkt.getTCPFlagsFIN());
	g_pTreeCtrlPacketInfo->InsertItem(strText, TCPFlagNode, 0);
							 
	strText.Format("���ڴ�С��%hu", ntohs(pkt.tcph->win_size));
	g_pTreeCtrlPacketInfo->InsertItem(strText, TCPNode, 0);
							
	strText.Format("У��ͣ�0x%04hX", ntohs(pkt.tcph->chksum));
	g_pTreeCtrlPacketInfo->InsertItem(strText, TCPNode, 0);
							
	strText.Format("����ָ�룺%hu", ntohs(pkt.tcph->urg_ptr));
	g_pTreeCtrlPacketInfo->InsertItem(strText, TCPNode, 0);

	if (pkt.dnsh != NULL)
	{
		printDNS2TreeCtrl(pkt, parentNode);
	}
	else if (pkt.dhcph != NULL)
	{
		printDHCP2TreeCtrl(pkt, parentNode);
	}
	else if (pkt.httpmsg != NULL)
	{
		printHTTP2TreeCtrl(pkt, parentNode);
	}

	return 0;
}

/**
*	@brief	��ӡUDP�ײ������οؼ�
*	@param	pkt ���ݰ�
*	@param	parentNode ���ڵ�
*	@return	0 ����ɹ�	-1 ����ʧ��
*/
int printUDP2TreeCtrl(const Packet & pkt, HTREEITEM & parentNode)
{
	if (pkt.isEmpty() || pkt.udph == NULL || parentNode == NULL)
	{
		return -1;
	}
	HTREEITEM UDPNode;		
	CString strText, strTmp;
							
	strText.Format("UDP��%hu -> %hu��", ntohs(pkt.udph->srcport), ntohs(pkt.udph->dstport));
	UDPNode = g_pTreeCtrlPacketInfo->InsertItem(strText, parentNode, 0);
							
	strText.Format("Դ�˿ڣ�%hu", ntohs(pkt.udph->srcport));
	g_pTreeCtrlPacketInfo->InsertItem(strText, UDPNode, 0);
							
	strText.Format("Ŀ�Ķ˿ڣ�%hu", ntohs(pkt.udph->dstport));
	g_pTreeCtrlPacketInfo->InsertItem(strText, UDPNode, 0);
							
	strText.Format("���ȣ�%hu", ntohs(pkt.udph->len));
	g_pTreeCtrlPacketInfo->InsertItem(strText, UDPNode, 0);
							
	strText.Format("У��ͣ�0x%04hX", ntohs(pkt.udph->checksum));
	g_pTreeCtrlPacketInfo->InsertItem(strText, UDPNode, 0);

	if (pkt.dnsh != NULL)
	{
		//printDNS2TreeCtrl(pkt, parentNode);
	}
	else if (pkt.dhcph != NULL)
	{
		printDHCP2TreeCtrl(pkt, parentNode);
	}
	return 0;
}

/** 
*	@brief	��ӡDNS������
*	@param	pkt	���ݰ�
*	@param	parentNode ���ڵ�
*	@return DNS���
*/
HTREEITEM printDNSBanner(const Packet &pkt, HTREEITEM &parentNode)
{
	if (pkt.isEmpty() || parentNode == NULL)
	{
		return NULL;
	}
	CString strText;

	switch (pkt.getDNSFlagsQR())
	{
	case DNS_FLAGS_QR_REQUEST:	strText = "DNS������";		break;
	case DNS_FLAGS_QR_REPLY:	strText = "DNS����Ӧ��";		break;
	}
	return g_pTreeCtrlPacketInfo->InsertItem(strText, parentNode, 0);
}


/**
*	@brief	��ӡDNS�ײ�
*	@param	pkt	���ݰ�
*	@param	parentNode	���ڵ�
*	@return 0 ��ӡ�ɹ�	-1 ��ӡʧ��
*/
int printDNSHeader(const Packet &pkt, HTREEITEM & parentNode)
{
	if (pkt.isEmpty() || pkt.dnsh == NULL || parentNode == NULL)
	{
		return -1;
	}
	CString strText, strTmp;
	strText.Format("��ʶ��0x%04hX (%hu)", ntohs(pkt.dnsh->identifier), ntohs(pkt.dnsh->identifier));
	g_pTreeCtrlPacketInfo->InsertItem(strText, parentNode, 0);

	strText.Format("��־��0x%04hX", ntohs(pkt.dnsh->flags));
	strText += strTmp;

	HTREEITEM DNSFlagNode = g_pTreeCtrlPacketInfo->InsertItem(strText, parentNode, 0);
	/* ��־���ֶ� */
	switch (pkt.getDNSFlagsQR())
	{
	case DNS_FLAGS_QR_REQUEST:	strText = "QR��; ��ѯ���� ��0��";	break;
	case DNS_FLAGS_QR_REPLY:	strText = "QR��; ��Ӧ���� ��1��";	break;
	}
	g_pTreeCtrlPacketInfo->InsertItem(strText, DNSFlagNode, 0);

	switch (pkt.getDNSFlagsOPCODE())
	{
	case DNS_FLAGS_OPCODE_STANDARD_QUERY:			strText = "OPCODE����׼��ѯ ��0��";			break;
	case DNS_FLAGS_OPCODE_INVERSE_QUERY:			strText = "OPCODE�������ѯ ��1��";			break;
	case DNS_FLAGS_OPCODE_SERVER_STATUS_REQUEST:	strText = "OPCODE��������״̬���� ��2��";	break;
	}
	g_pTreeCtrlPacketInfo->InsertItem(strText, DNSFlagNode, 0);

	switch (pkt.getDNSFlagsAA())
	{
	case 0:	strText = "AA������Ȩ�ش� ��0��";	break;
	case 1: strText = "AA����Ȩ�ش� ��1��";		break;
	}
	g_pTreeCtrlPacketInfo->InsertItem(strText, DNSFlagNode, 0);


	switch (pkt.getDNSFlagsTC())
	{
	case 0: strText = "TC������δ�ض� ��0��";	break;
	case 1: strText = "TC�����Ľض� ��1��";		break;
	}
	g_pTreeCtrlPacketInfo->InsertItem(strText, DNSFlagNode, 0);


	switch (pkt.getDNSFlagsRD())
	{
	case 0: strText = "RD��0";						break;
	case 1: strText = "RD��ϣ�����еݹ��ѯ ��1��";	break;
	}
	g_pTreeCtrlPacketInfo->InsertItem(strText, DNSFlagNode, 0);

	switch (pkt.getDNSFlagsRA())
	{
	case 0: strText = "RA����������֧�ֵݹ��ѯ ��0��"; break;
	case 1: strText = "RA��������֧�ֵݹ��ѯ ��1��";	break;
	}
	g_pTreeCtrlPacketInfo->InsertItem(strText, DNSFlagNode, 0);

	strText.Format("Z��������%d��", pkt.getDNSFlagsZ());
	g_pTreeCtrlPacketInfo->InsertItem(strText, DNSFlagNode, 0);

	switch (pkt.getDNSFlagsRCODE())
	{
	case DNS_FLAGS_RCODE_NO_ERROR:			strText = "RCODE���޲�� ��0��";							 break;
	case DNS_FLAGS_RCODE_FORMAT_ERROR:		strText = "RCODE����ʽ��� ��1��";							 break;
	case DNS_FLAGS_RCODE_SERVER_FAILURE:	strText = "RCODE��DNS���������� ��2��";						 break;
	case DNS_FLAGS_RCODE_NAME_ERROR:		strText = "RCODE�����������ڻ���� ��3��";					 break;
	case DNS_FLAGS_RCODE_NOT_IMPLEMENTED:	strText = "RCODE����ѯ���Ͳ�֧�� ��4��";					 break;
	case DNS_FLAGS_RCODE_REFUSED:			strText = "RCODE���ڹ����Ͻ�ֹ ��5��";						 break;
	default:								strText.Format("RCODE��������%d��", pkt.getDNSFlagsRCODE()); break;
	}
	g_pTreeCtrlPacketInfo->InsertItem(strText, DNSFlagNode, 0);

	strText.Format("��ѯ��¼����%hu", ntohs(pkt.dnsh->questions));
	g_pTreeCtrlPacketInfo->InsertItem(strText, parentNode, 0);

	strText.Format("�ش��¼����%hu", ntohs(pkt.dnsh->answer_RRs));
	g_pTreeCtrlPacketInfo->InsertItem(strText, parentNode, 0);

	strText.Format("��Ȩ�ش��¼����%hu", ntohs(pkt.dnsh->authority_RRs));
	g_pTreeCtrlPacketInfo->InsertItem(strText, parentNode, 0);

	strText.Format("������Ϣ��¼����%hu", ntohs(pkt.dnsh->additional_RRs));
	g_pTreeCtrlPacketInfo->InsertItem(strText, parentNode, 0);

	return 0;
}

/**
*	@brief	��DNS�����е�type�ֶ�ת����CString���ַ���
*	@param	type	DNS�����е�type�ֶ�
*	@return CString�ַ���
*/
CString DNSType2CString(const u_short &type)
{
	CString strType;
	switch (ntohs(type))
	{
	case DNS_TYPE_A:		strType = "Type A";										break;
	case DNS_TYPE_NS:		strType = "Type NS";									break;
	case DNS_TYPE_CNAME:	strType = "Type CNAME";									break;
	case DNS_TYPE_SOA:		strType = "Type SOA";									break;
	case DNS_TYPE_PTR:		strType = "Type PTR";									break;
	case DNS_TYPE_MX:		strType = "Type MX";									break;
	case DNS_TYPE_AAAA:		strType = "Type AAAA";									break;
	case DNS_TYPE_ANY:		strType = "Type ANY";									break;
	default:				strType.Format(" Type δ֪��%hu��,", ntohs(type));		break;
	}
	return strType;
}

/**
*	@brief	��DNS�����е�class�ֶ�ת����CString���ַ���
*	@param	class	DNS�����е�class�ֶ�
*	@return CString�ַ���
*/
CString DNSClass2CString(const u_short &classes)
{
	CString strClass;
	switch (ntohs(classes))
	{
	case DNS_CLASS_IN:		strClass = "Class IN";									break;
	case DNS_CLASS_CS:		strClass = "Class CS";									break;
	case DNS_CLASS_HS:		strClass = "Class HS";									break;
	default:				strClass.Format("Class δ֪��%hu��", ntohs(classes));	break;
	}
	return strClass;
}


/**
*	@brief	��ӡDNS��ѯ����
*	@param	DNSQuery	��ѯ����
*	@param	questions	��ѯ��¼��
*	@param	parentNode	���ڵ�
*	@return	0 ��ӡ�ɹ�	-1 ��ӡʧ��	������ DNS��ѯ�����ܳ���
*/
int printDNSQuery(char *DNSQuery, const u_short &questions, HTREEITEM &parentNode)
{
	if (DNSQuery == NULL && parentNode == NULL)
	{
		return -1;
	}
	CString strText, strTmp;
	HTREEITEM DNSQueryNode = g_pTreeCtrlPacketInfo->InsertItem("��ѯ���֣�", parentNode, 0);

	/* ��ѯ���� */
	
	char *p = DNSQuery;
	//if (questions < 10)
	//{
		for(int queryNum = 0; queryNum < questions; ++queryNum)
		{
			char *name = (char*)malloc(strlen(p) + 1);
			translateNameInDNS(name, p);

			/* ���������ֶ� */
			p += strlen(p) + 1;
			strText.Format("%s��", name);

			DNS_Query *DNSQuery = (DNS_Query*)p;
			strText += DNSType2CString(DNSQuery->type) + ", ";
			strText += DNSClass2CString(DNSQuery->classes);
			g_pTreeCtrlPacketInfo->InsertItem(strText, DNSQueryNode, 0);

			/* ������ѯ���ͺͲ�ѯ���ֶ� */
			p += sizeof(DNS_Query);		
			free(name);
		}// for
	//}// if
	return p - DNSQuery + 1;
}

/**
*	@brief	��ӡDNS�ش𲿷�
*	@param	dnsa		�ش𲿷�
*	@param	answers		�ش��¼��
*	@param	parentNode	���ڵ�
*	@return	0 ��ӡ�ɹ�	-1 ��ӡʧ��	������ DNS�ش𲿷��ܳ���
*/
//int printDNSAnswer(char *DNSAnswer, const u_short &answers, const DNS_Header *dnsh, HTREEITEM &parentNode)
//{
//	if (DNSAnswer == NULL || parentNode == NULL)
//	{
//		return -1;
//	}
//	CString strText, strTmp;
//	HTREEITEM DNSAnswerNode = g_pTreeCtrlPacketInfo->InsertItem("�ش𲿷֣�", parentNode, 0);
//
//	int answerNum = 0, byteCounter = 0;
//	char *p = DNSAnswer;
//	/* �ش𲿷� */
//	while (answerNum < answers)
//	{
//		/* ָ��ָ�� */
//		if (*p == 0xc0)
//		{
//
//			/* ָ��ƫ����
//			++p;
//
//			char *name = (char*)(pkt_data + offset + *(char*)p);			// ����
//			char *name1 = (char*)malloc(strlen(name)+1);
//
//
//			translateName(name1, name);
//
//			strText.Format("%s", name1);
//			strText += "��";
//
//			free(name1);
//			*/
//
//			char name[70];
//			char name1[70];
//
//			translateData(dnsh, name, p, 2);
//			translateName(name1, name);
//
//			strText.Format("%s��", name1);
//
//			/* ָ��ƫ���� */
//			++p;
//			++byteCounter;
//
//
//			/* ָ������*/
//			++p;
//			++byteCounter;
//			DNS_ResourceRecord *dnsa = (DNS_ResourceRecord*)p;
//
//			u_short type = ntohs(dnsa->type);
//			u_short classes = ntohs(dnsa->classes);
//			u_long  ttl = ntohl(dnsa->ttl);
//
//			switch (type)
//			{
//			case 1:	strTmp = "type A"; break;
//			case 2:	strTmp = "type NS"; break;
//			case 5: strTmp = "type CNAME"; break;
//			case 6: strTmp = "type SOA"; break;
//			case 12: strTmp = "type PTR"; break;
//			case 15: strTmp = "type MX"; break;
//			case 28: strTmp = "type AAAA"; break;
//			case 255: strTmp = "type ANY"; break;
//			default: strTmp.Format("type UNKNOWN(%hu)", type); break;
//			}
//			strText += strTmp + ", ";
//
//			switch (classes)
//			{
//			case 1: strTmp = "class INTERNET"; break;
//			case 2: strTmp = "class CSNET";	break;
//			case 3: strTmp = "class COAS";	break;
//			default: strTmp.Format("class UNKNOWN(%hu)", classes); break;
//			}
//			strText += strTmp + ", ";
//
//			strTmp.Format("TTL %lu", ttl);
//			strText += strTmp + ", ";
//
//			/* ָ����Դ���ݳ��� */
//			p += sizeof(DNS_ResourceRecord);
//			byteCounter += sizeof(DNS_ResourceRecord);
//			u_short data_len = ntohs(*(u_short*)p);
//
//			strTmp.Format("��Դ���ݳ��� %hu", data_len);
//			strText += strTmp + ", ";
//
//			/* ָ����Դ���� */
//			p += sizeof(u_short);
//			byteCounter += sizeof(u_short);
//
//			/* ��ѯ����ΪNS��CNAME��PTR����Դ���� */
//			if (type == 2 || type == 5 || type == 12)
//			{
//
//				/* ��Դ����Ϊָ��0xc0 + ƫ����*/
//				if (*(char*)p == 0xC0)
//				{
//					/* ����ƫ������ȡ����
//					char *data = (char*)(pkt_data + offset + *(char*)(p+1));			// ����
//					char *data1 = (char*)malloc(strlen(data)+1);
//
//					translateName(data1, data);
//
//					strText.Format("%s", data1);
//					strText += strTmp;
//
//					free(data1);
//					*/
//					char data[70];
//					char data1[70];
//
//					translateData(dnsh, data, p, 2);
//					translateName(data1, data);
//
//					strText.Format("%s", data1);
//					strText += strTmp;
//
//				}
//				/* ��Դ���ݴ���ָ��0xc0 + ƫ���� */
//				else if (isNamePtr(p))
//				{
//					char data[70];
//					char data1[70];
//
//					translateData(dnsh, data, p, data_len);		// ȥ��ָ��0xc0+ƫ����
//					translateName(data1, data);								// ȥ��'.'
//
//					strTmp.Format("%s", data1);
//					strText += strTmp;
//				}
//				/* ��Դ�����в�����ָ��0xc0 + ƫ���� */
//				else
//				{
//					char *data = (char*)malloc(data_len);
//
//					translateName(data, p);
//
//					strTmp.Format("%s", data);
//					strText += strTmp;
//					free(data);
//
//				}
//			}
//			/* ��ѯ����ΪA����Դ���� */
//			else if (type == 1)
//			{
//				IP_Address data = *(IP_Address*)p;
//				strText += IPAddr2CString(data);
//			}
//
//			g_pTreeCtrlPacketInfo->InsertItem(strText, DNSAnswerNode, 0);
//
//			/* �������ݲ��� */
//			p += data_len;
//			byteCounter += data_len;
//
//		}// if
//		answerNum++;
//	}// while
//	return byteCounter;
//}

/**
*	@brief	��ӡDNS��Դ��¼
*	@param	DNSResourceRecord	��Դ��¼
*	@param	resourceRecordNum	��Դ��¼��
*	@param	resourceRecordType	��Դ��¼���ͣ��ش���Ȩ�ش𣬸�����Ϣ��
*	@param	pDNSHeader			DNS�ײ�
*	@param	parentNode			���ڵ�
*	@return	0 ��ӡ�ɹ�	-1 ��ӡʧ�� ������ DNS��Դ��¼�ܳ���
*/
int printDNSResourceRecord(char *DNSResourceRecord, const u_short &resourceRecordNum, const int &resourceRecordType ,const DNS_Header *pDNSHeader, HTREEITEM parentNode)
{
	if (DNSResourceRecord == NULL || resourceRecordNum == 0 || pDNSHeader == NULL || parentNode == NULL)
	{
		return -1;
	}
	char *p = DNSResourceRecord;
	CString strText, strTmp;

	switch (resourceRecordType)
	{
	case DNS_RESOURCE_RECORD_TYPE_ANSWER:		strText = "�ش𲿷֣�";		break;
	case DNS_RESOURCE_RECORD_TYPE_AUTHORITY:	strText = "��Ȩ�ش𲿷֣�";	break;
	case DNS_RESOURCE_RECORD_TYPE_ADDITIONAL:	strText = "������Ϣ���֣�";	break;
	}
	HTREEITEM DNSResourceRecordNode = g_pTreeCtrlPacketInfo->InsertItem(strText, parentNode, 0);

	for (int count = 0; count < 1; ++count) //count < resourceRecordNum; ++count)
	{

		if ( *(u_char*)p == 0xC0)
		{
			// name
			strText = getNameInDNS(p, pDNSHeader) + "��";

			// ָ��type��class��ttl
			p += 2;			// 2 = 0xC0 + ƫ����
		}
		else
		{
			char *name = (char*)malloc(strlen(p) + 1);
			translateNameInDNS(name, p);

			CString strText, strTmp;
			strText.Format("%s: ", name);

			// ָ��type��class��ttl
			p += strlen(name) + 1;
			free(name);
		}

		DNS_ResourceRecord	*pRecord = (DNS_ResourceRecord*)p;
		strText += DNSType2CString(pRecord->type) + ", ";
		strText += DNSClass2CString(pRecord->classes) + ", ";
		strTmp.Format("TTL %d", ntohl(pRecord->ttl));
		strText += strTmp + ", ";

		// ָ����Դ���ݳ���
		p += sizeof(DNS_ResourceRecord);
		u_short dataLength = *(u_short*)p;
		strTmp.Format("��Դ���ݳ��ȣ�%hu �ֽ�", dataLength);
		strText += strTmp + ", ";

		// ָ����Դ����
		p += sizeof(u_short);

		switch (ntohs(pRecord->type))
		{
		case DNS_TYPE_A:
			strText += "IP��ַ�� " + IPAddr2CString(*(IP_Address*)p);
			break;
		case DNS_TYPE_NS:
			strText += "���ַ������� " + IPAddr2CString(*(IP_Address*)p);
			break;
		case DNS_TYPE_CNAME:
		{
			//char *cname = (char*)malloc(dataLength);
			//translateNameInDNS(cname, p);

			CString strCName = getNameInDNS(p, pDNSHeader);
			strText += "������" + strCName;
			//g_pTreeCtrlPacketInfo->InsertItem(strText, parentNode, 0);
			//free(cname);
			break;
		}
		//case DNS_TYPE_SOA:
		//	strText += ;
		//	break;
		//case DNS_TYPE_PTR:
		//	strText += ;
		//	break;
		//case DNS_TYPE_AAAA:
		//	strText += ;
		//	break;
		//case DNS_TYPE_ANY:
		//	strText += ;
		//	break;
		default:
			/*strTmp.Format("Type δ֪(%hu),", ntohs(pRecord->type));
			strText += strTmp;*/
			break;
		}
		g_pTreeCtrlPacketInfo->InsertItem(strText, DNSResourceRecordNode, 0);

	}// for
	return p - DNSResourceRecord + 1;
}

/**
*	@brief	��ӡDNS���ĵ����οؼ�
*	@param	pkt ���ݰ�
*	@param	parentNode ���ڵ�
*	@return	0 ����ɹ�	-1 ����ʧ��
*/
int printDNS2TreeCtrl(const Packet & pkt, HTREEITEM & parentNode)
{
	if (pkt.isEmpty() || pkt.dnsh == NULL || parentNode == NULL)
	{
		return -1;
	}
	HTREEITEM DNSNode = printDNSBanner(pkt, parentNode);

	printDNSHeader(pkt, DNSNode);


	char *DNSQuery = (char*)pkt.dnsh + DNS_HEADER_LENGTH;
	int DNSQueryLen = printDNSQuery(DNSQuery, ntohs(pkt.dnsh->questions), DNSNode);

	char *DNSAnswer = NULL, *DNSAuthority = NULL, *DNSAdditional = NULL;
	int DNSAnswerLen = 0, DNSAuthorityLen = 0;

	if (ntohs(pkt.dnsh->answer_RRs) > 0)
	{
		DNSAnswer = DNSQuery + DNSQueryLen;
		DNSAnswerLen = printDNSResourceRecord(DNSAnswer, ntohs(pkt.dnsh->answer_RRs), DNS_RESOURCE_RECORD_TYPE_ANSWER, pkt.dnsh, DNSNode);
	}

	if (ntohs(pkt.dnsh->authority_RRs) > 0)
	{
		DNSAuthority = DNSAnswer + DNSAnswerLen;
		DNSAuthorityLen = printDNSResourceRecord(DNSAuthority, ntohs(pkt.dnsh->authority_RRs), DNS_RESOURCE_RECORD_TYPE_AUTHORITY, pkt.dnsh, DNSNode);
	}
	

	if (ntohs(pkt.dnsh->additional_RRs) > 0)
	{
		DNSAdditional = DNSAuthority + DNSAuthorityLen;
		printDNSResourceRecord(DNSAdditional, ntohs(pkt.dnsh->additional_RRs), DNS_RESOURCE_RECORD_TYPE_ADDITIONAL, pkt.dnsh, DNSNode);
	}


	return 0;
}

/**
*	@brief	��ӡDHCP�ײ������οؼ�
*	@param	pkt ���ݰ�
*	@param	parentNode ���ڵ�
*	@return	0 ����ɹ�	-1 ����ʧ��
*/
int printDHCP2TreeCtrl(const Packet & pkt, HTREEITEM & parentNode)
{
	if (pkt.isEmpty() || pkt.dhcph == NULL || parentNode == NULL)
	{
		return -1;
	}

	HTREEITEM DHCPNode = g_pTreeCtrlPacketInfo->InsertItem("DHCP", parentNode, 0);
	CString strText, strTmp;
	/* ����dhcp�ײ� */
	strText.Format("�������ͣ�%d", pkt.dhcph->op);
	g_pTreeCtrlPacketInfo->InsertItem(strText, DHCPNode, 0);
	
	strText.Format("Ӳ�����ͣ�%d", pkt.dhcph->htype);
	g_pTreeCtrlPacketInfo->InsertItem(strText, DHCPNode, 0);
	
	strText.Format("Ӳ����ַ���ȣ�%d", pkt.dhcph->hlen);
	g_pTreeCtrlPacketInfo->InsertItem(strText, DHCPNode, 0);

	strText.Format("������%d",pkt.dhcph->hops);
	g_pTreeCtrlPacketInfo->InsertItem(strText, DHCPNode, 0);
	
	strText.Format("����ID��0x%08lX", ntohl(pkt.dhcph->xid));
	g_pTreeCtrlPacketInfo->InsertItem(strText, DHCPNode, 0);
	
	strText.Format("�ͻ�����ʱ�䣺%hu", ntohs(pkt.dhcph->secs));
	g_pTreeCtrlPacketInfo->InsertItem(strText, DHCPNode, 0);
	
	strText.Format("��־��0x%04hX", ntohs(pkt.dhcph->flags));
	switch(ntohs(pkt.dhcph->flags) >> 15)
	{
	case DHCP_FLAGS_BROADCAST: strText += "���㲥��"; break;
	case DHCP_FLAGS_UNICAST: strText += "��������"; break;
	}
	g_pTreeCtrlPacketInfo->InsertItem(strText, DHCPNode, 0);
	
	strText = "�ͻ���IP��ַ��" + IPAddr2CString(pkt.dhcph->ciaddr);
	g_pTreeCtrlPacketInfo->InsertItem(strText, DHCPNode, 0);
	
	strText = "��ģ��ͻ���IP��ַ��" + IPAddr2CString(pkt.dhcph->yiaddr);
	g_pTreeCtrlPacketInfo->InsertItem(strText, DHCPNode, 0);
	
	strText = "������IP��ַ��" + IPAddr2CString(pkt.dhcph->siaddr);;
	g_pTreeCtrlPacketInfo->InsertItem(strText, DHCPNode, 0);
	
	strText = "����IP��ַ��" + IPAddr2CString(pkt.dhcph->giaddr);
	g_pTreeCtrlPacketInfo->InsertItem(strText, DHCPNode, 0);
	
	/*  ����dhcp�ײ�ʣ�ಿ�� */
	CString strChaddr;
	for (int i=0; i< 6; ++i)
	{
		strTmp.Format("%02X", pkt.dhcph->chaddr[i]);
		strChaddr += strTmp + "-";
	}
	strChaddr.Delete(strChaddr.GetLength() - 1, 1);

	strText = "�ͻ���MAC��ַ��" + strChaddr;
	g_pTreeCtrlPacketInfo->InsertItem(strText, DHCPNode, 0);
	
	strText = "��������������";
	strTmp.Format("%s", pkt.dhcph->snamer);
	strText += strTmp;
	g_pTreeCtrlPacketInfo->InsertItem(strText, DHCPNode, 0);
	
	strText = "�����ļ�����";
	strTmp.Format("%s", pkt.dhcph->file);
	strText += strTmp;
	g_pTreeCtrlPacketInfo->InsertItem(strText, DHCPNode, 0);
	
	// ���������ļ���
	u_char *p = (u_char*)pkt.dhcph->file + 128;
	
	if(ntohl(*(u_long*)p) == 0x63825363)
	{
		strText = "Magic cookie: DHCP";
		g_pTreeCtrlPacketInfo->InsertItem(strText, DHCPNode, 0);
	}
	
	// ����magic cookie
	p += 4;
	
	while(*p != 0xFF)
	{
		switch (*p)
		{
		case DHCP_OPTIONS_DHCP_MESSAGE_TYPE:
		{
			strText = "ѡ���53��DHCP��������";
			switch (*(p + 2))
			{
			case 1: strText += "��Discover��"; break;
			case 2: strText += "��Offer��"; break;
			case 3: strText += "��Request��"; break;
			case 4: strText += "��Decline��"; break;
			case 5: strText += "��ACK��"; break;
			case 6: strText += "��NAK��"; break;
			case 7: strText += "��Release��"; break;
			case 8: strText += "��Inform��"; break;
			}
			HTREEITEM DHCPOptionNode = g_pTreeCtrlPacketInfo->InsertItem(strText, DHCPNode, 0);

			strText.Format("���ȣ�%d", *(++p));
			g_pTreeCtrlPacketInfo->InsertItem(strText, DHCPOptionNode, 0);

			strText.Format("DHCP��%d", *(++p));
			g_pTreeCtrlPacketInfo->InsertItem(strText, DHCPOptionNode, 0);

			// ָ����һ��ѡ��
			++p;
		}
			break;

		case DHCP_OPTIONS_REQUESTED_IP_ADDRESS:
		{
			strText = "ѡ���50������IP��ַ";
			HTREEITEM DHCPOptionNode = g_pTreeCtrlPacketInfo->InsertItem(strText, DHCPNode, 0);

			strText.Format("���ȣ�%d", *(++p));
			g_pTreeCtrlPacketInfo->InsertItem(strText, DHCPOptionNode, 0);

			IP_Address *addr = (IP_Address*)(++p);
			strText = "��ַ��" + IPAddr2CString(*addr);
			g_pTreeCtrlPacketInfo->InsertItem(strText, DHCPOptionNode, 0);

			// ָ����һ��ѡ��
			p += 4;
		}
			break;

		case DHCP_OPTIONS_IP_ADDRESS_LEASE_TIME:
		{
			strText = "ѡ���51��IP��ַ��Լʱ��";
			HTREEITEM DHCPOptionNode = g_pTreeCtrlPacketInfo->InsertItem(strText, DHCPNode, 0);

			strText.Format("���ȣ�%d", *(++p));
			g_pTreeCtrlPacketInfo->InsertItem(strText, DHCPOptionNode, 0);

			u_int time = *(++p);
			strText.Format("��Լʱ�䣺%u", time);
			g_pTreeCtrlPacketInfo->InsertItem(strText, DHCPOptionNode, 0);

			// ָ����һ��ѡ��
			p += 4;
		}
			break;

		case DHCP_OPTIONS_CLIENT_IDENTIFIER:
		{
			strText = "ѡ���61���ͻ�����ʶ";
			HTREEITEM DHCPOptionNode = g_pTreeCtrlPacketInfo->InsertItem(strText, DHCPNode, 0);

			int len = *(++p);
			strText.Format("���ȣ�%d", len);
			g_pTreeCtrlPacketInfo->InsertItem(strText, DHCPOptionNode, 0);

			strText = "Ӳ�����ͣ�";
			if (*(++p) == 0x01)
			{
				strText += "��̫����0x01��";
				g_pTreeCtrlPacketInfo->InsertItem(strText, DHCPOptionNode, 0);

				MAC_Address *addr = (MAC_Address*)(++p);
				strText = "�ͻ�����ʶ��" + MACAddr2CString(*addr);
				g_pTreeCtrlPacketInfo->InsertItem(strText, DHCPOptionNode, 0);

				p += 6;
			}
			else
			{
				strText.Format("%d", *p);
				strText += strTmp;
				g_pTreeCtrlPacketInfo->InsertItem(strText, DHCPOptionNode, 0);

				p += len;
			}
		}
			break;

		case DHCP_OPTIONS_VENDOR_CLASS_IDENTIFIER:
		{
			strText = "ѡ���60����Ӧ�����ʶ";
			HTREEITEM DHCPOptionNode = g_pTreeCtrlPacketInfo->InsertItem(strText, DHCPNode, 0);

			int len = *(++p);
			strText.Format("���ȣ�%d", len);
			g_pTreeCtrlPacketInfo->InsertItem(strText, DHCPOptionNode, 0);

			int count = 0;
			strText = "��Ӧ�����ʶ��";
			for (; count < len; count++)
			{
				strTmp.Format("%c", *(++p));
				strText += strTmp;
			}
			g_pTreeCtrlPacketInfo->InsertItem(strText, DHCPOptionNode, 0);

			++p;
		}
			break;

		case DHCP_OPTIONS_SERVER_IDENTIFIER:
		{
			strText = "ѡ���54����������ʶ";
			HTREEITEM DHCPOptionNode = g_pTreeCtrlPacketInfo->InsertItem(strText, DHCPNode, 0);

			int len = *(++p);
			strText.Format("���ȣ�%d", len);
			g_pTreeCtrlPacketInfo->InsertItem(strText, DHCPOptionNode, 0);

			IP_Address *addr = (IP_Address*)(++p);
			strText = "��������ʶ��" + IPAddr2CString(*addr);
			g_pTreeCtrlPacketInfo->InsertItem(strText, DHCPOptionNode, 0);

			p += 4;
		}
			break;

		case DHCP_OPTIONS_SUBNET_MASK:
		{

		
			strText = "ѡ���1����������";
			HTREEITEM DHCPOptionNode = g_pTreeCtrlPacketInfo->InsertItem(strText, DHCPNode, 0);

			int len = *(++p);
			strText.Format("���ȣ�%d", len);
			g_pTreeCtrlPacketInfo->InsertItem(strText, DHCPOptionNode, 0);

			IP_Address *submask = (IP_Address*)(++p);
			strText = "�������룺" + IPAddr2CString(*submask);
			g_pTreeCtrlPacketInfo->InsertItem(strText, DHCPOptionNode, 0);

			p += 4;
		}
			break;

		case DHCP_OPTIONS_ROUTER_OPTION:
		{

		
			strText = "ѡ���3��·����";
			HTREEITEM DHCPOptionNode = g_pTreeCtrlPacketInfo->InsertItem(strText, DHCPNode, 0);

			int len = *(++p);
			strText.Format("���ȣ�%d", len);
			g_pTreeCtrlPacketInfo->InsertItem(strText, DHCPOptionNode, 0);

			int count = 0;
			while (count < len)
			{
				IP_Address *addr = (IP_Address*)(++p);
				strText = "·������" + IPAddr2CString(*addr);
				g_pTreeCtrlPacketInfo->InsertItem(strText, DHCPOptionNode, 0);

				count += 4;
				p += 4;
			}
		}
			break;

		case DHCP_OPTIONS_DOMAIN_NAME_SERVER_OPTION: 
		{
			strText = "ѡ���6��DNS������";
			HTREEITEM DHCPOptionNode = g_pTreeCtrlPacketInfo->InsertItem(strText, DHCPNode, 0);

			int len = *(++p);
			strText.Format("���ȣ�%d", len);
			g_pTreeCtrlPacketInfo->InsertItem(strText, DHCPOptionNode, 0);

			int count = 0;
			++p;
			while (count < len)
			{
				IP_Address *addr = (IP_Address*)(p);
				strText = "DNS��������" + IPAddr2CString(*addr);
				g_pTreeCtrlPacketInfo->InsertItem(strText, DHCPOptionNode, 0);

				count += 4;
				p += 4;
			}
		}
			break;


		case DHCP_OPTIONS_HOST_NAME_OPTION:
		{
			strText = "ѡ���12��������";
			HTREEITEM DHCPOptionNode = g_pTreeCtrlPacketInfo->InsertItem(strText, DHCPNode, 0);

			int len = *(++p);
			strText.Format("���ȣ�%d", len);
			g_pTreeCtrlPacketInfo->InsertItem(strText, DHCPOptionNode, 0);

			int count = 0;
			strText = "��������";

			for (; count < len; count++)
			{
				strTmp.Format("%c", *(++p));
				strText += strTmp;
			}
			g_pTreeCtrlPacketInfo->InsertItem(strText, DHCPOptionNode, 0);

			++p;
		}
			break;

		case DHCP_OPTIONS_PAD_OPTION:
			++p;
			break;

		default:
		{
			strText.Format("ѡ���%d��", *p);
			HTREEITEM DHCPOptionNode = g_pTreeCtrlPacketInfo->InsertItem(strText, DHCPNode, 0);

			int len = *(++p);
			strText.Format("���ȣ�%d", len);
			g_pTreeCtrlPacketInfo->InsertItem(strText, DHCPOptionNode, 0);

			// ָ��ѡ������
			++p;

			// ����ѡ������
			p += len;
		}
			break;
		}// switch 
	
	}// while
	strText = "ѡ���255������";
	g_pTreeCtrlPacketInfo->InsertItem(strText, DHCPNode, 0);	 
		
	return 0;
}

/**
*	@brief	��ӡHTTP���ĵ����οؼ�
*	@param	pkt ���ݰ�
*	@param	parentNode ���ڵ�
*	@return	0 ����ɹ�	-1 ����ʧ��
*/
int printHTTP2TreeCtrl(const Packet & pkt, HTREEITEM & parentNode)
{
	if (pkt.isEmpty() || pkt.httpmsg == NULL || parentNode == NULL)
	{
		return -1;
	}

	u_char *p = pkt.httpmsg;
	int HTTPMsgLen = pkt.getL4PayloadLength();
		
	CString strText;
	if (ntohs(pkt.tcph->dstport) == PORT_HTTP)
	{
		strText = "HTTP������";
	}
	else if (ntohs(pkt.tcph->srcport) == PORT_HTTP)
	{
		strText = "HTTP����Ӧ��";
	}
	HTREEITEM HTTPNode = g_pTreeCtrlPacketInfo->InsertItem(strText, parentNode, 0);
	
	for(int count = 0; count < HTTPMsgLen; )
	{
		strText = "";
		while(*p != '\r')
		{
			strText += *p;
			++p;
			++count;
		}
		strText += "\\r\\n";
		g_pTreeCtrlPacketInfo->InsertItem(strText, HTTPNode, 0);
	
		p += 2;
		count += 2;
	}	
	return 0;
}

/**
*	@brief	��MAC��ַת����CString���ַ���
*	@param	addr MAC��ַ
*	@return	CString���ַ���
*/
CString MACAddr2CString(const MAC_Address &addr)
{
	CString strAddr, strTmp;

	for (int i = 0; i < 6; ++i)
	{
		strTmp.Format("%02X", addr.bytes[i]);
		strAddr += strTmp + "-";
	}
	strAddr.Delete(strAddr.GetLength() - 1, 1);

	return strAddr;
}

/**
*	@brief	��IP��ַת����CString���ַ���
*	@param	addr IP��ַ
*	@return	CString���ַ���
*/
CString IPAddr2CString(const IP_Address &addr)
{
	CString strAddr, strTmp;

	for (int i = 0; i < 4; ++i)
	{
		strTmp.Format("%d", addr.bytes[i]);
		strAddr += strTmp + ".";
	}
	strAddr.Delete(strAddr.GetLength() - 1, 1);

	return strAddr;
}

/**
*	@brief	����б���ӡ���ݰ��ײ�������������οؼ� ,�Լ����ݰ��ֽ������༭�ؼ�
*	@param	
*	@return	-
*/
void CSnifferUIDlg::OnClickedList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	/* ��ȡѡ���е��к� */
	int selectedItemIndex = g_pListCtrlPacketList->GetSelectionMark();
	CString strPktNum = g_pListCtrlPacketList->GetItemText(selectedItemIndex, 0);
	int pktNum = _ttoi(strPktNum);
	if (pktNum == -1)
	{
		return;
	}
	POSITION pos = g_packetLinkList.FindIndex(pktNum - 1);
	Packet &pkt = g_packetLinkList.GetAt(pos);

	printTreeCtrlPacketInfo(pkt);
	printEditCtrlPacketData(pkt);
}

/**
*	@brief	��������Ӵ�Github
*	@param
*	@return -
*/
void CAboutDlg::OnNMClickSyslink1(NMHDR *pNMHDR, LRESULT *pResult)
{
	PNMLINK pNMLink = (PNMLINK)pNMHDR;
	ShellExecuteW(NULL, L"open", pNMLink->item.szUrl, NULL, NULL, SW_SHOWNORMAL);
	*pResult = 0;
}

/**
*	@brief	����Э������ListCtrl�ؼ���Item����ɫ
*	@param	-
*	@return	-
*/
void CSnifferUIDlg::OnCustomdrawList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLVCUSTOMDRAW pNMCD = (LPNMLVCUSTOMDRAW)pNMHDR;
	*pResult = 0;

	if (CDDS_PREPAINT == pNMCD->nmcd.dwDrawStage)	
	{
		*pResult = CDRF_NOTIFYITEMDRAW;
	}
	else if(CDDS_ITEMPREPAINT == pNMCD->nmcd.dwDrawStage) // һ��Item(һ��)���滭ǰ
	{
		COLORREF itemColor;
		CString *pStrPktProtocol = (CString*)(pNMCD->nmcd.lItemlParam);	// ��printListCtrlPacketList(pkt)�ｫ���ݰ���protocol�ֶδ��ݹ���

		///* �����б�ѡ�У����䱳����ɫ����Ϊ */
		//if (pNMCD->nmcd.uItemState & CDIS_SELECTED)
		//{
		//	pNMCD->clrTextBk = RGB(0, 0, 0);
		//}
		if (!pStrPktProtocol->IsEmpty())
		{
			if (*pStrPktProtocol == "ARP")
			{
				itemColor = RGB(255, 182, 193);	// ��ɫ
			}
			else if (*pStrPktProtocol == "ICMP")
			{
				itemColor = RGB(186, 85, 211);	// ��ɫ
			}
			else if (*pStrPktProtocol == "TCP")
			{
				itemColor = RGB(144, 238, 144);	// ��ɫ
			}
			else if (*pStrPktProtocol == "UDP")
			{
				itemColor = RGB(100, 149, 237);	// ��ɫ

			}
			else if (*pStrPktProtocol == "DNS")
			{
				itemColor = RGB(135, 206, 250);	// ǳ��ɫ
			}
			else if (*pStrPktProtocol == "DHCP")
			{
				itemColor = RGB(189, 254, 76);	// ����ɫ
			}
			else if (*pStrPktProtocol == "HTTP")
			{
				itemColor = RGB(238, 232, 180);	// ��ɫ
			}
			else
			{
				itemColor = RGB(211, 211, 211);	// ��ɫ
			}
			pNMCD->clrTextBk = itemColor;
		}		
		*pResult = CDRF_DODEFAULT;
	}
}

/**
*	@brief	�����ݰ��б�ؼ��У��÷�����ϡ��¿��Ƶ�ǰѡ����
*	@param	-
*	@return	-
*/
void CSnifferUIDlg::OnKeydownList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLVKEYDOWN pLVKeyDow = reinterpret_cast<LPNMLVKEYDOWN>(pNMHDR);
	bool selectedItemChangedFlag = false;
	int selectedItemIndex = g_pListCtrlPacketList->GetSelectionMark();
	/* �жϰ��µļ��Ƿ�Ϊ������ϻ������*/
	switch (pLVKeyDow->wVKey)
	{
	case VK_UP:
	{
		if (selectedItemIndex > 0 && selectedItemIndex < g_pListCtrlPacketList->GetItemCount())
		{
			g_pListCtrlPacketList->SetSelectionMark(--selectedItemIndex );
			selectedItemChangedFlag = true;
		}
	}
	break;
	case VK_DOWN:
	{
		if (selectedItemIndex >= 0 && selectedItemIndex < g_pListCtrlPacketList->GetItemCount() - 1)
		{
			g_pListCtrlPacketList->SetSelectionMark(++selectedItemIndex);
			selectedItemChangedFlag = true;
		}
	}
	break;
	default:	break;
	}

	/* ѡ���з��ͱ仯����ӡ���ݰ���Ϣ���ֽ��� */
	if (selectedItemChangedFlag)
	{
		CString strPktNum = g_pListCtrlPacketList->GetItemText(selectedItemIndex, 0);
		int pktNum = _ttoi(strPktNum);
		if (pktNum < 1 || pktNum > g_packetLinkList.GetCount())
		{
			return;
		}
		POSITION pos = g_packetLinkList.FindIndex(pktNum - 1);
		Packet &pkt = g_packetLinkList.GetAt(pos);

		printTreeCtrlPacketInfo(pkt);
		printEditCtrlPacketData(pkt);
	}
	
	*pResult = 0;
}



/**
*	@brief	�������ֽڼ���������name2ת��������name1
*			�磺3www8bilibili3com	->	www.bilibili.com
*	@param	name1	����
*	@param	name2	���ֽڼ���������
*	@return	-
*/
void translateNameInDNS(char *name1, const char *name2)
{
	strcpy(name1, name2);

	char *p = name1;
	bool canMove = false;

	if (!isalnum(*p) && *p != '-')
	{
		canMove = true;
	}

	/* ������ת��Ϊ'.' */
	while (*p)
	{
		if (!isalnum(*p) && *p != '-')
		{
			*p = '.';
		}
		++p;
	}

	/* ������������ǰ��1λ */
	if (canMove)
	{
		p = name1;
		while (*p)
		{
			*p = *(p + 1);
			++p;
		}
	}
}


CString translateNameInDNS(const char *name)
{
	CString strName(name);
	bool canMove = false;

	if (!isalnum(strName.GetAt(0)) && strName.GetAt(0) != '-')
	{
		canMove = true;
	}
	/* ������ת��Ϊ'.' */
	for (int i = 0; i < strName.GetLength(); ++i)
	{
		if (!isalnum(strName.GetAt(i)) && strName.GetAt(i) != '-')
		{
			strName.SetAt(i, '.');
		}
	}

	/* ������������ǰ��1λ */
	if (canMove)
	{
		for (int i = 0; i<strName.GetLength(); ++i)
		{
			strName.SetAt(i, strName.GetAt(i + 1));
		}
	}
	return strName;
}
/* DNS��Դ��¼���ݲ���ת�� ������ָ��0xc0��data2ת��Ϊ����ָ���data1 offsetΪ��dns�ײ���ƫ����*/
void translateData(const DNS_Header *dnsh, char *data1, char *data2, const int data2_len)
{
	char *p = data2;
	int count = 0, i = 0;

	/* ����data2 */
	while (count < data2_len)
	{
		/* ָ�� */
		if (*(u_char*)p == 0xC0)
		{
			++p;

			/* ��ȡָ����ָ������� */
			char *data_ptr = (char*)((u_char*)dnsh + *(u_char*)p);

			int pos = is0xC0PointerInName(data_ptr);
			if (pos)
			{
				translateData(dnsh, data1 + i, data_ptr, pos + 2);
			}
			else
			{
				strcpy(data1 + i, data_ptr);
				i += strlen(data_ptr) + 1;
			}
			count += 2;
		}
		else
		{
			data1[i++] = *p;
			++p;
			++count;
		}
	}

}

/**
*	@brief	��ȡDNS�е�name�ֶΣ���ѯ������Դ��¼����
*	@param	name		����
*	@param	pDNSHeader	DNS�ײ�ָ��
*	@return	�����ַ���
*/
CString getNameInDNS(char *name, const DNS_Header *pDNSHeader)
{
	int pointerPos;

	// name����0xC0ָ��
	if ((pointerPos = is0xC0PointerInName(name)) == -1)
	{
		return translateNameInDNS(name);
	}
	else
	{
		int valueOffset = *(name + pointerPos + 1);
		CString value = get0xC0PointerValue(pDNSHeader, valueOffset);

		char *pName = (char*)malloc(pointerPos);
		memcpy(pName, name, pointerPos);
		CString strName(pName);
		strName += value;

		free(pName);
		return strName;

	}
}
/**
*	@brief	�ж�name������ָ��0xC0,������ָ����name�е�λ��
*	@param	name	����
*	@param	nameLen	��������
*	@return	��0	ָ����name�е�λ��	-1	name����ָ��0xC0	-2	nameΪ��
*/
int is0xC0PointerInName(char *name)
{
	if (name == NULL)
	{
		return -2;
	}
	char *p = name;
	int pos = 0;

	while(*p)
	{
		if (*(u_char*)p == 0xC0)
		{
			return pos;
		}
		++p;
		++pos;
	}
	return -1;
}
/**
*	@brief	��ȡ0xC0ָ���ֵ
*	@param
*	@return 
*/
CString get0xC0PointerValue(const DNS_Header *pDNSHeader, const int offset)
{
	char *pValue = (char*)pDNSHeader + offset;
	CString strValue = getNameInDNS(pValue, pDNSHeader);
	return strValue;
	
}

/**
*	@brief	���˵��� - �ļ� - �˳�������ʵ��
*	@param	-
*	@return	-
*/
void CSnifferUIDlg::On32775()
{
	exit(0);
}

/**
*	@brief	���˵��� - ���� - ���ڣ�����ʵ��
*	@param	-
*	@return	-
*/
void CSnifferUIDlg::On32776()
{
	CAboutDlg dlg;
	dlg.DoModal();
}
