// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EfiringStatus : uint8
{
	Locked,
	Aiming,
	Reloading,
	Empty
};

//forward declaration 
class UTankBarrel; 
class UTurretCustomMesh;
class AProjectile;


//Hold barral's properties 
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	void AimAT(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = Setup)
		void FireTank();

	UFUNCTION(BlueprintCallable, Category = "Setup")
		void Initialise(UTankBarrel* Barrel, UTurretCustomMesh* Turret);

	EfiringStatus GetFiringState() const;

	int GetAmmo();

protected:
	UPROPERTY(BlueprintReadOnly, Category = "UI")
		EfiringStatus FiringStatus = EfiringStatus::Reloading;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
		int Ammo = 3;

private:
	UTankBarrel* Barrel = nullptr;

	UTurretCustomMesh* TurretCustomMesh = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		TSubclassOf<AProjectile> ProjectileToShoot;
	

	void MoveBarrelTowards(FVector AimDirection);

	//TODO remove after refarctor 
	UPROPERTY(EditAnywhere, Category = Firing)
		float LanuchSpeed = 1000000.f; //TODO find sensible default
	double LastFireTime = 0;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float ReloadTimeSeconds = 3;




	FVector TankAimDirection;
	bool IsBarrelMoving();
};
