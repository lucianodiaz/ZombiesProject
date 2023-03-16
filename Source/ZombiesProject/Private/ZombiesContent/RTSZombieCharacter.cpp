// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombiesContent/RTSZombieCharacter.h"

#include "ZombiesContent/RTSZombieController.h"

// Sets default values
ARTSZombieCharacter::ARTSZombieCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = ARTSZombieController::StaticClass();

	bIsUserController = false;
}

// Called when the game starts or when spawned
void ARTSZombieCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARTSZombieCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARTSZombieCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

bool ARTSZombieCharacter::IsUserController_Implementation()
{
	return bIsUserController;
}

void ARTSZombieCharacter::SetNumberOfObservers_Implementation(int Watcher)
{
	NumberOfObservers = Watcher;
}

int ARTSZombieCharacter::GetNumberOfObservers_Implementation()
{
	return NumberOfObservers;
}



