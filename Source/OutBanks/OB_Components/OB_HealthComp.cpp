#include <OutBanks/OB_Components/OB_HealthComp.h>


void UOB_HealthComp::ApplyDamage(const int Amount)
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


void UOB_HealthComp::Heal(const int Amount)
{
	if(Amount > MaxHealth - CurrentHealth)
		CurrentHealth = MaxHealth;
	else
		CurrentHealth += Amount;
	
	UpdateHealthEvent.Broadcast();
}


void UOB_HealthComp::DotDamage(const float LoopTimer, int Amount)
{
	const FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &UOB_HealthComp::ApplyDamage, Amount);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, LoopTimer, true);
}

void UOB_HealthComp::StopDotDamage() { GetWorld()->GetTimerManager().ClearTimer(TimerHandle); }