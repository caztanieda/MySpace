// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Projectile.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "TankBarrelComponent.h"
#include "Runtime/Engine/Public/TimerManager.h"

// Sets default values
ATank::ATank()
{
     // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();

	TankAimingComponent = FindComponentByClass<UTankAimingComponent>();
}

void ATank::Initialize( UTankTurretComponent* TurretToSet, UTankBarrelComponent* BarrelToSet )
{
    Turret = TurretToSet;
    Barrel = BarrelToSet;
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ATank::AimAt( FVector HitLocation )
{
    //UE_LOG( LogTemp, Warning, TEXT( "%s aiming %s" ), *GetName(), *HitLocation.ToString() );
    if( TankAimingComponent )
    {
        TankAimingComponent->AimAt( HitLocation, LaunchSpeed );
    }
}

void ATank::Fire()
{
    if( TankReadyToFire )
    {
        UE_LOG( LogTemp, Warning, TEXT( "Fire" ) );
        UWorld* World = GetWorld();
        if( Barrel )
        {
            FVector Location = Barrel->GetSocketLocation( FName( "Spawner" ) );
            FRotator Rotation = Barrel->GetSocketRotation( FName( "Spawner" ) );
            auto Projectile = World->SpawnActor<AProjectile>( ProjectileBlueprint, Location, Rotation );
            Projectile->LaunchProjectile( LaunchSpeed );

            FTimerManager& TimerManager = GetWorldTimerManager();
            TankReadyToFire = false;
            TimerManager.SetTimer( FireRateTimerHandle, [this] {
                TankReadyToFire = true;
            }, FireRate, false );
        }
    }
}
