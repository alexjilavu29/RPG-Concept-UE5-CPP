// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BazaPerete.generated.h"

UCLASS()
class LECTIE2_API ABazaPerete : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABazaPerete();
	UPROPERTY(EditAnywhere);
	USceneComponent* Root;
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	UStaticMeshComponent* Mesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
