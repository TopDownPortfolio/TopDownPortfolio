#include "C_BuffMGR.h"
#include "O_Buff_Base.h"
#include "O_Buff_Status.h"

UC_BuffMGR::UC_BuffMGR() :
	UActorComponent{}
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UC_BuffMGR::BeginPlay()
{
	UActorComponent::BeginPlay();
}

void UC_BuffMGR::E_StartBuff(FS_BuffData const& sData)
{
	TSubclassOf<UO_Buff_Base> cBuff = E_GetStaticClass(sData.eBuffID);
	UO_Buff_Base* pBuff = NewObject< UO_Buff_Base>(this, cBuff);
	if (pBuff)
	{
		m_arBuff.Add(pBuff);
		pBuff->E_SetBuffData(sData);
		pBuff->E_Register();
	}
}

TSubclassOf<UO_Buff_Base> UC_BuffMGR::E_GetStaticClass(FE_BuffID eID)
{
	TSubclassOf<UO_Buff_Base> arClass[(uint8)FE_BuffID::E_EnumMAX]{};
	arClass[(uint8)FE_BuffID::E_NONE]		= UO_Buff_Base::StaticClass();
	arClass[(uint8)FE_BuffID::E_Status]		= UO_Buff_Status::StaticClass();
	return arClass[(uint8)eID] ? arClass[(uint8)eID] : arClass[(uint8)FE_BuffID::E_NONE];
}

