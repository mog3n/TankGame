// Copyright should be here but im lazy af lmao idk what company this is for

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

// Forward declaration
class ATank;
class UTankAimingComponent;

/**
 * Helps the player aim
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// Methods
protected:
	UFUNCTION(BlueprintCallable, Category="Setup")
		ATank* GetControlledTank() const;

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
		void FoundAimingComponent(UTankAimingComponent* AimCompRef);

private:
	UTankAimingComponent* AimingComponent;

public:
	void AimTowardsCrosshair();
	bool GetCrosshairHitLocation(FVector &HitLocation);
	bool GetLookRotationFromCrosshair(FVector2D ScreenPosition, FVector &LookDirection);
	bool GetLookHitPosition(FVector LookDirection, FVector &HitLocation);

	// Vars
	ATank* ControlledTank;
	UPROPERTY(EditAnywhere)
		float CrosshairY = 0.40;
	UPROPERTY(EditAnywhere)
		float CrosshairX = 0.50;
	UPROPERTY(EditAnywhere)
		float LineTraceRange = 1000000.f; // in cm
};
