#include "NHCallbackWrapper.h"

UNHCallbackWrapper::UNHCallbackWrapper() {
	//UE_LOG(LogTemp, Warning, TEXT("%s: %p"), ANSI_TO_TCHAR(__FUNCTION__), this);
}

UNHCallbackWrapper::~UNHCallbackWrapper() {
	//UE_LOG(LogTemp, Warning, TEXT("%s: %p"), ANSI_TO_TCHAR(__FUNCTION__), this);
}

void UNHCallbackWrapper::Run(int32 Code, const FString& Message, int64 Index) {
	if (Callback) {
		Callback(Code, Message, Index);
	}
}

void UNHCallbackWrapper::SetCallback(TFunction<void(int32, const FString&, int64)> InCallback) {
	Callback = InCallback;
}