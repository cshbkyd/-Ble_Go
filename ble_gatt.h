/****************************************************************************************
 *
 * @file ble_gatt.h
 *
 * @brief This file contains the definition of the os environment.
 *
 * Copyright (C) Verisilicon 2018-2024
 *
 *
 ****************************************************************************************
 */
#ifndef _BLE_GATT_H_
#define _BLE_GATT_H_
#include <inttypes.h>
#include "ble_att.h"
#ifdef __cplusplus
extern "C" {
#endif

enum gatt_msg_id
{
    /* Default event */
    GATT_CMP_EVT = TASK_FIRST_MSG(TASK_ID_GATT),//!< GATTC_CMP_EVT

    /* ATTRIBUTE CLIENT */
    /// Server configuration request
    GATT_EXC_MTU_CMD,                            //!< GATTC_EXC_MTU_CMD
    /// Indicate that the ATT MTU has been updated (negotiated)
    GATT_MTU_CHANGED_IND,                        //!< GATTC_MTU_CHANGED_IND

    /*Discover All Services */
    /*Discover Services by Service UUID*/
    /*Find Included Services*/
    /*Discover Characteristics by UUID*/
    /*Discover All Characteristics of a Service*/
    /*Discover All Characteristic Descriptors*/
    /// Discovery command
    GATT_DISC_CMD,                               //!< GATTC_DISC_CMD
    /* GATT -> HL: Events to Upper layer */
    /*Discover All Services*/
    /// Discovery services indication
    GATT_DISC_SVC_IND,                           //!< GATTC_DISC_SVC_IND
    /*Find Included Services*/
    /// Discover included services indication
    GATT_DISC_SVC_INCL_IND,                      //!< GATTC_DISC_SVC_INCL_IND
    /*Discover All Characteristics of a Service*/
    /// Discover characteristic indication
    GATT_DISC_CHAR_IND,                          //!< GATTC_DISC_CHAR_IND
    /*Discover All Characteristic Descriptors*/
    /// Discovery characteristic descriptor indication
    GATT_DISC_CHAR_DESC_IND,                     //!< GATTC_DISC_CHAR_DESC_IND

    /*Read Value*/
    /*Read Using UUID*/
    /*Read Long Value*/
    /*Read Multiple Values*/
    /// Read command
    GATT_READ_CMD,                               //!< GATTC_READ_CMD
    /// Read response
    GATT_READ_IND,                               //!< GATTC_READ_IND

    /*Write without response*/
    /*Write without response with Authentication*/
    /*Write Characteristic Value*/
    /*Signed Write Characteristic Value*/
    /*Write Long Characteristic Value*/
    /*Characteristic Value Reliable Write*/
    /*Write Characteristic Descriptors*/
    /*Write Long Characteristic Descriptors*/
    /*Characteristic Value Reliable Write*/
    /// Write command request
    GATT_WRITE_CMD,                              //!< GATTC_WRITE_CMD

    /* Cancel / Execute pending write operations */
    /// Execute write characteristic request
    GATT_EXECUTE_WRITE_CMD,                      //!< GATTC_EXECUTE_WRITE_CMD

    /* Reception of an indication or notification from peer device. */
    /// peer device triggers an event (notification)
    GATT_EVENT_IND,                              //!< GATTC_EVENT_IND
    /// peer device triggers an event that requires a confirmation (indication)
    GATT_EVENT_REQ_IND,                          //!< GATTC_EVENT_REQ_IND
    /// Confirm reception of event (trigger a confirmation message)
    GATT_EVENT_CFM,                              //!< GATTC_EVENT_CFM

    /// Registration to peer device events (Indication/Notification).
    GATT_REG_TO_PEER_EVT_CMD,                    //!< GATTC_REG_TO_PEER_EVT_CMD

    /* -------------------------- ATTRIBUTE SERVER ------------------------------- */
    /*Notify Characteristic*/
    /*Indicate Characteristic*/
    /// send an event to peer device
    GATT_SEND_EVT_CMD,                           //!< GATTC_SEND_EVT_CMD

    /* Service Changed Characteristic Indication */
    /**
     * Send a Service Changed indication to a device
     * (message structure is struct gattm_svc_changed_ind_req)
     */
    GATT_SEND_SVC_CHANGED_CMD,                   //!< GATTC_SEND_SVC_CHANGED_CMD
    /**
     * Inform the application when sending of Service Changed indications has been
     * enabled or disabled
     */
    GATT_SVC_CHANGED_CFG_IND,                    //!< GATTC_SVC_CHANGED_CFG_IND

    /* Indicate that read operation is requested. */
    /// Read command indicated to upper layers.
    GATT_READ_REQ_IND,                           //!< GATTC_READ_REQ_IND
    /// Read command confirmation from upper layers.
    GATT_READ_CFM,                               //!< GATTC_READ_CFM

    /* Indicate that write operation is requested. */
    /// Write command indicated to upper layers.
    GATT_WRITE_REQ_IND,                          //!< GATTC_WRITE_REQ_IND
    /// Write command confirmation from upper layers.
    GATT_WRITE_CFM,                              //!< GATTC_WRITE_CFM

    /* Indicate that write operation is requested. */
    /// Request Attribute info to upper layer - could be trigger during prepare write
    GATT_ATT_INFO_REQ_IND,                       //!< GATTC_ATT_INFO_REQ_IND
    /// Attribute info from upper layer confirmation
    GATT_ATT_INFO_CFM,                           //!< GATTC_ATT_INFO_CFM

    /* ----------------------- SERVICE DISCOVERY PROCEDURE  --------------------------- */
    /// Service Discovery command
    GATT_SDP_SVC_DISC_CMD,                       //!< GATTC_SDP_SVC_DISC_CMD
    /// Service Discovery indicate that a service has been found.
    GATT_SDP_SVC_IND,                            //!< GATTC_SDP_SVC_IND

    /* -------------------------- TRANSACTION ERROR EVENT ----------------------------- */
    /// Transaction Timeout Error Event no more transaction will be accepted
    GATT_TRANSACTION_TO_ERROR_IND,               //!< GATTC_TRANSACTION_TO_ERROR_IND

    /* ------------------------------- Internal API ----------------------------------- */
    /// Client Response timeout indication
    GATT_CLIENT_RTX_IND,                         //!< GATTC_CLIENT_RTX_IND
    /// Server indication confirmation timeout indication
    GATT_SERVER_RTX_IND,                         //!< GATTC_SERVER_RTX_IND
};

void gatt_init(void);
//  ==============================================


#define BLE_GATT_REGISTER_OP_SVC                        1
#define BLE_GATT_REGISTER_OP_CHR                        2
#define BLE_GATT_REGISTER_OP_DSC                        3

#define BLE_GATT_SVC_UUID16                             0x1801
#define BLE_GATT_DSC_CLT_CFG_UUID16                     0x2902

#define BLE_GATT_CHR_PROP_BROADCAST                     0x01
#define BLE_GATT_CHR_PROP_READ                          0x02
#define BLE_GATT_CHR_PROP_WRITE_NO_RSP                  0x04
#define BLE_GATT_CHR_PROP_WRITE                         0x08
#define BLE_GATT_CHR_PROP_NOTIFY                        0x10
#define BLE_GATT_CHR_PROP_INDICATE                      0x20
#define BLE_GATT_CHR_PROP_AUTH_SIGN_WRITE               0x40
#define BLE_GATT_CHR_PROP_EXTENDED                      0x80

#define BLE_GATT_ACCESS_OP_READ_CHR                     0
#define BLE_GATT_ACCESS_OP_WRITE_CHR                    1
#define BLE_GATT_ACCESS_OP_READ_DSC                     2
#define BLE_GATT_ACCESS_OP_WRITE_DSC                    3

#define BLE_GATT_CHR_F_BROADCAST                        0x0001
#define BLE_GATT_CHR_F_READ                             0x0002
#define BLE_GATT_CHR_F_WRITE_NO_RSP                     0x0004
#define BLE_GATT_CHR_F_WRITE                            0x0008
#define BLE_GATT_CHR_F_NOTIFY                           0x0010
#define BLE_GATT_CHR_F_INDICATE                         0x0020
#define BLE_GATT_CHR_F_AUTH_SIGN_WRITE                  0x0040
#define BLE_GATT_CHR_F_RELIABLE_WRITE                   0x0080
#define BLE_GATT_CHR_F_AUX_WRITE                        0x0100
#define BLE_GATT_CHR_F_READ_ENC                         0x0200
#define BLE_GATT_CHR_F_READ_AUTHEN                      0x0400
#define BLE_GATT_CHR_F_READ_AUTHOR                      0x0800
#define BLE_GATT_CHR_F_WRITE_ENC                        0x1000
#define BLE_GATT_CHR_F_WRITE_AUTHEN                     0x2000
#define BLE_GATT_CHR_F_WRITE_AUTHOR                     0x4000

#define BLE_GATT_SVC_TYPE_END                           0
#define BLE_GATT_SVC_TYPE_PRIMARY                       1
#define BLE_GATT_SVC_TYPE_SECONDARY                     2

/*** @client. */
struct ble_gatt_error {
    uint16_t status;
    uint16_t att_handle;
};

struct ble_gatt_svc {
    uint16_t start_handle;
    uint16_t end_handle;
    ble_uuid_any_t uuid;
};

struct ble_gatt_attr {
    uint16_t handle;
    uint16_t offset;
    uint8_t *p_value;
};

struct ble_gatt_chr {
    uint16_t def_handle;
    uint16_t val_handle;
    uint8_t properties;
    ble_uuid_any_t uuid;
};

struct ble_gatt_dsc {
    uint16_t handle;
    ble_uuid_any_t uuid;
};


/*** @client functions. */

/*** @server. */
struct ble_gatt_svc_def {
    /**
     * One of the following:
     *     o BLE_GATT_SVC_TYPE_PRIMARY - primary service
     *     o BLE_GATT_SVC_TYPE_SECONDARY - secondary service
     *     o 0 - No more services in this array.
     */
    uint8_t type;

    /**
     * Pointer to service UUID; use BLE_UUIDxx_DECLARE macros to declare
     * proper UUID; NULL if there are no more characteristics in the service.
     */
    const ble_uuid_t *uuid;

    /**
     * Array of pointers to other service definitions.  These services are
     * reported as "included services" during service discovery.  Terminate the
     * array with NULL.
     */
    const struct ble_gatt_svc_def **includes;

    /**
     * Array of characteristic definitions corresponding to characteristics
     * belonging to this service.
     */
    const struct ble_gatt_chr_def *characteristics;
};

struct ble_gatt_chr_def {
    /**
     * Pointer to characteristic UUID; use BLE_UUIDxx_DECLARE macros to declare
     * proper UUID; NULL if there are no more characteristics in the service.
     */
    const ble_uuid_t *uuid;

    /**
     * Callback that gets executed when this characteristic is read or
     * written.
     */
    ble_gatt_access_fn *access_cb;

    /** Optional argument for callback. */
    void *arg;

    /**
     * Array of this characteristic's descriptors.  NULL if no descriptors.
     * Do not include CCCD; it gets added automatically if this
     * characteristic's notify or indicate flag is set.
     */
    struct ble_gatt_dsc_def *descriptors;

    /** Specifies the set of permitted operations for this characteristic. */
    ble_gatt_chr_flags flags;

    /** Specifies minimum required key size to access this characteristic. */
    uint8_t min_key_size;

    /** 
     * At registration time, this is filled in with the characteristic's value
     * attribute handle.
     */
    uint16_t * const val_handle;
};

struct ble_gatt_dsc_def {
    /**
     * Pointer to descriptor UUID; use BLE_UUIDxx_DECLARE macros to declare
     * proper UUID; NULL if there are no more characteristics in the service.
     */
    const ble_uuid_t *uuid;

    /** Specifies the set of permitted operations for this descriptor. */
    uint8_t att_flags;

    /** Specifies minimum required key size to access this descriptor. */
    uint8_t min_key_size;

    /** Callback that gets executed when the descriptor is read or written. */
    ble_gatt_access_fn *access_cb;

    /** Optional argument for callback. */
    void *arg;
};

/**
 * Context for an access to a GATT characteristic or descriptor.  When a client
 * reads or writes a locally registered characteristic or descriptor, an
 * instance of this struct gets passed to the application callback.
 */
struct ble_gatt_access_ctxt {
    /**
     * Indicates the gatt operation being performed.  This is equal to one of
     * the following values:
     *     o  BLE_GATT_ACCESS_OP_READ_CHR
     *     o  BLE_GATT_ACCESS_OP_WRITE_CHR
     *     o  BLE_GATT_ACCESS_OP_READ_DSC
     *     o  BLE_GATT_ACCESS_OP_WRITE_DSC
     */
    uint8_t op;

    /**
     * A container for the GATT access data.
     *     o For reads: The application populates this with the value of the
     *       characteristic or descriptor being read.
     *     o For writes: This is already populated with the value being written
     *       by the peer.  If the application wishes to retain this mbuf for
     *       later use, the access callback must set this pointer to NULL to
     *       prevent the stack from freeing it.
     */
    struct os_mbuf *om;

    /**
     * The GATT operation being performed dictates which field in this union is
     * valid.  If a characteristic is being accessed, the chr field is valid.
     * Otherwise a descriptor is being accessed, in which case the dsc field
     * is valid.
     */
    union {
        /**
         * The characteristic definition corresponding to the characteristic
         * being accessed.  This is what the app registered at startup.
         */
        const struct ble_gatt_chr_def *chr;

        /**
         * The descriptor definition corresponding to the descriptor being
         * accessed.  This is what the app registered at startup.
         */
        const struct ble_gatt_dsc_def *dsc;
    };
};

/**
 * Context passed to the registration callback; represents the GATT service,
 * characteristic, or descriptor being registered.
 */
struct ble_gatt_register_ctxt {
    /**
     * Indicates the gatt registration operation just performed.  This is
     * equal to one of the following values:
     *     o BLE_GATT_REGISTER_OP_SVC
     *     o BLE_GATT_REGISTER_OP_CHR
     *     o BLE_GATT_REGISTER_OP_DSC
     */
    uint8_t op;

    /**
     * The value of the op field determines which field in this union is valid.
     */
    union {
        /** Service; valid if op == BLE_GATT_REGISTER_OP_SVC. */
        struct {
            /** The ATT handle of the service definition attribute. */
            uint16_t handle;

            /**
             * The service definition representing the service being
             * registered.
             */
            const struct ble_gatt_svc_def *svc_def;
        } svc;

        /** Characteristic; valid if op == BLE_GATT_REGISTER_OP_CHR. */
        struct {
            /** The ATT handle of the characteristic definition attribute. */
            uint16_t def_handle;

            /** The ATT handle of the characteristic value attribute. */
            uint16_t val_handle;

            /**
             * The characteristic definition representing the characteristic
             * being registered.
             */
            const struct ble_gatt_chr_def *chr_def;

            /**
             * The service definition corresponding to the characteristic's
             * parent service.
             */
            const struct ble_gatt_svc_def *svc_def;
        } chr;

        /** Descriptor; valid if op == BLE_GATT_REGISTER_OP_DSC. */
        struct {
            /** The ATT handle of the descriptor definition attribute. */
            uint16_t handle;

            /**
             * The descriptor definition corresponding to the descriptor being
             * registered.
             */
            const struct ble_gatt_dsc_def *dsc_def;

            /**
             * The characteristic definition corresponding to the descriptor's
             * parent characteristic.
             */
            const struct ble_gatt_chr_def *chr_def;

            /**
             * The service definition corresponding to the descriptor's
             * grandparent service
             */
            const struct ble_gatt_svc_def *svc_def;
        } dsc;
    };
};

/**
 * Contains counts of resources required by the GATT server.  The contents of
 * this struct are generally used to populate a configuration struct before
 * the host is initialized.
 */
struct ble_gatt_resources {
    /** Number of services. */
    uint16_t svcs;

    /** Number of included services. */
    uint16_t incs;

    /** Number of characteristics. */
    uint16_t chrs;

    /** Number of descriptors. */
    uint16_t dscs;

    /**
     * Number of client characteristic configuration descriptors.  Each of
     * these also contributes to the total descriptor count.
     */
    uint16_t cccds;

    /** Total number of ATT attributes. */
    uint16_t attrs;
};

typedef void ble_gatt_register_fn(struct ble_gatt_register_ctxt *ctxt,
                                  void *arg);

int ble_gatts_register_svcs(const struct ble_gatt_svc_def *svcs,
                            ble_gatt_register_fn *register_cb,
                            void *cb_arg);
int ble_gatts_add_svcs(const struct ble_gatt_svc_def *svcs);
int ble_gatts_count_resources(const struct ble_gatt_svc_def *svcs,
                              struct ble_gatt_resources *res);
int ble_gatts_count_cfg(const struct ble_gatt_svc_def *defs);

void ble_gatts_chr_updated(uint16_t chr_def_handle);

int ble_gatts_find_svc(const ble_uuid_t *uuid, uint16_t *out_handle);
int ble_gatts_find_chr(const ble_uuid_t *svc_uuid, const ble_uuid_t *chr_uuid,
                       uint16_t *out_def_handle, uint16_t *out_val_handle);
int ble_gatts_find_dsc(const ble_uuid_t *svc_uuid, const ble_uuid_t *chr_uuid,
                       const ble_uuid_t *dsc_uuid, uint16_t *out_dsc_handle);


struct ble_att_read_type_adata;
struct ble_att_find_type_value_hinfo;
struct ble_att_find_info_idata;
struct ble_att_read_group_type_adata;
struct ble_att_prep_write_cmd;

#define BLE_GATT_CHR_DECL_SZ_16     5
#define BLE_GATT_CHR_DECL_SZ_128    19
typedef uint8_t ble_gatts_conn_flags;

struct ble_gatts_conn {
    struct ble_gatts_clt_cfg *clt_cfgs;
    int num_clt_cfgs;

    uint16_t indicate_val_handle;
};


#ifdef __cplusplus
}
#endif
#endif // _BLE_GATT_H_
