// Fill out your copyright notice in the Description page of Project Settings.


#include "AvatarLoader.h"
#include "INextHumanSDK.h"
#include "NextAvatar.h"
#include "NHCategory.h"
#include "RunChain.h"
#include "NHCallbackWrapper.h"

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
	static const FString TempAccessToken = "J+W+sX+b1zYiKgQcVLh5rlRCGbu8rKWrA/UYqfe6qSFIblSL0z0JQ8mF4Y6lYgkYuap95BSjcPhOOuLLr9cOw6TY/65sB7DfBBYCnoB8noxDXnj7s918/0nw+yvcY8WXl2HcbswMBPDiBGT/Gc6eQg==";
	// female assets
	static const TMap<FString, FString> FA{
		{CATEGORY_AVATAR, TEXT("avatar_64241b207f42de7d0775140d")},
		{CATEGORY_BODY, TEXT("body_642413f6178b9538264e6a8e")},
		{CATEGORY_COVERALL, TEXT("coverall_64312f6f10809e0df45537a7")},
		{CATEGORY_CLOTH, TEXT("cloth_6437c90d9181074839341076")},
		{CATEGORY_SHOES, TEXT("shoes_6437d1b39181074839341077")},
		{CATEGORY_TROUSER, TEXT("trouser_6437d2829181074839341078")},
		{CATEGORY_HAIR, TEXT("hair_643cb3f3d46ccd6078f72385")},
		{CATEGORY_EYEBROW, TEXT("eyebrow_643cb7b016938c6c359608f2")},
		{CATEGORY_EYELASH, TEXT("eyelash_643cdab716938c6c359608f3")},
		{CATEGORY_ANIMATION_BODY, TEXT("skeani_64421d63c6745f0f67a92205")},
		{CATEGORY_ANIMATION_FACE, TEXT("faceani_6442437ec6745f0f67a92207")},
	};

	// male assets
	static const TMap<FString, FString> MA{
		{CATEGORY_AVATAR, TEXT("avatar_64241b057f42de7d0775140c")},
		{CATEGORY_BODY, TEXT("body_642412df178b9538264e6a8d")},
		{CATEGORY_BEARD, TEXT("beard_6441229dc6745f0f67a92203")},
		{CATEGORY_HAIR, TEXT("hair_644276a3f472c547bb215c2b")},

		{CATEGORY_CLOTH, TEXT("cloth_64427ab843093f642a13d877")},
		{CATEGORY_SHOES, TEXT("shoes_64427afb43093f642a13d879")},
		{CATEGORY_TROUSER, TEXT("trouser_64427adc43093f642a13d878")},

		{CATEGORY_COVERALL, TEXT("coverall_6434feb205a0d40a4d6f5d27")},
		{CATEGORY_EYELASH, TEXT("eyelash_644276fc43093f642a13d876")},
		{CATEGORY_ANIMATION_BODY, TEXT("skeani_64427654f472c547bb215c2a")},
		{CATEGORY_ANIMATION_FACE, TEXT("faceani_644243a2886e096bfce937fb")},
	};

	if (!INextHumanSDKModule::Get().IsInitialized()) {
		INextHumanSDKModule::Get().Initialize(/* Put your access token here */ TempAccessToken, /* optional: custom server address ,*/ [=](int32 Code, const FString& Message)
		{
			if (Code == INextHumanSDKModule::CODE_SUCCESS) {
				LoadAvatar(FA, FVector(50, 0, 0), FRotator(0, 0, 0));
				LoadAvatar(MA, FVector(-50, 0, 0), FRotator(0, 0, 0));
			}
		});
	}
	else {
		LoadAvatar(FA, FVector(50, 0, 0), FRotator(0, 0, 0));
		LoadAvatar(MA, FVector(-50, 0, 0), FRotator(0, 0, 0));
	}
}

// Called every frame
void AAvatarLoader::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AAvatarLoader::LoadAvatar(const TMap<FString, FString>& Assets, const FVector& Position, const FRotator& Rotation) {
	UWorld* World = GetWorld();
	if (!World) {
		return;
	}

	auto Avatar = World->SpawnActor<ANextAvatar>(Position, Rotation);
	if (!Avatar) {
		return;
	}

	using nexthuman::sdk::demo::FRet;
	using nexthuman::sdk::demo::TTaskChain;
	struct FTestRet : public FRet {
		int64 ClothId;
		int64 ShoesId;
		int64 TrousersId;
		FTestRet(int32 InCode = 0, FString InMessage = TEXT(""), int64 InClothId = INT64_MIN, int64 InShoesId = INT64_MIN, int64 InTrousersId = INT64_MIN) :FRet(InCode, InMessage), ClothId(InClothId), ShoesId(InShoesId), TrousersId(InTrousersId) {}
	};
	typedef TTaskChain<FTestRet> FTaskChain;
	INextHumanSDKModule& SDK = INextHumanSDKModule::Get();

	FTaskChain& Tasks = FTaskChain::Create(ENamedThreads::AnyNormalThreadNormalTask, [=](const FTestRet& Last, FTaskChain::FOnStepEnd OnStepEnd) {
		OnStepEnd(FTestRet{});
	});

	// Cache resource
	for (auto& Pair : Assets) {
		Tasks.AndThen(ENamedThreads::AnyNormalThreadNormalTask, [=, &SDK](const FTestRet& Last, FTaskChain::FOnStepEnd OnStepEnd) {
			SDK.PrepareResource(Pair.Value, [=](int32 Code, const FString& Message) {
				OnStepEnd(FTestRet{ Code, Message });
			});
		});
	}

	Tasks.AndThen(ENamedThreads::AnyNormalThreadNormalTask, [=](const FTestRet& Last, FTaskChain::FOnStepEnd OnStepEnd) {
		Avatar->SetAvatarId(Assets[CATEGORY_AVATAR], [=](int32 Code, const FString& Message, int64 Id) {
			OnStepEnd(FTestRet{ Code, Message });
			{
				const FString Category = CATEGORY_MORPH_HEAD;		// CATEGORY_MORPH_XX
				const FString Key = "Height";						// Category对应的参数列表
				const float Value = 0.05;							// -1 ~ 1
				// 将头部高度morph值改为0.05
				Avatar->GetBody()->GetFace()->ChangeMorphValue(Category, Key, Value);
			}
		});
	});

	for (auto& Cate : TArray<FString>{
		//CATEGORY_COVERALL,
		CATEGORY_CLOTH,
		CATEGORY_TROUSER,
		CATEGORY_SHOES,
	}) {
		Tasks.AndThen(ENamedThreads::AnyNormalThreadNormalTask, [=](const FTestRet& Last, FTaskChain::FOnStepEnd OnStepEnd) {
			if (Assets.Contains(Cate)) {
				FNHCallback Callback;
				TSharedPtr<UNHCallbackWrapper> CallbackWrapper = MakeShareable<UNHCallbackWrapper>(NewObject<UNHCallbackWrapper>());
				CallbackWrapper->SetCallback([=](int32 Code, const FString& Message, int64 Id) {
					OnStepEnd(FTestRet{ Code, Message });
				});
				Callback.BindUFunction(CallbackWrapper.Get(), TEXT("Run"));
				Avatar->GetBody()->AddBundle(Assets[Cate], Callback);
			}
		});
	}

	//for (auto& Cate : TArray<FString>{
	//	CATEGORY_HAIR,
	//	//CATEGORY_EYEBROW, // 眉毛有问题
	//	CATEGORY_EYELASH,
	//}) {
	//	Tasks.AndThen(ENamedThreads::AnyNormalThreadNormalTask, [=](const FTestRet& Last, FTaskChain::FOnStepEnd OnStepEnd) {
	//		if (Assets.Contains(Cate)) {
	//			Avatar->AddBundleById(Assets[Cate], [=](int32 Code, const FString& Message, int64 Id) {
	//				if (Cate == CATEGORY_HAIR && Code == 0) {
	//					const FString Category = CATEGORY_HAIR;		// 毛发类型
	//					FGroomMaterialParam Param;					// 对应资产的材质球支持的修改参数
	//					Param.Color = FLinearColor::Black;
	//					// 将当前头发的颜色改为黑色
	//					Avatar->GetBody()->GetFace()->ChangeGroomMaterialParam(Category, Param);
	//				}
	//				OnStepEnd(FTestRet{ Code, Message });
	//				});
	//		}
	//		});
	//}

	Tasks.Start([=](const FTestRet& Last) {
		UE_LOG(LogTemp, Warning, TEXT("==>> End %d %s"), Last.Code, *Last.Message);
	});
}
