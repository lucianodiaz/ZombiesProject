// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "RTSZombieController.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBIESPROJECT_API ARTSZombieController : public AAIController
{
	GENERATED_BODY()

	
public:
	ARTSZombieController();
	
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AI")
	UBehaviorTree* BTAsset;

	UPROPERTY(VisibleDefaultsOnly, Category = AI)
	UAIPerceptionComponent* RTSPerceptionComponent;
};
