// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class FE_StateType : uint8
{
    E_None              = (0x0) UMETA(Hidden),
    E_CantMoveable      = (1 << 0),
    E_CantJump          = (1 << 1),
    E_CantTarget        = (1 << 2),
    E_IsTravel          = (1 << 3)
};