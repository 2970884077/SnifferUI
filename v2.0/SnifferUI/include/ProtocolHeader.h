//#include "pcap.h"
#define ETHERNET_HEADER_LENGTH	14
#define	UDP_HEADER_LENGTH		8

#define	ETHERNET_TYPE_IP		0x0800
#define	ETHERNET_TYPE_ARP		0x0806
#define PROTOCOL_ICMP			1
#define PROTOCOL_TCP			6
#define PROTOCOL_UDP			17
#define PORT_DNS				53
#define	PORT_DHCP_CLIENT		67
#define PORT_DHCP_SERVER		68
#define PORT_HTTP				80

#define ARP_OPCODE_REQUET		1
#define	ARP_OPCODE_REPLY		2

/**
*	@brief	ICMP_TYPE
*/
#define ICMP_TYPE_ECHO_REPLY				0
#define	ICMP_TYPE_DESTINATION_UNREACHABLE	3
#define ICMP_TYPE_SOURCE_QUENCH				4
#define ICMP_TYPE_REDIRECT					5
#define ICMP_TYPE_ECHO						8
#define ICMP_TYPE_ROUTER_ADVERTISEMENT		9
#define ICMP_TYPE_ROUTER_SOLICITATION		10
#define ICMP_TYPE_TIME_EXCEEDED				11
#define ICMP_TYPE_PARAMETER_PROBLEM			12
#define ICMP_TYPE_TIMESTAMP					13
#define ICMP_TYPE_TIMESTAMP_REPLY			14

/**
*	@brief	ICMP_CODE
*/
#define ICMP_TYPE_DESTINATION_UNREACHABLE_CODE_NET_UNREACHABLE					0
#define ICMP_TYPE_DESTINATION_UNREACHABLE_CODE_HOST_UNREACHABLE					1
#define ICMP_TYPE_DESTINATION_UNREACHABLE_CODE_PROTOCOL_UNREACHABLE				2
#define ICMP_TYPE_DESTINATION_UNREACHABLE_CODE_PORT_UNREACHABLE					3
#define ICMP_TYPE_DESTINATION_UNREACHABLE_CODE_FRAGMENTATION_NEEDED_AND_DF_SET	4
#define ICMP_TYPE_DESTINATION_UNREACHABLE_CODE_SOURCE_ROUTE_FAILED				5

#define ICMP_TYPE_SOURCE_QUENCH_CODE											0

#define ICMP_TYPE_REDIRECT_CODE_REDIRECT_DATAGRAMS_FOR_THE_NETWORK				0
#define ICMP_TYPE_REDIRECT_CODE_REDIRECT_DATAGRAMS_FOR_THE_HOST					1
#define ICMP_TYPE_REDIRECT_CODE_REDIRECT_DATAGRAMS_FOR_THE_TOS_AND_NETWORK		2
#define ICMP_TYPE_REDIRECT_CODE_REDIRECT_DATAGRAMS_FOR_THE_TOS_AND_HOST			3

#define ICMP_TYPE_ECHO_CODE														0

#define ICMP_TYPE_ROUTER_ADVERTISEMENT_CODE										0
#define ICMP_TYPE_ROUTER_SOLICITATION_CODE										0

#define ICMP_TYPE_TIME_EXCEEDED_CODE_TTL_EXCEEDED_IN_TRANSIT					0
#define ICMP_TYPE_TIME_EXCEEDED_CODE_FRAGMENT_REASSEMBLY_TIME_EXCEEDE			1

#define ICMP_TYPE_PARAMETER_PROBLEM_CODE_POINTER_INDICATES_THE_ERROR			0	

#define ICMP_TYPE_TIMESTAMP_CODE												0




typedef struct MAC_Address
{
	u_char	bytes[6];

}MAC_Address;

typedef struct IP_Address
{
	u_char bytes[4];

}IP_Address;

typedef struct Ethernet_Header
{
	MAC_Address	dstaddr;		// Ŀ��MAC��ַ
	MAC_Address	srcaddr;		// ԴMAC��ַ	
	u_short		eth_type;		// ����

}Ethernet_Header;

typedef struct IP_Header
{
	u_char		ver_headerlen ;	// �汾��(4 bits) + �ײ�����(4 bits)
	u_char		tos;			// ��������
	u_short		totallen;		// �ܳ���
	u_short		identifier;		// ��ʶ
	u_short		flags_offset;	// ��־(3 bits) + Ƭƫ��(13 bits)
	u_char		ttl;			// ����ʱ��
	u_char		protocol;		// �ϲ�Э��
	u_short		checksum;		// �ײ�У���
	IP_Address	srcaddr;		// Դ��ַ
	IP_Address	dstaddr;		// Ŀ�ĵ�ַ
	u_int		option_padding;	// ѡ������

}IP_Header;


typedef struct ARP_Header
{
	u_short		hwtype;			// Ӳ������
	u_short		ptype;			// Э������
	u_char		hwlen;			// Ӳ������
	u_char		plen;			// Э�鳤��
	u_short		opcode;			// ������
	MAC_Address	srcmac;			// Դmac��ַ
	IP_Address	srcip;			// Դip��ַ
	MAC_Address	dstmac;			// Ŀ��mac��ַ
	IP_Address	dstip;			// Ŀ��ip��ַ

}ARP_Header;

typedef struct ICMP_Header
{
	u_char		type;				// ����
	u_char		code;				// ����
	u_short		chksum;				// У���
	u_int		others;				// �ײ��������֣��ɱ���������ȷ����Ӧ���ݣ�

}ICMP_Header;

typedef struct TCP_Header
{
	u_short		srcport;				// Դ�˿�
	u_short		dstport;				// Ŀ�Ķ˿�
	u_int		seq;					// ���
	u_int		ack;					// ȷ�Ϻ�
	u_short		headerlen_rsv_flags;	// �ײ�����(4 bits) + ����(6 bits) + 
										// URG(1 bit) + ACK(1 bit) + PSH(1 bit) + RST(1 bit) + SYN(1 bit) + FIN(1 bit)
	u_short		win_size;				// ���ڴ�С
	u_short		chksum;					// У���
	u_short		urg_ptr;				// ����ָ��
	u_int		option;					// ѡ��

}TCP_Header;

typedef struct UDP_Header
{
	u_short srcport;			// Դ�˿�
	u_short dstport;			// Ŀ�Ķ˿�
	u_short	len;				// ����
	u_short checksum;			// У���

}UDP_Header;

typedef struct DNS_Header
{
	u_short		identifier;		// ��ʶ
	u_short		flags;			// ��־
	u_short		questions;		// ��ѯ��¼��
	u_short		answers;		// �ش��¼��
	u_short		authority;		// ��Ȩ�ش��¼��
	u_short		additional;		// ������Ϣ��¼��

}DNS_Header;

typedef struct DNS_Query
{
	u_short type;				// ��ѯ����
	u_short classes;			// ��ѯ��

}DNS_Query;

typedef struct DNS_Answer
{
	u_short		type;				// ����
	u_short		classes;			// ��
	u_int		ttl;				// ����ʱ��

}DNS_Answer;


/* chaddr�ֶε�option�ֶ���decodeDHCP�н��� */
typedef struct DHCP_Header
{
	u_char		op;					// ��������
	u_char		htype;				// Ӳ������
	u_char		hlen;				// Ӳ����ַ����
	u_char		hops;				// ����
	u_int		xid;				// ����ID
	u_short		secs;				// �ͻ�����ʱ��
	u_short		flags;				// ��־
	IP_Address	ciaddr;			// �ͻ���IP��ַ
	IP_Address	yiaddr;			// ���IP��ַ
	IP_Address	siaddr;			// ������IP��ַ
	IP_Address	giaddr;			// ����IP��ַ
//  u_char[16] chaddr;			// �ͻ�Ӳ����ַ
//  u_char[64] sname;			// ������������
//  u_char[128] file;			// �����ļ���
//  options(variable)			// ѡ��䳤��
	
}DHCP_Header;



