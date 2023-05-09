// Fill out your copyright notice in the Description page of Project Settings.


#include "AvatarLoader.h"
#include "INextHumanSDK.h"
#include "NHCategory.h"
#include "NHCallbackWrapper.h"

using namespace nexthuman::sdk;

const TArray<AAvatarLoader::FAsset> AAvatarLoader::ASSETS {
	{ TEXT("SDK_Cloth_F_FC001"),	TEXT("cloth_6437c90d9181074839341076"), EGender::FEMALE, CATEGORY_CLOTH },
	{ TEXT("SDK_Cloth_F_FC002"),	TEXT("cloth_64421bfd886e096bfce937f5"), EGender::FEMALE, CATEGORY_CLOTH },
	{ TEXT("SDK_Cloth_F_neiyi"),	TEXT("cloth_64588abd2a48eb54410d4c65"), EGender::FEMALE, CATEGORY_CLOTH },
	{ TEXT("SDK_Coverall_F_FC002"), TEXT("coverall_644b7b02b4473e4ba1d59563"), EGender::FEMALE, CATEGORY_COVERALL },
	{ TEXT("SDK_Coverall_F_FC003"), TEXT("coverall_64350e7f05a0d40a4d6f5d28"), EGender::FEMALE, CATEGORY_COVERALL },
	{ TEXT("SDK_Earring_F_FC001"),	TEXT("earring_645350fb5abd84599e3b3d71"), EGender::FEMALE, CATEGORY_EARRINGS },
	{ TEXT("SDK_Earring_F_FC002"),	TEXT("earring_645885932a48eb54410d4c48"), EGender::FEMALE, CATEGORY_EARRINGS },
	{ TEXT("SDK_Eyebrows_F_01"),	TEXT("eyebrow_643cb7b016938c6c359608f2"), EGender::FEMALE, CATEGORY_EYEBROW },
	{ TEXT("SDK_Eyebrows_F_02"),	TEXT("eyebrow_645885a32a48eb54410d4c49"), EGender::FEMALE, CATEGORY_EYEBROW },
	{ TEXT("SDK_Glass_F_FC001"),	TEXT("glass_645882412a48eb54410d4c46"), EGender::FEMALE, CATEGORY_GLASS },
	{ TEXT("SDK_Glass_F_FC002"),	TEXT("glass_645885bd2a48eb54410d4c4a"), EGender::FEMALE, CATEGORY_GLASS },
	{ TEXT("SDK_Hair_F_FC01"),		TEXT("hair_643cb3f3d46ccd6078f72385"), EGender::FEMALE, CATEGORY_HAIR },
	{ TEXT("SDK_Hat_F_FC001"),		TEXT("hat_645350e95abd84599e3b3d70"), EGender::FEMALE, CATEGORY_HAT },
	{ TEXT("SDK_Hat_F_FC002"),		TEXT("hat_645885ec2a48eb54410d4c4b"), EGender::FEMALE, CATEGORY_HAT },
	{ TEXT("SDK_blusher_F_01"),		TEXT("blusher_645351575abd84599e3b3d74"), EGender::FEMALE, CATEGORY_MAKEUP_BLUSHER },
	{ TEXT("SDK_blusher_F_02"),		TEXT("blusher_645885fd2a48eb54410d4c4c"), EGender::FEMALE, CATEGORY_MAKEUP_BLUSHER },
	{ TEXT("SDK_eyemakeup_F_01"),	TEXT("eyemakeup_645351605abd84599e3b3d75"), EGender::FEMALE, CATEGORY_MAKEUP_EYE },
	{ TEXT("SDK_eyemakeup_F_02"),	TEXT("eyemakeup_6458860e2a48eb54410d4c4d"), EGender::FEMALE, CATEGORY_MAKEUP_EYE },
	{ TEXT("SDK_Lipstick_F_01"),	TEXT("lipstick_6453516b5abd84599e3b3d76"), EGender::FEMALE, CATEGORY_MAKEUP_LIP },
	{ TEXT("SDK_Lipstick_F_02"),	TEXT("lipstick_6458861e2a48eb54410d4c4e"), EGender::FEMALE, CATEGORY_MAKEUP_LIP },
	{ TEXT("SDK_Magicface_F_01"),	TEXT("magicface_645351745abd84599e3b3d77"), EGender::FEMALE, CATEGORY_MAKEUP_MAGIC_FACE },
	{ TEXT("SDK_Magicface_F_02"),	TEXT("magicface_6458862d2a48eb54410d4c4f"), EGender::FEMALE, CATEGORY_MAKEUP_MAGIC_FACE },
	{ TEXT("SDK_EyeIris_F_01"),		TEXT("pupil_6453517d5abd84599e3b3d78"), EGender::FEMALE, CATEGORY_MAKEUP_PUPIL },
	{ TEXT("SDK_EyeIris_F_02"),		TEXT("pupil_6458863f2a48eb54410d4c50"), EGender::FEMALE, CATEGORY_MAKEUP_PUPIL },
	{ TEXT("SDK_skintex_F_01"),		TEXT("skintex_6453518b5abd84599e3b3d79"), EGender::FEMALE, CATEGORY_MAKEUP_SKIN_TEXTURE },
	{ TEXT("SDK_skintex_F_02"),		TEXT("skintex_6455ebee5abd84599e3b3d88"), EGender::FEMALE, CATEGORY_MAKEUP_SKIN_TEXTURE },
	{ TEXT("SDK_Necklace_F_FC001"), TEXT("necklace_645351145abd84599e3b3d72"), EGender::FEMALE, CATEGORY_NECKLACE },
	{ TEXT("SDK_Necklace_F_FC002"), TEXT("necklace_645886832a48eb54410d4c51"), EGender::FEMALE, CATEGORY_NECKLACE },
	{ TEXT("SDK_Necklace_F_FC003"), TEXT("necklace_645886932a48eb54410d4c52"), EGender::FEMALE, CATEGORY_NECKLACE },
	{ TEXT("SDK_Shoes_F_FC003"),	TEXT("shoes_644b7e05b4473e4ba1d59567"), EGender::FEMALE, CATEGORY_SHOES },
	{ TEXT("SDK_Shoes_F_FC004"),	TEXT("shoes_6458ad882a48eb54410d4c6a"), EGender::FEMALE, CATEGORY_SHOES },
	{ TEXT("SDK_SkeAni_F_01"),		TEXT("skeani_64421d63c6745f0f67a92205"), EGender::FEMALE, CATEGORY_ANIMATION_BODY },
	{ TEXT("SDK_SkeAni_F_02"),		TEXT("skeani_645886bb2a48eb54410d4c53"), EGender::FEMALE, CATEGORY_ANIMATION_BODY },
	{ TEXT("SDK_Socks_F_FC001"),	TEXT("socks_6453512d5abd84599e3b3d73"), EGender::FEMALE, CATEGORY_SOCKS },
	{ TEXT("SDK_Socks_F_FC002"),	TEXT("socks_645886ed2a48eb54410d4c54"), EGender::FEMALE, CATEGORY_SOCKS },
	{ TEXT("SDK_Trouser_F_FC001"),	TEXT("trouser_6437d2829181074839341078"), EGender::FEMALE, CATEGORY_TROUSER },
	{ TEXT("SDK_Trouser_F_FC002"),	TEXT("trouser_645887202a48eb54410d4c55"), EGender::FEMALE, CATEGORY_TROUSER },
	{ TEXT("SDK_Trouser_F_neiyi"),	TEXT("trouser_6458ae112a48eb54410d4c6b"), EGender::FEMALE, CATEGORY_TROUSER },

	{ TEXT("SDK_Beard_M_01"),		TEXT("beard_6441229dc6745f0f67a92203"),  EGender::MALE, CATEGORY_BEARD },
	{ TEXT("SDK_Beard_M_02"),		TEXT("beard_645887312a48eb54410d4c56"),  EGender::MALE, CATEGORY_BEARD },
	{ TEXT("SDK_cloth_M_FC003"),	TEXT("cloth_644b79ceb4473e4ba1d5955f"),  EGender::MALE, CATEGORY_CLOTH },
	{ TEXT("SDK_cloth_M_FC004"),	TEXT("cloth_64588d072a48eb54410d4c66"),  EGender::MALE, CATEGORY_CLOTH },
	{ TEXT("SDK_Coverall_M_FC002"), TEXT("coverall_644b7b70b4473e4ba1d59564"),  EGender::MALE, CATEGORY_COVERALL },
	{ TEXT("SDK_Coverall_M_FC003"), TEXT("coverall_64588d392a48eb54410d4c67"),  EGender::MALE, CATEGORY_COVERALL },
	{ TEXT("SDK_Earring_M_FC001"),	TEXT("earring_645352345abd84599e3b3d7b"),  EGender::MALE, CATEGORY_EARRINGS },
	{ TEXT("SDK_Earring_M_FC002"),	TEXT("earring_645887872a48eb54410d4c57"),  EGender::MALE, CATEGORY_EARRINGS },
	{ TEXT("SDK_Eyebrows_M_01"),	TEXT("eyebrow_644b7ea7b4473e4ba1d59568"),  EGender::MALE, CATEGORY_EYEBROW },
	{ TEXT("SDK_Eyebrows_M_02"),	TEXT("eyebrow_645887962a48eb54410d4c58"),  EGender::MALE, CATEGORY_EYEBROW },
	{ TEXT("SDK_Glass_M_FC001"),	TEXT("glass_645882502a48eb54410d4c47"),  EGender::MALE, CATEGORY_GLASS },
	{ TEXT("SDK_Glass_M_FC002"),	TEXT("glass_645887b32a48eb54410d4c59"),  EGender::MALE, CATEGORY_GLASS },
	{ TEXT("SDK_Hair_M_FC01"),		TEXT("hair_644276a3f472c547bb215c2b"),  EGender::MALE, CATEGORY_HAIR },
	{ TEXT("SDK_Hat_M_FC001"),		TEXT("hat_645352215abd84599e3b3d7a"),  EGender::MALE, CATEGORY_HAT },
	{ TEXT("SDK_Hat_M_FC002"),		TEXT("hat_645887e12a48eb54410d4c5a"),  EGender::MALE, CATEGORY_HAT },
	{ TEXT("SDK_blusher_M_01"),		TEXT("blusher_645352835abd84599e3b3d7e"),  EGender::MALE, CATEGORY_MAKEUP_BLUSHER },
	{ TEXT("SDK_blusher_M_02"),		TEXT("blusher_645887f22a48eb54410d4c5b"),  EGender::MALE, CATEGORY_MAKEUP_BLUSHER },
	{ TEXT("SDK_eyemakeup_M_01"),	TEXT("eyemakeup_6453528c5abd84599e3b3d7f"),  EGender::MALE, CATEGORY_MAKEUP_EYE },
	{ TEXT("SDK_eyemakeup_M_02"),	TEXT("eyemakeup_645888062a48eb54410d4c5c"),  EGender::MALE, CATEGORY_MAKEUP_EYE },
	{ TEXT("SDK_Lipstick_M_01"),	TEXT("lipstick_645352975abd84599e3b3d80"),  EGender::MALE, CATEGORY_MAKEUP_LIP },
	{ TEXT("SDK_Lipstick_M_02"),	TEXT("lipstick_645888162a48eb54410d4c5d"),  EGender::MALE, CATEGORY_MAKEUP_LIP },
	{ TEXT("SDK_Magicface_M_01"),	TEXT("magicface_645352a05abd84599e3b3d81"),  EGender::MALE, CATEGORY_MAKEUP_MAGIC_FACE },
	{ TEXT("SDK_Magicface_M_02"),	TEXT("magicface_645888272a48eb54410d4c5e"),  EGender::MALE, CATEGORY_MAKEUP_MAGIC_FACE },
	{ TEXT("SDK_EyeIris_M_01"),		TEXT("pupil_645352aa5abd84599e3b3d82"),  EGender::MALE, CATEGORY_MAKEUP_PUPIL },
	{ TEXT("SDK_EyeIris_M_02"),		TEXT("pupil_645888372a48eb54410d4c5f"),  EGender::MALE, CATEGORY_MAKEUP_PUPIL },
	{ TEXT("SDK_skintex_M_01"),		TEXT("skintex_645352b95abd84599e3b3d83"),  EGender::MALE, CATEGORY_MAKEUP_SKIN_TEXTURE },
	{ TEXT("SDK_skintex_M_02"),		TEXT("skintex_6455ec285abd84599e3b3d89"),  EGender::MALE, CATEGORY_MAKEUP_SKIN_TEXTURE },
	{ TEXT("SDK_Mustache_M_01"),	TEXT("mustache_644121cac6745f0f67a92202"),  EGender::MALE, CATEGORY_MUSTACHE },
	{ TEXT("SDK_Mustache_M_02"),	TEXT("mustache_645888622a48eb54410d4c60"),  EGender::MALE, CATEGORY_MUSTACHE },
	{ TEXT("SDK_Necklace_M_FC001"), TEXT("necklace_645352455abd84599e3b3d7c"),  EGender::MALE, CATEGORY_NECKLACE },
	{ TEXT("SDK_Necklace_M_FC002"), TEXT("necklace_645888872a48eb54410d4c61"),  EGender::MALE, CATEGORY_NECKLACE },
	{ TEXT("SDK_Shoes_M_FC001"),	TEXT("shoes_64427afb43093f642a13d879"),  EGender::MALE, CATEGORY_SHOES },
	{ TEXT("SDK_Shoes_M_FC003"),	TEXT("shoes_645888ae2a48eb54410d4c62"),  EGender::MALE, CATEGORY_SHOES },
	{ TEXT("SDK_SkeAni_M_01"),		TEXT("skeani_64427654f472c547bb215c2a"),  EGender::MALE, CATEGORY_ANIMATION_BODY },
	{ TEXT("SDK_SkeAni_M_02"),		TEXT("skeani_645888bf2a48eb54410d4c63"),  EGender::MALE, CATEGORY_ANIMATION_BODY },
	{ TEXT("SDK_Socks_M_FC001"),	TEXT("socks_6453525b5abd84599e3b3d7d"),  EGender::MALE, CATEGORY_SOCKS },
	{ TEXT("SDK_Socks_M_FC002"),	TEXT("socks_645888e72a48eb54410d4c64"),  EGender::MALE, CATEGORY_SOCKS },
	{ TEXT("SDK_Trouser_M_FC003"),	TEXT("trouser_644b7dcbb4473e4ba1d59566"),  EGender::MALE, CATEGORY_TROUSER },
	{ TEXT("SDK_Trouser_M_FC004"),	TEXT("trouser_6458b02a2a48eb54410d4c6c"),  EGender::MALE, CATEGORY_TROUSER },
	{ TEXT("SDK_Trouser_M_neiyi"),	TEXT("trouser_6458b03e2a48eb54410d4c6d"),  EGender::MALE, CATEGORY_TROUSER },
};

#define NH_CREATE_CALLBACK(Func)\
	FNHCallback Callback;\
	UNHCallbackWrapper* CallbackWrapper = NewObject<UNHCallbackWrapper>(GetWorld());\
	Callbacks.Add(CallbackWrapper);\
	CallbackWrapper->SetCallback(Func);\
	Callback.BindUFunction(CallbackWrapper, TEXT("Run"));

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
	};

	// male assets
	static const TMap<FString, FString> MA{
		{CATEGORY_AVATAR, TEXT("avatar_64241b057f42de7d0775140c")},
		{CATEGORY_BODY, TEXT("body_642412df178b9538264e6a8d")},
	};


	if (!INextHumanSDKModule::Get().IsInitialized()) {
		INextHumanSDKModule::Get().Initialize(/* Put your access token here */ TempAccessToken,
			//TEXT("https://open-meta.tmall.com"), /* optional: custom server address ,*/
			[=](int32 Code, const FString& Message) {
				if (Code == INextHumanSDKModule::CODE_SUCCESS) {
					//LoadAvatar(FA, FVector(50, 0, 0), FRotator(0, 0, 0));
					//LoadAvatar(MA, FVector(-50, 0, 0), FRotator(0, 0, 0));

					Load(FA[CATEGORY_AVATAR], FindAssets(EGender::FEMALE, 0), FVector(50 * 1, -50, 0), FRotator(0, 0, 0));
					Load(FA[CATEGORY_AVATAR], FindAssets(EGender::FEMALE, 1), FVector(50 * 2, -50, 0), FRotator(0, 0, 0));
					Load(FA[CATEGORY_AVATAR], FindAssets(EGender::FEMALE, 2), FVector(50 * 3, -50, 0), FRotator(0, 0, 0));

					Load(MA[CATEGORY_AVATAR], FindAssets(EGender::MALE, 0), FVector(-50 * 1, -50, 0), FRotator(0, 0, 0));
					Load(MA[CATEGORY_AVATAR], FindAssets(EGender::MALE, 1), FVector(-50 * 2, -50, 0), FRotator(0, 0, 0));
					Load(MA[CATEGORY_AVATAR], FindAssets(EGender::MALE, 2), FVector(-50 * 3, -50, 0), FRotator(0, 0, 0));

					TArray<FAsset> FemaleCoverall = ASSETS.FilterByPredicate([](const FAsset& Item) {
						return Item.Category == CATEGORY_COVERALL && Item.Gender == EGender::FEMALE;
					});
					int32 Index = 3;
					for (auto& Coverall : FemaleCoverall) {
						Load(FA[CATEGORY_AVATAR], { Coverall }, FVector(50 * (Index++ + 1), -50, 0), FRotator(0, 0, 0));
					}

					TArray<FAsset> MaleCoverall = ASSETS.FilterByPredicate([](const FAsset& Item) {
						return Item.Category == CATEGORY_COVERALL && Item.Gender == EGender::MALE;
					});
					Index = 3;
					for (auto& Coverall : MaleCoverall) {
						Load(MA[CATEGORY_AVATAR], { Coverall }, FVector(-50 * (Index++ + 1), -50, 0), FRotator(0, 0, 0));
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


void AAvatarLoader::LoadAvatar(const TMap<FString, FString>& Assets, const FVector& Position, const FRotator& Rotation) {
	UWorld* World = GetWorld();
	if (!World) {
		return;
	}

	auto Avatar = World->SpawnActor<ANextAvatar>(Position, Rotation);
	if (!Avatar) {
		return;
	}

	INextHumanSDKModule& SDK = INextHumanSDKModule::Get();

	FTaskChain& Tasks = FTaskChain::Create(ENamedThreads::AnyNormalThreadNormalTask, [=](const FTestRet& Last, FTaskChain::FOnStepEnd OnStepEnd) {
		OnStepEnd(FTestRet{});
	});

	// Cache resource
	//for (auto& Pair : Assets) {
	//	Tasks.AndThen(ENamedThreads::AnyNormalThreadNormalTask, [=, &SDK](const FTestRet& Last, FTaskChain::FOnStepEnd OnStepEnd) {
	//		SDK.PrepareResource(Pair.Value, [=](int32 Code, const FString& Message) {
	//			OnStepEnd(FTestRet{ Code, Message });
	//		});
	//	});
	//}

	Tasks.AndThen(ENamedThreads::AnyNormalThreadNormalTask, [=, &SDK](const FTestRet& Last, FTaskChain::FOnStepEnd OnStepEnd) {
		SDK.PrepareResource(Assets[CATEGORY_BODY], [=](int32 Code, const FString& Message) {
			OnStepEnd(FTestRet{ Code, Message });
		});
	});

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

			UNHCallbackWrapper* Callback = NewObject<UNHCallbackWrapper>(GetWorld());
		});
	});

	//AddBodyBundle(Tasks, Avatar, CATEGORY_COVERALL, Assets[CATEGORY_COVERALL]);
	//Delay(Tasks, 3);
	//RemoveBodyBundle(Tasks, Avatar, CATEGORY_COVERALL);
	//Delay(Tasks, 3);

	AddBodyBundle(Tasks, Avatar, CATEGORY_CLOTH, Assets[CATEGORY_CLOTH]);
	AddBodyBundle(Tasks, Avatar, CATEGORY_TROUSER, Assets[CATEGORY_TROUSER]);
	AddBodyBundle(Tasks, Avatar, CATEGORY_SHOES, Assets[CATEGORY_SHOES]);
	AddBodyBundle(Tasks, Avatar, CATEGORY_SOCKS, Assets[CATEGORY_SOCKS]);
	AddFaceBundle(Tasks, Avatar, CATEGORY_HAIR, Assets[CATEGORY_HAIR], [=](int64) {
		const FString Category = CATEGORY_HAIR;		// 毛发类型
		FGroomMaterialParam Param;					// 对应资产的材质球支持的修改参数
		Param.Color = FLinearColor::Yellow; // 将当前头发的颜色改为黑色
		Avatar->GetBody()->GetFace()->ChangeGroomMaterialParam(Category, Param);
	});
	AddFaceBundle(Tasks, Avatar, CATEGORY_HAT, Assets[CATEGORY_HAT]);
	AddFaceBundle(Tasks, Avatar, CATEGORY_EARRINGS, Assets[CATEGORY_EARRINGS]);
	AddFaceBundle(Tasks, Avatar, CATEGORY_MAKEUP_BLUSHER, Assets[CATEGORY_MAKEUP_BLUSHER]);
	AddFaceBundle(Tasks, Avatar, CATEGORY_MAKEUP_EYE, Assets[CATEGORY_MAKEUP_EYE]);
	AddFaceBundle(Tasks, Avatar, CATEGORY_MAKEUP_LIP, Assets[CATEGORY_MAKEUP_LIP]);
	AddFaceBundle(Tasks, Avatar, CATEGORY_MAKEUP_MAGIC_FACE, Assets[CATEGORY_MAKEUP_MAGIC_FACE]);
	AddFaceBundle(Tasks, Avatar, CATEGORY_MAKEUP_PUPIL, Assets[CATEGORY_MAKEUP_PUPIL]);
	AddFaceBundle(Tasks, Avatar, CATEGORY_MAKEUP_SKIN_TEXTURE, Assets[CATEGORY_MAKEUP_SKIN_TEXTURE]);

	//RemoveBodyBundle(Tasks, Avatar, CATEGORY_CLOTH);
	//RemoveBodyBundle(Tasks, Avatar, CATEGORY_TROUSER);
	//RemoveBodyBundle(Tasks, Avatar, CATEGORY_SHOES);
	//RemoveBodyBundle(Tasks, Avatar, CATEGORY_SOCKS);
	//RemoveFaceBundle(Tasks, Avatar, CATEGORY_HAIR);
	//RemoveFaceBundle(Tasks, Avatar, CATEGORY_HAT);
	//RemoveFaceBundle(Tasks, Avatar, CATEGORY_EARRINGS);
	//RemoveFaceBundle(Tasks, Avatar, CATEGORY_MAKEUP_BLUSHER);
	//RemoveFaceBundle(Tasks, Avatar, CATEGORY_MAKEUP_EYE);
	//RemoveFaceBundle(Tasks, Avatar, CATEGORY_MAKEUP_LIP);
	//RemoveFaceBundle(Tasks, Avatar, CATEGORY_MAKEUP_MAGIC_FACE);
	//RemoveFaceBundle(Tasks, Avatar, CATEGORY_MAKEUP_PUPIL);
	//RemoveFaceBundle(Tasks, Avatar, CATEGORY_MAKEUP_SKIN_TEXTURE);

	Tasks.AndThen(ENamedThreads::AnyNormalThreadNormalTask, [=](const FTestRet& Last, FTaskChain::FOnStepEnd OnStepEnd) {
		auto Cb = [=](int32 Code, const FString& Message, int64 Index) {
			UE_LOG(LogTemp, Warning, TEXT("set anim to body %d, %s, %d"), Code, *Message, Index);
			OnStepEnd(FTestRet{ Code, Message });
		};
		NH_CREATE_CALLBACK(Cb);
		Avatar->GetBody()->SetAnim(Assets[CATEGORY_ANIMATION_BODY], Callback);
	});

	Tasks.AndThen(ENamedThreads::AnyNormalThreadNormalTask, [=](const FTestRet& Last, FTaskChain::FOnStepEnd OnStepEnd) {
		auto Cb = [=](int32 Code, const FString& Message, int64 Index) {
			UE_LOG(LogTemp, Warning, TEXT("set anim to face %d, %s, %d"), Code, *Message, Index);
			OnStepEnd(FTestRet{ Code, Message });
		};
		NH_CREATE_CALLBACK(Cb);
		Avatar->GetBody()->GetFace()->SetAnim(Assets[CATEGORY_ANIMATION_FACE], Callback);
	});

	Tasks.Start([=](const FTestRet& Last) {
		UE_LOG(LogTemp, Warning, TEXT("==>> End %d %s"), Last.Code, *Last.Message);
	});
}

void AAvatarLoader::AddFaceBundle(FTaskChain& Chain, ANextAvatar* Avatar, const FString& Key, const FString& Id, TFunction<void(int64)> OnComplete) {
	Chain.AndThen(ENamedThreads::AnyNormalThreadNormalTask, [=](const FTestRet& Last, FTaskChain::FOnStepEnd OnStepEnd) {
		auto Cb = [=](int32 Code, const FString& Message, int64 Index) {
			UE_LOG(LogTemp, Warning, TEXT("Add %s to face %d, %s, %d"), *Key, Code, *Message, Index);
			if (Code == 0) {
				IndexMap.Add(Key, Index);
			}
			OnComplete(Index);
			OnStepEnd(FTestRet{ Code, Message });
		};
		NH_CREATE_CALLBACK(Cb);
		Avatar->GetBody()->GetFace()->AddBundle(Id, Callback);
	});
}

void AAvatarLoader::AddBodyBundle(FTaskChain& Chain, ANextAvatar* Avatar, const FString& Key, const FString& Id, TFunction<void(int64)> OnComplete) {
	Chain.AndThen(ENamedThreads::AnyNormalThreadNormalTask, [=](const FTestRet& Last, FTaskChain::FOnStepEnd OnStepEnd) {
		auto Cb = [=](int32 Code, const FString& Message, int64 Index) {
			UE_LOG(LogTemp, Warning, TEXT("Add %s to body %d, %s, %d"), *Key, Code, *Message, Index);
			if (Code == 0) {
				IndexMap.Add(Key, Index);
			}
			OnComplete(Index);
			OnStepEnd(FTestRet{ Code, Message });
		};
		NH_CREATE_CALLBACK(Cb);
		Avatar->GetBody()->AddBundle(Id, Callback);
	});
}

void AAvatarLoader::RemoveBodyBundle(FTaskChain& Chain, ANextAvatar* Avatar, const FString& Key) {
	Chain.AndThen(ENamedThreads::GameThread, [=](const FTestRet& Last, FTaskChain::FOnStepEnd OnStepEnd) {
		if (IndexMap.Contains(Key)) {
			Avatar->GetBody()->RemoveBundle(IndexMap[Key]);
			IndexMap.Remove(Key);
			OnStepEnd(FTestRet{ 0, TEXT("") });
		}
		else {
			OnStepEnd(FTestRet{ -1, FString::Printf(TEXT("Key not found %s"), *Key) });
		}
	});
}

void AAvatarLoader::RemoveFaceBundle(FTaskChain& Chain, ANextAvatar* Avatar, const FString& Key) {
	Chain.AndThen(ENamedThreads::GameThread, [=](const FTestRet& Last, FTaskChain::FOnStepEnd OnStepEnd) {
		if (IndexMap.Contains(Key)) {
			Avatar->GetBody()->GetFace()->RemoveBundle(IndexMap[Key]);
			IndexMap.Remove(Key);
			OnStepEnd(FTestRet{ 0, TEXT("") });
		}
		else {
			OnStepEnd(FTestRet{ -1, FString::Printf(TEXT("Key not found %s"), *Key) });
		}
	});
}

void AAvatarLoader::Delay(FTaskChain& Chain, float Seconds) {
	Chain.AndThen(ENamedThreads::GameThread, [=](const FTestRet& Last, FTaskChain::FOnStepEnd OnStepEnd) {
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, [=]() {
			OnStepEnd(FTestRet{ 0, TEXT("") });
		}, Seconds, false);
	});
}

void AAvatarLoader::Load(FString AvatarId, TArray<FAsset> Assets, const FVector& Position, const FRotator& Rotation) {
	UWorld* World = GetWorld();
	if (!World) {
		return;
	}

	auto Avatar = World->SpawnActor<ANextAvatar>(Position, Rotation);
	if (!Avatar) {
		return;
	}

	UE_LOG(LogTemp, Display, TEXT("%s[%p]: %s"), ANSI_TO_TCHAR(__FUNCTION__), Avatar, *AvatarId);
	for (auto& Asset : Assets) {
		UE_LOG(LogTemp, Display, TEXT("%s[%p]: %s %s"), ANSI_TO_TCHAR(__FUNCTION__), Avatar, *Asset.Id, *Asset.Name);
	}

	INextHumanSDKModule& SDK = INextHumanSDKModule::Get();

	FTaskChain& Tasks = FTaskChain::Create(ENamedThreads::AnyNormalThreadNormalTask, [=](const FTestRet& Last, FTaskChain::FOnStepEnd OnStepEnd) {
		OnStepEnd(FTestRet{});
	});
	Tasks.AndThen(ENamedThreads::AnyNormalThreadNormalTask, [=](const FTestRet& Last, FTaskChain::FOnStepEnd OnStepEnd) {
		Avatar->SetAvatarId(AvatarId, [=](int32 Code, const FString& Message, int64 Id) {
			OnStepEnd(FTestRet{ Code, Message });
		});
	});

	TArray<FString> FaceCategoryList{
		CATEGORY_HAT,
		CATEGORY_GLASS,
		CATEGORY_EARRINGS,
		CATEGORY_HAIR,
		CATEGORY_EYEBROW,
		CATEGORY_EYELASH,
		CATEGORY_MUSTACHE,
		CATEGORY_BEARD,
		CATEGORY_MAKEUP_BLUSHER,
		CATEGORY_MAKEUP_EYE,
		CATEGORY_MAKEUP_LIP,
		CATEGORY_MAKEUP_MAGIC_FACE,
		CATEGORY_MAKEUP_PUPIL,
		CATEGORY_MAKEUP_SKIN_TEXTURE,
	};
	TArray<FString> BodyCategoyList{
		CATEGORY_COVERALL,
		CATEGORY_CLOTH,
		CATEGORY_TROUSER,
		CATEGORY_SHOES,
		CATEGORY_NECKLACE,
		CATEGORY_GLOVES,
		CATEGORY_SOCKS,
	};

	for (auto& Asset : Assets) {
		if (FaceCategoryList.Contains(Asset.Category)) {
			AddFaceBundle(Tasks, Avatar, Asset.Name, Asset.Id);
		}
		if (BodyCategoyList.Contains(Asset.Category)) {
			AddBodyBundle(Tasks, Avatar, Asset.Name, Asset.Id);
		}
		if (Asset.Category == CATEGORY_ANIMATION_BODY) {
			Tasks.AndThen(ENamedThreads::AnyNormalThreadNormalTask, [=](const FTestRet& Last, FTaskChain::FOnStepEnd OnStepEnd) {
				auto Cb = [=](int32 Code, const FString& Message, int64 Index) {
					UE_LOG(LogTemp, Warning, TEXT("set anim to body %d, %s, %d"), Code, *Message, Index);
					OnStepEnd(FTestRet{ Code, Message });
				};
				NH_CREATE_CALLBACK(Cb);
				Avatar->GetBody()->SetAnim(Asset.Id, Callback);
			});
		}
	}
	Tasks.Start([=](const FTestRet& Last) {

	});
}

TArray<AAvatarLoader::FAsset> AAvatarLoader::FindAssets(EGender Gender, int32 InIndex) {
	static const TArray<FString> CategoryList{
		//CATEGORY_COVERALL,
		CATEGORY_CLOTH, CATEGORY_TROUSER, CATEGORY_SOCKS, CATEGORY_SHOES, CATEGORY_HAIR, CATEGORY_HAT, CATEGORY_EARRINGS, CATEGORY_HAT, CATEGORY_NECKLACE,
		CATEGORY_GLASS, CATEGORY_MUSTACHE, CATEGORY_BEARD,
		CATEGORY_MAKEUP_BLUSHER, CATEGORY_MAKEUP_EYE, CATEGORY_MAKEUP_LIP, CATEGORY_MAKEUP_MAGIC_FACE, CATEGORY_MAKEUP_PUPIL, CATEGORY_MAKEUP_SKIN_TEXTURE,
		CATEGORY_ANIMATION_BODY,
	};

	int32 FemaleMax = 0;
	int32 MaleMax = 0;
	for (auto& Category : CategoryList) {
		int32 FemaleCount = 0;
		int32 MaleCount = 0;
		for (auto& Asset : ASSETS) {
			if (Category == Asset.Category && Asset.Gender == EGender::FEMALE) {
				FemaleCount++;
			}
		}
		//UE_LOG(LogTemp, Display, TEXT("FEMALE[%s]=%d"), *Category, FemaleCount);
		if (FemaleCount > FemaleMax) {
			FemaleMax = FemaleCount;
		}

		for (auto& Asset : ASSETS) {
			if (Category == Asset.Category && Asset.Gender == EGender::MALE) {
				MaleCount++;
			}
		}
		//UE_LOG(LogTemp, Display, TEXT("MALE[%s]=%d"), *Category, MaleCount);
		if (MaleCount > MaleMax) {
			MaleMax = MaleCount;
		}
	}

	TMap<EGender, int32> GenderMaxMap{
		{ EGender::FEMALE, FemaleMax },
		{ EGender::MALE, MaleMax },
	};

	TArray<FAsset> AssetGroup;
	for (auto& Category : CategoryList) {
		int32 Index = 0;
		for (auto& Asset : ASSETS) {
			if (Category == Asset.Category && Asset.Gender == Gender) {
				if (Index == InIndex) {
					AssetGroup.Add(Asset);
					break;
				}
				Index++;
			}
		}
	}
	return AssetGroup;
}