#include "NHCallbackWrapper.h"

UNHCallbackWrapper::UNHCallbackWrapper(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void UNHCallbackWrapper::Run(int32 Code, const FString& Message, int64 Index) {
	if (Callback) {
		Callback(Code, Message, Index);
	}
}

void UNHCallbackWrapper::SetCallback(TFunction<void(int32, const FString&, int64)> InCallback) {
	Callback = InCallback;
}