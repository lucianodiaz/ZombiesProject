// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/RTSBaseCharacters.h"

#include "Components/DecalComponent.h"
#include "Core/RTSPlayerController.h"
#include "GameFramework/GameSession.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ARTSBaseCharacters::ARTSBaseCharacters()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DecalSelectionComponent = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalSelectionComponent"));
	DecalSelectionComponent->SetupAttachment(GetMesh());
	DecalSelectionComponent->ToggleVisibility(false);

	HealthComponent = CreateDefaultSubobject<URTSHealthComponent>(TEXT("HealthComponent"));

	HealthComponent->OnHealthChanged.AddDynamic(this,&ARTSBaseCharacters::OnHealthChanged);

	FogRevealComponent = CreateDefaultSubobject<URTSFogRevealComponent>(TEXT("FogRevealComponent"));
	bIsUserController = false;
}

// Called when the game starts or when spawned
void ARTSBaseCharacters::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ARTSBaseCharacters::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ARTSBaseCharacters::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ARTSBaseCharacters::OnAction_Implementation()
{
	IRTSInteractable::OnAction_Implementation();

	// APlayerController* PC = Cast<APlayerController>(GetController());
	// if(PC)
	// {
	// 	if(UAIBlueprintHelperLibrary::GetBlackboard(this));
	// 	
	// }
	
	UKismetSystemLibrary::PrintString(GetWorld(),"OnAction");
}

void ARTSBaseCharacters::OnSelect_Implementation()
{
	IRTSInteractable::OnSelect_Implementation();
	
	DecalSelectionComponent->ToggleVisibility(true);
	UKismetSystemLibrary::PrintString(GetWorld(),"OnSelect");
}

void ARTSBaseCharacters::OnDeselect_Implementation()
{
	IRTSInteractable::OnDeselect_Implementation();
	DecalSelectionComponent->ToggleVisibility(false);
	UKismetSystemLibrary::PrintString(GetWorld(),"OnDeselect");
}
bool ARTSBaseCharacters::IsUserController_Implementation()
{
	return bIsUserController;
}


void ARTSBaseCharacters::OnHealthChanged(float Health, float HealthDelta, const UDamageType* DamageType,
                                         AController* InstigatedBy, AActor* DamageCauser)
{

	if(Health <= 0.0f)
	{
		//do something of dead's
	}
}
