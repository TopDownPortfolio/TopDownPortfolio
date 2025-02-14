#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "E_WindowType.h"
#include "C_WidgetMGR.generated.h"

class APlayerController;
class UUserWidget;
class UPanelWidget;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOPDOWNPORTFOLIO_API UC_WidgetMGR : public UActorComponent
{
	GENERATED_BODY()
protected:
	struct S_WidgetData
	{
		UUserWidget* pWidget;

	};
private:
	APlayerController* m_pController;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))

	TSubclassOf< UUserWidget> m_cMain;
	TMap<UUserWidget*, S_WidgetData*> m_mapWidget;
	UUserWidget* m_pMain;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TMap<FE_WindowID, TSubclassOf<UUserWidget>> m_mapWindow;
	S_WidgetData m_arWidgetData[(uint8)FE_WindowID::E_EnumMAX];
	int m_nOpenWidgetCount;
public:	
	UC_WidgetMGR();

protected:
	virtual void BeginPlay() override;

	void E_Add(UUserWidget* pWidget);
	void E_Remove(UUserWidget* pWidget);

	UPanelWidget* E_GetMainPannel();
public:	
	void E_RegisterWidget(FE_WindowID eID);

	UFUNCTION(BlueprintCallable)
	UUserWidget* E_RegisterWidget(TSubclassOf<UUserWidget> cWidget);
	UFUNCTION(BlueprintCallable)
	void E_UnRegisterWidget(UUserWidget* pWidget);
};
