#pragma once
/* 
*	�������ڲ������ݰ����Ϊת���ļ�
*   �����Ƕ�Ĭ�ϱ����ת���ļ�������ָ��λ�� 
*/
class PacketDumper
{
private:
	CString		m_path;			// ת���ļ�Ĭ�ϴ洢·��

public:
	PacketDumper();
	~PacketDumper();

	void setPath(CString path);
	CString getPath();

	void dump(CString path);
	void copyFile(CFile *dest, CFile *src);
};

