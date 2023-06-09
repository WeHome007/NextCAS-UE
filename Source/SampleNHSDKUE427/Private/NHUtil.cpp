#include "NHUtil.h"
using namespace nexthuman::sdk::demo;

TArray<FAsset> FNHUtil::FindAssets(EGender Gender, int32 InIndex) {
	static const TArray<FString> CategoryList{
		//CATEGORY_COVERALL,
		CATEGORY_CLOTH,
		CATEGORY_TROUSER,
		CATEGORY_SOCKS,
		CATEGORY_SHOES,
		CATEGORY_HAT,
		CATEGORY_EARRINGS,
		CATEGORY_NECKLACE,
		CATEGORY_GLASS,
		CATEGORY_HAIR,
		CATEGORY_MUSTACHE,
		CATEGORY_BEARD,
		CATEGORY_EYEBROW,
		CATEGORY_EYELASH,
		CATEGORY_MAKEUP_BLUSHER,
		CATEGORY_MAKEUP_EYE,
		CATEGORY_MAKEUP_LIP,
		CATEGORY_MAKEUP_MAGIC_FACE,
		CATEGORY_MAKEUP_PUPIL,
		CATEGORY_MAKEUP_SKIN_TEXTURE,
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

TArray<FAvatarInfo> FNHUtil::GetAvatarInfo() {
	TArray<FAvatarInfo> LoadInfoArray;
	TArray<TMap<FString, FAsset>> FemaleSuits = FNHUtil::Build(EGender::FEMALE);
	int Index = 1;
	for (auto& Suit : FemaleSuits) {
		FAvatarInfo AvatarInfo;
		AvatarInfo.AvatarId = FEMALE_AVATAR_ID;
		Suit.GenerateValueArray(AvatarInfo.Assets);
		AvatarInfo.Position = FVector(50 * Index, -50, 0);
		AvatarInfo.Rotation = FRotator(0, 0, 0);
		LoadInfoArray.Add(AvatarInfo);
		Index++;
	}
	Index = 1;
	TArray<TMap<FString, FAsset>> MaleSuits = FNHUtil::Build(EGender::MALE);
	for (auto& Suit : MaleSuits) {
		FAvatarInfo AvatarInfo;
		AvatarInfo.AvatarId = MALE_AVATAR_ID;
		Suit.GenerateValueArray(AvatarInfo.Assets);
		AvatarInfo.Position = FVector(-50 * Index, -50, 0);
		AvatarInfo.Rotation = FRotator(0, 0, 0);
		LoadInfoArray.Add(AvatarInfo);
		Index++;
	}
	return LoadInfoArray;
}

TArray<TMap<FString, FAsset>> FNHUtil::Build(EGender Gender) {
	TArray<FAsset> FilteredAssets = ASSETS.FilterByPredicate([=](const FAsset& Item) { return Item.Gender == Gender; });
	TMap<FString, TArray<FAsset>> AssetsMap;
	for (auto& A : FilteredAssets) {
		if (!AssetsMap.Contains(A.Category)) {
			AssetsMap.Add(A.Category, TArray<FAsset>{});
		}

		AssetsMap[A.Category].Add(A);
	}

	TArray<TMap<FString, FAsset>> Suits;
	for (auto& Pair : AssetsMap) {
		if (Pair.Key == CATEGORY_COVERALL) {
			continue;
		}
		for (int i = 0; i < Pair.Value.Num(); i++) {
			if (i >= Suits.Num()) {
				Suits.Add(TMap<FString, FAsset>());
			}
			Suits[i].Add(Pair.Value[i].Category, Pair.Value[i]);
		}
	}

	TArray<FAsset> CoverallAssets = AssetsMap[CATEGORY_COVERALL];
	if (CoverallAssets.Num() > 0) {
		int Index = 0;
		for (int j = 0; j < Suits.Num(); j++) {
			if (!Suits[j].Contains(CATEGORY_CLOTH) && !Suits[j].Contains(CATEGORY_TROUSER)) {
				Suits[j].Add(CATEGORY_COVERALL, CoverallAssets[Index]);
				Index++;
			}
		}
		while (Index < CoverallAssets.Num())
		{
			TMap<FString, FAsset> NewOne;
			NewOne.Add(CATEGORY_COVERALL, CoverallAssets[Index]);
			Suits.Add(NewOne);
			Index++;
		}
	}
	return Suits;
}