#include "OutBanks/OB_Enemies/OB_EnemyBase.h"
#include <Components/CapsuleComponent.h>
#include <Components/SphereComponent.h>
#include <OutBanks/OB_Character/OB_Character.h>
#include "OutBanks/OB_Components/OB_HealthComp.h"


AOB_EnemyBase::AOB_EnemyBase()
{
	PrimaryActorTick.bCanEverTick = true;

	TriggerChaseSphere = CreateDefaultSubobject<USphereComponent>("TriggerChaseSphere");
	TriggerChaseSphere->SetupAttachment(GetCapsuleComponent());

	TriggerAttackSphere = CreateDefaultSubobject<USphereComponent>("TriggerAttackSphere");
	TriggerAttackSphere->SetupAttachment(GetCapsuleComponent());

	HealthComp = CreateDefaultSubobject<UOB_HealthComp>("HealthComp");
	AddOwnedComponent(HealthComp);

	CurrentState = IDLE;
}


void AOB_EnemyBase::BeginPlay()
{
	Super::BeginPlay();

	TriggerChaseSphere->OnComponentBeginOverlap.AddDynamic(this, &AOB_EnemyBase::OnTriggerChase);
	TriggerChaseSphere->OnComponentEndOverlap.AddDynamic(this, &AOB_EnemyBase::OnEndTriggerChase);

	TriggerAttackSphere->OnComponentBeginOverlap.AddDynamic(this, &AOB_EnemyBase::OnTriggerAttack);
	TriggerAttackSphere->OnComponentEndOverlap.AddDynamic(this, &AOB_EnemyBase::OnEndTriggerAttack);

	//HealthComp->UpdateHealthEvent.AddDynamic(this, &AOB_EnemyBase::UpdateHealthHUD);
	HealthComp->DeathEvent.AddDynamic(this, &AOB_EnemyBase::Die);
}


void AOB_EnemyBase::Die()
{
	OnDeath.Broadcast();
	Destroy();
}


void AOB_EnemyBase::OnTriggerChase(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AOB_Character* CharacterRef = Cast<AOB_Character>(OtherActor);

	if(CharacterRef != nullptr)
	{
		CurrentState = CHASE;
		OnStateChange.Broadcast(CurrentState, CharacterRef);
	}
}


void AOB_EnemyBase::OnEndTriggerChase(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AOB_Character* CharacterRef = Cast<AOB_Character>(OtherActor);

	if(CharacterRef != nullptr)
	{
		CurrentState = IDLE;
		OnStateChange.Broadcast(CurrentState, CharacterRef);

		FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &AOB_EnemyBase::ToDestroy);
		GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, 5, false);
	}
}


void AOB_EnemyBase::OnTriggerAttack(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AOB_Character* CharacterRef = Cast<AOB_Character>(OtherActor);

	if(CharacterRef != nullptr)
	{
		CurrentState = ATTACK;
		OnStateChange.Broadcast(CurrentState, CharacterRef);

		CharacterRef->GetHealthComp()->ApplyDamage(DamageDone);

		const FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &AOB_EnemyBase::ApplyDamageToCharacter, CharacterRef);
		GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, AttackSpeed, true);
	}
}


void AOB_EnemyBase::OnEndTriggerAttack(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AOB_Character* CharacterRef = Cast<AOB_Character>(OtherActor);

	if(CharacterRef != nullptr)
	{
		CurrentState = CHASE;
		OnStateChange.Broadcast(CurrentState, CharacterRef);

		GetWorldTimerManager().ClearTimer(TimerHandle);
	}
}

void AOB_EnemyBase::ApplyDamageToCharacter(AOB_Character* Ref) const { Ref->GetHealthComp()->ApplyDamage(DamageDone); }