// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"




ATank* ATankAIController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
    ATank* playerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
    return playerTank;
}

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
    auto ControlledTank = GetControlledTank();
    if(!ControlledTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("TankAIController not possesing a tank"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("TankAIController possessing: %s"), *ControlledTank->GetName());
    }
    
    auto PlayerTank = GetPlayerTank();
    
    if(!PlayerTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("AIController hasn't found PlayerTank"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("AIController found PlayerTank : %s"), *PlayerTank->GetName());
    }
}

void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick( DeltaTime );
}