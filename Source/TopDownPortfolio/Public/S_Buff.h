#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedStruct.h"
#include "E_Buff.h"
#include "S_Buff.generated.h"

USTRUCT(BlueprintType)
struct FS_BuffData
{
	GENERATED_USTRUCT_BODY()
public:
	FS_BuffData() = default;
	virtual ~FS_BuffData() = default;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FE_BuffID eBuffID = FE_BuffID::E_Base;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fInRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fInFirstDelay = -1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int nCount = -1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bLoop;
};

class AA_Character_Base;
enum class FE_StatusID : uint8;

USTRUCT(BlueprintType)
struct FS_BuffData_Status : public FS_BuffData
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	AA_Character_Base* pCharacter;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FE_StatusID eStatuID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fRegenerationRatePerSecond;
};



UCLASS(Abstract)
class TOPDOWNPORTFOLIO_API US_Buff : public UUserDefinedStruct
{
	GENERATED_BODY()

private:
	US_Buff() {};
	
};
