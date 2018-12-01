// Fill out your copyright notice in the Description page of Project Settings.

#include "NPCBS.h"


// Sets default values
ANPCBS::ANPCBS()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANPCBS::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANPCBS::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANPCBS::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

