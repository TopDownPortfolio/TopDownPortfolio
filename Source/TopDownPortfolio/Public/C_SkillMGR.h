#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "E_Skill.h"
#include "S_Skill.h"
#include "C_SkillMGR.generated.h"

class AA_Character_Base;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TOPDOWNPORTFOLIO_API UC_SkillMGR : public UActorComponent
{
	GENERATED_BODY()
protected:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDL_OnAction, FE_SkillID, eSkillID, bool, bIsActionActive);
	struct S_CurrentData
	{
		FE_SkillID eSkillID;
		uint8 nSkillIndex;
		int nPlayIndex;
		int nIndex;
	};
protected:
	AA_Character_Base* m_pOwner;
	UPROPERTY(EditDefaultsOnly, Category = Data, meta = (AllowPrivateAccess = "true"))
	UDataTable* m_pDataTable;
	TArray<FS_SkillData*> m_arSkillData;

	TArray<int> m_arIndex[(uint8)FE_SkillID::E_EnumMAX];
	S_CurrentData m_sSrc;
	float m_arMaxTime[(uint8)FE_SkillID::E_EnumMAX];
	float m_arCoolTime[(uint8)FE_SkillID::E_EnumMAX];
public:
	UC_SkillMGR();

protected:
	virtual void BeginPlay() override;

	void E_Copy(S_CurrentData& sSrc, S_CurrentData& sDst)
	{
		sSrc.eSkillID = sDst.eSkillID;
		sSrc.nSkillIndex = sDst.nSkillIndex;
		sSrc.nPlayIndex = sDst.nPlayIndex;
		sSrc.nIndex = sDst.nIndex;
	}
public:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintPure)
	float E_CoolTimeRadio(FE_SkillID eSkillID) { return m_arCoolTime[(uint8)eSkillID] / m_arMaxTime[(uint8)eSkillID]; }
	UFUNCTION(BlueprintPure)
	float E_MaxCoolTime(FE_SkillID eSkillID) { return m_arMaxTime[(uint8)eSkillID]; }
	UFUNCTION(BlueprintPure)
	float E_CurrentCoolTime(FE_SkillID eSkillID) { return m_arCoolTime[(uint8)eSkillID]; }

	UFUNCTION(BlueprintCallable)
	void E_SetSkillIndex(FE_SkillID eSkillID, int nIndex, int nValue);
	UFUNCTION(BlueprintCallable)
	bool E_Action(FE_SkillID eID);
	UFUNCTION(BlueprintCallable)
	bool E_PlayNextMontage();
	UFUNCTION(BlueprintCallable)
	bool E_SetNextMontage();

	UPROPERTY(BlueprintAssignable)
	FDL_OnAction On_ActionActive;
};
