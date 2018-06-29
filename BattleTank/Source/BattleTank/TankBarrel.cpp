// Fill out your copyright notice in the Description page of Project Settings.

//#include "BattleTank.h"
#include "TankBarrel.h"
#include "Engine/World.h"


void UTankBarrel::Elevate(float RelativeSpeed)
{
	// Move the barrel the right amount this frame
	// Given a max elevation speed, and the frame time
//	auto Time = GetWorld()->GetTimeSeconds();
//	UE_LOG(LogTemp, Warning, TEXT("%f: Barrel-Elevate called at speed %f"), Time, RelativeSpeed);
	float ElevationChange = FMath::Clamp<float>(RelativeSpeed, -1, 1) * MaxDegreePerSecond * GetWorld()->DeltaTimeSeconds;
	float RawNewElevation = RelativeRotation.Pitch + ElevationChange;

	SetRelativeRotation(FRotator(FMath::Clamp(RawNewElevation, MinElevationDegrees, MaxElevationDegrees), 0, 0));
}


