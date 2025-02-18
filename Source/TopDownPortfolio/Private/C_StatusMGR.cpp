#include "C_StatusMGR.h"
#include "D_DataTable.h"

UC_StatusMGR::UC_StatusMGR() :
	UActorComponent{}, m_pDataTable{}, m_arStatus{}
{
	PrimaryComponentTick.bCanEverTick = false;
	m_pDataTable = UD_DataTable::E_GetDefault_DataTable(UD_DataTable::E_DefaultPath::E_Status);
	for (uint8 i = 0; i < (uint8)FE_StatusID::E_EnumMAX; i++)
	{
		E_GetClass((FE_StatusID)i)->E_SetID((FE_StatusID)i);
	}
}

void UC_StatusMGR::BeginPlay()
{
	E_Init_Begin();
	UActorComponent::BeginPlay();
}

E_Status* UC_StatusMGR::E_GetClass(FE_StatusID eID)
{
	FE_StatusID eResult = FE_StatusID::E_NONE;
	if (eID < FE_StatusID::E_EnumMAX)
		eResult = eID;
	return &m_arStatus[(uint8)eResult];
}

float UC_StatusMGR::E_GetStatus(FE_StatusID eID, FE_StatusType eType)
{
	return E_GetClass(eID)->E_GetValue(eType);
}

void UC_StatusMGR::E_SetStatus(FE_StatusID eID, FE_StatusType eType, float fValue)
{
	E_GetClass(eID)->E_SetValue(eType, fValue);
}

void UC_StatusMGR::E_AddStatus(FE_StatusID eID, FE_StatusType eType, float fValue)
{
	E_GetClass(eID)->E_AddValue(eType, fValue);
}

void UC_StatusMGR::E_Init_Begin()
{
	if (m_pDataTable)
	{
		TArray< FS_StatusData*> arData{};
		m_pDataTable->GetAllRows< FS_StatusData>("", arData);
		for (FS_StatusData*& pData : arData)
		{
			E_SetStatus(pData->eID, pData->eType, pData->fValue);
		}
	}
}

float UC_StatusMGR::E_GetStatus_Current(FE_StatusID eID)
{
	return E_GetStatus(eID, FE_StatusType::E_Current);
}

float UC_StatusMGR::E_GetStatus_Ratio(FE_StatusID eID)
{
	float fResult{};
	float fMax = E_GetStatus(eID, FE_StatusType::E_ValueMAX);
	if (fMax != 0.0f)
		fResult = E_GetStatus_Current(eID) / fMax;
	return  fResult;
}

float UC_StatusMGR::E_GetStatus_Max(FE_StatusID eID)
{
	return E_GetStatus(eID, FE_StatusType::E_ValueMAX);
}

void UC_StatusMGR::E_SetStatus_Current(FE_StatusID eID, float fValue)
{
	E_SetStatus(eID, FE_StatusType::E_Current, fValue);
}

void UC_StatusMGR::E_SetStatus_Max(FE_StatusID eID, float fValue)
{
	E_SetStatus(eID, FE_StatusType::E_ValueMAX, fValue);
}

void UC_StatusMGR::E_AddStatus_Current(FE_StatusID eID, float fValue)
{
	E_AddStatus(eID, FE_StatusType::E_Current, fValue);
}

void UC_StatusMGR::E_AddStatus_Max(FE_StatusID eID, float fValue)
{
	E_AddStatus(eID, FE_StatusType::E_ValueMAX, fValue);
}

bool UC_StatusMGR::E_CheckAdd(FE_StatusID eID, float fValue)
{
	float fMin = 0.0f;
	float fApplyValue = E_GetStatus_Current(eID) + fValue;
	float fMax = E_GetStatus_Max(eID);
	return fMin <= fApplyValue && fApplyValue <= fMax;
}
