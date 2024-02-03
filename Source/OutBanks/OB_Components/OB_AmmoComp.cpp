#include <OutBanks/OB_Components/OB_AmmoComp.h>


void UOB_AmmoComp::Reload()
{
	if(CurrentAmmoInReserve == 0 || CurrentAmmoInClip == MaxAmmoInClip) return;
	
	const int32 Diff = MaxAmmoInClip - CurrentAmmoInClip;
	
	if(CurrentAmmoInReserve > Diff)
	{
		CurrentAmmoInClip += Diff;
		CurrentAmmoInReserve -= Diff;
	}
	else
	{
		CurrentAmmoInClip += CurrentAmmoInReserve;
		CurrentAmmoInReserve = 0;
	}
	UpdateAmmo.Broadcast();
}

bool UOB_AmmoComp::ShootOneAmmo()
{
	if(CurrentAmmoInClip == 0) return false;

	if(!Rambo)
	{
		CurrentAmmoInClip--;
		UpdateAmmo.Broadcast();
	}
		
	return true;
}

void UOB_AmmoComp::PickUpAmmo(const int Amount)
{
	if(Amount > MaxAmmoInReserve - CurrentAmmoInReserve)
		CurrentAmmoInReserve = MaxAmmoInReserve;
	else
		CurrentAmmoInReserve += Amount;
	
	UpdateAmmo.Broadcast();
}

void UOB_AmmoComp::RamboTime(const float Timer)
{
	Rambo = true;

	FTimerHandle TimerHandle;
	const FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &UOB_AmmoComp::SetRambo, false);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, Timer, false);
}