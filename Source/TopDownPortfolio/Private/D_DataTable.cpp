#include "D_DataTable.h"
#include "InputMappingContext.h"
#include "Engine/DataTable.h"
#include "Blueprint/UserWidget.h"

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