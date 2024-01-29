// Copyright Epic Games, Inc. All Rights Reserved.

#include "OB_Character.h"

#include <OutBanks/OB_Character/OB_PlayerController.h>
#include <OutBanks/OB_Weapons/OB_WeaponBase.h>

#include "OutBanks/OB_Components/OB_AmmoComp.h"

#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/LocalPlayer.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);


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
	AmmoComp->UpdateAmmo.AddDynamic(this, &AOB_Character::UpdateHUDWidget);
	AddOwnedComponent(AmmoComp);
}

void AOB_Character::BeginPlay()
{
	Super::BeginPlay();

}

void AOB_Character::PickUpWeapon(AOB_WeaponBase* WeaponPickUp)
{
	if(bHasRifle) return;
	
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	WeaponPickUp->AttachToComponent(GetMesh(), AttachmentRules, FName(TEXT("GripPoint")));
	
	SetHasRifle(true);
	SetWeapon(WeaponPickUp);

	GetAmmoComponent()->SetMaxAmmoInClip(WeaponPickUp->GetWeaponClipSize());

	Cast<AOB_PlayerController>(Controller)->SetUpWeaponInputs();

	OnPickUpWeaponUpdateHUDWidget();
	UpdateHUDWidget();
}