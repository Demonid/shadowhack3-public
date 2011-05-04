/*
 * Copyright (C) 2010-2011 Izb00shka <http://izbooshka.net/>
 * Copyright (C) 2008 - 2010 Trinity <http://www.trinitycore.org/>
 *
 * Copyright (C) 2010 Myth Project <http://bitbucket.org/sun/myth-core/>
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

#include "OutdoorPvPWG.h"
#include "SpellAuras.h"
#include "Vehicle.h"
#include "ObjectMgr.h"
#include "Group.h"
#include "Chat.h"
#include "MapManager.h"
#include "ScriptedCreature.h"
#include "ScriptPCH.h"
#include "GameEventMgr.h"

Creature* FortressSpirit;
uint32 entry;
uint32 guide_entry;
uint32 guide_entry_fortress_horde;
uint32 guide_entry_fortress_alliance;

/* Vehicle teleport system*/
Map* pMap;

OutdoorPvPWG::OutdoorPvPWG()
{
    m_TypeId = OUTDOOR_PVP_WG;
    m_LastResurrectTime = 0; // Temporal copy of BG system till 3.2
}

void _RespawnCreatureIfNeeded(Creature *cr, uint32 entry)
{
    if (cr)
    {
        cr->UpdateEntry(entry); // SetOriginalEntry as used before may lead to crash
        if (entry != cr->GetEntry() || !cr->isAlive())
            cr->Respawn(true);
        cr->SetVisible(true);
    }
}

void OutdoorPvPWG::SaveData()
{

    SetControllingTeamId(isWarTime() ? TEAM_NEUTRAL : m_defender);
    sWorld->setWorldState(WS_WINTERGRASP_DEFENDER_TEAMID, uint64(m_defender));
    sWorld->setWorldState(WS_WINTERGRASP_CLOCK_ALLY, m_clock[TEAM_ALLIANCE]);
    sWorld->setWorldState(WS_WINTERGRASP_CLOCK_HORDE, m_clock[TEAM_HORDE]);
    sWorld->setWorldState(WS_WINTERGRASP_ISWAR, uint64(m_wartime));
    sWorld->setWorldState(WS_WINTERGRASP_TIMER, m_timer);

    // TODO: Until the team/state is at startup correct set (not implemented yet) we must set 0 here!
    /*sWorld->setWorldState(WS_WINTERGRASP_SHOP_CNT_ALLY, uint64(m_workshopCount[TEAM_ALLIANCE]));
    sWorld->setWorldState(WS_WINTERGRASP_SHOP_CNT_HORDE, uint64(m_workshopCount[TEAM_HORDE]));
    sWorld->setWorldState(WS_WINTERGRASP_TOWER_DEST_ALLY, uint64(m_towerDestroyedCount[TEAM_ALLIANCE]));
    sWorld->setWorldState(WS_WINTERGRASP_TOWER_DEST_HORDE, uint64(m_towerDestroyedCount[TEAM_HORDE]));
    sWorld->setWorldState(WS_WINTERGRASP_VEHICLE_CNT_ALLY, uint64(m_VehicleCnt[TEAM_ALLIANCE]));
    sWorld->setWorldState(WS_WINTERGRASP_VEHICLE_CNT_HORDE, uint64(m_VehicleCnt[TEAM_HORDE]));*/

    sWorld->setWorldState(WS_WINTERGRASP_SHOP_CNT_ALLY, uint64(0));
    sWorld->setWorldState(WS_WINTERGRASP_SHOP_CNT_HORDE, uint64(0));
    sWorld->setWorldState(WS_WINTERGRASP_TOWER_DEST_ALLY, uint64(0));
    sWorld->setWorldState(WS_WINTERGRASP_TOWER_DEST_HORDE, uint64(0));
    sWorld->setWorldState(WS_WINTERGRASP_VEHICLE_CNT_ALLY, uint64(0));
    sWorld->setWorldState(WS_WINTERGRASP_VEHICLE_CNT_HORDE, uint64(0));

    m_saveinterval = WG_MIN_SAVE;
}

void OutdoorPvPWG::LoadData()
{
    m_wartime                                     = sWorld->getWorldState(WS_WINTERGRASP_ISWAR);
    m_defender                                    = (TeamId)sWorld->getWorldState(WS_WINTERGRASP_DEFENDER_TEAMID);
    m_clock[TEAM_ALLIANCE]                        = sWorld->getWorldState(WS_WINTERGRASP_CLOCK_ALLY);
    m_clock[TEAM_HORDE]                           = sWorld->getWorldState(WS_WINTERGRASP_CLOCK_HORDE);    
    m_timer                                       = sWorld->getWorldState(WS_WINTERGRASP_TIMER);

    if (m_defender == TEAM_NEUTRAL)
    {
        if (!isWarTime() && GetControllingTeamID() != TEAM_NEUTRAL)
        {
            m_defender = GetControllingTeamID();
        }
        else
        {
            m_defender = TeamId(rand()%2);
        }
    }

    if (m_defender != GetControllingTeamID())
    {
        if (!isWarTime())
        {
            if (GetControllingTeamID() == TEAM_NEUTRAL)
                SetControllingTeamId(m_defender);
        }
    }

    if (isWarTime() && GetControllingTeamID() != TEAM_NEUTRAL)
        SetControllingTeamId(TEAM_NEUTRAL);

    SpawnDefenders();

    m_workshopCount[TEAM_ALLIANCE] = 0;
    m_workshopCount[TEAM_HORDE] = 0;
    m_towerDestroyedCount[TEAM_ALLIANCE] = 0;
    m_towerDestroyedCount[TEAM_HORDE] = 0;
    m_towerDamagedCount[TEAM_ALLIANCE] = 0;
    m_towerDamagedCount[TEAM_HORDE] = 0;
}

bool OutdoorPvPWG::SetupOutdoorPvP()
{
    StopAllWGEvents();

    if (!sWorld->getBoolConfig(CONFIG_OUTDOORPVP_WINTERGRASP_ENABLED))
    {
        SetControllingTeamId(TEAM_NEUTRAL);
        return true;
    }

    LoadData();

    m_changeDefender = false;

    m_tenacityStack = 0;
    m_gate = NULL;

    timer_30m = false;
    timer_10m = false;

    std::list<uint32> engGuids;
    std::list<uint32> spiritGuids;

    // Store Eng, spirit guide guids and questgiver for later use
    QueryResult result = WorldDatabase.PQuery("SELECT guid, id FROM creature WHERE map = 571"
        " AND id IN (%u, %u, %u, %u);",
        CRE_ENG_A, CRE_ENG_H, CRE_SPI_A, CRE_SPI_H);
    if (!result)
    {
        sLog->outError("Cannot find siege workshop master or spirit guides in creature!");
        return false;
    }
    else
    {
        do
        {
            Field *fields = result->Fetch();
            switch(fields[1].GetUInt32())
            {
                case CRE_ENG_A:
                case CRE_ENG_H:
                    engGuids.push_back(fields[0].GetUInt32());
                    break;
                case CRE_SPI_A:
                case CRE_SPI_H:
                    spiritGuids.push_back(fields[0].GetUInt32());
                    break;
                default:
                    break;
            }
        }
        while(result->NextRow());
    }

    // Select POI
    AreaPOIList areaPOIs;
    float minX = 9999, minY = 9999, maxX = -9999, maxY = -9999;
    for (uint32 i = 0; i < sAreaPOIStore.GetNumRows(); ++i)
    {
        const AreaPOIEntry * poiInfo = sAreaPOIStore.LookupEntry(i);
        if (poiInfo && poiInfo->zoneId == ZONE_WINTERGRASP)
        {
            areaPOIs.push_back(poiInfo);
            if (minX > poiInfo->x) minX = poiInfo->x;
            if (minY > poiInfo->y) minY = poiInfo->y;
            if (maxX < poiInfo->x) maxX = poiInfo->x;
            if (maxY < poiInfo->y) maxY = poiInfo->y;
        }
    }
    minX -= 20; minY -= 20; maxX += 20; maxY += 20;

    // Coords: 4290.330078, 1790.359985 - 5558.379883, 4048.889893
    result = WorldDatabase.PQuery("SELECT guid FROM gameobject, gameobject_template"
        " WHERE gameobject.map=571"
        " AND gameobject.position_x>%f AND gameobject.position_y>%f"
        " AND gameobject.position_x<%f AND gameobject.position_y<%f"
        " AND gameobject_template.type=33"
        " AND gameobject.id=gameobject_template.entry",
        minX, minY, maxX, maxY);

    if (!result)
    {
        sLog->outError("Cannot find WG gameobjects!");
        return false;
    }
    do
    {
        Field *fields = result->Fetch();

        uint32 guid = fields[0].GetUInt32();
        GameObjectData const * goData = sObjectMgr->GetGOData(guid);
        if (!goData) // this should not happen
            continue;

        float x = goData->posX, y = goData->posY;
        float minDist = 100;
        AreaPOIList::iterator poi = areaPOIs.end();
        for (AreaPOIList::iterator itr = areaPOIs.begin(); itr != areaPOIs.end(); ++itr)
        {
            if (!(*itr)->icon[1]) // note: may for other use
                continue;

            float dist = (abs((*itr)->x - x) + abs((*itr)->y - y));
            if (minDist > dist)
            {
                minDist = dist;
                poi = itr;
            }
        }

        if (poi == areaPOIs.end())
            continue;

        // add building to the list
        TeamId teamId = x > POS_X_CENTER-300 ? getDefenderTeam() : getAttackerTeam();
        m_buildingStates[guid] = new BuildingState((*poi)->worldState, teamId, getDefenderTeam() != TEAM_ALLIANCE);

        if ((*poi)->id == 2246)
            m_gate = m_buildingStates[guid];

        areaPOIs.erase(poi);

        // add capture point
        uint32 capturePointEntry = 0;

        switch(goData->id)
        {    
            //West Goblin Workshops
            case 192028: // NW
            case 192030: // W
            case 192032: // SW
                capturePointEntry = 190475;
                break;
            //East Goblin Workshops
            case 192029: // NE
            case 192031: // E
            case 192033: // SE
                capturePointEntry = 190487;
                break;
        }

        if (capturePointEntry)
        {
            uint32 engGuid = 0;
            uint32 spiritGuid = 0;
            // Find closest Eng to Workshop
            float minDist = 100;
            for (std::list<uint32>::iterator itr = engGuids.begin(); itr != engGuids.end(); ++itr)
            {
                if (const CreatureData *creData = sObjectMgr->GetCreatureData(*itr))
                {
                    float dist = (abs(creData->posX - x) + abs(creData->posY - y));
                    if (minDist > dist)
                    {
                        minDist = dist;
                        engGuid = *itr;
                    }
                }
            }

            if (!engGuid)
            {
                sLog->outError("Cannot find nearby siege workshop master!");
                continue;
            }
            else
                engGuids.remove(engGuid);

            // Find closest Spirit Guide to Workshop
            minDist = 255;
            for (std::list<uint32>::iterator itr = spiritGuids.begin(); itr != spiritGuids.end(); ++itr)
            {
                if (const CreatureData *creData = sObjectMgr->GetCreatureData(*itr))
                {
                    float dist = (abs(creData->posX - x) + abs(creData->posY - y));
                    if (minDist > dist)
                    {
                        minDist = dist;
                        spiritGuid = *itr;
                    }
                }
            }

            // Inside fortress won't be capturable
            OPvPCapturePointWG *workshop = new OPvPCapturePointWG(this, m_buildingStates[guid]);
            if (goData->posX < POS_X_CENTER && 
                !workshop->SetCapturePointData(capturePointEntry, goData->mapid,
                    goData->posX + 40 * cos(goData->orientation + M_PI * 0.5f), goData->posY + 40 * sin(goData->orientation + M_PI * 0.5f), goData->posZ))
            {
                delete workshop;
                sLog->outError("Cannot add capture point!");
                continue;
            }

            // West fortress Workshop fix
            if(goData->id == 192028 || goData->id == 192029)
                workshop->m_capturePointGUID = goData->id;

            const CreatureData *creData = sObjectMgr->GetCreatureData(engGuid);
            if (!creData)
                continue;

            workshop->m_engEntry = const_cast<uint32*>(&creData->id);
            workshop->m_engGuid = engGuid;

            // Back spirit is linked to one of the inside workshops, 1 workshop wont have spirit
            if (spiritGuid)
            {
                spiritGuids.remove(spiritGuid);

                const CreatureData *spiritData = sObjectMgr->GetCreatureData(spiritGuid);
                if (!spiritData)
                    continue;

                workshop->m_spiEntry = const_cast<uint32*>(&spiritData->id);
                workshop->m_spiGuid = spiritGuid;
            }
            else
                workshop->m_spiGuid = 0;

            workshop->m_workshopGuid = guid;
            AddCapturePoint(workshop);
            m_buildingStates[guid]->type = BUILDING_WORKSHOP;
            workshop->SetTeamByBuildingState();
        }
    }
    while(result->NextRow());

    engGuids.clear();
    spiritGuids.clear();

    if (!m_gate)
    {
        sLog->outError("Cannot find wintergrasp fortress gate!");
        return false;
    }

    // Load Graveyard
    GraveYardMap::const_iterator graveLow  = sObjectMgr->mGraveYardMap.lower_bound(ZONE_WINTERGRASP);
    GraveYardMap::const_iterator graveUp   = sObjectMgr->mGraveYardMap.upper_bound(ZONE_WINTERGRASP);
    for (AreaPOIList::iterator itr = areaPOIs.begin(); itr != areaPOIs.end();)
    {
        if ((*itr)->icon[1] == 8)
        {
            // find or create grave yard
            const WorldSafeLocsEntry *loc = sObjectMgr->GetClosestGraveYard((*itr)->x, (*itr)->y, (*itr)->z, (*itr)->mapId, 0);
            if (!loc)
            {
                ++itr;
                continue;
            }

            GraveYardMap::const_iterator graveItr;
            for (graveItr = graveLow; graveItr != graveUp; ++graveItr)
                if (graveItr->second.safeLocId == loc->ID)
                    break;

            if (graveItr == graveUp)
            {
                GraveYardData graveData;
                graveData.safeLocId = loc->ID;
                graveData.team = 0;
                graveItr = sObjectMgr->mGraveYardMap.insert(std::make_pair(ZONE_WINTERGRASP, graveData));
            }

            for (BuildingStateMap::iterator stateItr = m_buildingStates.begin(); stateItr != m_buildingStates.end(); ++stateItr)
            {
                if (stateItr->second->worldState == (*itr)->worldState)
                {
                    stateItr->second->graveTeam = const_cast<uint32*>(&graveItr->second.team);
                    break;
                }
            }
            areaPOIs.erase(itr++);
        }
        else
            ++itr;
    }

    //Titan Relic
    sObjectMgr->AddGOData(192829, 571, 5440.0f, 2840.8f, 420.43f + 10.0f, 0);

    if (!m_timer)
        m_timer = sWorld->getIntConfig(CONFIG_OUTDOORPVP_WINTERGRASP_START_TIME) * MINUTE * IN_MILLISECONDS;

    m_saveinterval = WG_MIN_SAVE;

    UpdateAllWorldObject();

    sWorld->SendWintergraspState();

    if (!isWarTime())
        RemoveOfflinePlayerWGAuras();

    RegisterZone(ZONE_WINTERGRASP);

    return true;
}

void OutdoorPvPWG::ProcessEvent(GameObject *obj, uint32 eventId)
{     
    if (!obj)
        return;

    if (obj->GetEntry() == 192829) // Titan Relic
    {
        if (obj->GetGOInfo()->goober.eventId == eventId && isWarTime() && m_gate &&  m_gate->damageState == DAMAGE_DESTROYED)
        {
            m_changeDefender = true;
            m_timer = 0;
        }
    }
    else if (obj->GetGoType() == GAMEOBJECT_TYPE_DESTRUCTIBLE_BUILDING)
    {
        BuildingStateMap::const_iterator itr = m_buildingStates.find(obj->GetDBTableGUIDLow());
        if (itr == m_buildingStates.end())
            return;
        std::string msgStr;
        switch(eventId)
        { // TODO - Localized msgs of GO names
            case 19672: case 19675: // Flamewatch Tower
                msgStr = "Flamewatch";
                break;
            case 18553: case 19677: // Shadowsight Tower
                msgStr = "Shadowsight";
                break;
            case 19673: case 19676: // Winter's Edge Tower
                msgStr = "Winter's Edge";
                break;
            case 19776: case 19778: // E Workshop damaged
                msgStr = "Sunken Ring";
                break;
            case 19777: case 19779: // W Workshop damaged
                msgStr = "Broken Temple";
                break;
            case 19782: case 19786: // NW Workshop damaged
                msgStr = "north-western";
                break;
            case 19783: case 19787: // NE Workshop damaged
                msgStr = "north-eastern";
                break;
            case 19784: case 19788: // SW Workshop damaged
                msgStr = "Westpark";
                break;
            case 19785: case 19789: // SE Workshop damaged
                msgStr = "Eastpark";
                break;
            case 19657: case 19661: // NW Wintergrasp Keep Tower damaged
                msgStr = "north-western";
                break;
            case 19658: case 19663: // NE Wintergrasp Keep Tower damaged
                msgStr = "north-eastern";
                break;
            case 19659: case 19662: // SW Wintergrasp Keep Tower damaged
                msgStr = "south-western";
                break;
            case 19660: case 19664: // SE Wintergrasp Keep Tower damaged
                msgStr = "south-eastern";
                break;
            default:
                msgStr = "";
        }

        BuildingState *state = itr->second;
        if (eventId == obj->GetGOInfo()->building.damagedEvent)
        {
            if (obj->GetEntry() == 191810)
            {
               //obj->TakenDamage(30000);
               MaingateDestroyed=true;
            }

            state->damageState = DAMAGE_DAMAGED;
            switch(state->type)
            {
                case BUILDING_WORKSHOP:
                    msgStr = fmtstring(sObjectMgr->GetTrinityStringForDBCLocale(LANG_BG_WG_WORKSHOP_DAMAGED), msgStr.c_str(), sObjectMgr->GetTrinityStringForDBCLocale(getDefenderTeam() == TEAM_ALLIANCE ? LANG_BG_AB_ALLY : LANG_BG_AB_HORDE));
                    sWorld->SendZoneText(ZONE_WINTERGRASP, msgStr.c_str());
                    break;
                case BUILDING_WALL:
                    sWorld->SendZoneText(ZONE_WINTERGRASP, sObjectMgr->GetTrinityStringForDBCLocale(LANG_BG_WG_FORTRESS_UNDER_ATTACK));
                    for (PlayerSet::iterator itr = m_players[getDefenderTeam()].begin(); itr != m_players[getDefenderTeam()].end(); ++itr)
                    {
                        (*itr)->PlayDirectSound(getDefenderTeam() == TEAM_ALLIANCE? OutdoorPvP_WG_SOUND_KEEP_ASSAULTED_HORDE : OutdoorPvP_WG_SOUND_KEEP_ASSAULTED_ALLIANCE) ; // Wintergrasp Fortress under Siege
                    }
                    for (PlayerSet::iterator itr = m_players[getAttackerTeam()].begin(); itr != m_players[getAttackerTeam()].end(); ++itr)
                    {
                        (*itr)->PlayDirectSound(getDefenderTeam() == TEAM_ALLIANCE? OutdoorPvP_WG_SOUND_KEEP_ASSAULTED_HORDE : OutdoorPvP_WG_SOUND_KEEP_ASSAULTED_ALLIANCE) ; // Wintergrasp Fortress under Siege
                    }
                    break;
                case BUILDING_TOWER:
                    ++m_towerDamagedCount[state->GetTeam()];
                    msgStr = fmtstring(sObjectMgr->GetTrinityStringForDBCLocale(LANG_BG_WG_TOWER_DAMAGED), msgStr.c_str());
                    sWorld->SendZoneText(ZONE_WINTERGRASP, msgStr.c_str());

                    for (PlayerSet::iterator itr = m_players[getDefenderTeam()].begin(); itr != m_players[getDefenderTeam()].end(); ++itr)
                    {
                        (*itr)->PlayDirectSound(getDefenderTeam() == TEAM_ALLIANCE? OutdoorPvP_WG_SOUND_KEEP_CAPTURED_HORDE : OutdoorPvP_WG_SOUND_KEEP_CAPTURED_ALLIANCE) ; // Wintergrasp Fortress under Siege
                    }

                    for (PlayerSet::iterator itr = m_players[getAttackerTeam()].begin(); itr != m_players[getAttackerTeam()].end(); ++itr)
                    {
                        (*itr)->PlayDirectSound(getDefenderTeam() == TEAM_ALLIANCE? OutdoorPvP_WG_SOUND_KEEP_CAPTURED_HORDE : OutdoorPvP_WG_SOUND_KEEP_CAPTURED_ALLIANCE) ; // Wintergrasp Fortress under Siege
                    }
                    break;
            }
        }
        else if (eventId == obj->GetGOInfo()->building.destroyedEvent)
        {
            state->damageState = DAMAGE_DESTROYED;

            switch(state->type)
            {
                case BUILDING_WORKSHOP:
                    ModifyWorkshopCount(state->GetTeam(), false);
                    msgStr = fmtstring(sObjectMgr->GetTrinityStringForDBCLocale(LANG_BG_WG_WORKSHOP_DESTROYED), msgStr.c_str(), sObjectMgr->GetTrinityStringForDBCLocale(getDefenderTeam() == TEAM_ALLIANCE ? LANG_BG_AB_ALLY : LANG_BG_AB_HORDE));
                    sWorld->SendZoneText(ZONE_WINTERGRASP, msgStr.c_str());
                    break;
                case BUILDING_WALL:
                    sWorld->SendZoneText(ZONE_WINTERGRASP, sObjectMgr->GetTrinityStringForDBCLocale(LANG_BG_WG_FORTRESS_UNDER_ATTACK));

                    for (PlayerSet::iterator itr = m_players[getDefenderTeam()].begin(); itr != m_players[getDefenderTeam()].end(); ++itr)
                    {
                        (*itr)->PlayDirectSound(getDefenderTeam() == TEAM_ALLIANCE? OutdoorPvP_WG_SOUND_KEEP_CAPTURED_HORDE : OutdoorPvP_WG_SOUND_KEEP_CAPTURED_ALLIANCE) ; // Wintergrasp Fortress under Siege
                    }

                    for (PlayerSet::iterator itr = m_players[getAttackerTeam()].begin(); itr != m_players[getAttackerTeam()].end(); ++itr)
                    {
                        (*itr)->PlayDirectSound(getDefenderTeam() == TEAM_ALLIANCE? OutdoorPvP_WG_SOUND_KEEP_CAPTURED_HORDE : OutdoorPvP_WG_SOUND_KEEP_CAPTURED_ALLIANCE) ; // Wintergrasp Fortress under Siege
                    }
                    break;
                case BUILDING_TOWER:
                     --m_towerDamagedCount[state->GetTeam()];
                     ++m_towerDestroyedCount[state->GetTeam()];
                     if (state->GetTeam() == getAttackerTeam())
                     {
                        TeamCastSpell(getAttackerTeam(), -SPELL_TOWER_CONTROL);
                        TeamCastSpell(getDefenderTeam(), -SPELL_TOWER_CONTROL);
                        uint32 attStack = 3 - m_towerDestroyedCount[getAttackerTeam()];
                        if (m_towerDestroyedCount[getAttackerTeam()])
                            for (PlayerSet::iterator itr = m_players[getDefenderTeam()].begin(); itr != m_players[getDefenderTeam()].end(); ++itr)
                                if ((*itr)->getLevel() > 74)
                                    (*itr)->SetAuraStack(SPELL_TOWER_CONTROL, (*itr), m_towerDestroyedCount[getAttackerTeam()]);

                        if (attStack)
                        {
                            for (PlayerSet::iterator itr = m_players[getAttackerTeam()].begin(); itr != m_players[getAttackerTeam()].end(); ++itr)
                                if ((*itr)->getLevel() > 74)
                                    (*itr)->SetAuraStack(SPELL_TOWER_CONTROL, (*itr), attStack);
                        }
                         else
                        {
                            if (m_timer < 600000)
                                m_timer = 0;
                            else
                                m_timer = m_timer - 600000; // - 10 mins
                        }
                    }
                    msgStr = fmtstring(sObjectMgr->GetTrinityStringForDBCLocale(LANG_BG_WG_TOWER_DESTROYED), msgStr.c_str());
                    sWorld->SendZoneText(ZONE_WINTERGRASP, msgStr.c_str());
                    for (PlayerSet::iterator itr = m_players[getDefenderTeam()].begin(); itr != m_players[getDefenderTeam()].end(); ++itr)
                    {
                        (*itr)->PlayDirectSound(getDefenderTeam() == TEAM_ALLIANCE? OutdoorPvP_WG_HORDE_CAPTAIN : OutdoorPvP_WG_ALLIANCE_CAPTAIN) ; // Wintergrasp Fortress under Siege
                        // Add Support of Quests Toppling the Towers & Southern Sabotage
                        if (obj->GetEntry()==190356 || obj->GetEntry()==190357 || obj->GetEntry()==190358)
                            (*itr)->RewardPlayerAndGroupAtEvent(TOWER_PVP_DESTROYED, obj);
                    }
                    for (PlayerSet::iterator itr = m_players[getAttackerTeam()].begin(); itr != m_players[getAttackerTeam()].end(); ++itr)
                    {
                        (*itr)->PlayDirectSound(getDefenderTeam() == TEAM_ALLIANCE? OutdoorPvP_WG_HORDE_CAPTAIN : OutdoorPvP_WG_ALLIANCE_CAPTAIN) ; // Wintergrasp Fortress under Siege
                    }
                    break;
            }
            BroadcastStateChange(state);
        }
    }
    SaveData();
}

void OutdoorPvPWG::RemoveOfflinePlayerWGAuras()
{
    // if server crashed while in battle there could be players with rank or tenacity
    CharacterDatabase.PExecute("DELETE FROM character_aura WHERE spell IN (%u, %u, %u, %u, %u)",
         SPELL_RECRUIT, SPELL_CORPORAL, SPELL_LIEUTENANT, SPELL_TENACITY, SPELL_TOWER_CONTROL);
}

void OutdoorPvPWG::ModifyWorkshopCount(TeamId team, bool add)
{
    if (team == TEAM_NEUTRAL)
        return;

    if (add)
        ++m_workshopCount[team];
    else if (m_workshopCount[team])
        --m_workshopCount[team];
    else
        sLog->outError("OutdoorPvPWG::ModifyWorkshopCount: negative workshop count!");

    SendUpdateWorldState(MaxVehNumWorldState[team], m_workshopCount[team] * MAX_VEHICLE_PER_WORKSHOP);
    SaveData();
}

uint32 OutdoorPvPWG::GetCreatureEntry(uint32 guidlow, const CreatureData *data)
{
    return data->id;
}

OutdoorPvPWGCreType OutdoorPvPWG::GetCreatureType(uint32 entry) const
{
    // VEHICLES, GUARDS and TURRETS gives kill credit
    // OTHER Not in wartime
    // TURRET Only during wartime
    // SPECIAL like "OTHER" but no despawn conditions
    // Entries like Case A: Case: B have their own despawn function
    switch(entry)
    {
        case 27881: // Catapult
        case 28094: // Demolisher
        case 28312: // Alliance Siege Engine
        case 32627: // Horde Siege Engine
        case 28319: // Siege turret
        case 32629: // Siege turret
            return CREATURE_SIEGE_VEHICLE;
        case 28366: // Wintergrasp Tower cannon
            return CREATURE_TURRET;
        case CRE_ENG_A: // Alliance Engineer
        case CRE_ENG_H: // Horde Engineer
            return CREATURE_ENGINEER;
        case 30739:case 30740: // Champions
        case 32307:case 32308: // Guards
            return CREATURE_GUARD;
        case CRE_SPI_A: // Dwarven Spirit Guide
        case CRE_SPI_H: // Taunka Spirit Guide
            return CREATURE_SPIRIT_GUIDE;
        case 6491: // Spirit Healers
            return CREATURE_SPIRIT_HEALER;
        case 31101:case 31051: // Hoodoo Master & Sorceress
        case 31102:case 31052: // Vieron Blazefeather & Bowyer
        case 31107:case 31109: // Lieutenant & Senior Demolitionist
        case 31151:case 31153: // Tactical Officer
        case 31106:case 31108: // Siegesmith & Siege Master
        case 31053:case 31054: // Primalist & Anchorite
        case 31091:case 31036: // Commander
            return CREATURE_QUESTGIVER;
        case 32615:case 32626: // Warbringer && Brigadier General
        case 32296:case 32294: // Quartermaster
        case 39173:case 39172: // Ros'slai && Marshal Magruder
        case 30870:case 30869: // Flight Masters
            return CREATURE_SPECIAL;
        default:
            return CREATURE_OTHER; // Revenants, Elementals, etc
    }
}

void OutdoorPvPWG::OnCreatureCreate(Creature *creature)
{
    uint32 entry = creature->GetEntry();
    switch(GetCreatureType(entry))
    {
        case CREATURE_SIEGE_VEHICLE:
        {
            if (!creature->isSummon())
                return;

            TeamId team;
            if (creature->getFaction() == WintergraspFaction[TEAM_ALLIANCE])
                team = TEAM_ALLIANCE;
            else if (creature->getFaction() == WintergraspFaction[TEAM_HORDE])
                team = TEAM_HORDE;
            else
                return;

            if (uint32 engLowguid = GUID_LOPART(creature->ToTempSummon()->GetSummonerGUID()))
            {
                if (OPvPCapturePointWG *workshop = GetWorkshopByEngGuid(engLowguid))
                {
                    if (CanBuildVehicle(workshop))
                        m_vehicles[team].insert(creature);
                    else
                    {
                        creature->setDeathState(DEAD);
                        creature->SetRespawnTime(DAY);
                        return;
                    }
                }

                if (m_tenacityStack > 0 && team == TEAM_ALLIANCE)
                    creature->SetAuraStack(SPELL_TENACITY_VEHICLE, creature, m_tenacityStack);
                else if (m_tenacityStack < 0 && team == TEAM_HORDE)
                    creature->SetAuraStack(SPELL_TENACITY_VEHICLE, creature, -m_tenacityStack);
            }
            SendUpdateWorldState(VehNumWorldState[team], m_vehicles[team].size());
            break;
        }
        case CREATURE_ENGINEER:
            for (OutdoorPvP::OPvPCapturePointMap::iterator itr = m_capturePoints.begin(); itr != m_capturePoints.end(); ++itr)
            {
                if (OPvPCapturePointWG *workshop = dynamic_cast<OPvPCapturePointWG*>(itr->second))
                    if (workshop->m_engGuid == creature->GetDBTableGUIDLow())
                    {
                        workshop->m_engineer = creature;
                        break;
                    }
            }
            break;
        case CREATURE_SPIRIT_GUIDE:
            for (OutdoorPvP::OPvPCapturePointMap::iterator itr = m_capturePoints.begin(); itr != m_capturePoints.end(); ++itr)
            {
                if (OPvPCapturePointWG *workshop = dynamic_cast<OPvPCapturePointWG*>(itr->second))
                    if (workshop->m_spiGuid == creature->GetDBTableGUIDLow())
                    {
                        workshop->m_spiritguide = creature;
                        break;
                    }
            }
            creature->CastSpell(creature, SPELL_SPIRITUAL_IMMUNITY, true);
        case CREATURE_SPIRIT_HEALER:
        case CREATURE_TURRET:
        case CREATURE_OTHER:
            UpdateCreatureInfo(creature);
        default:
            m_creatures.insert(creature);
            break;
    }
}

void OutdoorPvPWG::OnCreatureRemove(Creature *creature)
{
    uint32 entry = creature->GetEntry();
    switch(GetCreatureType(entry))
    {
        case CREATURE_SIEGE_VEHICLE:
        {
            if (!creature->isSummon())
                return;

            TeamId team;
            // the faction may be changed in uncharm
            // TODO: now you have to wait until the corpse of vehicle disappear to build a new one
            if (m_vehicles[TEAM_ALLIANCE].erase(creature))
                team = TEAM_ALLIANCE;
            else if (m_vehicles[TEAM_HORDE].erase(creature))
                team = TEAM_HORDE;
            else
                return;

            SendUpdateWorldState(VehNumWorldState[team], m_vehicles[team].size());
            break;
        }
        case CREATURE_ENGINEER:
            for (OutdoorPvP::OPvPCapturePointMap::iterator itr = m_capturePoints.begin(); itr != m_capturePoints.end(); ++itr)
            {
                if (OPvPCapturePointWG *workshop = dynamic_cast<OPvPCapturePointWG*>(itr->second))
                    if (workshop->m_engGuid == creature->GetDBTableGUIDLow())
                    {
                        workshop->m_engineer = NULL;
                        break;
                    }
            }
            m_creatures.erase(creature); // prevents crash, but i think it's wrong
            break;
        case CREATURE_SPIRIT_GUIDE:
            for (OutdoorPvP::OPvPCapturePointMap::iterator itr = m_capturePoints.begin(); itr != m_capturePoints.end(); ++itr)
            {
                if (OPvPCapturePointWG *workshop = dynamic_cast<OPvPCapturePointWG*>(itr->second))
                    if (workshop->m_spiGuid == creature->GetDBTableGUIDLow())
                    {
                        workshop->m_spiritguide = NULL;
                        break;
                    }
            }
            m_creatures.erase(creature); // prevents crash, but i think it's wrong
            break;
        default:
            m_creatures.erase(creature);
            break;
    }
}

void OutdoorPvPWG::OnGameObjectCreate(GameObject *go)
{
    OutdoorPvP::OnGameObjectCreate(go);

    if (UpdateGameObjectInfo(go))
        m_gobjects.insert(go);

    else if (go->GetGoType() == GAMEOBJECT_TYPE_DESTRUCTIBLE_BUILDING)
    {
        BuildingStateMap::const_iterator itr = m_buildingStates.find(go->GetDBTableGUIDLow());
        if (itr != m_buildingStates.end())
        {
            itr->second->building = go;
            if (go->GetGOInfo()->displayId == 7878 || go->GetGOInfo()->displayId == 7900)
                itr->second->type = BUILDING_TOWER;
            if (itr->second->damageState == DAMAGE_INTACT && !itr->second->health)
            {
                itr->second->health = go->GetGOValue()->building.health;
                go->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_DESTROYED);
            }
            else
            {
                go->GetGOValue()->building.health = itr->second->health;
                if (itr->second->damageState == DAMAGE_DAMAGED)
                    go->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_DAMAGED);
                else if (itr->second->damageState == DAMAGE_DESTROYED)
                    go->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_DESTROYED);
            }
        }
    }
}

void OutdoorPvPWG::OnGameObjectRemove(GameObject *go)
{
    OutdoorPvP::OnGameObjectRemove(go);

    if (UpdateGameObjectInfo(go))
    {
        m_gobjects.erase(go);
    }
    else if (go->GetGoType() == GAMEOBJECT_TYPE_DESTRUCTIBLE_BUILDING)
    {
        BuildingStateMap::const_iterator itr = m_buildingStates.find(go->GetDBTableGUIDLow());
        if (itr != m_buildingStates.end())
            itr->second->building = NULL;
    }
}

void OutdoorPvPWG::UpdateAllWorldObject()
{
    // update cre and go factions
    for (GameObjectSet::iterator itr = m_gobjects.begin(); itr != m_gobjects.end(); ++itr)
        UpdateGameObjectInfo(*itr);
    for (CreatureSet::iterator itr = m_creatures.begin(); itr != m_creatures.end(); ++itr)
        UpdateCreatureInfo(*itr);

    // rebuild and update building states
    RebuildAllBuildings();

    // update capture points
    for (OPvPCapturePointMap::iterator itr = m_capturePoints.begin(); itr != m_capturePoints.end(); ++itr)
        if (OPvPCapturePointWG *workshop = dynamic_cast<OPvPCapturePointWG*>(itr->second))
            workshop->SetTeamByBuildingState();
}

void OutdoorPvPWG::RebuildAllBuildings()
{
    m_workshopCount[TEAM_ALLIANCE] = 0;
    m_workshopCount[TEAM_HORDE] = 0;
    m_towerDamagedCount[TEAM_ALLIANCE] = 0;
    m_towerDamagedCount[TEAM_HORDE] = 0;
    m_towerDestroyedCount[TEAM_ALLIANCE] = 0;
    m_towerDestroyedCount[TEAM_HORDE] = 0;
    for (BuildingStateMap::const_iterator itr = m_buildingStates.begin(); itr != m_buildingStates.end(); ++itr)
    {
        if (!itr->second)
            continue;

        if (itr->second->building && itr->second->building->GetGoType() == GAMEOBJECT_TYPE_DESTRUCTIBLE_BUILDING)
        {
            UpdateGameObjectInfo(itr->second->building);
            itr->second->building->Rebuild();
            itr->second->health = itr->second->building->GetGOValue()->building.health;
            itr->second->damageState = DAMAGE_INTACT;
        }
        else
            itr->second->health = 0;

        if (itr->second->type == BUILDING_WORKSHOP)
            ModifyWorkshopCount(itr->second->GetTeam(), true);

        itr->second->SetTeam(getDefenderTeam() == TEAM_ALLIANCE ? OTHER_TEAM(itr->second->defaultTeam) : itr->second->defaultTeam);
    }
}

void OutdoorPvPWG::SendInitWorldStatesTo(Player *player) const
{
    WorldPacket data(SMSG_INIT_WORLD_STATES, (4+4+4+2+(m_buildingStates.size()*8)));
    data << uint32(571);
    data << uint32(ZONE_WINTERGRASP);
    data << uint32(0);
    data << uint16(4+2+4+m_buildingStates.size());

    data << uint32(3803) << uint32(getDefenderTeam() == TEAM_ALLIANCE ? 1 : 0);
    data << uint32(3802) << uint32(getDefenderTeam() != TEAM_ALLIANCE ? 1 : 0);
    data << uint32(3801) << uint32(isWarTime() ? 0 : 1);
    data << uint32(3710) << uint32(isWarTime() ? 1 : 0);

    for (uint32 i = 0; i < 2; ++i)
        data << ClockWorldState[i] << m_clock[i];

    data << uint32(3490) << uint32(m_vehicles[TEAM_HORDE].size());
    data << uint32(3491) << m_workshopCount[TEAM_HORDE] * MAX_VEHICLE_PER_WORKSHOP;
    data << uint32(3680) << uint32(m_vehicles[TEAM_ALLIANCE].size());
    data << uint32(3681) << m_workshopCount[TEAM_ALLIANCE] * MAX_VEHICLE_PER_WORKSHOP;

    for (BuildingStateMap::const_iterator itr = m_buildingStates.begin(); itr != m_buildingStates.end(); ++itr)
    {
        if (!itr->second)
            continue;

        itr->second->FillData(data);
    }

    if (player)
        player->GetSession()->SendPacket(&data);
    else
        BroadcastPacket(data);
}

void OutdoorPvPWG::BroadcastStateChange(BuildingState *state) const
{
    if (m_sendUpdate)
        for (uint32 team = 0; team < 2; ++team)
            for (PlayerSet::const_iterator p_itr = m_players[team].begin(); p_itr != m_players[team].end(); ++p_itr)
                state->SendUpdate(*p_itr);
}

// Called at Start and Battle End
bool OutdoorPvPWG::UpdateCreatureInfo(Creature *creature)
{
    if (!creature)
        return false;
    uint32 entry = creature->GetEntry();
    switch(GetCreatureType(entry))
    {
        case CREATURE_TURRET:
            if (isWarTime())
            {
                if (!creature->isAlive())
                    creature->Respawn(true);

                creature->setFaction(WintergraspFaction[getDefenderTeam()]);
                creature->SetVisible(true);
            }
            else
            {
                if (creature->IsVehicle() && creature->GetVehicleKit())
                    creature->GetVehicleKit()->RemoveAllPassengers();

                creature->SetVisible(false);
                creature->setFaction(PD_FACTION_FRIENDLY);
            }
            return false;
        case CREATURE_OTHER:
            if (isWarTime())
            {
                creature->SetVisible(false);
                creature->setFaction(PD_FACTION_FRIENDLY);
            }
            else
            {
                creature->RestoreFaction();
                creature->SetVisible(true);
            }
            return false;
        case CREATURE_SPIRIT_GUIDE:
            /*Vehicle teleport system*/
            pMap = creature->GetMap();
            if (isWarTime())
            {
              /*  if (creature->GetAreaId() == 4575) // Select Fortress Spirit
                {
                    FortressSpirit = creature;
                    if (getDefenderTeam() == TEAM_ALLIANCE) // Fortress Spirit Alliance
                            FortressSpirit->UpdateEntry(CRE_SPI_A);
                    if (getDefenderTeam() == TEAM_HORDE) // Fortress Spirit Horde
                        FortressSpirit->UpdateEntry(CRE_SPI_H);
                }*/
                creature->SetVisible(true);
            }
            else
                creature->SetVisible(false);

            return false;
        case CREATURE_SPIRIT_HEALER:
            creature->SetVisible(isWarTime() ? false : true);
            return false;
        case CREATURE_ENGINEER:
           return false;
        case CREATURE_SIEGE_VEHICLE:
            if (!isWarTime())
            {
                if (creature->IsVehicle() && creature->GetVehicleKit())
                    creature->GetVehicleKit()->RemoveAllPassengers();
                creature->DisappearAndDie();
            }
            return false;
        default:
            return false;
    }
}

// Return false = Need to rebuild at battle End/Start
//        true  = no need to rebuild (ie: Banners or teleporters)
bool OutdoorPvPWG::UpdateGameObjectInfo(GameObject *go) const
{
    uint32 attFaction = PD_FACTION_FRIENDLY;
    uint32 defFaction = PD_FACTION_FRIENDLY;

    if (isWarTime())
    {
        attFaction = WintergraspFaction[getAttackerTeam()];
        defFaction = WintergraspFaction[getDefenderTeam()];
    }

    switch(go->GetGOInfo()->displayId)
    {
        case 8244: // Defender's Portal - Vehicle Teleporter
            go->SetUInt32Value(GAMEOBJECT_FACTION, WintergraspFaction[getDefenderTeam()]);
            return true;
        case 7967: // Titan relic
            go->SetUInt32Value(GAMEOBJECT_FACTION, WintergraspFaction[getAttackerTeam()]);
            return true;

        case 8165: // Wintergrasp Keep Door
        case 7877: // Wintergrasp Fortress Wall
        case 7878: // Wintergrasp Keep Tower
        case 7906: // Wintergrasp Fortress Gate
        case 7909: // Wintergrasp Wall
            go->SetUInt32Value(GAMEOBJECT_FACTION, defFaction);
            return false;
        case 7900: // Flamewatch Tower - Shadowsight Tower - Winter's Edge Tower
            go->SetUInt32Value(GAMEOBJECT_FACTION, attFaction);
            return false;
        case 8208: // Goblin Workshop
            OPvPCapturePointWG *workshop = GetWorkshopByGOGuid(go->GetGUID());
            if (workshop)
                go->SetUInt32Value(GAMEOBJECT_FACTION, WintergraspFaction[workshop->m_buildingState->GetTeam()]);
            return false;
    }

    return false;
}

void OutdoorPvPWG::HandlePlayerEnterZone(Player * plr, uint32 zone)
{
    if (!sWorld->getBoolConfig(CONFIG_OUTDOORPVP_WINTERGRASP_ENABLED) || !plr)
        return;

    if (isWarTime())
    {
        if (plr->getLevel() < 75)
        {
            plr->CastSpell(plr, SPELL_TELEPORT_DALARAN, true);
            return;
        }
        else if (plr->GetTeamId() != getDefenderTeam() && plr->GetMap() && plr->GetAreaId() == 4575 && !plr->GetMap()->IsOutdoors(plr->GetPositionX(), plr->GetPositionY(), plr->GetPositionZ()))
        {
            if (plr->GetTeamId() == TEAM_ALLIANCE)
            {
                plr->CastSpell(plr, SPELL_TELEPORT_ALLIANCE_CAMP, true);
            } 
            else
            {
                plr->CastSpell(plr, SPELL_TELEPORT_HORDE_CAMP, true);
            }
            return;
        }
        else
        {
            if (!plr->HasAura(SPELL_RECRUIT) && !plr->HasAura(SPELL_CORPORAL)
                && !plr->HasAura(SPELL_LIEUTENANT))
                plr->CastSpell(plr, SPELL_RECRUIT, true);

            if (plr->GetTeamId() == getAttackerTeam())
                if (m_towerDestroyedCount[getAttackerTeam()] < 3)
                    plr->SetAuraStack(SPELL_TOWER_CONTROL, plr, 3 - m_towerDestroyedCount[getAttackerTeam()]);
            else
                if (m_towerDestroyedCount[getAttackerTeam()])
                    plr->SetAuraStack(SPELL_TOWER_CONTROL, plr, m_towerDestroyedCount[getAttackerTeam()]);
        }
    }
    else if (plr->GetTeamId() != GetControllingTeamID())
    {
        if (plr->GetMap() && plr->GetAreaId() == 4575 && !plr->GetMap()->IsOutdoors(plr->GetPositionX(), plr->GetPositionY(), plr->GetPositionZ()))
        {
            if (plr->GetTeamId() == TEAM_ALLIANCE)
            {
                plr->CastSpell(plr, SPELL_TELEPORT_ALLIANCE_CAMP, true);
            } 
            else
            {
                plr->CastSpell(plr, SPELL_TELEPORT_HORDE_CAMP, true);
            }
            return;
        }
    }

    SendInitWorldStatesTo(plr);
    OutdoorPvP::HandlePlayerEnterZone(plr, zone);
    UpdateTenacityStack();
}

// Reapply Auras if needed
void OutdoorPvPWG::HandlePlayerResurrects(Player * plr, uint32 zone)
{
    if (!sWorld->getBoolConfig(CONFIG_OUTDOORPVP_WINTERGRASP_ENABLED))
        return;

    if (isWarTime())
    {
        if (plr->getLevel() > 74)
        {
            // Tenacity
            if (plr->GetTeamId() == TEAM_ALLIANCE && m_tenacityStack > 0 ||
                plr->GetTeamId() == TEAM_HORDE && m_tenacityStack < 0)
            {
                if (plr->HasAura(SPELL_TENACITY))
                    plr->RemoveAurasDueToSpell(SPELL_TENACITY);

                int32 newStack = m_tenacityStack < 0 ? -m_tenacityStack : m_tenacityStack;
                if (newStack > 20)
                    newStack = 20;
                plr->SetAuraStack(SPELL_TENACITY, plr, newStack);
            }

            // Tower Control
            if (plr->GetTeamId() == getAttackerTeam())
                if (m_towerDestroyedCount[getAttackerTeam()] < 3)
                    plr->SetAuraStack(SPELL_TOWER_CONTROL, plr, 3 - m_towerDestroyedCount[getAttackerTeam()]);
            else
                if (m_towerDestroyedCount[getAttackerTeam()])
                    plr->SetAuraStack(SPELL_TOWER_CONTROL, plr, m_towerDestroyedCount[getAttackerTeam()]);
        }
    }
    OutdoorPvP::HandlePlayerResurrects(plr, zone);
}

void OutdoorPvPWG::HandlePlayerLeaveZone(Player * plr, uint32 zone)
{
    if (!sWorld->getBoolConfig(CONFIG_OUTDOORPVP_WINTERGRASP_ENABLED))
        return;

    if (!plr->GetSession()->PlayerLogout())
    {
        if (plr->GetVehicle()) // dismiss in change zone case
            plr->GetVehicle()->Dismiss();
        plr->RemoveAurasDueToSpell(SPELL_RECRUIT);
        plr->RemoveAurasDueToSpell(SPELL_CORPORAL);
        plr->RemoveAurasDueToSpell(SPELL_LIEUTENANT);
        plr->RemoveAurasDueToSpell(SPELL_TOWER_CONTROL);
        plr->RemoveAurasDueToSpell(SPELL_SPIRITUAL_IMMUNITY);
    }
    plr->RemoveAurasDueToSpell(SPELL_TENACITY);
    OutdoorPvP::HandlePlayerLeaveZone(plr, zone);
    UpdateTenacityStack();
}

void OutdoorPvPWG::PromotePlayer(Player *killer) const
{
    if (!killer)
        return;

    Aura * aur;
    if (aur = killer->GetAura(SPELL_RECRUIT))
    {
        if (aur->GetStackAmount() >= 5)
        {
            killer->RemoveAura(SPELL_RECRUIT);
            killer->CastSpell(killer, SPELL_CORPORAL, true);
            ChatHandler(killer).PSendSysMessage(LANG_BG_WG_RANK1);
        }
        else
            killer->CastSpell(killer, SPELL_RECRUIT, true);
    }
    else if (aur = killer->GetAura(SPELL_CORPORAL))
    {
        if (aur->GetStackAmount() >= 5)
        {
            killer->RemoveAura(SPELL_CORPORAL);
            killer->CastSpell(killer, SPELL_LIEUTENANT, true);
            ChatHandler(killer).PSendSysMessage(LANG_BG_WG_RANK2);
        }
        else
            killer->CastSpell(killer, SPELL_CORPORAL, true);
    }
}

void OutdoorPvPWG::HandleKill(Player *killer, Unit *victim)
{
    if (!sWorld->getBoolConfig(CONFIG_OUTDOORPVP_WINTERGRASP_ENABLED) || !isWarTime())
        return;

    if (!killer || !victim)
        return;

    bool ok = false;
    if (victim->GetTypeId() == TYPEID_PLAYER)
    {
        if (victim->getLevel() >= 74)
            ok = true;

        killer->RewardPlayerAndGroupAtEvent(CRE_PVP_KILL, victim);
    }
    else
    {
        switch(GetCreatureType(victim->GetEntry()))
        {
            case CREATURE_SIEGE_VEHICLE:
                killer->RewardPlayerAndGroupAtEvent(CRE_PVP_KILL_V, victim);
                ok = true;
                break;
            case CREATURE_GUARD:
                killer->RewardPlayerAndGroupAtEvent(CRE_PVP_KILL, victim);
                ok = true;
                break;
            case CREATURE_TURRET:
                ok = true;
                break;
        }
    }

    if (ok)
    {
        if (Group *pGroup = killer->GetGroup())
        {
            for (GroupReference *itr = pGroup->GetFirstMember(); itr != NULL; itr = itr->next())
                if (itr->getSource()->IsAtGroupRewardDistance(killer) && itr->getSource()->getLevel() > 74)
                    PromotePlayer(itr->getSource());
        }
        else
        {
            if (killer->getLevel() > 74)
                PromotePlayer(killer);
        }
    }
}

// Recalculates Tenacity and applies it to Players / Vehicles
void OutdoorPvPWG::UpdateTenacityStack()
{
    if (!isWarTime())
        return;

    TeamId team = TEAM_NEUTRAL;
    uint32 allianceNum = 0;
    uint32 hordeNum = 0;
    int32 newStack = 0;

    for (PlayerSet::iterator itr = m_players[TEAM_ALLIANCE].begin(); itr != m_players[TEAM_ALLIANCE].end(); ++itr)
        if ((*itr)->getLevel() > 74)
            ++allianceNum;

    for (PlayerSet::iterator itr = m_players[TEAM_HORDE].begin(); itr != m_players[TEAM_HORDE].end(); ++itr)
        if ((*itr)->getLevel() > 74)
            ++hordeNum;

    if (allianceNum && hordeNum)
    {
        if (allianceNum < hordeNum)
        {
            team = TEAM_ALLIANCE;
            newStack = int32((float(hordeNum) / float(allianceNum) - 1)*4); // positive, should cast on alliance
            if (newStack > 20)
                newStack = 20;
        }
        else if (allianceNum > hordeNum)
        {
            team = TEAM_HORDE;
            newStack = int32((1 - float(allianceNum) / float(hordeNum))*4); // negative, should cast on horde
            if (newStack < -20)
                newStack = -20;
        }
    }
 
    if (newStack == m_tenacityStack)
        return;

    m_tenacityStack = newStack;

    // Remove old buff
    for (uint8 teamID = 0; teamID < 2; ++teamID)
    {
        for (PlayerSet::const_iterator itr = m_players[teamID].begin(); itr != m_players[teamID].end(); ++itr)
            (*itr)->RemoveAurasDueToSpell(SPELL_TENACITY);

        for (CreatureSet::const_iterator itr = m_vehicles[teamID].begin(); itr != m_vehicles[teamID].end(); ++itr)
            (*itr)->RemoveAurasDueToSpell(SPELL_TENACITY_VEHICLE);
    }

    // Apply new buff
    if (team != TEAM_NEUTRAL && newStack)
    {
        if (newStack < 0)
            newStack = -newStack;

        for (PlayerSet::const_iterator itr = m_players[team].begin(); itr != m_players[team].end(); ++itr)
            if ((*itr)->getLevel() > 74)
                (*itr)->SetAuraStack(SPELL_TENACITY, (*itr), newStack);

        for (CreatureSet::const_iterator itr = m_vehicles[team].begin(); itr != m_vehicles[team].end(); ++itr)
            (*itr)->SetAuraStack(SPELL_TENACITY_VEHICLE, (*itr), newStack);
    }
}

void OutdoorPvPWG::UpdateClockDigit(uint32 &timer, uint32 digit, uint32 mod)
{
    uint32 value = timer%mod;
    if (m_clock[digit] != value)
    {
        m_clock[digit] = value;
        SendUpdateWorldState(ClockWorldState[digit], uint32(timer + time(NULL)));
        sWorld->SetWintergraspTimer(uint32(timer + time(NULL)), digit);
    }
}

void OutdoorPvPWG::UpdateClock()
{
    uint32 timer = m_timer *0.001f;
    if (!isWarTime())
        UpdateClockDigit(timer, 1, 10);
    else
        UpdateClockDigit(timer, 0, 10);

    //Announce in all world, comment it if you don't like/need it
    // Announce 30 minutes left
     if ((m_timer < 1800000) && !timer_30m && (m_wartime == false)) 
    {
        timer_30m = true;
        sWorld->SendWorldText(LANG_BG_WG_WORLD_ANNOUNCE_30);
    }

    // Announce 10 minutes left
    if ((m_timer < 600000) && !timer_10m && (m_wartime == false))
    {
        timer_10m = true;
        sWorld->SendWorldText(LANG_BG_WG_WORLD_ANNOUNCE_10);
    }
}

void OutdoorPvPWG::DoVehicleTeleport()
{
    if (pMap)
    {
        Map::PlayerList const &PlayerList = pMap->GetPlayers();
        for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
        {
            if (i->getSource()->ToPlayer()->GetTeamId() == getDefenderTeam())
            {
                if (i->getSource()->isAlive() 
                    && i->getSource()->IsOnVehicle(i->getSource()->GetVehicleCreatureBase())
                    &&(i->getSource()->GetDistance2d(5314.51f, 2703.69f) <= 5 || i->getSource()->GetDistance2d(5316.25f, 2977.04f) <= 5))
                {
                    if (Creature* Old = i->getSource()->GetVehicleCreatureBase())
                    {
                        if (Old->GetEntry() == 28319 || Old->GetEntry() == 32629) //Turret
                        {
                            i->getSource()->ExitVehicle();
                            i->getSource()->NearTeleportTo(5141.191406f, 2841.045410f, 408.703217f, 3.163321f, true); // Out of the Fortress Gate
                            Old->SetVisible(false);
                            Old->ToTempSummon()->UnSummon();
                        }
                        else
                        {
                            Unit* Driver = Old->GetVehicleKit()->GetPassenger(0);
                            Unit* Passenger1 = Old->GetVehicleKit()->GetPassenger(1);
                            Unit* Passenger2 = Old->GetVehicleKit()->GetPassenger(2);
                            Unit* Passenger3 = Old->GetVehicleKit()->GetPassenger(3);
                            if (Driver && Driver->isAlive())
                            {
                                if (Creature* New = i->getSource()->SummonCreature(Old->GetEntry(), 5141.191406f, 2841.045410f, 408.703217f, 3.163321f, TEMPSUMMON_MANUAL_DESPAWN))
                                {
                                    New->SetPower(POWER_MANA, Old->GetPower(POWER_MANA));
                                    New->SetPower(POWER_RAGE, Old->GetPower(POWER_RAGE));
                                    New->SetPower(POWER_FOCUS, Old->GetPower(POWER_FOCUS));
                                    New->SetPower(POWER_ENERGY, Old->GetPower(POWER_ENERGY));
                                    New->SetHealth(Old->GetHealth());
                                    New->SetRespawnTime(Old->GetRespawnTime());
                                    Old->GetVehicleKit()->Uninstall();
                                    Old->SetVisible(false);
                                    Old->ForcedDespawn();
                                    Driver->NearTeleportTo(5141.191406f, 2841.045410f, 408.703217f, 3.163321f, true); // Out of the Fortress Gate
                                    Driver->EnterVehicle(New, 0);
                                    if (Passenger1 && Passenger1->isAlive())
                                        Passenger1->NearTeleportTo(5141.191406f, 2841.045410f, 408.703217f, 3.163321f, true); // Out of the Fortress Gate
                                    if (Passenger2 && Passenger2->isAlive())
                                        Passenger2->NearTeleportTo(5141.191406f, 2841.045410f, 408.703217f, 3.163321f, true); // Out of the Fortress Gate
                                    if (Passenger3 && Passenger3->isAlive())
                                        Passenger3->NearTeleportTo(5141.191406f, 2841.045410f, 408.703217f, 3.163321f, true); // Out of the Fortress Gate
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

bool OutdoorPvPWG::Update(uint32 diff)
{
    if (!sWorld->getBoolConfig(CONFIG_OUTDOORPVP_WINTERGRASP_ENABLED))
        return false;

    if (m_saveinterval <= diff)
        SaveData();
    else
        m_saveinterval -= diff;

    if (m_timer > diff)
    {
        m_timer -= diff;

        if (isWarTime())
        {
            OutdoorPvP::Update(diff); // update capture points

            /*********************************************************/
            /***      BATTLEGROUND VEHICLE TELEPORTER SYSTEM       ***/
            /*********************************************************/
            
            DoVehicleTeleport();

            /*********************************************************/
            /***        BATTLEGROUND RESSURECTION SYSTEM           ***/
            /*********************************************************/

            //this should be handled by spell system
            m_LastResurrectTime += diff;
            if (m_LastResurrectTime >= RESURRECTION_INTERVAL)
            {
                if (GetReviveQueueSize())
                {
                    for (std::map<uint64, std::vector<uint64> >::iterator itr = m_ReviveQueue.begin(); itr != m_ReviveQueue.end(); ++itr)
                    {
                        Creature* sh = NULL;
                        for (std::vector<uint64>::const_iterator itr2 = (itr->second).begin(); itr2 != (itr->second).end(); ++itr2)
                        {
                            if(Player *plr = sObjectMgr->GetPlayer(*itr2))
                            {
                                if (!sh && plr->IsInWorld())
                                {
                                    // only for visual effect
                                    sh = plr->GetMap()->GetCreature(itr->first);
                                    if (sh) // Spirit Heal, effect 117                                        
                                        sh->CastSpell(sh, SPELL_SPIRIT_HEAL, true);
                                }

                                // Resurrection visual
                                if (sh && plr->GetDistance2d(sh) <= 18.0f)
                                {
                                    plr->CastSpell(plr, SPELL_RESURRECTION_VISUAL, true);
                                    m_ResurrectQueue.push_back(*itr2);
                                }
                            }                            
                        }
                        (itr->second).clear();
                    }

                    m_ReviveQueue.clear();
                    m_LastResurrectTime = 0;
                }
                else
                    // queue is clear and time passed, just update last resurrection time
                    m_LastResurrectTime = 0;
            }
            else if (m_LastResurrectTime > 500)    // Resurrect players only half a second later, to see spirit heal effect on NPC
            {
                for (std::vector<uint64>::const_iterator itr = m_ResurrectQueue.begin(); itr != m_ResurrectQueue.end(); ++itr)
                {
                    if(Player *plr = sObjectMgr->GetPlayer(*itr))
                    {
                        plr->ResurrectPlayer(1.0f);
                        plr->CastSpell(plr, 6962, true);
                        plr->CastSpell(plr, SPELL_SPIRIT_HEAL_MANA, true);
                        sObjectAccessor->ConvertCorpseForPlayer(*itr);
                    }                    
                }
                m_ResurrectQueue.clear();
            }
        }
        UpdateClock();
    }
    else
    {
        m_sendUpdate = false;
        int32 entry = LANG_BG_WG_DEFENDED;

        if (m_changeDefender)
        {
            m_changeDefender = false;
            m_defender = getAttackerTeam();
            entry = LANG_BG_WG_CAPTURED;
        }
        if (isWarTime())
        {
            if (m_timer != 1) // 1 = forceStopBattle
                sWorld->SendZoneText(ZONE_WINTERGRASP, fmtstring(sObjectMgr->GetTrinityStringForDBCLocale(entry), sObjectMgr->GetTrinityStringForDBCLocale(getDefenderTeam() == TEAM_ALLIANCE ? LANG_BG_AB_ALLY : LANG_BG_AB_HORDE)));
            EndBattle();
        }
        else
        {
            if (m_timer != 1) // 1 = forceStartBattle
                sWorld->SendZoneText(ZONE_WINTERGRASP, sObjectMgr->GetTrinityStringForDBCLocale(LANG_BG_WG_BATTLE_STARTS));
            StartBattle();
        }

        UpdateAllWorldObject();
        UpdateClock();
        SendInitWorldStatesTo();
        m_sendUpdate = true;
        SaveData();
    }

    return false;
}

void OutdoorPvPWG::forceStartBattle()
{// Uptime will do all the work
    m_wartime = false;

    if (m_timer != 1)
    {
        m_timer = 1;
        sWorld->SendZoneText(ZONE_WINTERGRASP, sObjectMgr->GetTrinityStringForDBCLocale(LANG_BG_WG_BATTLE_FORCE_START));
    }
    sWorld->SendWintergraspState();
}

void OutdoorPvPWG::forceStopBattle()
{// Uptime will do all the work.

    if (!isWarTime())
        m_wartime = true;

    timer_30m = false;
    timer_10m = false;

    if (m_timer != 1)
    {
        m_timer = 1;
        sWorld->SendZoneText(ZONE_WINTERGRASP, sObjectMgr->GetTrinityStringForDBCLocale(LANG_BG_WG_BATTLE_FORCE_STOP));
    }

    sWorld->SendWintergraspState();

    SaveData();
}

void OutdoorPvPWG::forceChangeTeam()
{
    m_changeDefender = true;
    m_timer = 1;
    sWorld->SendZoneText(ZONE_WINTERGRASP, fmtstring(sObjectMgr->GetTrinityStringForDBCLocale(LANG_BG_WG_SWITCH_FACTION), sObjectMgr->GetTrinityStringForDBCLocale(getAttackerTeam() == TEAM_ALLIANCE ? LANG_BG_AB_ALLY : LANG_BG_AB_HORDE)));
    if (isWarTime())
        forceStartBattle();
    else
        forceStopBattle();
}

// Can be forced by gm's while in battle so have to reset in case it was wartime
void OutdoorPvPWG::StartBattle()
{
    uint32 CountDef=0;
    uint32 CountAtk=0;
    m_wartime = true;
    MaingateDestroyed = false;
    
    SpawnBattle();

    m_timer = sWorld->getIntConfig(CONFIG_OUTDOORPVP_WINTERGRASP_BATTLE_TIME) * MINUTE * IN_MILLISECONDS;

    UpdateAllWorldObject();

    for (PlayerSet::iterator itr = m_players[getDefenderTeam()].begin(); itr != m_players[getDefenderTeam()].end(); ++itr)
    {
        if ((*itr)->getLevel() < 75)
            (*itr)->CastSpell((*itr), SPELL_TELEPORT_DALARAN, true);
        else
        {
            CountDef++;
            (*itr)->RemoveAurasByType(SPELL_AURA_MOD_INCREASE_MOUNTED_FLIGHT_SPEED);
            (*itr)->RemoveAurasByType(SPELL_AURA_FLY);
            (*itr)->CastSpell((*itr), 45472, true); //prevent die if fall
            (*itr)->PlayDirectSound(OutdoorPvP_WG_SOUND_START_BATTLE); // START Battle
        }
    }

    for (PlayerSet::iterator itr = m_players[getAttackerTeam()].begin(); itr != m_players[getAttackerTeam()].end(); ++itr)
    {
        if ((*itr)->getLevel() < 75)
            (*itr)->CastSpell((*itr), SPELL_TELEPORT_DALARAN, true);
        else
        {
            CountAtk++;
            (*itr)->RemoveAurasByType(SPELL_AURA_MOD_INCREASE_MOUNTED_FLIGHT_SPEED);
            (*itr)->RemoveAurasByType(SPELL_AURA_FLY);
            (*itr)->CastSpell((*itr), 45472, true); //prevent die if fall
            (*itr)->PlayDirectSound(OutdoorPvP_WG_SOUND_START_BATTLE); // START Battle
        }
    }

    if (sWorld->getBoolConfig(CONFIG_OUTDOORPVP_WINTERGRASP_ANTIFARM_ENABLE))
    {
        if ((CountAtk < sWorld->getIntConfig(CONFIG_OUTDOORPVP_WINTERGRASP_ANTIFARM_ATK)) || (CountDef < sWorld->getIntConfig(CONFIG_OUTDOORPVP_WINTERGRASP_ANTIFARM_DEF)))
        {
            if (CountAtk<=CountDef)
                sWorld->SendWorldText(LANG_BG_WG_WORLD_NO_ATK);
            if (CountDef<CountAtk)
            {  
                sWorld->SendWorldText(LANG_BG_WG_WORLD_NO_DEF);
                m_changeDefender=true;
            }
            forceStopBattle();
            return;
        }
    }

    SetControllingTeamId(TEAM_NEUTRAL);
    sWorld->UpdateAreaDependentAuras();

    // destroyed all vehicles
    for (uint32 team = 0; team < 2; ++team)
    {
        while(!m_vehicles[team].empty())
        {
            Creature *veh = *m_vehicles[team].begin();
            m_vehicles[team].erase(m_vehicles[team].begin());
            veh->setDeathState(JUST_DIED);
        }
    }

    for (PlayerSet::iterator itr = m_players[getAttackerTeam()].begin(); itr != m_players[getAttackerTeam()].end(); ++itr)
    {
        if (!(*itr))
            return;

        uint8 attackerstowerid = urand(0,2);

        float x, y, z;
        x = OutdoorPvPAttackersTower[attackerstowerid][0] + float(irand(-4, 4));
        y = OutdoorPvPAttackersTower[attackerstowerid][1] + float(irand(-4, 4));
        z = (*itr)->GetBaseMap()->GetHeight(x, y, OutdoorPvPAttackersTower[attackerstowerid][2] + 5);

        (*itr)->TeleportTo(571, x, y, z, OutdoorPvPAttackersTower[attackerstowerid][3]);
    }

    for (PlayerSet::iterator itr = m_players[getDefenderTeam()].begin(); itr != m_players[getDefenderTeam()].end(); ++itr)
    {
        if (!(*itr))
            return;

        float x, y, z;
        x = 5330.0f + float(irand(-6, 6));
        y = 2842.0f + float(irand(-6, 6));
        z = (*itr)->GetBaseMap()->GetHeight(x, y, 409.939807f + 5);

        (*itr)->TeleportTo(571, x, y, z, 0); 
    }

    // Remove All Wintergrasp auras. Add Recruit rank and Tower Control
    for (PlayerSet::iterator itr = m_players[getAttackerTeam()].begin(); itr != m_players[getAttackerTeam()].end(); ++itr)
    {
        (*itr)->RemoveAurasDueToSpell(SPELL_RECRUIT);
        (*itr)->RemoveAurasDueToSpell(SPELL_CORPORAL);
        (*itr)->RemoveAurasDueToSpell(SPELL_LIEUTENANT);
        (*itr)->RemoveAurasDueToSpell(SPELL_TOWER_CONTROL);
        (*itr)->RemoveAurasDueToSpell(SPELL_SPIRITUAL_IMMUNITY);
        if ((*itr)->getLevel() > 74)
        {
            (*itr)->SetAuraStack(SPELL_TOWER_CONTROL, (*itr), 3);
            (*itr)->CastSpell(*itr, SPELL_RECRUIT, true);
        }
    }

    // Remove All Wintergrasp auras. Add Recruit rank
    for (PlayerSet::iterator itr = m_players[getDefenderTeam()].begin(); itr != m_players[getDefenderTeam()].end(); ++itr)
    {
        (*itr)->RemoveAurasDueToSpell(SPELL_RECRUIT);
        (*itr)->RemoveAurasDueToSpell(SPELL_CORPORAL);
        (*itr)->RemoveAurasDueToSpell(SPELL_LIEUTENANT);
        (*itr)->RemoveAurasDueToSpell(SPELL_TOWER_CONTROL);
        (*itr)->RemoveAurasDueToSpell(SPELL_SPIRITUAL_IMMUNITY);
        if ((*itr)->getLevel() > 74)
            (*itr)->CastSpell(*itr, SPELL_RECRUIT, true);
    }
    UpdateTenacityStack();
    // Update timer in players battlegrounds tab
    sWorld->SendWintergraspState();
    SaveData();
}

void OutdoorPvPWG::EndBattle()
{
    timer_30m = false;
    timer_10m = false;

    // Cast Essence of Wintergrasp to all players (CheckCast will determine who to cast)
    SetControllingTeamId(getDefenderTeam());
    sWorld->UpdateAreaDependentAuras();

    StopAllWGEvents();
    SpawnDefenders();

    //Sound on End Battle
    for (PlayerSet::iterator itr = m_players[getDefenderTeam()].begin(); itr != m_players[getDefenderTeam()].end(); ++itr)
    {
        if (getDefenderTeam()==TEAM_ALLIANCE)
            TeamIDsound=OutdoorPvP_WG_SOUND_ALLIANCE_WINS; //Allience Win
        else
            TeamIDsound=OutdoorPvP_WG_SOUND_HORDE_WINS;  //Horde Win
        (*itr)->PlayDirectSound(TeamIDsound) ; // SoundOnEndWin
    }

    for (PlayerSet::iterator itr = m_players[getAttackerTeam()].begin(); itr != m_players[getAttackerTeam()].end(); ++itr)
        (*itr)->PlayDirectSound(OutdoorPvP_WG_SOUND_NEAR_VICTORY) ; // SoundOnEndLoose

    for (uint32 team = 0; team < 2; ++team)
    {
        // destroyed all vehicles
        while(!m_vehicles[team].empty())
        {
            Creature *veh = *m_vehicles[team].begin();
            m_vehicles[team].erase(m_vehicles[team].begin());
            veh->setDeathState(JUST_DIED);
        }

        if (m_players[team].empty())
            continue;

        for (PlayerSet::iterator itr = m_players[team].begin(); itr != m_players[team].end(); ++itr)
        {
            // When WG ends the zone is cleaned including corpses, revive all players if dead
            if ((*itr)->isDead())
            {
                (*itr)->ResurrectPlayer(1.0f);
                sObjectAccessor->ConvertCorpseForPlayer((*itr)->GetGUID());
            }
            (*itr)->RemoveAurasDueToSpell(SPELL_TENACITY);
            (*itr)->CombatStop(true);
            (*itr)->getHostileRefManager().deleteReferences();
        }

        if (m_timer == 1) // Battle End was forced so no reward.
        {
            for (PlayerSet::iterator itr = m_players[team].begin(); itr != m_players[team].end(); ++itr)
            {
                (*itr)->RemoveAurasDueToSpell(SPELL_RECRUIT);
                (*itr)->RemoveAurasDueToSpell(SPELL_CORPORAL);
                (*itr)->RemoveAurasDueToSpell(SPELL_LIEUTENANT);
                (*itr)->RemoveAurasDueToSpell(SPELL_TOWER_CONTROL);
                (*itr)->RemoveAurasDueToSpell(SPELL_SPIRITUAL_IMMUNITY);
            }
            continue;
        }

        // calculate rewards
        uint32 intactNum = 0;
        uint32 damagedNum = 0;
        for (OutdoorPvP::OPvPCapturePointMap::const_iterator itr = m_capturePoints.begin(); itr != m_capturePoints.end(); ++itr)
            if (OPvPCapturePointWG *workshop = dynamic_cast<OPvPCapturePointWG*>(itr->second))
                if (workshop->m_buildingState->GetTeam() == team)
                    if (workshop->m_buildingState->damageState == DAMAGE_DAMAGED)
                        ++damagedNum;
                    else if (workshop->m_buildingState->damageState == DAMAGE_INTACT)
                        ++intactNum;

        uint32 spellRewardId = team == getDefenderTeam() ? SPELL_VICTORY_REWARD : SPELL_DEFEAT_REWARD;
        uint32 baseHonor = 0;
        uint32 marks = 0;
        uint32 playersWithRankNum = 0;
        uint32 honor = 0;

        if (sWorld->getBoolConfig(CONFIG_OUTDOORPVP_WINTERGRASP_CUSTOM_HONOR))
        {
            // Calculate Level 70+ with Corporal or Lieutenant rank
            for (PlayerSet::iterator itr = m_players[team].begin(); itr != m_players[team].end(); ++itr)
                if ((*itr)->getLevel() > 74 && ((*itr)->HasAura(SPELL_LIEUTENANT) || (*itr)->HasAura(SPELL_CORPORAL)))
                    ++playersWithRankNum;

            baseHonor = team == getDefenderTeam() ? sWorld->getIntConfig(CONFIG_OUTDOORPVP_WINTERGRASP_WIN_BATTLE) : sWorld->getIntConfig(CONFIG_OUTDOORPVP_WINTERGRASP_LOSE_BATTLE);
            baseHonor += (sWorld->getIntConfig(CONFIG_OUTDOORPVP_WINTERGRASP_DAMAGED_TOWER) * m_towerDamagedCount[OTHER_TEAM(team)]);
            baseHonor += (sWorld->getIntConfig(CONFIG_OUTDOORPVP_WINTERGRASP_DESTROYED_TOWER) * m_towerDestroyedCount[OTHER_TEAM(team)]);
            baseHonor += (sWorld->getIntConfig(CONFIG_OUTDOORPVP_WINTERGRASP_INTACT_BUILDING) * intactNum);
            baseHonor += (sWorld->getIntConfig(CONFIG_OUTDOORPVP_WINTERGRASP_DAMAGED_BUILDING) * damagedNum);
            if (playersWithRankNum)
                baseHonor /= playersWithRankNum;
        }

        for (PlayerSet::iterator itr = m_players[team].begin(); itr != m_players[team].end(); ++itr)
        {
            if ((*itr)->getLevel() < 75)
                continue; // No rewards for level <75

            // give rewards
            if (sWorld->getBoolConfig(CONFIG_OUTDOORPVP_WINTERGRASP_CUSTOM_HONOR))
            {
                if (team == getDefenderTeam())
                {
                    if ((*itr)->HasAura(SPELL_LIEUTENANT))
                    {
                        marks = 3;
                        honor = baseHonor;
                    }
                    else if ((*itr)->HasAura(SPELL_CORPORAL))
                    {
                        marks = 2;
                        honor = baseHonor;
                    }
                    else
                    {
                        marks = 1;
                        honor = 0;
                    }
                }
                else
                {
                    if ((*itr)->HasAura(SPELL_LIEUTENANT))
                    {
                        marks = 1;
                        honor = baseHonor;
                    }
                    else if ((*itr)->HasAura(SPELL_CORPORAL))
                    {
                        marks = 1;
                        honor = baseHonor;
                    }
                    else
                    {
                        marks = 0;
                        honor = 0;
                    }
                }
                (*itr)->RewardHonor(NULL, 1, honor);
                RewardMarkOfHonor(*itr, marks);
                (*itr)->GetAchievementMgr().UpdateAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_BE_SPELL_TARGET, spellRewardId);
            }
            else
            {
                if ((*itr)->HasAura(SPELL_LIEUTENANT) || (*itr)->HasAura(SPELL_CORPORAL))
                {
                    // TODO - Honor from SpellReward should be shared by team players
                    // TODO - Marks should be given depending on Rank but 3 are given
                    // each time so Won't give any to recruits
                    (*itr)->CastSpell(*itr, spellRewardId, true);
                    for (uint32 i = 0; i < intactNum; ++i)
                        (*itr)->CastSpell(*itr, SPELL_INTACT_BUILDING, true);
                    for (uint32 i = 0; i < damagedNum; ++i)
                        (*itr)->CastSpell(*itr, SPELL_DAMAGED_BUILDING, true);
                    for (uint32 i = 0; i < m_towerDamagedCount[OTHER_TEAM(team)]; ++i)
                        (*itr)->CastSpell(*itr, SPELL_DAMAGED_TOWER, true);
                    for (uint32 i = 0; i < m_towerDestroyedCount[OTHER_TEAM(team)]; ++i)
                        (*itr)->CastSpell(*itr, SPELL_DESTROYED_TOWER, true);
                }
            }
            if (team == getDefenderTeam())
            {
                if ((*itr)->HasAura(SPELL_LIEUTENANT) || (*itr)->HasAura(SPELL_CORPORAL))
                {
                    (*itr)->AreaExploredOrEventHappens(A_VICTORY_IN_WG);
                    (*itr)->AreaExploredOrEventHappens(H_VICTORY_IN_WG);
                }
            }
            (*itr)->RemoveAurasDueToSpell(SPELL_RECRUIT);
            (*itr)->RemoveAurasDueToSpell(SPELL_CORPORAL);
            (*itr)->RemoveAurasDueToSpell(SPELL_LIEUTENANT);
            (*itr)->RemoveAurasDueToSpell(SPELL_TOWER_CONTROL);
            (*itr)->RemoveAurasDueToSpell(SPELL_SPIRITUAL_IMMUNITY);

            if (team != GetControllingTeamID())
            {
                if (!(*itr)->isGameMaster())
                    (*itr)->CastSpell(*itr, SPELL_TELEPORT_DALARAN, true);
            }
        }
    }

    m_wartime = false;
    m_timer = sWorld->getIntConfig(CONFIG_OUTDOORPVP_WINTERGRASP_INTERVAL) * MINUTE * IN_MILLISECONDS;
    RemoveOfflinePlayerWGAuras();
    // Update timer in players battlegrounds tab
    sWorld->SendWintergraspState();
}

void OutdoorPvPWG::StopAllWGEvents()
{
    sGameEventMgr->StopEvent(WG_EVENT_BATTLE, true);
    sGameEventMgr->StopEvent(WG_EVENT_A_DEF, true);
    sGameEventMgr->StopEvent(WG_EVENT_H_DEF, true);
}

void OutdoorPvPWG::SpawnDefenders()
{
    sGameEventMgr->StartEvent(getDefenderTeam() == TEAM_ALLIANCE ? WG_EVENT_A_DEF: WG_EVENT_H_DEF, true);
}

void OutdoorPvPWG::SpawnBattle()
{
    sGameEventMgr->StartEvent(WG_EVENT_BATTLE, true);
}

bool OutdoorPvPWG::CanBuildVehicle(OPvPCapturePointWG *workshop) const
{
    TeamId team = workshop->m_buildingState->GetTeam();
    if (team == TEAM_NEUTRAL)
        return false;

    return isWarTime()
        && workshop->m_buildingState->damageState != DAMAGE_DESTROYED
        && m_vehicles[team].size() < m_workshopCount[team] * MAX_VEHICLE_PER_WORKSHOP;
}

uint32 OutdoorPvPWG::GetData(uint32 id)
{
    // if can build more vehicles
    if (OPvPCapturePointWG *workshop = GetWorkshopByEngGuid(id))
        return CanBuildVehicle(workshop) ? 1 : 0;

    return 0;
}

void OutdoorPvPWG::RewardMarkOfHonor(Player *plr, uint32 count)
{
    // 'Inactive' this aura prevents the player from gaining honor points and battleground tokens
    if (plr->HasAura(SPELL_AURA_PLAYER_INACTIVE))
        return;
    if (count == 0)
        return;

    ItemPosCountVec dest;
    uint32 no_space_count = 0;
    uint8 msg = plr->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, WG_MARK_OF_HONOR, count, &no_space_count);

    if (msg == EQUIP_ERR_ITEM_NOT_FOUND)
    {
        sLog->outErrorDb("Wintergrasp reward item (Entry %u) not exist in `item_template`.", WG_MARK_OF_HONOR);
        return;
    }

    if (msg != EQUIP_ERR_OK) // convert to possible store amount
        count -= no_space_count;

    if (count != 0 && !dest.empty()) // can add some
        if (Item* item = plr->StoreNewItem(dest, WG_MARK_OF_HONOR, true, 0))
            plr->SendNewItem(item, count, true, false);
}

OPvPCapturePointWG *OutdoorPvPWG::GetWorkshop(uint32 lowguid) const
{
    if (OPvPCapturePoint *cp = GetCapturePoint(lowguid))
        return dynamic_cast<OPvPCapturePointWG*>(cp);
    return NULL;
}

OPvPCapturePointWG *OutdoorPvPWG::GetWorkshopByEngGuid(uint32 lowguid) const
{
    for (OutdoorPvP::OPvPCapturePointMap::const_iterator itr = m_capturePoints.begin(); itr != m_capturePoints.end(); ++itr)
        if (OPvPCapturePointWG *workshop = dynamic_cast<OPvPCapturePointWG*>(itr->second))
            if (workshop->m_engGuid == lowguid)
                return workshop;
    return NULL;
}

OPvPCapturePointWG *OutdoorPvPWG::GetWorkshopByGOGuid(uint64 lowguid) const
{
    for (OutdoorPvP::OPvPCapturePointMap::const_iterator itr = m_capturePoints.begin(); itr != m_capturePoints.end(); ++itr)
        if (OPvPCapturePointWG *workshop = dynamic_cast<OPvPCapturePointWG*>(itr->second))
            if (workshop->m_workshopGuid == lowguid)
                return workshop;
    return NULL;
}

/*########################################################
 * Copy of Battleground system to make Spirit Guides Work
 *#######################################################*/
void OutdoorPvPWG::SendAreaSpiritHealerQueryOpcode(Player *pl, const uint64& guid)
{
    WorldPacket data(SMSG_AREA_SPIRIT_HEALER_TIME, 12);
    uint32 time_ = 30000 - GetLastResurrectTime();      // resurrect every 30 seconds
    if (time_ == uint32(-1))
        time_ = 0;
    data << guid << time_;
    pl->GetSession()->SendPacket(&data);
}

void OutdoorPvPWG::AddPlayerToResurrectQueue(uint64 npc_guid, uint64 player_guid)
{
    m_ReviveQueue[npc_guid].push_back(player_guid);

    Player *plr = sObjectMgr->GetPlayer(player_guid);
    if (!plr)
        return;

    plr->CastSpell(plr, SPELL_WAITING_FOR_RESURRECT, true);
}

void OutdoorPvPWG::RemovePlayerFromResurrectQueue(uint64 player_guid)
{
    for (std::map<uint64, std::vector<uint64> >::iterator itr = m_ReviveQueue.begin(); itr != m_ReviveQueue.end(); ++itr)
    {
        for (std::vector<uint64>::iterator itr2 =(itr->second).begin(); itr2 != (itr->second).end(); ++itr2)
        {
            if (*itr2 == player_guid)
            {
                (itr->second).erase(itr2);

                Player *plr = sObjectMgr->GetPlayer(player_guid);
                if (!plr)
                    return;

                plr->RemoveAurasDueToSpell(SPELL_WAITING_FOR_RESURRECT);

                return;
            }
        }
    }
}

void OutdoorPvPWG::RelocateAllianceDeadPlayers(Creature *cr)
{
    if (!cr || GetCreatureType(cr->GetEntry()) != CREATURE_SPIRIT_GUIDE)
        return;

    // Those who are waiting to resurrect at this node are taken to the closest own node's graveyard
    std::vector<uint64> ghost_list = m_ReviveQueue[cr->GetGUID()];
    if (!ghost_list.empty())
    {
        WorldSafeLocsEntry const *ClosestGrave = NULL;
        for (std::vector<uint64>::const_iterator itr = ghost_list.begin(); itr != ghost_list.end(); ++itr)
        {
            Player* plr = sObjectMgr->GetPlayer(*itr);
            if (!plr)
                continue;

            if (plr->getFaction() == ALLIANCE)
            {
                if (ClosestGrave)
                    plr->TeleportTo(plr->GetMapId(), ClosestGrave->x, ClosestGrave->y, ClosestGrave->z, plr->GetOrientation());
                else
                    ClosestGrave = sObjectMgr->GetClosestGraveYard(plr->GetPositionX(), plr->GetPositionY(), plr->GetPositionZ(), plr->GetMapId(), plr->GetTeam());
            }
        }
    }
}

void OutdoorPvPWG::RelocateHordeDeadPlayers(Creature *cr)
{
    if (!cr || GetCreatureType(cr->GetEntry()) != CREATURE_SPIRIT_GUIDE)
        return;

    // Those who are waiting to resurrect at this node are taken to the closest own node's graveyard
    std::vector<uint64> ghost_list = m_ReviveQueue[cr->GetGUID()];
    if (!ghost_list.empty())
    {
        WorldSafeLocsEntry const *ClosestGrave = NULL;
        for (std::vector<uint64>::const_iterator itr = ghost_list.begin(); itr != ghost_list.end(); ++itr)
        {
            Player* plr = sObjectMgr->GetPlayer(*itr);
            if (!plr)
                continue;
            if (plr->getFaction() == HORDE)
            {
                if (ClosestGrave)
                    plr->TeleportTo(plr->GetMapId(), ClosestGrave->x, ClosestGrave->y, ClosestGrave->z, plr->GetOrientation());
                else
                    ClosestGrave = sObjectMgr->GetClosestGraveYard(plr->GetPositionX(), plr->GetPositionY(), plr->GetPositionZ(), plr->GetMapId(), plr->GetTeam());
            }
        }
    }
}

OPvPCapturePointWG::OPvPCapturePointWG(OutdoorPvPWG *opvp, BuildingState *state) : OPvPCapturePoint(opvp), m_buildingState(state), m_wintergrasp(opvp), m_engineer(NULL), m_engGuid(0), m_spiritguide(NULL), m_spiritguide_horde(NULL), m_spiritguide_alliance(NULL), m_spiGuid(0) { }

void OPvPCapturePointWG::SetTeamByBuildingState()
{
    if (m_buildingState->GetTeam() == TEAM_ALLIANCE)
    {
        m_value = m_maxValue;
        m_State = OBJECTIVESTATE_ALLIANCE;
    }
    else if (m_buildingState->GetTeam() == TEAM_HORDE)
    {
        m_value = -m_maxValue;
        m_State = OBJECTIVESTATE_HORDE;
    }
    else
    {
        m_value = 0;
        m_State = OBJECTIVESTATE_NEUTRAL;
    }

    if (m_team != m_buildingState->GetTeam())
    {
        TeamId oldTeam = m_team;
        m_team = m_buildingState->GetTeam();
        ChangeTeam(oldTeam);
    }

    SendChangePhase();
}

void OPvPCapturePointWG::ChangeTeam(TeamId oldTeam)
{
    entry = 0;
    guide_entry = 0;
    guide_entry_fortress_horde = 0;
    guide_entry_fortress_alliance = 0;

    if (oldTeam != TEAM_NEUTRAL)
        m_wintergrasp->ModifyWorkshopCount(oldTeam, false);

    if (m_team != TEAM_NEUTRAL)
    {
        entry = m_team == TEAM_ALLIANCE ? CRE_ENG_A : CRE_ENG_H;
        guide_entry = m_team == TEAM_ALLIANCE ? CRE_SPI_A : CRE_SPI_H;
        guide_entry_fortress_horde = m_team == TEAM_HORDE ? CRE_SPI_H : CRE_SPI_H;
        guide_entry_fortress_alliance = m_team == TEAM_ALLIANCE ? CRE_SPI_A : CRE_SPI_A;
        m_wintergrasp->ModifyWorkshopCount(m_team, true);
    }

    if (m_capturePoint)
        GameObject::SetGoArtKit(CapturePointArtKit[m_team], m_capturePoint, m_capturePointGUID);

    m_buildingState->SetTeam(m_team);
    // TODO: this may be sent twice
    m_wintergrasp->BroadcastStateChange(m_buildingState);
    
    if (m_buildingState->building)
        m_buildingState->building->SetUInt32Value(GAMEOBJECT_FACTION, WintergraspFaction[m_team]);

    if (entry)
    {
        if (m_engGuid)
        {
            *m_engEntry = entry;
            _RespawnCreatureIfNeeded(m_engineer, entry);
        }
        if (m_spiGuid)
        {
            if (m_wintergrasp->getAttackerTeam() == TEAM_ALLIANCE)
            {
                *m_spiEntry = guide_entry;
                _RespawnCreatureIfNeeded(m_spiritguide_horde, guide_entry_fortress_horde);
                m_wintergrasp->RelocateHordeDeadPlayers(m_spiritguide_horde); // Horde
                _RespawnCreatureIfNeeded(m_spiritguide, guide_entry);
                m_wintergrasp->RelocateAllianceDeadPlayers(m_spiritguide); // Alliance
            }
            else
            {
                *m_spiEntry = guide_entry;
                _RespawnCreatureIfNeeded(m_spiritguide_alliance, guide_entry_fortress_alliance);
                m_wintergrasp->RelocateAllianceDeadPlayers(m_spiritguide_alliance); // Alliance
                _RespawnCreatureIfNeeded(m_spiritguide, guide_entry);
                m_wintergrasp->RelocateHordeDeadPlayers(m_spiritguide); // Horde
            }
        }
    }
    else if (m_engineer)
        m_engineer->SetVisible(false);

    sLog->outDebug(LOG_FILTER_OUTDOORPVP, "Wintergrasp workshop now belongs to %u.", (uint32)m_buildingState->GetTeam());
}

class OutdoorPvP_wintergrasp : public OutdoorPvPScript
{
    public:
        OutdoorPvP_wintergrasp() : OutdoorPvPScript("outdoorpvp_wg") { }
        
        OutdoorPvP* GetOutdoorPvP() const
        {
            return new OutdoorPvPWG();
        }
};

void AddSC_outdoorpvp_wg()
{
    new OutdoorPvP_wintergrasp();
}