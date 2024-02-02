#include "OB_Projectile.h"

#include <Components/CapsuleComponent.h>
#include <Kismet/GameplayStatics.h>
#include <OutBanks/OB_Enemies/OB_EnemyBase.h>
#include <OutBanks/OB_Components/OB_HealthComp.h>

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AOB_Projectile::AOB_Projectile() 
{
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AOB_Projectile::OnHit);	

	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	RootComponent = CollisionComp;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	InitialLifeSpan = 3.0f;
}

void AOB_Projectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && Cast<UCapsuleComponent>(OtherComp))
	{
		AOB_EnemyBase* Enemy = Cast<AOB_EnemyBase>(OtherActor);
		
		if(Enemy)
		{
			Enemy->GetHealthComp()->ApplyDamage(10);

			if (DamageSound != nullptr)
				UGameplayStatics::PlaySoundAtLocation(this, DamageSound, GetActorLocation());
			
			if (Particles != nullptr)
				UGameplayStatics::SpawnEmitterAtLocation(this, Particles, GetActorLocation(),FRotator(0), FVector(0.05,0.05,0.05));
		}
	}
	Destroy();
}

void AOB_Projectile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorldTimerManager().ClearAllTimersForObject(this);
}