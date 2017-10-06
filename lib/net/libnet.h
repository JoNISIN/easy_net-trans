#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0501
#endif

#include <windows.h>
#include <winsock2.h>
#include <Ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma comment(lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#ifndef DEFAULT_PORT
#define DEFAULT_PORT "9900"
#endif

#ifndef BYTE_DEF
#define BYTE_DEF
typedef unsigned char Byte;
#endif

SOCKET StartUpServer(int mode);
SOCKET StartUpClient(char *net_addr,int mode);
int send_to(SOCKET sock,void *obj,int BYTE_LEN);
int read_from(SOCKET sock,void *obj_buf,int BYTE_LEN);