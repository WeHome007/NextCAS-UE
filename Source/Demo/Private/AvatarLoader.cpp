// Fill out your copyright notice in the Description page of Project Settings.


#include "AvatarLoader.h"
#include "INextHumanSDK.h"
#include "NHCategory.h"

using namespace nexthuman::sdk;

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


	FString AccessToken;
	FParse::Value(FCommandLine::Get(), TEXT("-at="), AccessToken);
	if (AccessToken.IsEmpty()) {
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("need argument(-at) to get accesstoken"));
	}

	FString DefaultAvatarId = TEXT("avatar_63edcef5ea719833f2b1eaff");
	FString AvatarId;
	FParse::Value(FCommandLine::Get(), TEXT("-aid="), AvatarId);
	if (AvatarId.IsEmpty()) {
		AvatarId = DefaultAvatarId;
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, FString::Printf(TEXT("argument(-aid) not specified，using default：%s"), *DefaultAvatarId));
	}

	if (!INextHumanSDKModule::Get().IsInitialized()) {
		// Initialize SDK
		INextHumanSDKModule::Get().Initialize(AccessToken, [=](int32 Code, const FString& Message) {
			if (Code == FNHError::SUCCESS) {

				UE_LOG(LogTemp, Warning, TEXT("SDK Initialize %d %s %d"), Code, *Message, IsInGameThread());
				UWorld* World = GetWorld();
				ANextAvatar* Avatar = World->SpawnActor<ANextAvatar>(FVector(0, 0, 0), FRotator(0, 0, 0));

				// Load Avatar by Id
				GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, FString::Printf(TEXT("Avatar loading start：%s"), *AvatarId));
				Avatar->SetAvatarId(AvatarId, [=](int32 Code, const FString& Message, TMap<FString, ANextAvatar::FBundleInfo> BundleInfos) {
					FColor Color = Code == 0 ? FColor::Green : FColor::Red;
					GEngine->AddOnScreenDebugMessage(-1, 10.0f, Color, FString::Printf(TEXT("Avatar loading end：%s %d %s"), *AvatarId, Code, *Message));
					for (auto& BundleInfo : BundleInfos) {
						GEngine->AddOnScreenDebugMessage(-1, 5.0f, Color, FString::Printf(TEXT("Bundle %s %d %s %d"), *BundleInfo.Value.Bundle.Id, BundleInfo.Value.Code, *BundleInfo.Value.Message, BundleInfo.Value.Index));
					}

					if (Code == FNHError::SUCCESS) {


					}
				});

			}
		});
	}
}

// Called every frame
void AAvatarLoader::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}