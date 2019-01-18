// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemBS.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "CharacterBS.h"
#include "PlayerStateBS.h"

// Sets default values
AItemBS::AItemBS()
{
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UMaterialInterface> OutlinMaterial;
		FConstructorStatics()
			: OutlinMaterial(TEXT("/Game/Materials/line.line")) {}
	};
	static FConstructorStatics ConstructorStatics;

	m_pSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	m_pMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	m_pOutline = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OutlineComp"));

	Meterial = ConstructorStatics.OutlinMaterial.Get();

	RootComponent = m_pSphere;
	m_pMesh->SetupAttachment(RootComponent);
	m_pOutline->SetupAttachment(RootComponent);
}

void AItemBS::SetUp(const FName &Name , const int & Count, const AActor* pPlayer)
{
	m_Name = Name;
	FString str;
	FItemCreate_Info data = *m_pDataTable->FindRow<FItemCreate_Info>(m_Name, str);
	data.Count = Count;

	m_pMesh->SetStaticMesh(data.pMesh);

	m_pOutline->SetStaticMesh(data.pMesh);
	m_pOutline->SetMaterial(0, Meterial);

	FVector::Dist(GetActorLocation(), pPlayer->GetActorLocation()) < 400? m_pOutline->SetVisibility(true): m_pOutline->SetVisibility(false);

	m_pSphere->SetSphereRadius(data.Radius);
	m_pSphere->OnComponentBeginOverlap.AddDynamic(this, &AItemBS::OnBeginOverlap);
	m_pSphere->OnComponentEndOverlap.AddDynamic(this, &AItemBS::OnEndOverlap);
}

void AItemBS::Picup(AActor* pPlayer)
{
	ACharacterBS* Player = Cast<ACharacterBS>(pPlayer);
	if (Player)
	{
		APlayerStateBS* pst = Cast<APlayerStateBS>(Player->PlayerState);
		if (pst)
		{
			pst->AddItem(m_Name);
		}
		Destroy();
	}
	
}

void AItemBS::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	m_pOutline->SetVisibility(true);
}

void AItemBS::OnEndOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	m_pOutline->SetVisibility(false);
}
