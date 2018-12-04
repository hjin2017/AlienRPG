// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBS.h"
#include "iGun.generated.h"

/**
 * 
 */
UCLASS()
class ALIENRPG_API AiGun : public AItemBS
{
	GENERATED_BODY()
protected:

	UPROPERTY(VisibleAnywhere, Category = "Comp")
		class USkeletalMeshComponent* m_pSkeletal;

	UPROPERTY(EditDefaultsOnly, Category = "Weapons")
		TSubclassOf<UDamageType>  DamageType;

	UPROPERTY(Category = "Weapons", EditDefaultsOnly, BlueprintReadOnly)
		TSubclassOf<class UCameraShake>  CamShake;

	FTimerHandle TimeHandle;


	UPROPERTY(Category = "Weapons", EditDefaultsOnly, BlueprintReadOnly)
		float fRateFire;

	UPROPERTY(Category = "Weapons", EditAnywhere, BlueprintReadOnly)
		int iisAmmo;

	UPROPERTY(Category = "Weapons", EditAnywhere, BlueprintReadOnly)
		int iMaxAmmo;

	float fBetween;

	float BaseDamege;

	float fFirstScons;
public:
		AiGun();
protected:
	virtual void BeginPlay()override;
public:
	void Fire();

	virtual void RayFunction(const FHitResult & Hit, const FVector& ShootDir, AActor* MyOnwner)override;
};
