#pragma once

namespace nexthuman {
    namespace sdk {
        namespace demo {
            struct FRet {
                int32 Code;
                FString Message;

                FRet(int32 InCode, FString InMessage) : Code(InCode), Message(InMessage) {}
            };

            template <typename RET>
            class TTaskChain {
            public:
                // TODO
                //static_assert(std::is_base_of_v(FRet, RET), "RET must be FRet or subclass");
                typedef TFunction<void(RET)> FOnStepEnd;
                typedef TFunction<void(const RET& PreviousRet, FOnStepEnd)> FTask;
                typedef TFunction<void(RET)> FCallback;

                TTaskChain& AndThen(ENamedThreads::Type ThreadName, FTask Task) {
                    Tasks.Add({ ThreadName, Task });
                    return *this;
                }

                TTaskChain& AndThen(FTask Task, ENamedThreads::Type ThreadName = ENamedThreads::AnyNormalThreadNormalTask) {
                    Tasks.Add({ ThreadName, Task });
                    return *this;
                }

                void Start(FCallback Callback = [](const RET&) {}) {
                    if (Tasks.Num() == 0) {
                        Callback(RET{ 0, TEXT("empty tasks") });
                        return;
                    }

                    RunAt(0, RET{ 0, TEXT("") }, Callback);
                }

                static TTaskChain& Create() {
                    TTaskChain* Chain = new TTaskChain();
                    return *Chain;
                }

                static TTaskChain& Create(ENamedThreads::Type InThread, FTask FirstTask) {
                    check(FirstTask);
                    TTaskChain* Chain = new TTaskChain();
                    return Chain->AndThen(InThread, FirstTask);
                }

                ~TTaskChain() {}
                TTaskChain(const TTaskChain& Value) = delete;
                TTaskChain(TTaskChain&& Value) = delete;
                TTaskChain& operator=(const TTaskChain& Value) = delete;

            private:
                TTaskChain() {}

                struct FTaskInfo
                {
                    ENamedThreads::Type ThreadName;
                    FTask Task;
                };

                TArray<FTaskInfo> Tasks;
                void RunAt(int32 Index, RET PreviousRet, FCallback Callback) {
                    //UE_LOG(LogTemp, Display, TEXT("RunAt Begin %d"), Index);
                    check(Index >= 0 && Index < Tasks.Num());
                    FTaskInfo& Task = Tasks[Index];
                    AsyncTask(Task.ThreadName, [=]()
                        {
                            UE_LOG(LogTemp, Display, TEXT("1RunAt %d %s"), Index, ANSI_TO_TCHAR(__FUNCTION__));
                            Task.Task(PreviousRet, [=](RET Ret)
                                {
                                    UE_LOG(LogTemp, Display, TEXT("2RunAt %d %s"), Index, ANSI_TO_TCHAR(__FUNCTION__));
                                    //UE_LOG(LogTemp, Display, TEXT("RunAt End %d %d %s"), Index, Ret.Code, *Ret.Message);
                                    if (Ret.Code != 0 || Index + 1 == Tasks.Num()) {
                                        //UE_LOG(LogTemp, Display, TEXT("Run Complete %d"), Index);
                                        Tasks.Empty();
                                        Callback(Ret);
                                        return;
                                    }

                                    RunAt(Index + 1, Ret, Callback);
                                });
                        });
                }
            };

            typedef TTaskChain<FRet> FTaskChain;
        }
    }
}