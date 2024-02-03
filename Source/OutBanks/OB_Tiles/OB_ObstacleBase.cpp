﻿#include <OutBanks/OB_Tiles/OB_ObstacleBase.h>


AOB_ObstacleBase::AOB_ObstacleBase()
{
	PrimaryActorTick.bCanEverTick = true;
	
	SceneRootComp = CreateDefaultSubobject<USceneComponent>("RootScene");
	SetRootComponent(SceneRootComp);
	
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComp->SetupAttachment(SceneRootComp);
}