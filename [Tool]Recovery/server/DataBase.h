// DataBase.h: interface for the CDataBase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATABASE_H__D0B26A3A_97A2_4DBE_A14F_4C60C09FD809__INCLUDED_)
#define AFX_DATABASE_H__D0B26A3A_97A2_4DBE_A14F_4C60C09FD809__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <MemoryPoolTempl.h>
#include "..\[cc]ServerModule\DBThreadInterface.h"
#include <PtrList.h>
#include "..\..\[CC]ServerModule\CommonDBMsgParser.h"

enum eQueryType
{
	eQueryType_Update = 4,
	eQueryType_Insert = 2,
	eQueryType_Delete = 3,
	eQueryType_ExecuteIUD = 1,
	eQueryType_Bind = 7,
	eQueryType_ResultSet = 9,
	eQueryType_Login = 5,
	eQueryType_SimpleLogin = 6,
	eQueryType_FreeQuery = 101,
	eQueryType_SingleQuery = 102,
	eQueryType_SingleQueryDA = 103,
	eQueryType_FreeLargeQuery = 104,
	eQueryType_FreeMiddleQuery = 105,
};

struct DBQUERY
{
	DWORD dwMessageID;
	DWORD dwID;
	BYTE dbcontype;
	BYTE QueryType;
	char strQuery[MAX_LENGTH_QUERY];
	void Copy(DBQUERY* pSrc)
	{
		dwMessageID = pSrc->dwMessageID;
		dwID		= pSrc->dwID;
		dbcontype	= pSrc->dbcontype;
		QueryType	= pSrc->QueryType;
//		strcpy(strQuery,pSrc->strQuery);
//		SafeStrCpy( strQuery,pSrc->strQery, MAX_LENGTH_QUERY );
		strncpy( strQuery, pSrc->strQuery, MAX_LENGTH_QUERY-1 );
		strQuery[MAX_LENGTH_QUERY-1] = 0;		
	}
	void SetQuery(BYTE dbcontype,BYTE QueryType,DWORD dwMessageID,char* strQuery,DWORD ID)
	{
		this->dwMessageID	= dwMessageID;
		this->dwID			= ID;
		this->dbcontype		= dbcontype;
		this->QueryType		= QueryType;
//		strcpy(this->strQuery,strQuery);
//		SafeStrCpy( this->strQuery, strQuery, MAX_LENGTH_QUERY );
		strncpy( this->strQuery, strQuery, MAX_LENGTH_QUERY-1 );
		this->strQuery[MAX_LENGTH_QUERY-1] = 0;		

	}
};
struct DBTH
{
	enum eDBCONTYPE
	{
		eDBCON_LOGIN,
		eDBCON_ADMIN,
		eDBCON_LOG,
	};
	DBTH()
	{
		m_pIDB = NULL;
	/// 071222 DB Thread 분리
	//	m_LoginDB = NULL;
	//	m_LogDB = NULL;
	/////////////////////////
	}
	IDBThread* m_pIDB;

	/// 071222 DB Thread 분리
	//LPDBCON    m_LoginDB; /// 로그인 디비에 접근...
	//LPDBCON    m_LogDB; /// 로그 디비에 접근
	/////////////////////////

	BOOL Init(DESC_DBTHREAD* pDesc,BOOL bUsingLoginDB);
	void Release();

	BOOL Query(DBQUERY* pQuery);
	void DeletePointer(LPDBMESSAGE pMessage,DWORD ret);
};

class CDataBase  
{
	CMemoryPoolTempl<DBQUERY>	m_QueryPool;
	cPtrList	m_QueryQueue;

	DWORD m_MaxDBThreadNum;
	DWORD m_SameTimeQueryPerThread;

	DBTH* m_pDB;
	
	/// 071222 DB Thread 분리
	DBTH* m_pLoginDB;
	DBTH* m_pLogDB;
	/////////////////////////

	friend void ReadDBResultMessage(int ThreadNum,DWORD ret, LPDBMESSAGE pMessage);

//	DBTH* GetCurDB();
	
	BOOL AddQueryQueue(DBQUERY* pQuery, BOOL bAddQueueWhenFull = TRUE, DWORD index = 0);

	//---KES DB Process Fix 071114
	int m_curDBNum;
	//----------------------------

	BOOL m_bInit;

public:

	DBTH* GetCurDB(DWORD index = 0);
	void ProcessingDBMessage();
	BOOL AllCleared();
	
	CDataBase();
	virtual ~CDataBase();

	BOOL Init(DWORD MaxDBThread,DWORD MaxSameTimeQuery,BOOL bUsingLoginDB);
	void Release();

	typedef DWORD QueryIndex;
	BOOL LogQuery(DBMsgFunc, QueryIndex, LPCTSTR, ...);
	BOOL LogMiddleQuery(DBMiddleMsgFunc, QueryIndex, LPCTSTR, ...);
	BOOL LoginQuery(DBMsgFunc, QueryIndex, LPTSTR strQuery, ...);
	BOOL LoginMiddleQuery(DBMiddleMsgFunc, QueryIndex, LPCTSTR strQuery, ...);
	void FreeQuery(DBMsgFunc, QueryIndex, LPCTSTR, ...);
	BOOL FreeMiddleQuery(DBMiddleMsgFunc, QueryIndex, LPCTSTR, ...);
	BOOL FreeLargeQuery(DBLargeMsgFunc, QueryIndex, LPCTSTR, ...);
	
	void ProcessingQueue();
};

extern CDataBase g_DB;

#endif // !defined(AFX_DATABASE_H__D0B26A3A_97A2_4DBE_A14F_4C60C09FD809__INCLUDED_)
