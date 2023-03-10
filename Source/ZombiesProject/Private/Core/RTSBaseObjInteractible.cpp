// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/RTSBaseObjInteractible.h"

#include "Components/DecalComponent.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ARTSBaseObjInteractible::ARTSBaseObjInteractible()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent = RootScene;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootScene);

	DecalSelectionComponent = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalSelectionComponent"));
	DecalSelectionComponent->ToggleVisibility(false);
	DecalSelectionComponent->SetupAttachment(StaticMeshComponent);
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
	DecalSelectionComponent->ToggleVisibility(true);
	UKismetSystemLibrary::PrintString(GetWorld(),"OnSelect");
}

void ARTSBaseObjInteractible::OnDeselect_Implementation()
{
	IRTSInteractable::OnDeselect_Implementation();
	DecalSelectionComponent->ToggleVisibility(false);
	UKismetSystemLibrary::PrintString(GetWorld(),"OnDeselect");
}

bool ARTSBaseObjInteractible::IsUserController_Implementation()
{
	return bIsUserController;
	
}

