/**
 ****************************************************************************************
 *
 * @file ble_att.c
 *
 * @brief This file contains the os definition.
 *
 * Copyright (C) Verisilicon 2018-2024
 *
 *
 ****************************************************************************************
 */

 static uint16_t ble_att_preferred_mtu_val;

 /** Dispatch table for incoming ATT requests.  Sorted by op code. */
 typedef int ble_att_rx_fn(uint16_t conn_handle, void *pdu);
 struct ble_att_rx_dispatch_entry {
     uint8_t bde_op;
     ble_att_rx_fn *bde_fn;
 };
 
 /** Dispatch table for incoming ATT commands.  Must be ordered by op code. */
 static const struct ble_att_rx_dispatch_entry ble_att_rx_dispatch[] = {
     { BLE_ATT_OP_ERROR_RSP,            ble_att_clt_rx_error },
     { BLE_ATT_OP_MTU_REQ,              ble_att_svr_rx_mtu },
     { BLE_ATT_OP_MTU_RSP,              ble_att_clt_rx_mtu },
     { BLE_ATT_OP_FIND_INFO_REQ,        ble_att_svr_rx_find_info },
     { BLE_ATT_OP_FIND_INFO_RSP,        ble_att_clt_rx_find_info },
     { BLE_ATT_OP_FIND_TYPE_VALUE_REQ,  ble_att_svr_rx_find_type_value },
     { BLE_ATT_OP_FIND_TYPE_VALUE_RSP,  ble_att_clt_rx_find_type_value },
     { BLE_ATT_OP_READ_TYPE_REQ,        ble_att_svr_rx_read_type },
     { BLE_ATT_OP_READ_TYPE_RSP,        ble_att_clt_rx_read_type },
     { BLE_ATT_OP_READ_REQ,             ble_att_svr_rx_read },
     { BLE_ATT_OP_READ_RSP,             ble_att_clt_rx_read },
     { BLE_ATT_OP_READ_BLOB_REQ,        ble_att_svr_rx_read_blob },
     { BLE_ATT_OP_READ_BLOB_RSP,        ble_att_clt_rx_read_blob },
     { BLE_ATT_OP_READ_MULT_REQ,        ble_att_svr_rx_read_mult },
     { BLE_ATT_OP_READ_MULT_RSP,        ble_att_clt_rx_read_mult },
     { BLE_ATT_OP_READ_GROUP_TYPE_REQ,  ble_att_svr_rx_read_group_type },
     { BLE_ATT_OP_READ_GROUP_TYPE_RSP,  ble_att_clt_rx_read_group_type },
     { BLE_ATT_OP_WRITE_REQ,            ble_att_svr_rx_write },
     { BLE_ATT_OP_WRITE_RSP,            ble_att_clt_rx_write },
     { BLE_ATT_OP_PREP_WRITE_REQ,       ble_att_svr_rx_prep_write },
     { BLE_ATT_OP_PREP_WRITE_RSP,       ble_att_clt_rx_prep_write },
     { BLE_ATT_OP_EXEC_WRITE_REQ,       ble_att_svr_rx_exec_write },
     { BLE_ATT_OP_EXEC_WRITE_RSP,       ble_att_clt_rx_exec_write },
     { BLE_ATT_OP_NOTIFY_REQ,           ble_att_svr_rx_notify },
     { BLE_ATT_OP_INDICATE_REQ,         ble_att_svr_rx_indicate },
     { BLE_ATT_OP_INDICATE_RSP,         ble_att_clt_rx_indicate },
     { BLE_ATT_OP_WRITE_CMD,            ble_att_svr_rx_write_no_rsp },
 };
 
#define BLE_ATT_RX_DISPATCH_SZ \
     (sizeof ble_att_rx_dispatch / sizeof ble_att_rx_dispatch[0])

static const struct ble_att_rx_dispatch_entry *
ble_att_rx_dispatch_entry_find(uint8_t op)
{
    const struct ble_att_rx_dispatch_entry *entry;
    int i;

    for (i = 0; i < BLE_ATT_RX_DISPATCH_SZ; i++) {
        entry = ble_att_rx_dispatch + i;
        if (entry->bde_op == op) {
            return entry;
        }

        if (entry->bde_op > op) {
            break;
        }
    }

    return NULL;
}

static int
ble_att_rx(uint16_t conn_handle, struct os_mbuf **om)
{
    const struct ble_att_rx_dispatch_entry *entry;
    uint8_t op;
    int rc;

    rc = os_mbuf_copydata(*om, 0, 1, &op);
    if (rc != 0) {
        return BLE_HS_EMSGSIZE;
    }

    entry = ble_att_rx_dispatch_entry_find(op);
    if (entry == NULL) {
        return BLE_HS_EINVAL;
    }

    ble_att_inc_rx_stat(op);

    rc = entry->bde_fn(conn_handle, om);
    if (rc != 0) {
        return rc;
    }

    return 0;
}
     
void att_init(void)
{

}



struct ble_att_attribute_entry_list {								\
	struct ble_att_attribute_entry *first;/* first element */			\
	struct ble_att_attribute_entry *last;/* last element */		\
}

static struct os_mempool ble_att_attribute_entry_pool;
static uint16_t ble_att_handle_id;
static struct ble_att_attribute_entry_list ble_att_attribute_list;


static struct ble_att_attribute_entry * ble_att_attribute_entry_alloc(void)
{
    struct ble_att_attribute_entry *entry;

    entry = os_memblock_get(&ble_att_attribute_entry_pool); //这里需要对接上OS ATT Memory.
    if (entry != NULL) {
        memset(entry, 0, sizeof *entry);
    }

    return entry;
}

/**
 * Allocate the next handle id and return it.
 *
 * @return A new 16-bit handle ID.
 */
static uint16_t ble_att_next_handle(void)
{
    /* Rollover is fatal. */
    assert(ble_att_handle_id != MAX_HANDLE_ID);
    return ++ble_att_handle_id;
}

uint16_t ble_att_current_handle(void)
{
    return ble_att_handle_id;
}

int ble_att_attribute_register(const ble_uuid_t *uuid, uint8_t permission,
                         uint8_t min_key_size, uint16_t *handle_id)
{
    struct ble_att_attribute_entry *entry;

    entry = ble_att_attribute_entry_alloc();
    if (entry == NULL) {
        return BLE_HS_ENOMEM;
    }

    entry->uuid = uuid;
    entry->permission = permission;
    entry->min_key_size = min_key_size;
    entry->handle= ble_att_next_handle_id();
    
    INSERT_LIST_TAIL(&ble_att_attribute_list, entry);   

    if (handle_id != NULL) {
        *handle_id = entry->handle;
    }

    return 0;
}

struct ble_att_attribute_entry * ble_att_attribute_find_by_handle(uint16_t handle_id)
{
    struct ble_att_attribute_entry *entry;

    for (entry = LIST_FIRST(&ble_att_attribute_list);
         entry != NULL;
         entry = LIST_NEXT(entry, ha_next)) {

        if (entry->handle == handle_id) {
            return entry;
        }
    }

    return NULL;
}

struct ble_att_attribute_entry * ble_att_attribute_find_by_uuid(struct ble_att_attribute_entry *prev, const ble_uuid_t *uuid,
                         uint16_t end_handle)
{
    struct ble_att_attribute_entry *entry;

    if (prev == NULL) {
        entry = STAILQ_FIRST(&ble_att_attribute_list);
    } else {
        entry = STAILQ_NEXT(prev, ha_next);
    }

    for (;
         entry != NULL && entry->ha_handle_id <= end_handle;
         entry = STAILQ_NEXT(entry, ha_next)) {

        if (ble_uuid_cmp(entry->ha_uuid, uuid) == 0) {
            return entry;
        }
    }

    return NULL;
}


static int ble_att_svr_check_perms(uint16_t conn_handle, int is_read,
                        struct ble_att_attribute_entry *entry,
                        uint8_t *out_att_err)
{
    struct ble_gap_sec_state sec_state;
    struct ble_store_value_sec value_sec;
    struct ble_store_key_sec key_sec;
    struct ble_hs_conn_addrs addrs;
    struct ble_hs_conn *conn;
    int author;
    int authen;
    int enc;
    int rc;

    if (is_read) {
        if (!(entry->ha_flags & BLE_ATT_F_READ)) {
            *out_att_err = BLE_ATT_ERR_READ_NOT_PERMITTED;
            return BLE_HS_ENOTSUP;
        }

        enc = entry->ha_flags & BLE_ATT_F_READ_ENC;
        authen = entry->ha_flags & BLE_ATT_F_READ_AUTHEN;
        author = entry->ha_flags & BLE_ATT_F_READ_AUTHOR;
    } else {
        if (!(entry->ha_flags & BLE_ATT_F_WRITE)) {
            *out_att_err = BLE_ATT_ERR_WRITE_NOT_PERMITTED;
            return BLE_HS_ENOTSUP;
        }

        enc = entry->ha_flags & BLE_ATT_F_WRITE_ENC;
        authen = entry->ha_flags & BLE_ATT_F_WRITE_AUTHEN;
        author = entry->ha_flags & BLE_ATT_F_WRITE_AUTHOR;
    }

    /* Bail early if this operation doesn't require security. */
    if (!enc && !authen && !author) {
        return 0;
    }

    ble_att_svr_get_sec_state(conn_handle, &sec_state);
    if ((enc || authen) && !sec_state.encrypted) {
        ble_hs_lock();
        conn = ble_hs_conn_find(conn_handle);
        if (conn != NULL) {
            ble_hs_conn_addrs(conn, &addrs);

            memset(&key_sec, 0, sizeof key_sec);
            key_sec.peer_addr = addrs.peer_id_addr;
        }
        ble_hs_unlock();

        rc = ble_store_read_peer_sec(&key_sec, &value_sec);
        if (rc == 0 && value_sec.ltk_present) {
            *out_att_err = BLE_ATT_ERR_INSUFFICIENT_ENC;
        } else {
            *out_att_err = BLE_ATT_ERR_INSUFFICIENT_AUTHEN;
        }

        return BLE_HS_ATT_ERR(*out_att_err);
    }

    if (authen && !sec_state.authenticated) {
        *out_att_err = BLE_ATT_ERR_INSUFFICIENT_AUTHEN;
        return BLE_HS_ATT_ERR(*out_att_err);
    }

    if (entry->ha_min_key_size > sec_state.key_size) {
        *out_att_err = BLE_ATT_ERR_INSUFFICIENT_KEY_SZ;
        return BLE_HS_ATT_ERR(*out_att_err);
    }

    if (author) {
        /* XXX: Prompt user for authorization. */
    }

    return 0;
}

int ble_att_init(void)
{
    int rc;

    ble_att_preferred_mtu_val = BLE_ATT_MTU_PREFERRED_DFLT;

    rc = stats_init_and_reg(
        STATS_HDR(ble_att_stats), STATS_SIZE_INIT_PARMS(ble_att_stats,
        STATS_SIZE_32), STATS_NAME_INIT_PARMS(ble_att_stats), "ble_att");
    if (rc != 0) {
        return BLE_HS_EOS;
    }

    return 0;
}



