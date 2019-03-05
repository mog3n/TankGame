// Copyright should be here but im lazy af lmao idk what company this is for

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), hidecategories=("Collision"))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Elevate(float DegreesPerSecond);

private:
	UPROPERTY(EditAnywhere, Category=Setup)
		float MaxDegPerSec = 90.f;
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxElevationInDeg = 40.f;
	UPROPERTY(EditAnywhere, Category = Setup)
		float MinElevationInDeg = -2.f;
};
