// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Engine/World.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG( LogTemp, Warning, TEXT( "Grabber is here!!!" ) );
	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);

	//UE_LOG( LogTemp, Warning, TEXT( "Viewport Position %s" ), *PlayerViewPointLocation.ToString() );
	//UE_LOG( LogTemp, Warning, TEXT( "Viewport Rotation %s" ), *PlayerViewPointRotation.ToString() );

	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

	DrawDebugLine( GetWorld(), PlayerViewPointLocation, LineTraceEnd, FColor::Red, false, 0.f, 0, 20.f );

	FHitResult HitResult;
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery( ECollisionChannel::ECC_PhysicsBody );
	bool Result = GetWorld()->LineTraceSingleByObjectType( HitResult,
		PlayerViewPointLocation, LineTraceEnd, ObjectQueryParams );
	if( Result )
	{
		UE_LOG( LogTemp, Warning, TEXT( "Hitted with %s" ), *HitResult.GetActor()->GetName() );
	}
}

