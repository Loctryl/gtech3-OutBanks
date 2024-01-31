#include <OutBanks/OB_Tiles/OB_ObstacleBase.h>


AOB_ObstacleBase::AOB_ObstacleBase()
{
	PrimaryActorTick.bCanEverTick = true;
	
	SceneRootComp = CreateDefaultSubobject<USceneComponent>("RootScene");
	SetRootComponent(SceneRootComp);
	
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComp->SetupAttachment(SceneRootComp);
	
}

void AOB_ObstacleBase::BeginPlay()
{
	Super::BeginPlay();

}

void AOB_ObstacleBase::Tick(float DeltaTime) { Super::Tick(DeltaTime); }