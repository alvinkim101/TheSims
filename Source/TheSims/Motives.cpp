// Fill out your copyright notice in the Description page of Project Settings.


#include "Motives.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UMotives::UMotives()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


}


// Called when the game starts
void UMotives::BeginPlay()
{
	Super::BeginPlay();


}


// Called every frame
void UMotives::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	for (auto& Motive : Motives)
	{
		if (Motive.Value.second == true)
		{
			Motive.Value.first = UKismetMathLibrary::FMin(Motive.Value.first + Rate * DeltaTime, Max);
		}
		else
		{
			Motive.Value.first = UKismetMathLibrary::FMax(Motive.Value.first - Rate * DeltaTime, 0.f);
		}
	}
}

FGameplayTag UMotives::ChooseMotive() const
{
	if (Motives[Energy].first < 0)
	{
		return Energy;
	}
	else
	{
		return Fun;
	}
}

void UMotives::SetRegenState(FGameplayTag Motive, bool RegenState)
{
	Motives[Motive].second = RegenState;
}

bool UMotives::IsFull(FGameplayTag Motive) const
{
	return Motives[Motive].first >= 99.f;
}

float UMotives::GetMotivePercent(FGameplayTag Motive) const
{
	return Motives[Motive].first / Max;
}
