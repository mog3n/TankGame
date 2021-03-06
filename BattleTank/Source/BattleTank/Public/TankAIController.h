// Copyright should be here but im lazy af lmao idk what company this is for

#pragma once



#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;
class UTankAimingComponent;

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

	UPROPERTY(EditDefaultsOnly)
	float AcceptableRadius = 10;

private:
	// vars
	ATank* ThisTankPawn;
	ATank* TargetTankPawn;
	UTankAimingComponent* AimingComponent;

};
