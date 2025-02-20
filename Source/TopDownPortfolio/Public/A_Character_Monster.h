#pragma once

#include "CoreMinimal.h"
#include "A_Character_Base.h"
#include "A_Character_Monster.generated.h"

class UC_AIActionMGR;

UCLASS()
class TOPDOWNPORTFOLIO_API AA_Character_Monster : public AA_Character_Base
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = AIAction, meta = (AllowPrivateAccess = "true"))
	UC_AIActionMGR* m_pAIAction;
protected:
	void E_Dead();

public:

	virtual void E_Defend(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AA_Character_Base* DamageCauser) override;
	AA_Character_Monster();
	virtual void OnConstruction(const FTransform& Transform) override;

	UFUNCTION(BlueprintPure)
	UC_AIActionMGR* E_GetAIAction() { return m_pAIAction; }
};

