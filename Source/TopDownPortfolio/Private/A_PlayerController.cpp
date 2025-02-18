#include "A_PlayerController.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "E_Skill.h"
#include "C_SkillMGR.h"


AA_PlayerController::AA_PlayerController() :
	APlayerController{}, m_pWidgetMGR{}, m_pInputActionMGR{}, m_pInterfaceMGR{}, FXCursor{}, m_pSkillMGR{}
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	
	m_pWidgetMGR = CreateDefaultSubobject<UC_WidgetMGR>("WidgetMGR");
	m_pInputActionMGR = CreateDefaultSubobject<UC_InputActionMGR>("InputActionMGR");
	m_pInterfaceMGR = CreateDefaultSubobject<UC_InterfaceMGR>("InterfaceMGR");
	m_pSkillMGR = CreateDefaultSubobject<UC_SkillMGR>("SkillMGR");
}

void AA_PlayerController::E_RegisterComponent(UActorComponent* pComponent)
{
	if (pComponent)
		pComponent->RegisterComponent();
}

void AA_PlayerController::E_SpawnEffect()
{
	FVector CachedDestination = E_GetInterfaceMGR()->E_GetLocation();
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
}

FE_SkillID AA_PlayerController::E_GetSkillID(FE_InputActionID eID)
{
	FE_SkillID arSkillID[(uint8)FE_InputActionID::E_EnumMAX] = { FE_SkillID::E_NONE };
	arSkillID[(uint8)FE_InputActionID::E_Q] = FE_SkillID::E_01;
	arSkillID[(uint8)FE_InputActionID::E_W] = FE_SkillID::E_02;
	arSkillID[(uint8)FE_InputActionID::E_E] = FE_SkillID::E_03;
	return arSkillID[(uint8)eID];
}

FE_WindowID AA_PlayerController::E_GetWidgetID(FE_InputActionID eID)
{
	FE_WindowID arSkillID[(uint8)FE_InputActionID::E_EnumMAX] = { FE_WindowID::E_NONE };
	arSkillID[(uint8)FE_InputActionID::E_SkillWindow] = FE_WindowID::E_Skill;
	return arSkillID[(uint8)eID];
}

void AA_PlayerController::E_Action_Implementation(FE_SkillID eID)
{
	if (m_pSkillMGR)
		m_pSkillMGR->E_Action(eID);
}

void AA_PlayerController::SetupInputComponent()
{
	APlayerController::SetupInputComponent();
	if (m_pInputActionMGR)
		m_pInputActionMGR->E_Init();
}

void AA_PlayerController::OnConstruction(const FTransform& Transform)
{
	APlayerController::OnConstruction(Transform);
	E_RegisterComponent(m_pWidgetMGR);
	E_RegisterComponent(m_pInputActionMGR);
	E_RegisterComponent(m_pSkillMGR);
	E_RegisterComponent(m_pInterfaceMGR);
}


void AA_PlayerController::Tick(float DeltaSeconds)
{
	APlayerController::Tick(DeltaSeconds);
}

