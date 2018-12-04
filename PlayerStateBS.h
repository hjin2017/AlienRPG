// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PlayerStateBS.generated.h"

/**
 * 
 */
UCLASS()
class ALIENRPG_API APlayerStateBS : public APlayerState
{
	GENERATED_BODY()

	enum  EQment:uint8
	{
		EQ_GUN,
		EQ_End
	};

	TArray<class AItemBS*> m_EQInven;
public:
	APlayerStateBS();
public:

	void EQUP(EQment eEQment,AItemBS* pItem);
	void EQDown(EQment eEQment);
	
};
