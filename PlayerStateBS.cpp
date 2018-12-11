// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerStateBS.h"
#include "iGun.h"
#include "Engine/World.h"
APlayerStateBS::APlayerStateBS()
{
	m_EQInven.SetNum((int)EQment::EQ_End);
	m_iExp = 0;
	m_iLv = 1;
	m_iLvUpExp = 1000;
}

void APlayerStateBS::EQUP(EQment eEQment,AItemBS * pItem)
{
	switch (eEQment)
	{
	case EQment::EQ_GUN:
		m_EQInven[(int)eEQment] = pItem;
		//FActorSpawnParameters ActorSpawnParams;
		//ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		//m_EQInven[eEQment] = GetWorld()->SpawnActor<AiGun>(WeaponsClass[Type], FVector(0, 0, 0), FRotator(0, 0, 0), ActorSpawnParams);
	break;
	case EQment::EQ_End:
		break;
	default:
		break;
	}
}

void APlayerStateBS::EQDown(EQment eEQment)
{
	m_EQInven[(int)eEQment]->Destroy();
	m_EQInven[(int)eEQment] = NULL;
}

void APlayerStateBS::Setuphp()
{
	m_fHp = m_fMaxhp;
	m_fHpPercent = m_fHp / m_fMaxhp;
}

void APlayerStateBS::SetDamege(float & Dameg)
{
	if (Dameg <= 0.0f)return;

	m_fHp = FMath::Clamp(m_fHp - Dameg, 0.0f, m_fMaxhp);
	m_fHpPercent = m_fHp / m_fMaxhp;
}

void APlayerStateBS::AddExp(const int &Exp)
{
	m_iExp += Exp;
	if (m_iExp >= m_iLvUpExp)
	{
		int Temp =  m_iExp- m_iLvUpExp;

		m_iLv++;
		m_iLvUpExp = m_iLvUpExp * 2;
		m_iExp = Temp;
	}
}