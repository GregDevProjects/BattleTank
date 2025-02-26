// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleTank.h"
#include "TankPlayerController_BP.h"
# include "TankAimingComponent.h"

// Tick 
	//Super
	//AimTowardsCrosshair();
void ATankPlayerController_BP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();

}

void ATankPlayerController_BP::BeginPlay() 
{
	Super::BeginPlay();
	auto AimingComp = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(AimingComp)) {
		FoundAimingComponent(AimingComp);

	} else {
		UE_LOG(LogTemp, Warning, TEXT("TankPlayerController_BP couldn't get aiming comp"));
	}


	auto TankController = GetPawn();
	if (TankController) {
		UE_LOG(LogTemp, Warning, TEXT("Player Got %s"), *TankController->GetName());
	} else {
		UE_LOG(LogTemp, Warning, TEXT("Couldn't get pawn"));
	}
}


void ATankPlayerController_BP::AimTowardsCrosshair()
{
	if (!GetPawn()) return;
	auto AimingComp = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComp)) return;

	FVector HitLocation; //Out param
	bool bGotHitLocation = GetSightRayHitLocation(HitLocation);
	//UE_LOG(LogTemp, Warning, TEXT("bGotHitLocation %i "), bGotHitLocation);
	//Get world location if linetrace through crosshair 
	if (GetSightRayHitLocation(HitLocation)) { //is going to ray trace 
		// If it hits the landscape tell controlled tank to aim at this point
		AimingComp->AimAT(HitLocation);
	}
}

//Get world location of linetrace through crosshair, true if hits landscape 
bool ATankPlayerController_BP::GetSightRayHitLocation(FVector& HitLocation) const
{
	//get location crosshair widget is looking at 
	int32 ViewPortSizeX, ViewportSizeY;
	GetViewportSize(ViewPortSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(
		CrossHairXLocation * ViewPortSizeX,
		CrossHairYLocation * ViewportSizeY
	);
	//De-project the screen position of the crosshair to a world direction 
	FVector CameraWorldLocation, CameraWorldDirection;
	if (GetLookDirection(ScreenLocation, CameraWorldDirection, CameraWorldLocation)) {
		
		return (GetLookVectorHitLocation(CameraWorldDirection, HitLocation));
	
	}
	
	//Line-trace along that look direction and see what we hit 

	return false;
}


bool ATankPlayerController_BP::GetLookDirection(FVector2D ScreenLocation, FVector& CameraWorldDirection, FVector& CameraWorldLocation) const
{
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldLocation,
		CameraWorldDirection
	);
}

bool ATankPlayerController_BP::GetLookVectorHitLocation(FVector CameraWorldDirection, FVector& HitLocation) const
{
	FHitResult TraceHit;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (CameraWorldDirection * LineTraceRange);
	//if line trace succeeds 
	if(GetWorld()->LineTraceSingleByChannel(
		TraceHit,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility))
	{
		HitLocation = TraceHit.Location;

		DrawDebugLine(GetWorld(),
			GetPawn()->GetActorLocation(),
			EndLocation,
			FColor(255, 0, 0));

		return true;
	}
	return false;

}
