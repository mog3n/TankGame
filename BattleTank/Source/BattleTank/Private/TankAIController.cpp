// Copyright should be here but im lazy af lmao idk what company this is for


#include "TankAIController.h"
#include "Engine/World.h"
#include "Tank.h"
#include "TankAimingComponent.h"
#include "GameFramework/PlayerController.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
	ThisTankPawn = Cast<ATank>(GetPawn());
	AimingComponent = ThisTankPawn->FindComponentByClass<UTankAimingComponent>();

	TargetTankPawn = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

void ATankAIController::Tick(float TimeDelta) {
	Super::Tick(TimeDelta);
	if (!ThisTankPawn) { return; }
	if (!TargetTankPawn) { return; }
	
	// Move towards player
	MoveToActor(TargetTankPawn, AcceptableRadius); //Todo: Check radius is in cm


	// Aim at player
	AimingComponent->AimAt(TargetTankPawn->GetActorLocation());
	// Fire
	AimingComponent->Fire(); // TODO: Limit fire rate

}
