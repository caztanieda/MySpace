// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurretComponent.generated.h"

/**
 * 
 */
UCLASS( ClassGroup = ( Custom ), meta = ( BlueprintSpawnableComponent ) )
class TANKGAME_API UTankTurretComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// -1 is min, 1 is max
	void Rotate( float RelativeSpeed );

private:
	UPROPERTY( EditAnywhere, Category = Setup )
		float MaxDegreesPerSecond = 50.f;
	
};
