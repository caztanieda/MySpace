// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrelComponent.generated.h"

/**
 * 
 */
UCLASS( ClassGroup = ( Custom ), meta = ( BlueprintSpawnableComponent ) )
class TANKGAME_API UTankBarrelComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	// -1 is min, 1 is max
	void Elevate( float RelativeSpeed );

private:
	UPROPERTY( EditAnywhere, Category=Setup )
		float MaxDegreesPerSecond = 5.f;

	UPROPERTY( EditAnywhere, Category = Setup )
		float MaxElevationDegrees = 40.f;

	UPROPERTY( EditAnywhere, Category = Setup )
		float MinElevationDegrees = 0.f;
};
