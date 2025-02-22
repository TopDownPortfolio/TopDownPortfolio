#pragma once

#include "CoreMinimal.h"
#include "A_Attacker.h"
#include "A_Attacker_CapsuleCollision.generated.h"

class UCapsuleComponent;

UCLASS()
class TOPDOWNPORTFOLIO_API AA_Attacker_CapsuleCollision : public AA_Attacker
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Attacker, meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* m_pCollision;
public:
	AA_Attacker_CapsuleCollision();

};
