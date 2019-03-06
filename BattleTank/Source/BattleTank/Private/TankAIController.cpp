// Copyright should be here but im lazy af lmao idk what company this is for


#include "TankAIController.h"
#include "Engine/World.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
	ThisTankPawn = Cast<ATank>(GetPawn());
	TargetTankPawn = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

void ATankAIController::Tick(float TimeDelta) {
	Super::Tick(TimeDelta);
	if (!ThisTankPawn) { return; }
	if (!TargetTankPawn) { return; }
	// Move towards player

	// Aim at player
	ThisTankPawn->AimAt(TargetTankPawn->GetActorLocation());

	// Fire
	ThisTankPawn->Fire(); // TODO: Limit fire rate

}
