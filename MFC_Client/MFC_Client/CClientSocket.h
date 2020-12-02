#pragma once
#include <afxsock.h>
class CMFCClientDlg;
class CClientSocket :
    public CSocket //�̳�CSocket��
{
public:
    CClientSocket(CMFCClientDlg* dlg = NULL); //���캯��
    virtual~CClientSocket();                //��������
    virtual void OnClose(int nErrorCode);     //�������رն��رտͻ��� 
    virtual void OnReceive(int nErrorCode);   //�������Է���������Ϣ
    bool Connect(LPCTSTR lpszHostAddress, UINT nHostPort);//���ӷ�����
private:
    UINT m_port;
    CString m_ip;
    CMFCClientDlg* m_dlg;
};

