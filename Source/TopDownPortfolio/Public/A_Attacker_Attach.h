#pragma once

#include "CoreMinimal.h"
#include "A_Attacker.h"
#include "A_Attacker_Attach.generated.h"

USTRUCT(BlueprintType)
struct  FS_Attacker_AttachData
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf< UPrimitiveComponent>  cClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName strAttachSocket;
};

UCLASS()
class TOPDOWNPORTFOLIO_API AA_Attacker_Attach : public AA_Attacker
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FS_Attacker_AttachData> m_arCollisionData;
public:
public:
	AA_Attacker_Attach();
	virtual void E_Init(AA_Character_Base* pOwner, FName strSocket) override;
};
