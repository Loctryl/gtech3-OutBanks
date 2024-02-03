#include <OutBanks/OB_Tiles/OB_Tile.h>
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "OutBanks/OB_Character/OB_Character.h"
#include "OutBanks/OB_Enemies/OB_EnemyBase.h"


AOB_Tile::AOB_Tile()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneRootComp = CreateDefaultSubobject<USceneComponent>("RootScene");
	SetRootComponent(SceneRootComp);
	
	FloorMesh = CreateDefaultSubobject<UStaticMeshComponent>("Floor");
	FloorMesh->SetupAttachment(SceneRootComp);

	RightWallMesh = CreateDefaultSubobject<UStaticMeshComponent>("RightWall");
	RightWallMesh->SetupAttachment(FloorMesh);

	LeftWallMesh = CreateDefaultSubobject<UStaticMeshComponent>("LeftWall");
	LeftWallMesh->SetupAttachment(FloorMesh);

	EndTrigger = CreateDefaultSubobject<UBoxComponent>("EndTrigger");
	EndTrigger->SetupAttachment(SceneRootComp);
	
	SpawnArea = CreateDefaultSubobject<UBoxComponent>("SpawnArea");
	SpawnArea->SetupAttachment(SceneRootComp);

	AttachPoint = CreateDefaultSubobject<UArrowComponent>("AttachPoint");
	AttachPoint->SetupAttachment(SceneRootComp);
}


void AOB_Tile::BeginPlay()
{
	Super::BeginPlay();
	EndTrigger->OnComponentBeginOverlap.AddDynamic(this, &AOB_Tile::OnEndTrigger);

	for(int i = 0; i < EnemiesOnTile; i++)
		SpawnEnemies();
	

	for(int i = 0; i < ObstaclesOnTile; i++)
		SpawnObstacles();
	

	for(int i = 0; i < PickUpOnTile; i++)
		SpawnPickUps();
	
}

void AOB_Tile::Tick(float DeltaTime) { Super::Tick(DeltaTime); }

void AOB_Tile::OnEndTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(Cast<AOB_Character>(OtherActor))
	{
		OnExitTile.Broadcast(this);
	}
}


TSubclassOf<AActor> AOB_Tile::GetClassInMapWithRate(TMap<TSubclassOf<AActor>, float> Map)
{
	const float RandWeight = FMath::FRandRange(0.0f,1.0f);
	float TotalWeight = 0.0f;

	TSubclassOf<AActor> ClassPick = nullptr;
	for (auto& [Class, SpawnRate] : Map)
	{
		TotalWeight += SpawnRate;
		if(RandWeight <= TotalWeight)
		{
			ClassPick = Class;
			break;
		}
	}
	return ClassPick;
}


void AOB_Tile::SpawnEnemies()
{
	const TSubclassOf<AActor> EnClass = GetClassInMapWithRate(EnemiesClasses);
	if(EnClass == nullptr) return;
	
	const FVector Location = UKismetMathLibrary::RandomPointInBoundingBox(SpawnArea->GetComponentLocation(),
																		SpawnArea->GetScaledBoxExtent()) + FVector(0,0,100);

	FActorSpawnParameters ActorSpawnParams;
	Enemies.Add(GetWorld()->SpawnActor<AOB_EnemyBase>(EnClass, Location, FRotator(0,180,0)));
}


void AOB_Tile::SpawnObstacles()
{
	const TSubclassOf<AActor> ObsClass = GetClassInMapWithRate(ObstacleClasses);
	if(ObsClass == nullptr) return;
	
	const FVector Location = UKismetMathLibrary::RandomPointInBoundingBox(SpawnArea->GetComponentLocation(), SpawnArea->GetScaledBoxExtent());
	const FTransform Transform = UKismetMathLibrary::MakeTransform(Location, FRotator(0));

	UChildActorComponent* ChildActorComp = NewObject<UChildActorComponent>(this);
	ChildActorComp->SetWorldTransform(Transform);
	ChildActorComp->SetChildActorClass(ObsClass);
	ChildActorComp->RegisterComponent();
}


void AOB_Tile::SpawnPickUps()
{
	const TSubclassOf<AActor> PickUpClass = GetClassInMapWithRate(PickUpClasses);
	if(PickUpClass == nullptr) return;
	
	const FVector Location = UKismetMathLibrary::RandomPointInBoundingBox(SpawnArea->GetComponentLocation(), SpawnArea->GetScaledBoxExtent());
	const FTransform Transform = UKismetMathLibrary::MakeTransform(Location + FVector(0,0,15), FRotator(0));

	UChildActorComponent* ChildActorComp = NewObject<UChildActorComponent>(this);
	ChildActorComp->SetWorldTransform(Transform);
	ChildActorComp->SetChildActorClass(PickUpClass);
	ChildActorComp->RegisterComponent();
}


void AOB_Tile::ToDestroy()
{
	for (auto en : Enemies)
		if(IsValid(en) && en->GetCurrentState() == IDLE)
		{
			GetWorldTimerManager().ClearAllTimersForObject(en);
			en->Destroy();
		}
	Destroy();
}