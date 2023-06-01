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
	TArray<FAvatarInfo> LoadInfoArray{
		{FEMALE_AVATAR_ID, FindAssets(EGender::FEMALE, 0), FVector(50 * 1, -50, 0), FRotator(0, 0, 0)},
		{FEMALE_AVATAR_ID, FindAssets(EGender::FEMALE, 1), FVector(50 * 2, -50, 0), FRotator(0, 0, 0)},
		{FEMALE_AVATAR_ID, FindAssets(EGender::FEMALE, 2), FVector(50 * 3, -50, 0), FRotator(0, 0, 0)},

		{MALE_AVATAR_ID, FindAssets(EGender::MALE, 0), FVector(-50 * 1, -50, 0), FRotator(0, 0, 0)},
		{MALE_AVATAR_ID, FindAssets(EGender::MALE, 1), FVector(-50 * 2, -50, 0), FRotator(0, 0, 0)},
		{MALE_AVATAR_ID, FindAssets(EGender::MALE, 2), FVector(-50 * 3, -50, 0), FRotator(0, 0, 0)},
	};

	TArray<FAsset> FemaleCoverall = ASSETS.FilterByPredicate([](const FAsset& Item) {
		return Item.Category == CATEGORY_COVERALL && Item.Gender == EGender::FEMALE;
	});
	int32 Index = 3;
	for (auto& Coverall : FemaleCoverall) {
		LoadInfoArray.Add({ FEMALE_AVATAR_ID, TArray<FAsset>{ Coverall }, FVector(50 * (Index++ + 1), -50, 0), FRotator(0, 0, 0) });
	}

	TArray<FAsset> MaleCoverall = ASSETS.FilterByPredicate([](const FAsset& Item) {
		return Item.Category == CATEGORY_COVERALL && Item.Gender == EGender::MALE;
	});
	Index = 3;
	for (auto& Coverall : MaleCoverall) {
		LoadInfoArray.Add({ MALE_AVATAR_ID, TArray<FAsset>{ Coverall }, FVector(-50 * (Index++ + 1), -50, 0), FRotator(0, 0, 0) });
	}
	return LoadInfoArray;
}
