// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurretComponent.h"


void UTankTurretComponent::Rotate( float RelativeSpeed )
{
	RelativeSpeed = FMath::Clamp( RelativeSpeed, -1.f, 1.f );
	//UE_LOG( LogTemp, Warning, TEXT( "Elevate Barrel at speed %f" ), RelativeSpeed);
	float RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->GetDeltaSeconds();

	SetRelativeRotation( FRotator(0.f, RelativeRotation.Yaw + RotationChange, 0.f ) );
}

