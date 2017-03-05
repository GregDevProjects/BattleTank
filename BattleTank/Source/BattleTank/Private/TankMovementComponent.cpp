// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankMovementComponent.h"
#include "TankTrack.h"
#include "../Public/TankMovementComponent.h"



void UTankMovementComponent::IntendMoveForward(float Throw) {
	if (!LeftTrack || !RightTrack) return;
	LeftTrack->SetTrottle(Throw);
	RightTrack->SetTrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw) {
	if (!LeftTrack || !RightTrack) return;
	//UE_LOG(LogTemp, Error, TEXT("Passed To Turn Right: %f"), Throw);
	LeftTrack->SetTrottle(Throw);
	RightTrack->SetTrottle(-Throw);
}

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet) {
	if (!LeftTrackToSet || !RightTrackToSet) { UE_LOG(LogTemp, Error, TEXT("NO TRACK")); return; }
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
	if (!RightTrack) { UE_LOG(LogTemp, Error, TEXT("SUCCESS INITIALIZWE")); }
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	//don't call super because we are replacing functionality 
	auto TankName = GetOwner()->GetName();
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	float DifferenceBetweenThisTankAndPlayerForard = FVector::DotProduct(TankForward, AIForwardIntention);
	IntendMoveForward(DifferenceBetweenThisTankAndPlayerForard);
	float DifferenceBetweenThisTankAndPlayerRotation = FVector::CrossProduct( TankForward, AIForwardIntention).Z;
	IntendTurnRight(DifferenceBetweenThisTankAndPlayerRotation);
	//UE_LOG(LogTemp, Error, TEXT("MoveVelocity: %s, ForwardVector: %s"), *TankForward.ToString(), *GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation().ToString() );
}
