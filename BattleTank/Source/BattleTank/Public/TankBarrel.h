// Copyright should be here but im lazy af lmao idk what company this is for

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// -1 to +1 (down/up) max speed
	void Elevate(float RelativeSpeed);

private:
	UPROPERTY(EditAnywhere, Category=Setup)
		float MaxDegPerSec = 90.f;
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxElevationInDeg = 40.f;
	UPROPERTY(EditAnywhere, Category = Setup)
		float MinElevationInDeg = -2.f;
};
