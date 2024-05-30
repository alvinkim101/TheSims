// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagsManager.h"
#include "Motives.generated.h"

#define STRINGIZE(s) #s

#define MOTIVES \
	X(Hunger) \
	X(Social) \
	X(Fun) \
	X(Energy)

UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THESIMS_API UMotives : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMotives();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UFUNCTION(BlueprintCallable)
	FGameplayTag ChooseMotive() const;

	UFUNCTION(BlueprintCallable)
	void SetRegenState(FGameplayTag Motive, bool RegenState);

	UFUNCTION(BlueprintCallable)
	bool IsFull(FGameplayTag Motive) const;

	UFUNCTION(BlueprintCallable)
	float GetMotivePercent(FGameplayTag Motive) const;

private:
	#define X(motive) FGameplayTag motive = UGameplayTagsManager::Get().RequestGameplayTag(TEXT(STRINGIZE(Motive.motive)));
	MOTIVES
	#undef X

	// Rate at which motive regens / decays
	UPROPERTY(EditDefaultsOnly)
	float Rate = 1.f;

	// Max value of motive
	UPROPERTY(EditDefaultsOnly)
	float Max = 100.f;

	// Key: motive name, Value: motive value and whether it is regenerating or not
	TMap<FGameplayTag, std::pair<float, bool>> Motives {
		#define X(motive) { motive, { Max, false } },
		MOTIVES
		#undef X
	};
};
