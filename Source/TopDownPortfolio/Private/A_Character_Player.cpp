#include "A_Character_Player.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/ChildActorComponent.h"
#include "C_BuffMGR.h"
#include "C_StatusMGR.h"
#include "C_InteractionInitiator.h"

AA_Character_Player::AA_Character_Player() :
	AA_Character_Base{}, m_pCameraComponent{}, m_pCameraBoom{}, m_pInteractionInitiator{}, m_pInteractionCollision{}, m_sMp {}
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	
	E_Init_Pawn();
	E_Init_CharacterMovement();
	E_Init_CameraBoom();
	E_Init_CameraComponent();
	m_pStateMGR->E_Init(FE_CharacterType::E_Player);

	m_pInteractionInitiator = CreateDefaultSubobject<UC_InteractionInitiator>("InteractionInitiator");
	m_pInteractionCollision = CreateDefaultSubobject<UCapsuleComponent>("InteractionCollision");
	m_pInteractionCollision->SetupAttachment(GetRootComponent());
	m_pInteractionCollision->SetCollisionProfileName(m_pInteractionInitiator->E_GetCollisionProfile());
}

void AA_Character_Player::OnConstruction(const FTransform& Transform)
{
	AA_Character_Base::OnConstruction(Transform);
	E_RegisterComponent(m_pInteractionInitiator);
}

void AA_Character_Player::BeginPlay()
{
	AA_Character_Base::BeginPlay();

	m_sMp.eBuffID = FE_BuffID::E_Status;
	m_sMp.pCharacter = this;
	if (m_pBuffMGR)
		m_pBuffMGR->E_StartBuff(m_sMp);
	m_pInteractionInitiator->E_BindCollisionOverlaps(m_pInteractionCollision);
}

void AA_Character_Player::E_Init_CharacterMovement()
{
	UCharacterMovementComponent* pMovement = GetCharacterMovement();
	pMovement->bOrientRotationToMovement = true;
	pMovement->RotationRate = FRotator(0.f, 640.f, 0.f);
	pMovement->bConstrainToPlane = true;
	pMovement->bSnapToPlaneAtStart = true;
}

void AA_Character_Player::E_Init_Pawn()
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
}

void AA_Character_Player::E_Init_CameraBoom()
{
	USpringArmComponent* pCameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	m_pCameraBoom = pCameraBoom;
	pCameraBoom->SetupAttachment(GetRootComponent());
	pCameraBoom->SetUsingAbsoluteRotation(true);
	pCameraBoom->TargetArmLength = 1300.f;
	pCameraBoom->SetRelativeRotation(FRotator(-50.f, 0.f, 0.f));
	pCameraBoom->bDoCollisionTest = false; 
}

void AA_Character_Player::E_Init_CameraComponent()
{
	UCameraComponent* pCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	m_pCameraComponent = pCamera;
	pCamera->SetupAttachment(m_pCameraBoom, USpringArmComponent::SocketName);
	pCamera->bUsePawnControlRotation = false; 
}
