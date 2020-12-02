#include "pch.h"
#include "CClientSocket.h"
#include "MFC_Client.h"
#include "MFC_ClientDlg.h"


CClientSocket::CClientSocket(CMFCClientDlg* dlg)
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
	// TODO: �ڴ����ר�ô����/����û���
	CString msg;
	msg.Format(_T("������(%s:%d): �������ر�!"), m_ip, m_port);
	m_dlg->AddMsg(msg);
	m_dlg->MyEnableBtn();

	this->Close();
	CSocket::OnClose(nErrorCode);
}

//�ͻ��˽������Է���������Ϣ
void CClientSocket::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	char recvBuf[512] = { 0 };
	int recvLen = this->Receive(recvBuf, sizeof(recvBuf));
	CString msg;
	//SYSTEMTIME t;
	//GetLocalTime(&t);
	msg.Format(_T("������(%s:%d): %s"), m_ip, m_port, CString(recvBuf));
	//msg.Format(_T("������: %s"),CString(recvBuf));
	m_dlg->AddMsg(msg);

	CSocket::OnReceive(nErrorCode);
}

//�ͻ������ӷ�����
bool CClientSocket::Connect(LPCTSTR lpszHostAddress, UINT nHostPort)
{
	// TODO: �ڴ˴����ʵ�ִ���.
	m_ip = lpszHostAddress;
	m_port = nHostPort;
	return CAsyncSocket::Connect(lpszHostAddress, nHostPort);
}

