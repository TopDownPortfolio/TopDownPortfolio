#pragma once

#include "CoreMinimal.h"

class UDataTable;
class UInputMappingContext;
class UUserWidget;

class TOPDOWNPORTFOLIO_API UD_DataTable 
{
public:
	enum E_DefaultPath
	{
		E_None,
		E_Montage,
		E_Status,
		E_Skill,
		E_InputMapping,
		E_AIAction,
		E_MainWidget,
		E_Attack,
		E_EnumMax
	};
private:
	UD_DataTable() = default;
	~UD_DataTable() = default;
	
	static const TCHAR* E_GetDefault(E_DefaultPath eID);
public:
	static UDataTable* E_GetDefault_DataTable(E_DefaultPath eID);
	static UInputMappingContext* E_GetDefault_InputMappingContext(E_DefaultPath eID);
	static TSubclassOf< UUserWidget> E_GetDefault_UserWidgetClass(E_DefaultPath eID);
};
