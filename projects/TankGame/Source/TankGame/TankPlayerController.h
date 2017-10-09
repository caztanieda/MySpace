// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;
/**
 * 
 */
UCLASS()
class TANKGAME_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintCallable)
    ATank* GetControlledTank() const;

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    
    void AimTowardsCrossHair();
    bool GetSightRayHitLocation(FVector& OUTHitLocation ) const;
    bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
	bool GetHitVectorHitLocation( FVector LookDirection, FVector& HitLocation ) const;

public:
	UFUNCTION( BlueprintImplementableEvent, Category = "Setup" )
	void FoundTankAimingComponent( UTankAimingComponent* AimComp );

private:
    
    UPROPERTY(EditAnywhere)
        float CrosshairXLocation = 0.5f;
    
    UPROPERTY(EditAnywhere)
        float CrosshairYLocation = 0.33333f;

	UPROPERTY(EditAnywhere)
		float LineTraceRange = 100000.f;
};
