export THEOS=/var/mobile/theos
THEOS_PACKAGE_DIR_NAME = File-Deb
ARCHS = arm64
MOBILE_THEOS=1
PACKAGE_BUILDNAME = NemG
TARGET = iphone:latest:10.0
ROOTLESS = 0
ifeq ($(ROOTLESS), 1)
THEOS_PACKAGE_SCHEME = rootless
endif 
include $(THEOS)/makefiles/common.mk
UDID_SRC = $(wildcard NemGSCR/*.mm) $(wildcard NemGSCR/*.m)
TWEAK_NAME = NemG
NemG_FILES = $(UDID_SRC)

NemG_FRAMEWORKS = IOKit UIKit Foundation Security QuartzCore CoreGraphics CoreText UIKit Foundation CoreText AdSupport QuartzCore Foundation
 
NemG_CFLAGS = -fobjc-arc

    ####Quan Trọng#####
##################Import_NemG#########

NemG_CFLAGS += -I$(THEOS_PROJECT_DIR)/API
NemG_LDFLAGS += $(THEOS_PROJECT_DIR)/API/NemGVn.a

#################Import_END############


include $(THEOS_MAKE_PATH)/tweak.mk
