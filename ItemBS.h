// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "ItemBS.generated.h"


USTRUCT(BlueprintType)
struct FItemCreate_Info : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ITEM")
	class UStaticMesh* pMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ITEM")
	FName ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ITEM")
	int Count;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ITEM")
	float Radius;
};

UCLASS()
class ALIENRPG_API AItemBS : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Comp")
	class UStaticMeshComponent* m_pMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Comp")
	class USphereComponent* m_pSphere;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Comp")
	class UStaticMeshComponent* m_pOutline;

	UPROPERTY(EditDefaultsOnly, Category = ITem, BlueprintReadOnly)
		UDataTable* m_pDataTable;
	UPROPERTY()
	class UMaterialInterface* Meterial;

	FName m_Name;
protected:
	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
		void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor ,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
public:	
	// Sets default values for this actor's properties
	AItemBS();

	UFUNCTION(BlueprintCallable, Category = "ITEM")
	void SetUp(const FName &Name,const int & Count,const AActor* pPlayer);
	void Picup(AActor* pPlayer);
};
