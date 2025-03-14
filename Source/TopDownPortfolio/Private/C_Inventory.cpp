#include "C_Inventory.h"
#include "W_ItemSlot.h"
#include "BFL_ItemLibrary.h"


UC_Inventory::UC_Inventory() :
	UActorComponent{}, m_arItemSlot{}, m_arMoneySlot{}, m_arInventorySlot{}, m_pDummySlot{}
{
	using namespace std;
	PrimaryComponentTick.bCanEverTick = false;
	m_arItemSlot[0].resize(1, vector<S_ItemSlot>(1));
	m_arInventorySlot[0] = &m_arItemSlot[0];
	m_arInventorySlot[(uint8)FE_ItemType::E_ItemSlotMAX] = &m_arItemSlot[0];

	for (uint8 k = 1; k < (uint8)FE_ItemType::E_ItemSlotMAX; k++)
	{
		m_arItemSlot[k].resize(E_ArSize::E_ItemSlotY, vector<S_ItemSlot>(E_ArSize::E_ItemSlotX));
		m_arInventorySlot[k] = &m_arItemSlot[k];
	}
	m_arMoneySlot.resize(1, vector<S_ItemSlot>((uint8)FE_MoneyType::E_EnumMAX));
	m_arInventorySlot[(uint8)FE_ItemType::E_Money] = &m_arMoneySlot;

	for (uint8 k = 1; k < (uint8)FE_ItemType::E_ItemSlotMAX; k++)
	{
		for (int i = 0; i < E_ArSize::E_ItemSlotY; i++)
		{
			for (int j = 0; j < E_ArSize::E_ItemSlotX; j++)
			{
				S_ItemSlot* pSlot = E_GetInventroySlot((FE_ItemType)k, i, j);
				pSlot->sInstanceData.eItemType = (FE_ItemType)k;
				pSlot->nIndexY = i;
				pSlot->nIndexX = j;
			}
		}
	}
}

void UC_Inventory::BeginPlay()
{
	UActorComponent::BeginPlay();
	m_pDummySlot.pWidget = CreateWidget<UW_ItemSlot>(Cast<APlayerController>( GetOwner()));
}

UC_Inventory::S_ItemSlot* UC_Inventory::E_GetSameItemIDSlot(FE_ItemType eItemType, int nItemID)
{
	S_ItemSlot* pResult{};
	for (int i = 0; i < E_ArSize::E_ItemSlotY && pResult == nullptr; i++)
	{
		for (int j = 0; j < E_ArSize::E_ItemSlotX && pResult == nullptr; j++)
		{
			S_ItemSlot* pSlot = E_GetInventroySlot(eItemType, i, j);
			if (pSlot->sInstanceData.nItemID == nItemID)
				pResult = pSlot;
		}
	}
	return pResult;
}

UC_Inventory::S_ItemSlot* UC_Inventory::E_GetInventroySlot(FE_ItemType eItemType, int nIndexY, int nIndexX)
{
	using namespace std;
	S_ItemSlot* pReusult{};
	vector<vector<S_ItemSlot>>* arSlot = m_arInventorySlot[(uint8)eItemType];
	if (arSlot->size() > nIndexY && (*arSlot)[0].size() > nIndexX)
	{
		pReusult = &(*arSlot)[nIndexY][nIndexX];
	}
	if (!pReusult)
		pReusult = &(*arSlot)[0][0];
	return  pReusult;
}

void UC_Inventory::E_MergeSlot(S_ItemSlot* pSrc, S_ItemSlot* pDst)
{
	if (!pSrc || !pDst)
		return;
	pDst->sInstanceData.nItemCount += pSrc->sInstanceData.nItemCount;
	pSrc->sInstanceData.nItemID = 0;
	pSrc->sInstanceData.nItemCount = 0;
}

void UC_Inventory::E_SetDummy(FE_ItemType eItemType, int nItemID, int nItemCount)
{
	m_pDummySlot.sInstanceData.eItemType = eItemType;
	m_pDummySlot.sInstanceData.nItemID = nItemID;
	m_pDummySlot.sInstanceData.nItemCount = nItemCount;
}

void UC_Inventory::E_SwitchSlot(S_ItemSlot* pSrc, S_ItemSlot* pDst)
{
	Swap<FE_ItemType>(pSrc->sInstanceData.eItemType, pDst->sInstanceData.eItemType);
	Swap<int>(pSrc->sInstanceData.nItemID, pDst->sInstanceData.nItemID);
	Swap<int>(pSrc->sInstanceData.nItemCount, pDst->sInstanceData.nItemCount);
}

void UC_Inventory::E_UpdateSlot(S_ItemSlot* pSlot)
{
	if (pSlot->pWidget)
		pSlot->pWidget->E_UpdateItem();
}

void UC_Inventory::E_GetSameSlots(FE_ItemType eItemType, int nItemID, std::vector<S_ItemSlot*>& arSlots, int& nCounts)
{
	using namespace std;
	arSlots.reserve(100);
	nCounts = 0;
	vector<vector<S_ItemSlot>>* arSlot = m_arInventorySlot[(uint8)eItemType];
	int nMaxY = arSlot->size();;
	int nMaxX = arSlot[0].size();
	for (int i = 0; i < nMaxY; i++)
	{
		for (int j = 0; j < nMaxX; j++)
		{
			S_ItemSlot* pSlot = E_GetInventroySlot(eItemType, i, j);
			if (pSlot->sInstanceData.nItemID == nItemID)
			{
				arSlots.push_back(pSlot);
				nCounts += pSlot->sInstanceData.nItemCount;
			}
		}
	}
}

int UC_Inventory::E_GetItemTotalCount(const FS_ItemInstanceData& sInstanceData)
{
	int nCounts = 0;
	E_GetItemTotalCount(sInstanceData.eItemType, sInstanceData.nItemID, nCounts);
	return nCounts;
}

void UC_Inventory::E_GetItemTotalCount(FE_ItemType eItemType, int nItemID, int& nCounts)
{
	using namespace std;
	nCounts = 0;
	vector<vector<S_ItemSlot>>* arSlot = m_arInventorySlot[(uint8)eItemType];
	int nMaxY = arSlot->size();;
	int nMaxX = arSlot[0].size();
	for (int i = 0; i < nMaxY; i++)
	{
		for (int j = 0; j < nMaxX; j++)
		{
			S_ItemSlot* pSlot = E_GetInventroySlot(eItemType, i, j);
			if (pSlot->sInstanceData.nItemID == nItemID)
			{
				nCounts += pSlot->sInstanceData.nItemCount;
			}
		}
	}
}

int UC_Inventory::E_GetItemCounts(FE_ItemType eItemType, int nIndexY, int nIndexX)
{
	return E_GetInventroySlot(eItemType, nIndexY, nIndexX)->sInstanceData.nItemCount;
}

int UC_Inventory::E_GetItemID(FE_ItemType eItemType, int nIndexY, int nIndexX)
{
	return E_GetInventroySlot(eItemType, nIndexY, nIndexX)->sInstanceData.nItemID;
}

bool UC_Inventory::E_PushItem(FS_ItemInstanceData* sInstanceData)
{
	int nItemID = sInstanceData->nItemID;
	int nCount = sInstanceData->nItemCount;
	FE_ItemType eItemType = sInstanceData->eItemType;
	uint8 nType = (uint8)eItemType;
	S_ItemSlot* pDst = E_GetSameItemIDSlot(eItemType);
	bool bMerge{};
	if(UBFL_ItemLibrary::E_GetCheckItemFlag(this, sInstanceData->eItemType, nItemID, FE_ItemManageabilityFlag::E_Bundlable))
	{
		S_ItemSlot* pTemp = E_GetSameItemIDSlot(eItemType, nItemID);
		if (pTemp)
			pDst = pTemp;
		bMerge = true;
	}
	if (!pDst)
		return false;
	// 더미에 넣고  1. 같은 솔롯은 더하거나 / 2. 빈 슬롯과 교체 하거나
	E_SetDummy(eItemType, nItemID, nCount);
	if (bMerge)
		E_SetDummy(eItemType, nItemID, nCount + pDst->sInstanceData.nItemCount);
	E_SwitchSlot(&m_pDummySlot, pDst);
	E_UpdateSlot(pDst);
	return true;
}

bool UC_Inventory::E_PushItem(FS_ItemInstanceData sInstanceData)
{
	return E_PushItem(&sInstanceData);
}

bool UC_Inventory::E_PopItem(FS_ItemInstanceData* sInstanceData, int& nRemainCount)
{
	using namespace std;
	FE_ItemType eItemType = sInstanceData->eItemType;
	int nItemID = sInstanceData->nItemID;
	int nCount = sInstanceData->nItemCount;
	uint8 nType = (uint8)eItemType;
	vector<S_ItemSlot*> arSlots{};
	int nTotal{};
	E_GetSameSlots(eItemType, nItemID, arSlots, nTotal);
	if (nTotal < nCount)
		return false;
	S_ItemSlot* pSlot{};
	nRemainCount = nTotal;
	for (int i = 0 ; i < arSlots.size() && nCount > 0; i++)
	{
		pSlot = arSlots[i];
		int nSubCount = pSlot->sInstanceData.nItemCount;
		int nNextID{};
		if (eItemType == FE_ItemType::E_Money)
			nNextID = nItemID;
		int nNextCount{};
		if (nSubCount > nCount)
		{
			nSubCount = nCount;
			nNextID = nItemID;
			nNextCount = pSlot->sInstanceData.nItemCount - nCount;
		}
		nCount -= nNextCount;
		E_SetDummy(eItemType, nNextID, nNextCount);
		E_SwitchSlot(pSlot, &m_pDummySlot);
		E_UpdateSlot(pSlot);
	}
	nRemainCount -= sInstanceData->nItemCount;
	//E_GetItemTotalCount(eItemType, nItemID, nRemainCount);
	return true;
}

bool UC_Inventory::E_RemoveItem(UW_ItemSlot* pWidget)
{
	if (!pWidget)
		return false;
	FE_ItemType eItemType = pWidget->E_GetItemType();
	S_ItemSlot* pDstSlot = E_GetInventroySlot(eItemType, pWidget->E_GetSlotIndexY(), pWidget->E_GetSlotIndexX());
	E_SetDummy(eItemType);
	E_SwitchSlot(pDstSlot, &m_pDummySlot);
	E_UpdateSlot(pDstSlot);
	return 	true;
}


bool UC_Inventory::E_PopItem(FS_ItemInstanceData sInstanceData, int& nRemainCount)
{
	return E_PopItem(&sInstanceData, nRemainCount);
}

bool UC_Inventory::E_Switch(UW_ItemSlot* pSrc, UW_ItemSlot* pDst)
{
	if (!pSrc || pSrc == pDst)
		return false;
	if (!pDst || pSrc->E_GetItemType() != pDst->E_GetItemType())
		return false;
	S_ItemSlot* pSrcSlot = E_GetInventroySlot(pSrc->E_GetItemType(), pSrc->E_GetSlotIndexY(), pSrc->E_GetSlotIndexX());
	S_ItemSlot* pDstSlot = E_GetInventroySlot(pDst->E_GetItemType(), pDst->E_GetSlotIndexY(), pDst->E_GetSlotIndexX());
	bool bBundleable = UBFL_ItemLibrary::E_GetCheckItemFlag(this, pSrc->E_GetItemType(), pSrcSlot->sInstanceData.nItemID, FE_ItemManageabilityFlag::E_Bundlable);
	if (pSrcSlot->sInstanceData.nItemID == pDstSlot->sInstanceData.nItemID && bBundleable)
	{
		E_MergeSlot(pSrcSlot, pDstSlot);
	}
	E_SwitchSlot(pSrcSlot, pDstSlot);
	E_UpdateSlot(pSrcSlot);
	E_UpdateSlot(pDstSlot);
	return true;
}

void UC_Inventory::E_CreateInventoryWidget(UUniformGridPanel* pGridPanel, FE_ItemType eItemType, TSubclassOf<UW_ItemSlot> wSlot)
{
	APlayerController* pPlayer = Cast<APlayerController>(GetOwner());
	for (int i = 0; i < E_GetSlotSizeY(); i++)
	{
		for (int j = 0; j < E_GetSlotSizeX(); j++)
		{
			UW_ItemSlot* pSlot = Cast< UW_ItemSlot>(CreateWidget(pPlayer, wSlot));
			if (pSlot)
			{
				pSlot->E_InitItemSlot(eItemType, i, j);
				pGridPanel->AddChildToUniformGrid(pSlot, i, j);
				E_GetInventroySlot(eItemType, i, j)->pWidget = pSlot;
			}
		}
	}
}

void UC_Inventory::E_SetMoneySlot(UUniformGridPanel* pGridPanel)
{
	if (!pGridPanel)
		return;
	TArray<UWidget*> arWidget = pGridPanel->GetAllChildren();
	for (UWidget* pWdiget : arWidget)
	{
		UW_ItemSlot* pSlot = Cast<UW_ItemSlot>(pWdiget);
		if (pSlot)
		{
			E_GetInventroySlot(pSlot->E_GetItemType(), pSlot->E_GetSlotIndexY(), pSlot->E_GetSlotIndexX())->pWidget = pSlot;
		}
	}
}
