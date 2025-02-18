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
		E_EnumMax
	};
private:
	UD_DataTable() = default;
	~UD_DataTable() = default;
	
	static const TCHAR* E_GetDefault(E_DefaultPath eID)
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
public:
	static UDataTable* E_GetDefault_DataTable(E_DefaultPath eID);
	static UInputMappingContext* E_GetDefault_InputMappingContext(E_DefaultPath eID);
	static TSubclassOf< UUserWidget> E_GetDefault_UserWidgetClass(E_DefaultPath eID);
};
