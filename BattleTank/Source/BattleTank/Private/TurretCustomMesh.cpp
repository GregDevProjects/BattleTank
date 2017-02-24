// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TurretCustomMesh.h"




void UTurretCustomMesh::Rotate(float RotationDirection) {
	

	RotationDirection = FMath::Clamp<float>(RotationDirection, -1, 1);

	auto RotationChange = RotationDirection * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Yaw + RotationChange;
	//UE_LOG(LogTemp, Warning, TEXT("RotateCalled ElevationChange: %f RawNewElevation: %f"), RawNewElevation, RawNewElevation);
	//RawNewElevation = FMath::Clamp<float>(RawNewElevation, MinElevation, MaxElevation);
	SetRelativeRotation(FRotator(0, RawNewElevation, 0));

}