LOCAL_PATH := .
include $(CLEAR_VARS)
LOCAL_MODULE := game_logic

LOCAL_SRC_FILES := \
$(LOCAL_PATH)/../../Common/Src/ChinesePuzzle/AppDelegate.cpp \
$(LOCAL_PATH)/../../Common/Src/ChinesePuzzle/Game/GameScene.cpp \
$(LOCAL_PATH)/../../Common/Src/ChinesePuzzle/Game/Game/Card.cpp \
$(LOCAL_PATH)/../../Common/Src/ChinesePuzzle/Game/Game/CardBoard.cpp \
$(LOCAL_PATH)/../../Common/Src/ChinesePuzzle/Game/Game/CardPlay.cpp \
$(LOCAL_PATH)/../../Common/Src/ChinesePuzzle/Game/Game/Game.cpp \
$(LOCAL_PATH)/../../Common/Src/ChinesePuzzle/Game/Game/GameConfig.cpp \
$(LOCAL_PATH)/../../Common/Src/ChinesePuzzle/Game/Game/GameControl.cpp \
$(LOCAL_PATH)/../../Common/Src/ChinesePuzzle/Game/Game/GameControlChipmunk.cpp \
$(LOCAL_PATH)/../../Common/Src/ChinesePuzzle/Game/Game/GameControlSprite.cpp \
$(LOCAL_PATH)/../../Common/Src/ChinesePuzzle/Game/Game/GameLayout.cpp \
$(LOCAL_PATH)/../../Common/Src/ChinesePuzzle/Game/Menu/Menu.cpp \
$(LOCAL_PATH)/../../Common/Src/ChinesePuzzle/Game/Menu/MenuBox.cpp \
$(LOCAL_PATH)/../../Common/Src/ChinesePuzzle/Game/Menu/MenuBoxContainer.cpp \
$(LOCAL_PATH)/../../Common/Src/ChinesePuzzle/Game/Menu/MenuContainer.cpp \
$(LOCAL_PATH)/../../Common/Src/ChinesePuzzle/Game/Menu/MenuLayout.cpp \
$(LOCAL_PATH)/../../Common/Src/Externals/ChipmunkDraw/cpDrawSpace.cpp \
$(LOCAL_PATH)/../../Common/Src/Externals/DecoratedBox/DecoratedBox.cpp

LOCAL_C_INCLUDES := \
$(LOCAL_PATH)/../../Common/Src/ChinesePuzzle \
$(LOCAL_PATH)/../../Common/Src/ChinesePuzzle/Game \
$(LOCAL_PATH)/../../Common/Src/ChinesePuzzle/Game/Game \
$(LOCAL_PATH)/../../Common/Src/ChinesePuzzle/Game/Menu \
$(LOCAL_PATH)/../../Common/Src/Externals/ChipmunkDraw \
$(LOCAL_PATH)/../../Common/Src/Externals/Cocos2Dx/chipmunk/include/chipmunk \
$(LOCAL_PATH)/../../Common/Src/Externals/Cocos2Dx/cocos2dx \
$(LOCAL_PATH)/../../Common/Src/Externals/Cocos2Dx/cocos2dx/platform \
$(LOCAL_PATH)/../../Common/Src/Externals/Cocos2Dx/cocos2dx/include \
$(LOCAL_PATH)/../../Common/Src/Externals/Cocos2Dx/CocosDenshion/include \
$(LOCAL_PATH)/../../Common/Src/Externals/Cocos2Dx/cocos2dx/lua_support \
$(LOCAL_PATH)/../../Common/Src/Externals/DecoratedBox \

LOCAL_LDLIBS := -L$(call host-path, $(LOCAL_PATH)/../Project/libs/$(TARGET_ARCH_ABI)) -lcocos2d -lcocosdenshion -lchipmunk \
                -L$(call host-path, $(LOCAL_PATH)/../../Common/Src/Externals/Cocos2Dx/cocos2dx/platform/third_party/android/libraries/$(TARGET_ARCH_ABI)) -lcurl \
                -lGLESv1_CM
            
include $(BUILD_SHARED_LIBRARY)