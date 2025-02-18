#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedStruct.h"
#include "S_Skill.generated.h"

enum class FE_MontageID : uint8;
enum class FE_SkillID : uint8;

USTRUCT(BlueprintType)
struct FS_SkillData: public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FE_SkillID eSkillID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FE_MontageID eMontageID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fConsumMP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fAttack;
};