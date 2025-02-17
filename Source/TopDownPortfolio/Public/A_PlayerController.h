#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "C_InputActionMGR.h"
#include "C_InterfaceMGR.h"
#include "C_WidgetMGR.h"
#include "A_PlayerController.generated.h"

class UNiagaraSystem;
enum class FE_SkillID :uint8;
class UC_SkillMGR;

UCLASS()
class TOPDOWNPORTFOLIO_API AA_PlayerController : public APlayerController
{
	GENERATED_BODY()
protected: 
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	UC_WidgetMGR* m_pWidgetMGR;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	UC_InputActionMGR* m_pInputActionMGR;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	UC_InterfaceMGR* m_pInterfaceMGR;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UNiagaraSystem* FXCursor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = "true"))
	UC_SkillMGR* m_pSkillMGR;

public:
	AA_PlayerController();


protected:
	virtual void SetupInputComponent() override;
public:
	virtual void Tick(float DeltaSeconds) override;
	virtual void OnConstruction(const FTransform& Transform) override;
protected:
	void E_RegisterComponent(UActorComponent* pComponent);
public:
	void E_SpawnEffect();
	FE_SkillID E_GetSkillID(FE_InputActionID eID);
	FE_WindowID E_GetWidgetID(FE_InputActionID eID);

	UFUNCTION(BlueprintPure)
	UC_WidgetMGR* E_GetWidgetMGR() { return m_pWidgetMGR; }
	UFUNCTION(BlueprintPure)
	UC_InterfaceMGR* E_GetInterfaceMGR() { return m_pInterfaceMGR; }
	UFUNCTION(BlueprintPure)
	UC_InputActionMGR* E_GetInputActionMGR() { return m_pInputActionMGR; }
	UFUNCTION(BlueprintPure)

	UC_SkillMGR* E_GetSkillMGR() { return m_pSkillMGR; }
	UFUNCTION(BlueprintCallable, NetMulticast, Reliable)
	void E_Action(FE_SkillID eID);
	virtual void E_Action_Implementation(FE_SkillID eID);
};
