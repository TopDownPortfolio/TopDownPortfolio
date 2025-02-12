#include "O_Buff_Status.h"
#include "A_Character_Base.h"
#include "C_StatusMGR.h"

UO_Buff_Status::UO_Buff_Status() :
	UO_Buff_Base{}, m_pOwner{}, m_eStatuID{}, m_fValuePerSecond{}
{
}

void UO_Buff_Status::E_SetBuffData(FS_BuffData const& sData)
{
	E_SetDefault(sData);
	FS_BuffData_Status* const pStatus = (FS_BuffData_Status*)&sData;
	if (pStatus)
	{
		m_pOwner = pStatus->pCharacter;
		m_eStatuID = pStatus->eStatuID;
		m_fValuePerSecond = pStatus->fRegenerationRate;
	}
}

void UO_Buff_Status::E_TimerFunction()
{
	if (!m_pOwner)
		return;
	UC_StatusMGR* pMGR = m_pOwner->E_GetStatusMGR();
	if (pMGR->E_CheckAdd(m_eStatuID, m_fValuePerSecond))
	{
		pMGR->E_AddStatus_Current(m_eStatuID, m_fValuePerSecond);
	}
}
