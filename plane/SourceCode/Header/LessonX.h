/////////////////////////////////////////////////////////////////////////////////
//
//
//
//
/////////////////////////////////////////////////////////////////////////////////
#ifndef _LESSON_X_H_
#define _LESSON_X_H_
//
#include <Windows.h>
#include "CMyFighter.h"
#include "CBullet.h"
#include "CEnemyFighter.h"
#include "CSpriteList.h"

/////////////////////////////////////////////////////////////////////////////////
//
// ��Ϸ�ܹ��ࡣ��������Ϸ��ѭ������Ϸ��ʼ���������ȹ���
class	CGameMain
{
private:
	int				m_iGameState;				// ��Ϸ״̬��0���������ߵȴ���ʼ��1����ʼ����2����Ϸ������

public:
	CGameMain();            //���캯��
	~CGameMain();           //��������  

	// Get����
	int				GetGameState()											{ return m_iGameState; }
	
	// Set����
	void			SetGameState( const int iState )				{ m_iGameState	=	iState; }
	
	// ��Ϸ��ѭ����
	void			GameMainLoop( float	fDeltaTime );
	void			GameInit();
	void			GameRun( float fDeltaTime );
	void			GameEnd();
	void 			OnMouseMove( const float fMouseX, const float fMouseY );
	void 			OnMouseClick( const int iMouseType, const float fMouseX, const float fMouseY );
	void 			OnMouseUp( const int iMouseType, const float fMouseX, const float fMouseY );
	void 			OnKeyDown( const int iKey, const bool bAltPress, const bool bShiftPress, const bool bCtrlPress );
	void 			OnKeyUp( const int iKey );
	void 			OnSpriteColSprite( const char *szSrcName, const char *szTarName );
	void 			OnSpriteColWorldLimit( const char *szName, const int iColSide );

	CSprite*		m_pBeginSprite; //GameBeginΪ���ո�ʼ������
	CTextSprite*	m_pCurScoreText;//��ʾ��ǰ����
	CTextSprite*	m_pMaxScoreText;// ��ʾ��߷�
	CMyFighter*		 m_pMyFighter;
	int m_iCreatedBulletCount;
	void CreateBullet(int iType, const float fPosX, const float fPosY);
	CSpriteList m_SpriteList;
	void AddSprite(CWeapon  *pSprite);
	CWeapon *GetSprite(const int iIndex);
	CWeapon *GetSprite(const char *szName);
	void DeleteSprite(const char *szName, bool bDeleteImage);

	bool IsMyFighter(const char *szName);
	CMyFighter * GetMyFighter();

	bool IsGameLost();

	

};

/////////////////////////////////////////////////////////////////////////////////
// 
extern CGameMain	g_GameMain;

#endif // _LESSON_X_H_