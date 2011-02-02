#include "ScriptPCH.h"
#include "eye_of_eternity.h"
#include "WorldPacket.h"

#define DISABLED_ENTER_MESSAGE "You cannot enter Eye of Eternity now"
#define EXIT_MAP 571
#define EXIT_X 3845.7653f
#define EXIT_Y 6994.2817f
#define EXIT_Z 86.0937f

class instance_eye_of_eternity : public InstanceMapScript
{
public:
    instance_eye_of_eternity() : InstanceMapScript("instance_eye_of_eternity", 616) {}

    InstanceScript* GetInstanceScript(InstanceMap* pMap) const
    {
        return new instance_eye_of_eternity_InstanceScript(pMap);
    }

    struct instance_eye_of_eternity_InstanceScript : public InstanceScript
    {
        instance_eye_of_eternity_InstanceScript(Map* pMap) : InstanceScript(pMap) {Initialize();}
     
        std::string strInstData;
        uint32 m_auiEncounter;
        uint32 m_uiOutroCheck;
        uint32 m_uiMalygosPlatformData;
     
        uint64 m_uiMalygosPlatformGUID;
        uint64 m_uiFocusingIrisGUID;
        uint64 m_uiExitPortalGUID;
     
        uint64 m_uiMalygosGUID;
	    uint64 m_AlexstraszaGUID;
        uint64 m_uiPlayerCheckGUID;
        
        bool m_bVortex;    
     
        void Initialize()
        {
		    m_auiEncounter = NOT_STARTED;           
            m_uiMalygosGUID = 0;
            m_uiOutroCheck = 0; 
            m_uiMalygosPlatformData = 0;
            m_uiMalygosPlatformGUID = 0;
            m_uiFocusingIrisGUID = 0;
            m_uiExitPortalGUID = 0;
            m_uiPlayerCheckGUID = 0;
            m_bVortex = false;
        }
        
        void OnCreatureCreate(Creature* pCreature)
        {
            switch(pCreature->GetEntry())
            {
                case NPC_MALYGOS:
                    m_uiMalygosGUID = pCreature->GetGUID();
                    break;
                default:
                    break;
            }
        }
        
        void OnGameObjectCreate(GameObject *pGo)
        {
            switch(pGo->GetEntry())
            {
                case 193070: m_uiMalygosPlatformGUID = pGo->GetGUID(); break;
                case 193958: //normal,hero
                case 193960: m_uiFocusingIrisGUID = pGo->GetGUID(); break;
                case 193908: m_uiExitPortalGUID = pGo->GetGUID(); break;
                default:
                    break;
            }
        }
     
        bool IsEncounterInProgress() const
        {
		    if (m_auiEncounter == IN_PROGRESS)
			    return true;
     
		    return false;
        }
     
        void SetData(uint32 uiType, uint32 uiData)
        {
            switch(uiType)
            {
                case TYPE_MALYGOS:
                    if (uiData == IN_PROGRESS)
                    {
                        if(GameObject* m_uiExitPortal = instance->GetGameObject(m_uiExitPortalGUID))
                            m_uiExitPortal->SetPhaseMask(0, true);
                        if(GameObject* m_uiFocusingIris = instance->GetGameObject(m_uiFocusingIrisGUID))
                            m_uiFocusingIris->SetPhaseMask(0, true);
                    }
                    if (uiData == NOT_STARTED)
                    {
                        //Summon Platform
                        SetData(TYPE_DESTROY_PLATFORM, NOT_STARTED);
                        //Summon focusing iris
					    if(GameObject* pGo = instance->GetGameObject(m_uiFocusingIrisGUID))
						    pGo->SetPhaseMask(1, true);
                        //Summon exit portal
                        if(GameObject* pGo = instance->GetGameObject(m_uiExitPortalGUID))
                            pGo->SetPhaseMask(1, true);
                    }
                    m_auiEncounter = uiData;
                    break;
                case TYPE_OUTRO_CHECK:
                    m_uiOutroCheck = uiData;
                    break;
                case TYPE_DESTROY_PLATFORM:
                    if(uiData == IN_PROGRESS)
                    {
                        if(GameObject* m_uiMalygosPlatform = instance->GetGameObject(m_uiMalygosPlatformGUID))
                            m_uiMalygosPlatform->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_DESTROYED);
                    }
                    else if(uiData == NOT_STARTED)
                    {
                        if(GameObject* m_uiMalygosPlatform = instance->GetGameObject(m_uiMalygosPlatformGUID))
                        {
                            m_uiMalygosPlatform->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_DESTROYED);
                            m_uiMalygosPlatform->Respawn();
                        }
                    }
                    m_uiMalygosPlatformData = uiData;
                    break;
                case TYPE_VORTEX:
                    if(uiData)
                        m_bVortex = true;
                    else
                        m_bVortex = false;
                    break;
                case TYPE_PLAYER_HOVER:
                    if(uiData == DATA_DROP_PLAYERS)
                        dropAllPlayers();
                    break;
            }
        }

        std::string GetSaveData()
        {
            OUT_SAVE_INST_DATA;
            std::ostringstream saveStream;
            saveStream << m_auiEncounter << " " << m_uiOutroCheck;

            strInstData = saveStream.str();
            SaveToDB();
            OUT_SAVE_INST_DATA_COMPLETE;
            return strInstData.c_str();
        }

        void Load(const char* chrIn)
        {
            if (!chrIn)
            {
                OUT_LOAD_INST_DATA_FAIL;
                return;
            }
     
            OUT_LOAD_INST_DATA(chrIn);
     
            std::istringstream loadStream(chrIn);
            loadStream >> m_auiEncounter >> m_uiOutroCheck;
     
		    if (m_auiEncounter == IN_PROGRESS)
			    m_auiEncounter = NOT_STARTED;

     
            OUT_LOAD_INST_DATA_COMPLETE;
        }
     
        uint32 GetData(uint32 uiType)
        {
            switch(uiType)
            {
                case TYPE_MALYGOS:
                    return m_auiEncounter;
                case TYPE_OUTRO_CHECK:
                    return m_uiOutroCheck;
                case TYPE_DESTROY_PLATFORM:
                    return m_uiMalygosPlatformData;
                case TYPE_VORTEX:
                    return m_bVortex;
            }
            return 0;
        }
     
        uint64 GetData64(uint32 uiData)
        {
            switch(uiData)
            {
                case NPC_MALYGOS:
                    return m_uiMalygosGUID;
			    case DATA_PLATFORM:
				    return m_uiMalygosPlatformGUID;
			    case DATA_EXIT_PORTAL:
				    return m_uiExitPortalGUID;
                default:
                    return 0;
            }
            return 0;
        }

        void dropAllPlayers()
        {
            Map::PlayerList const &PlayerList = instance->GetPlayers();

            if (!PlayerList.isEmpty())
                for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                    if (Player *pPlayer = i->getSource())
                        if (Unit* pDisk = pPlayer->GetVehicleBase())
                        {
                            pPlayer->ExitVehicle();
                            pDisk->ToCreature()->ForcedDespawn();
                        }
        }

        /*void OnPlayerEnter(Player* pPlayer)
        {
            if(GetData(TYPE_MALYGOS) == DONE)
            {
                Creature *pTemp = pPlayer->SummonCreature(NPC_WYRMREST_SKYTALON, pPlayer->GetPositionX(), pPlayer->GetPositionY(), pPlayer->GetPositionZ() - 5, 0);
                if(pTemp)
                {
                    pTemp->SetCreatorGUID(pPlayer->GetGUID());
                    pPlayer->EnterVehicle(pTemp, 0);
                }
            }
		    if (GetData(TYPE_MALYGOS) == IN_PROGRESS)
		    {
			    pPlayer->MonsterTextEmote(DISABLED_ENTER_MESSAGE, pPlayer->GetGUID(), true);
			    pPlayer->TeleportTo(EXIT_MAP, EXIT_X, EXIT_Y, EXIT_Z, 0);
			    return;
		    }
    		
        }*/
    };
};

void AddSC_instance_eye_of_eternity()
{
    new instance_eye_of_eternity;
}