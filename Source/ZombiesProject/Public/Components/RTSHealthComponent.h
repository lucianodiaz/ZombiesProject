// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Controller.h"
#include "RTSHealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnHealthChangedSignature, float, Health,
											 float, HealthDelta, const class UDamageType*, DamageType,
											 class AController*, InstigatedBy, AActor*, DamageCauser);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ZOMBIESPROJECT_API URTSHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URTSHealthComponent();

	
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void HandleTakeAnyDamage(AActor* DamagedActor,float Damage, const UDamageType* DamageType,
							AController* InstigatedBy,AActor* DamageCauser);


public:
	UFUNCTION(BlueprintCallable,Category="HealthComponent")
	void Heal(const float HealAmount);
	
	float GetHealth() const;

	UPROPERTY(BlueprintAssignable,Category="Events")
	FOnHealthChangedSignature OnHealthChanged;

	
protected:
    UPROPERTY(BlueprintReadWrite,EditAnywhere, Category="HealthComponent")
	float DefaultHealth;
	
	UPROPERTY(BlueprintReadOnly,Category="HealthComponent")
    float Health;

	UPROPERTY(BlueprintReadOnly,Category="HealthComponent")
	bool bIsDead;
	
};