#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "S_AIAction.h"
#include  <queue>
#include "C_AIActionMGR.generated.h"

class AA_Character_Base;
class UDataTable;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOPDOWNPORTFOLIO_API UC_AIActionMGR : public UActorComponent
{
	GENERATED_BODY()
private:
	enum E_ActionIndex
	{
		E_EnumMax = 5
	};
	AA_Character_Base* m_pOwner;
	UPROPERTY(EditDefaultsOnly, Category = Data, meta = (AllowPrivateAccess = "true"))
	UDataTable* m_pDataTable;
	TMap<int, FS_AIActionData*> m_mapActionData;
	std::priority_queue< FS_AIActionData*, std::vector<FS_AIActionData*>, FS_AIActionData> m_pq;
public:	
	UC_AIActionMGR();

protected:
	virtual void BeginPlay() override;
private:
	FS_AIActionData* E_Pop();
	int32 E_Push(FS_AIActionData*  pSrc);
public:	

	UFUNCTION(BlueprintCallable)
	bool E_RegiserAction(int nIndex);
	UFUNCTION(BlueprintCallable)
	void E_PlayAction();
};
