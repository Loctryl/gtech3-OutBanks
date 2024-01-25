// Fill out your copyright notice in the Description page of Project Settings.


#include <OutBanks/OB_Components/OB_AmmoComp.h>


// Sets default values for this component's properties
UOB_AmmoComp::UOB_AmmoComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
}


// Called when the game starts
void UOB_AmmoComp::BeginPlay()
{
	Super::BeginPlay();

	
}


// Called every frame
void UOB_AmmoComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UOB_AmmoComp::Reload()
{
	if(CurrentAmmoInReserve == 0 || CurrentAmmoInClip == MaxAmmoInClip) return;
	
	const int32 Diff = MaxAmmoInClip - CurrentAmmoInClip;
	
	if(CurrentAmmoInReserve < Diff)
	{
		CurrentAmmoInClip += CurrentAmmoInReserve;
		CurrentAmmoInReserve = 0;
	} else
	{
		CurrentAmmoInClip += Diff;
		CurrentAmmoInClip -= Diff;
	}
}

