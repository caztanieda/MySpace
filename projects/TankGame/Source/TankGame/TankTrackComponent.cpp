// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrackComponent.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"

void UTankTrackComponent::SetThrottle( float Throttle )
{
	//UE_LOG( LogTemp, Warning, TEXT( "SetTrackThrottle %f" ), Throttle );
	
	AddForceAtLocation( GetForwardVector() * MaxAppliedForce * Throttle, GetSocketLocation("Force") );

	//DrawDebugLine( GetWorld(), GetComponentLocation(), GetComponentLocation() + GetForwardVector() * 1000.f, FColor::Red );

}