// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TurretCustomMesh.h"
#include "TankAimingComponent.h"
#include "../Public/TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTurretCustomMesh *TurretToSet)
{
	TurretCustomMesh = TurretToSet;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

void UTankAimingComponent::AimAT(FVector HitLocation, float LaunchSpeed)
{

	if (!Barrel) { return; }

	float Time = GetWorld()->GetTimeSeconds();
	FVector OutLaunchVelocity;
	//if aim solution is found
	if (UGameplayStatics::SuggestProjectileVelocity
		(	
			this,
			OutLaunchVelocity,
			Barrel->GetSocketLocation(FName("Projectile")),
			HitLocation,
			LaunchSpeed,
			false,
			0,
			0,
			ESuggestProjVelocityTraceOption::DoNotTrace
		)
	) 
	{
		//rotate barrel towards hit location 
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
		
	//	UE_LOG(LogTemp, Warning, TEXT("Speed %s"), *AimDirection.ToString());
		//UE_LOG(LogTemp, Warning, TEXT("aim loc %s"), *HitLocation.ToString());
		//UE_LOG(LogTemp, Warning, TEXT("elevate called %f"), Time);
	} else {
		
		//UE_LOG(LogTemp, Warning, TEXT("elevate called"));
		//UE_LOG(LogTemp, Warning, TEXT("elevate NOT called %f"), Time);
	}
	
	


}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	
	//work out difference between current barrel rotation and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	//move barrel right amount each frame 
	//Given max elevation speed and the frame time
	Barrel->Elevate(DeltaRotator.Pitch);
	TurretCustomMesh->Rotate(DeltaRotator.Yaw);
	

}

