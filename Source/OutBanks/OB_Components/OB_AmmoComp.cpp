#include <OutBanks/OB_Components/OB_AmmoComp.h>


UOB_AmmoComp::UOB_AmmoComp()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}

void UOB_AmmoComp::BeginPlay()
{
	Super::BeginPlay();
	
}

void UOB_AmmoComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

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

void UOB_AmmoComp::PickUpAmmo(int Amount)
{
	if(Amount > MaxAmmoInReserve - CurrentAmmoInReserve)
		CurrentAmmoInReserve = MaxAmmoInReserve;
	else
		CurrentAmmoInReserve += Amount;
	
	UpdateAmmo.Broadcast();
}

void UOB_AmmoComp::RamboTime(float Timer)
{
	Rambo = true;

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle,[this]() 
	{
		Rambo = false;
	}, Timer, false);
}
