#include "D_DataTable.h"
#include "InputMappingContext.h"
#include "Engine/DataTable.h"
#include "Blueprint/UserWidget.h"

const TCHAR* UD_DataTable::E_GetDataTable(N_DefaultPath::E_DataTable eID)
{
	using namespace N_DefaultPath;
	const TCHAR* pResult[E_DataTable::E_DataTableMax]{};
	pResult[E_DataTable::E_Montage] = TEXT("/Game/02_Data/DefaultData/DT-MontageData.DT-MontageData");
	pResult[E_DataTable::E_Status] = TEXT("/Game/02_Data/DefaultData/DT-StatusData.DT-StatusData");
	pResult[E_DataTable::E_Skill] = TEXT("/Game/02_Data/DefaultData/DT-SkillData.DT-SkillData");
	pResult[E_DataTable::E_AIAction] = TEXT("/Game/02_Data/DefaultData/DT-AIAction.DT-AIAction");
	pResult[E_DataTable::E_Attack] = TEXT("/Game/02_Data/DefaultData/DT-AttackData.DT-AttackData");
	pResult[E_DataTable::E_InputAction] = TEXT("/Game/02_Data/DefaultData/DT-InputActionData.DT-InputActionData");
	return pResult[eID];
}

const TCHAR* UD_DataTable::E_GetWidgetClass(N_DefaultPath::E_Widget eID)
{
	using namespace N_DefaultPath;
	const TCHAR* pResult[E_Widget::E_WidgetMax]{};
	pResult[E_Widget::E_MainWidget] = TEXT("/Game/01_Blueprint/Widget/W-Main");
	return  pResult[eID];
}

const TCHAR* UD_DataTable::E_GetInpuMapping(N_DefaultPath::E_InputMapping eID)
{
	using namespace N_DefaultPath;
	const TCHAR* pResult[E_InputMapping::E_InputMappingMax]{};
	pResult[E_InputMapping::E_InputMappingContext] = TEXT("/Game/02_Data/Input/IMC-TopDownPlayer");
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

TSubclassOf<UUserWidget> UD_DataTable::E_GetDefault_UserWidgetClass(N_DefaultPath::E_Widget eID)
{
	TSubclassOf< UUserWidget> cResult{};
	ConstructorHelpers::FClassFinder<UUserWidget> ClassFind(E_GetWidgetClass(eID));
	if (ClassFind.Succeeded())
		cResult = ClassFind.Class;
	return cResult;
}
