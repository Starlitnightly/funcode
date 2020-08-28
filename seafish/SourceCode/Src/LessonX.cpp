/////////////////////////////////////////////////////////////////////////////////
//
//
//
//
/////////////////////////////////////////////////////////////////////////////////
#include <Stdio.h>
#include "CommonClass.h"
#include "LessonX.h"
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
	m_iGameState			=	1;
	yu_0 = new CSprite("yu_0");
	m_fScreenBottom = 0.f;
	m_fScreenLeft = 0.f;
	m_fScreenRight = 0.f;
	m_fScreenTop = 0.f;
	speed = 0;
	kongzhiyu=new CSprite("kongzhiyu");

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
			GameInit1();
			SetGameState(2); // ��ʼ��֮�󣬽���Ϸ״̬����Ϊ������
		}
		break;

		// ��Ϸ�����У����������Ϸ�߼�
	case 2:
		{
			// TODO �޸Ĵ˴���Ϸѭ�������������ȷ��Ϸ�߼�
			if( true )
			{
				GameRun( fDeltaTime );
			}
			else // ��Ϸ������������Ϸ���㺯����������Ϸ״̬�޸�Ϊ����״̬
			{				
				SetGameState(0);
				GameEnd();
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
void CGameMain::GameInit1()
{
	yu_0->SetSpriteLinearVelocity(30, 30);
	// ��ȡ��Ļ�ı߽�ֵ
	m_fScreenLeft = CSystem::GetScreenLeft();
	m_fScreenRight = CSystem::GetScreenRight();
	m_fScreenTop = CSystem::GetScreenTop();
	m_fScreenBottom = CSystem::GetScreenBottom();

	// ���þ�������߽�
	yu_0->SetSpriteWorldLimit(WORLD_LIMIT_NULL, m_fScreenLeft, m_fScreenTop, m_fScreenRight, m_fScreenBottom);

	speed = 30;
	yu_0->SetSpriteLinearVelocity(speed, 0);

	// ���ɶ����㾫��
	for (int i = 0; i < 4; i++)
	{
		char  szName[128];
		float fPosX, fPosY;
		float fSpeedX;
		//��szName��ֵ��Ϊ��fish����I,��ѭ������
		sprintf(szName, "fish%d", i);//fish0,fish1,fish2,fish3
		CSprite* tmpSprite = new CSprite(szName);
		tmpSprite->CloneSprite("kongzhiyu");//��������

		fPosX = CSystem::RandomRange(m_fScreenLeft + 10.f, m_fScreenRight - 10.f);
		fPosY = CSystem::RandomRange(m_fScreenTop + 10.f, m_fScreenBottom - 10.f);
		tmpSprite->SetSpritePosition(fPosX, fPosY);
		tmpSprite->SetSpriteWorldLimit(WORLD_LIMIT_NULL, m_fScreenLeft - 20.f, m_fScreenTop, m_fScreenRight + 20.f, m_fScreenBottom);
		
		fSpeedX = CSystem::RandomRange(10, 20);
		tmpSprite->SetSpriteLinearVelocity(fSpeedX, 0);
		m_vFish.push_back(tmpSprite);

	}





}
//=============================================================================
//
// ÿ����Ϸ������
void CGameMain::GameRun( float fDeltaTime )
{
}
//=============================================================================
//
// ������Ϸ����
void CGameMain::GameEnd()
{
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
	float	fSpeedX = 0.f, fSpeedY = 0.f;
	switch (iKey)
	{
	case KEY_W:
		fSpeedY = -10.f; //���ϵ�ʱ��Y�����ٶ�Ϊ����
		break;
	case KEY_A:
		fSpeedX = -15.f;	//�����ʱ��X������ٶ�Ϊ��ֵ
		break;
	case KEY_S:
		fSpeedY = 10.f; //���µ�ʱ��Y������ٶ�Ϊ��ֵ
		break;
	case KEY_D:
		fSpeedX = 15.f;//���ҵ�ʱ��X������ٶ�Ϊ��ֵ
		break;
	}
	kongzhiyu->SetSpriteLinearVelocity(fSpeedX, fSpeedY);

	if (iKey == KEY_F && bCtrlPress == true) {
		yu_0->SetSpriteVisible(false);
	}

}
//==========================================================================
//
// ���̵���
// ���� iKey������ļ���ֵ�� enum KeyCodes �궨��
void CGameMain::OnKeyUp( const int iKey )
{
	float	fSpeedX=0.f, fSpeedY=0.f;
	switch (iKey)
	{
	case KEY_W:
	case KEY_A:
	case KEY_S:
	case KEY_D:
		fSpeedX = 0.f;
		fSpeedY = 0.f;
	}
	kongzhiyu->SetSpriteLinearVelocity(fSpeedX, fSpeedY);

}
//===========================================================================
//
// �����뾫����ײ
// ���� szSrcName��������ײ�ľ�������
// ���� szTarName������ײ�ľ�������
void CGameMain::OnSpriteColSprite( const char *szSrcName, const char *szTarName )
{
	
}
//===========================================================================
//
// ����������߽���ײ
// ���� szName����ײ���߽�ľ�������
// ���� iColSide����ײ���ı߽� 0 ��ߣ�1 �ұߣ�2 �ϱߣ�3 �±�
void CGameMain::OnSpriteColWorldLimit( const char *szName, const int iColSide )
{
	if (strcmp(szName, "yu_0") == 0)
	{
		bool panduan;
		if (speed > 0)
			panduan = true;
		else
			panduan = false;
		speed = 0 - speed;
		yu_0->SetSpriteLinearVelocity(speed, 0);
		
		
		yu_0->SetSpriteFlipX(panduan);
	}

	bool bFlip;
	float fSpeedX = 0.f, fSpeedY = 0.f;

	if (strstr(szName, "fish") != NULL)
	{
		if (iColSide == 1)  // �ұ�
		{
			bFlip = true;
			fSpeedX = -CSystem::RandomRange(10, 20);
		}
		else if (iColSide == 0)   // ���
		{
			bFlip = false;
			fSpeedX = CSystem::RandomRange(10, 20);
		}
		CSprite* tmpSprite = FindSpriteByName(szName);
		tmpSprite->SetSpriteFlipX(bFlip);
		tmpSprite->SetSpriteLinearVelocity(fSpeedX, 0);
		float fPosY;
		fPosY = CSystem::RandomRange(m_fScreenTop + 10.f, m_fScreenBottom - 10.f);

		tmpSprite->SetSpritePositionY(fPosY);
	}


}


CSprite* CGameMain::FindSpriteByName(const char* szName)
{
	for (int i = 0; i < m_vFish.size(); i++)
		if (strcmp(szName, m_vFish[i]->GetName()) == 0)
			return m_vFish[i];

}


