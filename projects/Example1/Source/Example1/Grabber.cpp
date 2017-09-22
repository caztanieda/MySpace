// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Engine/World.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "Components/ActorComponent.h"

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

    FindPhysicsHandleComponent();
    SetupInputComponent();
	
}

void UGrabber::SetupInputComponent()
{
    InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
    
    if( InputComponent )
    {
        InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
        InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
    }
    else
    {
        UE_LOG( LogTemp, Error, TEXT( "Can't find UInputComponent. Owner name %s " ), *GetOwner()->GetName() );
    }
}

void UGrabber::FindPhysicsHandleComponent()
{
    PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
    
    if( !PhysicsHandle )
    {
        UE_LOG( LogTemp, Error, TEXT( "Can't find PhysicsHandleComponent. Owner name %s " ) , *GetOwner()->GetName() );
    }
}

void UGrabber::Grab()
{
    auto HitResult = GetFirstPhysicsBodyInReach();
    auto ComponentToGrab = HitResult.GetComponent();
    
    auto ActorHit = HitResult.GetActor();
    if(ActorHit)
    {
        PhysicsHandle->GrabComponent(
            ComponentToGrab,
            FName(TEXT("")),
            ComponentToGrab->GetOwner()->GetActorLocation(),
            true
        );
    }
}

void UGrabber::Release()
{
    PhysicsHandle->ReleaseComponent();
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
    FHitResult HitResult;
    FCollisionObjectQueryParams ObjectQueryParams;
    ObjectQueryParams.AddObjectTypesToQuery( ECollisionChannel::ECC_PhysicsBody );
    
    FCollisionQueryParams CollisionQueryParams(FName(TEXT("TraceTag")), false, GetOwner());
    
    bool Result = GetWorld()->LineTraceSingleByObjectType( HitResult,
                                                          GetReachLineStart(),
                                                          GetReachLineEnd(),
                                                          ObjectQueryParams,
                                                          CollisionQueryParams );
    if( Result )
    {
        UE_LOG( LogTemp, Warning, TEXT( "Hitted with %s" ), *HitResult.GetActor()->GetName() );
    }
    
    //DrawDebugLine( GetWorld(), PlayerViewPointLocation, LineTraceEnd, FColor::Red, false, 0.f, 0, 20.f );
    
    return HitResult;
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    if(PhysicsHandle->GrabbedComponent)
    {
        auto LineTraceEnd = GetReachLineEnd();
        PhysicsHandle->SetTargetLocation(LineTraceEnd);
    }
}

FVector UGrabber::GetReachLineEnd()
{
    FVector PlayerViewPointLocation;
    FRotator PlayerViewPointRotation;
    
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);
    
    FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
    return LineTraceEnd;
}

FVector UGrabber::GetReachLineStart()
{
    FVector PlayerViewPointLocation;
    FRotator PlayerViewPointRotation;
    
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);

    return PlayerViewPointLocation;
}
