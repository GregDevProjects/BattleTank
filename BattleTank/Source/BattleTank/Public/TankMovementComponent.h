// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

/**
 * Responsible for driving the tank tracks 
 */


class UTankTrack;

UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	public:
		UFUNCTION(BlueprintCallable, Category = "Input")
			void IntendMoveForward(float Trow);

		UFUNCTION(BlueprintCallable, Category = "Input")
		void IntendTurnRight(float Trow);

		UFUNCTION(BlueprintCallable, Category = "Setup")
			void Initialise(UTankTrack* LeftTrack, UTankTrack* RightTrack);


	private:

		UTankTrack* LeftTrack = nullptr;
		UTankTrack* RightTrack = nullptr;
		//Called from pathfinding method from ai controllers 
		virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
};
