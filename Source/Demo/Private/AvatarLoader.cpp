// Fill out your copyright notice in the Description page of Project Settings.


#include "AvatarLoader.h"
#include "INextHumanSDK.h"
#include "NextHuman/NHCategory.h"
#include "NHAgentComponent.h"
#include "NHSpeakerComponent.h"
#include "Blueprint/UserWidget.h"

using namespace nexthuman::sdk;

const float TimeToDisplay = 20.0F;

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
		GEngine->AddOnScreenDebugMessage(-1, TimeToDisplay, FColor::Red, TEXT("need argument(-at) to get accesstoken"));
	}

	FString DefaultAvatarId = TEXT("avatar_63edcef5ea719833f2b1eaff");
	FString AvatarId;
	FParse::Value(FCommandLine::Get(), TEXT("-aid="), AvatarId);
	if (AvatarId.IsEmpty()) {
		AvatarId = DefaultAvatarId;
		GEngine->AddOnScreenDebugMessage(-1, TimeToDisplay, FColor::Yellow, FString::Printf(TEXT("argument(-aid) not specified，using default：%s"), *DefaultAvatarId));
	}

	bool IsTestSpeak = FParse::Param(FCommandLine::Get(), TEXT("testspeak"));
	bool IsTestAsk = FParse::Param(FCommandLine::Get(), TEXT("testask"));
	UE_LOG(LogTemp, Display, TEXT("-testspeak=%d -testask=%d"), IsTestSpeak, IsTestAsk);

	UWorld* W1 = GetWorld();
	APlayerController* PlayerController = W1->GetFirstPlayerController();
	
	UClass* MyWidgetClass = LoadClass<UClass>(nullptr, TEXT("WidgetBlueprint'/Game/Input/TextInput.TextInput'"));
	UE_LOG(LogTemp, Display, TEXT("Add Widget %p and %p"), PlayerController, MyWidgetClass);
	//if (PlayerController && MyWidgetClass) {
	//	UUserWidget* MyWidget = CreateWidget<UUserWidget>(PlayerController, MyWidgetClass);
	//	if (MyWidget) {
	//		UE_LOG(LogTemp, Display, TEXT("My Widget Added"));
	//		MyWidget->AddToViewport();
	//	}
	//}
	//

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
					GEngine->AddOnScreenDebugMessage(-1, TimeToDisplay, FColor::Blue, FString::Printf(TEXT("Avatar loading start：%s"), *AvatarId));
					Avatar->SetAvatarId(AvatarId, [=](int32 Code, const FString& Message, TMap<FString, ANextAvatar::FBundleInfo> BundleInfos) {
						if (CheckResult(AvatarId, Code, Message, BundleInfos)) {
							if (IsTestSpeak) {
								TestSpeak(Avatar);
							}
							else if (IsTestAsk) {
								TestAsk(Avatar);
							}
						}
					}, [=](const FString& Category) {
						return Filter.IsEmpty() || !Filter.Contains(Category, ESearchCase::IgnoreCase);
					});

				}
			}
			else {
				GEngine->AddOnScreenDebugMessage(-1, TimeToDisplay, FColor::Red, FString::Printf(TEXT("SDK init failed：%s"), *Message));
			}
		});
	}
}

void AAvatarLoader::TestAsk(ANextAvatar* Avatar) {
	FString DefaultQuestion = TEXT("你好！");
	FString Question;
	FParse::Value(FCommandLine::Get(), TEXT("-q="), Question);
	if (Question.IsEmpty()) {
		Question = DefaultQuestion;
		GEngine->AddOnScreenDebugMessage(-1, TimeToDisplay, FColor::Yellow, FString::Printf(TEXT("argument(-q) not specified，using default：%s"), *DefaultQuestion));
	}

	// Get or Create Agent
	UNHAgentComponent* Agent = Cast<UNHAgentComponent>(Avatar->GetComponentByClass(UNHAgentComponent::StaticClass()));
	if (!Agent) {
		Agent = NewObject<UNHAgentComponent>(Avatar);
		Agent->ComponentTags.Add(TEXT("CtrlFBF"));
		Agent->RegisterComponent();
		Agent->AttachToComponent(Avatar->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	}

	// Bind Answer Callback
	Agent->OnAnswer().AddLambda([=](nexthuman::sdk::FNHError Result, const FString& Text) {

		if (Result.Code == 0) {
			UE_LOG(LogTemp, Display, TEXT("Answer Complete: %d %s %s"), Result.Code, *Result.Message, *Text);
		}
		else {
			UE_LOG(LogTemp, Display, TEXT("Answer: %d, %s, %s"), Result.Code, *Result.Message, *Text);
		}
		GEngine->AddOnScreenDebugMessage(-1, TimeToDisplay, FColor::Black, FString::Printf(TEXT("A：%s"), *Text));
	});

	// Ask Question
	GEngine->AddOnScreenDebugMessage(-1, TimeToDisplay, FColor::Black, FString::Printf(TEXT("Q: %s"), *Question));
	Agent->Ask(Question);
}

const FString Content = TEXT("明月几时有？把酒问青天。 不知天上宫阙，今夕是何年。 我欲乘风归去，又恐琼楼玉宇，高处不胜寒。 起舞弄清影，何似在人间。转朱阁，低绮户，照无眠。 不应有恨，何事长向别时圆？ 人有悲欢离合，月有阴晴圆缺，此事古难全。 但愿人长久，千里共婵娟。");

void AAvatarLoader::TestSpeak(ANextAvatar* Avatar) {
	// Get or Create Agent
	UNHSpeakerComponent* Agent = Cast<UNHSpeakerComponent>(Avatar->GetComponentByClass(UNHSpeakerComponent::StaticClass()));
	if (!Agent) {
		Agent = NewObject<UNHSpeakerComponent>(Avatar);
		Agent->ComponentTags.Add(TEXT("CtrlFBF"));
		Agent->RegisterComponent();
		Agent->AttachToComponent(Avatar->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	}

	// Bind Answer Callback
	Agent->OnComplete().Clear();
	Agent->OnComplete().AddLambda([=](nexthuman::sdk::FNHError Result, const FString& Text) {
		UE_LOG(LogTemp, Display, TEXT("Speak complete: %d, %s, %s"), Result.Code, *Result.Message, *Text);
		// ActorId: 
		// FaceModel: "richu" for male, "beibei" for female
		Agent->Speak(Content, TEXT("641811add41a3f2f91247ae8"), TEXT("beibei"));
	});

	// Ask Question
	Agent->Speak(Content);
}

bool AAvatarLoader::CheckResult(const FString& AvatarId, int32 Code, const FString& Message, TMap<FString, ANextAvatar::FBundleInfo> BundleInfos) {
	bool AsSuccess = true;
	for (auto& BundleInfo : BundleInfos) {
		AsSuccess = AsSuccess && (BundleInfo.Value.Code == FNHError::SUCCESS || BundleInfo.Value.Code == FNHError::ERROR_RESTORE || BundleInfo.Value.Code == FNHError::ERROR_LOAD);
		FString BundleInfoMessage = FString::Printf(TEXT("Bundle Id(%s) Category(%s) Index(%lld) %d %s"), *(BundleInfo.Value.Bundle->GetId()), *BundleInfo.Value.Bundle->GetCategory(), BundleInfo.Value.Index, BundleInfo.Value.Code, *BundleInfo.Value.Message);
		UE_LOG(LogTemp, Warning, TEXT("%s"), *BundleInfoMessage);
	}
	UE_LOG(LogTemp, Warning, TEXT("SetAvatarId %s"), AsSuccess ? TEXT("true") : TEXT("false"));
	FColor Color = AsSuccess ? FColor::Green : FColor::Red;
	GEngine->AddOnScreenDebugMessage(-1, TimeToDisplay, Color, FString::Printf(TEXT("Avatar loading end：%s %d %s"), *AvatarId, Code, *Message));
	return AsSuccess;
}

// Called every frame
void AAvatarLoader::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}