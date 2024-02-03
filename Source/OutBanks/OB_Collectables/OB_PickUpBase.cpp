#include <OutBanks/OB_Collectables/OB_PickUpBase.h>

#include <GameFramework/RotatingMovementComponent.h>

AOB_PickUpBase::AOB_PickUpBase()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	SetRootComponent(StaticMeshComp);

	RotatorComp = CreateDefaultSubobject<URotatingMovementComponent>("RotatorComp");
	RotatorComp->RotationRate = FRotator(0,150,0);
}