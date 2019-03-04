// Copyright should be here but im lazy af lmao idk what company this is for

#pragma once


#include "Tank.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
public:
	ATank* GetTankPawn() const;
	ATank* GetPlayerTank() const;
	void BeginPlay() override;
};
