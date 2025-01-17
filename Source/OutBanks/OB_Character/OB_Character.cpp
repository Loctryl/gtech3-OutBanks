#include "OB_Character.h"
#include <GameFramework/CharacterMovementComponent.h>
#include <OutBanks/OB_Character/OB_PlayerController.h>
#include <OutBanks/OB_Components/OB_HealthComp.h>
#include <OutBanks/OB_Weapons/OB_WeaponBase.h>
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "OutBanks/OB_Components/OB_AmmoComp.h"


//Setting up components
AOB_Character::AOB_Character()
{
	bHasRifle = false;
	
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	FPCameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FPCameraComp->SetupAttachment(GetCapsuleComponent());
	FPCameraComp->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FPCameraComp->bUsePawnControlRotation = true;

	USkeletalMeshComponent* MeshSet = GetMesh();
	MeshSet->SetupAttachment(FPCameraComp);
	MeshSet->SetOnlyOwnerSee(true);
	MeshSet->bCastDynamicShadow = false;
	MeshSet->CastShadow = false;
	MeshSet->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	AmmoComp = CreateDefaultSubobject<UOB_AmmoComp>("AmmoComp");
	AddOwnedComponent(AmmoComp);

	HealthComp = CreateDefaultSubobject<UOB_HealthComp>("HealthComp");
	AddOwnedComponent(HealthComp);
}


void AOB_Character::BeginPlay()
{
	Super::BeginPlay();

	AmmoComp->UpdateAmmo.AddDynamic(this, &AOB_Character::UpdateAmmoHUD);
	
	HealthComp->UpdateHealthEvent.AddDynamic(this, &AOB_Character::UpdateHealthHUD);
	HealthComp->DeathEvent.AddDynamic(this, &AOB_Character::OnDeath);
}


// Triggered when the player overlap a weapon so he can pick it up
void AOB_Character::PickUpWeapon(AOB_WeaponBase* WeaponPickUp)
{
	if(bHasRifle) return;
	
	const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	WeaponPickUp->AttachToComponent(GetMesh(), AttachmentRules, FName(TEXT("GripPoint")));
	
	SetHasRifle(true);
	SetWeapon(WeaponPickUp);

	GetAmmoComp()->SetMaxAmmoInClip(WeaponPickUp->GetWeaponClipSize());

	Cast<AOB_PlayerController>(Controller)->SetUpWeaponInputs();

	OnPickUpWeaponUpdateHUD();
	UpdateAmmoHUD();
}


void AOB_Character::OnDeath()
{
	DetachFromControllerPendingDestroy();
	OnPlayerDeath.Broadcast();
}


void AOB_Character::Speeder(float Timer, float Amount)
{
	IncreaseSpeed(Amount);

	FTimerHandle TimerHandle;
	const FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &AOB_Character::DecreaseSpeed, Amount);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, Timer, false);
}

void AOB_Character::IncreaseSpeed(const float Amount) { GetCharacterMovement()->MaxWalkSpeed += Amount; }

void AOB_Character::DecreaseSpeed(const float Amount) { GetCharacterMovement()->MaxWalkSpeed -= Amount; }