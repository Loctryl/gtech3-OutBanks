// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OB_AmmoComp.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUpdateAmmo);


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class OUTBANKS_API UOB_AmmoComp : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UOB_AmmoComp();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void SetRambo(bool Value) { Rambo = Value; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentAmmoInClip;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxAmmoInClip;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentAmmoInReserve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxAmmoInReserve;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime,
								ELevelTick TickType,
								FActorComponentTickFunction* ThisTickFunction) override;
	
	void SetMaxAmmoInClip(int32 MaxAmmo) { MaxAmmoInClip = MaxAmmo; }
	
	UFUNCTION(BlueprintCallable)
	void Reload();

	UFUNCTION(BlueprintCallable)
	bool ShootOneAmmo();

	UFUNCTION(BlueprintCallable)
	void PickUpAmmo(int Amount);

	UFUNCTION(BlueprintCallable)
	void RamboTime(float Timer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Rambo;

	FUpdateAmmo UpdateAmmo;
};
