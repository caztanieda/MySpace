// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Projectile.h"
#include "Runtime/Engine/Classes/Engine/World.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>( TEXT( "Aiming Component" ) );
}

void ATank::SetBarrelReference( UTankBarrelComponent * BarrelToSet )
{
	TankAimingComponent->SetBarrelReference( BarrelToSet );
}

void ATank::SetTurretReference( UTankTurretComponent * TurretToSet )
{
	TankAimingComponent->SetTurretReference( TurretToSet );
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::AimAt( FVector HitLocation )
{
	//UE_LOG( LogTemp, Warning, TEXT( "%s aiming %s" ), *GetName(), *HitLocation.ToString() );
	TankAimingComponent->AimAt( HitLocation, LaunchSpeed);
}

void ATank::Fire()
{
	UE_LOG( LogTemp, Warning, TEXT( "Fire" ) );
	UWorld* World = GetWorld();
	World->SpawnActor<AProjectile>( ProjectileBlueprint::GetClass() );
}
