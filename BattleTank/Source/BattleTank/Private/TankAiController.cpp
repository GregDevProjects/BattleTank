// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAiController.h"
#include "../Public/TankAiController.h"
#include "Tank.h"

void ATankAiController::BeginPlay() {
	Super::BeginPlay();
}


void ATankAiController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ThisTank = Cast<ATank>(GetPawn());
	if (PlayerTank) {
		//Move towards player
		MoveToActor(
			PlayerTank,
			AcceptanceRadius
		);
		//Aim towards player
		ThisTank->AimAT(PlayerTank->GetActorLocation());
		

		//ThisTank->FireTank();
	}
}



