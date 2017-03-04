// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "Projectile.h"
#include "TankBarrel.h"
#include "TankMovementComponent.h"
#include "../Public/Tank.h"
#include "TankAimingComponent.h"




// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
	//TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("Movement Component"));

	
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
//void ATank::Tick( float DeltaTime )
//{
	//Super::Tick( DeltaTime );

//}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(class UInputComponent* InputComp)
{
	Super::SetupPlayerInputComponent(InputComp);

}

void ATank::AimAT(FVector HitLocation)
{
	TankAimingComponent->AimAT(HitLocation, LanuchSpeed);
}


void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	TankAimingComponent->SetBarrelReference(BarrelToSet);
	Barrel = BarrelToSet;
}



void ATank::SetTurretReference(UTurretCustomMesh* TurretToSet)
{
	TankAimingComponent->SetTurretReference(TurretToSet);
}

void ATank::FireTank()
{
	bool bIsReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeSeconds;
	//auto Projectile = nullptr;
	
	if ( !Barrel || !bIsReloaded)return;
	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBluePrint, Barrel->GetSocketLocation("Projectile"), Barrel->GetSocketRotation("Projectile"));
	Projectile->LaunchProjectile(LanuchSpeed);
	LastFireTime = FPlatformTime::Seconds();
}
