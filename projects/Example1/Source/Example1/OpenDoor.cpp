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
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	APawn* Pawn = PlayerController->GetPawn();
	PawnActorThatOpens = Pawn;
	
}

void UOpenDoor::OpenDoor()
{
	GetOwner()->SetActorRotation( FRotator( 0.f, OpenDoorAngle, 0.f ) );
}

void UOpenDoor::CloseDoor()
{
	GetOwner()->SetActorRotation( FRotator( 0.f, CloseDoorAngle, 0.f ) );
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if( GetTotalMassOfActorsOnPlate() > TotalMassToOpen )//PressurePlate->IsOverlappingActor( PawnActorThatOpens ) )
	{
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}
	
	if( GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay )
	{
		CloseDoor();
	}
	// ...
}

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
    float TotalMass = 0.f;
    TArray<AActor*> OverlappingActors;
    PressurePlate->GetOverlappingActors(OverlappingActors);
    for( AActor* Actor : OverlappingActors)
    {
        UE_LOG( LogTemp, Warning, TEXT( "Overlapped with %s" ), *Actor->GetName() );
        TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
    }
    return TotalMass;
}
