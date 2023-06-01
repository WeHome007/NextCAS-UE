#pragma once

#include "CoreMinimal.h"
#include "RunChain.h"
#include "NHCommon.h"
#include "NextAvatar.h"

class AAvatarLoader;

namespace nexthuman {
	namespace sdk {
		namespace demo {
			class FAvatarWrapper {
			public:
				explicit FAvatarWrapper(AAvatarLoader& InAvatarLoader,
					FTestTaskChain& InTasks,
					const FString& InAvatarId,
					TArray<FAsset> InAssets,
					const FVector& InPosition,
					const FRotator& InRotation);

				void Load();

			private:
				void AddBundle(FTestTaskChain& Chain,
					ANextAvatar* Avatar,
					const FString& Key,
					const FString& Id,
					TFunction<void(int64)> OnComplete = [](int64) {});

				void RemoveBundle(FTestTaskChain& Chain,
					ANextAvatar* Avatar,
					const FString& Key);

				void AddFaceBundle(FTestTaskChain& Chain,
					ANextAvatar* Avatar,
					const FString& Key,
					const FString& Id,
					TFunction<void(int64)> OnComplete = [](int64) {});

				void AddBodyBundle(FTestTaskChain& Chain,
					ANextAvatar* Avatar,
					const FString& Key,
					const FString& Id,
					TFunction<void(int64)> OnComplete = [](int64) {});

				void RemoveBodyBundle(FTestTaskChain& Chain,
					ANextAvatar* Avatar,
					const FString& Key);

				void RemoveFaceBundle(FTestTaskChain& Chain,
					ANextAvatar* Avatar,
					const FString& Key);

				void Delay(FTestTaskChain& Chain,
					float Seconds);

				AAvatarLoader& AvatarLoader;
				FTestTaskChain& Tasks;
				FString AvatarId;
				TArray<FAsset> Assets;
				FVector Position;
				FRotator Rotation;
				TMap<FString, int64> IndexMap;
			};
		}
	}
}