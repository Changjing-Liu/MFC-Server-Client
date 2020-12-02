#include "pch.h"
#include "CClientSocket.h"
#include "MFC_Server.h"
#include "MFC_ServerDlg.h"
//��ʼ�������Ի���ָ��dlgָ��m_dlg
CClientSocket::CClientSocket(CMFCServerDlg* dlg)
{
	m_dlg = dlg;
}
//���������������ͷ��ڴ�
CClientSocket::~CClientSocket()
{
}
//�������ر�ʱ�رտͻ���
void CClientSocket::OnClose(int nErrorCode)
{
	CString msg;
	//�ӿͻ����б���ɾ��
	msg.Format(_T("�ͻ���(%s:%d): �ѹر�!"),m_ip, m_port);
	m_dlg->AddMsg(msg);
	CSocket::OnClose(nErrorCode);
	m_dlg->CloseClient(this);
}

//�������������Կͻ��˵���Ϣ
void CClientSocket::OnReceive(int nErrorCode)
{
	// �������ɿ�ܵ��ã�֪ͨ�׽��ֻ����������ݣ����Ե���Receive��Ա����ȡ��
	char recvBuf[512] = { 0 };
	int recvLen = this->Receive(recvBuf, sizeof(recvBuf));
	CString msg;
	SYSTEMTIME t;
	GetLocalTime(&t);
	msg.Format(_T("�ͻ���(%s:%d): %s"), m_ip, m_port,CString(recvBuf));
	m_dlg->AddMsg(msg);
	// ������Ϣ
	/*
	CharUpperA(recvBuf);
	this->Send(recvBuf, strlen(recvBuf));
	*/
}

//��������ͻ��˽������Ӻ������Ϣ
void CClientSocket::OnSend(int nErrorCode)
{
	// �������ɿ�ܵ��ã�֪ͨ�׽������ڿ��Ե���Send��Ա�������������ˡ�
	char buf[] = "���������ӳɹ�";
	Send(buf, strlen(buf)); //���ͻ��˷�����Ϣ

	CSocket::OnSend(nErrorCode);
}


void CClientSocket::SetClientAddr(CString ip, USHORT port)
{
	m_ip = ip;
	m_port = port;
}
