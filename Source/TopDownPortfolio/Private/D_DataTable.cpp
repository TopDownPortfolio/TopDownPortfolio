#include "D_DataTable.h"
#include "InputMappingContext.h"
#include "Engine/DataTable.h"
#include "Blueprint/UserWidget.h"

const TCHAR* UD_DataTable::E_GetDefault(E_DefaultPath eID)
{
	const TCHAR* pResult[E_DefaultPath::E_EnumMax]{};
	pResult[E_DefaultPath::E_Montage]			= TEXT("/Game/02_Data/DefaultData/DT-MontageData.DT-MontageData");
	pResult[E_DefaultPath::E_Status]			= TEXT("/Game/02_Data/DefaultData/DT-StatusData.DT-StatusData");
	pResult[E_DefaultPath::E_Skill]				= TEXT("/Game/02_Data/DefaultData/DT-SkillData.DT-SkillData");
	pResult[E_DefaultPath::E_InputMapping]		= TEXT("/Game/01_Blueprint/Input/IMC_Default");
	pResult[E_DefaultPath::E_AIAction]			= TEXT("/Game/02_Data/DefaultData/DT-AIAction.DT-AIAction");
	pResult[E_DefaultPath::E_MainWidget]		= TEXT("/Game/01_Blueprint/Widget/W-Main");
	return pResult[eID];
}

UDataTable* UD_DataTable::E_GetDefault_DataTable(E_DefaultPath eID)
{
	UDataTable* pResult{};
	ConstructorHelpers::FObjectFinder<UDataTable> ObejctFind(E_GetDefault(eID));
	if (ObejctFind.Succeeded())
		pResult = ObejctFind.Object;
	return pResult;
}

UInputMappingContext* UD_DataTable::E_GetDefault_InputMappingContext(E_DefaultPath eID)
{
	UInputMappingContext* pResult{};
	ConstructorHelpers::FObjectFinder<UInputMappingContext> ObejctFind(E_GetDefault(eID));
	if (ObejctFind.Succeeded())
		pResult = ObejctFind.Object;
	return pResult;
}

TSubclassOf< UUserWidget> UD_DataTable::E_GetDefault_UserWidgetClass(E_DefaultPath eID)
{
	TSubclassOf< UUserWidget> cResult{};
	ConstructorHelpers::FClassFinder<UUserWidget> ClassFind(E_GetDefault(eID));
	if (ClassFind.Succeeded())
		cResult = ClassFind.Class;
	return cResult;
}