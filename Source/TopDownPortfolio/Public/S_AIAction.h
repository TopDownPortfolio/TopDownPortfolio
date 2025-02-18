#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedStruct.h"
#include "S_AIAction.generated.h"

USTRUCT(BlueprintType)
struct FS_AIActionData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int nActionIndex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int nPriority;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int nActionID;

	bool operator()(const FS_AIActionData* sSrc, const FS_AIActionData* sDst)
	{
		return sSrc->nPriority > sDst->nPriority;
	}
};