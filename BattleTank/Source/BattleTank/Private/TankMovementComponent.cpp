// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"


void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if (!LeftTrackToSet || !RightTrackToSet) { return; }

	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	//auto Time = GetWorld()->GetTimeSeconds();
	//auto Name = GetName();

	//UE_LOG(LogTemp, Warning, TEXT("Intend move forward throw: %f"), Throw);

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendMoveBackwards(float Throw)
{
	//auto Time = GetWorld()->GetTimeSeconds();
	//auto Name = GetName();

	//UE_LOG(LogTemp, Warning, TEXT("Intend move backwards throw: %f"), Throw);

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
	// TODO prevent double-speed due to duel control use
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
	// TODO prevent double-speed due to duel control use
}

void UTankMovementComponent::IntendTurnLeft(float Throw)
{
	LeftTrack->SetThrottle(-Throw);
	RightTrack->SetThrottle(Throw);
	// TODO prevent double-speed due to duel control use
}


