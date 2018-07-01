// Fill out your copyright notice in the Description page of Project Settings.

#include "TankyTurret.h"
#include "Engine/World.h"


void UTankyTurret::Rotate(float RelativeSpeed)
{
	float RotationChange = FMath::Clamp<float>(RelativeSpeed, -1, 1) * MaxDegreePerSecond * GetWorld()->DeltaTimeSeconds;
	float Rotation = RelativeRotation.Yaw + RotationChange; // see http://api.unrealengine.com/INT/API/Runtime/Core/Math/FRotator/index.html

	SetRelativeRotation(FRotator(0, Rotation, 0));

}




