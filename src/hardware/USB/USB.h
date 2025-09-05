#pragma once
#include <stdint.h>


// This is super hard to figure out and youll never belive what it does (I defines speeds)
typedef enum {
    USB_SPEED_LOW  = 1,
    USB_SPEED_FULL = 2,
    USB_SPEED_HIGH = 3,
    USB_SPEED_SUPER = 4,
} usb_speed_t;

typedef struct {
    uint8_t  address;      // 1..127
    uint16_t vid, pid;
    usb_speed_t speed;
} usb_device_t;

// Standard requests we’ll use
#define USB_REQ_GET_DESCRIPTOR  0x06
#define USB_DT_DEVICE           0x01
#define USB_DT_CONFIG           0x02

// Setup packet (8 bytes)
typedef struct {
    uint8_t  bmRequestType;
    uint8_t  bRequest;
    uint16_t wValue;
    uint16_t wIndex;
    uint16_t wLength;
} __attribute__((packed)) usb_setup_t;
//someone find out why it is expecting a ";" when there is one

// Why are USB so complicated?

//Made this file cause I was bored in class this doesnt mean im doing anything with USB cause im lazy
//I need instant gratification

// This is from USB 3.0 spec
