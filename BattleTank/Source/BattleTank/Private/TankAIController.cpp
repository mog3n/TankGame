// Copyright should be here but im lazy af lmao idk what company this is for


#include "TankAIController.h"
#include "Engine/World.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
	ThisTankPawn = GetTankPawn();
	TargetTankPawn = GetPlayerTank();
}

void ATankAIController::Tick(float TimeDelta) {
	Super::Tick(TimeDelta);
	if (ThisTankPawn) {
		// Move towards player


		// Aim at player
		ThisTankPawn->AimAt(TargetTankPawn->GetActorLocation());
	}

}

ATank* ATankAIController::GetTankPawn() const {
	ATank* TankPawn = Cast<ATank>(GetPawn());
	if (TankPawn) {
		//UE_LOG(LogTemp, Warning, TEXT("AI is controlling: %s"), *TankPawn->GetName());
	}
	else {
		//UE_LOG(LogTemp, Warning, TEXT("AI is NOT controlling this tank."));
	}
	return TankPawn;
}

ATank * ATankAIController::GetPlayerTank() const
{
	// Get the player tank (from pawn)
	ATank* PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	// Check
	if (PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("AI Tank is targetting: %s"), *PlayerTank->GetName());
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI Tank is NOT targetting anything"));
	}
	return PlayerTank;
}