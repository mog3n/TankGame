// Copyright should be here but im lazy af lmao idk what company this is for


#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"

#include "GameFramework/Actor.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"
#include "Core/Public/Math/Rotator.h"



UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}
void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) {
	UE_LOG(LogTemp, Warning, TEXT("TICK"));
}


void UTankAimingComponent::Initialize(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}



void UTankAimingComponent::AimAt(FVector Location)
{
	if (!ensure(Barrel)) { UE_LOG(LogTemp, Error, TEXT("Barrel not set on %s"), *GetOwner()->GetName()); return; }
	if (!ensure(Turret)) { UE_LOG(LogTemp, Error, TEXT("Turret not set on %s"), *GetOwner()->GetName());  return; }
	
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
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
		//UE_LOG(LogTemp, Warning, TEXT("%f Aim solution found"), GetWorld()->GetTimeSeconds());
	}

}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) {

	// get diff between current rotation and aim direction
	// given max elevation speed and frame time
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();

	auto DeltaBarrelRotator = AimAsRotator - BarrelRotator;

	// Move barrel the right amount
	Barrel->Elevate(DeltaBarrelRotator.Pitch);
	Turret->Rotate(DeltaBarrelRotator.Yaw);

	//UE_LOG(LogTemp, Warning, TEXT("BarrelRotator: %s, Aim: %s"), *BarrelRotator.ToString(), *AimAsRotator.ToString());
}

void UTankAimingComponent::Fire()
{
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	// UE_LOG(LogTemp, Warning, TEXT("Fire"));
	if (!isReloaded) { return; }
	if (!ensure(ProjectileBlueprint)) { return; } // ensure the projectile blueprint was loaded

	// Spawn a projectile
	FVector SpawnLocation = Barrel->GetSocketLocation(FName("Projectile"));
	FRotator SpawnRotation = Barrel->GetSocketRotation(FName("Projectile"));
	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, SpawnLocation, SpawnRotation);
	// Launch it
	Projectile->LaunchProjectile(FiringSpeed);

	LastFireTime = FPlatformTime::Seconds();
}