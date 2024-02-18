// Fill out your copyright notice in the Description page of Project Settings.


#include "Labirint.h"

int32 ULabirint::harta[DIM(NL_MAX, NC_MAX)];
bool ULabirint::vizitat[DIM(NL_MAX, NC_MAX)];

bool ULabirint::citesteHarta(FString caleFisier, FString& continut) {
	// caleFisier = cale relativa

	FString caleCompleta = FPaths::Combine(FPaths::ProjectContentDir(), caleFisier);

	IFileManager& fm = IFileManager::Get(); //singleton, obiect cu o singura instanta

	if (!fm.FileExists(*caleCompleta)){
		UE_LOG(LogTemp, Warning, TEXT("Fisierul de la calea %s nu exista"), *caleCompleta);
		return false;
	}

	FFileHelper::LoadFileToString(continut, *caleCompleta);

	UE_LOG(LogTemp, Warning, TEXT("Continut: %s"), *continut);

	return true;
}

bool ULabirint::citesteHartaMatrice(FString caleFisier, TArray<int32>& matrice, int32& nrColoane) {
	FString continut;

	FString caleCompleta = FPaths::Combine(FPaths::ProjectContentDir(), caleFisier);

	IFileManager& fm = IFileManager::Get(); //singleton, obiect cu o singura instanta

	if (!fm.FileExists(*caleCompleta)) {
		UE_LOG(LogTemp, Warning, TEXT("Fisierul de la calea %s nu exista"), *caleCompleta);
		return false;
	}

	FFileHelper::LoadFileToString(continut, *caleCompleta);

	UE_LOG(LogTemp, Warning, TEXT("Continut: %s"), *continut);

	TArray<FString> linii;
	continut.ParseIntoArrayLines(linii);

	for (int i = 1; i < linii.Num(); i++) {
		TArray<FString> elementeLinie;
		linii[i].ParseIntoArray(elementeLinie, TEXT(" "));
		nrColoane = elementeLinie.Num();
		for (int j = 0; j < elementeLinie.Num(); j++)
		{
			matrice.Add(FCString::Atoi(*elementeLinie[j]));

			UE_LOG(LogTemp, Warning, TEXT("Continut %d %d %d "), i-1, j, matrice[(i-1) * nrColoane + j]);
		}

		
	}


	return true;

}



bool ULabirint::scrieInFisier(FString caleFisier, FString continut){
	FString caleCompleta = FPaths::Combine(FPaths::ProjectContentDir(), caleFisier);
	IFileManager& fm = IFileManager::Get();

	FFileHelper::SaveStringToFile(continut, *caleCompleta);

	UE_LOG(LogTemp, Warning, TEXT("Am scris: %s la calea %s"), *continut, *caleCompleta);

	return true;
}

bool ULabirint::citesteToateHartile(FString caleDirector, TArray <FString>& fisiere) {

	FString caleCompleta = FPaths::Combine(FPaths::ProjectContentDir(), caleDirector);
	IFileManager& fm = IFileManager::Get();

	fm.FindFiles(fisiere, *caleCompleta);

	for (int i = 0; i < fisiere.Num(); i++) {
		UE_LOG(LogTemp, Warning, TEXT("Fisier %s"), *fisiere[i]);
	}
	return true;
}






bool ULabirint::genereazaHarta(int nrLinii, int nrColoane, TArray<int32>& matrice, int& outLinii, int& outColoane) {
	/*if (nrLinii > NL_MAX)
		outLinii = NL_MAX;
	else outLinii = nrLinii;*/

	outLinii = (nrLinii > NL_MAX) ? NL_MAX : nrLinii; // echivalent cu if else

	outColoane = (nrColoane > NC_MAX) ? NC_MAX : nrColoane;

	srand(time(NULL));

	int lStart = rand() % outLinii;
	int cStart = rand() % outColoane;

	for (int i = 0; i < outLinii * outColoane; i++)
	{
		harta[i] = 15;
		vizitat[i] = false;
	}
	stergePereti(lStart, cStart, outLinii, outColoane);

	//acum este harta completa

	matrice.Append(harta, outLinii * outColoane);

	return true;
}

// 0 - sus ; 1- dreapta ; 2-jos ; 3 stanga

#define SUS 0
#define DREAPTA 1
#define JOS 2
#define STANGA 3



bool ULabirint::stergePereti(int linie, int coloana, int nrLinii, int nrColoane) {

	vizitat[linie * nrColoane + coloana] = true;

	int vecini[4]; //indicii vecinilor(directiilor)
	int nrVecini = gasesteVecini(linie, coloana, nrLinii, nrColoane, vecini);
	int directie[4][2] = { {-1,0},{0,1},{1,0},{0,-1} };
	int coduri[4] = { 1,2,4,8 };

	shuffle(vecini, nrVecini);

	for (int i = 0; i < nrVecini; i++) {
		int linieVecin = linie + directie[vecini[i]][0];
		int coloanaVecin = coloana + directie[vecini[i]][1];
		int codPereteSters = coduri[(vecini[i] + 2) % 4];

		if (!vizitat[linieVecin * nrColoane + coloanaVecin]) {
			UE_LOG(LogTemp, Warning, TEXT("Linie : %d Coloana : %d, LinieVecin : %d ColoanaVecin : %d"), linie, coloana, linieVecin,coloanaVecin);
			
			harta[linie * nrColoane + coloana] -= coduri[vecini[i]];
			
			stergePerete(linieVecin, coloanaVecin, codPereteSters, nrLinii, nrColoane);
			stergePereti(linieVecin, coloanaVecin, nrLinii, nrColoane);
		}

	}
	return true;
}

bool ULabirint::stergePerete(int linie, int coloana, int codPereteSters, int nrLinii, int nrColoane) {
	vizitat[linie * nrColoane + coloana] = true;
	harta[linie * nrColoane + coloana] -= codPereteSters;

	UE_LOG(LogTemp, Warning, TEXT("Perete Sters , Linie : %d Coloana : %d , Cod Perete: %d"), linie, coloana, codPereteSters);
		return true;
}

void ULabirint::shuffle(int v[], int nr_elem) {
	for (int i = 0; i < nr_elem; i++) {
		int j = rand() % nr_elem;
		int aux = v[i];
		v[i] = v[j];
		v[j] = aux;
	}
}

int ULabirint::gasesteVecini(int linie, int coloana, int nrLinii, int nrColoane, int vecini[4]) {
	int i = 0;
	//sus
	if (linie > 0 && vizitat[(linie - 1) * nrColoane + coloana] == false)
	{
		vecini[i] = SUS;
		i++;
	}

	if (coloana < nrColoane-1 && vizitat[linie *nrColoane + coloana+1] == false)
	{
		vecini[i] = DREAPTA;
		i++;
	}

	if (linie < nrLinii-1 && vizitat[(linie+1) * nrColoane + coloana] == false)
	{
		vecini[i] = JOS;
		i++;
	}
	if (coloana > 0 && vizitat[linie * nrColoane + coloana -1] == false)
	{
		vecini[i] = STANGA;
		i++;
	}

	return i;
}