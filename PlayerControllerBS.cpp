// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerControllerBS.h"
#include "Engine/World.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "NPCBS.h"

APlayerControllerBS::APlayerControllerBS()
{
	m_bIsTalk = false;
}

void APlayerControllerBS::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FVector start=	PlayerCameraManager->GetTransform().GetLocation();
	m_FHitresult.EndPoint = start + PlayerCameraManager->GetActorForwardVector()* 1000.0f;

	FCollisionQueryParams QP;
	QP.AddIgnoredActor(this);
	QP.bTraceComplex = true;
	QP.bReturnPhysicalMaterial = true;

	GetWorld()->LineTraceSingleByChannel(m_FHitresult.Hit, start, m_FHitresult.EndPoint,ECollisionChannel::ECC_Visibility, QP)
	 ? BeginMousePoint(m_FHitresult.Hit): EndPoint();
}

void APlayerControllerBS::BeginMousePoint(const FHitResult& hit)
{
	FVector::Distance(PlayerCameraManager->GetTransform().GetLocation(), hit.GetActor()->GetActorLocation()) <= 500 ?
		m_pNPC ? NULL : m_pNPC = Cast<ANPCBS>(hit.GetActor()),
		m_pNPC ? m_pNPC->MouseBegin(), m_bIsTalk = true : m_bIsTalk = false
		: EndPoint();
}
	
void APlayerControllerBS::EndPoint()
{
	m_pNPC ? m_pNPC->MouseEnd(), m_pNPC = NULL, m_bIsTalk = false : NULL;
}