// Copyright should be here but im lazy af lmao idk what company this is for

#include "TankBarrel.h"


void UTankBarrel::Elevate(float RelativeSpeed) {
	//UE_LOG(LogTemp, Warning, TEXT("BarrelElevate: %f"), DegreesPerSecond);
	// ensure relative speed is between 0/1
	RelativeSpeed = FMath::Clamp(RelativeSpeed, -1.f, 1.f);

	auto ElevationChange = RelativeSpeed * MaxDegPerSec * GetWorld()->GetDeltaSeconds();
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;

	float NewElevation = FMath::Clamp(RawNewElevation, MinElevationInDeg, MaxElevationInDeg); // restrict to min/max
	SetRelativeRotation(FRotator(NewElevation, 0, 0));
	// UE_LOG(LogTemp, Warning, TEXT("%s is elevating: %f"), *GetOwner()->GetName(), RelativeSpeed);
}