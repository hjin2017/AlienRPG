// Fill out your copyright notice in the Description page of Project Settings.

#include "iGun.h"
#include "Components/SkeletalMeshComponent.h"

AiGun::AiGun()
{
	m_pSkeletal = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("mesh"));
	m_pSkeletal->SetupAttachment(RootComponent);

	BaseDamege = 20.0f;
	fRateFire = 600.0f;
	iMaxAmmo = 100;
	NetUpdateFrequency = 66.0f;
	MinNetUpdateFrequency = 33.0f;
}

void AiGun::Fire()
{
	if (m_EQ)
	{

	}
}

void AiGun::BeginPlay()
{
	Super::BeginPlay();
	fBetween = 60 / fRateFire;
	iisAmmo = iMaxAmmo;
}

void AiGun::RayFunction(const FHitResult & Hit, const FVector & ShootDir, AActor * MyOnwner)
{

}
