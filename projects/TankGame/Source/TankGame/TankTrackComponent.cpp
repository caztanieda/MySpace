// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrackComponent.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"

void UTankTrackComponent::OnHit( UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit )
{
	ApplySidewayForces();
	DriveTrack();
	CurrentThrottle = 0.f;
}

UTankTrackComponent::UTankTrackComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.SetTickFunctionEnable( true );
}

void UTankTrackComponent::BeginPlay()
{
	OnComponentHit.AddDynamic( this, &UTankTrackComponent::OnHit );
}

void UTankTrackComponent::SetThrottle( float Throttle )
{
	CurrentThrottle += Throttle;

	CurrentThrottle = FMath::Clamp( CurrentThrottle, -1.f, 1.f );
	//UE_LOG( LogTemp, Warning, TEXT( "SetTrackThrottle %f" ), Throttle );
}

void UTankTrackComponent::DriveTrack()
{
	AddForceAtLocation( GetForwardVector() * MaxAppliedForce * CurrentThrottle, GetSocketLocation( "Force" ) );
}

void UTankTrackComponent::TickComponent( float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
}

void UTankTrackComponent::ApplySidewayForces()
{
	float DeltaTime = GetWorld()->GetDeltaSeconds();
	float SlippageSpeed = FVector::DotProduct( GetRightVector(), GetComponentVelocity() );

	FVector CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();

	UStaticMeshComponent* TankBody = Cast<UStaticMeshComponent>( GetOwner()->GetRootComponent() );

	auto CorrectionForce = TankBody->GetMass() * CorrectionAcceleration / 2.f;//Two tracks 


	TankBody->AddForce( CorrectionForce );
}
