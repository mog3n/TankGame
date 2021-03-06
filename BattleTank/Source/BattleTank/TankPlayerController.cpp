// Copyright should be here but im lazy af lmao idk what company this is for

#include "TankPlayerController.h"

#include "Tank.h"
#include "Engine/World.h"
#include "Engine/Public/DrawDebugHelpers.h"
#include "TankAimingComponent.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ControlledTank = GetControlledTank();
	AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>(); // assume 1 comp
	if (AimingComponent) {
		FoundAimingComponent(AimingComponent);
	}
	else { UE_LOG(LogTemp, Warning, TEXT("No aiming component found at begin play!!! UI will not work properly")); }
	// UE_LOG(LogTemp, Warning, TEXT("Player is controlling: %s"), *ControlledTank->GetName());
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair(); // Aim towards the crosshair...
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn()); // get the pawn as ATank
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!ensure(ControlledTank)) { return; } // Ensure tank exists
	FVector HitLocation;
	if (GetCrosshairHitLocation(HitLocation)) {
		AimingComponent->AimAt(HitLocation);
	}
}

// Get hit location from the camera
bool ATankPlayerController::GetCrosshairHitLocation(FVector &HitLocation)
{
	// find crosshair pos
	// de-proejct screen position to a world direction
	// line trace
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	FVector2D ScreenLocation = FVector2D(ViewportSizeX*CrosshairX, ViewportSizeY*CrosshairY);
	FVector LookDirection;

	// Get the look direction from the crosshair (i.e. rotation relative to world)
	GetLookRotationFromCrosshair(ScreenLocation, LookDirection);
	// Find the ray cast location (Cast the look direction starting at the camera)
	GetLookHitPosition(LookDirection, HitLocation);

	return false ? HitLocation.IsZero() : true;
}

// Gets the look direction
bool ATankPlayerController::GetLookRotationFromCrosshair(FVector2D ScreenLocation, FVector &LookDirection)
{
	FVector t;
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, t, LookDirection);
}

// Get hit position
bool ATankPlayerController::GetLookHitPosition(FVector LookDirection, FVector &HitLocation)
{
	// UE_LOG(LogTemp, Warning, TEXT("LookDirection: %s"), *LookDirection.ToString());
	FVector Start = PlayerCameraManager->GetCameraLocation();
	FVector End = Start + LookDirection * LineTraceRange;
	FCollisionQueryParams Query = FCollisionQueryParams(TEXT(""), false, ControlledTank);
	FHitResult Hit;

	bool didHit = GetWorld()->LineTraceSingleByChannel(
		Hit,
		Start,
		End,
		ECollisionChannel::ECC_Visibility,
		Query
	);
	//DrawDebugLine(GetWorld(),Start,End,FColor(255, 0, 0),false,-1.f,100,10.f);
	HitLocation = Hit.Location; // Set the OUT vector
	return didHit;
}

