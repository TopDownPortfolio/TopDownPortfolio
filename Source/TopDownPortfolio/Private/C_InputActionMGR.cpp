#include "C_InputActionMGR.h"
#include "GameFramework/PlayerController.h"
#include "O_InputAction.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "D_DataTable.h"

UC_InputActionMGR::UC_InputActionMGR() :
	UActorComponent{}, m_mapInputAction{}, m_pDefaultMappingContext{}, m_arInputAction {}
{
	PrimaryComponentTick.bCanEverTick = false;
	m_pDefaultMappingContext = UD_DataTable::E_GetDefault_InputMappingContext(UD_DataTable::E_DefaultPath::E_InputMapping);
}

void UC_InputActionMGR::BeginPlay()
{
	UActorComponent::BeginPlay();
	APlayerController* pPlayer = Cast< APlayerController>(GetOwner());
	if (!pPlayer)
	{
		DestroyComponent();
		return;
	}

	TArray<FE_InputActionID> arData{};
	m_mapInputAction.GetKeys(arData);
	for (FE_InputActionID eID : arData)
	{
		E_Change_InputAction(eID);
	}
}

void UC_InputActionMGR::E_Delete_InputAction(FE_InputActionID eID)
{
	uint8 nIndex = (uint8)eID;
	FS_InputActionData* pInputAction = &m_mapInputAction[eID];
	UO_InputAction* pInputActionObj = E_GetInputAction(eID);
	if (!pInputAction || !pInputActionObj)
		return;
	pInputActionObj->E_Delete();
	m_arInputAction[nIndex] = nullptr;
}

void UC_InputActionMGR::E_Init_InputAction(FE_InputActionID eID)
{
	uint8 nIndex = (uint8)eID;
	FS_InputActionData* pInputAction = &m_mapInputAction[eID];
	UO_InputAction* pInputActionObj = E_GetInputAction(eID);
	if (!pInputAction || !pInputActionObj)
		return;
	pInputActionObj->E_SetInputActionID(eID);
	if (!pInputAction->pInputAction)
	{
		m_arInputAction[nIndex] = nullptr;
		return;
	}

	pInputActionObj->E_Init(Cast< APlayerController>(GetOwner()), pInputAction->pInputAction);
}

void UC_InputActionMGR::E_Change_InputAction(FE_InputActionID eID)
{
	uint8 nIndex = (uint8)eID;
	E_Delete_InputAction(eID);
	m_arInputAction[nIndex] = E_CreateInputAction(m_mapInputAction[eID].cClass);
	E_Init_InputAction(eID);
}

UO_InputAction* UC_InputActionMGR::E_CreateInputAction(TSubclassOf<UO_InputAction> cClass)
{
	if (!cClass)
		return nullptr;
	return NewObject<UO_InputAction>(this, cClass.Get(), NAME_None, EObjectFlags::RF_Public);
}

void UC_InputActionMGR::E_SetActiveInputAction(FE_InputActionID eID, bool bValue)
{
	E_GetInputAction(eID)->E_SetActive(bValue);
}

void UC_InputActionMGR::E_Init()
{
	APlayerController* pPlayer = Cast< APlayerController>(GetOwner());
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pPlayer->GetLocalPlayer());
	if (!Subsystem)
		return;
	Subsystem->AddMappingContext(m_pDefaultMappingContext, 0);
}

UO_InputAction* UC_InputActionMGR::E_GetInputAction(FE_InputActionID eID)
{
	FE_InputActionID eResult = FE_InputActionID::E_NONE;
	if (FE_InputActionID::E_NONE <= eID && eID < FE_InputActionID::E_EnumMAX)
		eResult = eID;
	return m_arInputAction[(uint8)eResult];
}