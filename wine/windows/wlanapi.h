/*
 * Copyright (C) 2016 Austin English
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

#ifndef _WLAN_WLANAPI_H
#define _WLAN_WLANAPI_H

typedef enum _WLAN_INTERFACE_STATE
{
    wlan_interface_state_not_ready,
    wlan_interface_state_connected,
    wlan_interface_state_ad_hoc_network_formed,
    wlan_interface_state_disconnecting,
    wlan_interface_state_disconnected,
    wlan_interface_state_associating,
    wlan_interface_state_discovering,
    wlan_interface_state_authenticating
} WLAN_INTERFACE_STATE, *PWLAN_INTERFACE_STATE;

typedef struct _WLAN_INTERFACE_INFO
{
    GUID InterfaceGuid;
    WCHAR strInterfaceDescription[256];
    WLAN_INTERFACE_STATE isState;
} WLAN_INTERFACE_INFO, *PWLAN_INTERFACE_INFO;

typedef struct _WLAN_INTERFACE_INFO_LIST
{
    DWORD dwNumberOfItems;
    DWORD dwIndex;
    WLAN_INTERFACE_INFO InterfaceInfo[1];
} WLAN_INTERFACE_INFO_LIST, *PWLAN_INTERFACE_INFO_LIST;

#define DOT11_SSID_MAX_LENGTH 32
typedef struct _DOT11_SSID
{
    DWORD uSSIDLength;
    UCHAR ucSSID[DOT11_SSID_MAX_LENGTH];
} DOT11_SSID;

typedef struct _WLAN_RAW_DATA
{
    DWORD dwDataSize;
    BYTE DataBlob[1];
} WLAN_RAW_DATA, *PWLAN_RAW_DATA;

typedef struct _WLAN_NOTIFICATION_DATA
{
    DWORD NotificationSource;
    DWORD NotificationCode;
    GUID InterfaceGuid;
    DWORD dwDataSize;
    PVOID pData;
} WLAN_NOTIFICATION_DATA, *PWLAN_NOTIFICATION_DATA;

typedef void (WINAPI *WLAN_NOTIFICATION_CALLBACK)(WLAN_NOTIFICATION_DATA *, void *);

DWORD WINAPI WlanCloseHandle(HANDLE, void *);
DWORD WINAPI WlanEnumInterfaces(HANDLE, void *, WLAN_INTERFACE_INFO_LIST **);
DWORD WINAPI WlanOpenHandle(DWORD, void *, DWORD *, HANDLE *);
void *WINAPI WlanAllocateMemory(DWORD);
void WINAPI WlanFreeMemory(void *);
DWORD WINAPI WlanScan(HANDLE, const GUID *, const DOT11_SSID *, const WLAN_RAW_DATA *, void *);
DWORD WINAPI WlanRegisterNotification(HANDLE, DWORD, BOOL, WLAN_NOTIFICATION_CALLBACK, void *, void *, DWORD *);

#endif /* _WLAN_WLANAPI_H */
