#include "pcap.h"
#include "remote-ext.h"
#include "Afxtempl.h"
#include "Packet.h"

#define PCAP_ERRBUFF_SIZE	50

/* ���ļ��ļ��� */
char filename[50];

/* �ؼ�ָ�� */
CWnd *g_pBtnStart;
CWnd *g_pBtnPause;
CWnd *g_pBtnStop;
CComboBox *g_pComboBoxDevList;
CListCtrl *g_pListCtrlPacketList;
CTreeCtrl *g_pTreeCtrlPacketInfo;
CEdit *g_pEditCtrlPacketData;

/* ������Ϣ */
pcap_if_t *g_pAllDevs,*g_pDev;

/* pcapץ���õ��ı��� */
pcap_t *g_pAdhandle;

/* ȫ�ֱ���errbuf����Ŵ�����Ϣ */
char g_errbuf[PCAP_ERRBUF_SIZE];



/* ���ݰ��б����У���� */
int g_listctrlPacketListRows = -1;
int g_listctrlPacketListCols = 0;
int g_listctrlPacketListCount = 0;



/* �������汨�ĵ��ײ� */
//CList<packet_header, packet_header> linklist;
CList<Packet, Packet> g_packetLinkList;

/* �߳���ں��� */
UINT capture_thread(LPVOID pParam);
//UINT decode_thread(LPVOID pParam);

//typedef struct decode_Thread_pParam
//{
//	u_char*	pkt_data;
//	u_short	caplen;
//}decode_Thread_pParam;

/* �������� */
void packet_handler(u_char *dumpfile, const struct pcap_pkthdr *header, const u_char *pkt_data);

/* �ؼ���ʼ�� */
void initialComboBoxDevList();
void initialListCtrlPacketList();


/* ��ӡ */
int printListCtrlPacketList(const Packet &pkt);
int printListCtrlPacketList(const CList<Packet, Packet> &packetLinkList);


int	printEditCtrlPacketData(const Packet &pkt);

int printTreeCtrlPacketInfo(const Packet &pkt, int pktIndex);
int printEthernet2TreeCtrl(const Packet &pkt, HTREEITEM &parentNode);
int	printIP2TreeCtrl(const Packet &pkt, HTREEITEM &parentNode);
int	printARP2TreeCtrl(const Packet &pkt, HTREEITEM &parentNode);
int	printICMP2TreeCtrl(const Packet &pkt, HTREEITEM &parentNode);
int	printTCP2TreeCtrl(const Packet &pkt, HTREEITEM &parentNode);
int	printUDP2TreeCtrl(const Packet &pkt, HTREEITEM &parentNode);
//int	printDNS2TreeCtrl(const Packet &pkt, HTREEITEM &parentNode);
//int	printDHCP2TreeCtrl(const Packet &pkt, HTREEITEM &parentNode);
//int	printHTTP2TreeCtrl(const Packet &pkt, HTREEITEM &parentNode);

/* ת�� */
CString	MACAddr2CString(const MAC_Address &addr);
CString	IPAddr2CString(const IP_Address &addr);






/* �洢�����ײ�	*/
//void saveFrame(const u_char *pkt_data, int offset);		//ok
//void saveIP(const u_char *pkt_data, int offset);		//ok
//void saveARP(const u_char *pkt_data, int offset);		//ok
//void saveUDP(const u_char *pkt_data, int offset);		//ok
//void saveTCP(const u_char *pkt_data, int offset);		//ok
//void saveICMP(const u_char *pkt_data,int offset);		//ok
//void saveDNS(const u_char *pkt_data,int offset);		//ok


/* ���������ײ� */
//void decodeFrame(mac_address *saddr, mac_address *daddr, u_short *eth_type, HTREEITEM *hParent);
//void decodeIP(ip_header *iph,HTREEITEM *hParent);
//void decodeARP(arp_header *arph, HTREEITEM *hParent);
//void decodeUDP(udp_header *udph, HTREEITEM *hParent);
//void decodeTCP(tcp_header *tcph, HTREEITEM *hParent);
//void decodeDNS(u_char *pkt_data, int offset, dns_header *dnsh, HTREEITEM *hParent);			// offsetΪ��dns�ײ���ƫ����
//void decodeHTTP(u_char *pkt_data, int offset, HTREEITEM *hParent);							// offsetΪ��HTTP���ĵ�ƫ����
//void decodeICMP(icmp_header *icmph, HTREEITEM *hParent);		
//void decodeDHCP(u_char *pkt_data, int offset, HTREEITEM *hParent);							// offsetΪ��DHCP���ĵ�ƫ����


///* ����ת�� ���涨��ʽ��name2ת��Ϊ����name1 */
//void translateName(char *name1, const char *name2);
//
///* DNS��Դ��¼���ݲ���ת�� ������ָ��c0�ĵ�ַdata2ת��Ϊ��ַdata1 offsetΪ��dns�ײ���ƫ����*/
//void translateData(u_char *pkt_data, int offset, char *data1, char *data2, int data2_len);
//
///* �ж�data������ָ��0xc0,������ָ����data�е�λ��*/
//int isNamePtr(char *data);
