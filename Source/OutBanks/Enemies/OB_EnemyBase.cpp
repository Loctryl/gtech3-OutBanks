#include "OutBanks/Enemies/OB_EnemyBase.h"

#include <Components/CapsuleComponent.h>
#include <Components/SphereComponent.h>
#include <OutBanks/OB_Character/OB_Character.h>

#include "OutBanks/OB_Components/OB_HealthComp.h"


AOB_EnemyBase::AOB_EnemyBase()
{
	PrimaryActorTick.bCanEverTick = true;

	TriggerSphere = CreateDefaultSubobject<USphereComponent>("TriggerSphere");
	TriggerSphere->SetupAttachment(GetCapsuleComponent());

	HealthComp = CreateDefaultSubobject<UOB_HealthComp>("HealthComp");
	AddOwnedComponent(HealthComp);

	CurrentState = IDLE;
}

void AOB_EnemyBase::BeginPlay()
{
	Super::BeginPlay();

	TriggerSphere->OnComponentBeginOverlap.AddDynamic(this, &AOB_EnemyBase::OnTrigger);
	TriggerSphere->OnComponentEndOverlap.AddDynamic(this, &AOB_EnemyBase::OnEndTrigger);

	HealthComp->UpdateHealthEvent.AddDynamic(this, &AOB_EnemyBase::UpdateHealthHUD);
	HealthComp->DeathEvent.AddDynamic(this, &AOB_EnemyBase::OnDeath);
}

void AOB_EnemyBase::Tick(float DeltaTime) { Super::Tick(DeltaTime); }


void AOB_EnemyBase::OnDeath()
{
	Destroy();
}

void AOB_EnemyBase::OnTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AOB_Character* Character = Cast<AOB_Character>(OtherActor);

	if(Character != nullptr)
	{
		CurrentState = CHASE;
		OnStateChange.Broadcast(CurrentState, Character);
	}
}

void AOB_EnemyBase::OnEndTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AOB_Character* Character = Cast<AOB_Character>(OtherActor);

	if(Character != nullptr)
	{
		CurrentState = IDLE;
		OnStateChange.Broadcast(CurrentState, Character);
	}
}

