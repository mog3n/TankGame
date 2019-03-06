// Copyright should be here but im lazy af lmao idk what company this is for


#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"

#include "Engine/Public/DrawDebugHelpers.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Instance of TankAimingComponent
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}


void ATank::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	TankAimingComponent->SetBarrelReference(BarrelToSet);
	Barrel = BarrelToSet;
}

void ATank::SetTurretReference(UTankTurret* TurretToSet) {
	TankAimingComponent->SetTurretReference(TurretToSet);
}

void ATank::Fire()
{
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
	
	// UE_LOG(LogTemp, Warning, TEXT("Fire"));
	if (!Barrel) { return; }
	if (!isReloaded) { return; }

	// Spawn a projectile
	FVector SpawnLocation = Barrel->GetSocketLocation(FName("Projectile"));
	FRotator SpawnRotation = Barrel->GetSocketRotation(FName("Projectile"));
	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, SpawnLocation, SpawnRotation);
	// Launch it
	Projectile->LaunchProjectile(FiringSpeed);

	LastFireTime = FPlatformTime::Seconds();
}


// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATank::AimAt(FVector HitLocation)
{
	TankAimingComponent->AimAt(HitLocation, FiringSpeed);

	// Visualize the aim targets
	FVector Start = GetActorLocation();
	FVector End = HitLocation;
	// DrawDebugLine(GetWorld(), Start, End, FColor(255, 0, 0), false, -1.f, 100, 10.f);
}

