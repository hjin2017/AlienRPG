// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Engine/DataTable.h"
#include "GameStateBS.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FQuestData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Quest)
	FString sQuestName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Quest)
		FString sQuestmanual;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Quest)
		FString sQuestMonster;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Quest)
		int iCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Quest)
		int iQuestmanual;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Quest)
		UTexture2D* pQuestItem;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Quest)
		int iQuestItem;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Quest)
		int iQuestExp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Quest)
		AActor* pOnwer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Quest)
		TSubclassOf<class AMonsterBS> Monsterclass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Quest)
		FName ItemName;
};

UCLASS()
class ALIENRPG_API AGameStateBS : public AGameStateBase
{
	GENERATED_BODY()
protected:	
	UPROPERTY(EditDefaultsOnly, Category = "Quest", BlueprintReadOnly)
		UDataTable* m_pDataTable;
	UPROPERTY(BlueprintReadOnly, Category = "Quest")
		TMap<FString, FQuestData> mapQustList;
public:
		UFUNCTION(BlueprintCallable, Category = "QuestEnvent")
		void AddQuest(const FQuestData &AddQuest,  AActor* pNpc);

		UFUNCTION(BlueprintImplementableEvent, Category = "QuestEnvent")
		void MonseterDie(const FQuestData& pData);

		void QuestMonsterDie(const FString & MonsterName);
};
