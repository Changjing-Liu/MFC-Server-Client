#pragma once
//#include <afxsock.h>
#include"CClientSocket.h"

#include<list>
using namespace std;
// CServerSocket ����Ŀ��
class CMFCServerDlg;
class CServerSocket :
    public CSocket
{
public:
    CServerSocket(CMFCServerDlg* dlg = NULL); // ���캯��
    virtual ~CServerSocket();
    //���ܵ��ͻ������ӵ� �ص�����
    virtual void OnAccept(int nErrorCode);
    //�ر���������Client��socket
    void CloseAllClient();
    void CloseSpecialClient(CClientSocket* pointer);
    void UpdateCombo();
    bool SendMsg(CString str, char* send);
    //virtual void OnClose(int nErrorCode);
private:
    CMFCServerDlg* m_dlg;
    list<CClientSocket*> m_clientList;
    //�ͻ����б�
};

