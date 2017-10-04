// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrackComponent.h"

void UTankMovementComponent::Initialize( UTankTrackComponent* RightTrackToSet, UTankTrackComponent* LeftTrackToSet )
{
	RightTrack = RightTrackToSet;
	LeftTrack = LeftTrackToSet;
}

void UTankMovementComponent::IntendMoveForward( float Throw )
{
	LeftTrack->SetThrottle( Throw );
	RightTrack->SetThrottle( Throw );
}

void UTankMovementComponent::IntendTurnRight( float Throw )
{
	LeftTrack->SetThrottle( Throw );
	RightTrack->SetThrottle( -Throw );
}

void UTankMovementComponent::RequestDirectMove( const FVector& MoveVelocity, bool bForceMaxSpeed )
{
	//Super::RequestDirectMove( const FVector& MoveVelocity, bool bForceMaxSpeed );
	UE_LOG( LogTemp, Warning, TEXT( "RequestDirectMove %s" ), *MoveVelocity.ToString() );

}