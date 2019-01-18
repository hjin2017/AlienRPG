// Fill out your copyright notice in the Description page of Project Settings.

#include "NPCBS.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerStateBS.h"
// Sets default values
ANPCBS::ANPCBS()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_pCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	m_pCapsule->SetCapsuleHalfHeight(88.0f);
	m_pCapsule->SetCapsuleRadius(34.0f);
	RootComponent = m_pCapsule;

	m_pMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	m_pMesh->SetWorldRotation(FRotator(0, -90.0f, 0));
	m_pMesh->SetWorldLocation(FVector(0, 0, -90.0f));
	m_pMesh->SetupAttachment(RootComponent);

	m_pOutline = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Outline"));
	m_pOutline->SetupAttachment(m_pMesh);
	m_pOutline->CastShadow = false;
	m_pOutline->SetVisibility(false);
	m_iStoryIndex = 0;
	m_iQuestIndex = 0;
	m_iQuestIndexPrive = 0;
}

// Called when the game starts or when spawned
void ANPCBS::BeginPlay()
{
	Super::BeginPlay();

	OnTakeAnyDamage.AddDynamic(this, &ANPCBS::OnDameged);

	m_ArrayStory.SetNum(1);
	int Maxsize = FCString::Atoi(*SetQuest(EQuest::QUEST_NNOMAL, NpcName)->sQuestion5);

	m_ArrayStory.SetNum(Maxsize+1,false);
	for (int i = 1; i < Maxsize+1; i++)
	{
		FString str = NpcName.ToString();
		str = str + FString::FromInt(i);
	
		if (!SetQuest(i, *str))break;
	}
	if (m_ArrayStory.Num() > EQuest::QUEST_Value)
	{
		m_iQuestIndex =  EQuest::QUEST_Value;
	}
	m_fHp = m_fMaxhp;
	m_fHpPercent = m_fHp / m_fMaxhp;
}

void ANPCBS::OnDameged(AActor * DamagedActor, float Damage, const UDamageType * DamageType, AController * InstigatedBy, AActor * DamageCauser)
{
	if (Damage <= 0.0f)return;

	m_fHp = FMath::Clamp(m_fHp - Damage, 0.0f, m_fMaxhp);
	m_fHpPercent = m_fHp / m_fMaxhp;
}

void ANPCBS::MouseBegin()
{
	m_pOutline->SetVisibility(true);
}

void ANPCBS::MouseEnd()
{
	m_pOutline->SetVisibility(false);
}
bool ANPCBS::Talk()
{
	if (m_ArrayStory.Num() < 0)return true;

	FString Story = m_ArrayStory[m_iQuestIndex][m_iStoryIndex];

	switch (m_iStoryIndex)
	{
	case Question1:case Question2:case Question3:case Question4:case Question5:
	OnQuestTalk(Story);
	m_iStoryIndex++;
	break;
	case QustName:
		OnQuestTalk(m_ArrayStory[m_iQuestIndex][EQuestion::Question5]);
		AddQuest(this, *Story);

		if(m_ArrayStory.Num() > m_iQuestIndex + 1)
			m_iQuestIndexPrive = m_iQuestIndex+1;
		else
		{
			m_iQuestIndexPrive = 0;
		}
	break;
	}

	if (Story.IsEmpty())
	{
		m_iStoryIndex = 0;

		if (m_iQuestIndex == EQuest::QUEST_SUCCESS)
		{
	
			APlayerStateBS* pPs = Cast<APlayerStateBS>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->PlayerState);
			if (pPs)
			{
				pPs->AddExp(m_fReward.Exp);
			}

			m_fReward.Exp = 0;
			m_fReward.ItemAmount = 0;
			m_fReward.ItemName = FString();
			m_iQuestIndex = m_iQuestIndexPrive;
			QuestSuccess(m_fReward.Monster);

		}
		return true;
	}
   
	return false;
}

const FQuestionData* ANPCBS::SetQuest(const int &index, const FName &sQustName)
{
	FString str;
	FQuestionData* data = m_pDataTable->FindRow<FQuestionData>(sQustName, str);

	if (data)
	{
		m_ArrayStory[index].SetNum(EQuestion::Question_NULL);
		m_ArrayStory[index][EQuestion::Question1] = data->sQuestion1;
		m_ArrayStory[index][EQuestion::Question2] = data->sQuestion2;
		m_ArrayStory[index][EQuestion::Question3] = data->sQuestion3;
		m_ArrayStory[index][EQuestion::Question4] = data->sQuestion4;
		m_ArrayStory[index][EQuestion::Question5] = data->sQuestion5;
		m_ArrayStory[index][EQuestion::QustMonster] = data->QustMonster;
		m_ArrayStory[index][EQuestion::QustName] = data->QustName;
	}
	return data;
}

void ANPCBS::StoryIndexReset()
{
	m_iStoryIndex = 0;
}

void ANPCBS::QuestPlaying(EQuest eQuest)
{
	m_iQuestIndex = eQuest;

	//switch (eQuest)
	//{
	//case QUEST_NNOMAL:
	//	 = eQuest;
	//break;
	//case QUEST_SUCCESS:
	//{
	//	m_iQuestIndex = m_iQuestIndexPrive;
	//	break;
	//}
	//}
}

void ANPCBS::SetQuestReward(FString ItemName, FString Monster, int ItemAmount, int Exp)
{
	m_fReward.ItemName = ItemName;
	m_fReward.Monster = Monster;
	m_fReward.ItemAmount = ItemAmount;
	m_fReward.Exp = Exp;
}

// Called every frame
void ANPCBS::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
