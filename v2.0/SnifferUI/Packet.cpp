#include "stdafx.h"
#include "Packet.h"
#include "pcap.h"
Packet::Packet()
{
	ethh = NULL;
	iph = NULL;
	arph = NULL;
	icmph = NULL;
	udph = NULL;
	tcph = NULL;
	dnsh = NULL;
	dhcph = NULL;
	httpmsg = NULL;

	pkt_data = NULL;
	header = NULL;
}

Packet::Packet(const Packet &p)
{
	ethh = NULL;
	iph = NULL;
	arph = NULL;
	icmph = NULL;
	udph = NULL;
	tcph = NULL;
	dnsh = NULL;
	dhcph = NULL;
	httpmsg = NULL;

	if (!p.isEmpty())
	{
		u_int caplen = p.header->caplen;

		pkt_data = (u_char*)malloc( caplen );
		memcpy(pkt_data, p.pkt_data, caplen);

		header = (struct pcap_pkthdr *)malloc(sizeof( *(p.header) ));
		memcpy(header, p.header, sizeof(*(p.header)));

		if (decodeEthernet() == -1)
		{
			AfxMessageBox("decodeEthernetʧ��");
			return;
		}
	}
	else
	{
		pkt_data = NULL;
		header = NULL;
	}
}

Packet::Packet(const u_char *pkt_data, const struct pcap_pkthdr *header)
{
	ethh = NULL;
	iph = NULL;
	arph = NULL;
	icmph = NULL;
	udph = NULL;
	tcph = NULL;
	dnsh = NULL;
	dhcph = NULL;
	httpmsg = NULL;

	if (pkt_data != NULL && header != NULL)
	{
		this->pkt_data = (u_char*)malloc(header->caplen);
		memcpy(this->pkt_data, pkt_data, header->caplen);

		this->header = (struct pcap_pkthdr *)malloc(sizeof(*header));
		memcpy(this->header, header, sizeof(*header));

		if (decodeEthernet() == -1)
		{
			AfxMessageBox("decodeEthernetʧ��");
			return;
		}
	}
	else
	{
		this->pkt_data = NULL;
		this->header = NULL;
	}
}

Packet & Packet::operator=(const Packet & p)
{
	ethh = NULL;
	iph = NULL;
	arph = NULL;
	icmph = NULL;
	udph = NULL;
	tcph = NULL;
	dnsh = NULL;
	dhcph = NULL;
	httpmsg = NULL;

	if (!p.isEmpty())
	{
		u_int caplen = p.header->caplen;

		if (pkt_data == NULL)
		{
			pkt_data = (u_char*)malloc(caplen);
		}
		memcpy(pkt_data, p.pkt_data, caplen);

		if (header == NULL)
		{
			header = (struct pcap_pkthdr *)malloc(sizeof(*(p.header)));
		}
		memcpy(header, p.header, sizeof(*(p.header)));

		if (decodeEthernet() == -1)
		{
			AfxMessageBox("decodeEthernetʧ��");
			return *this;
		}
	}
	else
	{
		pkt_data = NULL;
		header = NULL;
	}
	return *this;
}

Packet::~Packet()
{
	ethh = NULL;
	iph = NULL;
	arph = NULL;
	icmph = NULL;
	udph = NULL;
	tcph = NULL;
	dnsh = NULL;
	dhcph = NULL;
	httpmsg = NULL;

	free(pkt_data);
	pkt_data = NULL;

	free(header);
	header = NULL;
	protocol.Empty();
}

/**
*	@brief	�ж����ݰ��Ƿ�Ϊ��
*	@param	-
*	@return true pkt_data��headerΪ��	false pkt_data��header������
*/
bool Packet::isEmpty() const
{
	if (pkt_data == NULL || header == NULL)
	{
		return true;
	}
	return false;
}

/**
*	@brief	����Ethernet֡���ó�Ա����ethh���棬����eth_typeֵ������һ��������
*	@param	-
*	@return	0 ��ʾ�����ɹ�	-1 ��ʾ����ʧ��
*/
int Packet::decodeEthernet()
{
	if (isEmpty())
	{
		return -1;
	}

	protocol = "Ethernet";
	ethh = (Ethernet_Header*)pkt_data;
	
	switch (ntohs(ethh->eth_type))
	{
		case ETHERNET_TYPE_IP:
			decodeIP(pkt_data + ETHERNET_HEADER_LENGTH);
			break;
		case ETHERNET_TYPE_ARP:
			decodeARP(pkt_data + ETHERNET_HEADER_LENGTH);
			break;
		default:
			break;
	}
	return 0;
}

/**
*	@brief	����IP���ݰ��ײ����ó�Ա����iph���棬����protocolֵ������һ��������
*	@param	L2payload	ָ��IP���ݰ���ָ��
*	@return	0 ��ʾ�����ɹ�	-1 ��ʾ����ʧ��
*/
int Packet::decodeIP(u_char * L2payload)
{
	if (L2payload == NULL)
	{
		return -1;
	}

	protocol = "IPv4";
	iph = (IP_Header*)(L2payload);
	u_short ip_header_len = (iph->ver_headerlen & 0x0f) * 4;
	switch (iph->protocol)
	{
		case PROTOCOL_ICMP:		
			decodeICMP(L2payload + ip_header_len);
			break;	

		case PROTOCOL_TCP:		
			decodeTCP(L2payload + ip_header_len);
			break;	

		case PROTOCOL_UDP:
			decodeUDP(L2payload + ip_header_len);
			break;	

		default:
			break;
	}
	return 0;
}

/**
*	@brief	����ARP�����ײ����ó�Ա����arph����
*	@param	L2payload	ָ��ARP���ĵ�ָ��
*	@return	0 ��ʾ�����ɹ�	-1 ��ʾ����ʧ��
*/
int Packet::decodeARP(u_char * L2payload)
{
	if (L2payload == NULL)
	{
		return -1;
	}
	protocol = "ARP";
	arph = (ARP_Header*)(L2payload);

	return 0;
}

/**
*	@brief	����ICMP�����ײ����ó�Ա����icmph����
*	@param	L2payload	ָ��ICMP���ĵ�ָ��
*	@return	0 ��ʾ�����ɹ�	-1 ��ʾ����ʧ��
*/
int Packet::decodeICMP(u_char * L3payload)
{
	if (L3payload == NULL)
	{
		return -1;
	}

	protocol = "ICMP";
	icmph = (ICMP_Header*)(L3payload);
	return 0;
}

/**
*	@brief	����TCP���Ķ��ײ����ó�Ա����tcph���棬����ԴĿ�˿�ѡ����һ��������
*	@param	L3payload	ָ��TCP���Ķε�ָ��
*	@return	0 ��ʾ�����ɹ�	-1 ��ʾ����ʧ��
*/
int Packet::decodeTCP(u_char * L3payload)
{
	if (L3payload == NULL)
	{
		return -1;
	}

	protocol = "TCP";
	tcph = (TCP_Header*)(L3payload);

	u_short tcp_header_len = (ntohs(tcph->headerlen_rsv_flags) >> 12) * 4;
	if (ntohs(tcph->srcport) == PORT_DNS || ntohs(tcph->dstport) == PORT_DNS)
	{
		decodeDNS(L3payload + tcp_header_len);
	}
	else if (ntohs(tcph->srcport) == PORT_HTTP || ntohs(tcph->dstport) == PORT_HTTP)
	{
		decodeHTTP(L3payload + tcp_header_len);
	}
	return 0;
}

/**
*	@brief	����UDP�û����ݱ��ײ����ó�Ա����udph���棬����ԴĿ�˿�ѡ����һ��������
*	@param	L2payload	ָ��UDP�û����ݱ���ָ��
*	@return	0 ��ʾ�����ɹ�	-1 ��ʾ����ʧ��
*/
int Packet::decodeUDP(u_char *L3payload)
{
	if (L3payload == NULL)
	{
		return -1;
	}

	protocol = "UDP";
	udph = (UDP_Header*)(L3payload);
	if (ntohs(udph->srcport) == PORT_DNS || ntohs(udph->dstport) == PORT_DNS)
	{
		decodeDNS(L3payload + UDP_HEADER_LENGTH);

	}
	else if ((ntohs(udph->srcport) == PORT_DHCP_CLIENT && ntohs(udph->dstport) == PORT_DHCP_SERVER) || (ntohs(udph->srcport) == PORT_DHCP_SERVER && ntohs(udph->dstport) == PORT_DHCP_CLIENT))
	{
		decodeDHCP(L3payload + UDP_HEADER_LENGTH);
	}
	return 0;
}

/**
*	@brief	����DNS�����ײ����ó�Ա����dnsh����
*	@param	L4payload	ָ��DNS���ĵ�ָ��
*	@return	0 ��ʾ�����ɹ�	-1 ��ʾ����ʧ��
*/
int Packet::decodeDNS(u_char * L4payload)
{
	if (L4payload == NULL)
	{
		return -1;
	}

	protocol = "DNS";
	dnsh = (DNS_Header*)(L4payload);
	return 0;
}

/**
*	@brief	����DHCP�����ײ����ó�Ա����dhcph����
*	@param	L4payload	ָ��DHCP���ĵ�ָ��
*	@return	0 ��ʾ�����ɹ�	-1 ��ʾ����ʧ��
*/
int Packet::decodeDHCP(u_char * L4payload)
{
	if (L4payload == NULL)
	{
		return -1;
	}

	protocol = "DHCP";
	dhcph = (DHCP_Header*)L4payload;
	return 0;
}

/**
*	@brief	����HTTP�����ײ����ó�Ա����httpmsg����
*	@param	L4payload	ָ��httpmsg���ĵ�ָ��
*	@return	0 ��ʾ�����ɹ�	-1 ��ʾ����ʧ��
*/
int Packet::decodeHTTP(u_char * L4payload)
{
	if (L4payload == NULL)
	{
		return -1;
	}

	protocol = "HTTP";
	httpmsg = L4payload;
	return 0;
}

