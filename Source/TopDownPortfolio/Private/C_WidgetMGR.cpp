#include "C_WidgetMGR.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Blueprint/WidgetBlueprintLibrary.h"


UC_WidgetMGR::UC_WidgetMGR() :
	UActorComponent{}, m_pController{}, m_cMain{}, m_pMain{}, m_pMainPanel{} , m_mapWindow{}, m_arWidgetData{}, m_arWidgetStack{}, m_nStackCount{}
{
	PrimaryComponentTick.bCanEverTick = false;

	ConstructorHelpers::FClassFinder<UUserWidget> ObejctFind(TEXT("/Game/01_Blueprint/Widget/W-Main"));
	// /Script/UMGEditor.WidgetBlueprint'/Game/01_Blueprint/Widgm_arWidgetStack[(uint8)FE_WindowID::E_EnumMAX];

	if (ObejctFind.Succeeded())
		m_cMain = ObejctFind.Class;
	m_nStackCount = -1;
}


void UC_WidgetMGR::BeginPlay()
{
	UActorComponent::BeginPlay();
	m_pController = Cast<APlayerController>(GetOwner());
	if (!m_pController || !m_cMain)
	{
		DestroyComponent();
		return;
	}
	if (m_cMain)
	{
		m_pMain = E_CreateWidget(m_cMain);
		m_pMain->AddToViewport();
	}
	for (uint8 i = (uint8)FE_WindowID::E_NONE + 1; i < (uint8)FE_WindowID::E_EnumMAX; i++)
	{
		FE_WindowID eWindowID = (FE_WindowID)i;
		TSubclassOf<UUserWidget>* pcWidget = m_mapWindow.Find(eWindowID);
		if (pcWidget)
			m_arWidgetData[i].pWidget = E_CreateWidget(*pcWidget);
	}
}
UPanelWidget* UC_WidgetMGR::E_GetMainPanel()
{
	if (!m_pMainPanel)
		m_pMainPanel = Cast<UPanelWidget>(m_pMain->WidgetTree->RootWidget);
	return m_pMainPanel;
}

UUserWidget* UC_WidgetMGR::E_CreateWidget(TSubclassOf<UUserWidget> cWidget)
{
	return CreateWidget(m_pController, cWidget);
}

bool UC_WidgetMGR::E_CheckWindow(FE_WindowID eWindowID)
{
	return m_arWidgetData[(uint8)eWindowID].pWidget != nullptr;
}

void UC_WidgetMGR::E_Register(FE_WindowID eWindowID, UUserWidget* pWidget)
{
	m_arWidgetData[(uint8)eWindowID].pWidget = pWidget;
}

void UC_WidgetMGR::E_RegisterWidget(FE_WindowID eWindowID)
{
	if (m_nStackCount == (uint8)FE_WindowID::E_EnumMAX || !E_CheckWindow(eWindowID))
		return;
	UUserWidget* pRefWidget = m_arWidgetData[(uint8)eWindowID].pWidget;
	E_Register(eWindowID, pRefWidget);
	E_AddWidget(pRefWidget);
	m_nStackCount++;
	m_arWidgetStack[m_nStackCount] = eWindowID;
}

void UC_WidgetMGR::E_UnRegisterWidget()
{
	if (m_nStackCount < 0)
		return;
	FE_WindowID eWindowID = m_arWidgetStack[m_nStackCount];
	UUserWidget* pWidget = m_arWidgetData[(uint8)eWindowID].pWidget;
	E_RemoveWidget(pWidget);
	m_nStackCount--;
	/* 함수 리뉴얼 과정에서 잠시 보류 중인 코드
	pWidget->MarkAsGarbage(); => endplay?
	*/
}

void UC_WidgetMGR::E_AddWidget(UUserWidget* pWidget)
{
	UPanelWidget* pMain = E_GetMainPanel();
	pMain->AddChild(pWidget);
}

void UC_WidgetMGR::E_RemoveWidget(UUserWidget* pWidget)
{
	UPanelWidget* pMain = E_GetMainPanel();
	pMain->RemoveChild(pWidget);
	if (pWidget)
		pWidget->RemoveFromParent();
}