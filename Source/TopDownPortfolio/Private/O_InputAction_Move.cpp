#include "O_InputAction_Move.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

UO_InputAction_Move::UO_InputAction_Move() :
	UO_InputAction{}
{
	// ���ʿ� ���� ����
	//m_fShortPressThreshold = 0.3f;
}

void UO_InputAction_Move::E_Release()
{
	m_pController->E_SpawnEffect();
	// TODO : EffectMGR ������ ������?
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
		// TODO : ������ ���� ��ȭ �Ǹ� �ٲ���� �ҵ�? �����̴� ����� �������� MoveMGR ������ ����� ��ü �ϴ� ������ �غ���
		// �Ʒ� �ڵ�� �Ϲ����� Move�ε� ���� ���� ���̸� �����ϴ� �˰���
		// ���� AIPathfind�� �������� �̵������ִ� ���� �׷��� ���� �����Ͽ� �ڵ� �����Ͽ���
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
