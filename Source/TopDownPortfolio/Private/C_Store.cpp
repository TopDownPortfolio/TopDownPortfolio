#include "C_Store.h"
#include "W_StoreSlot.h"
#include "Components/ScrollBox.h"

UC_Store::UC_Store() :
	UActorComponent{}, m_arStoreData{}, m_arWidget{}
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UC_Store::BeginPlay()
{
	UActorComponent::BeginPlay();
	FS_ItemStoreData* pSrc{};
	m_arWidget.Init(nullptr, m_arStoreData.Num());
	for (int i = 0; i < m_arWidget.Num(); i++)
	{
		pSrc = &m_arStoreData[i];
		E_CreateWidget(*pSrc, m_arWidget[i]);
	}
}

void UC_Store::E_CreateWidget(FS_ItemStoreData& sSrc, UW_StoreSlot*& pDst)
{
	pDst = Cast< UW_StoreSlot>(CreateWidget(GetWorld(), sSrc.cWidgetClass));
	pDst->E_SetStoreData(sSrc);
}

void UC_Store::E_AddToStoreWidget(UScrollBox* pScrollBox, APlayerController* pPlayer)
{
	if (!pScrollBox)
		return;
	for (UW_StoreSlot*& pWidget : m_arWidget)
	{
		pScrollBox->AddChild(pWidget);
		pWidget->E_SetInventory(pPlayer);
	}
}

void UC_Store::E_EraseStroeWidget(UScrollBox* pScrollBox)
{
	if (!pScrollBox)
		return;
	pScrollBox->ClearChildren();
}
