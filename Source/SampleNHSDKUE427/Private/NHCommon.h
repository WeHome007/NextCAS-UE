#pragma once

#include "RunChain.h"
#include "NHCategory.h"

namespace nexthuman {
	namespace sdk {
		namespace demo {
			enum class EGender {
				FEMALE,
				MALE,
			};

			struct FAsset {
				const FString Name;
				const FString Id;
				const EGender Gender;
				const FString Category;
			};

			struct FAvatarInfo {
				FString AvatarId;
				TArray<FAsset> Assets;
				FVector Position;
				FRotator Rotation;
			};

			struct FTestRet : public FRet {
				int64 ClothId;
				int64 ShoesId;
				int64 TrousersId;

				FTestRet(int32 InCode = 0,
					FString InMessage = TEXT(""),
					int64 InClothId = INT64_MIN,
					int64 InShoesId = INT64_MIN,
					int64 InTrousersId = INT64_MIN
				) : FRet(InCode, InMessage),
					ClothId(InClothId),
					ShoesId(InShoesId),
					TrousersId(InTrousersId) {}
			};

			typedef TTaskChain<FTestRet> FTestTaskChain;
			
			const FString FEMALE_AVATAR_ID = TEXT("avatar_64241b207f42de7d0775140d");
			const FString FEMALE_BODY_ID = TEXT("body_642413f6178b9538264e6a8e");
			const FString MALE_AVATAR_ID = TEXT("avatar_64241b057f42de7d0775140c");
			const FString MALE_BODY_ID = TEXT("body_642412df178b9538264e6a8d");
			const FString ACCESS_TOKEN = "J+W+sX+b1zYiKgQcVLh5rlRCGbu8rKWrA/UYqfe6qSFIblSL0z0JQ8mF4Y6lYgkYuap95BSjcPhOOuLLr9cOw6TY/65sB7DfBBYCnoB8noxDXnj7s918/0nw+yvcY8WXl2HcbswMBPDiBGT/Gc6eQg==";

			const TArray<FAsset> ASSETS{
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
				{ TEXT("SDK_Hair_F_001"),		TEXT("hair_645dd5131473414344da00b6"), EGender::FEMALE, CATEGORY_HAIR },
				{ TEXT("SDK_Hair_F_002"),		TEXT("hair_6462142490b14d23d3542bd1"), EGender::FEMALE, CATEGORY_HAIR },
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
				{ TEXT("SDK_SkeAni_F_03"),		TEXT("skeani_64621b261473414344da00c0"), EGender::FEMALE, CATEGORY_ANIMATION_BODY },
				{ TEXT("SDK_Socks_F_FC001"),	TEXT("socks_6453512d5abd84599e3b3d73"), EGender::FEMALE, CATEGORY_SOCKS },
				{ TEXT("SDK_Socks_F_FC002"),	TEXT("socks_645886ed2a48eb54410d4c54"), EGender::FEMALE, CATEGORY_SOCKS },
				{ TEXT("SDK_Trouser_F_FC001"),	TEXT("trouser_6437d2829181074839341078"), EGender::FEMALE, CATEGORY_TROUSER },
				{ TEXT("SDK_Trouser_F_FC002"),	TEXT("trouser_645887202a48eb54410d4c55"), EGender::FEMALE, CATEGORY_TROUSER },
				{ TEXT("SDK_Trouser_F_neiyi"),	TEXT("trouser_6458ae112a48eb54410d4c6b"), EGender::FEMALE, CATEGORY_TROUSER },
				{TEXT("SDK_Eyelashes_F_nh001"),	TEXT("eyelash_6482e3797941f3271e6c98a3"), EGender::FEMALE, CATEGORY_EYELASH },
				{TEXT("SDK_Eyelashes_F_nh002"),	TEXT("eyelash_6482e38eb325db3f950dca5e"), EGender::FEMALE, CATEGORY_EYELASH },
				{TEXT("SDK_Eyelashes_F_nh003"),	TEXT("eyelash_6482e39bb325db3f950dca5f"), EGender::FEMALE, CATEGORY_EYELASH },
				{TEXT("SDK_Eyelashes_F_nh004"),	TEXT("eyelash_6482e3a7b325db3f950dca60"), EGender::FEMALE, CATEGORY_EYELASH },
				{TEXT("SDK_Eyelashes_F_nh005"),	TEXT("eyelash_6482e3b5b325db3f950dca61"), EGender::FEMALE, CATEGORY_EYELASH },

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
				{ TEXT("SDK_Hair_M_001"),		TEXT("hair_645dd5361473414344da00b7"),  EGender::MALE, CATEGORY_HAIR },
				{ TEXT("SDK_Hair_M_002"),		TEXT("hair_6462146190b14d23d3542bd2"),  EGender::MALE, CATEGORY_HAIR },
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
				{TEXT("SDK_Eyelashes_M_nh001"),	TEXT("eyelash_6482e3c5b325db3f950dca62"), EGender::MALE, CATEGORY_EYELASH },
				{TEXT("SDK_Eyelashes_M_nh002"),	TEXT("eyelash_6482e3d6b325db3f950dca63"), EGender::MALE, CATEGORY_EYELASH },
				{TEXT("SDK_Eyelashes_M_nh003"),	TEXT("eyelash_6482e3e3b325db3f950dca64"), EGender::MALE, CATEGORY_EYELASH },
				{TEXT("SDK_Eyelashes_M_nh004"),	TEXT("eyelash_6482e3efb325db3f950dca65"), EGender::MALE, CATEGORY_EYELASH },
				{TEXT("SDK_Eyelashes_M_nh005"),	TEXT("eyelash_6482e3fcb325db3f950dca66"), EGender::MALE, CATEGORY_EYELASH },

			};
		}
	}
}