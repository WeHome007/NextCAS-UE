// Fill out your copyright notice in the Description page of Project Settings.


#include "AvatarLoader.h"
#include "INextHumanSDK.h"
#include "NextAvatar.h"

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
    static const FString TrouserId = TEXT("trouser_6437d2829181074839341078");
    
    INextHumanSDKModule::Get().PrepareResource(BodyId, [=](int32 Code, const FString& Message) {
        Avatar->SetAvatarId(/* Put Avatar Id here */ AvatarId, [=](int32 Code, const FString& Message, int64 Id) {
            UE_LOG(LogTemp, Warning, TEXT("SetAvatarId(%s): %d %s"), *AvatarId, Code, *Message);
            if (Code == 0) {
                //Avatar->AddBundleById(CoverallId, [=](int32 Code, const FString& Message, int64 Id) {
                //    UE_LOG(LogTemp, Warning, TEXT("AddBundleById(%s): %d %s %lld"), *CoverallId, Code, *Message, Id);
                //});

                Avatar->AddBundleById(ClothId, [=](int32 Code, const FString& Message, int64 Id) {
                    UE_LOG(LogTemp, Warning, TEXT("AddBundleById(%s): %d %s %d"), *ClothId, Code, *Message, Id);
                    FTimerHandle TH;
                    GetWorldTimerManager().SetTimer(TH, [=]() {
                        UE_LOG(LogTemp, Warning, TEXT("Try to remove %d"), Id);
                        Avatar->RemoveBundle(Id);
                        }, 5.0, false);
                });

                Avatar->AddBundleById(ShoesId, [=](int32 Code, const FString& Message, int64 Id) {
                    UE_LOG(LogTemp, Warning, TEXT("AddBundleById(%s): %d %s %d"), *ShoesId, Code, *Message, Id);
                    FTimerHandle TH;
                    GetWorldTimerManager().SetTimer(TH, [=]() {
                        UE_LOG(LogTemp, Warning, TEXT("Try to remove %d"), Id);
                        Avatar->RemoveBundle(Id);
                        }, 10.0, false);
                });

                Avatar->AddBundleById(TrouserId, [=](int32 Code, const FString& Message, int64 Id) {
                    UE_LOG(LogTemp, Warning, TEXT("AddBundleById(%s): %d %s %d"), *TrouserId, Code, *Message, Id);
                    FTimerHandle TH;
                    GetWorldTimerManager().SetTimer(TH, [=]() {
                        UE_LOG(LogTemp, Warning, TEXT("Try to remove %d"), Id);
                        Avatar->RemoveBundle(Id);
                        }, 15.0, false);
                });
            }
        });
    });
}
