LOCAL_PATH := .
include $(CLEAR_VARS)
LOCAL_MODULE := game_logic

LOCAL_SRC_FILES := \
$(LOCAL_PATH)/../../Android/Src/ChinesePuzzle/GameConfig_android.cpp \
$(LOCAL_PATH)/../../Android/Src/ChinesePuzzle/GameScene_android.cpp \
$(LOCAL_PATH)/../../Common/Src/ChinesePuzzle/AppDelegate.cpp \
$(LOCAL_PATH)/../../Common/Src/ChinesePuzzle/GameConfig.cpp \
$(LOCAL_PATH)/../../Common/Src/ChinesePuzzle/GameScene.cpp \
$(LOCAL_PATH)/../../Common/Src/ChinesePuzzle/Background/Background.cpp \
$(LOCAL_PATH)/../../Common/Src/ChinesePuzzle/Cocos2Dx/CCLabelBMFontMultiline.cpp \
$(LOCAL_PATH)/../../Common/Src/ChinesePuzzle/Cocos2Dx/CCReshapeDelegate.cpp \
$(LOCAL_PATH)/../../Common/Src/ChinesePuzzle/Game/Card.cpp \
$(LOCAL_PATH)/../../Common/Src/ChinesePuzzle/Game/CardBoard.cpp \
$(LOCAL_PATH)/../../Common/Src/ChinesePuzzle/Game/CardPlay.cpp \
$(LOCAL_PATH)/../../Common/Src/ChinesePuzzle/Game/Game.cpp \
$(LOCAL_PATH)/../../Common/Src/ChinesePuzzle/Game/GameControl.cpp \
$(LOCAL_PATH)/../../Common/Src/ChinesePuzzle/Game/GameControlChipmunk.cpp \
$(LOCAL_PATH)/../../Common/Src/ChinesePuzzle/Game/GameControlNode.cpp \
$(LOCAL_PATH)/../../Common/Src/ChinesePuzzle/Game/GameLayout.cpp \
$(LOCAL_PATH)/../../Common/Src/ChinesePuzzle/Menu/Menu.cpp \
$(LOCAL_PATH)/../../Common/Src/ChinesePuzzle/Menu/MenuBox.cpp \
$(LOCAL_PATH)/../../Common/Src/ChinesePuzzle/Menu/MenuGrid.cpp \
$(LOCAL_PATH)/../../Common/Src/ChinesePuzzle/Menu/MenuGridContainer.cpp \
$(LOCAL_PATH)/../../Common/Src/ChinesePuzzle/Menu/MenuLabel.cpp \
$(LOCAL_PATH)/../../Common/Src/ChinesePuzzle/Menu/MenuLabelContainer.cpp \
$(LOCAL_PATH)/../../Common/Src/ChinesePuzzle/Menu/MenuLayout.cpp \
$(LOCAL_PATH)/../../Common/Src/Externals/Archivist/Source/Archive.cpp \
$(LOCAL_PATH)/../../Common/Src/Externals/Archivist/Source/Array.cpp \
$(LOCAL_PATH)/../../Common/Src/Externals/Archivist/Source/Null.cpp \
$(LOCAL_PATH)/../../Common/Src/Externals/Archivist/Source/Object.cpp \
$(LOCAL_PATH)/../../Common/Src/Externals/Archivist/Source/StreamReader.cpp \
$(LOCAL_PATH)/../../Common/Src/Externals/Archivist/Source/StreamWriter.cpp \
$(LOCAL_PATH)/../../Common/Src/Externals/Archivist/Source/Unknown.cpp \
$(LOCAL_PATH)/../../Common/Src/Externals/ChipmunkDraw/cpDrawSpace.cpp \
$(LOCAL_PATH)/../../Common/Src/Externals/DecoratedBox/DecoratedBox.cpp

LOCAL_C_INCLUDES := \
$(LOCAL_PATH)/../../Android/Src/ChinesePuzzle \
$(LOCAL_PATH)/../../Common/Src/ChinesePuzzle \
$(LOCAL_PATH)/../../Common/Src/ChinesePuzzle/Background \
$(LOCAL_PATH)/../../Common/Src/ChinesePuzzle/Cocos2Dx \
$(LOCAL_PATH)/../../Common/Src/ChinesePuzzle/Game \
$(LOCAL_PATH)/../../Common/Src/ChinesePuzzle/Menu \
$(LOCAL_PATH)/../../Common/Src/Externals \
$(LOCAL_PATH)/../../Common/Src/Externals/Archivist/Source \
$(LOCAL_PATH)/../../Common/Src/Externals/ChipmunkDraw \
$(LOCAL_PATH)/../../Common/Src/Externals/Cocos2Dx/chipmunk/include/chipmunk \
$(LOCAL_PATH)/../../Common/Src/Externals/Cocos2Dx/cocos2dx \
$(LOCAL_PATH)/../../Common/Src/Externals/Cocos2Dx/cocos2dx/platform \
$(LOCAL_PATH)/../../Common/Src/Externals/Cocos2Dx/cocos2dx/include \
$(LOCAL_PATH)/../../Common/Src/Externals/Cocos2Dx/CocosDenshion/include \
$(LOCAL_PATH)/../../Common/Src/Externals/Cocos2Dx/cocos2dx/lua_support \
$(LOCAL_PATH)/../../Common/Src/Externals/DecoratedBox

LOCAL_LDLIBS := -L$(call host-path, $(LOCAL_PATH)/../Project/libs/$(TARGET_ARCH_ABI)) -lcocos2d -lcocosdenshion -lchipmunk \
                -L$(call host-path, $(LOCAL_PATH)/../../Common/Src/Externals/Cocos2Dx/cocos2dx/platform/third_party/android/libraries/$(TARGET_ARCH_ABI)) -lcurl \
                -lGLESv1_CM

LOCAL_CPPFLAGS += -fexceptions
LOCAL_CPPFLAGS += -frtti

include $(BUILD_SHARED_LIBRARY)