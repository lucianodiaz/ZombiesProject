// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombiesContent/RTSZombieController.h"

#include "Perception/AIPerceptionComponent.h"

ARTSZombieController::ARTSZombieController()
{
	RTSPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("RTSPerceptionComponent"));
}

void ARTSZombieController::BeginPlay()
{
	Super::BeginPlay();
	RunBehaviorTree(BTAsset);
}
