// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Engine/DataTable.h"

#include "NPCBS.generated.h"



USTRUCT(BlueprintType)
struct FQuestionData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()


		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Question)
		FString sQuestion1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Question)
		FString sQuestion2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Question)
		FString sQuestion3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Question)
		FString sQuestion4;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Question)
		FString sQuestion5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Question)
		FString QustName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Question)
		FString QustMonster;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Question)
		bool QustSuess;
};

enum EQuestion :uint8
{
	Question1,
	Question2,
	Question3,
	Question4,
	Question5,
	QustName,
	QustMonster,
	QustSuess,
	Question_NULL,
};

enum EQuest :uint8
{
	QUEST_NNOMAL ,
	QUEST_SUCCESS ,
	QUEST_Value
};

struct FReward
{
	FString ItemName;
	FString Monster;
	int ItemAmount;
	int Exp;
};

UCLASS()
class ALIENRPG_API ANPCBS : public APawn
{
	GENERATED_BODY()

protected:
	UPROPERTY(Category = NPC, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USkeletalMeshComponent* m_pMesh;
	UPROPERTY(Category = NPC, VisibleAnywhere, BlueprintReadOnly)
		class USkeletalMeshComponent* m_pOutline;
	UPROPERTY(Category = NPC, VisibleAnywhere, BlueprintReadOnly)
	class UCapsuleComponent*m_pCapsule;
	UPROPERTY(EditDefaultsOnly, Category = NPC, BlueprintReadOnly)
		UDataTable* m_pDataTable;
	UPROPERTY(EditDefaultsOnly, Category = NPC, BlueprintReadOnly)
		FName NpcName;
	UPROPERTY(Category = NPC, BlueprintReadOnly)
		float m_fHp;
	UPROPERTY(Category = NPC, EditAnywhere)
		float m_fMaxhp;
	UPROPERTY(Category = NPC, BlueprintReadOnly)
		float m_fHpPercent;

	TArray<TArray<FString>> m_ArrayStory;
	int m_iStoryIndex;
	int m_iQuestIndex;
	int m_iQuestIndexPrive;
	FReward m_fReward;
public:
	// Sets default values for this pawn's properties
	ANPCBS();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
		void OnDameged(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
	
	UFUNCTION(BlueprintImplementableEvent, Category = "NPCEnvent")
		void OnQuestTalk(const FString& Stroy);

	UFUNCTION(BlueprintImplementableEvent, Category = "NPCEnvent")
		void AddQuest(const ANPCBS* pNpc , const FName& QuestName);

		const FQuestionData* SetQuest(const int &index, const FName &sQustName);

		UFUNCTION(BlueprintImplementableEvent, Category = "NPCEnvent")
			void QuestSuccess(const FString& Monster);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual	void MouseBegin();
	virtual void MouseEnd();
	bool Talk();
	void StoryIndexReset();
	void QuestPlaying(EQuest eQuest);
	void SetQuestReward(FString ItemName, FString Monster,int ItemAmount ,int Exp=0);
};
