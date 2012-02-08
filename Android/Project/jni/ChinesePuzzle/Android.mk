LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := game

LOCAL_SRC_FILES := main.cpp

LOCAL_C_INCLUDES := \
$(LOCAL_PATH)/ChinesePuzzle \
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

LOCAL_LDLIBS := -L$(call host-path, $(LOCAL_PATH)/../../libs/$(TARGET_ARCH_ABI)) \
                -lcocos2d -llog -lgame_logic
            
include $(BUILD_SHARED_LIBRARY)
