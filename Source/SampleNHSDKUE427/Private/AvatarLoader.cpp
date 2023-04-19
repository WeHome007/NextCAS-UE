// Fill out your copyright notice in the Description page of Project Settings.


#include "AvatarLoader.h"
#include "INextHumanSDK.h"
#include "NextAvatar.h"
#include "NHCategory.h"
#include "RunChain.h"

#include "Misc/DataDrivenPlatformInfoRegistry.h"

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
	if (!INextHumanSDKModule::Get().IsInitialized()) {

		INextHumanSDKModule::Get().Initialize(/* Put your access token here */ TempAccessToken, /* optional: custom server address ,*/ [=](int32 Code, const FString& Message)
		{
			if (Code == INextHumanSDKModule::CODE_SUCCESS) {
				LoadAvatar();
			}
		});
	}
	else {
		LoadAvatar();
	}
}

// Called every frame
void AAvatarLoader::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AAvatarLoader::LoadAvatar() {
	UWorld* World = GetWorld();
	if (!World) {
		return;
	}

	auto Avatar = World->SpawnActor<ANextAvatar>(FVector(0, 0, 20), FRotator(0, 0, 0));
	if (!Avatar) {
		return;
	}
	//female
	static const FString AvatarId = TEXT("avatar_64241b207f42de7d0775140d");
	static const FString BodyId = TEXT("body_642413f6178b9538264e6a8e");
	static const FString CoverallId = TEXT("coverall_64312f6f10809e0df45537a7");
	static const FString ClothId = TEXT("cloth_6437c90d9181074839341076");
	static const FString ShoesId = TEXT("shoes_6437d1b39181074839341077");
	static const FString TrousersId = TEXT("trouser_6437d2829181074839341078");
	static const FString HairId = TEXT("hair_643cb3f3d46ccd6078f72385");
	static const FString EyebrowId = TEXT("eyebrow_643cb7b016938c6c359608f2");
	static const FString Eyelash = TEXT("eyelash_643cdab716938c6c359608f3");

	using nexthuman::sdk::demo::FRet;
	using nexthuman::sdk::demo::TTaskChain;
	struct FTestRet : public FRet {
		int64 ClothId;
		int64 ShoesId;
		int64 TrousersId;
		FTestRet(int32 InCode, FString InMessage, int64 InClothId = INT64_MIN, int64 InShoesId = INT64_MIN, int64 InTrousersId = INT64_MIN):FRet(InCode, InMessage), ClothId(InClothId), ShoesId(InShoesId), TrousersId(InTrousersId) {}
	};
	typedef TTaskChain<FTestRet> FTaskChain;

	FTaskChain& Tasks = FTaskChain::Create(ENamedThreads::AnyNormalThreadNormalTask, [=](const FTestRet& Last, FTaskChain::FOnStepEnd OnStepEnd) {
		INextHumanSDKModule::Get().PrepareResource(AvatarId, [=](int32 Code, const FString& Message) {
			OnStepEnd(FTestRet{ Code, Message });
		});
	}).AndThen(ENamedThreads::AnyNormalThreadNormalTask, [=](const FTestRet& Last, FTaskChain::FOnStepEnd OnStepEnd) {
		INextHumanSDKModule::Get().PrepareResource(BodyId, [=](int32 Code, const FString& Message) {
			OnStepEnd(FTestRet{ Code, Message });
		});
	}).AndThen(ENamedThreads::AnyNormalThreadNormalTask, [=](const FTestRet& Last, FTaskChain::FOnStepEnd OnStepEnd) {
		INextHumanSDKModule::Get().PrepareResource(CoverallId, [=](int32 Code, const FString& Message) {
			OnStepEnd(FTestRet{ Code, Message });
		});
	}).AndThen(ENamedThreads::AnyNormalThreadNormalTask, [=](const FTestRet& Last, FTaskChain::FOnStepEnd OnStepEnd) {
		INextHumanSDKModule::Get().PrepareResource(ClothId, [=](int32 Code, const FString& Message) {
			OnStepEnd(FTestRet{ Code, Message });
		});
	}).AndThen(ENamedThreads::AnyNormalThreadNormalTask, [=](const FTestRet& Last, FTaskChain::FOnStepEnd OnStepEnd) {
		INextHumanSDKModule::Get().PrepareResource(ShoesId, [=](int32 Code, const FString& Message) {
			OnStepEnd(FTestRet{ Code, Message });
		});
	}).AndThen(ENamedThreads::AnyNormalThreadNormalTask, [=](const FTestRet& Last, FTaskChain::FOnStepEnd OnStepEnd) {
		INextHumanSDKModule::Get().PrepareResource(TrousersId, [=](int32 Code, const FString& Message) {
			OnStepEnd(FTestRet{ Code, Message });
		});
	}).AndThen(ENamedThreads::AnyNormalThreadNormalTask, [=](const FTestRet& Last, FTaskChain::FOnStepEnd OnStepEnd) {
		Avatar->SetAvatarId(/* Put Avatar Id here */ AvatarId, [=](int32 Code, const FString& Message, int64 Id) {
			OnStepEnd(FTestRet{ Code, Message });

			{
				// struct HeadMorphParam
				// {
				// 	float Depth; 				// 扁头
				// 	float Width;				// 宽度 
				// 	float Height;				// 高度
				// 	float Size;					// 大小
				// 	float UpperWidth;			// 上部宽度
				// 	float LowerWidth;			// 下部高度
				// 	float NeckSize;				// 脖子粗细
				// 	float NeckWidth;			// 脖子宽度
				// 	float NeckDepth;			// 脖子深度
				// 	float PomumSize;			// 喉结大小
				// 	float PomumVertical;		// 喉结上下移动
				// 	float ClavicleSize;			// 锁骨大小
				// 	float ClavicleVertical;		// 锁骨上下移动
				// }
				//
				// struct FaceMorphParam
				// {
				// 	float Width;				// 面宽
				// 	float Height;				// 面长
				// 	float Depth;				// 面深
				// 	float UpperWidth;			// 上庭宽度
				// 	float UpperHeight;			// 上庭高度
				// 	float UpperDepth;			// 上庭深度
				// 	float MiddleWidth;			// 中庭宽度
				// 	float MiddleHeight;			// 中庭高度
				// 	float MiddleDepth;			// 中庭深度
				// 	float PhiltrumHeight;		// 人中高度
				// 	float LowerWidth;			// 下庭宽度
				// 	float LowerHeight;			// 下庭高度
				// 	float LowerDepth;			// 下庭深度
				// 	float ForeheadDepth;		// 额头深度
				// 	float ForeheadVertical;		// 额头上下
				// 	float ForeheadPlumpness;	// 额头饱满
				// 	float ForeheadWidth;		// 额头宽度
				// 	float TemplePlumpness;		// 太阳穴饱满度
				// 	float TempleWidth;			// 太阳穴宽度
				// 	float CheekSize;			// 脸颊大小
				// 	float CheekPlumpness;		// 脸颊饱满度
				// 	float CheekDepth;			// 脸颊深度
				// 	float Nasolabial;			// 法令纹
				// 	float CheekboneHeight;		// 颧骨高度
				// 	float CheekboneSize;		// 颧骨尺寸
				// 	float JawAngleSize;			// 下颌角大小
				// 	float JawAngleHeight;		// 下颌角高度
				// 	float JawAngleWidth;		// 下颌角宽度
				// 	float JawDepth;				// 下颌深度
				// 	float JawHeight;			// 下颌高度
				// 	float JawNeckHeight;		// 颌颈高度
				// 	float JawWidth;				// 下颌宽度
				// 	float Masseter;				// 咬肌
				// 	float JawCurve;				// 下颌曲线
				// 	float JawboneWidth;			// 下颌骨宽度
				// 	float ChinSize;				// 下巴大小
				// 	float ChinWidth;			// 下巴宽度
				// 	float ChinLength;			// 下巴长度
				// 	float ChinPlumpness;		// 下巴饱满度
				// 	float ChinLowerVertical;	// 下巴底部
				// 	float ChinSidesLength;		// 下巴两侧长度
				// 	float ChinSidesDepth;		// 下巴两侧深度
				// 	float ChinSidesWidth;		// 下巴两侧宽度
				// 	float Basiator;				// 口轮匝肌
				// };
				//
				// struct EyesMorphParam
				// {
				// 	float Depth;					// 眼窝深度
				// 	float Size;						// 眼睛大小
				// 	float Open;						// 眼睛开合
				// 	float Spacing;					// 眼睛间距
				// 	float Vertical;					// 眼睛上下移动
				// 	float Tilt;						// 倾斜
				// 	float EyelidDouble; 			// 双眼皮强度
				// 	float EyelidDoubleVertical; 	// 双眼皮上下移动
				// 	float EyelidDoubleThickness; 	// 双眼皮厚度
				// 	float EyelidDoubleTilt; 		// 双眼皮旋转
				// 	float EyelidUpperLeftVertical;	// 上眼皮前部
				// 	float EyelidUpperRightVertical;	// 上眼皮中部
				// 	float EyelidLowerLeftVertical;	// 下眼皮前部
				// 	float EyelidLowerRightVertical;	// 下眼皮中部
				// 	float EyelidLowerVertical;		// 下眼皮高度
				// 	float InnerCornerSpacing;		// 内眼角间距
				// 	float OuterCornerSpacing;		// 外眼角间距
				// 	float OuterCornerVertical;		// 外眼角高度
				// 	float EyebrowVertical;			// 眉毛上下移动
				// 	float EyebrowSpacing;			// 眉毛间距
				// 	float EyebrowPitch;				// 眉毛旋转
				// 	float SilkwormSize;				// 卧蚕大小
				// 	float SilkwormDepth;			// 卧蚕前后移动
				// };
				//
				// struct EarsMorphParam
				// {
				// 	float Size;					// 耳朵大小
				// 	float Horizontal;			// 耳朵前后
				// 	float Vertical;				// 耳朵上下
				// 	float Yaw;					// 耳朵旋转
				// 	float TragusSize;			// 耳屏大小
				// 	float EarlobeSize;			// 耳垂大小
				// 	float EarlobeVertical;		// 耳垂上下移动
				// };
				// 			
				// struct NoseMorphParam
				// {
				// 	float Size;					// 鼻子大小
				// 	float Length;				// 鼻子长度
				// 	float Depth;				// 鼻子深度
				// 	float Vertical;				// 鼻子高度
				// 	float ApexNasiSize;			// 鼻尖大小
				// 	float ApexNasiCurve;		// 鼻尖弯曲
				// 	float NasionDepthP;			// 鼻根高低
				// 	float NasionWidth;			// 鼻根宽度
				// 	float BridgeDepth;			// 鼻梁高低
				// 	float BridgeWidth;			// 鼻梁宽度
				// 	float NostrilSize;			// 鼻孔大小
				// 	float NostrilHeight;		// 鼻孔长度
				// 	float LowerWidth;			// 鼻翼宽度
				// 	float LowerHeight;			// 鼻翼上部高度
				// 	float LowerVertical;		// 鼻翼高度
				// 	float GeisomaDepth;			// 眉弓前后移动
				// };
				//
				// struct MouthMorphParam
				// {
				// 	float Size;					// 嘴巴大小
				// 	float Vertical;				// 嘴巴上下移动
				// 	float Depth;				// 嘴巴深度
				// 	float Width;				// 嘴巴宽度
				// 	float Thickness;			// 嘴巴厚度
				// 	float LipLowerWidth;		// 下唇宽度
				// 	float LipLowerHeight;		// 下唇高度
				// 	float LipLowerCenterHeight;	// 下唇中心高度
				// 	float LipLowerDepth;		// 下唇深度
				// 	float LipLowerPlumpness;	// 下唇饱满度
				// 	float LipUpperWidth;		// 上唇宽度
				// 	float LipUpperHeight;		// 上唇高度
				// 	float LipUpperDepth;		// 上唇深度
				// 	float LipUpperPlumpness;	// 上唇饱满度
				// 	float LipCrestHeight;		// 唇峰高度
				// 	float LipCrestSpacing;		// 唇峰间距
				// 	float LipCrestDepth;		// 唇峰深度
				// 	float LipMPlumpness;		// M唇丰满度
				// 	float LipAngleVertical;		// 唇角上扬
				// 	float LipAngleDepth;		// 唇角深度
				// 	float LipAngleHeight;		// 唇角高度
				// 	float LipMiddleVertical;	// 唇中垂直
				// 	float LipQuarterVertical;	// 唇外侧垂直
				// 	float MentalisDepth;		// 颏肌前后
				// 	float MentalisUpperDepth;	// 颏肌深度
				// 	float MentalisHeight;		// 颏肌高度
				// };
				//
				// struct FTeethMorphParam
				// {
				// 	float Size;					// 牙齿大小
				// 	float Depth;				// 牙齿深度
				// 	float Vertical;				// 牙齿上下移动
				// };

				const FString Category = CATEGORY_MORPH_HEAD;		// CATEGORY_MORPH_XX
				const FString Key = "Height";						// Category对应的参数列表
				const float Value = 0.5;							// -1 ~ 1
				// 将头部高度morph值改为0.5
				Avatar->GetBody()->GetFace()->ChangeMorphValue(Category, Key, Value);
			}
			
		});
	})
		.AndThen(ENamedThreads::AnyNormalThreadNormalTask, [=](const FTestRet& Last, FTaskChain::FOnStepEnd OnStepEnd) {
		Avatar->AddBundleById(ClothId, [=](int32 Code, const FString& Message, int64 Id) {
			OnStepEnd(FTestRet{ Code, Message, Id });
		});
	})
		.AndThen(ENamedThreads::AnyNormalThreadNormalTask, [=](const FTestRet& Last, FTaskChain::FOnStepEnd OnStepEnd) {
		Avatar->AddBundleById(ShoesId, [=](int32 Code, const FString& Message, int64 Id) {
			OnStepEnd(FTestRet{ Code, Message, Last.ClothId, Id });
		});
	})
		.AndThen(ENamedThreads::AnyNormalThreadNormalTask, [=](const FTestRet& Last, FTaskChain::FOnStepEnd OnStepEnd) {
		Avatar->AddBundleById(TrousersId, [=](int32 Code, const FString& Message, int64 Id) {
			OnStepEnd(FTestRet{ Code, Message, Last.ClothId, Last.ShoesId, Id });
		});
	})
		.AndThen(ENamedThreads::AnyNormalThreadNormalTask, [=](const FTestRet& Last, FTaskChain::FOnStepEnd OnStepEnd) {
		Avatar->AddBundleById(HairId, [=](int32 Code, const FString& Message, int64 Id) {
			OnStepEnd(FTestRet{ Code, Message, Last.ClothId, Last.ShoesId, Last.TrousersId });

			{
				const FString Category = CATEGORY_HAIR;		// 毛发类型
				FGroomMaterialParam Param;					// 对应资产的材质球支持的修改参数
				Param.Color = FLinearColor::Blue;
				// 将当前头发的颜色改为蓝色
				Avatar->GetBody()->GetFace()->ChangeGroomMaterialParam(Category, Param);
			}
		});
	})
		.AndThen(ENamedThreads::AnyNormalThreadNormalTask, [=](const FTestRet& Last, FTaskChain::FOnStepEnd OnStepEnd) {
		Avatar->AddBundleById(EyebrowId, [=](int32 Code, const FString& Message, int64 Id) {
			OnStepEnd(FTestRet{ Code, Message, Last.ClothId, Last.ShoesId, Last.TrousersId });
		});
	})
		;

	Tasks.Start([=](const FTestRet& Last) {
		for (auto& Info : FDataDrivenPlatformInfoRegistry::GetAllPlatformInfos()) {
			UE_LOG(LogTemp, Warning, TEXT("DDPI %s"), *Info.Key);
			UE_LOG(LogTemp, Warning, TEXT("\tFreezing_bAlignBases %d"), Info.Value.Freezing_bAlignBases);
		}
		UE_LOG(LogTemp, Warning, TEXT("==>> End"));
	});
}
