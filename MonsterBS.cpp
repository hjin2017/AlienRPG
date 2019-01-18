// Fill out your copyright notice in the Description page of Project Settings.

#include "MonsterBS.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "GameStateBS.h"
#include "PlayerStateBS.h"
#include "Components/SphereComponent.h"

// Sets default values
AMonsterBS::AMonsterBS()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("monsSphere"));
	Sphere->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMonsterBS::BeginPlay()
{
	Super::BeginPlay();

	OnTakeAnyDamage.AddDynamic(this, &AMonsterBS::OnDameged);

	//m_pWifget->bHiddenInGame = true;
	m_fHp = m_fMaxhp;
	m_fHpPercent = m_fHp / m_fMaxhp;
}

// Called every frame
void AMonsterBS::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMonsterBS::OnDameged(AActor * DamagedActor, float Damage, const UDamageType * DamageType, AController * InstigatedBy, AActor * DamageCauser)
{
	if (Damage <= 0.0f)return;

	//if (m_fHpPercent != 1)
	//	m_pWifget->bHiddenInGame = false;

	m_fHp = FMath::Clamp(m_fHp - Damage, 0.0f, m_fMaxhp);
	m_fHpPercent = m_fHp / m_fMaxhp;

	if (m_fHpPercent == 0)
	{
		APlayerStateBS* pPs = Cast<APlayerStateBS>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->PlayerState);
		if (pPs)
		{
			pPs->AddExp(m_iExp);
		}

		AGameStateBS* pGs = Cast<AGameStateBS>(GetWorld()->GetGameState());
		if (pGs)
		{
			pGs->QuestMonsterDie(m_sMonsterName);
		}

		DroItem();
		Destroy();
	}
}
