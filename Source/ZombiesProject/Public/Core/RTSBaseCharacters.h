// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/RTSFogRevealComponent.h"
#include "Components/RTSHealthComponent.h"
#include "GameFramework/Character.h"
#include "Interfaces/RTSInteractable.h"
#include "Interfaces/RTSPawnInterfaces.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "RTSBaseCharacters.generated.h"

UCLASS(Blueprintable)
class ZOMBIESPROJECT_API ARTSBaseCharacters : public ACharacter, public IRTSInteractable, public IRTSPawnInterfaces
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARTSBaseCharacters();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Component")
	UDecalComponent* DecalSelectionComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Component")
	URTSHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Component")
	URTSFogRevealComponent* FogRevealComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Component")
	UAIPerceptionStimuliSourceComponent* PerceptionStimuliSourceComponent;
	
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

	virtual bool IsUserController_Implementation() override;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	bool bIsUserController;
protected:
	
	UFUNCTION()
	void OnHealthChanged(float Health, float HealthDelta, const class UDamageType* DamageType,
						 class AController* InstigatedBy, AActor* DamageCauser);
	
};
