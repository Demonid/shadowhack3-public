/*
 * Copyright (C) 2010-2011 Izb00shka <http://izbooshka.net/>
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

#ifndef _MOVE_MAP_H
#define _MOVE_MAP_H

#include "DetourAlloc.h"
#include "DetourNavMesh.h"
#include "DetourNavMeshQuery.h"

/*  memory management  */

inline void* dtCustomAlloc(int size, dtAllocHint /*hint*/)
{
    return (void*)new unsigned char[size];
}

inline void dtCustomFree(void* ptr)
{
    delete [] (unsigned char*)ptr;
}

//  move map related classes
namespace MMAP
{
    typedef UNORDERED_MAP<uint32, dtTileRef> MMapTileSet;

    // dummy struct to hold map's mmap data
    struct MMapData
    {
        MMapData(dtNavMesh* mesh, dtNavMeshQuery* query) : navMesh(mesh), navMeshQuery(query) {}
        ~MMapData()
        {
            if(navMeshQuery)
                dtFreeNavMeshQuery(navMeshQuery);

            if (navMesh)
                dtFreeNavMesh(navMesh);
        }

        dtNavMesh* navMesh;
        dtNavMeshQuery* navMeshQuery;
        MMapTileSet mmapLoadedTiles;    // maps [map grid coords] to [dtTile]
    };


    typedef UNORDERED_MAP<uint32, MMapData*> MMapDataSet;

    // singelton class
    // holds all all access to mmap loading unloading and meshes
    class MMapManager
    {
        public:
            MMapManager(){}
            ~MMapManager();

            bool loadMap(uint32 mapId, int32 x, int32 y);
            bool unloadMap(uint32 mapId, int32 x, int32 y);
            bool unloadMap(uint32 mapId);

            dtNavMesh const* GetNavMesh(uint32 mapId);
            dtNavMeshQuery const* GetNavMeshQuery(uint32 mapId);

            // TODO: add statistics functions here
        private:
            bool loadMapData(uint32 mapId);
            uint32 packTileID(int32 x, int32 y);

            MMapDataSet loadedMMaps;
    };

    // static class
    // holds all mmap global data
    // access point to MMapManager singelton
    class MMapFactory
    {
        public:
            static MMapManager* createOrGetMMapManager();
            static void clear();
            static void preventPathfindingOnMaps(const char* ignoreMapIds);
            static bool IsPathfindingEnabled(uint32 mapId);
    };
}

#endif  // _MOVE_MAP_H
