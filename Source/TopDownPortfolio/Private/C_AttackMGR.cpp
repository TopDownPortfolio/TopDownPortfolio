#include "C_AttackMGR.h"
#include "A_Attacker.h"
#include "A_Character_Base.h"
#include "D_DataTable.h"
#include "T_DamageType.h"


UC_AttackMGR::UC_AttackMGR() :
	UActorComponent{}, m_mapHitted{}, m_mapAttacker{}, m_pOwner{}, m_pTarget{}, m_fMaxTime{}, m_fTime{}, m_cDamageType{}, On_TargetChange {}, m_pDataTable{}
{
	PrimaryComponentTick.bCanEverTick = true;
	m_fMaxTime = 5.0f;
	m_pDataTable = UD_DataTable::E_GetDefault_DataTable(N_DefaultPath::E_Attack);
}

void UC_AttackMGR::BeginPlay()
{
	UActorComponent::BeginPlay();
	m_pOwner = Cast<AA_Character_Base>(GetOwner());

	if (m_pDataTable)
	{
		TArray< FS_AttackData*> arData{};
		m_pDataTable->GetAllRows< FS_AttackData>("", arData);
		for (FS_AttackData*& pData : arData)
		{
			AA_Attacker* pAttacker{};
			E_SpawnAttacker(*pData, pAttacker);
		}
	}
}

TSet<AA_Character_Base*>* UC_AttackMGR::E_GetHitted(int nAttackerIndex)
{
	return m_mapHitted.Find(nAttackerIndex);
}

TArray<AA_Attacker*>* UC_AttackMGR::E_GetAttacker(int nAttackerIndex)
{
	return m_mapAttacker.Find(nAttackerIndex);
}

AA_Attacker* UC_AttackMGR::E_SpawnAttacker(TSubclassOf<AA_Attacker> cAttacker)
{
	return GetWorld()->SpawnActor< AA_Attacker>(cAttacker);;
}

void UC_AttackMGR::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	UActorComponent::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (m_pTarget && m_fTime > 0)
	{
		m_fTime -= DeltaTime;
		if (m_fTime < 0)
		{
			if (On_TargetChange.IsBound())
				On_TargetChange.Broadcast(m_pTarget, nullptr);
			m_pTarget = nullptr;
		}
	}
	if (!IsValid( m_pTarget) && On_TargetChange.IsBound())
	{
		On_TargetChange.Broadcast(nullptr, nullptr);
	}
}

bool UC_AttackMGR::E_AddHitted(int nAttackerIndex, AA_Character_Base* pTarget)
{
	TSet<AA_Character_Base*>* pHitted = E_GetHitted(nAttackerIndex);
	if (!pHitted || !pTarget)
		return false;
	bool bIsAlreadyIn{};
	pHitted->FindOrAdd(pTarget, &bIsAlreadyIn);
	return bIsAlreadyIn;
}

void UC_AttackMGR::E_ResetHitted(int nAttackerIndex)
{
	TSet<AA_Character_Base*>* pHitted = E_GetHitted(nAttackerIndex);
	if (!pHitted)
		return;
	pHitted->Reset();
}

void UC_AttackMGR::E_GetHittedaArray(int nAttackerIndex, TArray<AA_Character_Base*>& arTargets)
{
	TSet<AA_Character_Base*>* pHitted = E_GetHitted(nAttackerIndex);
	if (!pHitted)
		return;
	arTargets = pHitted->Array();
}

bool UC_AttackMGR::E_IsAlreadyHitted(int nAttackerIndex, AA_Character_Base* pTarget)
{
	TSet<AA_Character_Base*>* pHitted = E_GetHitted(nAttackerIndex);
	if (!pHitted)
		return false;
	return pHitted->Find(pTarget) != nullptr;
}

TSubclassOf<UDamageType> UC_AttackMGR::E_GetDamageType()
{
	return m_cDamageType;
}

void UC_AttackMGR::E_SetDamageType(TSubclassOf<UDamageType> cDamageType)
{
	m_cDamageType = cDamageType;
}

void UC_AttackMGR::E_SpawnAttacker(FS_AttackData sAttckerData, AA_Attacker*& arSpawnedAttacker)
{
	int nAttackIndex = sAttckerData.nAttackIndex;
	TArray<AA_Attacker*>& arAttacker = m_mapAttacker.FindOrAdd(nAttackIndex);
	arSpawnedAttacker = E_SpawnAttacker(sAttckerData.cAttackClass);
	if (!arSpawnedAttacker)
		return;
	arSpawnedAttacker->E_Init(m_pOwner, sAttckerData.strSocket);
	m_mapHitted.FindOrAdd(nAttackIndex);
	arAttacker.Add(arSpawnedAttacker);
}

void UC_AttackMGR::E_OnAttack(int nAttackerIndex)
{
	TArray<AA_Attacker*>* pAttackers = E_GetAttacker(nAttackerIndex);
	if (!pAttackers)
		return;
	for (AA_Attacker* pAttacker :* pAttackers)
	{
		pAttacker->E_OnAttack();
	}
}

void UC_AttackMGR::E_EndAttack(int nAttackerIndex)
{
	TArray<AA_Attacker*>* pAttackers = E_GetAttacker(nAttackerIndex);
	if (!pAttackers)
		return;
	for (AA_Attacker* pAttacker : *pAttackers)
	{
		pAttacker->E_OffAttack();
	}
	TSet<AA_Character_Base*>* pHitted = E_GetHitted(nAttackerIndex);
	if (!pHitted)
		return;
	for (AA_Character_Base* pTarget: *pHitted)
	{
		bool bAttacker = m_pOwner->E_Attack(pTarget);
		AA_Character_Base* pNext = m_pTarget;
		if (bAttacker)
		{
			pNext = pTarget;
			m_fTime = m_fMaxTime;
			if (!m_pTarget)
			{
				if (On_TargetChange.IsBound())
					On_TargetChange.Broadcast(m_pTarget, pNext);
				m_pTarget = pNext;
			}
		}
	}
	pHitted->Reset();
}