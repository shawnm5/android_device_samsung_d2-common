/*
 * Copyright (C) 2011 The Android Open Source Project
 * Copyright (C) 2017 The LineageOS Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <errno.h>
#include <malloc.h>
#include <string.h>

#include <hardware/hardware.h>
#include <hardware/nfc.h>

#define NFC_DEVICE "/dev/pn544"

static uint8_t pn544_eedata_settings[][4] = {
    {0x00, 0x9B, 0xD1, 0x0D},
    {0x00, 0x9B, 0xD2, 0x24},
    {0x00, 0x9B, 0xD3, 0x0A},
    {0x00, 0x9B, 0xD4, 0x22},
    {0x00, 0x9B, 0xD5, 0x08},
    {0x00, 0x9B, 0xD6, 0x1E},
    {0x00, 0x9B, 0xDD, 0x1C},
    {0x00, 0x9B, 0x84, 0x13},
    {0x00, 0x99, 0x81, 0x7F},
    {0x00, 0x99, 0x31, 0x70},
    {0x00, 0x99, 0x29, 0xF1},
    {0x00, 0x99, 0x2A, 0xF1},
    {0x00, 0x98, 0x00, 0x3F},
    {0x00, 0x9F, 0x09, 0x00},
    {0x00, 0x9F, 0x0A, 0x05},
    {0x00, 0x9E, 0xD1, 0xA1},
    {0x00, 0x99, 0x23, 0x00},
    {0x00, 0x9E, 0x74, 0xB0},
    {0x00, 0x9E, 0x90, 0x00},
    {0x00, 0x9F, 0x28, 0x01},
    {0x00, 0x9F, 0x35, 0x14},
    {0x00, 0x9F, 0x36, 0x60},
    {0x00, 0x9C, 0x31, 0x00},
    {0x00, 0x9C, 0x32, 0xC8},
    {0x00, 0x9C, 0x19, 0x40},
    {0x00, 0x9C, 0x1A, 0x40},
    {0x00, 0x9C, 0x0C, 0x00},
    {0x00, 0x9C, 0x0D, 0x00},
    {0x00, 0x9C, 0x12, 0x00},
    {0x00, 0x9C, 0x13, 0x00},
    {0x00, 0x98, 0xA2, 0x0E},
    {0x00, 0x98, 0x93, 0x40},
    {0x00, 0x98, 0x7D, 0x02},
    {0x00, 0x98, 0x7E, 0x00},
    {0x00, 0x9F, 0xC8, 0x01},
    {0x00, 0x9F, 0x9A, 0x00},
    {0x00, 0x9F, 0x09, 0x00},
    {0x00, 0x9C, 0x5C, 0x06},
    {0x00, 0x9C, 0x5D, 0x81},
    {0x00, 0x9B, 0x65, 0xFB}
};

/* Close an opened pn544 device instance */
static int pn544_close(hw_device_t *dev) {
    free(dev);
    return 0;
}

/*
 * Generic device handling
 */
static int nfc_open(const hw_module_t *module, const char *name,
        hw_device_t **device) {
    if (strcmp(name, NFC_PN544_CONTROLLER) == 0) {
        nfc_pn544_device_t *dev = calloc(1, sizeof(nfc_pn544_device_t));

        dev->common.tag = HARDWARE_DEVICE_TAG;
        dev->common.version = 0;
        dev->common.module = (struct hw_module_t*) module;
        dev->common.close = pn544_close;

        /* Device settings */
        dev->num_eeprom_settings = sizeof(pn544_eedata_settings) / 4;
        dev->eeprom_settings = (uint8_t*)pn544_eedata_settings;
        dev->linktype = PN544_LINK_TYPE_I2C;
        dev->device_node = NFC_DEVICE;
        dev->enable_i2c_workaround = 0;
        dev->i2c_device_address = 0;

        *device = (hw_device_t*) dev;
        return 0;
    } else {
        return -EINVAL;
    }
}


static struct hw_module_methods_t nfc_module_methods = {
    .open = nfc_open,
};

struct nfc_module_t HAL_MODULE_INFO_SYM = {
    .common = {
        .tag = HARDWARE_MODULE_TAG,
        .module_api_version = 1,
        .hal_api_version = HARDWARE_HAL_API_VERSION,
        .id = NFC_HARDWARE_MODULE_ID,
        .name = "D2 NFC HW HAL",
        .author = "The LineageOS Project",
        .methods = &nfc_module_methods,
    },
};
