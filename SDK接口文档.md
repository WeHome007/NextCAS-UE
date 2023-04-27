## SDK接口文档

###### 修改时间：2023-04-26

### 通用说明
#### 1、道具Id

道具Id的生成规则见服务端文档

#### 2、回调结构
```
    DECLARE_DYNAMIC_DELEGATE_ThreeParams(FNHCallback, int32, Code, const FString&, Message, int64, Index);
```
- ###### 参数说明
|字段名|描述|
|--|--|
|Code|返回码|
|Message|详细信息|
|Index|标识索引|

### 常用接口
#### 1、添加道具
```
    void AddBundle(const FString& Id, FNHCallback Callback)
``` 
- ###### 接口描述

    根据道具的Id添加对应的道具，并在Callback中返回加载状态、详细信息和道具的标识索引。

- ###### 参数说明

|字段名|描述|
|--|--|
|Id|道具id|
|Callback|回调函数，会返回加载状态|

#### 2、添加道具
```
    void RemoveBundle(int64 Index)
``` 
- ###### 接口描述

    根据道具的标识索引移除道具。

- ###### 参数说明

|字段名|描述|
|--|--|
|Index|道具的标识索引|

#### 3、修改Morph
```
    void bool ChangeMorphValue(const FString& Category, const FString& Key, const float Value)
``` 
- ###### 接口描述

    根据道具的标识索引移除道具。
    
- ###### 参数说明

|字段名|描述|
|--|--|
|Category|Morph道具类型，具体类型可参考下表|
|Key|Morph名称，具体名称可参考下表|
|Value|Morph值，范围：[-1, 1]|

- ###### 额外说明

|Morph道具类型|描述|
|-|-|
|CATEGORY_MORPH_HEAD|头部Morph|
|CATEGORY_MORPH_FACE|面部Morph|
|CATEGORY_MORPH_EYES|眼部Morph|
|CATEGORY_MORPH_EARS|耳朵Morph|
|CATEGORY_MORPH_NOSE|鼻子Morph|
|CATEGORY_MORPH_MOUTH|嘴巴Morph|
|CATEGORY_MORPH_TEETH|牙齿Morph|

|头部Morph可修改名称|描述|
|--|--|
|Depth|扁头|
|Width|宽度 |
|Height|高度|
|Size|大小|
|UpperWidth|上部宽度|
|LowerWidth|下部高度|
|NeckSize|脖子粗细|
|NeckWidth|脖子宽度|
|NeckDepth|脖子深度|
|PomumSize|喉结大小|
|PomumVertical|喉结上下移动|
|ClavicleSize|锁骨大小|
|ClavicleVertical|锁骨上下移动|

|面部Morph可修改名称|描述|
|--|--|
|Width|面宽|
|Height|面长|
|Depth|面深|
|UpperWidth|上庭宽度|
|UpperHeight|上庭高度|
|UpperDepth|上庭深度|
|MiddleWidth|中庭宽度|
|MiddleHeight|中庭高度|
|MiddleDepth|中庭深度|
|PhiltrumHeight|人中高度|
|LowerWidth|下庭宽度|
|LowerHeight|下庭高度|
|LowerDepth|下庭深度|
|ForeheadDepth|额头深度|
|ForeheadVertical|额头上下|
|ForeheadPlumpness|额头饱满|
|ForeheadWidth|额头宽度|
|TemplePlumpness|太阳穴饱满度|
|TempleWidth|太阳穴宽度|
|CheekSize|脸颊大小|
|CheekPlumpness|脸颊饱满度|
|CheekDepth|脸颊深度|
|Nasolabial|法令纹|
|CheekboneHeight|颧骨高度|
|CheekboneSize|颧骨尺寸|
|JawAngleSize|下颌角大小|
|JawAngleHeight|下颌角高度|
|JawAngleWidth|下颌角宽度|
|JawDepth|下颌深度|
|JawHeight|下颌高度|
|JawNeckHeight|颌颈高度|
|JawWidth|下颌宽度|
|Masseter|咬肌|
|JawCurve|下颌曲线|
|JawboneWidth|下颌骨宽度|
|ChinSize|下巴大小|
|ChinWidth|下巴宽度|
|ChinLength|下巴长度|
|ChinPlumpness|下巴饱满度|
|ChinLowerVertical|下巴底部|
|ChinSidesLength|下巴两侧长度|
|ChinSidesDepth|下巴两侧深度|
|ChinSidesWidth|下巴两侧宽度|
|Basiator|口轮匝肌|

|眼部Morph可修改名称|描述|
|--|--|
|Depth|眼窝深度|
|Size|眼睛大小|
|Open|眼睛开合|
|Spacing|眼睛间距|
|Vertical|眼睛上下移动|
|Tilt|倾斜|
|EyelidDouble|双眼皮强度|
|EyelidDoubleVertical|双眼皮上下移动|
|EyelidDoubleThickness|双眼皮厚度|
|EyelidDoubleTilt|双眼皮旋转|
|EyelidUpperLeftVertical|上眼皮前部|
|EyelidUpperRightVertical|上眼皮中部|
|EyelidLowerLeftVertical|下眼皮前部|
|EyelidLowerRightVertical|下眼皮中部|
|EyelidLowerVertical|下眼皮高度|
|InnerCornerSpacing|内眼角间距|
|OuterCornerSpacing|外眼角间距|
|OuterCornerVertical|外眼角高度|
|EyebrowVertical|眉毛上下移动|
|EyebrowSpacing|眉毛间距|
|EyebrowPitch|眉毛旋转|
|SilkwormSize|卧蚕大小|
|SilkwormDepth|卧蚕前后移动|

|耳朵Morph可修改名称|描述|
|--|--|
|Size|耳朵大小|
|Horizontal|耳朵前后|
|Vertical|耳朵上下|
|Yaw|耳朵旋转|
|TragusSize|耳屏大小|
|EarlobeSize|耳垂大小|
|EarlobeVertical|耳垂上下移动|

|鼻子Morph可修改名称|描述|
|--|--|
|Size|鼻子大小|
|Length|鼻子长度|
|Depth|鼻子深度|
|Vertical|鼻子高度|
|ApexNasiSize|鼻尖大小|
|ApexNasiCurve|鼻尖弯曲|
|NasionDepthP|鼻根高低|
|NasionWidth|鼻根宽度|
|BridgeDepth|鼻梁高低|
|BridgeWidth|鼻梁宽度|
|NostrilSize|鼻孔大小|
|NostrilHeight|鼻孔长度|
|LowerWidth|鼻翼宽度|
|LowerHeight|鼻翼上部高度|
|LowerVertical|鼻翼高度|
|GeisomaDepth|眉弓前后移动|

|嘴巴Morph可修改名称|描述|
|--|--|
|Size|嘴巴大小|
|Vertical|嘴巴上下移动|
|Depth|嘴巴深度|
|Width|嘴巴宽度|
|Thickness|嘴巴厚度|
|LipLowerWidth|下唇宽度|
|LipLowerHeight|下唇高度|
|LipLowerCenterHeight|下唇中心高度|
|LipLowerDepth|下唇深度|
|LipLowerPlumpness|下唇饱满度|
|LipUpperWidth|上唇宽度|
|LipUpperHeight|上唇高度|
|LipUpperDepth|上唇深度|
|LipUpperPlumpness|上唇饱满度|
|LipCrestHeight|唇峰高度|
|LipCrestSpacing|唇峰间距|
|LipCrestDepth|唇峰深度|
|LipMPlumpness|M唇丰满度|
|LipAngleVertical|唇角上扬|
|LipAngleDepth|唇角深度|
|LipAngleHeight|唇角高度|
|LipMiddleVertical|唇中垂直|
|LipQuarterVertical|唇外侧垂直|
|MentalisDepth|颏肌前后|
|MentalisUpperDepth|颏肌深度|
|MentalisHeight|颏肌高度|

|牙齿Morph可修改名称|描述|
|--|--|
|Size|牙齿大小|
|Depth|牙齿深度|
|Vertical|牙齿上下移动|

#### 4、重置Morph
```
    void ResetMorphValue()
``` 
- ###### 接口描述

    重置所有修改过的morph值
    
#### 5、修改美妆
```
    ChangeMakeupMaterialParam(const FString& Category, const FMakeupMaterialParam& Param)
``` 
- ###### 接口描述

    根据美妆类型和美妆参数，修改美妆效果
    
- ###### 参数说明

|字段名|描述|
|--|--|
|Category|美妆道具类型|
|Param|美妆参数|

- ###### 额外说明

|美妆道具类型|描述|
|--|--|
|CATEGORY_MAKEUP_EYE|眼妆|
|CATEGORY_MAKEUP_BLUSHER|腮妆|
|CATEGORY_MAKEUP_LIP|唇妆|
|CATEGORY_MAKEUP_MAGIC|幻装（脸部彩绘）|
|CATEGORY_MAKEUP_SKIN|肤质|

|美妆参数|描述|
|--|--|
|Intensity|强度|
|Metalness|金属度|
|Roughness|粗糙度|
|Color|颜色（肤质只支持该属性）|

#### 6、修改毛发参数
```
    void ChangeGroomMaterialParam(const FString& Category, const FGroomMaterialParam& Param)
``` 
- ###### 接口描述

    根据毛发类型和毛发参数，修改毛发效果
    
- ###### 参数说明

|字段名|描述|
|--|--|
|Category|毛发道具类型|
|Param|毛发参数|

- ###### 额外说明

|毛发道具类型|描述|
|--|--|
|CATEGORY_HAIR|头发|
|CATEGORY_EYEBROW|眉毛|
|CATEGORY_EYELASH|睫毛|
|CATEGORY_MUSTACHE|上胡须|
|CATEGORY_BEARD|下胡须|

|毛发参数|描述|
|--|--|
|Metalness|金属度|
|Roughness|粗糙度|
|Color|颜色（头发和睫毛只支持该属性）|

#### 7、修改动画
```
    void SetAnim(const FString& Id, FNHCallback Callback)
``` 
- ###### 接口描述

    根据动画道具id加载对应的动画，并在Callback中返回加载状态、详细信息。

- ###### 参数说明

|字段名|描述|
|--|--|
|Id|动画道具id|
|Callback|回调函数，会返回加载状态|

---