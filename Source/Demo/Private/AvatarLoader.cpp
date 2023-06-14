// Fill out your copyright notice in the Description page of Project Settings.


#include "AvatarLoader.h"
#include "INextHumanSDK.h"
#include "RunChain.h"
#include "NextAvatar.h"
#include "NHCategory.h"
#include "NHCallbackWrapper.h"
#include "NHCommon.h"
#include "NHUtil.h"

using namespace nexthuman::sdk;
using namespace nexthuman::sdk::demo;

// Sets default values
AAvatarLoader::AAvatarLoader()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAvatarLoader::BeginPlay()
{
	Super::BeginPlay();

	static const FString Domain = TEXT("https://open-meta.tmall.com");
	if (!INextHumanSDKModule::Get().IsInitialized()) {
		INextHumanSDKModule::Get().Initialize(
			ACCESS_TOKEN,
			[=](int32 Code, const FString& Message) {
				if (Code == INextHumanSDKModule::CODE_SUCCESS) {
					if (Domain.IsEmpty()) {
						LoadTen();
					}
					else {
						Load(TEXT("avatar_641884b0ba43910940e21054"));
					}
				}
			}, Domain);
	}
}

// Called every frame
void AAvatarLoader::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAvatarLoader::LoadTen() {
	TArray<FAvatarInfo> Avatars = FNHUtil::GetAvatarInfo();
	for (int i = 0; i < Avatars.Num(); i++) {
		FAvatarInfo& LoadInfo = Avatars[i];
		if (i < Avatars.Num()) {
			FTestTaskChain& Tasks = FTestTaskChain::Create();
			TSharedPtr<FAvatarWrapper> Wrapper = MakeShareable(new FAvatarWrapper(*this, Tasks, LoadInfo.AvatarId, LoadInfo.Assets, LoadInfo.Position, LoadInfo.Rotation));
			AvatarWrappers.Add(Wrapper);
			(Wrapper)->Load();
			Tasks.Start([=](const FTestRet& Last) {
				AvatarWrappers.Remove(Wrapper);
				UE_LOG(LogTemp, Warning, TEXT("End %d %s"), Last.Code, *Last.Message);
			});
		}
	}
}

void AAvatarLoader::TestRestoreAndRemove() {
	auto Avatar = GetWorld()->SpawnActor<ANextAvatar>(FVector(0, 0, 0), FRotator(0, 0, 0));
	Avatar->SetAvatarId(FEMALE_AVATAR_ID, [=](int32 Code, const FString& Message, TMap<FString, ANextAvatar::FBundleInfo> LoadedBundle) {
		AsyncTask(ENamedThreads::GameThread, [=]() {
			for (auto Pair : LoadedBundle) {
				Avatar->RemoveBundle(Pair.Value.Index);
			}
		});
	}, [](const FString& Category) {
		// Only restore below categories
		return Category != TEXT("");
	});
}

void AAvatarLoader::Load(const FString AvatarId, const FVector& Position, const FRotator& Rotation) {
	auto Avatar = GetWorld()->SpawnActor<ANextAvatar>(FVector(0, 0, 0), FRotator(0, 0, 0));
	Avatar->SetAvatarId(AvatarId, [=](int32 Code, const FString& Message, TMap<FString, ANextAvatar::FBundleInfo> LoadedBundle) {
		UE_LOG(LogTemp, Warning, TEXT("SetAvatarId %d %s %d"), Code, *Message, LoadedBundle.Num());
		for (auto& Item : LoadedBundle) {
			UE_LOG(LogTemp, Warning, TEXT("LoadedBundle ==>> %s %d"), *Item.Key, Item.Value.Index);
		}

		Avatar->AddBundleById(TEXT("cloth_6434df618b3a9d45f9c9d1b9"), [=](int32 Code, const FString& Message, int64 Index) {
			UE_LOG(LogTemp, Warning, TEXT("===>>> %d %s %lld"), Code, *Message, Index);
		});
	}, [](const FString& Category) {
		return false;
	});
}