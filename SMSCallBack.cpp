#include "SMSCallBack.h"
#include "GameManager.h"
#include "GameDataManager.h"
#include "Player.h"
#include "SMSInfo.h"
#include "UI.h"
void buyItems(int payId)
{
	CastInf *inf = GData->getCastInf(payId);
	switch (payId)
	{
	case SMS_BUY_Gold1:
	case SMS_BUY_Gold2:
	case SMS_BUY_Gold3:
	case SMS_BUY_Gold4:
	case SMS_BUY_Gold5:
	case SMS_BUY_Gold6:
	case SMS_BUY_Gold7:
	case SMS_BUY_Gold8:
	case SMS_BUY_Gold9:
	case SMS_BUY_Gold10:
		SELF->addGold(inf->buygold);
		break;
	case SMS_BUY_Rage:
		SELF->addVariable(RageItem,3);
		break;
	case SMS_BUY_FixedScreen:
		SELF->addVariable(FixedItem,3);
		break;
	case SMS_BUY_LockFish:
		SELF->addVariable(LockFishItem,3);
		break;
	case SMS_BUY_Missile:
		SELF->addVariable(MissileItem,3);
		break;
	case SMS_BUY_Laser:
		SELF->addVariable(LaserItem,3);
		break;
	case SMS_BUY_Cananon2:
	case SMS_BUY_Cananon3:
	case SMS_BUY_Cananon4:
	case SMS_BUY_Cananon5:
	case SMS_BUY_Cananon6:
		{
			CannonInf *inf = GData->getCannonInf(payId - SMS_BUY_Cananon2 + 1);
			inf->bOpen = true;
		}
		break;
	case SMS_BUY_FirstCharge:
		SELF->addGold(8000);
		SELF->addVariable(MissileItem,1);
		SELF->addVariable(LaserItem,1);
		break;
	case SMS_BUY_CoinPackage:
		SELF->addGold(125000);
		break;
	case SMS_BUY_GoldChannel:
		SELF->addGold(20000);
		break;
	default:
		break;
	}
}

void chargeCB(int payId,bool flag)
{
	if(flag)
	{
		buyItems(payId);
	}
}