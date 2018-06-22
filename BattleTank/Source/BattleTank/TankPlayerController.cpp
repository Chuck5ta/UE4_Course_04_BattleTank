// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "BattleTank.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("PlayerController BeginPlay"));

	ATank* PossessedTank = GetControlledTank();
	if (GetControlledTank() == nullptr)
	{
		PossessedTank->GetName();
		UE_LOG(LogTemp, Warning, TEXT("Tank not possessed"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank possessed: %s"), *PossessedTank->GetName());
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();

	//UE_LOG(LogTemp, Warning, TEXT("TICK TOCK"));
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank())
	{
		return;
	}

	// get world location if linetrace through crosshair
	// If it hits the landscape 
	    // tell controlled tank to aim at this point 

}
