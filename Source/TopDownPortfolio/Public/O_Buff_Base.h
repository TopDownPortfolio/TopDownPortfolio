#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "S_Buff.h"
#include "O_Buff_Base.generated.h"


UCLASS()
class TOPDOWNPORTFOLIO_API UO_Buff_Base : public UObject
{
	GENERATED_BODY()
protected:
	FTimerHandle m_sHandle;
	float m_fInRate;
	float m_fInFirstDelay = -1.0f;
	int m_nCount;
	bool m_bLoop;
public:
	UO_Buff_Base();
protected:
	FTimerManager& E_GetTimer();
	void E_SetDefault(FS_BuffData const& sData)
	{
		m_fInRate = sData.fInRate;
		m_bLoop = sData.bLoop;
		m_nCount = sData.nCount;
		m_fInFirstDelay = sData.fInFirstDelay;
	}

	virtual void E_TimerFunction() {}
	void E_Timer();

public:
	virtual void E_SetBuffData(FS_BuffData const& sData) { E_SetDefault(sData); }
	void E_Register();
	void E_UnRegister();


};
	
/* 버프 예시
* FS_BuffData_Status status;
	status.fValuePerSecond = -2.0f;
	status.eStatuID = FE_StatusID::E_HP;
	status.bLoop = true;
	status.fInRate = 0.5f;
	status.nCount = 10;
	status.pCharacter = this;
	m_pBuffMGR->E_StartBuff(UO_Buff_Status::StaticClass(), status);*/