/****************************************************************************************
 *
 * @file ble_att_common.h
 *
 * @brief This file contains the definition of the os environment.
 *
 * Copyright (C) Verisilicon 2018-2024
 *
 *
 ****************************************************************************************
 */
#ifndef _BLE_ATT_COMMON_H_
#define _BLE_ATT_COMMON_H_

#include <inttypes.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
//These error code is system level, could be placed in a complete common define place.
*/
#define BLE_HS_EAGAIN               1
#define BLE_HS_EALREADY             2
#define BLE_HS_EINVAL               3
#define BLE_HS_EMSGSIZE             4
#define BLE_HS_ENOENT               5
#define BLE_HS_ENOMEM               6
#define BLE_HS_ENOTCONN             7
#define BLE_HS_ENOTSUP              8
#define BLE_HS_EAPP                 9
#define BLE_HS_EBADDATA             10
#define BLE_HS_EOS                  11
#define BLE_HS_ECONTROLLER          12
#define BLE_HS_ETIMEOUT             13
#define BLE_HS_EDONE                14
#define BLE_HS_EBUSY                15
#define BLE_HS_EREJECT              16
#define BLE_HS_EUNKNOWN             17
#define BLE_HS_EROLE                18
#define BLE_HS_ETIMEOUT_HCI         19
#define BLE_HS_ENOMEM_EVT           20
#define BLE_HS_ENOADDR              21
#define BLE_HS_ENOTSYNCED           22
#define BLE_HS_EAUTHEN              23
#define BLE_HS_EAUTHOR              24
#define BLE_HS_EENCRYPT             25
#define BLE_HS_EENCRYPT_KEY_SZ      26


/*
 * Singly-linked Tail queue declarations.
 */
#define	STAILQ_HEAD(name, type)						\
struct name {								\
	struct type *stqh_first;/* first element */			\
	struct type **stqh_last;/* addr of last next element */		\
}

#define	STAILQ_HEAD_INITIALIZER(head)					\
	{ NULL, &(head).stqh_first }

#define	STAILQ_ENTRY(type)						\
struct {								\
	struct type *stqe_next;	/* next element */			\
}

/*
 * Singly-linked Tail queue functions.
 */
#define	STAILQ_EMPTY(head)	((head)->stqh_first == NULL)

#define	STAILQ_FIRST(head)	((head)->stqh_first)

#define	STAILQ_FOREACH(var, head, field)				\
	for((var) = STAILQ_FIRST((head));				\
	   (var);							\
	   (var) = STAILQ_NEXT((var), field))

#define	STAILQ_INIT(head) do {						\
	STAILQ_FIRST((head)) = NULL;					\
	(head)->stqh_last = &STAILQ_FIRST((head));			\
} while (0)

#define	STAILQ_INSERT_AFTER(head, tqelm, elm, field) do {		\
	if ((STAILQ_NEXT((elm), field) = STAILQ_NEXT((tqelm), field)) == NULL)\
		(head)->stqh_last = &STAILQ_NEXT((elm), field);		\
	STAILQ_NEXT((tqelm), field) = (elm);				\
} while (0)

#define	STAILQ_INSERT_HEAD(head, elm, field) do {			\
	if ((STAILQ_NEXT((elm), field) = STAILQ_FIRST((head))) == NULL)	\
		(head)->stqh_last = &STAILQ_NEXT((elm), field);		\
	STAILQ_FIRST((head)) = (elm);					\
} while (0)

#define	STAILQ_INSERT_TAIL(head, elm, field) do {			\
	STAILQ_NEXT((elm), field) = NULL;				\
	*(head)->stqh_last = (elm);					\
	(head)->stqh_last = &STAILQ_NEXT((elm), field);			\
} while (0)

#define	STAILQ_LAST(head, type, field)					\
	(STAILQ_EMPTY(head) ?						\
		NULL :							\
	        ((struct type *)					\
		((char *)((head)->stqh_last) - offsetof(struct type, field))))

#define	STAILQ_NEXT(elm, field)	((elm)->field.stqe_next)

#define	STAILQ_REMOVE(head, elm, type, field) do {			\
	if (STAILQ_FIRST((head)) == (elm)) {				\
		STAILQ_REMOVE_HEAD(head, field);			\
	}								\
	else {								\
		struct type *curelm = STAILQ_FIRST((head));		\
		while (STAILQ_NEXT(curelm, field) != (elm))		\
			curelm = STAILQ_NEXT(curelm, field);		\
		if ((STAILQ_NEXT(curelm, field) =			\
		     STAILQ_NEXT(STAILQ_NEXT(curelm, field), field)) == NULL)\
			(head)->stqh_last = &STAILQ_NEXT((curelm), field);\
	}								\
} while (0)

#define	STAILQ_REMOVE_HEAD(head, field) do {				\
	if ((STAILQ_FIRST((head)) =					\
	     STAILQ_NEXT(STAILQ_FIRST((head)), field)) == NULL)		\
		(head)->stqh_last = &STAILQ_FIRST((head));		\
} while (0)

#define	STAILQ_REMOVE_HEAD_UNTIL(head, elm, field) do {			\
	if ((STAILQ_FIRST((head)) = STAILQ_NEXT((elm), field)) == NULL)	\
		(head)->stqh_last = &STAILQ_FIRST((head));		\
} while (0)

#define STAILQ_REMOVE_AFTER(head, elm, field) do {			\
	if ((STAILQ_NEXT(elm, field) =					\
	     STAILQ_NEXT(STAILQ_NEXT(elm, field), field)) == NULL)	\
		(head)->stqh_last = &STAILQ_NEXT((elm), field);		\
} while (0)



/*
 * Ble-UUID  declarations.
 */
enum {
    BLE_UUID_TYPE_16 = 16,
    BLE_UUID_TYPE_32 = 32,
    BLE_UUID_TYPE_128 = 128,
};

/* Generic UUID type, to be used only as a pointer */
typedef struct {
    uint8_t type;
} ble_uuid_t;

typedef struct {
    ble_uuid_t u;
    uint16_t value;
} ble_uuid16_t;

typedef struct {
    ble_uuid_t u;
    uint32_t value;
} ble_uuid32_t;

typedef struct {
    ble_uuid_t u;
    uint8_t value[16];
} ble_uuid128_t;

/* Universal UUID type, to be used for any-UUID static allocation */
typedef union {
    ble_uuid_t u;
    ble_uuid16_t u16;
    ble_uuid32_t u32;
    ble_uuid128_t u128;
} ble_uuid_any_t;

#define BLE_UUID16_INIT(uuid16)         \
    {                                   \
        .u.type = BLE_UUID_TYPE_16,     \
        .value = (uuid16),              \
    }

#define BLE_UUID32_INIT(uuid32)         \
    {                                   \
        .u.type = BLE_UUID_TYPE_32,     \
        .value = (uuid32),              \
    }

#define BLE_UUID128_INIT(uuid128...)    \
    {                                   \
        .u.type = BLE_UUID_TYPE_128,    \
        .value = { uuid128 },           \
    }

#define BLE_UUID16_DECLARE(uuid16) \
    ((ble_uuid_t *) (&(ble_uuid16_t) BLE_UUID16_INIT(uuid16)))

#define BLE_UUID32_DECLARE(uuid32) \
    ((ble_uuid_t *) (&(ble_uuid32_t) BLE_UUID32_INIT(uuid32)))

#define BLE_UUID128_DECLARE(uuid128...) \
    ((ble_uuid_t *) (&(ble_uuid128_t) BLE_UUID128_INIT(uuid128)))

#define BLE_UUID16(u) \
    ((ble_uuid16_t *) (u))

#define BLE_UUID32(u) \
    ((ble_uuid32_t *) (u))

#define BLE_UUID128(u) \
    ((ble_uuid128_t *) (u))

#define BLE_UUID_STR_LEN (37)

#define MAX_HANDLE_ID (0xFFFF)

int ble_uuid_init_from_buf(ble_uuid_any_t *uuid, const void *buf, size_t len);
int ble_uuid_cmp(const ble_uuid_t *uuid1, const ble_uuid_t *uuid2);
char *ble_uuid_to_str(const ble_uuid_t *uuid, char *dst);
uint16_t ble_uuid_u16(const ble_uuid_t *uuid);
int ble_uuid_to_any(const ble_uuid_t *uuid, ble_uuid_any_t *uuid_any);
int ble_uuid_length(const ble_uuid_t *uuid);
#ifdef __cplusplus
}
#endif
