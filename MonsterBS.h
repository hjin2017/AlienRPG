// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MonsterBS.generated.h"

UCLASS()
class ALIENRPG_API AMonsterBS : public ACharacter
{
	GENERATED_BODY()
protected:
		UPROPERTY(Category = "Heaalth", BlueprintReadOnly)
		float m_fHp;
	UPROPERTY(Category = "Heaalth", EditAnywhere)
		float m_fMaxhp;
	UPROPERTY(Category = "Heaalth", BlueprintReadOnly)
		float m_fHpPercent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Monster)
		FString m_sMonsterName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Monster)
		int m_iExp;
public:
	// Sets default values for this character's properties
	AMonsterBS();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnDameged(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
};
