// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBlueprintFunctionLibrary.h"

int UMyBlueprintFunctionLibrary::f(int a, int b) {
	return a + b;
}

int UMyBlueprintFunctionLibrary::g(int a, int b, int& c) {
	c = a * b;
	return a - b;
}