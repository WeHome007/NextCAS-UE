// Fill out your copyright notice in the Description page of Project Settings.


#include "AvatarLoader.h"
#include "INextHumanSDK.h"
#include "NextAvatar.h"
#include "RunChain.h"

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
	static const FString TempAccessToken = "J+W+sX+b1zYiKgQcVLh5rlRCGbu8rKWrA/UYqfe6qSFIblSL0z0JQ8mF4Y6lYgkYuap95BSjcPhOOuLLr9cOw6TY/65sB7DfBBYCnoB8noxDXnj7s918/0nw+yvcY8WXl2HcbswMBPDiBGT/Gc6eQg==";
	if (!INextHumanSDKModule::Get().IsInitialized()) {

		INextHumanSDKModule::Get().Initialize(/* Put your access token here */ TempAccessToken, /* optional: custom server address ,*/ [=](int32 Code, const FString& Message)
		{
			if (Code == INextHumanSDKModule::CODE_SUCCESS) {
				LoadAvatar();
			}
		});
	}
	else {
		LoadAvatar();
	}
}

// Called every frame
void AAvatarLoader::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AAvatarLoader::LoadAvatar() {
	UWorld* World = GetWorld();
	if (!World) {
		return;
	}

	auto Avatar = World->SpawnActor<ANextAvatar>(FVector(0, 0, 20), FRotator(0, 0, 0));
	if (!Avatar) {
		return;
	}
	//female
	static const FString AvatarId = TEXT("avatar_64241b207f42de7d0775140d");
	static const FString BodyId = TEXT("body_642413f6178b9538264e6a8e");
	static const FString CoverallId = TEXT("coverall_64312f6f10809e0df45537a7");
	static const FString ClothId = TEXT("cloth_6437c90d9181074839341076");
	static const FString ShoesId = TEXT("shoes_6437d1b39181074839341077");
	static const FString TrousersId = TEXT("trouser_6437d2829181074839341078");

	using nexthuman::sdk::demo::FRet;
	using nexthuman::sdk::demo::TTaskChain;
	struct FTestRet : public FRet {
		int64 ClothId;
		int64 ShoesId;
		int64 TrousersId;
		FTestRet(int32 InCode, FString InMessage, int64 InClothId = INT64_MIN, int64 InShoesId = INT64_MIN, int64 InTrousersId = INT64_MIN):FRet(InCode, InMessage), ClothId(InClothId), ShoesId(InShoesId), TrousersId(InTrousersId) {}
	};
	typedef TTaskChain<FTestRet> FTaskChain;

	FTaskChain& Tasks = FTaskChain::Create(ENamedThreads::AnyNormalThreadNormalTask, [=](const FTestRet& Last, FTaskChain::FOnStepEnd OnStepEnd) {
		INextHumanSDKModule::Get().PrepareResource(AvatarId, [=](int32 Code, const FString& Message) {
			OnStepEnd(FTestRet{ Code, Message });
		});
	}).AndThen(ENamedThreads::AnyNormalThreadNormalTask, [=](const FTestRet& Last, FTaskChain::FOnStepEnd OnStepEnd) {
		INextHumanSDKModule::Get().PrepareResource(BodyId, [=](int32 Code, const FString& Message) {
			OnStepEnd(FTestRet{ Code, Message });
		});
	}).AndThen(ENamedThreads::AnyNormalThreadNormalTask, [=](const FTestRet& Last, FTaskChain::FOnStepEnd OnStepEnd) {
		INextHumanSDKModule::Get().PrepareResource(CoverallId, [=](int32 Code, const FString& Message) {
			OnStepEnd(FTestRet{ Code, Message });
		});
	}).AndThen(ENamedThreads::AnyNormalThreadNormalTask, [=](const FTestRet& Last, FTaskChain::FOnStepEnd OnStepEnd) {
		INextHumanSDKModule::Get().PrepareResource(ClothId, [=](int32 Code, const FString& Message) {
			OnStepEnd(FTestRet{ Code, Message });
		});
	}).AndThen(ENamedThreads::AnyNormalThreadNormalTask, [=](const FTestRet& Last, FTaskChain::FOnStepEnd OnStepEnd) {
		INextHumanSDKModule::Get().PrepareResource(ShoesId, [=](int32 Code, const FString& Message) {
			OnStepEnd(FTestRet{ Code, Message });
		});
	}).AndThen(ENamedThreads::AnyNormalThreadNormalTask, [=](const FTestRet& Last, FTaskChain::FOnStepEnd OnStepEnd) {
		INextHumanSDKModule::Get().PrepareResource(TrousersId, [=](int32 Code, const FString& Message) {
			OnStepEnd(FTestRet{ Code, Message });
		});
	}).AndThen(ENamedThreads::AnyNormalThreadNormalTask, [=](const FTestRet& Last, FTaskChain::FOnStepEnd OnStepEnd) {
		Avatar->SetAvatarId(/* Put Avatar Id here */ AvatarId, [=](int32 Code, const FString& Message, int64 Id) {
			OnStepEnd(FTestRet{ Code, Message });
		});
	});

	for (int i = 0; i < 1; i++) {
		Tasks.AndThen(ENamedThreads::AnyNormalThreadNormalTask, [=](const FTestRet& Last, FTaskChain::FOnStepEnd OnStepEnd) {
			Avatar->AddBundleById(ClothId, [=](int32 Code, const FString& Message, int64 Id) {
				OnStepEnd(FTestRet{ Code, Message, Id });
			});
		}).AndThen(ENamedThreads::AnyNormalThreadNormalTask, [=](const FTestRet& Last, FTaskChain::FOnStepEnd OnStepEnd) {
			Avatar->AddBundleById(ShoesId, [=](int32 Code, const FString& Message, int64 Id) {
				OnStepEnd(FTestRet{ Code, Message, Last.ClothId, Id});
			});
		}).AndThen(ENamedThreads::AnyNormalThreadNormalTask, [=](const FTestRet& Last, FTaskChain::FOnStepEnd OnStepEnd) {
			Avatar->AddBundleById(TrousersId, [=](int32 Code, const FString& Message, int64 Id) {
				OnStepEnd(FTestRet{ Code, Message, Last.ClothId, Last.ShoesId, Id });
			});
		}).AndThen(ENamedThreads::GameThread, [=](const FTestRet& Last, FTaskChain::FOnStepEnd OnStepEnd) {
			FTimerHandle TH;
			GetWorldTimerManager().SetTimer(TH, [=]() {
				Avatar->RemoveBundle(Last.ClothId);
				OnStepEnd(FTestRet{ 0, TEXT(""), INT64_MIN, Last.ShoesId, Last.TrousersId });
			}, 3.0, false);
		}).AndThen(ENamedThreads::GameThread, [=](const FTestRet& Last, FTaskChain::FOnStepEnd OnStepEnd) {
			FTimerHandle TH;
			GetWorldTimerManager().SetTimer(TH, [=]() {
				Avatar->RemoveBundle(Last.ShoesId);
				OnStepEnd(FTestRet{ 0, TEXT(""), INT64_MIN, INT64_MIN, Last.TrousersId });
			}, 3.0, false);
		}).AndThen(ENamedThreads::GameThread, [=](const FTestRet& Last, FTaskChain::FOnStepEnd OnStepEnd) {
			FTimerHandle TH;
			GetWorldTimerManager().SetTimer(TH, [=]() {
				Avatar->RemoveBundle(Last.TrousersId);
				OnStepEnd(FTestRet{ 0, TEXT(""), INT64_MIN, INT64_MIN, INT64_MIN });
			}, 3.0, false);
		});
	}

	Tasks.Start([=](const FTestRet& Last) {
		UE_LOG(LogTemp, Warning, TEXT("==>> End"));
	});
}