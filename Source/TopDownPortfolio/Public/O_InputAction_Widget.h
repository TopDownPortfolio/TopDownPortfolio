// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "O_InputAction.h"
#include "O_InputAction_Widget.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNPORTFOLIO_API UO_InputAction_Widget : public UO_InputAction
{
	GENERATED_BODY()
private:

public:
	UO_InputAction_Widget();
public:
	virtual void E_Started(const FInputActionValue& fInputValue) override;
};
