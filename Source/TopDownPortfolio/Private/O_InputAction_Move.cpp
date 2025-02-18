#include "O_InputAction_Move.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

UO_InputAction_Move::UO_InputAction_Move() :
	UO_InputAction{}
{
	// 불필요 변수 삭제
	//m_fShortPressThreshold = 0.3f;
}

void UO_InputAction_Move::E_Release()
{
	m_pController->E_SpawnEffect();
	// TODO : EffectMGR 있으면 좋을듯?
	//UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
}

void UO_InputAction_Move::E_Triggered(const FInputActionValue& fInputValue)
{
	UC_InterfaceMGR* pMGR = m_pController->E_GetInterfaceMGR();
	pMGR->E_SetLocation(FE_InterfaceType::E_Cursor);
	APawn* ControlledPawn = Cast< APawn>(E_GetPlayerCharacter());
	if (ControlledPawn != nullptr)
	{
		FVector CachedDestination = m_pController->E_GetInterfaceMGR()->E_GetLocation();
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(m_pController, CachedDestination);
		// TODO : 움직임 형식 변화 되면 바꿔줘야 할듯? 움직이는 방식이 많아지면 MoveMGR 같은거 만들고 교체 하는 식으로 해보자
		// 아래 코드는 일반적인 Move인데 절벽 같은 높이를 무시하는 알고리즘
		// 위는 AIPathfind를 기준으로 이동시켜주는 로직 그래서 위가 적절하여 코드 변경하였음
		// FVector WorldDirection = (pMGR->E_GetLocation() - ControlledPawn->GetActorLocation()).GetSafeNormal();
		// ControlledPawn->AddMovementInput(WorldDirection, 1.0, false);
	}
}

void UO_InputAction_Move::E_Started(const FInputActionValue& fInputValue)
{
	m_pController->StopMovement();
}

void UO_InputAction_Move::E_Canceled(const FInputActionValue& fInputValue)
{
	E_Release();
}

void UO_InputAction_Move::E_Completed(const FInputActionValue& fInputValue)
{
	
	E_Release();
}
