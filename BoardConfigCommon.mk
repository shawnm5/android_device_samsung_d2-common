#
# Copyright (C) 2014 The CyanogenMod Project
# Copyright (C) 2017 The LineageOS Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

#
# This file sets variables that control the way modules are built
# thorughout the system. It should not be used to conditionally
# disable makefiles (the proper mechanism to control what gets
# included in a build is to use PRODUCT_PACKAGES in a product
# definition file).
#

# inherit from common msm8960
-include device/samsung/msm8960-common/BoardConfigCommon.mk

TARGET_SPECIFIC_HEADER_PATH += device/samsung/d2-common/include

# Bootloader
TARGET_BOOTLOADER_BOARD_NAME := MSM8960

# Kernel
TARGET_KERNEL_CONFIG        := lineageos_d2_defconfig

# Audio
BOARD_HAVE_AUDIENCE_A2220 := true
BOARD_HAVE_SAMSUNG_CSDCLIENT := true
USE_CUSTOM_AUDIO_POLICY := 1

# Bluetooth
BOARD_BLUETOOTH_BDROID_BUILDCFG_INCLUDE_DIR := device/samsung/d2-common/bluetooth
BOARD_CUSTOM_BT_CONFIG := device/samsung/d2-common/bluetooth/vnd_d2.txt
BOARD_HAVE_BLUETOOTH_BCM := true
BOARD_HAVE_SAMSUNG_BLUETOOTH := true

# Camera
TARGET_NEED_DISABLE_FACE_DETECTION := true
TARGET_NEED_DISABLE_FACE_DETECTION_BOTH_CAMERAS := true
TARGET_NEED_DISABLE_AUTOFOCUS := true
TARGET_NEED_CAMERA_ZSL := true
TARGET_NEED_CAF_HACK := true
TARGET_NEED_SAMSUNG_CAMERA_MODE := true
TARGET_NEED_DISABLE_VIDEO_SNAPSHOT := true
TARGET_ADD_ISO_MODE_1600 := true
TARGET_NEED_FFC_PICTURE_FIXUP := true
TARGET_NEED_FFC_VIDEO_FIXUP := true
TARGET_NEED_EXPOSURE_HACK := true
TARGET_NEED_NARDSHU_HACK := true

## Unsupported camera flags
# D2 doesn't have ISO50
#TARGET_ADD_ISO_MODE_50 := true
# D2 camera hal crashes on ISO_HJR
#TARGET_ADD_ISO_MODE_HJR := true

# GPS
TARGET_NO_RPC := true
USE_DEVICE_SPECIFIC_GPS := true

# Partitions
BOARD_BOOTIMAGE_PARTITION_SIZE := 10485760
BOARD_RECOVERYIMAGE_PARTITION_SIZE := 10485760
BOARD_SYSTEMIMAGE_PARTITION_SIZE := 1572864000
BOARD_USERDATAIMAGE_PARTITION_SIZE := 13140754432
BOARD_CACHEIMAGE_FILE_SYSTEM_TYPE := ext4
BOARD_CACHEIMAGE_PARTITION_SIZE := 880803840
TARGET_RECOVERY_FSTAB := device/samsung/d2-common/rootdir/etc/fstab.qcom
TARGET_USERIMAGES_USE_F2FS := true

# Recovery
TARGET_RECOVERY_DENSITY := hdpi

# RIL
BOARD_RIL_CLASS := ../../../device/samsung/d2-common/ril

# Wifi
BOARD_WLAN_DEVICE := bcmdhd
BOARD_HAVE_SAMSUNG_WIFI := true
BOARD_HOSTAPD_DRIVER := NL80211
BOARD_HOSTAPD_PRIVATE_LIB := lib_driver_cmd_${BOARD_WLAN_DEVICE}
BOARD_WPA_SUPPLICANT_DRIVER := NL80211
BOARD_WPA_SUPPLICANT_PRIVATE_LIB := lib_driver_cmd_${BOARD_WLAN_DEVICE}
WPA_SUPPLICANT_VERSION := VER_0_8_X
WIFI_DRIVER_FW_PATH_PARAM   := "/sys/module/dhd/parameters/firmware_path"
WIFI_DRIVER_FW_PATH_STA     := "/system/etc/wifi/bcmdhd_sta.bin"
WIFI_DRIVER_FW_PATH_AP      := "/system/etc/wifi/bcmdhd_apsta.bin"
