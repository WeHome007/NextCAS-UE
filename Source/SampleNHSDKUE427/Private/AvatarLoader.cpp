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

	if (!INextHumanSDKModule::Get().IsInitialized()) {
		INextHumanSDKModule::Get().Initialize(
			ACCESS_TOKEN,
			[=](int32 Code, const FString& Message) {
				if (Code == INextHumanSDKModule::CODE_SUCCESS) {
					LoadTen();
					//TestRestoreAndRemove();
				}
			},
			TEXT(""), //TEXT("https://open-meta.tmall.com"), // optional: custom server address
			TEXT(""));
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