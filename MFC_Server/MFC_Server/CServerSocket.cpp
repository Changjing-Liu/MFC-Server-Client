#include "pch.h"
#include "CServerSocket.h"
//#include "CClientSocket.h"
#include "MFC_Server.h"
#include "MFC_ServerDlg.h"

//��ʼ�������Ի���ָ��dlgָ��m_dlg
CServerSocket::CServerSocket(CMFCServerDlg* dlg)
{
	//��ʼ��ʱ���ù��캯��
	m_dlg = dlg;
}
//���������������ͷ��ڴ�
CServerSocket::~CServerSocket()
{
	
}
//���������ܿͻ��˵�����
void CServerSocket::OnAccept(int nErrorCode)
{
	// �ɿ�ܵ��ã�֪ͨ�����׽������ڿ��Ե���Accept��Ա�������������ҵģ�pending����������
	CClientSocket* client = new CClientSocket(m_dlg); 
	// �½�CClientSocket���󣬹��캯�����ӶԻ���
	SOCKADDR_IN addr;
	memset(&addr, 0, sizeof(addr));
	int addrLen = sizeof(addr);

	// ��ȡͨ���׽���
	Accept(*client, (SOCKADDR*)&addr, &addrLen);
	char* ip = inet_ntoa(addr.sin_addr);
	client->SetClientAddr(CString(ip), addr.sin_port);
	//�����б�
	m_clientList.push_back(client);
	CString msg;
	//msg.Format(_T("�ͻ���(%d): ����"), m_clientList.size());
	//m_dlg->AddMsg(msg);
	// �������������Ϣ
	//CString msg;
	//SYSTEMTIME t;
	//GetLocalTime(&t);
	msg.Format(_T("�ͻ���(%s:%d): ���ӳɹ�!"),CString(ip), addr.sin_port);
	m_dlg->AddMsg(msg);

	//���֮ǰ��combo
	m_dlg->CleanCombo();
	//����combo
	UpdateCombo();
	//������������
	m_dlg->AddCount(m_clientList.size());

	CSocket::OnAccept(nErrorCode);
}
//ĳһ�ͻ��˹رպ�����������е���ص���Ϣ
void CServerSocket::CloseSpecialClient(CClientSocket*  pointer) {
	//USHORT m_port1
	CString msg;
	//msg.Format(_T("�������յ�ɾ������"));
	//m_dlg->AddMsg(msg);
	list<CClientSocket*>::iterator it = m_clientList.begin();
	//����Ѱ�Ҷ�Ӧָ�������
	for (; it != m_clientList.end();it++ )
	{
		//(*it).m_port == m_port1
		if (*it==pointer) {
			CString msg;
			//msg.Format(_T("���ҵ��˺ٺ�"));
			//m_dlg->AddMsg(msg);
			(*it)->Close();
			delete (*it);
			it = m_clientList.erase(it); //ɾ��
			break;
		}
	}
	//���֮ǰ��combo
	m_dlg->CleanCombo();
	//����combo
	UpdateCombo();
	//������������
	m_dlg->AddCount(m_clientList.size());
}
//�������رգ�ʹ�������ӶϿ�
void CServerSocket::CloseAllClient()
{
	// �رռ����׽��֣��ȹر����ӵ��׽���
	list<CClientSocket*>::iterator it = m_clientList.begin();
	//�������
	for (; it != m_clientList.end(); )
	{
		
		(*it)->Close();
		delete (*it);
		it = m_clientList.erase(it);
	}

	//���֮ǰ��combo
	m_dlg->CleanCombo();
	//����combo
	UpdateCombo();

	//������������
	m_dlg->AddCount(m_clientList.size());
	this->Close();
}
/*
//ĳһ�ͻ��˹رգ�����������е�socket
void CServerSocket::OnClose(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	CString msg;
	msg.Format(_T("�ͻ���: ������ѹر�!"));
	m_dlg->AddMsg(msg);
	m_dlg->AddCount(m_clientList.size());
	CSocket::OnClose(nErrorCode);
}
*/
//��������ʽ�����Ϣ
void CServerSocket::UpdateCombo()
{
	//���cmobo֮ǰ����Ϣ
	//m_dlg->CleanCombo();
	//m_dlg->m_combo.ResetContent();
	list<CClientSocket*>::iterator it = m_clientList.begin();
	for (; it != m_clientList.end(); it++)
	{
		//���ͻ�����Ϣ��ӵ�combo
		m_dlg->AddClientAddrs(*it);
	}
	
}
//��������ָ���ͻ��˷�����Ϣ
bool CServerSocket::SendMsg(CString str,char* send)
{
	list<CClientSocket*>::iterator it = m_clientList.begin();
	for (; it != m_clientList.end(); it++)
	{
		CString msg;
		msg.Format(_T("%s:%d"), (*it)->m_ip, (*it)->m_port);
		if (msg == str) {
			(*it)->Send(send,strlen(send));
			return 1;
		}
	}
	m_dlg->MessageBox(_T("�Ҳ����ͻ��ˣ�����ʧ�ܣ�"));
	return 0;
}

