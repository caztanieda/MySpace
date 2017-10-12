// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "TankBarrelComponent.h"
#include "TankTurretComponent.h"
#include "Projectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.SetTickFunctionEnable( true );
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UTankAimingComponent::TickComponent( float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	if( FiringStatus != EFiringStatus::Reloading )
	{
		FiringStatus = IsBarrelMoving() ? EFiringStatus::Aiming : EFiringStatus::Locked;
	}
}

void UTankAimingComponent::Initialize( UTankTurretComponent * TurretToSet, UTankBarrelComponent * BarrelToSet )
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

inline void UTankAimingComponent::AimAt( FVector HitLocation )
{
	if( !ensure( Barrel ) ) return;
	FVector SpawnerLocation = Barrel->GetSocketLocation( "Spawner" );
	//UE_LOG( LogTemp, Warning, TEXT("SpawnerLocation %s"), *SpawnerLocation.ToString() );
	//DrawDebugPoint(
	//	GetWorld(),
	//	SpawnerLocation,
	//	100.f,
	//	FColor::Red );
	FVector OUTVelocity;

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity( GetWorld(), OUTVelocity,
		SpawnerLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0.f,
		0.f,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if( bHaveAimSolution )
	{

		AimDirection = OUTVelocity.GetSafeNormal();

		MoveBarrelTowards();
		MoveTurretTowards();
		//DrawDebugDirectionalArrow( GetWorld(), SpawnerLocation, SpawnerLocation + OUTVelocity, 100.f, FColor::Red );
	}
	else
	{
		//UE_LOG( LogTemp, Warning, TEXT( "Have no aimSolution" ) );
	}
}

void UTankAimingComponent::MoveBarrelTowards()
{
	auto BarrelAsRotation = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelAsRotation;
	Barrel->Elevate( DeltaRotator.Pitch );
}

void UTankAimingComponent::MoveTurretTowards()
{
	auto TurretAsRotation = Turret->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - TurretAsRotation;
	
	//UE_LOG( LogTemp, Warning, TEXT( "Rotate turret %f" ), Turret->RelativeRotation.Yaw + DeltaRotator.Yaw );

	Turret->Rotate( DeltaRotator.Yaw );
}


void UTankAimingComponent::Fire()
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

	        FTimerManager& TimerManager = GetWorld()->GetTimerManager();
	        TankReadyToFire = false;
			FiringStatus = EFiringStatus::Reloading;
	        TimerManager.SetTimer( FireRateTimerHandle, [this] {
	            TankReadyToFire = true;
				FiringStatus = IsBarrelMoving() ? EFiringStatus::Aiming : EFiringStatus::Locked;
	        }, FireRate, false );
	    }
	}
}

bool UTankAimingComponent::IsBarrelMoving() const
{
	bool Result = true;
	if( ensure( Barrel ) )
	{
		Result = !AimDirection.Equals( Barrel->GetForwardVector().GetSafeNormal(), 0.1f );
	}

	return Result;
}