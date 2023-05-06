// Fill out your copyright notice in the Description page of Project Settings.


#include "AvatarLoader.h"
#include "INextHumanSDK.h"
#include "NHCategory.h"
#include "NHCallbackWrapper.h"

using namespace nexthuman::sdk;

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
	const FString SDK_Coverall_F_FC001 = TEXT("SDK_Coverall_F_FC001");
	const FString SDK_Coverall_F_FC002 = TEXT("SDK_Coverall_F_FC002");
	const FString SDK_Coverall_F_FC003 = TEXT("SDK_Coverall_F_FC003");
	const FString SDK_Coverall_M_FC001 = TEXT("SDK_Coverall_M_FC001");
	const FString SDK_Coverall_M_FC002 = TEXT("SDK_Coverall_M_FC002");
	const FString SDK_skintex_F_01 = TEXT("SDK_skintex_F_01");
	const FString SDK_skintex_F_02 = TEXT("SDK_skintex_F_02");

	// female assets
	static const TMap<FString, FString> FA{
		{CATEGORY_AVATAR, TEXT("avatar_64241b207f42de7d0775140d")},
		{CATEGORY_BODY, TEXT("body_642413f6178b9538264e6a8e")},

		{SDK_Coverall_F_FC001, TEXT("coverall_64312f6f10809e0df45537a7")}, //
		{SDK_Coverall_F_FC002, TEXT("coverall_644b7b02b4473e4ba1d59563")},
		{SDK_Coverall_F_FC003, TEXT("coverall_64350e7f05a0d40a4d6f5d28")}, // json有问题
		{CATEGORY_COVERALL, TEXT("coverall_644b7b02b4473e4ba1d59563")},

		{CATEGORY_CLOTH, TEXT("cloth_6437c90d9181074839341076")}, //
		{CATEGORY_SHOES, TEXT("shoes_6437d1b39181074839341077")}, //
		{CATEGORY_TROUSER, TEXT("trouser_6437d2829181074839341078")}, //
		{CATEGORY_EARRINGS, TEXT("earring_645350fb5abd84599e3b3d71")}, //
		{CATEGORY_HAT, TEXT("hat_645350e95abd84599e3b3d70")}, //
		{CATEGORY_SOCKS, TEXT("socks_6453512d5abd84599e3b3d73")}, //

		{CATEGORY_HAIR, TEXT("hair_643cb3f3d46ccd6078f72385")}, // 材质有问题
		{CATEGORY_EYEBROW, TEXT("eyebrow_643cb7b016938c6c359608f2")}, // 需要更新
		{CATEGORY_EYELASH, TEXT("eyelash_643cdab716938c6c359608f3")}, //

		{CATEGORY_ANIMATION_BODY, TEXT("skeani_64421d63c6745f0f67a92205")}, //
		{CATEGORY_ANIMATION_FACE, TEXT("faceani_6442437ec6745f0f67a92207")}, //

		{CATEGORY_MAKEUP_BLUSHER, TEXT("blusher_645351575abd84599e3b3d74")}, // Mask.uasset不能加载，原始资产名称不对
		{CATEGORY_MAKEUP_EYE, TEXT("eyemakeup_645351605abd84599e3b3d75")}, // Mask.uasset不能加载，原始资产名称不对
		{CATEGORY_MAKEUP_LIP, TEXT("lipstick_6453516b5abd84599e3b3d76")},
		{CATEGORY_MAKEUP_MAGIC_FACE, TEXT("magicface_645351745abd84599e3b3d77")},
		{CATEGORY_MAKEUP_PUPIL, TEXT("pupil_6453517d5abd84599e3b3d78")}, // Mask.uasset不能加载，原始资产名称不对

		{SDK_skintex_F_01, TEXT("skintex_6453518b5abd84599e3b3d79")},
		{SDK_skintex_F_02, TEXT("skintex_6455ebee5abd84599e3b3d88")},
		{CATEGORY_MAKEUP_SKIN_TEXTURE, TEXT("skintex_6453518b5abd84599e3b3d79")}, // 
	};

	// male assets
	static const TMap<FString, FString> MA{
		{CATEGORY_AVATAR, TEXT("avatar_64241b057f42de7d0775140c")},
		{CATEGORY_BODY, TEXT("body_642412df178b9538264e6a8d")},

		{SDK_Coverall_M_FC001, TEXT("coverall_6434feb205a0d40a4d6f5d27")},
		{SDK_Coverall_M_FC002, TEXT("coverall_644b7b70b4473e4ba1d59564")},
		{CATEGORY_COVERALL, TEXT("coverall_6434feb205a0d40a4d6f5d27")},

		{CATEGORY_CLOTH, TEXT("cloth_64427ab843093f642a13d877")},
		{CATEGORY_SHOES, TEXT("shoes_64427afb43093f642a13d879")},
		{CATEGORY_TROUSER, TEXT("trouser_64427adc43093f642a13d878")},
		{CATEGORY_EARRINGS, TEXT("earring_645352345abd84599e3b3d7b")},
		{CATEGORY_HAT, TEXT("hat_645350e95abd84599e3b3d70")},
		{CATEGORY_SOCKS, TEXT("socks_6453525b5abd84599e3b3d7d")},

		{CATEGORY_HAIR, TEXT("hair_644276a3f472c547bb215c2b")},
		{CATEGORY_EYEBROW, TEXT("eyebrow_644b7ea7b4473e4ba1d59568")},
		{CATEGORY_EYELASH, TEXT("eyelash_644276fc43093f642a13d876")},
		{CATEGORY_BEARD, TEXT("beard_6441229dc6745f0f67a92203")},
		{CATEGORY_MUSTACHE, TEXT("mustache_644121cac6745f0f67a92202")},

		{CATEGORY_ANIMATION_BODY, TEXT("skeani_64427654f472c547bb215c2a")},
		{CATEGORY_ANIMATION_FACE, TEXT("faceani_644243a2886e096bfce937fb")},

		{CATEGORY_MAKEUP_BLUSHER, TEXT("blusher_645352835abd84599e3b3d7e")},
		{CATEGORY_MAKEUP_EYE, TEXT("eyemakeup_6453528c5abd84599e3b3d7f")},
		{CATEGORY_MAKEUP_LIP, TEXT("lipstick_645352975abd84599e3b3d80")},
		{CATEGORY_MAKEUP_MAGIC_FACE, TEXT("magicface_645352a05abd84599e3b3d81")},
		{CATEGORY_MAKEUP_PUPIL, TEXT("pupil_645352aa5abd84599e3b3d82")},
		{CATEGORY_MAKEUP_SKIN_TEXTURE, TEXT("skintex_645352b95abd84599e3b3d83")},
	};

	if (!INextHumanSDKModule::Get().IsInitialized()) {
		INextHumanSDKModule::Get().Initialize(/* Put your access token here */ TempAccessToken, /* optional: custom server address ,*/ [=](int32 Code, const FString& Message)
		{
			if (Code == INextHumanSDKModule::CODE_SUCCESS) {
				LoadAvatar(FA, FVector(50, 0, 0), FRotator(0, 0, 0));
				//LoadAvatar(MA, FVector(-50, 0, 0), FRotator(0, 0, 0));
			}
		});
	}
	else {
		LoadAvatar(FA, FVector(50, 0, 0), FRotator(0, 0, 0));
		//LoadAvatar(MA, FVector(-50, 0, 0), FRotator(0, 0, 0));
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

	AddBodyBundle(Tasks, Avatar, CATEGORY_COVERALL, Assets[CATEGORY_COVERALL]);
	Delay(Tasks, 3);
	RemoveBodyBundle(Tasks, Avatar, CATEGORY_COVERALL);
	Delay(Tasks, 3);


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
	//AddFaceBundle(Tasks, Avatar, CATEGORY_MAKEUP_BLUSHER, Assets[CATEGORY_MAKEUP_BLUSHER]);
	//AddFaceBundle(Tasks, Avatar, CATEGORY_MAKEUP_EYE, Assets[CATEGORY_MAKEUP_EYE]);
	AddFaceBundle(Tasks, Avatar, CATEGORY_MAKEUP_LIP, Assets[CATEGORY_MAKEUP_LIP]);
	AddFaceBundle(Tasks, Avatar, CATEGORY_MAKEUP_MAGIC_FACE, Assets[CATEGORY_MAKEUP_MAGIC_FACE]);
	//AddFaceBundle(Tasks, Avatar, CATEGORY_MAKEUP_PUPIL, Assets[CATEGORY_MAKEUP_PUPIL]);
	AddFaceBundle(Tasks, Avatar, CATEGORY_MAKEUP_SKIN_TEXTURE, Assets[CATEGORY_MAKEUP_SKIN_TEXTURE]);

	Delay(Tasks, 5);

	RemoveBodyBundle(Tasks, Avatar, CATEGORY_CLOTH);
	RemoveBodyBundle(Tasks, Avatar, CATEGORY_TROUSER);
	RemoveBodyBundle(Tasks, Avatar, CATEGORY_SHOES);
	RemoveBodyBundle(Tasks, Avatar, CATEGORY_SOCKS);
	RemoveFaceBundle(Tasks, Avatar, CATEGORY_HAIR);
	RemoveFaceBundle(Tasks, Avatar, CATEGORY_HAT);
	RemoveFaceBundle(Tasks, Avatar, CATEGORY_EARRINGS);
	//RemoveFaceBundle(Tasks, Avatar, CATEGORY_MAKEUP_BLUSHER);
	//RemoveFaceBundle(Tasks, Avatar, CATEGORY_MAKEUP_EYE);
	RemoveFaceBundle(Tasks, Avatar, CATEGORY_MAKEUP_LIP);
	RemoveFaceBundle(Tasks, Avatar, CATEGORY_MAKEUP_MAGIC_FACE);
	//RemoveFaceBundle(Tasks, Avatar, CATEGORY_MAKEUP_PUPIL);
	RemoveFaceBundle(Tasks, Avatar, CATEGORY_MAKEUP_SKIN_TEXTURE);


	Delay(Tasks, 3);

	//AddBodyBundle(Tasks, Avatar, CATEGORY_CLOTH, Assets[CATEGORY_CLOTH]);
	//AddBodyBundle(Tasks, Avatar, CATEGORY_TROUSER, Assets[CATEGORY_TROUSER]);
	//AddBodyBundle(Tasks, Avatar, CATEGORY_SHOES, Assets[CATEGORY_SHOES]);
	//AddBodyBundle(Tasks, Avatar, CATEGORY_SOCKS, Assets[CATEGORY_SOCKS]);
	//AddFaceBundle(Tasks, Avatar, CATEGORY_HAIR, Assets[CATEGORY_HAIR]);
	//AddFaceBundle(Tasks, Avatar, CATEGORY_HAT, Assets[CATEGORY_HAT]);
	//AddFaceBundle(Tasks, Avatar, CATEGORY_EARRINGS, Assets[CATEGORY_EARRINGS]);

	//int64 EyelashIndex = -1;
	//AddFaceBundle(Tasks, Avatar, CATEGORY_EYELASH, Assets[CATEGORY_EYELASH], [=, &EyelashIndex](int64 Index) {
	//	EyelashIndex = Index;
	//});

	//int64 EarringIndex = -1;
	//AddFaceBundle(Tasks, Avatar, CATEGORY_EARRINGS, Assets[CATEGORY_EARRINGS], [=, &EarringIndex](int64 Index) {
	//	EarringIndex = Index;
	//});

	//int64 HatIndex = -1;
	//AddFaceBundle(Tasks, Avatar, CATEGORY_HAT, Assets[CATEGORY_HAT], [=, &HatIndex](int64 Index) {
	//	HatIndex = Index;
	//});

	// Mask.uasset 名称对不上
	//int64 MakeupBlusherIndex = -1;
	//AddFaceBundle(Tasks, Avatar, CATEGORY_MAKEUP_BLUSHER, Assets[CATEGORY_MAKEUP_BLUSHER], [=, &MakeupBlusherIndex](int64 Index) {
	//	MakeupBlusherIndex = Index;
	//});

	// 不能用
	//int64 EyeBrowIndex = -1;
	//AddFaceBundle(Tasks, Avatar, CATEGORY_EYEBROW, Assets[CATEGORY_EYEBROW], [=, &EyeBrowIndex](int64 Index) {
	//	EyeBrowIndex = Index;
	//});

	//Tasks.AndThen(ENamedThreads::AnyNormalThreadNormalTask, [=](const FTestRet& Last, FTaskChain::FOnStepEnd OnStepEnd) {
	//	auto Cb = [=](int32 Code, const FString& Message, int64 Index) {
	//		UE_LOG(LogTemp, Warning, TEXT("set anim to body %d, %s, %d"), Code, *Message, Index);
	//		OnStepEnd(FTestRet{ Code, Message });
	//	};
	//	NH_CREATE_CALLBACK(Cb);
	//	Avatar->GetBody()->SetAnim(Assets[CATEGORY_ANIMATION_BODY], Callback);
	//});

	//Tasks.AndThen(ENamedThreads::AnyNormalThreadNormalTask, [=](const FTestRet& Last, FTaskChain::FOnStepEnd OnStepEnd) {
	//	auto Cb = [=](int32 Code, const FString& Message, int64 Index) {
	//		UE_LOG(LogTemp, Warning, TEXT("set anim to face %d, %s, %d"), Code, *Message, Index);
	//		OnStepEnd(FTestRet{ Code, Message });
	//	};
	//	NH_CREATE_CALLBACK(Cb);
	//	Avatar->GetBody()->GetFace()->SetAnim(Assets[CATEGORY_ANIMATION_FACE], Callback);
	//});

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