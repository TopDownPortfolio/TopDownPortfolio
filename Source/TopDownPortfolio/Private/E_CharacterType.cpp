#include "E_CharacterType.h"

FE_Affiliation C_CharacterType::E_GetAffiliation(FE_CharacterType eSrc, FE_CharacterType eDst)
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
