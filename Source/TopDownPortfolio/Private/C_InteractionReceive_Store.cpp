#include "C_InteractionReceive_Store.h"
#include "A_PlayerController.h"
#include "W_Store.h"
#include "A_Interaction.h"
#include "C_Store.h"

UC_InteractionReceive_Store::UC_InteractionReceive_Store() : 
    UC_InteractionReceive{}, m_pStore{}, m_pStoreWidget{}, m_pWidgetMGR{}
{
    m_bDetectTogle = true;
}

void UC_InteractionReceive_Store::BeginPlay()
{
    UC_InteractionReceive::BeginPlay();
    AA_Interaction* pActor = Cast<AA_Interaction>(GetOwner());
    if (!pActor)
    {
        DestroyComponent();
        return;
    }
    m_pStore = Cast<UC_Store>(pActor->E_GetActionComponent());
}

bool UC_InteractionReceive_Store::E_EndEvent_Detect_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (m_pStoreWidget && m_pStore)
    {
        m_pStore->E_EraseStroeWidget( m_pStoreWidget->E_GetScrollBox());
        //m_pWidgetMGR->E_UnRegisterWidget(FE_WindowID::E_Inventory);
        m_pWidgetMGR->E_UnRegisterWidget(FE_WindowID::E_ItemStore);
        return true;
    }
    return false;
}

bool UC_InteractionReceive_Store::E_InteractionEvent_Implementation(AActor* pInitiator)
{
    APawn* pPawn = Cast<APawn>(pInitiator);
    if (!pPawn || !m_pStore)
        return false;
    AA_PlayerController* pController = Cast< AA_PlayerController>(pPawn->Controller);
    if (!pController)
        return false;
    m_pWidgetMGR = pController->E_GetWidgetMGR();
    m_pStoreWidget = Cast< UW_Store>(m_pWidgetMGR->E_GetWidget(FE_WindowID::E_ItemStore));
    if (!m_pStoreWidget)
        return false;
    m_pStore->E_AddToStoreWidget(m_pStoreWidget->E_GetScrollBox(), pController);
    if (!m_pWidgetMGR->E_CheckRegistered(FE_WindowID::E_Inventory))
        m_pWidgetMGR->E_RegisterWidget(FE_WindowID::E_Inventory);
    if (!m_pWidgetMGR->E_CheckRegistered(FE_WindowID::E_ItemStore))
        m_pWidgetMGR->E_RegisterWidget(FE_WindowID::E_ItemStore);

    return true;
}
