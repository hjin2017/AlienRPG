// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerStateBS.h"
#include "iGun.h"
#include "Engine/World.h"
#include "ItemBS.h"
APlayerStateBS::APlayerStateBS()
{
	m_EQInven.SetNum((int)EQment::EQ_End);
	m_iExp = 0;
	m_iLv = 1;
	m_iLvUpExp = 1000;
	m_iWeaponIndex = 0;
}

void APlayerStateBS::BeginPlay()
{
	Super::BeginPlay();

	m_fHp = m_fMaxhp;
	m_fHpPercent = m_fHp / m_fMaxhp;
}

void APlayerStateBS::EQUP(EQment eEQment,AActor * pItem)
{
	switch (eEQment)
	{
	case EQment::EQ_GUN:
		if (m_EQInven[(int)eEQment] && m_EQInven[(int)eEQment]->GetName() != pItem->GetName())
		{
			m_EQInven[(int)eEQment]->Destroy();
			//가방이나 바닦으로
		}
		m_EQInven[(int)eEQment] = pItem;
		m_iWeaponIndex++;
		if (m_iWeaponIndex == 3)m_iWeaponIndex = 0;
	break;
	case EQment::EQ_End:
		break;
	}
}

void APlayerStateBS::Setuphp(const float & addHp)
{
	m_fHp += addHp;

	if (m_fHp > m_fMaxhp) m_fHp = m_fMaxhp;

	m_fHpPercent = m_fHp / m_fMaxhp;
}

void APlayerStateBS::SetDamege(const float & Dameg)
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

void APlayerStateBS::AddItem(const FName & ItemName)
{
	FString str;

	FItem_Info data = *m_pDataTable->FindRow<FItem_Info>(ItemName, str);

	for (int i = 0; i < m_Inven.Num(); i++)
	{
		if (m_Inven[i].ItemName != ItemName) continue;

		m_Inven[i].Count++;
		Picup();
		return;
	}

	m_Inven.Add(data);
	Picup();
}
/*
void APlayerStateBS::EmptyItem(const int& Index)
{
	FTransform Tr; 
	AItemBS* Item;
	Item = GetWorld()->SpawnActor<AItemBS>(ItemClass, Tr);
	Item->SetUp(m_Inven[Index].ItemName,1,GetOwner());
	
	m_Inven[Index].Count--;

	if (m_Inven[Index].Count == 0)
		m_Inven.Empty(Index);
}
*/