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
	FString AccessToken = TEXT("dYQrr2AabBMpId92+MOYmnhUAEIDALcLWfdbgd4AJm8EL2P5t7laLVtfFukTkuAJVF6OZb7bDt6p8SBSpL6i3n+zdMTcxTUNHRPZM/uSVgXftkY4rZgP4PISS+I4RroCTFVTLzoKpDv9pHav3OUfX75GrjDkl6xOYfeH0Rtdp7DOTd5IY+utrKbxAZNQt9TE");
	FString AvatarId = TEXT("avatar_205547");
	if (!INextHumanSDKModule::Get().IsInitialized()) {
		INextHumanSDKModule::Get().Initialize(AccessToken, [=](int32 Code, const FString& Message) {
			if (Code == FNHError::SUCCESS) {
				UE_LOG(LogTemp, Warning, TEXT("SDK Initialize %d %s %d"), Code, *Message, IsInGameThread());
				UWorld* World = GetWorld();
				ANextAvatar* Avatar = World->SpawnActor<ANextAvatar>(FVector(0, 0, 0), FRotator(0, 0, 0));
				Avatar->SetAvatarId(AvatarId, [=](int32 Code, const FString& Message, TMap<FString, ANextAvatar::FBundleInfo> BundleInfo) {

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