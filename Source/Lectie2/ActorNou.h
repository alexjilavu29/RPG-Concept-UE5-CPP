// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActorNou.generated.h"

UCLASS()
class LECTIE2_API AActorNou : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActorNou();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int a;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString sir;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText text;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int32> vector;

};
