LOCAL_PATH := $(call my-dir)
MODULE_PATH := $(LOCAL_PATH)

include $(CLEAR_VARS)
LOCAL_MODULE := libGamesparks

LOCAL_C_INCLUDES := \
	"../../include/" \

LOCAL_SRC_FILES := \
	$(wildcard ../../src/cjson/*.cpp) \
	$(wildcard ../../src/easywsclient/*.cpp) \
	$(wildcard ../../src/GameSparks/*.cpp) \
	$(wildcard ../../src/google/*.cpp) \
	$(wildcard ../../src/hmac/*.cpp) \
	$(wildcard ../../src/mbedtls/*.c) \
	$(wildcard ../../include/*.h)

include $(BUILD_STATIC_LIBRARY)
