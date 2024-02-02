﻿#include <OutBanks/OB_Components/OB_HealthComp.h>


UOB_HealthComp::UOB_HealthComp()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UOB_HealthComp::BeginPlay()
{
	Super::BeginPlay();
	
}


void UOB_HealthComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}


void UOB_HealthComp::ApplyDamage(int Amount)
{
	if(Amount >= CurrentHealth)
	{
		CurrentHealth = 0;
		DeathEvent.Broadcast();
	}
	else
		CurrentHealth -= Amount;

	UpdateHealthEvent.Broadcast();
}


void UOB_HealthComp::Heal(int Amount)
{
	if(Amount > MaxHealth - CurrentHealth)
		CurrentHealth = MaxHealth;
	else
		CurrentHealth += Amount;
	
	UpdateHealthEvent.Broadcast();
}


void UOB_HealthComp::DotDamage(float LoopTimer, int Amount)
{
	FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &UOB_HealthComp::ApplyDamage, Amount);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, LoopTimer, true);
}

void UOB_HealthComp::StopDotDamage()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}

void UOB_HealthComp::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	//GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
}
