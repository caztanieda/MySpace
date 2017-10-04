// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrackComponent;
/**
 * 
 */
UCLASS( ClassGroup = ( Custom ), meta = ( BlueprintSpawnableComponent ) )
class TANKGAME_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
	
public:

	virtual void RequestDirectMove( const FVector& MoveVelocity, bool bForceMaxSpeed ) override;

	UFUNCTION( BlueprintCallable )
	void IntendMoveForward( float Throw );

	UFUNCTION( BlueprintCallable )
	void IntendTurnRight( float Throw );

	UFUNCTION( BlueprintCallable )
		void Initialize( UTankTrackComponent* RightTrackToSet, UTankTrackComponent* LeftTrackToSet );

	UTankTrackComponent* LeftTrack = nullptr;
	UTankTrackComponent* RightTrack = nullptr;
};
