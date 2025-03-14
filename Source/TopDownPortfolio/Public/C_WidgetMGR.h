#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "E_WindowType.h"
#include "C_WidgetMGR.generated.h"

class APlayerController;
class UW_WindowBase;
class UPanelWidget;

USTRUCT(BlueprintType)
struct FS_WindowClassData: public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FE_WindowID eWindowID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UW_WindowBase> cWindowClass;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOPDOWNPORTFOLIO_API UC_WidgetMGR : public UActorComponent
{
	GENERATED_BODY()
protected:
	struct S_WidgetData
	{
		UW_WindowBase* pWidget;
		int nStackIndedx;
		bool bRegistered;
	};
private:
	APlayerController* m_pController;
	UW_WindowBase* m_pMain;
	UPanelWidget* m_pMainPanel;
	S_WidgetData m_arWidgetData[(uint8)FE_WindowID::E_EnumMAX];
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WidgetMGR)
	UDataTable* m_pDataTable;
	TMap<FE_WindowID, const FS_WindowClassData*> m_mapWindow;
private:
	FE_WindowID m_arWidgetStack[(uint8)FE_WindowID::E_EnumMAX];
	int m_nStackCount;
public:	
	UC_WidgetMGR();

protected:
	virtual void BeginPlay() override;

	UPanelWidget* E_GetMainPanel();
	UW_WindowBase* E_CreateWidget(TSubclassOf<UW_WindowBase> cWidget);

	bool E_CheckWindow(FE_WindowID eWindowID);
	void E_Register(FE_WindowID eWindowID, UW_WindowBase* pWidget);
	void E_AddWidget(UW_WindowBase* pWidget);
	void E_RemoveWidget(UW_WindowBase* pWidget);

	bool E_PushStack(FE_WindowID eWindowID);
	void E_PopStack(FE_WindowID eWindowID);
public:	
	void E_SetFocus(FE_WindowID eWindowID);
	UFUNCTION(BlueprintPure)
	UW_WindowBase* E_GetWidget(FE_WindowID eWindowID);
	UFUNCTION(BlueprintCallable)
	void E_RegisterWidget(FE_WindowID eWindowID);
	UFUNCTION(BlueprintCallable)
	void E_UnRegisterWidget(FE_WindowID eWindowID);

	UFUNCTION(BlueprintPure)
	bool E_CheckRegistered(FE_WindowID eWindowID);
	void E_UnRegisterWidget();

};
