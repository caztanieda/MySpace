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

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKGAME_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	UPROPERTY( BlueprintReadOnly, Category = "State" )
		EFiringStatus FiringStatus = EFiringStatus::Reloading;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize( UTankTurretComponent* TurretToSet, UTankBarrelComponent* BarrelToSet );
public:

	void AimAt( FVector HitLocation, float LaunchSpeed );
private:		
	UTankBarrelComponent* Barrel = nullptr;
	UTankTurretComponent* Turret = nullptr;
	void MoveBarrelTowards( FVector AimDirection );
	void MoveTurretTowards( FVector AimDirection );
	
};