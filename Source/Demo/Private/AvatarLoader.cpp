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

	static const FString Domain =
		TEXT("");
		//TEXT("https://open-meta.tmall.com");
	if (!INextHumanSDKModule::Get().IsInitialized()) {
		INextHumanSDKModule::Get().Initialize(
			ACCESS_TOKEN,
			[=](int32 Code, const FString& Message) {
				if (Code == INextHumanSDKModule::CODE_SUCCESS && !FParse::Param(FCommandLine::Get(), TEXT("nexthuman.notest"))) {
					if (Domain.IsEmpty()) {
						auto Infos = FNHUtil::GetAvatarInfo();
						for (int i = 0; i < Infos.Num(); i++) {
							Load(Infos[i]);
						}

						//Load(FEMALE_AVATAR_ID, {
						//	TEXT("eyemakeup_64a5382a7868363aa03260bc"),
						//	TEXT("blusher_64a538157868363aa03260bb"),
						//	TEXT("eyelash_6482e3a7b325db3f950dca60"),
						//	TEXT("eyebrow_645885a32a48eb54410d4c49"),
						//	});
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

void AAvatarLoader::Load(FAvatarInfo AvatarInfo) {
	FTestTaskChain& Tasks = FTestTaskChain::Create();
	FAvatarWrapperPtr Wrapper = MakeShareable(new FAvatarWrapper(*this, Tasks, AvatarInfo.AvatarId, AvatarInfo.Assets, AvatarInfo.Position, AvatarInfo.Rotation));
	AvatarWrappers.Add(Wrapper);
	(Wrapper)->Load();
	Tasks.Start([=](const FTestRet& Last) {
		AvatarWrappers.Remove(Wrapper);
		UE_LOG(LogTemp, Warning, TEXT("End %d %s"), Last.Code, *Last.Message);
	});
}

void AAvatarLoader::Load(const FString AvatarId, TArray<FString> BundleIds, ANextAvatar::FRestoreFilter RestoreFilter, const FVector& Position, const FRotator& Rotation) {
	auto Avatar = GetWorld()->SpawnActor<ANextAvatar>(Position, Rotation);

	Avatar->SetAvatarId(AvatarId, [=](int32 Code, const FString& Message, TMap<FString, ANextAvatar::FBundleInfo> LoadedBundle) {
		UE_LOG(LogTemp, Warning, TEXT("SetAvatarId %d %s %d"), Code, *Message, LoadedBundle.Num());
		for (auto& Item : LoadedBundle) {
			UE_LOG(LogTemp, Warning, TEXT("LoadedBundle ==>> %s %lld %d %s"), *Item.Key, Item.Value.Index, Item.Value.Code, *Item.Value.Message);
		}

		for (auto& Id : BundleIds) {
			Avatar->AddBundleById(Id, [=](int32 Code, const FString& Message, int64 Index) {
				UE_LOG(LogTemp, Warning, TEXT("AddBundleById  %s %d %s %lld"), *Id, Code, *Message, Index);
			});
		}	
	}, RestoreFilter);
}