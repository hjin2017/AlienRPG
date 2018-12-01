// Fill out your copyright notice in the Description page of Project Settings.

#include "MonsterBS.h"


// Sets default values
AMonsterBS::AMonsterBS()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMonsterBS::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMonsterBS::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMonsterBS::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

