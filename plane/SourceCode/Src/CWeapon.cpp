#include "CWeapon.h"

CWeapon::CWeapon(const char *szName) :CSprite(szName){};
CWeapon::CWeapon(int iType, const char* szName): CSprite(szName) {
	m_iType = iType;
};  //ΪCBullet��׼��
