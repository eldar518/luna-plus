#pragma once

class CDialogDirectionalLightProperty : public CDialog
{
	DIRECTIONAL_LIGHT_DESC*		m_pLightDesc;

// Construction
public:
	void			SetLightDescPtr(DIRECTIONAL_LIGHT_DESC* pLightDesc) {	m_pLightDesc = pLightDesc; }
	CDialogDirectionalLightProperty(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogDirectionalLightProperty)
	enum { IDD = IDD_DIALOG_DIRECTIONAL_LIGHT };
	BYTE	m_bAmbientB;
	BYTE	m_bAmbientG;
	BYTE	m_bAmbientR;
	BYTE	m_bDiffuseB;
	BYTE	m_bDiffuseG;
	BYTE	m_bDiffuseR;
	BYTE	m_bSpecularB;
	BYTE	m_bSpecularG;
	BYTE	m_bSpecularR;
	float	m_fDirZ;
	float	m_fDirY;
	float	m_fDirX;
	BOOL	m_bEnableLight;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogDirectionalLightProperty)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogDirectionalLightProperty)
	afx_msg void OnButtonOk();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};