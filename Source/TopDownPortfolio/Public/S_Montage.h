#pragma once

#include "CoreMinimal.h"
#include "E_MontageID.h"
#include "Engine/UserDefinedStruct.h"
#include "S_Montage.generated.h"

class UAnimMontage;

USTRUCT(BlueprintType)
struct FS_MontagePlayData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FE_MontageID eID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName strSection;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fPlaySpeed = 1.0f;
};

USTRUCT(BlueprintType)
struct FS_MontageData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FE_MontageID eID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int nIndex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* pMontage;
};

UCLASS(Abstract)
class TOPDOWNPORTFOLIO_API US_Montage : public UUserDefinedStruct
{
	GENERATED_BODY()
private:
	US_Montage() {};
};
