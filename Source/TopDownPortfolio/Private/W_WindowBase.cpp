#include "W_WindowBase.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanelSlot.h"
#include "Widgets/Layout/Anchors.h"

UW_WindowBase::UW_WindowBase(const FObjectInitializer& ObjectInitializer) :
	UUserWidget{ ObjectInitializer }, m_vAnchors{}, m_vWidgetPosition{}, m_vWidgetSize{}, m_eWindowID{}
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
