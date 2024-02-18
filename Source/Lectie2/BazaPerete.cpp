// Fill out your copyright notice in the Description page of Project Settings.


#include "BazaPerete.h"

// Sets default values
ABazaPerete::ABazaPerete()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Root = CreateDefaultSubobject <USceneComponent>(TEXT("ROOT"));
	RootComponent = Root;
	
	Mesh = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("MESH"));
	Mesh->AttachToComponent(Root,FAttachmentTransformRules::KeepWorldTransform);


}

// Called when the game starts or when spawned
void ABazaPerete::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABazaPerete::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

