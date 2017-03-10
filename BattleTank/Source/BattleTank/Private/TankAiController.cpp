// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAiController.h"
#include "../Public/TankAiController.h"
#include "TankAimingComponent.h"

void ATankAiController::BeginPlay() {
	Super::BeginPlay();
}


void ATankAiController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	auto PlayerTank = (GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ThisTank = GetPawn();
	if (!ensure(PlayerTank && ThisTank)) {return;}
	//Move towards player
	MoveToActor(
		PlayerTank,
		AcceptanceRadius
	);
	//Aim towards player
	auto aimingComp = ThisTank->FindComponentByClass<UTankAimingComponent>();
	aimingComp->AimAT(PlayerTank->GetActorLocation());
		
	aimingComp->FireTank();
	
}



