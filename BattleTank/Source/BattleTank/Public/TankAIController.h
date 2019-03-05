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
	void Tick(float TimeDelta) override;
	void BeginPlay() override;

private:
	ATank* GetTankPawn() const;
	ATank* GetPlayerTank() const;

	// vars
	ATank* ThisTankPawn;
	ATank* TargetTankPawn;

};
