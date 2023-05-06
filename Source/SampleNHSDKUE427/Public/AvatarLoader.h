// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NHCallbackWrapper.h"
#include "RunChain.h"
#include "NextAvatar.h"
#include "AvatarLoader.generated.h"

UCLASS()
class SAMPLENHSDKUE427_API AAvatarLoader : public AActor
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
	struct FTestRet : public nexthuman::sdk::demo::FRet {
		int64 ClothId;
		int64 ShoesId;
		int64 TrousersId;
		FTestRet(int32 InCode = 0, FString InMessage = TEXT(""), int64 InClothId = INT64_MIN, int64 InShoesId = INT64_MIN, int64 InTrousersId = INT64_MIN) :FRet(InCode, InMessage), ClothId(InClothId), ShoesId(InShoesId), TrousersId(InTrousersId) {}
	};
	typedef nexthuman::sdk::demo::TTaskChain<FTestRet> FTaskChain;

	void LoadAvatar(const TMap<FString, FString>& Assets, const FVector& Position, const FRotator& Rotation);
	void AddFaceBundle(FTaskChain& Chain, ANextAvatar* Avatar, const FString& Key, const FString& Id, TFunction<void(int64)> OnComplete = [](int64) {});
	void AddBodyBundle(FTaskChain& Chain, ANextAvatar* Avatar, const FString& Key, const FString& Id, TFunction<void(int64)> OnComplete = [](int64) {});
	void RemoveBodyBundle(FTaskChain& Chain, ANextAvatar* Avatar, const FString& Key);
	void RemoveFaceBundle(FTaskChain& Chain, ANextAvatar* Avatar, const FString& Key);
	void Delay(FTaskChain& Chain, float Seconds);
	TArray<UNHCallbackWrapper*> Callbacks;
	TMap<FString, int64> IndexMap;
};
