#include "D_DataTable.h"
#include "InputMappingContext.h"
#include "Engine/DataTable.h"
#include "Blueprint/UserWidget.h"
#include "W_WindowBase.h"

const TCHAR* UD_DataTable::E_GetDataTable(N_DefaultPath::E_DataTable eID)
{
	using namespace N_DefaultPath;
	const TCHAR* pResult[E_DataTable::E_DataTableMax]{};
	pResult[E_DataTable::E_Montage]					= TEXT("/Game/02_Data/DefaultData/DT-MontageData.DT-MontageData");
	pResult[E_DataTable::E_Status]					= TEXT("/Game/02_Data/DefaultData/DT-StatusData.DT-StatusData");
	pResult[E_DataTable::E_Skill]					= TEXT("/Game/02_Data/DefaultData/DT-SkillData.DT-SkillData");
	pResult[E_DataTable::E_AIAction]				= TEXT("/Game/02_Data/DefaultData/DT-AIAction.DT-AIAction");
	pResult[E_DataTable::E_Attack]					= TEXT("/Game/02_Data/DefaultData/DT-AttackData.DT-AttackData");
	pResult[E_DataTable::E_InputAction]				= TEXT("/Game/02_Data/DefaultData/DT-InputActionData.DT-InputActionData");
	pResult[E_DataTable::E_CollectionItemData]		= TEXT("/Game/02_Data/Item/DataTable/DT-ItemCollectionData.DT-ItemCollectionData");
	pResult[E_DataTable::E_WindowClassData]			= TEXT("/Game/02_Data/DefaultData/DT-WindowClassData.DT-WindowClassData");
	pResult[E_DataTable::E_MoneyData]				= TEXT("/Game/02_Data/Item/DataTable/DT-ItemMoneyData.DT-ItemMoneyData");
	pResult[E_DataTable::E_EquipItemData]			= TEXT("/Game/02_Data/Item/DataTable/DT-ItemEquipData.DT-ItemEquipData");
	return pResult[eID];
}

const TCHAR* UD_DataTable::E_GetInpuMapping(N_DefaultPath::E_InputMapping eID)
{
	using namespace N_DefaultPath;
	const TCHAR* pResult[E_InputMapping::E_InputMappingMax]{};
	pResult[E_InputMapping::E_InputMappingContext] = TEXT("/Game/02_Data/Input/IMC-TopDownPlayer");
	return  pResult[eID];
}

const TCHAR* UD_DataTable::E_GetItemIDDataPath(N_DefaultPath::E_ItemIDData eID)
{
	using namespace N_DefaultPath;
	const TCHAR* pResult[E_ItemIDData::E_StaticMeshMax]{};
	pResult[E_ItemIDData::E_ItemTexture] = TEXT("/Game/02_Data/Item/StaticMesh/helmet");
	pResult[E_ItemIDData::E_ItemMesh] = TEXT("/Game/02_Data/Item/StaticMesh/helmet");
	return  pResult[eID];
}

UDataTable* UD_DataTable::E_GetDefault_DataTable(N_DefaultPath::E_DataTable eID)
{
	UDataTable* pResult{};
	ConstructorHelpers::FObjectFinder<UDataTable> ObejctFind(E_GetDataTable(eID));
	if (ObejctFind.Succeeded())
		pResult = ObejctFind.Object;
	return pResult;
}

UInputMappingContext* UD_DataTable::E_GetDefault_InputMappingContext(N_DefaultPath::E_InputMapping eID)
{
	UInputMappingContext* pResult{};
	ConstructorHelpers::FObjectFinder<UInputMappingContext> ObejctFind(E_GetInpuMapping(eID));
	if (ObejctFind.Succeeded())
		pResult = ObejctFind.Object;
	return pResult;
}

//TSubclassOf<UW_WindowBase> UD_DataTable::E_GetDefault_UserWidgetClass(N_DefaultPath::E_Widget eID)
//{
//	TSubclassOf< UW_WindowBase> cResult{};
//	ConstructorHelpers::FClassFinder<UW_WindowBase> ClassFind(E_GetWidgetClass(eID));
//	if (ClassFind.Succeeded())
//		cResult = ClassFind.Class;
//	return cResult;
//}
