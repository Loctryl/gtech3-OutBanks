#include <OutBanks/Enemies/OB_EnemyBaseController.h>
#include "OutBanks/Enemies/OB_EnemyBase.h"
#include "OutBanks/OB_Character/OB_Character.h"


AOB_EnemyBaseController::AOB_EnemyBaseController()
{
	PrimaryActorTick.bCanEverTick = true;
	
}

void AOB_EnemyBaseController::BeginPlay()
{
	Super::BeginPlay();

	AOB_EnemyBase* EnemyRef = Cast<AOB_EnemyBase>(GetPawn());

	EnemyRef->OnStateChange.AddDynamic(this, &AOB_EnemyBaseController::OnPawnStateChange);
}

void AOB_EnemyBaseController::Tick(float DeltaTime) 
{ 
	Super::Tick(DeltaTime);

	if(PlayerToChase && Chasing)
	{
		MoveToActor(PlayerToChase, 1);
	}
}

void AOB_EnemyBaseController::OnPawnStateChange(BaseStates NewState, AOB_Character* Player)
{
	switch (NewState)
	{
		case CHASE:
			PlayerToChase = Player;
			Chasing = true;
			break;
		case IDLE:
			PlayerToChase = Player;
			Chasing = false;
			StopMovement();
			break;
		case ATTACK:
			PlayerToChase = Player;
			Chasing = false;
			StopMovement();
			break;
	}
}
