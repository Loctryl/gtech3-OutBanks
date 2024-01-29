#include "OutBanks/Enemies/OB_EnemyBase.h"

#include <Components/CapsuleComponent.h>

#include "OutBanks/OB_Components/OB_HealthComp.h"


AOB_EnemyBase::AOB_EnemyBase()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>("CapsuleComp");
	SetRootComponent(CapsuleComponent);

	SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
	SkeletalMeshComp->SetupAttachment(CapsuleComponent);

	HealthComp = CreateDefaultSubobject<UOB_HealthComp>("HealthComp");
	HealthComp->UpdateHealthEvent.AddDynamic(this, &AOB_EnemyBase::UpdateHealthHUD);
	HealthComp->DeathEvent.AddDynamic(this, &AOB_EnemyBase::OnDeath);
	AddOwnedComponent(HealthComp);
}

void AOB_EnemyBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AOB_EnemyBase::Tick(float DeltaTime) { Super::Tick(DeltaTime); }


void AOB_EnemyBase::OnDeath()
{
	Destroy();
}