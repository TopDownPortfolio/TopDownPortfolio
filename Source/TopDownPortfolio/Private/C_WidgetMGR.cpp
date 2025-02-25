#include "C_WidgetMGR.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "GameFramework/PawnMovementComponent.h"
#include "W_WindowBase.h"
#include "D_DataTable.h"

UC_WidgetMGR::UC_WidgetMGR() :
	UActorComponent{}, m_pController{}, m_pMain{}, m_pMainPanel{}, m_pDataTable{}, m_mapWindow {}, m_arWidgetData{}, m_arWidgetStack{}, m_nStackCount{}
{
	PrimaryComponentTick.bCanEverTick = false;

	//m_mapWindow.FindOrAdd(FE_WindowID::E_Main, UD_DataTable::E_GetDefault_UserWidgetClass(N_DefaultPath::E_MainWidget));
	m_nStackCount = -1;
	m_pDataTable = UD_DataTable::E_GetDefault_DataTable(N_DefaultPath::E_WindowClassData);
	if (m_pDataTable)
	{
		TArray< FS_WindowClassData*> arData{};
		m_pDataTable->GetAllRows< FS_WindowClassData>("", arData);
		for ( FS_WindowClassData*& pData : arData)
		{
			FE_WindowID eWindowID = pData->eWindowID;
			uint8 nIndedx = (uint8)eWindowID;
			if (pData->cWindowClass)
				m_mapWindow.FindOrAdd(eWindowID,pData);
		}
	
	}
}

void UC_WidgetMGR::BeginPlay()
{
	UActorComponent::BeginPlay();
	m_pController = Cast<APlayerController>(GetOwner());
	if (!m_pController || !m_pDataTable)
	{
		DestroyComponent();
		return;
	}
	TArray< FE_WindowID> arData{};
	m_mapWindow.GetKeys(arData);
	for (FE_WindowID& eID : arData)
	{
		const FS_WindowClassData* const * pData = m_mapWindow.Find(eID);
		uint8 nIndedx = (uint8)(*pData)->eWindowID;
		m_arWidgetData[nIndedx].pWidget = E_CreateWidget((*pData)->cWindowClass);
	}
	m_pMain = m_arWidgetData[(uint8)FE_WindowID::E_Main].pWidget;
	m_pMain->AddToViewport();
	E_AddWidget(m_arWidgetData[(uint8)FE_WindowID::E_PlayerActionBar].pWidget);
	m_arWidgetData[(uint8)FE_WindowID::E_PlayerActionBar].bRegistered = true;
}

UPanelWidget* UC_WidgetMGR::E_GetMainPanel()
{
	if (!m_pMainPanel)
		m_pMainPanel = Cast<UPanelWidget>(m_pMain->WidgetTree->RootWidget);
	return m_pMainPanel;
}

UW_WindowBase* UC_WidgetMGR::E_CreateWidget(TSubclassOf<UW_WindowBase> cWidget)
{
	return Cast< UW_WindowBase>(CreateWidget(m_pController, cWidget));
}

bool UC_WidgetMGR::E_CheckWindow(FE_WindowID eWindowID)
{
	return m_arWidgetData[(uint8)eWindowID].pWidget != nullptr;
}

void UC_WidgetMGR::E_Register(FE_WindowID eWindowID, UW_WindowBase* pWidget)
{
	if (!m_arWidgetData[(uint8)eWindowID].pWidget)
		m_arWidgetData[(uint8)eWindowID].pWidget = pWidget;
}

UW_WindowBase* UC_WidgetMGR::E_GetWidget(FE_WindowID eWindowID)
{
	return m_arWidgetData[(uint8)eWindowID].pWidget;
}

void UC_WidgetMGR::E_RegisterWidget(FE_WindowID eWindowID)
{
	if (m_nStackCount == (uint8)FE_WindowID::E_EnumMAX || !E_CheckWindow(eWindowID))
		return;
	S_WidgetData* pWidgetData = &m_arWidgetData[(uint8)eWindowID];
	UW_WindowBase* pRefWidget = pWidgetData->pWidget;
	E_Register(eWindowID, pRefWidget);
	pRefWidget->SetFocus();
	if (!pWidgetData->bRegistered)
	{
		E_AddWidget(pRefWidget);
		pWidgetData->bRegistered = true;
	}
	m_nStackCount++;
	m_arWidgetStack[m_nStackCount] = eWindowID;
	
}

void UC_WidgetMGR::E_UnRegisterWidget()
{
	if (m_nStackCount < 0)
		return;
	FE_WindowID eWindowID = m_arWidgetStack[m_nStackCount];
	S_WidgetData* pWidgetData = &m_arWidgetData[(uint8)eWindowID];
	pWidgetData->bRegistered = false;
	UW_WindowBase* pWidget = pWidgetData->pWidget;
	E_RemoveWidget(pWidget);
	m_nStackCount--;
	/* 함수 리뉴얼 과정에서 잠시 보류 중인 코드
	pWidget->MarkAsGarbage(); => endplay?
	*/
}

void UC_WidgetMGR::E_AddWidget(UW_WindowBase* pWidget)
{
	UPanelWidget* pMain = E_GetMainPanel();
	if (pMain)
		pMain->AddChild(pWidget);
}

void UC_WidgetMGR::E_RemoveWidget(UW_WindowBase* pWidget)
{
	UPanelWidget* pMain = E_GetMainPanel();
	if (pMain)
		pMain->RemoveChild(pWidget);
	if (pWidget)
		pWidget->RemoveFromParent();
}