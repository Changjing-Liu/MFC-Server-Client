#pragma once
//#include <afxsock.h>
//#include "MFC_Server.h"
//#include "MFC_ServerDlg.h"
//#include "CClientSocket.h"

class CMFCServerDlg;

class CClientSocket :
    public CSocket
{
public:
    CClientSocket(CMFCServerDlg* dlg = NULL);
    virtual ~CClientSocket();
    virtual void OnClose(int nErrorCode);
    virtual void OnReceive(int nErrorCode);
    virtual void OnSend(int nErrorCode);
    //�������ӵ�Client��IP��port
    void SetClientAddr(CString ip, USHORT port);
    CString m_ip;
    USHORT m_port;
    
private:
    CMFCServerDlg* m_dlg;
    
    
};

