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
	DDX_Control(pDX, IDC_COMBO1, comboboxDevlist_);
	DDX_Control(pDX, IDC_LIST1, listctrlPacketList_);
	DDX_Control(pDX, IDC_TREE1, treectrlPacketInfo_);
	DDX_Control(pDX, IDC_EDIT1, editCtrlPacketData_);
	
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
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnClickList1)
	//}}AFX_MSG_MAP
//	ON_BN_CLICKED(IDC_PAUSE, &CSnifferUIDlg::OnBnClickedPause)
ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST1, &CSnifferUIDlg::OnCustomdrawList1)
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

	/* �ؼ�ָ���ʼ�� */
	g_pBtnStart = &btnStart_;
	g_pBtnPause = &btnPause_;
	g_pBtnStop = &btnStop_;
	g_pComboBoxDevList = &comboboxDevlist_;
	g_pListCtrlPacketList = &listctrlPacketList_;
	g_pTreeCtrlPacketInfo = &treectrlPacketInfo_;
	g_pEditCtrlPacketData = &editCtrlPacketData_;

	///* ��ť��ʼ�� */
	//g_pBtnStart->SetIcon(LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON1)));
	//g_pBtnPause->SetIcon(LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON2)));
	//g_pBtnStop->SetIcon(LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON3)));


	/* �б�ؼ���ʼ�� */
	initialListCtrlPacketList();

	/* �����б��ʼ������ʾ�����б�*/
	initialComboBoxDevList();

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
	if (g_pComboBoxDevList->GetCurSel() == CB_ERR)
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
		g_pComboBoxDevList->EnableWindow(TRUE);
		pcap_breakloop(g_pAdhandle);
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
	pcap_breakloop(g_pAdhandle);

	g_pListCtrlPacketList->DeleteAllItems();
	g_pTreeCtrlPacketInfo->DeleteAllItems();
	g_pEditCtrlPacketData->Clear();

	g_listctrlPacketListRows = -1;
	g_listctrlPacketListCols = 0;
	g_listctrlPacketListCount = 0;

	// TODO ��ϵ㿴�Ƿ��������
	if (!g_packetLinkList.IsEmpty())
	{
		g_packetLinkList.RemoveAll();
	}
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
	if(selIndex == CB_ERR )
	{
		AfxMessageBox(_T("��ѡ������"),MB_OK);
		return -1;
	}		
	int count = 0;
    for(g_pDev = g_pAllDevs; count < selIndex; g_pDev = g_pDev->next, ++count);
	if((g_pAdhandle = pcap_open_live(g_pDev->name,
					65535,
					 PCAP_OPENFLAG_PROMISCUOUS,
					1000,
					g_errbuf)) == NULL)
	{ 
		AfxMessageBox(_T("pcap_open_live����!"), MB_OK);
	}

	/* �жϽӿڵ���·�������Ƿ�Ϊ��̫��*/
	if( pcap_datalink(g_pAdhandle) != DLT_EN10MB)
		AfxMessageBox(_T("������·�㲻����̫��"), MB_OK);

	
	pcap_dumper_t *dumpfile = NULL;	
	/* �򿪶��ļ�
	strcpy(filename, "pkt_cap");

	dumpfile = pcap_dump_open(adhandle, filename);
	*/

	/* ��ʼ�������ݰ� */
	pcap_loop(g_pAdhandle, -1,	packet_handler, (unsigned char *)dumpfile);
	
	return 0;
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
//	pcap_dump(dumpfile, header, pkt_data);
	

	/* ��־�ļ� 
	char *path = "E:\\Code\\Sniffer\\pkt_cap_log.txt";
	FILE *save_file;
	save_file = fopen(path,"a");	//��׷����ʽд��
	*/
	
	/* �洢���ݰ������� */
	Packet pkt(pkt_data, header);

	g_packetLinkList.AddTail(pkt);
	Packet &pkt1 = g_packetLinkList.GetTail();
	printListCtrlPacketList(pkt1);
	
	//fclose(save_file);
}

/**
*	@brief	��ȡ���ػ��������б�,����ӡ���������������б���
*	@param	-
*	@return -
*/
void initialComboBoxDevList()
{
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
	/* ��ӡ��� */
	CString	strCount;
	strCount.Format("%d", ++g_listctrlPacketListCount);
	g_pListCtrlPacketList->InsertItem(++g_listctrlPacketListRows, strCount);

	/* ��ӡʱ�� */
	CTime pktArrivalTime( (time_t)(pkt.header->ts.tv_sec) ) ;
	CString strPktArrivalTime = pktArrivalTime.Format("%Y/%m/%d %H:%M:%S");
	g_pListCtrlPacketList->SetItemText(g_listctrlPacketListRows, ++g_listctrlPacketListCols, strPktArrivalTime);

	/* ��ӡЭ�� */	
	if (!pkt.protocol.IsEmpty())
	{
		g_pListCtrlPacketList->SetItemText(g_listctrlPacketListRows, ++g_listctrlPacketListCols, pkt.protocol);
		//COLORREF ref = RGB(120, 250, 110);
		///*if(pkt.protocol == "TCP")
		//	g_pListCtrlPacketList->SetTextBkColor(ref);*/
		//
	}
	else
	{
		++g_listctrlPacketListCols;
	}

	/* ��ӡ���� */
	CString strCaplen;
	strCaplen.Format("%d", pkt.header->caplen);
	g_pListCtrlPacketList->SetItemText(g_listctrlPacketListRows, ++g_listctrlPacketListCols, strCaplen);

	/* ��ӡԴĿMAC��ַ */
	if (pkt.ethh != NULL)
	{
		CString strSrcMAC = MACAddr2CString(pkt.ethh->srcaddr);
		CString strDstMAC = MACAddr2CString(pkt.ethh->dstaddr);

		g_pListCtrlPacketList->SetItemText(g_listctrlPacketListRows, ++g_listctrlPacketListCols, strSrcMAC);
		g_pListCtrlPacketList->SetItemText(g_listctrlPacketListRows, ++g_listctrlPacketListCols, strDstMAC);
	}
	else
	{
		g_listctrlPacketListCols += 2;
	}

	/* ��ӡԴĿIP��ַ */
	if (pkt.iph != NULL)
	{
		CString strSrcIP = IPAddr2CString(pkt.iph->srcaddr);
		CString strDstIP = IPAddr2CString(pkt.iph->dstaddr);

		g_pListCtrlPacketList->SetItemText(g_listctrlPacketListRows, ++g_listctrlPacketListCols, strSrcIP);
		g_pListCtrlPacketList->SetItemText(g_listctrlPacketListRows, ++g_listctrlPacketListCols, strDstIP);
	}
	else
	{
		g_listctrlPacketListCols += 2;
	}
	g_listctrlPacketListCols = 0;		// �и�λ 

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
	for (int i = 0; i < packetLinkList.GetCount(); ++i)
	{
		POSITION pos = packetLinkList.FindIndex(i);
		printListCtrlPacketList(g_packetLinkList.GetAt(pos));
	}
	return 0;
}

/**
*	@brief ��ӡ���ݰ����ݵ��༭��
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
	for (int i = 0,  count16=1, offset = 0; i < pkt.header->caplen && pHexPacketData != NULL; ++i, ++count16)
	{
		// ��ӡ����ƫ����
		if (i % 16 == 0)
		{
			strTmp.Format("%04X:", offset);
			strPacketData += strTmp + " ";
		}

		// ��ӡ16��������
		strTmp.Format("%02X", *pHexPacketData);
		strPacketData += strTmp + " ";
		++pHexPacketData;

		// ÿ8���ֽ����ݴ�ӡһ���Ʊ��
		if (count16 == 8)
		{
			strPacketData += "\t";
		}

		// ÿ16���ֽ����ݴ�ӡASCII�ַ����ݣ�ֻ��ӡ��ĸ����
		if (count16 == 16)
		{
			strPacketData += " ";
			for (int j=0; j < 16; ++j, ++pASCIIPacketData)
			{
				strTmp.Format("%c", isalnum(*pASCIIPacketData) ? *pASCIIPacketData : '.');
				strPacketData += strTmp;
			}
			strPacketData += "\r\n";
			offset += 16;
			count16 = 0;
		}
	}
	// ��ӡʣ��ASCII�ֽ�
	for (int j = 0, count16= (pkt.header->caplen % 16); j < 16 - (pkt.header->caplen % 16); ++j, ++count16)
	{
		strPacketData += "   ";
		if (count16 == 8)
		{
			strPacketData += "\t";
		}
	}
	strPacketData += " ";
	for (int j = 0; j < (pkt.header->caplen % 16); ++j, ++pASCIIPacketData)
	{
		strTmp.Format("%c", isalnum(*pASCIIPacketData) ? *pASCIIPacketData : '.');
		strPacketData += strTmp;
	}
	strPacketData += "\r\n";
	
	g_pEditCtrlPacketData->SetWindowTextA(strPacketData);

	return 0;
}

/**
*	@brief	��ӡ���ݰ��ײ�������������οؼ�
*	@param	pkt	���ݰ�
*	@return	0 ��ӡ�ɹ�	-1 ��ӡʧ��
*/
int printTreeCtrlPacketInfo(const Packet &pkt, int pktIndex)
{
	g_pTreeCtrlPacketInfo->DeleteAllItems();

	/* ������Ž�� */
	CString strText;

	CTime pktArrivalTime((time_t)(pkt.header->ts.tv_sec));
	CString strPktArrivalTime = pktArrivalTime.Format("%Y/%m/%d %H:%M:%S");

	strText.Format("��%d�����ݰ���%s, �� %hu �ֽ�, ���� %hu �ֽڣ�", pktIndex + 1, strPktArrivalTime, pkt.header->len, pkt.header->caplen);

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

	HTREEITEM	EthNode = g_pTreeCtrlPacketInfo->InsertItem( "��̫�� ��" + strSrcMAC + " -> " + strDstMAC + "��", parentNode, 0);

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
	HTREEITEM IPNode = g_pTreeCtrlPacketInfo->InsertItem("IP ��" + IPAddr2CString(pkt.iph->srcaddr) + " -> " + IPAddr2CString(pkt.iph->dstaddr) + "��", parentNode, 0);
	CString strText;

	strText.Format("�汾�ţ�%d", pkt.iph->ver_headerlen >> 4);
	g_pTreeCtrlPacketInfo->InsertItem(strText, IPNode, 0);
	
	strText.Format("�ײ����ȣ�%d �ֽ� (%d)", (pkt.iph->ver_headerlen & 0x0f) * 4, pkt.iph->ver_headerlen & 0x0f);
	g_pTreeCtrlPacketInfo->InsertItem(strText, IPNode, 0);
	
	strText.Format("����������0x%02x", pkt.iph->tos);
	g_pTreeCtrlPacketInfo->InsertItem(strText, IPNode, 0);
	
	strText.Format("�ܳ��ȣ�%hu", ntohs(pkt.iph->totallen));
	g_pTreeCtrlPacketInfo->InsertItem(strText, IPNode, 0);
	
	strText.Format("��ʶ��0x%04hX(%hu)", ntohs(pkt.iph->identifier), ntohs(pkt.iph->identifier));
	g_pTreeCtrlPacketInfo->InsertItem(strText, IPNode, 0);
				
	strText.Format("��־��0x%02x", ntohs(pkt.iph->flags_offset) >> 13);
	HTREEITEM IPFlagNode = g_pTreeCtrlPacketInfo->InsertItem(strText, IPNode, 0);
	
	strText = "RSV��0";
	g_pTreeCtrlPacketInfo->InsertItem(strText, IPFlagNode, 0);
	
	strText.Format("MF��%d", (ntohs(pkt.iph->flags_offset) >> 14) & 0x0001);
	g_pTreeCtrlPacketInfo->InsertItem(strText, IPFlagNode, 0);
	
	strText.Format("DF��%d", (ntohs(pkt.iph->flags_offset) >> 13) & 0x0001);
	g_pTreeCtrlPacketInfo->InsertItem(strText, IPFlagNode, 0);
			
	strText.Format("Ƭƫ�ƣ�%d", ntohs(pkt.iph->flags_offset) & 0x1fff);
	g_pTreeCtrlPacketInfo->InsertItem(strText, IPNode, 0);
	
	strText.Format("TTL��%u", pkt.iph->ttl);
	g_pTreeCtrlPacketInfo->InsertItem(strText, IPNode, 0);
	
	switch(pkt.iph->protocol)
	{
	case PROTOCOL_ICMP:	
		strText = "Э�飺ICMP (1)";
		break;
	case PROTOCOL_TCP:	
		strText = "Э�飺TCP (6)";
		break;
	case PROTOCOL_UDP: 
		strText = "Э�飺UDP (17)";
		break;
	default: 
		strText.Format("Э�飺δ֪ (%d)", pkt.iph->protocol);
		break;
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
	case 1:	strText.Format("ARP ������)"); break;
	case 2:	strText.Format("ARP ����Ӧ)");	break;
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
	case ARP_OPCODE_REQUET:	strText.Format("OP�룺���� (%hu)", ntohs(pkt.arph->opcode));
		break;
	case ARP_OPCODE_REPLY:	strText.Format("OP�룺��Ӧ (%hu)", ntohs(pkt.arph->opcode));
		break;
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
	
	strText = "ICMP ��";
	switch(pkt.icmph->type)
	{
		case ICMP_TYPE_ECHO_REPLY: 
			strTmp = "��ӦӦ�𱨸�"; 
			break;
		case ICMP_TYPE_DESTINATION_UNREACHABLE: 
			strTmp = "���޲��ɴﱨ��"; 
			break;
		case ICMP_TYPE_SOURCE_QUENCH: 
			strTmp = "Դ�����Ʊ���"; 
			break;
		case ICMP_TYPE_REDIRECT: 
			strTmp = "�ض��򱨸�"; 
			break;
		case ICMP_TYPE_ECHO: 
			strTmp = "��Ӧ���󱨸�"; 
			break;
		case ICMP_TYPE_ROUTER_ADVERTISEMENT: 
			strTmp = "·����ͨ�汨��"; 
			break;
		case ICMP_TYPE_ROUTER_SOLICITATION: 
			strTmp = "·����ѯ�ʱ���";
			break;
		case ICMP_TYPE_TIME_EXCEEDED: 
			strTmp = "��ʱ����"; 
			break;
		case ICMP_TYPE_PARAMETER_PROBLEM: 
			strTmp = "���ݱ��������󱨸�"; 
			break;
		case ICMP_TYPE_TIMESTAMP: 
			strTmp = "ʱ������󱨸�"; 
			break;
		case ICMP_TYPE_TIMESTAMP_REPLY: 
			strTmp = "ʱ�����Ӧ����"; 
			break;
		default: 
			strText.Format("δ֪"); 
			break;
	}
	strText += strTmp + "��";
	ICMPNode = g_pTreeCtrlPacketInfo->InsertItem(strText, parentNode, 0);
	
	IP_Address addr = *(IP_Address*)&(pkt.icmph->others);
	u_short id = (u_short)(ntohl(pkt.icmph->others) >> 16);
	u_short seq = (u_short)(ntohl(pkt.icmph->others) & 0x0000ffff);
	
	strText.Format("���ͣ�%u", pkt.icmph->type);
	g_pTreeCtrlPacketInfo->InsertItem(strText, ICMPNode, 0);

	switch(pkt.icmph->type)
	{
		case ICMP_TYPE_ECHO_REPLY:
			strText = "���룺0";
			g_pTreeCtrlPacketInfo->InsertItem(strText, 0, 0, ICMPNode, 0);

			strText.Format("У���:0x%04hX", ntohs(pkt.icmph->chksum));
			g_pTreeCtrlPacketInfo->InsertItem(strText, 0, 0, ICMPNode, 0);

			strText.Format("��ʶ��%hu", id);
			g_pTreeCtrlPacketInfo->InsertItem(strText, 0, 0, ICMPNode, 0);

			strText.Format("��ţ�%hu", seq);
			g_pTreeCtrlPacketInfo->InsertItem(strText, 0, 0, ICMPNode, 0);

			break;

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
							
	strText.Format("TCP ��%hu -> %hu��", ntohs(pkt.tcph->srcport), ntohs(pkt.tcph->dstport));
	TCPNode = g_pTreeCtrlPacketInfo->InsertItem(strText,parentNode, 0);
							
	strText.Format("Դ�˿ڣ�%hu", ntohs(pkt.tcph->srcport));
	g_pTreeCtrlPacketInfo->InsertItem(strText, TCPNode, 0);
							
	strText.Format("Ŀ�Ķ˿ڣ�%hu", ntohs(pkt.tcph->dstport));
	g_pTreeCtrlPacketInfo->InsertItem(strText, TCPNode, 0);
							
	strText.Format("���кţ�0x%0lX", ntohl(pkt.tcph->seq));
	g_pTreeCtrlPacketInfo->InsertItem(strText, TCPNode, 0);
							
	strText.Format("ȷ�Ϻţ�0x%0lX", ntohl(pkt.tcph->ack));
	g_pTreeCtrlPacketInfo->InsertItem(strText, TCPNode, 0);
							
	strText.Format("�ײ����ȣ�%d �ֽ�(%d)", (ntohs(pkt.tcph->headerlen_rsv_flags) >> 12 ) * 4, ntohs(pkt.tcph->headerlen_rsv_flags) >> 12);
	g_pTreeCtrlPacketInfo->InsertItem(strText, TCPNode, 0);
							
	strText.Format("��־��0x%03X", ntohs(pkt.tcph->headerlen_rsv_flags) & 0x0FFF);
	HTREEITEM TCPFlagNode = g_pTreeCtrlPacketInfo->InsertItem(strText, TCPNode, 0);
							
	strText.Format("URG��%d", (ntohs(pkt.tcph->headerlen_rsv_flags) >> 5) & 0x0001);
	g_pTreeCtrlPacketInfo->InsertItem(strText, TCPFlagNode, 0);
							
	strText.Format("ACK��%d", (ntohs(pkt.tcph->headerlen_rsv_flags) >> 4) & 0x0001);
	g_pTreeCtrlPacketInfo->InsertItem(strText, TCPFlagNode, 0);
							
	strText.Format("PSH��%d", (ntohs(pkt.tcph->headerlen_rsv_flags) >> 3) & 0x0001);
	g_pTreeCtrlPacketInfo->InsertItem(strText, TCPFlagNode, 0);
							
	strText.Format("RST��%d", (ntohs(pkt.tcph->headerlen_rsv_flags) >> 2) & 0x0001);
	g_pTreeCtrlPacketInfo->InsertItem(strText, TCPFlagNode, 0);

	strText.Format("SYN��%d", (ntohs(pkt.tcph->headerlen_rsv_flags) >> 1) & 0x0001);
	g_pTreeCtrlPacketInfo->InsertItem(strText, TCPFlagNode, 0);
							
	strText.Format("FIN��%d", ntohs(pkt.tcph->headerlen_rsv_flags)  & 0x0001);
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
							
	strText.Format("UDP ��%hu -> %hu��", ntohs(pkt.udph->srcport), ntohs(pkt.udph->dstport));
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
		printDNS2TreeCtrl(pkt, parentNode);
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
	CString strText, strTmp;

	switch (pkt.dnsh->flags >> 15)
	{
	case DNS_FLAGS_QR_REQUEST:	strText = "DNS ������";		break;
	case DNS_FLAGS_QR_REPLY:	strText = "DNS ����Ӧ��";		break;
	}
	return g_pTreeCtrlPacketInfo->InsertItem(strText, parentNode, 0);
}


/**
*	@brief	��ӡDNS�ײ�
*	@param	dnsh	DNS�ײ�
*	@param	parentNode	���ڵ�
*	@return 0 ��ӡ�ɹ�	-1 ��ӡʧ��
*/
int printDNSHeader(const DNS_Header *dnsh, HTREEITEM & parentNode)
{
	if (dnsh == NULL || parentNode == NULL)
	{
		return -1;
	}
	CString strText, strTmp;
	strText.Format("��ʶ��0x%04hX (%hu)", ntohs(dnsh->identifier), ntohs(dnsh->identifier));
	g_pTreeCtrlPacketInfo->InsertItem(strText, parentNode, 0);

	strText.Format("��־��0x%04hX", ntohs(dnsh->flags));
	strText += strTmp;

	HTREEITEM DNSFlagNode = g_pTreeCtrlPacketInfo->InsertItem(strText, parentNode, 0);
	/* ��־���ֶ� */
	switch (ntohs(dnsh->flags) >> 15)
	{
	case DNS_FLAGS_QR_REQUEST:	strText = "QR��; ��ѯ���� ��0��";	break;
	case DNS_FLAGS_QR_REPLY:	strText = "QR��; ��Ӧ���� ��1��";	break;
	}
	g_pTreeCtrlPacketInfo->InsertItem(strText, DNSFlagNode, 0);

	switch ((ntohs(dnsh->flags) >> 11) & 0x000f)
	{
	case DNS_FLAGS_OPCODE_STANDARD_QUERY:			strText = "Opcode����׼��ѯ ��0��";	break;
	case DNS_FLAGS_OPCODE_INVERSE_QUERY:			strText = "Opcode�������ѯ ��1��";	break;
	case DNS_FLAGS_OPCODE_SERVER_STATUS_REQUEST:	strText = "Opcode��������״̬���� ��2��"; break;
	}
	g_pTreeCtrlPacketInfo->InsertItem(strText, DNSFlagNode, 0);

	switch ((ntohs(dnsh->flags) >> 10) & 0x0001)
	{
	case 0:	strText = "AA������Ȩ�ش� ��0��"; break;
	case 1: strText = "AA����Ȩ�ش� ��1��"; break;
	}
	g_pTreeCtrlPacketInfo->InsertItem(strText, DNSFlagNode, 0);


	switch ((ntohs(dnsh->flags) >> 9) & 0x0001)
	{
	case 0: strText = "TC������δ�ض� ��0��"; break;
	case 1: strText = "TC�����Ľض� ��1��";	break;
	}
	g_pTreeCtrlPacketInfo->InsertItem(strText, DNSFlagNode, 0);


	switch ((ntohs(dnsh->flags) >> 8) & 0x0001)
	{
	case 0: strText = "RD��0"; break;
	case 1: strText = "RD��ϣ�����еݹ��ѯ ��1��";	break;
	}
	g_pTreeCtrlPacketInfo->InsertItem(strText, DNSFlagNode, 0);

	switch ((ntohs(dnsh->flags) >> 7) & 0x0001)
	{
	case 0: strText = "RA����������֧�ֵݹ��ѯ ��0��"; break;
	case 1: strText = "RA��������֧�ֵݹ��ѯ ��1��";	break;
	}
	g_pTreeCtrlPacketInfo->InsertItem(strText, DNSFlagNode, 0);

	strText.Format("Reserved��%d", (ntohs(dnsh->flags) >> 4) & 0x0007);
	g_pTreeCtrlPacketInfo->InsertItem(strText, DNSFlagNode, 0);

	switch (ntohs(dnsh->flags) & 0x000f)
	{
	case 0: strText = "rCode���޲�� ��0��";			break;
	case 1: strText = "rCode����ʽ��� ��1��";			break;
	case 2: strText = "rCode��DNS���������� ��2��";		break;
	case 3: strText = "rCode�����������ڻ���� ��3��";	break;
	case 4: strText = "rCode����ѯ���Ͳ�֧�� ��4��";	break;
	case 5: strText = "rCode���ڹ����Ͻ�ֹ ��5��";		break;
	default: strText.Format("rCode��������%d��", ntohs(dnsh->flags) & 0x000f);		break;
	}
	g_pTreeCtrlPacketInfo->InsertItem(strText, DNSFlagNode, 0);

	strText.Format("��ѯ��¼����%hu", ntohs(dnsh->questions));
	g_pTreeCtrlPacketInfo->InsertItem(strText, parentNode, 0);

	strText.Format("�ش��¼����%hu", ntohs(dnsh->answers));
	g_pTreeCtrlPacketInfo->InsertItem(strText, parentNode, 0);

	strText.Format("��Ȩ�ش��¼����%hu", ntohs(dnsh->authority));
	g_pTreeCtrlPacketInfo->InsertItem(strText, parentNode, 0);

	strText.Format("������Ϣ��¼����%hu", ntohs(dnsh->additional));
	g_pTreeCtrlPacketInfo->InsertItem(strText, parentNode, 0);

	return 0;
}

/**
*	@brief	��ӡDNS��ѯ����
*	@param	dnsq		��ѯ����
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
	int queryNum = 0, byteCounter = 0;
	char *p = DNSQuery;
	if (questions < 10)
	{
		while (queryNum < questions)
		{
			char *name1 = (char*)malloc(strlen(p) + 1);
			translateName(name1, p);

			/* ���������ֶ� */
			while (*p)
			{
				++p;
				++byteCounter;
			}
			++p;
			++byteCounter;

			strText.Format("%s:", name1);

			DNS_Query *dnsq = (DNS_Query*)p;
			u_short	type, classes;

			type = ntohs(dnsq->type);
			classes = ntohs(dnsq->classes);

			switch (type)
			{
			case 1:	strTmp = "type A"; break;
			case 2:	strTmp = "type NS"; break;
			case 5: strTmp = "type CNAME"; break;
			case 6: strTmp = "type SOA"; break;
			case 12: strTmp = "type PTR"; break;
			case 15: strTmp = "type MX"; break;
			case 28: strTmp = "type AAAA"; break;
			case 255: strTmp = "type ANY"; break;
			default: strTmp.Format("type UNKNOWN(%hu)", type); break;
			}
			strText += strTmp + ", ";

			switch (classes)
			{
			case 1: strTmp = "class INTERNET"; break;
			case 2: strTmp = "class CSNET";	break;
			case 3: strTmp = "class COAS";	break;
			default: strTmp.Format("class UNKNOWN(%hu)", classes); break;
			}
			strText += strTmp;

			g_pTreeCtrlPacketInfo->InsertItem(strText, DNSQueryNode, 0);

			/* ������ѯ���ͺͲ�ѯ���ֶ� */
			p += sizeof(DNS_Query);
			byteCounter += sizeof(DNS_Query);
			queryNum++;
			free(name1);
		}// while
	}// if
	return p - DNSQuery + 1;
}

/**
*	@brief	��ӡDNS�ش𲿷�
*	@param	dnsa		�ش𲿷�
*	@param	answers		�ش��¼��
*	@param	parentNode	���ڵ�
*	@return	0 ��ӡ�ɹ�	-1 ��ӡʧ��	������ DNS�ش𲿷��ܳ���
*/
int printDNSAnswer(char *DNSAnswer, const u_short &answers, const DNS_Header *dnsh, HTREEITEM &parentNode)
{
	if (DNSAnswer == NULL || parentNode == NULL)
	{
		return -1;
	}
	CString strText, strTmp;
	HTREEITEM DNSAnswerNode = g_pTreeCtrlPacketInfo->InsertItem("�ش𲿷֣�", parentNode, 0);

	int answerNum = 0, byteCounter = 0;
	char *p = DNSAnswer;
	/* �ش𲿷� */
	while (answerNum < answers)
	{
		/* ָ��ָ�� */
		if (*p == 0xc0)
		{

			/* ָ��ƫ����
			++p;

			char *name = (char*)(pkt_data + offset + *(char*)p);			// ����
			char *name1 = (char*)malloc(strlen(name)+1);


			translateName(name1, name);

			strText.Format("%s", name1);
			strText += "��";

			free(name1);
			*/

			char name[70];
			char name1[70];

			translateData(dnsh, name, p, 2);
			translateName(name1, name);

			strText.Format("%s��", name1);

			/* ָ��ƫ���� */
			++p;
			++byteCounter;


			/* ָ������*/
			++p;
			++byteCounter;
			DNS_Answer *dnsa = (DNS_Answer*)p;

			u_short type = ntohs(dnsa->type);
			u_short classes = ntohs(dnsa->classes);
			u_long  ttl = ntohl(dnsa->ttl);

			switch (type)
			{
			case 1:	strTmp = "type A"; break;
			case 2:	strTmp = "type NS"; break;
			case 5: strTmp = "type CNAME"; break;
			case 6: strTmp = "type SOA"; break;
			case 12: strTmp = "type PTR"; break;
			case 15: strTmp = "type MX"; break;
			case 28: strTmp = "type AAAA"; break;
			case 255: strTmp = "type ANY"; break;
			default: strTmp.Format("type UNKNOWN(%hu)", type); break;
			}
			strText += strTmp + ", ";

			switch (classes)
			{
			case 1: strTmp = "class INTERNET"; break;
			case 2: strTmp = "class CSNET";	break;
			case 3: strTmp = "class COAS";	break;
			default: strTmp.Format("class UNKNOWN(%hu)", classes); break;
			}
			strText += strTmp + ", ";

			strTmp.Format("TTL %lu", ttl);
			strText += strTmp + ", ";

			/* ָ����Դ���ݳ��� */
			p += sizeof(DNS_Answer);
			byteCounter += sizeof(DNS_Answer);
			u_short data_len = ntohs(*(u_short*)p);

			strTmp.Format("��Դ���ݳ��� %hu", data_len);
			strText += strTmp + ", ";

			/* ָ����Դ���� */
			p += sizeof(u_short);
			byteCounter += sizeof(u_short);

			/* ��ѯ����ΪNS��CNAME��PTR����Դ���� */
			if (type == 2 || type == 5 || type == 12)
			{

				/* ��Դ����Ϊָ��0xc0 + ƫ����*/
				if (*(char*)p == 0xC0)
				{
					/* ����ƫ������ȡ����
					char *data = (char*)(pkt_data + offset + *(char*)(p+1));			// ����
					char *data1 = (char*)malloc(strlen(data)+1);

					translateName(data1, data);

					strText.Format("%s", data1);
					strText += strTmp;

					free(data1);
					*/
					char data[70];
					char data1[70];

					translateData(dnsh, data, p, 2);
					translateName(data1, data);

					strText.Format("%s", data1);
					strText += strTmp;

				}
				/* ��Դ���ݴ���ָ��0xc0 + ƫ���� */
				else if (isNamePtr(p))
				{
					char data[70];
					char data1[70];

					translateData(dnsh, data, p, data_len);		// ȥ��ָ��0xc0+ƫ����
					translateName(data1, data);								// ȥ��'.'

					strTmp.Format("%s", data1);
					strText += strTmp;
				}
				/* ��Դ�����в�����ָ��0xc0 + ƫ���� */
				else
				{
					char *data = (char*)malloc(data_len);

					translateName(data, p);

					strTmp.Format("%s", data);
					strText += strTmp;
					free(data);

				}
			}
			/* ��ѯ����ΪA����Դ���� */
			else if (type == 1)
			{
				IP_Address data = *(IP_Address*)p;
				strText += IPAddr2CString(data);
			}

			g_pTreeCtrlPacketInfo->InsertItem(strText, DNSAnswerNode, 0);

			/* �������ݲ��� */
			p += data_len;
			byteCounter += data_len;

		}// if
		answerNum++;
	}// while
	return byteCounter;
}


int printDNSAuthority(char *DNSAuthority, const u_short &authority, const DNS_Header *dnsh, HTREEITEM parentNode)
{
	CString strText, strTmp;
	HTREEITEM DNSAuthorityNode = g_pTreeCtrlPacketInfo->InsertItem("��Ȩ�ش𲿷֣�", parentNode, 0);

	int authorityNum = 0, byteCounter = 0;;
	char *p = DNSAuthority;
	/* ��Ȩ�ش𲿷� */
	while (authorityNum < authority)
	{
		/* ָ��ָ�� */
		if (*p == 0xC0)
		{

			/* ָ��ƫ����
			++p;

			char *name = (char*)(pkt_data + offset + *(char*)p);			// ����
			char *name1 = (char*)malloc(strlen(name)+1);
			translateName(name1, name);

			strText.Format("%s", name1);
			strText += "��";
			free(name1);
			*/
			char name[70];
			char name1[70];

			translateData(dnsh, name, p, 2);
			translateName(name1, name);

			strText.Format("%s", name1);
			strText += "��";

			/* ָ��ƫ���� */
			++p;
			++byteCounter;

			/* ָ������*/
			++p;
			++byteCounter;
			DNS_Answer *dnsa = (DNS_Answer*)p;

			u_short type = ntohs(dnsa->type);
			u_short classes = ntohs(dnsa->classes);
			u_long  ttl = ntohl(dnsa->ttl);

			switch (type)
			{
			case 1:	strTmp = "type A"; break;
			case 2:	strTmp = "type NS"; break;
			case 5: strTmp = "type CNAME"; break;
			case 6: strTmp = "type SOA"; break;
			case 12: strTmp = "type PTR"; break;
			case 15: strTmp = "type MX"; break;
			case 28: strTmp = "type AAAA"; break;
			case 255: strTmp = "type ANY"; break;
			default: strTmp.Format("type UNKNOWN(%hu)", type); break;
			}
			strText += strTmp + ", ";

			switch (classes)
			{
			case 1: strTmp = "class INTERNET"; break;
			case 2: strTmp = "class CSNET";	break;
			case 3: strTmp = "class COAS";	break;
			default: strTmp.Format("class UNKNOWN(%hu)", classes); break;
			}
			strText += strTmp + ", ";

			strTmp.Format("ttl %lu", ttl);
			strText += strTmp + ", ";

			/* ָ����Դ���ݳ��� */
			p += sizeof(DNS_Answer);
			byteCounter += sizeof(DNS_Answer);

			u_short data_len = ntohs(*(u_short*)p);

			strTmp.Format("len %hu", data_len);
			strText += strTmp + ", ";

			/* ָ����Դ���� */
			p += sizeof(u_short);
			byteCounter += sizeof(u_short);

			/* ��ѯ����ΪNS��CNAME��PTR����Դ���� */
			if (type == 2 || type == 5 || type == 12)
			{

				/* ��Դ����Ϊָ��0xc0 + ƫ����*/
				if (*(char*)p == 0xc0)
				{
					/* ����ƫ������ȡ����
					char *data = (char*)(pkt_data + offset + *(char*)(p+1));			// ����
					char *data1 = (char*)malloc(strlen(data)+1);
					translateName(data1, data);
					strTmp.Format("%s", data1);
					strText += strTmp;
					free(data1);
					*/

					char data[70];
					char data1[70];

					translateData(dnsh, data, p, 2);
					translateName(data1, data);

					strTmp.Format("%s", data1);
					strText += strTmp;
				}
				/* ��Դ���ݴ���ָ��0xc0 + ƫ���� */
				else if (isNamePtr(p))
				{
					char data[70];
					char data1[70];

					translateData(dnsh, data, p, data_len);		// ȥ��ָ��0xc0+ƫ����
					translateName(data1, data);								// ȥ��'.'

					strTmp.Format("%s", data1);
					strText += strTmp;
				}
				/* ��Դ�����в�����ָ��0xc0 + ƫ���� */
				else
				{
					char *data = (char*)malloc(data_len);

					translateName(data, p);

					strTmp.Format("%s", data);
					strText += strTmp;
					free(data);

				}
			}
			/* ��ѯ����ΪA����Դ���� */
			else if (type == 1)
			{
				IP_Address data = *(IP_Address*)p;

				strText += IPAddr2CString(data);
			}

			g_pTreeCtrlPacketInfo->InsertItem(strText, DNSAuthorityNode, 0);

			/* �������ݲ��� */
			p += data_len;
			byteCounter += data_len;


		}// if
		authorityNum++;
	}
	return byteCounter;
}

/**
*	@brief	��ӡDNS������Ϣ����
*	@param	dnsa		������Ϣ����
*	@param	answers		������Ϣ��¼��
*	@param	parentNode	���ڵ�
*	@return	0 ��ӡ�ɹ�	-1 ��ӡʧ�� ������ DNS������Ϣ�����ܳ���
*/
int printDNSAdditional(char *DNSAdditional, const u_short &additional, const DNS_Header *dnsh, HTREEITEM &parentNode)
{
	if (DNSAdditional == NULL || parentNode == NULL)
	{
		return -1;
	}
	CString strText, strTmp;
	HTREEITEM DNSAdditionalNode = g_pTreeCtrlPacketInfo->InsertItem("������Ϣ���֣�", parentNode, 0);

	int additionalNum = 0, byteCounter = 0;
	char *p = DNSAdditional;
	/* ������Ϣ���� */
	while (additionalNum < additional)
	{

		/* ָ��ָ�� */
		if (*(char*)p == 0xC0)
		{

			/* ָ��ƫ����
			++p;

			char *name = (char*)(pkt_data + offset + *(char*)p);			// ����
			char *name1 = (char*)malloc(strlen(name)+1);

			translateName(name1, name);

			strText.Format("%s", name1);
			strText += "��";

			free(name1);
			*/
			char name[70];
			char name1[70];

			translateData(dnsh, name, p, 2);
			translateName(name1, name);

			strText.Format("%s", name1);
			strText += "��";

			/* ָ��ƫ���� */
			++p;
			++byteCounter;

			/* ָ������*/
			++p;
			++byteCounter;
			DNS_Answer *dnsa = (DNS_Answer*)p;

			u_short type = ntohs(dnsa->type);
			u_short classes = ntohs(dnsa->classes);
			u_long  ttl = ntohl(dnsa->ttl);

			switch (type)
			{
			case 1:	strTmp = "type A"; break;
			case 2:	strTmp = "type NS"; break;
			case 5: strTmp = "type CNAME"; break;
			case 6: strTmp = "type SOA"; break;
			case 12: strTmp = "type PTR"; break;
			case 15: strTmp = "type MX"; break;
			case 28: strTmp = "type AAAA"; break;
			case 255: strTmp = "type ANY"; break;
			default: strText.Format("type UNKNOWN(%hu)", type); break;
			}
			strText += strTmp + ", ";

			switch (classes)
			{
			case 1: strTmp = "class INTERNET"; break;
			case 2: strTmp = "class CSNET";	break;
			case 3: strTmp = "class COAS";	break;
			default: strText.Format("class UNKNOWN(%hu)", classes); break;
			}
			strText += strTmp + ", ";

			strText.Format("ttl %lu", ttl);
			strText += strTmp + ", ";

			/* ָ����Դ���ݳ��� */
			p += sizeof(DNS_Answer);
			byteCounter += sizeof(DNS_Answer);

			u_short data_len = ntohs(*(u_short*)p);

			strText.Format("len %hu", data_len);
			strText += strTmp + ", ";

			/* ָ����Դ���� */
			p += sizeof(u_short);
			byteCounter += sizeof(u_short);

			/* ��ѯ����ΪNS��CNAME��PTR����Դ���� */
			if (type == 2 || type == 5 || type == 12)
			{

				/* ��Դ����Ϊָ��0xc0 + ƫ����*/
				if (*(char*)p == 0xc0)
				{
					/* ����ƫ������ȡ����
					char *data = (char*)(pkt_data + offset + *(char*)(p+1));			// ����
					char *data1 = (char*)malloc(strlen(data)+1);

					translateName(data1, data);

					strText.Format("%s", data1);
					strText += strTmp;

					free(data1);
					*/

					char data[70];
					char data1[70];

					translateData(dnsh, data, p, 2);
					translateName(data1, data);

					strText.Format("%s", data1);
					strText += strTmp;
				}
				/* ��Դ���ݴ���ָ��0xc0 + ƫ���� */
				else if (isNamePtr(p))
				{
					char data[70];
					char data1[70];

					translateData(dnsh, data, p, data_len);		// ȥ��ָ��0xc0+ƫ����
					translateName(data1, data);								// ȥ��'.'

					strText.Format("%s", data1);
					strText += strTmp;
				}
				/* ��Դ�����в�����ָ��0xc0 + ƫ���� */
				else
				{
					char *data = (char*)malloc(data_len);

					translateName(data, p);

					strText.Format("%s", data);
					strText += strTmp;
					free(data);

				}
			}
			/* ��ѯ����ΪA����Դ���� */
			else if (type == 1)
			{
				IP_Address data = *(IP_Address*)p;
				strText += IPAddr2CString(data);
			}

			g_pTreeCtrlPacketInfo->InsertItem(strText, DNSAdditionalNode, 0);

			/* �������ݲ��� */
			p += data_len;
			byteCounter += data_len;

		}// if
		additionalNum++;
	}// while
	return byteCounter;
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

	printDNSHeader(pkt.dnsh, DNSNode);


	char *DNSQuery = (char*)pkt.dnsh + DNS_HEADER_LENGTH;
	int DNSQueryLen = printDNSQuery(DNSQuery, ntohs(pkt.dnsh->questions), DNSNode);

	char *DNSAnswer = NULL, *DNSAuthority = NULL, *DNSAdditional = NULL;
	int DNSAnswerLen = 0, DNSAuthorityLen = 0;

	if (pkt.dnsh->answers > 0)
	{
		DNSAnswer = DNSQuery + DNSQueryLen;
		DNSAnswerLen = printDNSAnswer(DNSAnswer, ntohs(pkt.dnsh->answers), pkt.dnsh, DNSNode);
	}

	if (pkt.dnsh->authority > 0)
	{
		DNSAuthority = DNSAnswer + DNSAnswerLen;
		DNSAuthorityLen = printDNSAuthority(DNSAuthority, ntohs(pkt.dnsh->authority), pkt.dnsh, DNSNode);
	}
	

	if (pkt.dnsh->additional > 0)
	{
		DNSAdditional = DNSAuthority + DNSAuthorityLen;
		printDNSAdditional(DNSAdditional, ntohs(pkt.dnsh->additional), pkt.dnsh, DNSNode);
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
		strText.Format("%02X", pkt.dhcph->chaddr[i]);
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
				strText.Format("%c", *(++p));
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
				strText.Format("%c", *(++p));
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
			strTmp.Format("ѡ���%d", *p);
			strText += strTmp + "��";
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
		strText = "HTTP (����)";
	}
	else if (ntohs(pkt.tcph->srcport) == PORT_HTTP)
	{
		strText = "HTTP (��Ӧ)";
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
*	@brief	����б���ӡ���ݰ��ײ�������������οؼ� 
*	@param	
*	@return	-
*/
void CSnifferUIDlg::OnClickList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	/* ��ȡѡ���е��к� */
	int	selRow = g_pListCtrlPacketList->GetSelectionMark();
	if (selRow == -1)
	{
		return;
	}

	POSITION pos = g_packetLinkList.FindIndex(selRow);
	Packet &pkt = g_packetLinkList.GetAt(pos);

	printTreeCtrlPacketInfo(pkt, selRow);
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
	else if(CDDS_ITEMPREPAINT == pNMCD->nmcd.dwDrawStage) 
	{

		COLORREF itemColor;

		POSITION pos = g_packetLinkList.FindIndex(pNMCD->nmcd.dwItemSpec);
		Packet &pkt = g_packetLinkList.GetAt(pos);

		if (pkt.protocol == "ARP")
		{
			itemColor = RGB(255, 182, 193);
		}
		else if (pkt.protocol == "ICMP")
		{
			itemColor = RGB(186, 85, 211);
		}
		else if (pkt.protocol == "TCP")
		{
			itemColor = RGB(144, 238, 144);
		}
		else if (pkt.protocol == "UDP")
		{
			itemColor = RGB(100, 149, 237);

		}
		else if (pkt.protocol == "DNS")
		{
			itemColor = RGB(135, 206, 250);
		}
		else if (pkt.protocol == "DHCP")
		{
			itemColor = RGB(189, 254, 76);
		}
		else if (pkt.protocol == "HTTP")
		{
			itemColor = RGB(238, 232, 180);
		}
		else
		{
			itemColor = RGB(211, 211, 211);
		}

		pNMCD->clrTextBk = itemColor;
		*pResult = CDRF_DODEFAULT;
	}
}

void translateName(char *name1, const char *name2)
{
	strcpy(name1, name2);

	char *p = name1;
	bool canMove = false;

	if (!isalnum(*(u_char*)p) && *(u_char*)p != '-')
	{
		canMove = true;
	}

	/* ������ת��Ϊ'.' */
	while (*p)
	{
		if (!isalnum(*(u_char*)p) && *(u_char*)p != '-')
			*p = '.';

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

			int pos = isNamePtr(data_ptr);
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
/* �ж�data������ָ��0xc0,������ָ����data�е�λ��*/
int isNamePtr(char *data)
{
	char *p = data;
	int pos = 0;

	while (*p)
	{
		if (*(u_char*)p == 0xC0)
		{
			return pos;
		}
		++p;
		++pos;
	}

	return 0;
}