#include "BFL_ItemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "C_ItemDataTable.h"
#include "G_GameModeBase.h"

AG_GameModeBase* UBFL_ItemLibrary::E_GetGameModeBase(const UObject* WorldContextObject)
{
	AGameModeBase* pGame = UGameplayStatics::GetGameMode(WorldContextObject);
	if (!pGame)
		return nullptr;
	return Cast<AG_GameModeBase>(pGame);
}

UC_ItemDataTable* UBFL_ItemLibrary::E_GetItemDataTable(const UObject* WorldContextObject)
{
	AG_GameModeBase* pGame = E_GetGameModeBase(WorldContextObject);
	if (!pGame)
		return nullptr;
	return pGame->E_GetItemDataTableComponent();
}

void UBFL_ItemLibrary::E_GetItemName(const UObject* WorldContextObject, FE_ItemType eItemType, int nItemID, FName& strResult)
{
	UC_ItemDataTable* pInstance = E_GetItemDataTable(WorldContextObject);
	if (!pInstance)
		return;
	strResult = pInstance->E_GetItemName(eItemType, nItemID);
}

void UBFL_ItemLibrary::E_GetItemFlag(const UObject* WorldContextObject, FE_ItemType eItemType, int nItemID, uint8& nItemFlag)
{
	UC_ItemDataTable* pInstance = E_GetItemDataTable(WorldContextObject);
	if (!pInstance)
		return;
	nItemFlag = pInstance->E_GetItemFlag(eItemType, nItemID);
}

void UBFL_ItemLibrary::E_GetItemTexture(const UObject* WorldContextObject, FE_ItemType eItemType, int nItemID, UTexture2D*& pItemTexture)
{
	UC_ItemDataTable* pInstance = E_GetItemDataTable(WorldContextObject);
	if (!pInstance)
		return;
	pItemTexture = pInstance->E_GetItemTexture(eItemType, nItemID);
}

void UBFL_ItemLibrary::E_GetItemStaticMesh(const UObject* WorldContextObject, FE_ItemType eItemType, int nItemID, UStaticMesh*& pItemStaticMesh)
{
	UC_ItemDataTable* pInstance = E_GetItemDataTable(WorldContextObject);
	if (!pInstance)
		return;
	pItemStaticMesh = pInstance->E_GetItemStaticMesh(eItemType, nItemID);
}

void UBFL_ItemLibrary::E_GetItemDesc(const UObject* WorldContextObject, FE_ItemType eItemType, int nItemID, FName& ItemDesc)
{
	UC_ItemDataTable* pInstance = E_GetItemDataTable(WorldContextObject);
	if (!pInstance)
		return;
	ItemDesc = pInstance->E_GetItemDesc(eItemType, nItemID);
}