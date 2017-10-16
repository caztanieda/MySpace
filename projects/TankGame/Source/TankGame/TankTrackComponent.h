// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrackComponent.generated.h"


UCLASS( ClassGroup = ( Custom ), meta = ( BlueprintSpawnableComponent ) )
class TANKGAME_API UTankTrackComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

private:
		UFUNCTION()
		void OnHit( UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit );

		float CurrentThrottle = 0.f;
public:

	UTankTrackComponent();

	virtual void BeginPlay() override;

	UFUNCTION( BlueprintCallable )
		void SetThrottle( float Throttle );

	void DriveTrack();

	UPROPERTY( EditDefaultsOnly )
		float MaxAppliedForce = 4000000.f;

	virtual void TickComponent( float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction ) override;
	void ApplySidewayForces();
};
