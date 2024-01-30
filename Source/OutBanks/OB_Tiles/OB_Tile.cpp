#include <OutBanks/OB_Tiles/OB_Tile.h>
#include "Components/BoxComponent.h"
#include "Components/MeshComponent.h"
#include "OutBanks/OB_Character/OB_Character.h"


AOB_Tile::AOB_Tile()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneRootComp = CreateDefaultSubobject<USceneComponent>("RootScene");
	SetRootComponent(SceneRootComp);
	
	FloorMesh = CreateDefaultSubobject<UStaticMeshComponent>("Floor");
	FloorMesh->SetupAttachment(SceneRootComp);

	RightWallMesh = CreateDefaultSubobject<UStaticMeshComponent>("RightWall");
	RightWallMesh->SetupAttachment(SceneRootComp);

	LeftWallMesh = CreateDefaultSubobject<UStaticMeshComponent>("LeftWall");
	LeftWallMesh->SetupAttachment(SceneRootComp);

	EndTrigger = CreateDefaultSubobject<UBoxComponent>("EndTrigger");
	EndTrigger->SetupAttachment(SceneRootComp);
	
	SpawnArea = CreateDefaultSubobject<UBoxComponent>("SpawnArea");
	SpawnArea->SetupAttachment(SceneRootComp);

}

void AOB_Tile::BeginPlay()
{
	Super::BeginPlay();

	//EndTrigger->OnComponentBeginOverlap.AddDynamic(this, &AOB_Tile::OnEndTrigger);
	
}

void AOB_Tile::Tick(float DeltaTime) { Super::Tick(DeltaTime); }


void AOB_Tile::OnEndTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(Cast<AOB_Character>(OtherActor))
	{
		OnExitTile.Broadcast();
	}
}