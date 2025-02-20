#include "C_AttackMGR.h"
#include "A_Attacker.h"
#include "A_Character_Base.h"
#include "D_DataTable.h"

UC_AttackMGR::UC_AttackMGR() :
	UActorComponent{}, m_mapHitted{}, m_mapAttacker{}, m_pOwner {}, m_pTarget{}, m_fMaxTime{}, m_fTime{}
{
	PrimaryComponentTick.bCanEverTick = true;
	m_fMaxTime = 5.0f;
	m_pDataTable = UD_DataTable::E_GetDefault_DataTable(UD_DataTable::E_DefaultPath::E_Attack);
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
			if (OnTargetChange.IsBound())
				OnTargetChange.Broadcast(m_pTarget, nullptr);
			m_pTarget = nullptr;
		}
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
		m_pOwner->E_Attack(pTarget);
		if (!m_pTarget)
		{
			m_pTarget = pTarget;
			if (OnTargetChange.IsBound())
				OnTargetChange.Broadcast(nullptr, m_pTarget);
		}
		if (m_pTarget == pTarget)
		{
			m_fTime = m_fMaxTime;
		}
	}
	pHitted->Reset();
}
// 아래 코드는 Attacker 변경 전 코드
//void UC_AttackMGR::E_CollisionEnable(std::list<AA_Attacker*>& arList, ECollisionEnabled::Type eType)
//{
//	for (AA_Attacker* pAttacker : arList)
//	{
//		pAttacker->E_OnOff(eType);
//	}
//}
//bool UC_AttackMGR::E_AddTarget(AA_Character_Base* pTarget)
//{
//	bool bResult{};
//	m_setTarget.Add(pTarget, &bResult);
//	return bResult;
//}
//
//void UC_AttackMGR::E_ResetTarget()
//{
//	m_setTarget.Reset();
//}
//
//bool UC_AttackMGR::E_AddTarget(int nAttackIndex, AA_Character_Base* pTarget)
//{
//	return false;
//}
//
//void UC_AttackMGR::E_ResetTarget(int nAttackIndex)
//{
//}
//
//bool UC_AttackMGR::E_IsAlreadyIn(AA_Character_Base* pTarget)
//{
//	return !m_setTarget.Contains(pTarget);
//}
//
//std::list<AA_Attacker*>* UC_AttackMGR::E_GetRegisterAttacker(uint8 nIndex)
//{
//	std::list<AA_Attacker*>* pResult{};
//	/*if (m_arAttacker.IsValidIndex(nIndex))
//		pResult = &m_arAttacker[nIndex];*/
//	return pResult;
//}
//void UC_AttackMGR::E_RegisterAttacker(uint8 nIndex, AActor* pAttacker)
//{
//	if (!pAttacker)
//		return;
//	AA_Attacker* pAttack= Cast < AA_Attacker>(pAttacker);
//	if (!m_arAttacker.IsValidIndex(nIndex) || !pAttack)
//		return;
//	//m_arAttacker[nIndex].push_back(pAttack);
//}
//void UC_AttackMGR::E_On(uint8 nIndex)
//{
//	if (!m_arAttacker.IsValidIndex(nIndex))
//		return;
//	//E_CollisionEnable(m_arAttacker[nIndex], ECollisionEnabled::QueryOnly);
//}
//
//void UC_AttackMGR::E_Off(uint8 nIndex)
//{
//	if (!m_arAttacker.IsValidIndex(nIndex))
//		return;
//	//E_CollisionEnable(m_arAttacker[nIndex], ECollisionEnabled::NoCollision);
//	for (AA_Character_Base* pTarget : m_setTarget)
//	{
//		m_pOwner->E_Attack(pTarget);
//		if (!m_pTarget)
//		{
//			m_pTarget = pTarget;
//			if (OnTargetChange.IsBound())
//				OnTargetChange.Broadcast(nullptr, m_pTarget);
//
//		}
//		if (m_pTarget == pTarget)
//		{
//			m_fTime = m_fMaxTime;
//
//		}
//	}
//	m_setTarget.Reset();
//	//GetWorld()->GetTime
//}

