/**
 ****************************************************************************************
 *
 * @file ble_att_common.c
 *
 * @brief This file contains the os definition.
 *
 * Copyright (C) Verisilicon 2018-2024
 *
 *
 ****************************************************************************************
 */
#include <stdio.h>
#include <string.h>

static uint8_t ble_uuid_base[16] = {
    0xfb, 0x34, 0x9b, 0x5f, 0x80, 0x00, 0x00, 0x80,
    0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static int verify_uuid(const ble_uuid_t *uuid)
{
    switch (uuid->type) {
    case BLE_UUID_TYPE_16:
    case BLE_UUID_TYPE_32:
        return 0;
    case BLE_UUID_TYPE_128:
        if (memcmp(BLE_UUID128(uuid)->value, ble_uuid_base, 12) != 0) {
            return 0;
        }
        break;
    }

    return BLE_HS_EBADDATA;
}

int
ble_uuid_init_from_buf(ble_uuid_any_t *uuid, const void *buf, size_t len)
{
    switch (len) {
    case 2:
        uuid->u.type = BLE_UUID_TYPE_16;
        uuid->u16.value = get_le16(buf);
        return 0;
    case 4:
        uuid->u.type = BLE_UUID_TYPE_32;
        uuid->u32.value = get_le32(buf);
        return 0;
    case 16:
        uuid->u.type = BLE_UUID_TYPE_128;
        memcpy(uuid->u128.value, buf, 16);
        return 0;
    }

    return BLE_HS_EINVAL;
}

int
ble_uuid_cmp(const ble_uuid_t *uuid1, const ble_uuid_t *uuid2)
{
    assert(verify_uuid(uuid1) == 0);
    assert(verify_uuid(uuid2) == 0);

    switch (uuid1->type) {
    case BLE_UUID_TYPE_16:
        return (int) BLE_UUID16(uuid1)->value - (int) BLE_UUID16(uuid2)->value;
    case BLE_UUID_TYPE_32:
        return (int) BLE_UUID32(uuid1)->value - (int) BLE_UUID32(uuid2)->value;
    case BLE_UUID_TYPE_128:
        return memcmp(BLE_UUID128(uuid1)->value, BLE_UUID128(uuid2)->value, 16);
    }

    assert(0);

    return 0;
}

char *
ble_uuid_to_str(const ble_uuid_t *uuid, char *dst)
{
    const uint8_t *u8p;

    switch (uuid->type) {
    case BLE_UUID_TYPE_16:
        sprintf(dst, "0x%04" PRIx16, BLE_UUID16(uuid)->value);
        break;
    case BLE_UUID_TYPE_32:
        sprintf(dst, "0x%08" PRIx32, BLE_UUID32(uuid)->value);
        break;
    case BLE_UUID_TYPE_128:
        u8p = BLE_UUID128(uuid)->value;

        sprintf(dst, "%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-"
                     "%02x%02x%02x%02x%02x%02x",
                u8p[15], u8p[14], u8p[13], u8p[12],
                u8p[11], u8p[10],  u8p[9],  u8p[8],
                 u8p[7],  u8p[6],  u8p[5],  u8p[4],
                 u8p[3],  u8p[2],  u8p[1],  u8p[0]);
        break;
    default:
        dst[0] = '\0';
        break;
    }

    return dst;
}

uint16_t
ble_uuid_u16(const ble_uuid_t *uuid)
{
    assert(verify_uuid(uuid) == 0);

    return uuid->type == BLE_UUID_TYPE_16 ? BLE_UUID16(uuid)->value : 0;
}


int
ble_uuid_to_any(const ble_uuid_t *uuid, ble_uuid_any_t *uuid_any)
{
    BLE_HS_DBG_ASSERT(verify_uuid(uuid) == 0);

    uuid_any->u.type = uuid->type;

    switch (uuid->type) {
    case BLE_UUID_TYPE_16:
        uuid_any->u16.value = BLE_UUID16(uuid)->value;
        break;

    case BLE_UUID_TYPE_32:
        uuid_any->u32.value = BLE_UUID32(uuid)->value;
        break;

    case BLE_UUID_TYPE_128:
        memcpy(uuid_any->u128.value, BLE_UUID128(uuid)->value, 16);
        break;
    default:
        return BLE_HS_EINVAL;
    }

    return 0;
}

/*
int
ble_uuid_to_mbuf(const ble_uuid_t *uuid, struct os_mbuf *om)
{
    int len;
    void *buf;

    BLE_HS_DBG_ASSERT(verify_uuid(uuid) == 0);

    len = ble_uuid_length(uuid);

    buf = os_mbuf_extend(om, len);
    if (buf == NULL) {
        return BLE_HS_ENOMEM;
    }

    ble_uuid_flat(uuid, buf);

    return 0;
}

int
ble_uuid_flat(const ble_uuid_t *uuid, void *dst)
{
    BLE_HS_DBG_ASSERT(verify_uuid(uuid) == 0);

    switch (uuid->type) {
    case BLE_UUID_TYPE_16:
        put_le16(dst, BLE_UUID16(uuid)->value);
        break;
    case BLE_UUID_TYPE_32:
        memcpy(dst, ble_uuid_base, 16);
        put_le32(dst + 12, BLE_UUID32(uuid)->value);
        break;
    case BLE_UUID_TYPE_128:
        memcpy(dst, BLE_UUID128(uuid)->value, 16);
        break;
    default:
        return BLE_HS_EINVAL;
    }

    return 0;
}
*/
int
ble_uuid_length(const ble_uuid_t *uuid)
{
    assert(verify_uuid(uuid) == 0);

    return uuid->type >> 3;
}

