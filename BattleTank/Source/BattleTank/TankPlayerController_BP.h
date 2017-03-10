// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameFramework/PlayerController.h"
#include "TankPlayerController_BP.generated.h"

class ATank;
class UTankAimingComponent;

/**
 * Helps player aim
 */
UCLASS()
class BATTLETANK_API ATankPlayerController_BP : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
		void FoundAimingComponent(UTankAimingComponent* AimingRef);


private:
	void AimTowardsCrosshair();
	//@return true if hit landscape 
	//@OUT FVector
	bool GetSightRayHitLocation(FVector&) const;
	UPROPERTY(EditAnywhere)
		float CrossHairXLocation = 0.5f;
	UPROPERTY(EditAnywhere)
		float CrossHairYLocation = 0.33333f;
	bool GetLookDirection(FVector2D, FVector&, FVector&) const;

	UPROPERTY(EditAnywhere)
		float LineTraceRange = 1000000.0f;	

	bool GetLookVectorHitLocation(FVector, FVector&) const;
};
