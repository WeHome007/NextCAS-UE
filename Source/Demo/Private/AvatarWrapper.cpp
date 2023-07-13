#include "AvatarWrapper.h"
#include "AvatarLoader.h"
#include "INextHumanSDK.h"
#include "NextAvatar.h"
#include "NHCommon.h"
#include "NHCallbackWrapper.h"

#include "HAL/ThreadManager.h"

using namespace nexthuman::sdk::demo;

const TArray<FString> FAvatarWrapper::FaceCategoryList{
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

const TArray<FString> FAvatarWrapper::BodyCategoyList{
		CATEGORY_COVERALL,
		CATEGORY_CLOTH,
		CATEGORY_TROUSER,
		CATEGORY_SHOES,
		CATEGORY_NECKLACE,
		CATEGORY_GLOVES,
		CATEGORY_SOCKS,
};

FAvatarWrapper::FAvatarWrapper(AAvatarLoader& InAvatarLoader, FTestTaskChain& InTasks, const FString& InAvatarId, TArray<FAsset> InAssets, const FVector& InPosition, const FRotator& InRotation)
	: AvatarLoader(InAvatarLoader), Tasks(InTasks), AvatarId(InAvatarId), Assets(InAssets), Position(InPosition), Rotation(InRotation)
{
}

FAvatarWrapper::~FAvatarWrapper() {
	uint32 ThreadId = FPlatformTLS::GetCurrentThreadId();
	FString Name = FThreadManager::Get().GetThreadName(ThreadId);

	UE_LOG(LogTemp, Warning, TEXT("==>> %s: %s %p %d %s"), ANSI_TO_TCHAR(__FUNCTION__), *AvatarId, this, ThreadId, *Name);
	FDebug::DumpStackTraceToLog(ELogVerbosity::Warning);
}

void FAvatarWrapper::Wear(ANextAvatar* Avatar, FTestTaskChain& Chain) {
	for (auto& Asset : Assets) {
		if (FaceCategoryList.Contains(Asset.Category)) {
			//AddFaceBundle(Tasks, Avatar, Asset.Name, Asset.Id);
			AddBundle(Tasks, Avatar, Asset.Name, Asset.Id, [=](int64) {
				UE_LOG(LogTemp, Warning, TEXT("FAvatarWrapper::Wear1 %s"), ANSI_TO_TCHAR(__FUNCTION__));
			});
		}
		if (BodyCategoyList.Contains(Asset.Category)) {
			//AddBodyBundle(Tasks, Avatar, Asset.Name, Asset.Id);
			AddBundle(Tasks, Avatar, Asset.Name, Asset.Id, [=](int64) {
				UE_LOG(LogTemp, Warning, TEXT("FAvatarWrapper::Wear2 %s"), ANSI_TO_TCHAR(__FUNCTION__));
			});
		}
		if (Asset.Category == CATEGORY_ANIMATION_BODY) {
			Tasks.AndThen(ENamedThreads::GameThread, [=](const FTestRet& Last, FTestTaskChain::FOnStepEnd OnStepEnd) {
				auto Cb = [=](int32 Code, const FString& Message, int64 Index) {
					UE_LOG(LogTemp, Warning, TEXT("set anim to body %d, %s, %d"), Code, *Message, Index);
					OnStepEnd(FTestRet{ Code, Message });
				};
				Avatar->GetBody()->SetAnim(Asset.Id, Cb);
				FString Temp = TEXT("IndexMap =>\n");
				for (auto& KV : IndexMap) {
					Temp.Appendf(TEXT("\t%s %d\n"), *KV.Key, KV.Value);
				}
				UE_LOG(LogTemp, Display, TEXT("%s"), *Temp);
			});
		}
	}
}

void FAvatarWrapper::Takeoff(ANextAvatar* Avatar, FTestTaskChain& Chain) {
	for (auto& Asset : Assets) {
		if (FaceCategoryList.Contains(Asset.Category)) {
			//RemoveFaceBundle(Tasks, Avatar, Asset.Name);
			RemoveBundle(Tasks, Avatar, Asset.Name);
		}
		if (BodyCategoyList.Contains(Asset.Category)) {
			//RemoveBodyBundle(Tasks, Avatar, Asset.Name);
			RemoveBundle(Tasks, Avatar, Asset.Name);
		}
	}
}

void FAvatarWrapper::Dummy() {
	UE_LOG(LogTemp, Display, TEXT("%s"), ANSI_TO_TCHAR(__FUNCTION__));
}

void FAvatarWrapper::Load() {
	UWorld* World = AvatarLoader.GetWorld();
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

	FString TempId = AvatarId;
	Tasks.AndThen(ENamedThreads::AnyNormalThreadNormalTask, [Avatar, TempId](const FTestRet& Last, FTestTaskChain::FOnStepEnd OnStepEnd) {
		Avatar->SetAvatarId(TempId, [Avatar, OnStepEnd](int32 Code, const FString& Message, TMap<FString, ANextAvatar::FBundleInfo> BundleInfos) {
			OnStepEnd(FTestRet{ Code, Message });
			TArray<UActorComponent*> Bodys = Avatar->GetComponentsByTag(UActorComponent::StaticClass(), TEXT("Body"));
			UE_LOG(LogTemp, Warning, TEXT("Bodys Num %d LoadedBundle Num %d"), Bodys.Num(), BundleInfos.Num());
			for (auto& Info : BundleInfos) {
				UE_LOG(LogTemp, Warning, TEXT("LoadedBundle %s %lld"), *Info.Value.Bundle.Id, Info.Value.Index);
			}
		}, [](const FString& Category) {
			// Only restore below categories
			UE_LOG(LogTemp, Warning, TEXT("SetAvatarId: RestoreFilter %s"), *Category);
			return false;
		});

		//OnStepEnd(FTestRet{ 0, TEXT("") });
	});

	for (int32 i = 0; i < 0; i++) {
		Wear(Avatar, Tasks);
		Delay(Tasks, 1);
		Takeoff(Avatar, Tasks);
		Delay(Tasks, 1);
		Tasks.AndThen(ENamedThreads::AnyNormalThreadNormalTask, [=](const FTestRet& Last, FTestTaskChain::FOnStepEnd OnStepEnd) {
			Dummy();
			UE_LOG(LogTemp, Warning, TEXT("Wear/Takeoff %d"), i);
			OnStepEnd(FTestRet{ 0, TEXT("") });
		});
	}
	Wear(Avatar, Tasks);
}

void FAvatarWrapper::AddBundle(FTestTaskChain& Chain, ANextAvatar* Avatar, const FString& Key, const FString& Id, TFunction<void(int64)> OnComplete) {
	FString TempKey = Key;
	Chain.AndThen(ENamedThreads::AnyNormalThreadNormalTask, [=](const FTestRet& Last, FTestTaskChain::FOnStepEnd OnStepEnd) {
		Avatar->AddBundleById(Id, [=](int32 Code, const FString& Message, int64 Index) {
			UE_LOG(LogTemp, Warning, TEXT("FAvatarWrapper::AddBundle 1 %s"), ANSI_TO_TCHAR(__FUNCTION__));
			if (Code == 0) {
				IndexMap.Add(TEXT("NA_") + TempKey, Index);
			}
			UE_LOG(LogTemp, Warning, TEXT("AddBundleById %d %s %d %s"), Code, *Message, Index, *Id);
			OnStepEnd(FTestRet{ Code, Message });
		});
	});
}

void FAvatarWrapper::RemoveBundle(FTestTaskChain& Chain, ANextAvatar* Avatar, const FString& Key) {
	Chain.AndThen(ENamedThreads::GameThread, [=](const FTestRet& Last, FTestTaskChain::FOnStepEnd OnStepEnd) {
		FString TempKey = TEXT("NA_") + Key;
		FString Temp = FString::Printf(TEXT("Remove %s from body. IndexMap =>\n"), *TempKey);
		for (auto& KV : IndexMap) {
			Temp.Appendf(TEXT("\t%s %d\n"), *KV.Key, KV.Value);
		}
		UE_LOG(LogTemp, Display, TEXT("%s"), *Temp);
		if (IndexMap.Contains(TempKey)) {
			int64 Index = IndexMap[TempKey];
			if (Avatar->RemoveBundle(Index)) {
				IndexMap.Remove(TempKey);
				OnStepEnd(FTestRet{ 0, TEXT("") });
				return;
			}
		}
		OnStepEnd(FTestRet{ -1, FString::Printf(TEXT("Key not found %s"), *TempKey) });
	});
}

void FAvatarWrapper::AddFaceBundle(FTestTaskChain& Chain, ANextAvatar* Avatar, const FString& Key, const FString& Id, TFunction<void(int64)> OnComplete) {
	Chain.AndThen(ENamedThreads::GameThread, [=](const FTestRet& Last, FTestTaskChain::FOnStepEnd OnStepEnd) {
		auto Cb = [=](int32 Code, const FString& Message, int64 Index) {
			FString Temp = FString::Printf(TEXT("Add %s to face %d, %s, %d. IndexMap =>\n"), *Key, Code, *Message, Index);
			if (Code == 0) {
				IndexMap.Add(Key, Index);

				for (auto& KV : IndexMap) {
					Temp.Appendf(TEXT("\t%s %d\n"), *KV.Key, KV.Value);
				}
				UE_LOG(LogTemp, Display, TEXT("%s"), *Temp);
			}
			OnComplete(Index);
			OnStepEnd(FTestRet{ Code, Message });
		};
		Avatar->GetBody()->GetFace()->AddBundle(Id, Cb);
	});
}

void FAvatarWrapper::AddBodyBundle(FTestTaskChain& Chain, ANextAvatar* Avatar, const FString& Key, const FString& Id, TFunction<void(int64)> OnComplete) {
	Chain.AndThen(ENamedThreads::GameThread, [=](const FTestRet& Last, FTestTaskChain::FOnStepEnd OnStepEnd) {
		auto Cb = [=](int32 Code, const FString& Message, int64 Index) {
			FString Temp = FString::Printf(TEXT("Add %s to body %d, %s, %d. IndexMap =>\n"), *Key, Code, *Message, Index);
			if (Code == 0) {
				IndexMap.Add(Key, Index);

				for (auto& KV : IndexMap) {
					Temp.Appendf(TEXT("\t%s %d\n"), *KV.Key, KV.Value);
				}
				UE_LOG(LogTemp, Display, TEXT("%s"), *Temp);
			}
			OnComplete(Index);
			OnStepEnd(FTestRet{ Code, Message });
		};
		Avatar->GetBody()->AddBundle(Id, Cb);
	});
}

void FAvatarWrapper::RemoveBodyBundle(FTestTaskChain& Chain, ANextAvatar* Avatar, const FString& Key) {
	Chain.AndThen(ENamedThreads::GameThread, [=](const FTestRet& Last, FTestTaskChain::FOnStepEnd OnStepEnd) {
		FString Temp = FString::Printf(TEXT("Remove %s from body. IndexMap =>\n"), *Key);
		for (auto& KV : IndexMap) {
			Temp.Appendf(TEXT("\t%s %d\n"), *KV.Key, KV.Value);
		}
		UE_LOG(LogTemp, Display, TEXT("%s"), *Temp);

		if (IndexMap.Contains(Key)) {
			Avatar->GetBody()->RemoveBundle(IndexMap[Key]);
			IndexMap.Remove(Key);
			OnStepEnd(FTestRet{ 0, TEXT("") });
		}
		else {
			OnStepEnd(FTestRet{ 0, FString::Printf(TEXT("Key not found %s"), *Key) });
		}
	});
}

void FAvatarWrapper::RemoveFaceBundle(FTestTaskChain& Chain, ANextAvatar* Avatar, const FString& Key) {
	Chain.AndThen(ENamedThreads::GameThread, [=](const FTestRet& Last, FTestTaskChain::FOnStepEnd OnStepEnd) {
		FString Temp = FString::Printf(TEXT("Remove %s from face. IndexMap =>\n"), *Key);
		for (auto& KV : IndexMap) {
			Temp.Appendf(TEXT("\t%s %d\n"), *KV.Key, KV.Value);
		}
		UE_LOG(LogTemp, Display, TEXT("%s"), *Temp);

		if (IndexMap.Contains(Key)) {
			Avatar->GetBody()->GetFace()->RemoveBundle(IndexMap[Key]);
			IndexMap.Remove(Key);
			OnStepEnd(FTestRet{ 0, TEXT("") });
		}
		else {
			OnStepEnd(FTestRet{ 0, FString::Printf(TEXT("Key not found %s"), *Key) });
		}
	});
}

void FAvatarWrapper::Delay(FTestTaskChain& Chain, float Seconds) {
	Chain.AndThen(ENamedThreads::GameThread, [=](const FTestRet& Last, FTestTaskChain::FOnStepEnd OnStepEnd) {
		FTimerHandle TimerHandle;
		AvatarLoader.GetWorld()->GetTimerManager().SetTimer(TimerHandle, [=]() {
			OnStepEnd(FTestRet{ 0, TEXT("") });
		}, Seconds, false);
	});
}