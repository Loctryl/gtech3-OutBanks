#include <OutBanks/OB_Enemies/OB_EnemyBaseController.h>
#include "OutBanks/OB_Character/OB_Character.h"
#include "OutBanks/OB_Enemies/OB_EnemyBase.h"


void AOB_EnemyBaseController::Tick(float DeltaTime) 
{ 
	Super::Tick(DeltaTime);

	if(PlayerToChase && Chasing)
		MoveToActor(PlayerToChase, 1);
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

void AOB_EnemyBaseController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	AOB_EnemyBase* EnemyRef = Cast<AOB_EnemyBase>(InPawn);

	EnemyRef->OnStateChange.AddDynamic(this, &AOB_EnemyBaseController::OnPawnStateChange);
}