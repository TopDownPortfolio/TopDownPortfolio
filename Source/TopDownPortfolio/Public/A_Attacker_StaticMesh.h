#pragma once

#include "CoreMinimal.h"
#include "A_Attacker.h"
#include "A_Attacker_StaticMesh.generated.h"

class UStaticMeshComponent;
class UCapsuleComponent;

UCLASS()
class TOPDOWNPORTFOLIO_API AA_Attacker_StaticMesh : public AA_Attacker
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Attacker, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* m_pMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Attacker, meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* m_pCollision;

public:
	AA_Attacker_StaticMesh();
};
