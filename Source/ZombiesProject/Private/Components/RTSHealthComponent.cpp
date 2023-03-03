// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/RTSHealthComponent.h"

// Sets default values for this component's properties
URTSHealthComponent::URTSHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	DefaultHealth = 100;
	bIsDead = false;
	// ...
}


// Called when the game starts
void URTSHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	AActor* MyOwner = GetOwner();

	if(MyOwner)
	{
		MyOwner->OnTakeAnyDamage.AddDynamic(this,&URTSHealthComponent::HandleTakeAnyDamage);
	}

	Health = DefaultHealth;
}

void URTSHealthComponent::Heal(const float HealAmount)
{
	if(HealAmount <= 0.0f || Health <= 0.0f)
	{
		return;
	}
	Health = FMath::Clamp(Health+HealAmount,0.0f,DefaultHealth);
	OnHealthChanged.Broadcast(Health,-HealAmount,nullptr,nullptr,nullptr);
}

float URTSHealthComponent::GetHealth() const
{
	return Health;
}

void URTSHealthComponent::HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
                                              AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.0f || bIsDead)
	{
		return;
	}

	Health = FMath::Clamp(Health - Damage,0.0f,DefaultHealth);

	UE_LOG(LogTemp,Log,TEXT("Health changed: %s"), *FString::SanitizeFloat(Health));

	bIsDead = Health <= 0.0f;

	OnHealthChanged.Broadcast(Health,Damage,DamageType,InstigatedBy,DamageCauser);
	//
	// ASGameMode* GM = Cast<ASGameMode>(GetWorld()->GetAuthGameMode());

	// if(bIsDead)
	// {
	// 	if(GM)
	// 	{
	// 		GM->OnActorKilled.Broadcast(GetOwner(),DamageCauser,InstigatedBy);
	// 	}
	// }
}



