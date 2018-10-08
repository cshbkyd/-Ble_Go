/****************************************************************************************
 *
 * @file ble_att.h
 *
 * @brief This file contains the definition of the os environment.
 *
 * Copyright (C) Verisilicon 2018-2024
 *
 *
 ****************************************************************************************
 */
#ifndef _BLE_ATT_H_
#define _BLE_ATT_H_

#include "ble_att_common.h"

#ifdef __cplusplus
extern "C" {
#endif

enum l2cc_attribute_code
{
    BLE_ATT_OP_ERROR_RSP = 0x01,
    BLE_ATT_OP_MTU_REQ = 0x02,
    BLE_ATT_OP_MTU_RSP = 0x03,
    BLE_ATT_OP_FIND_INFO_REQ = 0x04,
    BLE_ATT_OP_FIND_INFO_RSP = 0x05,
    BLE_ATT_OP_FIND_TYPE_VALUE_REQ = 0x06,
    BLE_ATT_OP_FIND_TYPE_VALUE_RSP = 0x07,
    BLE_ATT_OP_READ_TYPE_REQ = 0x08,
    BLE_ATT_OP_READ_TYPE_RSP = 0x09,
    BLE_ATT_OP_READ_REQ = 0x0a,
    BLE_ATT_OP_READ_RSP = 0x0b,
    BLE_ATT_OP_READ_BLOB_REQ = 0x0c,
    BLE_ATT_OP_READ_BLOB_RSP = 0x0d,
    BLE_ATT_OP_READ_MULT_REQ = 0x0e,
    BLE_ATT_OP_READ_MULT_RSP = 0x0f,
    BLE_ATT_OP_READ_GROUP_TYPE_REQ = 0x10,
    BLE_ATT_OP_READ_GROUP_TYPE_RSP = 0x11,
    BLE_ATT_OP_WRITE_REQ = 0x12,
    BLE_ATT_OP_WRITE_RSP = 0x13,
    BLE_ATT_OP_PREP_WRITE_REQ = 0x16,
    BLE_ATT_OP_PREP_WRITE_RSP = 0x17,
    BLE_ATT_OP_EXEC_WRITE_REQ = 0x18,
    BLE_ATT_OP_EXEC_WRITE_RSP = 0x19,
    BLE_ATT_OP_NOTIFY_REQ = 0x1b,
    BLE_ATT_OP_INDICATE_REQ = 0x1d,
    BLE_ATT_OP_INDICATE_RSP = 0x1e,
    BLE_ATT_OP_WRITE_CMD = 0x52
}
void att_init(void);

/*==============================================*/

#define BLE_ATT_UUID_PRIMARY_SERVICE        0x2800
#define BLE_ATT_UUID_SECONDARY_SERVICE      0x2801
#define BLE_ATT_UUID_INCLUDE                0x2802
#define BLE_ATT_UUID_CHARACTERISTIC         0x2803

#define BLE_ATT_ERR_INVALID_HANDLE          0x01
#define BLE_ATT_ERR_READ_NOT_PERMITTED      0x02
#define BLE_ATT_ERR_WRITE_NOT_PERMITTED     0x03
#define BLE_ATT_ERR_INVALID_PDU             0x04
#define BLE_ATT_ERR_INSUFFICIENT_AUTHEN     0x05
#define BLE_ATT_ERR_REQ_NOT_SUPPORTED       0x06
#define BLE_ATT_ERR_INVALID_OFFSET          0x07
#define BLE_ATT_ERR_INSUFFICIENT_AUTHOR     0x08
#define BLE_ATT_ERR_PREPARE_QUEUE_FULL      0x09
#define BLE_ATT_ERR_ATTR_NOT_FOUND          0x0a
#define BLE_ATT_ERR_ATTR_NOT_LONG           0x0b
#define BLE_ATT_ERR_INSUFFICIENT_KEY_SZ     0x0c
#define BLE_ATT_ERR_INVALID_ATTR_VALUE_LEN  0x0d
#define BLE_ATT_ERR_UNLIKELY                0x0e
#define BLE_ATT_ERR_INSUFFICIENT_ENC        0x0f
#define BLE_ATT_ERR_UNSUPPORTED_GROUP       0x10
#define BLE_ATT_ERR_INSUFFICIENT_RES        0x11

#define BLE_ATT_OP_ERROR_RSP                0x01
#define BLE_ATT_OP_MTU_REQ                  0x02
#define BLE_ATT_OP_MTU_RSP                  0x03
#define BLE_ATT_OP_FIND_INFO_REQ            0x04
#define BLE_ATT_OP_FIND_INFO_RSP            0x05
#define BLE_ATT_OP_FIND_TYPE_VALUE_REQ      0x06
#define BLE_ATT_OP_FIND_TYPE_VALUE_RSP      0x07
#define BLE_ATT_OP_READ_TYPE_REQ            0x08
#define BLE_ATT_OP_READ_TYPE_RSP            0x09
#define BLE_ATT_OP_READ_REQ                 0x0a
#define BLE_ATT_OP_READ_RSP                 0x0b
#define BLE_ATT_OP_READ_BLOB_REQ            0x0c
#define BLE_ATT_OP_READ_BLOB_RSP            0x0d
#define BLE_ATT_OP_READ_MULT_REQ            0x0e
#define BLE_ATT_OP_READ_MULT_RSP            0x0f
#define BLE_ATT_OP_READ_GROUP_TYPE_REQ      0x10
#define BLE_ATT_OP_READ_GROUP_TYPE_RSP      0x11
#define BLE_ATT_OP_WRITE_REQ                0x12
#define BLE_ATT_OP_WRITE_RSP                0x13
#define BLE_ATT_OP_PREP_WRITE_REQ           0x16
#define BLE_ATT_OP_PREP_WRITE_RSP           0x17
#define BLE_ATT_OP_EXEC_WRITE_REQ           0x18
#define BLE_ATT_OP_EXEC_WRITE_RSP           0x19
#define BLE_ATT_OP_NOTIFY_REQ               0x1b
#define BLE_ATT_OP_INDICATE_REQ             0x1d
#define BLE_ATT_OP_INDICATE_RSP             0x1e
#define BLE_ATT_OP_WRITE_CMD                0x52

#define BLE_ATT_ATTR_MAX_LEN                512

#define BLE_ATT_F_READ                      0x01
#define BLE_ATT_F_WRITE                     0x02
#define BLE_ATT_F_READ_ENC                  0x04
#define BLE_ATT_F_READ_AUTHEN               0x08
#define BLE_ATT_F_READ_AUTHOR               0x10
#define BLE_ATT_F_WRITE_ENC                 0x20
#define BLE_ATT_F_WRITE_AUTHEN              0x40
#define BLE_ATT_F_WRITE_AUTHOR              0x80

#define HA_FLAG_PERM_RW                     (BLE_ATT_F_READ | BLE_ATT_F_WRITE)

#define BLE_ATT_ACCESS_OP_READ              1
#define BLE_ATT_ACCESS_OP_WRITE             2

#define BLE_ATT_MTU_DFLT                    23  /* Also the minimum. */

/**
 * An ATT MTU of 527 allows the largest ATT command (signed write) to contain a
 * 512-byte attribute value.
 */
#define BLE_ATT_MTU_MAX                     527
#define BLE_ATT_MTU_PREFERRED_DFLT          527

int ble_att_svr_read_local(uint16_t attr_handle, struct os_mbuf **out_om);
int ble_att_svr_write_local(uint16_t attr_handle, struct os_mbuf *om);

uint16_t ble_att_mtu(uint16_t conn_handle);
uint16_t ble_att_preferred_mtu(void);
int ble_att_set_preferred_mtu(uint16_t mtu);

typedef struct {
    struct ble_att_attribute_entry *next;

    const ble_uuid_t *uuid;
    uint8_t permission;
    uint8_t min_key_size;
    uint16_t handle;
    //ble_att_svr_access_fn *ha_cb;
    //void *ha_cb_arg;
} ble_att_attribute_entry;

int ble_att_attribute_register(const ble_uuid_t *uuid, uint8_t permission,
                         uint8_t min_key_size, uint16_t *handle_id);
int ble_att_init(void);

#ifdef __cplusplus
}
#endif

#endif // _BLE_ATT_H_
