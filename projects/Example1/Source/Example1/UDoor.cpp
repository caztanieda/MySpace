// Fill out your copyright notice in the Description page of Project Settings.

#include "UDoor.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UUDoor::UUDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UUDoor::BeginPlay()
{
	Super::BeginPlay();
	
	// ...
	
}


// Called every frame
void UUDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	static float Yaw = 0.f;
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AActor* Door = GetOwner();
	Door->SetActorRotation( FRotator( 0.f, Yaw, 0.f ) );
	Yaw += DeltaTime*10.f;
	// ...
}

