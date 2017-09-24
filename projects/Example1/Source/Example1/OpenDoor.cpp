// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"

#include "Engine/TriggerVolume.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	if( !PressurePlate )
	{
		UE_LOG( LogTemp, Error, TEXT( "Can't find pressure plate %s" ), *GetOwner()->GetName() );
	}
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if( GetTotalMassOfActorsOnPlate() > TotalMassToOpen )
	{
		OnOpen.Broadcast();
	}
	else
	{
		OnClose.Broadcast();
	}
	// ...
}

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
    float TotalMass = 0.f;
    TArray<AActor*> OverlappingActors;
	if( PressurePlate )
	{
		PressurePlate->GetOverlappingActors( OverlappingActors );
		for( AActor* Actor : OverlappingActors )
		{
			//UE_LOG( LogTemp, Warning, TEXT( "Overlapped with %s" ), *Actor->GetName() );
			TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		}
	}
    return TotalMass;
}
