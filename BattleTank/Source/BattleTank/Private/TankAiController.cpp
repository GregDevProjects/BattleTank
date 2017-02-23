// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAiController.h"
#include "../Public/TankAiController.h"
#include "Tank.h"

void ATankAiController::BeginPlay() {
	Super::BeginPlay();
	
	auto TankController = GetControlledTank();
	auto PlayerInTank = GetPlayerTank();

	if (TankController && PlayerInTank) {
		UE_LOG(LogTemp, Warning, TEXT("AI Got %s"), *TankController->GetName());
		UE_LOG(LogTemp, Warning, TEXT("AI FOUND PLAYER %s"), *PlayerInTank->GetName());
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Couldn't get pawn"));
	}
}

ATank * ATankAiController::GetPlayerTank() const
{
	auto Player =  Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (Player) { return Player; }
	else return nullptr;
}

void ATankAiController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	auto PlayerTank = GetPlayerTank();
	if (PlayerTank) {
		//Move towards player
		//Aim towards player
		GetControlledTank()->AimAT(PlayerTank->GetActorLocation());
		//Fire if ready 
	}
}

ATank* ATankAiController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}


