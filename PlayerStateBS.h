// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PlayerStateBS.generated.h"

UENUM(BlueprintType)
enum class EQment :uint8
{
	EQ_GUN,
	EQ_End
};

UCLASS()
class ALIENRPG_API APlayerStateBS : public APlayerState
{
	GENERATED_BODY()


protected:
	UPROPERTY(Category = "Heaalth", BlueprintReadOnly)
		float m_fHp;
	UPROPERTY(Category = "Heaalth", EditAnywhere)
		float m_fMaxhp;
	UPROPERTY(Category = "Heaalth", BlueprintReadOnly)
		float m_fHpPercent;
	UPROPERTY(Category = "Heaalth", BlueprintReadOnly)
		int m_iExp;
	UPROPERTY(Category = "Heaalth", BlueprintReadOnly)
		int m_iLvUpExp;
	UPROPERTY(Category = "Heaalth", BlueprintReadOnly)
		int m_iLv;
public:
	APlayerStateBS();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category = "EQinve")
		TArray<class AItemBS*> m_EQInven;
public:
	UFUNCTION(BlueprintCallable, Category = "EQinve")
	void EQUP(EQment eEQment, AItemBS* pItem);

	void EQDown(EQment eEQment);

	void Setuphp();
	void SetDamege(float &Dameg);
	void AddExp(const int &Exp);
};
