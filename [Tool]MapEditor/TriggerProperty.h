#pragma once

class CTriggerProperty : public CDialog
{
	GXTRIGGER_PROPERTY*		m_pProperty;
// Construction
public:
	CTriggerProperty(CWnd* pParent = NULL);   // standard constructor
	void			SetTriggerProperty(GXTRIGGER_PROPERTY* pProperty) {m_pProperty = pProperty;}
// Dialog Data
	//{{AFX_DATA(CTriggerProperty)
	enum { IDD = IDD_DIALOG_TRIGGER_PROPERTY };
	DWORD	m_dwID;
	float	m_fX;
	float	m_fY;
	float	m_fZ;
	BYTE	m_bB;
	BYTE	m_bG;
	BYTE	m_bR;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTriggerProperty)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTriggerProperty)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonOk();
	afx_msg void OnButtonDelete();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};