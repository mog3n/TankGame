// Copyright should be here but im lazy af lmao idk what company this is for

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankAimingComponent;
class UTankBarrel;
class UTankTurret;
class AProjectile;
class UTankMovementComponent;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetBarrelReference(UTankBarrel* BarrelToSet);
	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetTurretReference(UTankTurret* TurretToSet);
	UFUNCTION(BlueprintCallable, Category=Setup)
		void Fire();
	UPROPERTY(EditAnywhere)
		TSubclassOf<AProjectile> ProjectileBlueprint;
	// Local barrel ref for spawning projectile
	UPROPERTY(EditAnywhere, Category=Firing)
		float FiringSpeed = 20000.f;

	UPROPERTY(EditDefaultsOnly)
	float ReloadTimeInSeconds = 3.f;
	UTankBarrel* Barrel = nullptr;

private:
	double LastFireTime = 0;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UTankAimingComponent* TankAimingComponent = nullptr;
	UPROPERTY(BlueprintReadOnly)
		UTankMovementComponent* TankMovementComponent = nullptr;

public:	
	// Called every frame
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void AimAt(FVector HitLocation);
};
