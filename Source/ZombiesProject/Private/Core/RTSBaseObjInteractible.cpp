// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/RTSBaseObjInteractible.h"

#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ARTSBaseObjInteractible::ARTSBaseObjInteractible()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ARTSBaseObjInteractible::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARTSBaseObjInteractible::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARTSBaseObjInteractible::OnAction_Implementation()
{
	IRTSInteractable::OnAction_Implementation();
}

void ARTSBaseObjInteractible::OnSelect_Implementation()
{
	IRTSInteractable::OnSelect_Implementation();
	UKismetSystemLibrary::PrintString(GetWorld(),"OnSelect");
}

void ARTSBaseObjInteractible::OnDeselect_Implementation()
{
	IRTSInteractable::OnDeselect_Implementation();
	UKismetSystemLibrary::PrintString(GetWorld(),"OnDeselect");
}

