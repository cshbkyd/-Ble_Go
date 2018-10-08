/**
 ****************************************************************************************
 *
 * @file ble_gatt.c
 *
 * @brief This file contains the os definition.
 *
 * Copyright (C) Verisilicon 2018-2024
 *
 *
 ****************************************************************************************
 */

struct os_msg_handler gatt_msg_handler_tab[] =
{
    { GATT_EXC_MTU_CMD,             (os_msg_func_t) gatt_exc_mtu_cmd_handler },
    { GATT_DISC_CMD,                (os_msg_func_t) gatt_disc_cmd_handler },
    { GATT_READ_CMD,                (os_msg_func_t) gatt_read_cmd_handler },
    { GATT_WRITE_CMD,               (os_msg_func_t) gatt_write_cmd_handler },
    { GATT_EVENT_CFM,               (os_msg_func_t) gatt_event_cfm_handler },

    { GATT_EXECUTE_WRITE_CMD,       (os_msg_func_t) gatt_execute_write_cmd_handler },
    { GATT_REG_TO_PEER_EVT_CMD,     (os_msg_func_t) gatt_reg_to_peer_evt_cmd_handler },
    { GATT_CLIENT_RTX_IND,          (os_msg_func_t) gatt_timeout_handler },

    { GATT_SDP_SVC_DISC_CMD,        (os_msg_func_t) gatt_sdp_svc_disc_cmd_handler },
    { GATT_CMP_EVT,                 (os_msg_func_t) gatt_cmp_evt_handler },
    { GATT_DISC_SVC_IND,            (os_msg_func_t) gatt_disc_svc_ind_handler },
    { GATT_DISC_SVC_INCL_IND,       (os_msg_func_t) gatt_disc_svc_incl_ind_handler },
    { GATT_DISC_CHAR_IND,           (os_msg_func_t) gatt_disc_char_ind_handler },
    { GATT_DISC_CHAR_DESC_IND,      (os_msg_func_t) gatt_disc_char_desc_ind_handler },

    { GATT_READ_CFM,                (os_msg_func_t) gatt_read_cfm_handler },
    { GATT_WRITE_CFM,               (os_msg_func_t) gatt_write_cfm_handler },
    { GATT_ATT_INFO_CFM,            (os_msg_func_t) gatt_att_info_cfm_handler },
    { GATT_SEND_SVC_CHANGED_CMD,    (os_msg_func_t) gatt_send_svc_changed_cmd_handler },
    { GATT_SEND_EVT_CMD,            (os_msg_func_t) gatt_send_evt_cmd_handler },
    { GATT_SERVER_RTX_IND,          (os_msg_func_t) gatt_timeout_handler },

    { GATT_WRITE_REQ_IND,           (os_msg_func_t) gatt_write_req_ind_handler },
    { GATT_ATT_INFO_REQ_IND,        (os_msg_func_t) gatt_att_info_req_ind_handler },
    { GATT_READ_REQ_IND,            (os_msg_func_t) gatt_read_req_ind_handler },
};
 
/// GATT task instance.
os_state_t gatt_state[GATT_IDX_MAX];


/// GATTC task descriptor
const struct os_task_desc TASK_DESC_GATT = {gatt_msg_handler_tab, gatt_state, GATT_IDX_MAX, ARRAY_LEN(gatt_msg_handler_tab)};
void gatt_init(void)
{
    // Create GAP task
    os_task_create(TASK_GATT, &TASK_DESC_GATT); 
}

