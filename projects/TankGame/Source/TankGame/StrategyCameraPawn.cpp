// Fill out your copyright notice in the Description page of Project Settings.

#include "StrategyCameraPawn.h"


// Sets default values
AStrategyCameraPawn::AStrategyCameraPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStrategyCameraPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AStrategyCameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AStrategyCameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

