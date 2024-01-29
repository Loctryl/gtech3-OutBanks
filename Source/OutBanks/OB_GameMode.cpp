
#include "OB_GameMode.h"
#include "OutBanks/OB_Character/OB_Character.h"
#include "UObject/ConstructorHelpers.h"

AOB_GameMode::AOB_GameMode()
	: Super()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/OutBanks/Blueprints/OBP_Character"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
	
}
