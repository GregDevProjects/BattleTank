// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TurretCustomMesh.h"
#include "TankAimingComponent.h"
#include "Projectile.h"
#include "../Public/TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	LastFireTime = FPlatformTime::Seconds();
	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	//UE_LOG(LogTemp, Warning, TEXT("tick"));


	if ((Ammo <= 0)) {
		FiringStatus = EfiringStatus::Empty;

	}
	else if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeSeconds){
		FiringStatus = EfiringStatus::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringStatus = EfiringStatus::Aiming;
	}
	else 
	{
		FiringStatus = EfiringStatus::Locked;
	}
	
	// ...
}

void UTankAimingComponent::AimAT(FVector HitLocation)
{
	
	if (!ensure(Barrel)) { return; }

	float Time = GetWorld()->GetTimeSeconds();
	FVector OutLaunchVelocity;
	//if aim solution is found
	if (UGameplayStatics::SuggestProjectileVelocity
		(	
			this,
			OutLaunchVelocity,
			Barrel->GetSocketLocation(FName("Projectile")),
			HitLocation,
			LanuchSpeed,
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

void UTankAimingComponent::Initialise(UTankBarrel * BarrelToSet, UTurretCustomMesh * TurretToSet)
{
	if (!ensure(BarrelToSet && TurretToSet )) {UE_LOG(LogTemp, Warning, TEXT("Tank Aiming Comp missing params")); return; }
	Barrel = BarrelToSet;
	TurretCustomMesh = TurretToSet;
	//ProjectileToShoot = ProjectileToSet;
	UE_LOG(LogTemp, Warning, TEXT("INIT FINISHED"));
}

EfiringStatus UTankAimingComponent::GetFiringState() const
{
	return FiringStatus;
}

int UTankAimingComponent::GetAmmo()
{
	return Ammo;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	TankAimDirection = AimDirection;
	if (!ensure(Barrel && TurretCustomMesh)) { return; }
	//work out difference between current barrel rotation and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	//move barrel right amount each frame 
	//Given max elevation speed and the frame time
	Barrel->Elevate(DeltaRotator.Pitch);
	//always yaw the shortest way
	if (DeltaRotator.Yaw > 180) {
		TurretCustomMesh->Rotate(-DeltaRotator.Yaw);
	}else{
		TurretCustomMesh->Rotate(DeltaRotator.Yaw);
	}
	
	

}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }
	FVector BarrelRotator = Barrel->GetForwardVector();
	if ( BarrelRotator.Equals(TankAimDirection,0.1f))
		return false;
	else
		return true;
}

void UTankAimingComponent::FireTank()
{
	if (!ensure(Barrel && ProjectileToShoot)) return;
	
	//if (Ammo == 0) {
	//	UE_LOG(LogTemp, Warning, TEXT("NO AMMO"));
	//	return;
	//}
	

	UE_LOG(LogTemp, Warning, TEXT("Ammo %d"), Ammo);
	//auto Projectile = nullptr;

	if (FiringStatus == EfiringStatus::Reloading || FiringStatus == EfiringStatus::Empty) return;

	Ammo--;

	//auto ProjectileBluePrint = GetOwner()->FindComponentByClass<AProjectile>();
	auto Projectile = GetWorld()->SpawnActor<AProjectile>(
		ProjectileToShoot,
		Barrel->GetSocketLocation("Projectile"), 
		Barrel->GetSocketRotation("Projectile")
	);
//	TODO use launchspeed variable for this
	Projectile->LaunchProjectile(10000.f);
	LastFireTime = FPlatformTime::Seconds();
}