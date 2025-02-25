#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "E_WindowType.h"
#include "W_WindowBase.generated.h"

struct FAnchors;

UCLASS()
class TOPDOWNPORTFOLIO_API UW_WindowBase : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = WindowBase, meta = (AllowPrivateAccess = "true"))
	FAnchors m_vAnchors;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = WindowBase, meta = (AllowPrivateAccess = "true"))
	FVector2D m_vWidgetPosition;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = WindowBase, meta = (AllowPrivateAccess = "true"))
	FVector2D m_vWidgetSize;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = WindowBase, meta = (AllowPrivateAccess = "true"))
	FE_WindowID m_eWindowID;
public:
	UW_WindowBase(const FObjectInitializer& ObjectInitializer);
protected:
	FVector2D& E_GetSettingVector2D(FE_WindowSetting eSettingID);
	virtual void NativePreConstruct() override;
public:
	FE_WindowID E_GetWindowID() { return m_eWindowID; }
};
