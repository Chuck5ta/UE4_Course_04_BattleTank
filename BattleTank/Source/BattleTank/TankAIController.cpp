// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "BattleTank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("AI BeginPlay"));

	ATank* PossessedTank = GetControlledTank();
	if (GetControlledTank() == nullptr)
	{
		PossessedTank->GetName();
		UE_LOG(LogTemp, Warning, TEXT("AI Tank not possessed"));
	}
	else
	{

		UE_LOG(LogTemp, Warning, TEXT("AI Tank possessed: %s"), *PossessedTank->GetName());
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}




