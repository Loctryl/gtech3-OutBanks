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
	CharacterRef = Cast<AOB_Character>(OtherActor);
	if(CharacterRef != nullptr)
	{
		CharacterRef->PickUpWeapon(this);
		BoxComp->OnComponentBeginOverlap.RemoveDynamic(this, &AOB_WeaponBase::OnTrigger);
	}
}


void AOB_WeaponBase::Fire()
{
	if (ProjectileClass != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr && CharacterRef->GetAmmoComponent()->ShootOneAmmo())
		{
			APlayerController* PlayerController = Cast<APlayerController>(CharacterRef->GetController());
			const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
			const FVector SpawnLocation = GetActorLocation() + SpawnRotation.RotateVector(FireSpawnOffset);
	
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	
			World->SpawnActor<AOB_Projectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);

			PlayAnimationAndSound();
		}
	}
}


void AOB_WeaponBase::PlayAnimationAndSound()
{
	if (FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, CharacterRef->GetActorLocation());
	}
	
	if (FireAnimation != nullptr)
	{
		UAnimInstance* AnimInstance = CharacterRef->GetMesh()->GetAnimInstance();
		if (AnimInstance != nullptr)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}
}

void AOB_WeaponBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	
}