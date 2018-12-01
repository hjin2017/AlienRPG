// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemBS.h"


// Sets default values
AItemBS::AItemBS()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AItemBS::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItemBS::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

