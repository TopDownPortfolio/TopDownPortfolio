#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "E_MontageID.h"
#include "S_Montage.h"
#include "C_MontageMGR.generated.h"
//casting에는 결국 부하가 걸리긴한다.
	// animinstance 변경x 

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOPDOWNPORTFOLIO_API UC_MontageMGR : public UActorComponent
{
	GENERATED_BODY()
protected:
	TArray< FS_MontageData*> m_arMontageData[(uint8)FE_MontageID::E_EnumMAX];
	UAnimInstance* m_pInstance;
	FS_MontageData* m_pCurrentData;
	FS_MontagePlayData m_sPlayData;
	FE_MontageID m_eCurrentID;
	UPROPERTY(EditDefaultsOnly, Category = Data, meta = (AllowPrivateAccess = "true"))
	UDataTable* m_pDataTable;
	bool m_bIsPlaying;
	bool m_bCanPlay;
	bool m_bIsInterruptable;
public:	
	UC_MontageMGR();

protected:
	virtual void BeginPlay() override;

	FS_MontageData* E_GetMontageData(FE_MontageID eID, int nIndex);
	UFUNCTION()
	void E_Started(UAnimMontage* pMontage);
	UFUNCTION()
	void E_Ended(UAnimMontage* pMontage, bool bInterrupted);
	UFUNCTION()
	void E_BlendingOutStarted(UAnimMontage* pMontage, bool bInterrupted);
	UFUNCTION()
	void E_BlendedInEnded(UAnimMontage* pMontage);
	UFUNCTION()
	void E_Bind();

public:	
	//void E_SetMontageData(TArray< FS_MontageData*>* arMontageData) { m_arMontageData = arMontageData; }
	UFUNCTION(BlueprintCallable, Category = SetData)
	void E_SetMontageData(FE_MontageID eID, int nIndex = 0)
	{
		m_eCurrentID = eID;
		m_pCurrentData = E_GetMontageData(m_eCurrentID, nIndex);
	}
	UFUNCTION(BlueprintCallable, Category = SetData)
	void E_SetPlaySpeed(float fPlaySpeed = 1.0f) { m_sPlayData.fPlaySpeed = fPlaySpeed; }
	UFUNCTION(BlueprintCallable, Category = SetData)
	void E_SetPlaySection(FName sSection = NAME_None) { m_sPlayData.strSection = sSection; }
	UFUNCTION(BlueprintCallable, Category = SetData)
	void E_SetCanPlay(bool bValue) { m_bCanPlay = bValue; }
	UFUNCTION(BlueprintCallable, Category = Play)
	bool E_Play(FE_MontageID eID, int nIndex = 0);
		
	UFUNCTION(BlueprintPure)
	bool E_CheckPlayable(FE_MontageID eID, int nIndex = 0);
	UFUNCTION(BlueprintCallable, Category = Play, NetMulticast, Reliable)
	void E_PlayMontage();
	void E_PlayMontage_Implementation();
	UFUNCTION(BlueprintCallable, Category = Play, NetMulticast, Reliable)
	void E_Jump2Section();
	void E_Jump2Section_Implementation();
};
