// Define here what components you want for this platform
// Also used for compile-time configuration constants (like TCP/IP config)

#ifndef __BUILD_H__
#define __BUILD_H__

#define BUILD_XMODEM
#define BUILD_SHELL
#define BUILD_ROMFS
#define BUILD_TERM
#define BUILD_UIP
#define BUILD_CON_GENERIC
//#define BUILD_CON_TCP

// Static TCP/IP configuration
#define ELUA_IPADDR0         192
#define ELUA_IPADDR1         168
#define ELUA_IPADDR2         1
#define ELUA_IPADDR3         13
#define ELUA_NETMASK0        255
#define ELUA_NETMASK1        255
#define ELUA_NETMASK2        255
#define ELUA_NETMASK3        0

#endif