#include "W_WindowBase.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanelSlot.h"
#include "Widgets/Layout/Anchors.h"
#include "A_PlayerController.h"

UW_WindowBase::UW_WindowBase(const FObjectInitializer& ObjectInitializer) :
	UUserWidget{ ObjectInitializer }, m_vAnchors{}, m_vWidgetPosition{}, m_vWidgetSize{}, m_eWindowID{}, m_pWidgetMGR{}
{
	
}

FVector2D& UW_WindowBase::E_GetSettingVector2D(FE_WindowSetting eSettingID)
{
	FVector2D* arVector[(uint8)FE_WindowSetting::E_EnumMax]{};
	arVector[(uint8)FE_WindowSetting::E_AnchorsMin]				= &m_vAnchors.Minimum;
	arVector[(uint8)FE_WindowSetting::E_AnchorsMax]				= &m_vAnchors.Maximum;
	arVector[(uint8)FE_WindowSetting::E_WidgetPosition]			= &m_vWidgetPosition;
	arVector[(uint8)FE_WindowSetting::E_WidgetSize]				= &m_vWidgetSize;
	return *arVector[(uint8)eSettingID];
}

void UW_WindowBase::NativePreConstruct()
{
	UUserWidget::NativePreConstruct();
	UCanvasPanelSlot* pOwner = Cast<UCanvasPanelSlot>(Slot);
	if (pOwner)
	{
		pOwner->SetAnchors(m_vAnchors);
		pOwner->SetPosition(E_GetSettingVector2D(FE_WindowSetting::E_WidgetPosition));
		pOwner->SetSize(E_GetSettingVector2D(FE_WindowSetting::E_WidgetSize));
	}
}

void UW_WindowBase::NativeOnInitialized()
{
	UUserWidget::NativeOnInitialized();
	AA_PlayerController* pPlayer = Cast<AA_PlayerController>(GetOwningPlayer());
	if (!pPlayer)
		return;
	m_pWidgetMGR = pPlayer->E_GetWidgetMGR();
}

FReply UW_WindowBase::NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent)
{
	if (m_pWidgetMGR)
		m_pWidgetMGR->E_SetFocus(m_eWindowID);
	return UUserWidget::NativeOnFocusReceived(InGeometry, InFocusEvent);
}
