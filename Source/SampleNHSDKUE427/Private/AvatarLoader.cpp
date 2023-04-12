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
    Avatar->SetActorLocationAndRotation(FVector(0, 0, 0), FRotator(0, 0, 0));
    static const FString TempAvatarId = TEXT("avatar_64241b207f42de7d0775140d");
    Avatar->SetAvatarId(/* Put Avatar Id here */ TempAvatarId, [=](int32 Code, const FString& Message) {
        UE_LOG(LogTemp, Warning, TEXT("SetAvatarId(%s): %d %s"), *TempAvatarId, Code, *Message);
        if (Code == 0) {
            // Success
            FString CoverallId = TEXT("coverall_64312f6f10809e0df45537a7");
            Avatar->AddBundleById(CoverallId, [=](int32 Code, const FString& Message) {
                UE_LOG(LogTemp, Warning, TEXT("AddBundleById(%s): %d %s"), *CoverallId, Code, *Message);
            });
        }
    });
}
