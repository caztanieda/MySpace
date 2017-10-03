// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrackComponent.h"

void UTankTrackComponent::SetThrottle( float Throttle )
{
	UE_LOG( LogTemp, Warning, TEXT( "SetTrackThrottle %f" ), Throttle );
	
	AddForceAtLocation( GetForwardVector() * MaxAppliedForce * Throttle, GetComponentLocation() );
}