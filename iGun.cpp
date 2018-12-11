// Fill out your copyright notice in the Description page of Project Settings.

#include "iGun.h"
#include "Components/SkeletalMeshComponent.h"
#include "PlayerControllerBS.h"
#include "Kismet/GameplayStatics.h"
#include "CharacterBS.h"
#include "Animation/AnimInstance.h"
#include "TimerManager.h"
#include "DrawDebugHelpers.h"
#include "PhysicalMaterials/PhysicalMaterial.h"

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

void AiGun::BeginPlay()
{
	Super::BeginPlay();
	fBetween = 60 / fRateFire;
	iisAmmo = iMaxAmmo;
}

void AiGun::Fire()
{
	APlayerControllerBS* pC = Cast<APlayerControllerBS>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (pC)
	{
		EPhysicalSurface ESurface = UPhysicalMaterial::DetermineSurfaceType(pC->m_FHitresult.Hit.PhysMaterial.Get());

		switch (ESurface)
		{
		case SurfaceType_Default:
			DrawDebugLine(GetWorld(), m_pSkeletal->GetSocketLocation("MuzzleFlashSocket"), pC->m_FHitresult.EndPoint, FColor::Yellow, false, 1.0f, 0, 1.0f);
			break;
		case NPCSurface:
		{
			FireEnd();
		}
		break;
		case MonsterSurface:
		{
			FVector Dir, FirstLocation;
			FirstLocation = m_pSkeletal->GetSocketLocation("MuzzleFlashSocket");
			Dir = FirstLocation - pC->m_FHitresult.Hit.ImpactPoint;
			Dir.Normalize();

			UGameplayStatics::ApplyPointDamage(pC->m_FHitresult.Hit.GetActor(), 24.0f, Dir, pC->m_FHitresult.Hit, pC, this, DamageType);
			DrawDebugLine(GetWorld(), FirstLocation, pC->m_FHitresult.Hit.ImpactPoint, FColor::Yellow, false, 1.0f, 0, 1.0f);
		}
		break;
		}
		fFirstScons = GetWorld()->TimeSeconds;
	}
}

void AiGun::FireStart()
{
	ACharacterBS* pA = Cast<ACharacterBS>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (pA)
	{
		UAnimInstance* Anim = pA->GetMesh()->GetAnimInstance();
		Anim->Montage_Play(m_pMontage);
	}

	float FiresDelay = FMath::Max(fFirstScons + fBetween - GetWorld()->TimeSeconds, 0.0f);
	GetWorldTimerManager().SetTimer(TimeHandle, this, &AiGun::Fire, fBetween, true, FiresDelay);
}

void AiGun::FireEnd()
{
	ACharacterBS* pA = Cast<ACharacterBS>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (pA)
	{
		pA->GetMesh()->GetAnimInstance()->Montage_Stop(0);
	}
	GetWorldTimerManager().ClearTimer(TimeHandle);
}

