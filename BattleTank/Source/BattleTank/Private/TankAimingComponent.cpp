// Copyright should be here but im lazy af lmao idk what company this is for


#include "TankAimingComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"
#include "Core/Public/Math/Rotator.h"


UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}



void UTankAimingComponent::AimAt(FVector Location, float FiringSpeed)
{
	if (!Barrel) {return;}
	FVector OutLaunchVelocity = FVector();
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	
	// Calculate velocity
	bool didGetProjectileVelocity = UGameplayStatics::SuggestProjectileVelocity(
		GetWorld(),
		OutLaunchVelocity,
		StartLocation,
		Location,
		FiringSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if (didGetProjectileVelocity) {
		//UE_LOG(LogTemp, Warning, TEXT("%s is aiming at: %s"), *GetOwner()->GetName(), *AimDirection.ToString());
	}

	auto AimDirection = OutLaunchVelocity.GetSafeNormal();
	MoveBarrelTowards(AimDirection);

}

void UTankAimingComponent::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	Barrel = BarrelToSet;
}


void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) {
	// get diff between current rotation and aim direction
	// given max elevation speed and frame time
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	// Move barrel the right amount
	Barrel->Elevate(5); //TODO remove magic num

	//UE_LOG(LogTemp, Warning, TEXT("BarrelRotator: %s, Aim: %s"), *BarrelRotator.ToString(), *AimAsRotator.ToString());
}