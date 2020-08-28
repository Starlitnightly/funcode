#include "CommonClass.h"
#include "LessonX.h"
#include "CEnemyFighter.h"
#include <Stdio.h>



CEnemyFighter::CEnemyFighter(const char* szName) :CWeapon(szName)
{


}

CEnemyFighter::~CEnemyFighter()
{
}

float CEnemyFighter::m_fCreateTime = 0.f;
int CEnemyFighter::m_iCreatedEnemyCount = 0;

void CEnemyFighter::createEnemyFighter(float fDeltaTime) //�����з�ս��
{
	// �Ƿ�ʱ�䴴��
	m_fCreateTime -= fDeltaTime;
	if (m_fCreateTime <= 0.f)
	{
		// ���һ��ʱ�䣬��Ϊ�´γ�����ʱ��
		m_fCreateTime = (float)CSystem::RandomRange(1, 3);
		//��������Ӵ���һ�ܵз�ս���Ĵ���
		char	szName[MAX_NAME_LEN];
		sprintf(szName, "HorizontalSprite_%d", m_iCreatedEnemyCount); //���½��ĵз�ս������
		m_iCreatedEnemyCount++;
		CEnemyFighter *pSprite = new CEnemyFighter(szName);
		pSprite->CloneSprite("HorizontalSprite_Template");  //��¡ģ��
		int iPosBase = CSystem::RandomRange((int)CSystem::GetScreenTop() + 10, (int)CSystem::GetScreenBottom() - 10);
		int	iRandom = CSystem::RandomRange(iPosBase - 10, iPosBase + 10);
		float	fPosX = (int)CSystem::GetScreenRight() + 20.f;
		pSprite->SetSpritePosition(fPosX, (float)iRandom);
		pSprite->SetSpriteLinearVelocityX(-10.f);
		pSprite->SetSpriteWorldLimit(WORLD_LIMIT_KILL, CSystem::GetScreenLeft() - 10.f, CSystem::GetScreenTop(), CSystem::GetScreenRight() + 200.f, CSystem::GetScreenBottom());
		pSprite->SetSpriteCollisionActive(true, true);
		pSprite->SetHp(300);
		pSprite->SetScore(100);
		pSprite->SetDamage(200);

		g_GameMain.AddSprite(pSprite);

	}
}

void CEnemyFighter::OnFire(float fDeltaTime)
{

		m_fBulletCreateTime -= fDeltaTime;
		if (m_fBulletCreateTime <= 0.f)
		{
			m_fBulletCreateTime = 1.f;
			g_GameMain.CreateBullet(1, GetSpritePositionX(),
				GetSpritePositionY());   //1��ʾ�ǵз�ս���ӵ�
		}

		if (m_bFloatUp)
		{
			m_fFloatTime += fDeltaTime;
			if (m_fFloatTime >= 1.f)
			{
				m_bFloatUp = false;
			}
			float	fPosY = GetSpritePositionY();
			fPosY += 6.f * fDeltaTime;
			SetSpritePositionY(fPosY);
		}
		else
		{
			m_fFloatTime -= fDeltaTime;
			if (m_fFloatTime <= 0.f)
			{
				m_bFloatUp = true;
			}
			float	fPosY = GetSpritePositionY();
			fPosY -= 6.f * fDeltaTime;
			SetSpritePositionY(fPosY);
		}



}

void CEnemyFighter::OnColOtherSprite(CWeapon *pOther)
{
	if (NULL == pOther)
		return;
	if (pOther->IsMyFighter() || pOther->IsMyBullet())
	{
		SetHp(GetHp() - pOther->GetDamage());
		if (IsDead())
		{
			g_GameMain.GetMyFighter()->SetScore(g_GameMain.GetMyFighter()->GetScore() + GetScore());
		}
	}
}



