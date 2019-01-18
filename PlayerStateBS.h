// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Engine/DataTable.h"
#include "PlayerStateBS.generated.h"

UENUM(BlueprintType)
enum class EQment :uint8
{
	EQ_GUN,
	EQ_End
};

UENUM(BlueprintType)
enum class WeaponAmmo :uint8
{
	Ammo_GUN,
	Ammo_None
};

UENUM(BlueprintType)
enum class EItemType :uint8
{
	Item_Postion,
	Item_Eqment,
	Item_Quest
};

USTRUCT(BlueprintType)
struct FItem_Info : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ITEM")
	FName ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ITEM")
	EItemType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ITEM")
	WeaponAmmo AmmoType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ITEM")
	int Count;
};

UCLASS()
class ALIENRPG_API APlayerStateBS : public APlayerState
{
	GENERATED_BODY()


protected:
	UPROPERTY(Category = "Heaalth", BlueprintReadWrite)
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

	UPROPERTY(EditDefaultsOnly, Category = ITem, BlueprintReadOnly)
	UDataTable* m_pDataTable;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EQinve")
		TSubclassOf<class AItemBS> ItemClass;
	int m_iWeaponIndex;
public:
	APlayerStateBS();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category = "EQinve")
		TArray<AActor*> m_EQInven;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "inven")
		TArray<FItem_Info> m_Inven;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ITEM")
		FName ItemName;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent, Category = "ITEM")
		void Picup();
public:
	UFUNCTION(BlueprintCallable, Category = "EQinve")
	void EQUP(EQment eEQment, AActor* pItem);

	UFUNCTION(BlueprintCallable, Category = "Heaalth")
	void Setuphp(const float & addHp);

	UFUNCTION(BlueprintCallable, Category = "Heaalth")
	void SetDamege(const float &Dameg);

	void AddExp(const int &Exp);

	void AddItem(const FName &ItemName);
//	void EmptyItem(const int& Index);
};
