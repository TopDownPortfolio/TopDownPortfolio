#include "C_WidgetMGR.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Blueprint/WidgetBlueprintLibrary.h"


UC_WidgetMGR::UC_WidgetMGR() :
	UActorComponent{}, m_pController{}, m_cMain{}, m_mapWidget{}, m_pMain{}, m_mapWindow{}, m_arWidgetData{}, m_nOpenWidgetCount{}
{
	PrimaryComponentTick.bCanEverTick = false;
	m_mapWidget.Reserve(20);

	ConstructorHelpers::FClassFinder<UUserWidget> ObejctFind(TEXT("/Game/01_Blueprint/Widget/W-Main"));
	// /Script/UMGEditor.WidgetBlueprint'/Game/01_Blueprint/Widget/W-Main.W-Main'

	if (ObejctFind.Succeeded())
		m_cMain = ObejctFind.Class;
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
		m_pMain = CreateWidget(m_pController, m_cMain);
		m_pMain->AddToViewport();
	}
}

void UC_WidgetMGR::E_Add(UUserWidget* pWidget)
{
	if (!m_pMain)
		return;
	m_mapWidget.Add(pWidget);
}

void UC_WidgetMGR::E_Remove(UUserWidget* pWidget)
{
	m_mapWidget.Remove(pWidget);
}

UPanelWidget* UC_WidgetMGR::E_GetMainPannel()
{
	return Cast<UPanelWidget>(m_pMain->WidgetTree->RootWidget);
}

void UC_WidgetMGR::E_RegisterWidget(FE_WindowID eID)
{
	TSubclassOf<UUserWidget>* pcWidget = m_mapWindow.Find(eID);
	if (!pcWidget || m_arWidgetData[(uint8)eID].pWidget)
		return;
	m_nOpenWidgetCount++;
	if (m_nOpenWidgetCount == 1)
	{
		//UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(m_pController, m_pMain);
		m_pController->StopMovement();
	}
	UUserWidget* pWidget = E_RegisterWidget(*pcWidget);
	m_arWidgetData[(uint8)eID].pWidget = pWidget;
	m_mapWidget.Add({ pWidget, &m_arWidgetData[(uint8)eID] });
}

UUserWidget* UC_WidgetMGR::E_RegisterWidget(TSubclassOf<UUserWidget> cWidget)
{
	UUserWidget* pWidget = CreateWidget(m_pController, cWidget);
	UPanelWidget* pMain = E_GetMainPannel();
	if (pMain)
		pMain->AddChild(pWidget);
	return pWidget;
}

void UC_WidgetMGR::E_UnRegisterWidget(UUserWidget* pWidget)
{
	UPanelWidget* pMain = E_GetMainPannel();
	m_nOpenWidgetCount--;
	if (m_nOpenWidgetCount == 0)
	{
		//UWidgetBlueprintLibrary::SetInputMode_GameOnly(m_pController);
	}
	if (pMain)
		pMain->RemoveChild(pWidget);
	pWidget->RemoveFromParent();
	(*m_mapWidget.Find(pWidget))->pWidget = nullptr;
	m_mapWidget.Remove(pWidget);
	pWidget->MarkAsGarbage();
	//CollectGarbage();

}