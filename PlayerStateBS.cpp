// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerStateBS.h"
#include "ItemBS.h"

APlayerStateBS::APlayerStateBS()
{
	m_EQInven.SetNum(EQment::EQ_End);
}
void APlayerStateBS::EQUP(EQment eEQment,AItemBS * pItem)
{
	m_EQInven[eEQment] = pItem;
}

void APlayerStateBS::EQDown(EQment eEQment)
{
	m_EQInven[eEQment]->Destroy();
	m_EQInven[eEQment] = NULL;
}
