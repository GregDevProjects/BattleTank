// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "AIController.h"
#include "TankAiController.generated.h"

class UTankAimingComponent;

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API ATankAiController : public AAIController
{
	GENERATED_BODY()
public:
	void BeginPlay() override;
private:
	virtual void Tick(float DeltaSeconds) override;
	UPROPERTY(EditAnywhere, Category = "Movement")
		float AcceptanceRadius = 4000.f;
};
