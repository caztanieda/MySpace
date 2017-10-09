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

	UFUNCTION( BlueprintCallable, Category = Action )
		void Fire();

	UFUNCTION( BlueprintCallable, Category = "Setup" )
		void Initialize(UTankTurretComponent* TurretToSet, UTankBarrelComponent* BarrelToSet);

	UPROPERTY( EditDefaultsOnly, Category = Firing )
		float LaunchSpeed = 4000.f;

	UPROPERTY( EditDefaultsOnly, Category = Firing )
		float FireRate = 2.5f;

	UPROPERTY( EditDefaultsOnly, Category = Firing )
		TSubclassOf<AProjectile> ProjectileBlueprint = nullptr;

protected:

	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent* TankAimingComponent = nullptr;

	UPROPERTY( BlueprintReadOnly )
	UTankBarrelComponent* Barrel = nullptr;

	UPROPERTY( BlueprintReadOnly )
		UTankTurretComponent* Turret = nullptr;

	bool TankReadyToFire = true;
	FTimerHandle FireRateTimerHandle;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AimAt( FVector HitLocation );
	
	
};
