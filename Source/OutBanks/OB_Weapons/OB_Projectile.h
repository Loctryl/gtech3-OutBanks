#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OB_Projectile.generated.h"


UCLASS(config=Game)
class AOB_Projectile : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleDefaultsOnly, Category=Projectile)
	class USphereComponent* CollisionComp;

	UPROPERTY(VisibleAnywhere, Category = Movement)
	class UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditAnywhere, BlueprintGetter=BPGetSound, Category=Projectile)
	class USoundBase* DamageSound;

	UPROPERTY(EditAnywhere, BlueprintGetter=BPGetParticle, Category=Projectile)
	class UParticleSystem* Particles;


public:
	AOB_Projectile();

	UFUNCTION(BlueprintCallable)
	USoundBase* BPGetSound() const { return DamageSound; }

	UFUNCTION(BlueprintCallable)
	UParticleSystem* BPGetParticle() const { return Particles; }

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};

