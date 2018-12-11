// Fill out your copyright notice in the Description page of Project Settings.

#include "GameStateBS.h"
#include "NPCBS.h"



void AGameStateBS::AddQuest(const FQuestData &AddQuest,  AActor* pNpc)
{

	FQuestData Data = AddQuest;
	FString str;

	str = Data.sQuestMonster;

	mapQustList.Add(str) = Data;
	mapQustList[str].pOnwer = pNpc;

	ANPCBS * pointNpc = Cast<ANPCBS>(pNpc);
	if (pointNpc)
	{
		pointNpc->QuestPlaying(EQuest::QUEST_NNOMAL);
	}
}

void AGameStateBS::QuestMonsterDie(const FString & MonsterName)
{
	FQuestData* pQD = mapQustList.Find(MonsterName);

	if (pQD)
	{
		pQD->iCount++;

		MonseterDie(MonsterName, pQD->sQuestmanual, pQD->iCount, pQD->iQuestmanual);

		if (pQD->iCount == pQD->iQuestmanual)
		{
			mapQustList.Remove(MonsterName);

			ANPCBS * pNpc = Cast<ANPCBS>(pQD->pOnwer);
			if (pNpc)
			{
				pNpc->QuestPlaying(EQuest::QUEST_SUCCESS);
				pNpc->SetQuestReward(FString(), MonsterName, 0, pQD->iQuestExp);
			}
		}
	}
}