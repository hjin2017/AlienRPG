// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerControllerBS.generated.h"

#define AISurface SurfaceType1
#define NPCSurface SurfaceType2
#define MonsterSurface SurfaceType3
#define PlyaerRay ECC_GameTraceChannel2
/**
 * 
 */
UCLASS()
class ALIENRPG_API APlayerControllerBS : public APlayerController
{
	GENERATED_BODY()
public:
	APlayerControllerBS();
protected:
	class ANPCBS* m_pNPC;
	bool m_bIsTalk;
public:
	struct FHitControllerresult
	{
		FHitResult Hit;
		FVector EndPoint;
	};
	FHitControllerresult m_FHitresult;

	virtual void Tick(float DeltaTime) override;
	
	void BeginMousePoint(const FHitResult& hit);
	void EndPoint();

	bool IsTalk() { return m_bIsTalk; }
};
