#pragma once

#include "NHPartInterface.h"
#include "NHCallbackWrapper.generated.h"

UCLASS()
class DEMO_API UNHCallbackWrapper : public UObject {
public:
	GENERATED_BODY()
public:

	UFUNCTION(Category = "NextHuman")
		void Run(int32 Code, const FString& Message, int64 Index);

	UNHCallbackWrapper();
	~UNHCallbackWrapper();
	void SetCallback(TFunction<void(int32, const FString&, int64)> InCallback);

private:
	TFunction<void(int32, const FString&, int64)> Callback;
};