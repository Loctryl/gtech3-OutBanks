
#include "OB_GameMode.h"
#include "OutBanks/OB_Character/OB_Character.h"
#include "OutBanks/OB_Tiles/OB_Tile.h"
#include "UObject/ConstructorHelpers.h"

AOB_GameMode::AOB_GameMode()
	: Super()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/OutBanks/Blueprints/OBP_Character"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
	
}

void AOB_GameMode::BeginPlay()
{
	Super::BeginPlay();
	NextSpawnPoint = FVector(1500,0,0);

	for(int i = 0; i < 8; i++)
	{
		SpawnTile();
	}
}

void AOB_GameMode::TriggerSpawn(AOB_Tile* Tile)
{
	SpawnTile();

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, Tile, &AOB_Tile::ToDestroy, 5, false);
}


void AOB_GameMode::SpawnTile()
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParameters.bNoFail = true;
	
	FTransform Transform;
	Transform.SetLocation(NextSpawnPoint);
	
	AOB_Tile* Spawned = GetWorld()->SpawnActor<AOB_Tile>(TileClass, Transform, SpawnParameters);

	Spawned->OnExitTile.AddDynamic(this, &AOB_GameMode::TriggerSpawn);

	NextSpawnPoint = Spawned->GetAttachPoint();
}