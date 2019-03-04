// Copyright should be here but im lazy af lmao idk what company this is for


#include "TankAIController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

ATank* ATankAIController::GetTankPawn() const {
	ATank* TankPawn = Cast<ATank>(GetPawn());
	if (TankPawn) {
		UE_LOG(LogTemp, Warning, TEXT("AI is controlling: %s"), *TankPawn->GetName());
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI is NOT controlling this tank."));
	}
	return TankPawn;
}

ATank * ATankAIController::GetPlayerTank() const
{
	// Get the player tank (from pawn)
	ATank* PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	// Check
	if (PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("AI is targetting: %s"), *PlayerTank->GetName());
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI is NOT targetting anything"));
	}
	return PlayerTank;
}

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
	auto AITank = GetTankPawn();
	auto Playertank = GetPlayerTank();
}