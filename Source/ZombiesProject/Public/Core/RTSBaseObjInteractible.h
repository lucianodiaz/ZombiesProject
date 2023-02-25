// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/RTSInteractable.h"
#include "RTSBaseObjInteractible.generated.h"

UCLASS()
class ZOMBIESPROJECT_API ARTSBaseObjInteractible : public AActor, public IRTSInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARTSBaseObjInteractible();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

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