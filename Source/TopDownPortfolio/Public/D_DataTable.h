#pragma once

#include "CoreMinimal.h"

class UDataTable;
class UInputMappingContext;
class UStaticMesh;
class UW_WindowBase;

namespace N_DefaultPath
{
	enum E_DataTable
	{
		E_Montage,
		E_Status,
		E_Skill,
		E_AIAction,
		E_Attack,
		E_InputAction,
		E_CollectionItemData,
		E_WindowClassData,
		E_DataTableMax
	};
	enum E_Widget
	{
		E_MainWidget,
		E_WidgetMax
	};
	enum E_InputMapping
	{
		E_InputMappingContext,
		E_InputMappingMax
	};

	enum E_ItemIDData
	{
		E_ItemTexture,
		E_ItemMesh,
		E_StaticMeshMax
	};
}

class TOPDOWNPORTFOLIO_API UD_DataTable 
{
public:

private:
	UD_DataTable() = default;
	~UD_DataTable() = default;
	
	static const TCHAR* E_GetDataTable(N_DefaultPath::E_DataTable eID);
	static const TCHAR* E_GetWidgetClass(N_DefaultPath::E_Widget eID);
	static const TCHAR* E_GetInpuMapping(N_DefaultPath::E_InputMapping eID);
public:
	static const TCHAR* E_GetItemIDDataPath(N_DefaultPath::E_ItemIDData eID);
	static UDataTable* E_GetDefault_DataTable(N_DefaultPath::E_DataTable eID);
	static UInputMappingContext* E_GetDefault_InputMappingContext(N_DefaultPath::E_InputMapping eID);
	static TSubclassOf< UW_WindowBase> E_GetDefault_UserWidgetClass(N_DefaultPath::E_Widget  eID);
};
