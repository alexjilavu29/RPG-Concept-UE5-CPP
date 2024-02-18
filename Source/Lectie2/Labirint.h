// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Labirint.generated.h"

#define NL_MAX 20
#define NC_MAX 25

#define DIM(a,b) a*b

/**
 * 
 */
UCLASS()
class LECTIE2_API ULabirint : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static int32 harta[DIM(NL_MAX,NC_MAX)];
	static bool vizitat[DIM(NL_MAX, NC_MAX)];

	UFUNCTION(BlueprintCallable)
	static bool citesteHarta(FString caleFisier, FString& continut);

	UFUNCTION(BlueprintCallable)
	static bool citesteHartaMatrice(FString caleFisier, TArray<int32> &matrice, int32 &nrColoane);

	UFUNCTION(BlueprintCallable)
	static bool scrieInFisier(FString caleFisier, FString continut);
	
	UFUNCTION(BlueprintCallable)
	static bool citesteToateHartile(FString caleDirector, TArray <FString> & fisiere);

	UFUNCTION(BlueprintCallable)
	static bool genereazaHarta(int nrLinii, int nrColoane, TArray<int32>& matrice, int &outLinii, int &outColoane);

	UFUNCTION(BlueprintCallable)
	static bool stergePereti(int linie, int coloana, int nrLinii, int nrColoane);

	static int gasesteVecini(int linie, int coloana, int nrLinii, int nrColoane, int vecini[4]);
	//returnează nr de vecini nevizitati
	static void shuffle(int v[], int nr_elem);

	UFUNCTION(BlueprintCallable)
	static bool stergePerete(int linie, int coloana, int codPereteSters, int nrLinii, int nrColoane);
		
};
