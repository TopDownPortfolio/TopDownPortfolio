#include "C_DefendMGR.h"
#include "T_DamageType.h"
#include "A_Character_Base.h"
#include "C_StatusMGR.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AISenseConfig_Damage.h"

UC_DefendMGR::UC_DefendMGR() :
	UActorComponent{}, m_pOwner{}, m_pStatus{}, m_eDmamgeType{}, m_eDefendType{}, m_eApplyStatus{}, On_StartDamage{}, On_EndDamage{}
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UC_DefendMGR::BeginPlay()
{
	UActorComponent::BeginPlay();
	m_pOwner = Cast< AA_Character_Base>(GetOwner());
	if (!m_pOwner)
	{
		DestroyComponent();
		return;
	}
	m_pStatus = m_pOwner->E_GetStatusMGR();
}

float UC_DefendMGR::E_Calcul_Default(float fDamageAmount)
{
	float fDamage = fDamageAmount;
	float fDefend = m_pStatus->E_GetStatus_Current(FE_StatusID::E_DEFEND);
	if (fDefend > 0.0f)
		fDamage -= fDefend;
	if (fDamage < 0.0f)
		fDamage = 0.0f;
	else
	{
		float fHP = m_pStatus->E_GetStatus_Current(FE_StatusID::E_HP);
		if (fHP - fDamage < 0.0f)
			fDamage = fHP;
	}
	return fDamage;
}

float UC_DefendMGR::E_ApplyStatus(FE_ApplyStatus eApplyStatus, float fDamageAmount)
{
	FE_StatusID eStatus[(uint8)FE_ApplyStatus::E_EnumMAX]{};
	eStatus[(uint8)FE_ApplyStatus::E_Hp] = FE_StatusID::E_HP;
	eStatus[(uint8)FE_ApplyStatus::E_Sheild] = FE_StatusID::E_HP; // TODO: FE_StatusID에 (실드 Sheild) 추가시 변경
	m_pStatus->E_AddStatus_Current(eStatus[(uint8)eApplyStatus], -fDamageAmount);
	return m_pStatus->E_GetStatus_Current(FE_StatusID::E_HP);;
}

float UC_DefendMGR::E_CalculDmage(FE_DefendType eDefendType, float fDamageAmount)
{
	float (UC_DefendMGR:: * pCalcul[(uint8)FE_DefendType::E_EnumMAX])(float){};
	pCalcul[(uint8)FE_DefendType::E_Default] = &UC_DefendMGR::E_Calcul_Default;
	return (this->*pCalcul[(uint8)eDefendType])(fDamageAmount);
}

void UC_DefendMGR::E_DamageEvent(float fDamageAmount, FDamageEvent const& DamageEvent)
{
	if (!DamageEvent.DamageTypeClass)
		return;
	UT_DamageType* cClass = Cast< UT_DamageType>(DamageEvent.DamageTypeClass->StaticClass());
	if (!cClass)
		return;
	TSubclassOf<UT_DamageType> cDamgeType{};
	cDamgeType = DamageEvent.DamageTypeClass;
	UT_DamageType const* const pDamageType = cDamgeType.GetDefaultObject();
	m_eDmamgeType = pDamageType->eDamageEventType;
	if(On_EndDamage.IsBound())
	{
		On_EndDamage.Broadcast(fDamageAmount, m_eDmamgeType);
	}
}

bool UC_DefendMGR::E_Defend(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AA_Character_Base* DamageCauser)
{
	if (!m_pOwner->CanBeDamaged())
		return false;
	if (On_StartDamage.IsBound())
	{
		On_StartDamage.Broadcast();
	}
	//m_pStateMGR->E_SubState(FE_StateFlag::E_IsTravel);
	//m_pStateMGR->E_AddState(FE_StateFlag::E_IsHitted);
	
	float fDamage = E_CalculDmage(m_eDefendType, DamageAmount);
	E_ApplyStatus(m_eApplyStatus, fDamage);
	E_DamageEvent(fDamage, DamageEvent);

	//TakeDamage(fDamage, DamageEvent, EventInstigator, DamageCauser);
	UGameplayStatics::ApplyDamage(m_pOwner, fDamage, EventInstigator, DamageCauser, UDamageType::StaticClass());
	UAISense_Damage::ReportDamageEvent(GetWorld(), m_pOwner, DamageCauser, fDamage, m_pOwner->GetActorLocation(), FVector::Zero());
	return true;
}
