// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OB_WeaponBase.generated.h"


class UBoxComponent;
class USphereComponent;
class UInputAction;
class UInputMappingContext;
class AOB_Character;


UCLASS()
class OUTBANKS_API AOB_WeaponBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AOB_WeaponBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName WeaponName;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* SkeletalMeshComp;

	UPROPERTY(VisibleAnywhere);
	UBoxComponent* BoxComp;

	
	UPROPERTY(EditDefaultsOnly, Category=Shoot)
	TSubclassOf<class AOB_Projectile> ProjectileClass;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Shoot)
	USoundBase* FireSound;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Shoot)
	UAnimMontage* FireAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* FireMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* FireAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* ReloadAction;

	
	UPROPERTY()
	AOB_Character* Character;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector FireSpawnOffset;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 MaxAmmoInClip;

	
	UFUNCTION(BlueprintCallable, Category="Weapon")
	void AttachWeapon(AOB_Character* TargetCharacter);
	
	UFUNCTION(BlueprintCallable, Category="Weapon")
	void Fire();

	UFUNCTION(BlueprintCallable, Category="Weapon")
	void PlayAnimationAndSound();
	
	UFUNCTION()
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	FName GetWeaponName() const { return WeaponName; }

	UFUNCTION()
	int32 GetWeaponClipSize() const { return MaxAmmoInClip; }

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void OnTrigger(UPrimitiveComponent* OverlappedComponent,
						AActor* OtherActor,
						UPrimitiveComponent* OtherComp,
						int32 OtherBodyIndex,
						bool bFromSweep,
						const FHitResult& SweepResult
	);
};
