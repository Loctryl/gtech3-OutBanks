#include <OutBanks/OB_Weapons/OB_WeaponBase.h>
#include <EnhancedInputComponent.h>
#include <EnhancedInputSubsystems.h>
#include <Components/BoxComponent.h>
#include <Kismet/GameplayStatics.h>
#include <OutBanks/OB_Weapons/OB_Projectile.h>
#include "OutBanks/OB_Character/OB_Character.h"
#include "OutBanks/OB_Components/OB_AmmoComp.h"


AOB_WeaponBase::AOB_WeaponBase()
{
	PrimaryActorTick.bCanEverTick = true;

	FireSpawnOffset = FVector(100.0f, 0.0f, 10.0f);

	SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>("StaticMesh");
	SetRootComponent(SkeletalMeshComp);

	BoxComp = CreateDefaultSubobject<UBoxComponent>("SphereTrigger");
	BoxComp->SetupAttachment(SkeletalMeshComp);
}

void AOB_WeaponBase::BeginPlay()
{
	Super::BeginPlay();

	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &AOB_WeaponBase::OnTrigger);
}

void AOB_WeaponBase::Tick(float DeltaTime) { Super::Tick(DeltaTime); }

void AOB_WeaponBase::OnTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AttachWeapon(Cast<AOB_Character>(OtherActor));
}


void AOB_WeaponBase::AttachWeapon(AOB_Character* TargetCharacter)
{
	Character = TargetCharacter;

	// Check that the character is valid, and has no rifle yet
	if (Character == nullptr || Character->GetHasRifle())
	{
		return;
	}

	// Attach the weapon to the First Person Character
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(Character->GetMesh(), AttachmentRules, FName(TEXT("GripPoint")));
	
	// switch bHasRifle so the animation blueprint can switch to another animation set
	Character->SetHasRifle(true);
	Character->SetWeapon(this);

	Character->GetAmmoComponent()->SetMaxAmmoInClip(MaxAmmoInClip);

	// Set up action bindings
	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			// Set the priority of the mapping to 1, so that it overrides the Jump action with the Fire action when using touch input
			Subsystem->AddMappingContext(FireMappingContext, 1);
		}

		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
		{
			// Fire
			EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &AOB_WeaponBase::Fire);
			EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Triggered, Character->GetAmmoComponent(), &UOB_AmmoComp::Reload);
		}
	}
	Character->PickUpWeapon();
}

void AOB_WeaponBase::Fire()
{
	if (Character == nullptr || Character->GetController() == nullptr)
	{
		return;
	}

	// Try and fire a projectile
	if (ProjectileClass != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr && Character->GetAmmoComponent()->ShootOneAmmo())
		{
			APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
			const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
			// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
			const FVector SpawnLocation = GetActorLocation() + SpawnRotation.RotateVector(FireSpawnOffset);
	
			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	
			// Spawn the projectile at the muzzle
			World->SpawnActor<AOB_Projectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);

			PlayAnimationAndSound();
		}
	}
}


void AOB_WeaponBase::PlayAnimationAndSound()
{
	// Try and play the sound if specified
	if (FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, Character->GetActorLocation());
	}
	
	// Try and play a firing animation if specified
	if (FireAnimation != nullptr)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();
		if (AnimInstance != nullptr)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}
}

void AOB_WeaponBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (Character == nullptr)
	{
		return;
	}

	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->RemoveMappingContext(FireMappingContext);
		}
	}
}