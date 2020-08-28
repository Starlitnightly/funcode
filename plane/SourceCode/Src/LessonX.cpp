/////////////////////////////////////////////////////////////////////////////////
//
//
//
//
/////////////////////////////////////////////////////////////////////////////////
#include <Stdio.h>
#include "CommonClass.h"
#include "LessonX.h"
#include "CBullet.h"
#include "CSpriteList.h"
////////////////////////////////////////////////////////////////////////////////
//
//
CGameMain		g_GameMain;	

//==============================================================================
//
// ����ĳ�������Ϊ��GameMainLoop����Ϊ��ѭ��������������ÿ֡ˢ����Ļͼ��֮�󣬶��ᱻ����һ�Ρ�

//==============================================================================
//
// ���캯��
CGameMain::CGameMain()
{
	m_iGameState			=	0;


	m_pBeginSprite = new CSprite("GameBegin");
	m_pCurScoreText = new CTextSprite("CurScoreText");
	m_pMaxScoreText = new CTextSprite("MaxScoreText");
	m_pMyFighter = NULL;



}
//==============================================================================
//
// ��������
CGameMain::~CGameMain()
{
}

//==============================================================================
//
// ��Ϸ��ѭ�����˺���������ͣ�ĵ��ã�����ÿˢ��һ����Ļ���˺�����������һ��
// ���Դ�����Ϸ�Ŀ�ʼ�������С������ȸ���״̬. 
// ��������fDeltaTime : �ϴε��ñ��������˴ε��ñ�������ʱ��������λ����
void CGameMain::GameMainLoop( float	fDeltaTime )
{
	switch( GetGameState() )
	{
		// ��ʼ����Ϸ�������һ���������
	case 1:
		{
			GameInit();
			SetGameState(2); // ��ʼ��֮�󣬽���Ϸ״̬����Ϊ������
		}
		break;

		// ��Ϸ�����У����������Ϸ�߼�
	case 2:
		{
			// TODO �޸Ĵ˴���Ϸѭ�������������ȷ��Ϸ�߼�
			if(!IsGameLost())
			{
				GameRun( fDeltaTime );
			}
			else // ��Ϸ������������Ϸ���㺯����������Ϸ״̬�޸�Ϊ����״̬
			{				
				GameEnd();
				SetGameState(0);
				
			}
		}
		break;

		// ��Ϸ����/�ȴ����ո����ʼ
	case 0:
	default:
		break;
	};
}
//=============================================================================
//
// ÿ�ֿ�ʼǰ���г�ʼ���������һ���������
void CGameMain::GameInit()
{
	m_pBeginSprite->SetSpriteVisible(false);

	if (NULL == m_pMyFighter)
	{
		m_pMyFighter = new CMyFighter("ControlSprite");
		m_pMyFighter->SetSpriteWorldLimit(WORLD_LIMIT_STICKY, CSystem::GetScreenLeft() - 10.f, CSystem::GetScreenTop(), CSystem::GetScreenRight(), CSystem::GetScreenBottom());
	}
	m_pMyFighter->SetHp(500);
	m_pMyFighter->SetScore(0);
	m_pMyFighter->SetSpriteVisible(true);
	m_pCurScoreText->SetTextValue(m_pMyFighter->GetScore());
	m_pMaxScoreText->SetTextValue(0);
	m_iCreatedBulletCount = 0;

	


}
//=============================================================================
//
// ÿ����Ϸ������
void CGameMain::GameRun( float fDeltaTime )
{
	// ִ���ҷ�ս����ѭ������
	if (m_pMyFighter)
		m_pMyFighter->OnFire(fDeltaTime);
	CEnemyFighter::createEnemyFighter(fDeltaTime);

	int	iListSize = m_SpriteList.GetListSize();
	for (int iLoop = 0; iLoop < iListSize; iLoop++)
	{
		CSprite * pSprite = m_SpriteList.GetSprite(iLoop);
		if (pSprite != NULL && (strstr(pSprite->GetName(), "HorizontalSprite") != NULL))
		{
			((CEnemyFighter *)pSprite)->OnFire(fDeltaTime);
		}
	}
	m_pCurScoreText->SetTextValue(m_pMyFighter->GetScore());


}
//=============================================================================
//
// ������Ϸ����
void CGameMain::GameEnd()
{
	m_pBeginSprite->SetSpriteVisible(true);
	m_SpriteList.DeleteAllSprite(true);
	m_pMyFighter->SetSpriteVisible(false);
	delete m_pMyFighter;
	m_pMyFighter = NULL;

}
//==========================================================================
//
// ����ƶ�
// ���� fMouseX, fMouseY��Ϊ��굱ǰ����
void CGameMain::OnMouseMove( const float fMouseX, const float fMouseY )
{
	
}
//==========================================================================
//
// �����
// ���� iMouseType����갴��ֵ���� enum MouseTypes ����
// ���� fMouseX, fMouseY��Ϊ��굱ǰ����
void CGameMain::OnMouseClick( const int iMouseType, const float fMouseX, const float fMouseY )
{
	
}
//==========================================================================
//
// ��굯��
// ���� iMouseType����갴��ֵ���� enum MouseTypes ����
// ���� fMouseX, fMouseY��Ϊ��굱ǰ����
void CGameMain::OnMouseUp( const int iMouseType, const float fMouseX, const float fMouseY )
{

	
}
//==========================================================================
//
// ���̰���
// ���� iKey�������µļ���ֵ�� enum KeyCodes �궨��
// ���� iAltPress, iShiftPress��iCtrlPress�������ϵĹ��ܼ�Alt��Ctrl��Shift��ǰ�Ƿ�Ҳ���ڰ���״̬(0δ���£�1����)
void CGameMain::OnKeyDown( const int iKey, const bool bAltPress, const bool bShiftPress, const bool bCtrlPress )
{	
	// ���¿ո���Ϸ��ʼ
	if (KEY_SPACE == iKey && 0 == GetGameState())
	{
		SetGameState(1);
	}

	if (2 == GetGameState()) //����Ϸ״̬Ϊ2ʱ
	{
		m_pMyFighter->OnMove(true, iKey);
	}
	// ��Ϸ�����У����¿ո����ӵ�
	if (2 == GetGameState() && KEY_SPACE == iKey && NULL != m_pMyFighter)
		m_pMyFighter->SetCanFire(true);



}
//==========================================================================
//
// ���̵���
// ���� iKey������ļ���ֵ�� enum KeyCodes �궨��
void CGameMain::OnKeyUp( const int iKey )
{
	if (2 == GetGameState())
	{
		m_pMyFighter->OnMove(false, iKey);
	}
	if (2 == GetGameState() && KEY_SPACE == iKey && NULL != m_pMyFighter)
		m_pMyFighter->SetCanFire(false);

}
//===========================================================================
//
// �����뾫����ײ
// ���� szSrcName��������ײ�ľ�������
// ���� szTarName������ײ�ľ�������
void CGameMain::OnSpriteColSprite( const char *szSrcName, const char *szTarName )
{
	if (2 != GetGameState())
		return;

	CWeapon	*pSrcSprite = IsMyFighter(szSrcName) ? m_pMyFighter : GetSprite(szSrcName);
	CWeapon *pTarSprite = IsMyFighter(szTarName) ? m_pMyFighter : GetSprite(szTarName);

	if (NULL == pSrcSprite || NULL == pTarSprite)
		return;

	pSrcSprite->OnColOtherSprite(pTarSprite);
	pTarSprite->OnColOtherSprite(pSrcSprite);

	if (!pSrcSprite->IsMyFighter())
	{
		if (pSrcSprite->IsDead())
			g_GameMain.DeleteSprite(szSrcName, true);
	}
	if (!pTarSprite->IsMyFighter())
	{
		if (pTarSprite->IsDead())
			g_GameMain.DeleteSprite(szTarName, true);
	}

	
}
//===========================================================================
//
// ����������߽���ײ
// ���� szName����ײ���߽�ľ�������
// ���� iColSide����ײ���ı߽� 0 ��ߣ�1 �ұߣ�2 �ϱߣ�3 �±�
void CGameMain::OnSpriteColWorldLimit( const char *szName, const int iColSide )
{
	
}

void CGameMain::CreateBullet(int iType,const float fPosX, const float fPosY)
{
	char	szName[MAX_NAME_LEN];// MAX_NAME_LEΪCommonClass.h�к궨�� ֵΪ128
	sprintf(szName, "Bullet1_%d", m_iCreatedBulletCount);
	m_iCreatedBulletCount++;
	CBullet *pBullet = new CBullet(iType, szName);
	pBullet->CloneSprite("Bullet1_Template");
	pBullet->SetSpritePosition(fPosX, fPosY);
	if (1 == iType) //���iTypeֵΪ1����˵���ӵ�Ϊ�з�ս�����䡣
	{
		pBullet->SetSpriteLinearVelocityX(-30);
	}
	else//�������˵��Ϊ�ҷ�ս������
	{
		pBullet->SetSpriteFlipX(true);
		pBullet->SetSpriteLinearVelocityX(60);
	}

	pBullet->SetSpriteWorldLimit(WORLD_LIMIT_NULL, CSystem::GetScreenLeft() - 10.f, CSystem::GetScreenTop(), CSystem::GetScreenRight() + 200.f, CSystem::GetScreenBottom());
	pBullet->SetSpriteCollisionActive(true, true);
	pBullet->SetDamage(100);
	pBullet->SetHp(10);

	AddSprite(pBullet);
}

void CGameMain::AddSprite(CWeapon  *pSprite)
{
	m_SpriteList.AddSprite(pSprite);
}

CWeapon *CGameMain::GetSprite(const int iIndex)
{
	return m_SpriteList.GetSprite(iIndex);
}

CWeapon *CGameMain::GetSprite(const char *szName)
{
	return m_SpriteList.GetSprite(szName);
}
//��װɾ������
void	CGameMain::DeleteSprite(const char *szName, bool bDeleteImage)
{
	m_SpriteList.DeleteSprite(szName, bDeleteImage);
}

bool CGameMain::IsMyFighter(const char *szName)
{
	return (strcmp(m_pMyFighter->GetName(), szName) == 0);
}

CMyFighter * CGameMain::GetMyFighter()
{
	return m_pMyFighter;
}

bool CGameMain::IsGameLost()
{
	return (m_pMyFighter ? m_pMyFighter->IsDead() : false);
}




