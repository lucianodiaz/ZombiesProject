// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/RTSInteractable.h"
#include "RTSBaseCharacters.generated.h"

UCLASS()
class ZOMBIESPROJECT_API ARTSBaseCharacters : public ACharacter, public IRTSInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARTSBaseCharacters();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UDecalComponent* DecalSelectionComponent;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable,Category="Interaction")
	void OnAction();
	virtual void OnAction_Implementation();
	
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable,Category="Interaction")
	void OnSelect();
	virtual void OnSelect_Implementation();
	
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable,Category="Interaction")
	void OnDeselect();
	virtual void OnDeselect_Implementation();
};
