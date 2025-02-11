#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "E_InputActionID.h"
#include "C_InputActionMGR.generated.h"


class UO_InputAction;
class UInputMappingContext;
class UInputAction;

USTRUCT(BlueprintType)
struct FS_InputActionData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UInputAction* pInputAction;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf< UO_InputAction> cClass;
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TOPDOWNPORTFOLIO_API UC_InputActionMGR : public UActorComponent
{
	GENERATED_BODY()
private:
	UPROPERTY(EditDefaultsOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TMap<FE_InputActionID, FS_InputActionData> m_mapInputAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* m_pDefaultMappingContext;
	UPROPERTY(VisibleAnywhere,  Category = Input, meta = (AllowPrivateAccess = "true"))
	UO_InputAction* m_arInputAction[(uint8)FE_InputActionID::E_EnumMAX];
public:
	UC_InputActionMGR();

protected:
	virtual void BeginPlay() override;

private:
	UO_InputAction* E_CreateInputAction(TSubclassOf< UO_InputAction> cClass);
	UO_InputAction* E_GetInputAction(FE_InputActionID eID);
	void E_Init_InputAction(FE_InputActionID eID);
	void E_Delete_InputAction(FE_InputActionID eID);
public:
	void E_Init();
	void E_Change_InputAction(FE_InputActionID eID);

	UFUNCTION(BlueprintCallable)
	void E_SetActiveInputAction(FE_InputActionID eID,bool bValue);
};