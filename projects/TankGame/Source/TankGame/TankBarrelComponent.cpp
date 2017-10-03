// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrelComponent.h"
#include "Runtime/Engine/Classes/Engine/StaticMesh.h"


void UTankBarrelComponent::Elevate( float RelativeSpeed )
{
	RelativeSpeed = FMath::Clamp(RelativeSpeed, -1.f, 1.f);
	//UE_LOG( LogTemp, Warning, TEXT( "Elevate Barrel at speed %f" ), RelativeSpeed);
	float ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->GetDeltaSeconds();
	float RawElevation = FMath::Clamp(RelativeRotation.Pitch + ElevationChange, MinElevationDegrees, MaxElevationDegrees);

	SetRelativeRotation( FRotator(RawElevation, 0.f, 0.f) );
}
