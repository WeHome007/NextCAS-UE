#pragma once
#include "NHCommon.h"

namespace nexthuman {
	namespace sdk {
		namespace demo {
			class FNHUtil {
			public:
				static TArray<FAsset> FindAssets(EGender Gender, int32 InIndex);
				static TArray<FAvatarInfo> GetAvatarInfo();
			};
		}
	}
}