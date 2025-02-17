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
	UUserWidget* m_pMain;
	UPanelWidget* m_pMainPanel;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TMap<FE_WindowID, TSubclassOf<UUserWidget>> m_mapWindow;
	S_WidgetData m_arWidgetData[(uint8)FE_WindowID::E_EnumMAX];
	FE_WindowID m_arWidgetStack[(uint8)FE_WindowID::E_EnumMAX];
	int m_nStackCount;
public:	
	UC_WidgetMGR();

protected:
	virtual void BeginPlay() override;

	UPanelWidget* E_GetMainPanel();
	UUserWidget* E_CreateWidget(TSubclassOf<UUserWidget> cWidget);

	bool E_CheckWindow(FE_WindowID eWindowID);
	void E_Register(FE_WindowID eWindowID, UUserWidget* pWidget);

public:	
	UFUNCTION(BlueprintPure)

	UUserWidget* E_GetWidget(FE_WindowID eWindowID);
	void E_RegisterWidget(FE_WindowID eWindowID);
	UFUNCTION(BlueprintCallable)
	void E_UnRegisterWidget();

	UFUNCTION(BlueprintCallable)
	void E_AddWidget(UUserWidget* pWidget);
	UFUNCTION(BlueprintCallable)
	void E_RemoveWidget(UUserWidget* pWidget);
};
