/*
 * Copyright (C) 2005-2010 MaNGOS <http://getmangos.com/>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef _PROTOCOL_H
#define _PROTOCOL_H

enum eWardendOpcode
{
    MMSG_REGISTER                   = 0x01,
    //  uint32  accountId;
    WMSG_REGISTER_REPLY             = 0x02,
    //  uint32  accountId;
    //  uint32  moduleLen
    //  if (moduleLen!=0)
    //      uint8 rc4[16];
    //      uint8 md5[16];
    MMSG_UNREGISTER                 = 0x03,
    //  uint32  accountId;
    MMSG_SERVER_KEY_REQUEST         = 0x04,
    //  uint32  accountId;
    //  uint8   sessionKey[40];
    //  uint8   seedRequestPacket[17]; // full packet
    WMSG_SERVER_KEY_REPLY           = 0x05,
    //  uint32  accountId;
    //  uint8   serverKey[208];
    MMSG_CLIENT_KEY_REQUEST         = 0x06,
    //  uint32  accountId;
    WMSG_CLIENT_KEY_REPLY           = 0x07,
    //  uint32  accountId;
    //  uint8   clientKey[208];
    MMSG_CHEATS_REQUEST             = 0x08,
    //  uint32  accountId;
    WMSG_CHEATS_REPLY               = 0x09,
    //  uint32  accountId;
    //  uint32  packetSize;
    //  uint8   clientCheatCheckPacket[packetSize]; // full packet
    MMSG_CHEATS_VALIDATION_REQUEST  = 0x0A,
    //  uint32  accountId;
    //  uint32  packetSize;
    //  uint8   clientCheatCheckResultPacket[packetSize]; // full packet
    WMSG_CHEATS_VALIDATION_REPLY    = 0x0B,
    //  uint32  accountId;
    //  uint8   result; // bool 0=failed, 1=success
    MMSG_MODULEFILE_REQUEST         = 0x0C,
    //  uint32  accountId;
    WMSG_MODULEFILE_REPLY           = 0x0D,
    //  uint32  accountId;
    //  uint16  moduleLen;
    //  uint8   module[moduleLen];
    MMSG_TSEED_VALIDATION_REQUEST   = 0x0E,
    // uint32  accountId;
    // uint8   tSeed[20];
    WMGS_TSEED_VALIDATION_REPLY     = 0x0F
    // uint32   accountId;
    // uint8    result; // bool 0=failed, 1=success
};

enum eWardenServerCmd
{
    WARDS_MODULE_INFO               = 0x0,
    WARDS_MODULE_CHUNK              = 0x1,
    WARDS_CHEAT_CHECK               = 0x2,
    WARDS_DATA                      = 0x3,

    WARDS_SEED                      = 0x5
};

enum eWardenClientCmd
{
    WARDC_MODULE_LOAD_FAILED        = 0x0,
    WARDC_MODULE_LOADED             = 0x1,
    WARDC_CHEAT_CHECK_RESULT        = 0x2,

    WARDC_TRANSFORMED_SEED          = 0x4
};

enum eWardenClientStatus
{
    WARD_STATUS_UNREGISTERED,
    WARD_STATUS_REGISTERED,
    WARD_STATUS_INIT,
    WARD_STATUS_LOAD_FAILED,
    WARD_STATUS_CHEAT_CHECK_IN,
    WARD_STATUS_CHEAT_CHECK_PENDING,
    WARD_STATUS_CHEAT_CHECK_OUT,
};

enum eWardenCheckType
{
    WARD_CHECK_MEMORY               = 0,
    WARD_CHECK_PAGE1                = 1,
    WARD_CHECK_PAGE2                = 2,
    WARD_CHECK_FILE                 = 3,
    WARD_CHECK_LUA                  = 4,
    WARD_CHECK_DRIVER               = 5,
    WARD_CHECK_TIMING               = 6,
    WARD_CHECK_PROCESS              = 7,
    WARD_CHECK_MODULE               = 8,
    WARD_CHECK_END                  = 9
};

#define WARDEND_SIGN "izbwrd"
#endif
