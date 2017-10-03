// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TankAimingComponent.h"
#include "Tank.generated.h"

class UTankBarrelComponent;
class UTankTurretComponent;
class AProjectile;

UCLASS()
class TANKGAME_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	UFUNCTION(BlueprintCallable, Category=Setup)
	void SetBarrelReference( UTankBarrelComponent* BarrelToSet );

	UFUNCTION( BlueprintCallable, Category = Setup )
	void SetTurretReference( UTankTurretComponent* TurretToSet );

	UFUNCTION( BlueprintCallable, Category = Action )
		void Fire();

	UPROPERTY( EditDefaultsOnly, Category = Firing )
		float LaunchSpeed = 4000.f;

	UPROPERTY( EditDefaultsOnly, Category = Firing )
		float FireRate = 2.5f;

	UPROPERTY( EditDefaultsOnly, Category = Firing )
		TSubclassOf<AProjectile> ProjectileBlueprint = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UTankAimingComponent* TankAimingComponent = nullptr;
	UTankBarrelComponent* Barrel = nullptr;
	bool TankReadyToFire = true;
	FTimerHandle FireRateTimerHandle;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void AimAt( FVector HitLocation );
	
	
};
