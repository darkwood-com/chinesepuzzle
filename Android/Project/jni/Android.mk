LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

subdirs := $(addprefix $(LOCAL_PATH)/../../../Common/Src/Externals/Cocos2Dx/,$(addsuffix /Android.mk, \
           cocos2dx \
           CocosDenshion/android \
           chipmunk \
	))
subdirs += $(LOCAL_PATH)/../../Src/Android.mk $(LOCAL_PATH)/ChinesePuzzle/Android.mk

include $(subdirs)
