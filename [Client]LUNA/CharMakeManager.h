#ifndef _CHARACTERMAKE_MANAGER_
#define _CHARACTERMAKE_MANAGER_

#include "MHfile.h"

class cStatic;

enum CHAR_M
{
//	CE_JOB,
	CE_SEX, 
	CE_MHAIR, 
	CE_WMHAIR, 
	CE_MFACE, 
	CE_WMFACE, 
	CE_WEAR, 
	CE_BOOT, 
	CE_WEAPON,
	CE_AREA,
	CE_MAX
};

// 061215 LYW --- Add enum for new make list.
enum CHARMAKE_LIST
{
	CM_MFACE, 
	CM_MHAIR, 
	CM_WMFACE, 
	CM_WMHAIR,
	CM_EMFACE,
	CM_EMHAIR,
	CM_EWFACE,
	CM_EWHAIR,
	// 090604 ONS 신규종족 캐릭터속성 추가
	CM_DMFACE,
	CM_DMHAIR,
	CM_DWFACE,
	CM_DWHAIR,
	CM_MAX
} ;

enum{CM_PREV, CM_NEXT};

struct CM_OPTION
{
	char		strName[20];
	DWORD		dwData;
	DWORD		dwHelperData;
//	void*		pDescCombo;
	cStatic*	pDescStatic;
	VECTOR2		vTextPos;
};


#define CHARMAKEMGR 	USINGTON(cCharMakeManager)

enum ENUM_CM_CLASS;
class CPlayer;
class cStatic;

// 061215 LYW --- Include interface.
class CCharMakeNewDlg ;

class cCharMakeManager
{
protected:
	CPlayer*				m_pNewPlayer;					// 쨩천쨌횓쩔챤 횆쨀쨍짱횇횒
	CHARACTERMAKEINFO		m_CharMakeInfo;
	// 090529 LUJ, 직업에 따른 기본 아이템
	struct WearedItem
	{
		DWORD mWeaponIndex;
		DWORD mDressIndex;
	}
	mWearedItem;
	cPtrList				m_UserSelectOption[CM_MAX];		// 쨩챌쩔챘?횣째징 쩌짹횇횄째징쨈횋 쩔횋쩌횉 쨍챰쨌횕
	BOOL					m_bInit;
	CCharMakeNewDlg*		m_pCharMakeNewDlg ;
public:

	cCharMakeManager();
	virtual ~cCharMakeManager();

	void Init();	// 횄횎짹창횊짯
	void Release();

	void CreateNewCharacter(VECTOR3* pv3Pos);
	
	// 070523 LYW --- CharMakeManager : Modified function ReplaceCharMakeInfo.
	//BOOL ReplaceCharMakeInfo( int idx, WORD wValue );
	void ReplaceCharMakeInfo();
	void ComboBoxResetAll();
	void ListBoxResetAll();

	//SW050812
	// 070523 LYW --- CharMakeManager : Delete function that is not use.
	//void RotateSelection( int idx, int Dir );

	CPlayer* GetNewPlayer() { return m_pNewPlayer; }

	CHARACTERMAKEINFO* GetCharacterMakeInfo() { return &m_CharMakeInfo; }
	DWORD GetWeaponIndex( ENUM_CM_CLASS ) const;
	DWORD GetDressIndex( ENUM_CM_CLASS ) const;
	CCharMakeNewDlg* GetCharMakeNewDlg() { return m_pCharMakeNewDlg ; }

	// 061214 LYW ---- Add function to load option list.
	void LoadOptionList() ;
	// 061214 LYW ---- End add.

	// 061215 LYW --- Add fucntion to setting selection value.
	void SetOptionList( int curStatic, int curIdx ) ;

	// desc_hseos_성별선택01
	// S 성별선택 추가 added by hseos 2007.06.16
	void SetCharSexKindFromDB(BYTE nSexKind)	{ m_CharMakeInfo.SexType = nSexKind; }
	// E 성별선택 추가 added by hseos 2007.06.16

	cPtrList* GetOptionList(int idx) ;

};
EXTERNGLOBALTON(cCharMakeManager)
#endif // _CHARACTERMAKE_MANAGER_
