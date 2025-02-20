#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "E_Status.h"
#include "Engine/DataTable.h"
#include "C_StatusMGR.generated.h"

USTRUCT(BlueprintType)
struct FS_StatusData: public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FE_StatusID eID;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FE_StatusType eType;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float fValue;
};


USTRUCT(BlueprintType)
struct FS_StatusInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FE_StatusID eID;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName strName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName strDesc;
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOPDOWNPORTFOLIO_API UC_StatusMGR : public UActorComponent
{
	GENERATED_BODY()
protected:
	E_Status m_arStatus[(uint8)FE_StatusID::E_EnumMAX];
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = StatusMGR)
	UDataTable* m_pDataTable;
public:	
	UC_StatusMGR();

protected:
	virtual void BeginPlay() override;

protected:
	E_Status* E_GetClass(FE_StatusID eID);
	float E_GetStatus(FE_StatusID eID, FE_StatusType eType);
	void E_SetStatus(FE_StatusID eID, FE_StatusType eType, float fValue);
	void E_AddStatus(FE_StatusID eID, FE_StatusType eType, float fValue);

public:	
	void E_Init_Begin();
	UFUNCTION(BlueprintPure)
	float E_GetStatus_Current(FE_StatusID eID);
	UFUNCTION(BlueprintPure)
	float E_GetStatus_Ratio(FE_StatusID eID);
	UFUNCTION(BlueprintPure)
	float E_GetStatus_Max(FE_StatusID eID);
	UFUNCTION(BlueprintCallable)
	void E_SetStatus_Current(FE_StatusID eID, float fValue);
	UFUNCTION(BlueprintCallable)
	void E_SetStatus_Max(FE_StatusID eID, float fValue);
	UFUNCTION(BlueprintCallable)
	void E_AddStatus_Current(FE_StatusID eID, float fValue);
	UFUNCTION(BlueprintCallable)
	void E_AddStatus_Max(FE_StatusID eID, float fValue);
	UFUNCTION(BlueprintCallable)
	bool E_CheckAdd(FE_StatusID eID, float fValue);
};
