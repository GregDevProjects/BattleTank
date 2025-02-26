// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS( meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// -1 is max downward speed, and +1 is max up movement 
	void Elevate(float);

private:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MaxDegreesPerSecond = 20.f; 

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MaxElevation = 70.f;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MinElevation = 0.f;
	
};
