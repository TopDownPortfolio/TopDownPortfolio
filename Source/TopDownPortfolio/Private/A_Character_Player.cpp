#include "A_Character_Player.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/ChildActorComponent.h"
#include "O_Buff_Status.h"


AA_Character_Player::AA_Character_Player() :
	AA_Character_Base{}, m_pCameraComponent{}, m_pCameraBoom{}, m_pWeaponR{}, m_pTarget{}, m_pSkillMGR{}, m_sMp{}
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	m_pSkillMGR = CreateDefaultSubobject<UC_SkillMGR>("SkillMGR");
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	
	E_Init_Pawn();
	E_Init_CharacterMovement();
	E_Init_CameraBoom();
	E_Init_CameraComponent();
	m_pWeaponR = CreateDefaultSubobject<UChildActorComponent>(E_GetWeaponRSocketName());
	m_pWeaponR->SetupAttachment(GetMesh(), E_GetWeaponRSocketName());
}

void AA_Character_Player::OnConstruction(const FTransform& Transform)
{
	AA_Character_Base::OnConstruction(Transform);
	E_RegisterComponent(m_pSkillMGR);
}

void AA_Character_Player::E_Init_CharacterMovement()
{
	UCharacterMovementComponent* pMovement = GetCharacterMovement();
	pMovement->bOrientRotationToMovement = true;
	pMovement->RotationRate = FRotator(0.f, 640.f, 0.f);
	pMovement->bConstrainToPlane = true;
	pMovement->bSnapToPlaneAtStart = true;
}

void AA_Character_Player::E_Attack(AA_Character_Base* pTarget)
{
	AA_Character_Base::E_Attack(pTarget);
	if (!IsValid(m_pTarget) )
	{
		m_pTarget = pTarget;
	}
}

void AA_Character_Player::E_Action_Implementation(FE_SkillID eID)
{
	m_pSkillMGR->E_Action(eID);
}

void AA_Character_Player::BeginPlay()
{
	E_GetAttackMGR()->E_RegisterAttacker(0, m_pWeaponR->GetChildActor());
	AA_Character_Base::BeginPlay();
	
	m_sMp.pCharacter = this;
	m_pBuffMGR->E_StartBuff(UO_Buff_Status::StaticClass(), m_sMp);
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
	pCameraBoom->SetupAttachment(RootComponent);
	pCameraBoom->SetUsingAbsoluteRotation(true);
	pCameraBoom->TargetArmLength = 800.f;
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
