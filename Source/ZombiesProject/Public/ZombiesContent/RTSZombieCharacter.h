// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/RTSPawnInterfaces.h"
#include "RTSZombieCharacter.generated.h"

UCLASS()
class ZOMBIESPROJECT_API ARTSZombieCharacter : public ACharacter,public IRTSPawnInterfaces
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARTSZombieCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual bool IsUserController_Implementation() override;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	bool bIsUserController;

	void SetNumberOfObservers_Implementation(int Watcher) override;

	int GetNumberOfObservers_Implementation() override;

private:
	int NumberOfObservers;
};
