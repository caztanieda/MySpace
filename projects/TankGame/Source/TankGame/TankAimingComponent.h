// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrelComponent;
class UTankTurretComponent;

UENUM()
enum class EFiringStatus: uint8
{
	Reloading,
	Aiming,
	Locked
};

class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKGAME_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	virtual void BeginPlay() override;

	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;


	UPROPERTY( BlueprintReadOnly, Category = "State" )
		EFiringStatus FiringStatus = EFiringStatus::Aiming;

	UPROPERTY( EditDefaultsOnly, Category = Firing )
		float LaunchSpeed = 4000.f;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize( UTankTurretComponent* TurretToSet, UTankBarrelComponent* BarrelToSet );


	UFUNCTION( BlueprintCallable, Category = Action )
		void Fire();

	UPROPERTY( EditDefaultsOnly, Category = Firing )
		float FireRate = 2.5f;
	 
	UPROPERTY( EditDefaultsOnly, Category = Firing )
		TSubclassOf<AProjectile> ProjectileBlueprint = nullptr;

public:

	void AimAt( FVector HitLocation );
private:		
	UTankBarrelComponent* Barrel = nullptr;
	UTankTurretComponent* Turret = nullptr;
	bool TankReadyToFire = true;
	FVector AimDirection;
	FTimerHandle FireRateTimerHandle;
	void MoveBarrelTowards();
	void MoveTurretTowards();
	bool IsBarrelMoving() const;
	
};
