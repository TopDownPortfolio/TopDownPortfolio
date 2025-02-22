#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "E_State.h"
#include "E_CharacterType.h"
#include "C_StateMGR.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOPDOWNPORTFOLIO_API UC_StateMGR : public UActorComponent
{
	GENERATED_BODY()
private:

public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = StateMGR, meta = ( Bitmask, BitmaskEnum = FE_StateFlag))
	uint8 m_eState;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = StateMGR)
	FE_CharacterType m_eCharacterType;
public:	
	UC_StateMGR();

protected:
	virtual void BeginPlay() override;

public:	
	void E_Init(FE_CharacterType eCharacterType) { E_SetCharacterType(eCharacterType);}
	UFUNCTION(BlueprintPure)
	FE_Affiliation E_GetAffiliation(AA_Character_Base* pACharacter);

	FE_Affiliation E_GetAffiliation(FE_CharacterType eSrc, FE_CharacterType eDst);

	UFUNCTION(BlueprintPure)
	FE_CharacterType E_GetCharacterType() { return m_eCharacterType; }
	UFUNCTION(BlueprintCallable)
	void E_SetCharacterType(FE_CharacterType eCharacterType) { m_eCharacterType = eCharacterType; }

	UFUNCTION(BlueprintCallable)
	bool E_CalculStateType(FE_StateCalcul eCalcul, FE_StateFlag eStateType);
	UFUNCTION(BlueprintPure)	
	bool E_CheckState(FE_StateFlag eStateType) { return m_eState & (uint8)eStateType; }
	bool E_CheckState(uint8 eStateType) { return E_CheckState((FE_StateFlag)eStateType); }
	UFUNCTION(BlueprintCallable)
	bool E_AddState(FE_StateFlag eStateType);
	bool E_AddState(uint8 eStateType) { return E_AddState((FE_StateFlag)eStateType); }
	UFUNCTION(BlueprintCallable)
	bool E_SubState(FE_StateFlag eStateType);
	bool E_SubState(uint8 eStateType) { return E_SubState((FE_StateFlag)eStateType); }
};
