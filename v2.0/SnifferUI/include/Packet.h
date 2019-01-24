#pragma once
#include "ProtocolHeader.h"

class Packet
{
public:
	Ethernet_Header			*ethh;			// ��̫���ײ�
	IP_Header				*iph;			// ip�ײ�
	ARP_Header				*arph;			// arp�ײ�
	ICMP_Header				*icmph;			// icmp�ײ�
	TCP_Header				*tcph;			// tcp�ײ�
	UDP_Header				*udph;			// udp�ײ�
	DNS_Header				*dnsh;			// dns�ײ�
	DHCP_Header				*dhcph;			// dhcp�ײ�
	u_char					*httpmsg;		// http����

	u_char					*pkt_data;		// ���ݰ���֡��
	struct pcap_pkthdr		*header;		// �������ݰ����ȣ����ݰ����ȣ����ݰ�����ʱ��
	CString					protocol;		// Э��

	Packet();
	Packet(const Packet &p);
	Packet(const u_char *pkt_data, const struct pcap_pkthdr *header);
	Packet& operator=(const Packet	&p);
	~Packet();

	bool isEmpty() const;

	int decodeEthernet();
	int decodeIP(u_char *L2payload);
	int decodeARP(u_char *L2payload);
	int decodeICMP(u_char *L3payload);
	int decodeTCP(u_char *L3payload);
	int decodeUDP(u_char *L3payload);
	int decodeDNS(u_char *L4payload);
	int decodeDHCP(u_char *L4payload);
	int decodeHTTP(u_char *L4payload);

	int getL4PayloadLength() const;
};