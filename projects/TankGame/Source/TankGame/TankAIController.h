// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class TANKGAME_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
    ATank* GetPlayerTank() const;
    ATank* GetControlledTank() const;
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
	
};
