// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "A_Attacker.h"
#include "A_Attacker_Spawn.generated.h"

/**
 * 
 */
UCLASS(NotBlueprintable)
class TOPDOWNPORTFOLIO_API AA_Attacker_Spawn : public AA_Attacker
{
	GENERATED_BODY()
protected:
	TSet< AA_Character_Base*> m_setTarget;
public:
	AA_Attacker_Spawn();

protected:
	virtual bool E_CheckOverlap(AActor* pTarget) override;
	virtual bool E_CheckOverlap(AActor* pTarget) override;
	virtual void E_OverlapEvent(AActor* pTarget) override;
	virtual void E_On()  override;
	virtual void E_Off() override;
};
