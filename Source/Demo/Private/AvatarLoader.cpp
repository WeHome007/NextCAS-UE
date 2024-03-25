// Fill out your copyright notice in the Description page of Project Settings.


#include "AvatarLoader.h"
#include "INextHumanSDK.h"
#include "NextHuman/NHCategory.h"
#include "NHAgentComponent.h"

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

	FString DefaultQuestion = TEXT("你好！");
	FString Question;
	FParse::Value(FCommandLine::Get(), TEXT("-q="), Question);
	if (Question.IsEmpty()) {
		Question = DefaultQuestion;
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, FString::Printf(TEXT("argument(-q) not specified，using default：%s"), *DefaultQuestion));
	}

	FString Filter;
	FParse::Value(FCommandLine::Get(), TEXT("-filter="), Filter);

	if (!INextHumanSDKModule::Get().IsInitialized()) {
		// Initialize SDK
		INextHumanSDKModule::Get().Initialize(AccessToken, [=](int32 Code, const FString& Message) {
			if (Code == FNHError::SUCCESS) {

				UE_LOG(LogTemp, Warning, TEXT("SDK Initialize %d %s %d"), Code, *Message, IsInGameThread());
				{
					UWorld* World = GetWorld();
					ANextAvatar* Avatar = World->SpawnActor<ANextAvatar>(FVector(0, 0, 0), FRotator(0, 0, 0));

					// Load Avatar by Id
					GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, FString::Printf(TEXT("Avatar loading start：%s"), *AvatarId));
					Avatar->SetAvatarId(AvatarId, [=](int32 Code, const FString& Message, TMap<FString, ANextAvatar::FBundleInfo> BundleInfos) {
						bool AsSuccess = true;
						for (auto& BundleInfo : BundleInfos) {
							AsSuccess = AsSuccess && (BundleInfo.Value.Code == FNHError::SUCCESS || BundleInfo.Value.Code == FNHError::ERROR_RESTORE || BundleInfo.Value.Code == FNHError::ERROR_LOAD);
							FString BundleInfoMessage = FString::Printf(TEXT("Bundle %s %d %s %d"), *(BundleInfo.Value.Bundle->GetId()), BundleInfo.Value.Code, *BundleInfo.Value.Message, BundleInfo.Value.Index);
							UE_LOG(LogTemp, Warning, TEXT("%s"), *BundleInfoMessage);
						}
						UE_LOG(LogTemp, Warning, TEXT("SetAvatarId %s"), AsSuccess ? TEXT("true") : TEXT("false"));
						FColor Color = AsSuccess ? FColor::Green : FColor::Red;
						GEngine->AddOnScreenDebugMessage(-1, 10.0f, Color, FString::Printf(TEXT("Avatar loading end：%s %d %s"), *AvatarId, Code, *Message));

						if (AsSuccess) {

							// Get or Create Agent
							UNHAgentComponent* Agent = Cast<UNHAgentComponent>(Avatar->GetComponentByClass(UNHAgentComponent::StaticClass()));
							if (!Agent) {
								Agent = NewObject<UNHAgentComponent>(Avatar);
								Agent->ComponentTags.Add(TEXT("CtrlFBF"));
								Agent->RegisterComponent();
								Agent->AttachToComponent(Avatar->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
							}

							// Bind Answer Callback
							Agent->OnAnswer().BindLambda([=](nexthuman::sdk::FNHError Result, const FString& Text) {
								UE_LOG(LogTemp, Display, TEXT("Answer: %d, %s, %s"), Result.Code, *Result.Message, *Text);
								GEngine->AddOnScreenDebugMessage(-1, 10.0f, Color, FString::Printf(TEXT("A：%s"), *Text));
							});

							// Ask Question
							GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Black, FString::Printf(TEXT("Q: %s"), *Question));
							Agent->Ask(Question);

						}
					}, [=](const FString& Category) {
						return Filter.IsEmpty() || !Filter.Contains(Category, ESearchCase::IgnoreCase);
					});

				}
			}
		});
	}
}

// Called every frame
void AAvatarLoader::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}