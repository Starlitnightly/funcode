#pragma once
#include "CommonClass.h"
#include "CWeapon.h"
class CEnemyFighter :
	public CWeapon
{
private:


public:

	CEnemyFighter(const char* szName);
	~CEnemyFighter();

	static float	m_fCreateTime;			// �����л���ʱ����
	static int	m_iCreatedEnemyCount;//��ʾ����ս������

	void static createEnemyFighter(float fDeltaTime);

	float m_fBulletCreateTime;
	float m_fFloatTime;
	bool m_bFloatUp;
	void  OnFire(float fDeltaTime);
	void OnColOtherSprite(CWeapon *pOther);

};

