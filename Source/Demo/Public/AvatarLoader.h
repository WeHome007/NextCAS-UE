// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AvatarWrapper.h"
#include "AvatarLoader.generated.h"

UCLASS()
class DEMO_API AAvatarLoader : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAvatarLoader();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void LoadTen();
	void TestRestoreAndRemove();
	void Load(const FString AvatarId, const FVector& Position = { 0, 0, 0 }, const FRotator& Rotation = { 0, 0, 0 });
	TArray<TSharedPtr<nexthuman::sdk::demo::FAvatarWrapper>> AvatarWrappers;
};
