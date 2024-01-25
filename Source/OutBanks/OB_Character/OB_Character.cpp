// Copyright Epic Games, Inc. All Rights Reserved.

#include "OB_Character.h"

#include <OutBanks/OB_Components/OB_AmmoComp.h>

#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/LocalPlayer.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);


AOB_Character::AOB_Character()
{
	// Character doesnt have a rifle at start
	bHasRifle = false;
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	USkeletalMeshComponent* TempMesh = GetMesh();
	TempMesh->SetupAttachment(FirstPersonCameraComponent);
	TempMesh->SetOnlyOwnerSee(true);
	TempMesh->bCastDynamicShadow = false;
	TempMesh->CastShadow = false;
	TempMesh->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	AmmoComp = CreateDefaultSubobject<UOB_AmmoComp>("AmmoComp");
	AddOwnedComponent(AmmoComp);
}

void AOB_Character::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

}


void AOB_Character::SetHasRifle(bool bNewHasRifle)
{
	bHasRifle = bNewHasRifle;
}

bool AOB_Character::GetHasRifle()
{
	return bHasRifle;
}