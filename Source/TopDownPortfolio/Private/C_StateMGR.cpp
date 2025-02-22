#include "C_StateMGR.h"
#include "A_Character_Base.h"

UC_StateMGR::UC_StateMGR()
{
	PrimaryComponentTick.bCanEverTick = false;
	E_AddState(FE_StateFlag::E_IsTravel);
}

void UC_StateMGR::BeginPlay()
{
	UActorComponent::BeginPlay();
}

FE_Affiliation UC_StateMGR::E_GetAffiliation(FE_CharacterType eSrc, FE_CharacterType eDst)
{
	FE_Affiliation arAffiliation[(uint8)FE_CharacterType::E_EnumMAX][(uint8)FE_CharacterType::E_EnumMAX] =
	{
		{ FE_Affiliation::E_Friend,		FE_Affiliation::E_NONE,		FE_Affiliation::E_NONE,		FE_Affiliation::E_NONE},
		{ FE_Affiliation::E_NONE,		FE_Affiliation::E_Friend,	FE_Affiliation::E_Enemy,	FE_Affiliation::E_NONE},
		{ FE_Affiliation::E_NONE,		FE_Affiliation::E_Enemy,	FE_Affiliation::E_Friend,	FE_Affiliation::E_NONE},
		{ FE_Affiliation::E_NONE,		FE_Affiliation::E_NONE,		FE_Affiliation::E_NONE,		FE_Affiliation::E_Friend}
	};
	return arAffiliation[(uint8)eSrc][(uint8)eDst];
}

FE_Affiliation UC_StateMGR::E_GetAffiliation(AA_Character_Base* pACharacter)
{
	FE_Affiliation eReulst = FE_Affiliation::E_Neutral;
	if (pACharacter)
	{
		eReulst = E_GetAffiliation(pACharacter->E_GetStateMGR()->E_GetCharacterType(), E_GetCharacterType());
	}
	return eReulst;
}

bool UC_StateMGR::E_CalculStateType(FE_StateCalcul eCalcul, FE_StateFlag eStateType)
{
	bool (UC_StateMGR::*Func[(uint8)FE_StateCalcul::E_EnumMax])(FE_StateFlag){};
	bool (UC_StateMGR:: * pResult)(FE_StateFlag) {};
	Func[(uint8)FE_StateCalcul::E_Add] = &UC_StateMGR::E_AddState;
	Func[(uint8)FE_StateCalcul::E_Sub] = &UC_StateMGR::E_SubState;
	Func[(uint8)FE_StateCalcul::E_Check] = &UC_StateMGR::E_CheckState;
	pResult = Func[(uint8)eCalcul];
	return (this->*pResult)(eStateType);
}

bool UC_StateMGR::E_AddState(FE_StateFlag eStateType)
{
	m_eState |= (uint8)eStateType;
	return  E_CheckState(eStateType);
}

bool UC_StateMGR::E_SubState(FE_StateFlag eStateType)
{
	if (E_CheckState(eStateType))
		m_eState ^= (uint8)eStateType;
	return  E_CheckState(eStateType);
	// or로 추가 and로 확인 xor 로 제거
	// 주의 : xor를 잘못 사용하면 추가가 되버림 if로 확인하는걸 추천
}

