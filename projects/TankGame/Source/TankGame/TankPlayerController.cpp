// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"

#include "Tank.h"
#include "TankAimingComponent.h"

ATank* ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();
    auto ControlledTank = GetControlledTank();
	PrimaryActorTick.bCanEverTick = true;
    if(!ControlledTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerController not possesing a tank"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing: %s"), *ControlledTank->GetName());
    }

	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	FoundTankAimingComponent( AimingComponent );
}

void ATankPlayerController::Tick(float DeltaTime)
{
    Super::Tick( DeltaTime );
    AimTowardsCrossHair();
}

void ATankPlayerController::AimTowardsCrossHair()
{
    FVector HitLocation;
    if(GetSightRayHitLocation(HitLocation))
    {
		ATank* Tank = GetControlledTank();
		if( Tank )
		{
			Tank->AimAt( HitLocation );
		}
    }
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OUTHitLocation ) const
{
    //Find the crosshair position
    int32 ViewportSizeX, ViewportSizeY;
    GetViewportSize(ViewportSizeX, ViewportSizeY);
    
    auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
    //"De-p-roject" the screen position of the crosshair to a world direction
    FVector LookDirection;
    if(GetLookDirection(ScreenLocation, LookDirection))
    {
        //UE_LOG(LogTemp, Warning, TEXT("World direction %s"), *LookDirection.ToString());
		GetHitVectorHitLocation(LookDirection, OUTHitLocation);
    }
    
    //Line-trace along that look direction, and see what we hit (up to max range)


    return true;
}

bool ATankPlayerController::GetHitVectorHitLocation( FVector LookDirection, FVector& HitLocation ) const
{
	FHitResult HitResult;
	FVector CameraLocation = PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = CameraLocation + LookDirection * LineTraceRange;
	bool result = GetWorld()->LineTraceSingleByChannel( HitResult, CameraLocation, EndLocation, ECollisionChannel::ECC_Visibility );
	AActor* Actor = HitResult.GetActor();
	if( Actor )
	{
		//UE_LOG( LogTemp, Warning, TEXT( "Traced actor %s" ), *actor->GetName() );
		DrawDebugPoint(
			GetWorld(),
			HitResult.Location,
			10.f,
			FColor::Blue
		);

		if( Cast<ATank>( Actor ) )
		{
			
		}

		HitLocation = HitResult.Location;
	}
	return result;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
    FVector CameraWorldLocation;
    return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
}
