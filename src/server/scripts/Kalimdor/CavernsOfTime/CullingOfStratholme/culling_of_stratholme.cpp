/*
 * Copyright (C) 2010-2011 Izb00shka <http://izbooshka.net/>
 * Copyright (C) 2008-2011 TrinityCore <http://www.trinitycore.org/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "ScriptPCH.h"
#include "culling_of_stratholme.h"
#include "ScriptedEscortAI.h"
#include "WorldPacket.h"
 
/*###
## npc_arthas
###*/
 
 enum
 {
    SAY_INTRO01                           = -1594071,    //Arthas
    SAY_INTRO02                           = -1594072,    //Uther
    SAY_INTRO03                           = -1594073,    //Arthas
    SAY_INTRO04                           = -1594074,    //Arthas
    SAY_INTRO05                           = -1594075,    //Uther
    SAY_INTRO06                           = -1594076,    //Arthas
    SAY_INTRO07                           = -1594077,    //Uther
    SAY_INTRO08                           = -1594078,    //Arthas
    SAY_INTRO09                           = -1594079,    //Arthas
    SAY_INTRO10                           = -1594080,    //Uther
    SAY_INTRO11                           = -1594081,    //Arthas
    SAY_INTRO12                           = -1594082,    //Uther
    SAY_INTRO13                           = -1594083,    //Jaina
    SAY_INTRO14                           = -1594084,    //Arthas
    SAY_INTRO15                           = -1594085,    //Uther
    SAY_INTRO16                           = -1594086,    //Arthas
    SAY_INTRO17                           = -1594087,    //Jaina
    SAY_INTRO18                           = -1594088,    //Arthas
    SAY_ENTER01                           = -1594089,    //Arthas
    SAY_ENTER02                           = -1594090,    //Cityman
    SAY_ENTER03                           = -1594091,    //Arthas
    SAY_ENTER04                           = -1594092,    //Crazyman
    SAY_ENTER05                           = -1594093,    //Crazyman2
    SAY_ENTER06                           = -1594094,    //Arthas
    SAY_ENTER07                           = -1594095,    //Malganis
    SAY_ENTER08                           = -1594096,    //Malganis
    SAY_ENTER09                           = -1594097,    //Arthas
    SAY_ENTER10                           = -1594098,    //Arthas
    SAY_SALRAMM_SPAWN                     = -1594129, 
    SAY_MEATHOOK_SPAWN                    = -1594110, 
    SAY_PHASE501                          = -1594142,    //Arthas
    SAY_PHASE502                          = -1594143,    //Arthas
    SAY_PHASE503                          = -1594144,    //Human
    SAY_PHASE504                          = -1594145,    //Arthas
    SAY_PHASE505                          = -1594146,    //Arthas
    SAY_PHASE506                          = -1594147,    //Human
    SAY_PHASE507                          = -1594148,    //Arthas
    SAY_PHASE508                          = -1594149,    //Arthas
    SAY_PHASE509                          = -1594150,    //Arthas
    SAY_PHASE510                          = -1594151,    //Arthas
    SAY_PHASE511                          = -1594152,    //Arthas
    SAY_PHASE512                          = -1594153,    //Arthas
    SAY_PHASE513                          = -1594154,    //Arthas
 
    SAY_EPOCH_INTRO                       = -1594155, 
    SAY_ARTHAS_INTRO                      = -1594156, 
    SAY_EPOCH_AGGRO                       = -1594157, 
 
    SAY_PHASE514                        = -1594158,   //Arthas Shkaf 01
    SAY_PHASE515                        = -1594159,   //Arthas Shkaf 02
    SAY_PHASE601                        = -1594160,  //Arthas Fire
    SAY_PHASE602                        = -1594161,  //Arthas Picnic
    SAY_PHASE603                        = -1594162,  //Arthas Picnic End
    SAY_PHASE604                        = -1594163, 
    SAY_PHASE605                        = -1594164,  //Arthas mall start
 
    SAY_MALGANIS_ESCAPE02    = -1594180, 
    SAY_MALGANIS_ESCAPE01    = -1594187, 
    SAY_MALGANIS_OUTRO       = -1594182, 
    SAY_ARTHAS_OUTRO01       = -1594181, 
    SAY_ARTHAS_OUTRO02       = -1594183, 
    SAY_ARTHAS_OUTRO03       = -1594184, 
 
    /*NPC*/
    NPC_CITYMAN                    = 28167, 
    NPC_CRAZYMAN                   = 28169, 
    NPC_MALGANIS_INTRO             = 26533, 

    /*OTHER*/
    POINT_LAST_POINT    = 0xFFFFFF, 
    FACTION             = 2076
};

enum ArthasSpells
{
    SPELL_EXORCISM_N          = 52445, 
    SPELL_EXORCISM_H          = 58822, 
    SPELL_HOLY_LIGHT          = 52444, 
    SPELL_ARTHAS_AURA         = 52442,
};

const float SummonScourge[2][4] =
 {
    {2340.058f, 1253.570f, 132.733f, 5.09f}, //right wing
    {2272.773f, 1331.824f, 124.171f, 3.12f}, //left wing
};
 
/*###
## npc_arthas_priest
###*/

enum
{
    SPELL_SMITE         = 61923, 
    SPELL_HEAL          = 62442
};

/*###
## npc_arthas_dialog
###*/

enum
{
    GOSSIP_MENU_ARTHAS_1                        = 100001, 
    GOSSIP_MENU_ARTHAS_2                        = 100002, 
    GOSSIP_MENU_ARTHAS_3                        = 100003, 
    GOSSIP_MENU_ARTHAS_4                        = 100004, 
    GOSSIP_MENU_ARTHAS_5                        = 100005
};

#define GOSSIP_ITEM_ARTHAS_0 "I'm ready to start Culling of Stratholme."
#define GOSSIP_ITEM_ARTHAS_1 "Yes, my Prince. We're ready."
#define GOSSIP_ITEM_ARTHAS_2 "We're only doing what is best for Loarderon your Highness."
#define GOSSIP_ITEM_ARTHAS_3 "I'm ready."
#define GOSSIP_ITEM_ARTHAS_4 "For Lordaeron!"
#define GOSSIP_ITEM_ARTHAS_5 "I'm ready to battle the dreadlord, sire."

#define GOSSIP_ITEM_ARTHAS_0_RU "Я готов приступить к очищению Стратхольма."
#define GOSSIP_ITEM_ARTHAS_1_RU "Да, мой принц. Мы готовы."
#define GOSSIP_ITEM_ARTHAS_2_RU "Ваше высочество, всё, что мы делаем - мы делаем во благо Лордерона."
#define GOSSIP_ITEM_ARTHAS_3_RU "Я готов."
#define GOSSIP_ITEM_ARTHAS_4_RU "За Лордерон!"
#define GOSSIP_ITEM_ARTHAS_5_RU "Я готов к битве с Повелителем ужаса, сир."
 
    
class npc_arthas_priest : public CreatureScript
{
public:
    npc_arthas_priest() : CreatureScript("npc_arthas_priest") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_arthas_priestAI(pCreature);
    }

    struct npc_arthas_priestAI : public ScriptedAI
    {
        npc_arthas_priestAI(Creature *c) : ScriptedAI(c)
        {
            SetCombatMovement(false);
            Reset();
        }

        uint32 m_uiSmiteTimer;
        uint32 m_uiHealTimer;

        void Reset() 
        {
            m_uiSmiteTimer = 100;
            m_uiHealTimer = 1000;
        }

        void AttackStart(Unit* pWho)
        {
            if (!pWho)
                return;

            if (me->Attack(pWho, true))
            {
                me->AddThreat(pWho, 0.0f);
                me->SetInCombatWith(pWho);
                pWho->SetInCombatWith(me);
            }
        }

        void EnterEvadeMode()
        {
            me->RemoveAllAuras();
            me->DeleteThreatList();
            me->CombatStop(true);
            me->LoadCreaturesAddon();

            me->SetLootRecipient(NULL);

            Reset();
        }

        void MoveInLineOfSight(Unit* pWho)
        {
            if (!pWho)
                return;

            if (!me->HasUnitState(UNIT_STAT_STUNNED) && pWho->isTargetableForAttack() &&
                me->IsHostileTo(pWho) && pWho->isInAccessiblePlaceFor(me))
            {
                if (!me->canFly() && me->GetDistanceZ(pWho) > CREATURE_Z_ATTACK_RANGE)
                    return;

                float attackRadius = me->GetAttackDistance(pWho);
                if (me->IsWithinDistInMap(pWho, attackRadius) && me->IsWithinLOSInMap(pWho))
                {
                    if (!me->getVictim())
                    {
                        AttackStart(pWho);
                        pWho->RemoveAurasByType(SPELL_AURA_MOD_STEALTH);
                    }
                    else if (me->GetMap()->IsDungeon())
                    {
                        pWho->SetInCombatWith(me);
                        me->AddThreat(pWho, 0.0f);
                    }
                }
            }
        }
 
        void UpdateAI(const uint32 uiDiff)
        {

            if (!UpdateVictim())
                return;

            if(m_uiSmiteTimer < uiDiff)
            {
                DoCast(me->getVictim(), SPELL_SMITE);
                m_uiSmiteTimer = 3000;
            }
            else m_uiSmiteTimer -= uiDiff;

            if(m_uiHealTimer < uiDiff)
            {
                if(HealthBelowPct(40.0f))
                {
                    me->InterruptNonMeleeSpells(false);
                    DoCast(me, SPELL_HEAL);
                    m_uiHealTimer = 3000;
                }
            }
            else m_uiHealTimer -= uiDiff;

            DoMeleeAttackIfReady();

            return;
        }
    };
};

class npc_arthas : public CreatureScript
{
public:
    npc_arthas() : CreatureScript("npc_arthas") { }

    bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
    {
        pPlayer->PlayerTalkClass->ClearMenus();

        InstanceScript* m_pInstance = pCreature->GetInstanceScript();

        if(m_pInstance && m_pInstance->GetData(TYPE_PHASE) == 0)
        {
            m_pInstance->SetData(TYPE_PHASE, 1);
            CAST_AI(npc_arthasAI, pCreature->AI())->EnableEscort();
            CAST_AI(npc_arthasAI, pCreature->AI())->RemoveGossip();
            CAST_AI(npc_arthasAI, pCreature->AI())->culling_faction = pPlayer->getFaction();
        }

        if(m_pInstance && m_pInstance->GetData(TYPE_PHASE) == 5)
        {
            CAST_AI(npc_arthasAI, pCreature->AI())->EnableEscort();
            CAST_AI(npc_arthasAI, pCreature->AI())->RemoveGossip();
        }

        if(m_pInstance && m_pInstance->GetData(TYPE_PHASE) == 8)
        {
            CAST_AI(npc_arthasAI, pCreature->AI())->EnableEscort();
            CAST_AI(npc_arthasAI, pCreature->AI())->RemoveGossip();
        }

        if(m_pInstance && m_pInstance->GetData(TYPE_PHASE) == 9)
        {
            CAST_AI(npc_arthasAI, pCreature->AI())->EnableEscort();
            CAST_AI(npc_arthasAI, pCreature->AI())->RemoveGossip();
            if(Creature* pMalganis = pCreature->SummonCreature(NPC_MALGANIS, 2296.665f, 1502.362f, 128.362f, 4.961f, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 900000))
            {
                m_pInstance->SetData64(NPC_MALGANIS, pMalganis->GetGUID());
                pMalganis->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            }
        }

        return true; 
    }

    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
        InstanceScript* pInstance = pCreature->GetInstanceScript(); 

        if(pInstance && pInstance->GetData(TYPE_PHASE) == 0) 
        {
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, (pPlayer->isRussianLocale())? GOSSIP_ITEM_ARTHAS_1_RU:GOSSIP_ITEM_ARTHAS_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_MENU_ARTHAS_1, pCreature->GetGUID()); 
        }

        if(pInstance && pInstance->GetData(TYPE_PHASE) == 5)
        {
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, (pPlayer->isRussianLocale())? GOSSIP_ITEM_ARTHAS_2_RU:GOSSIP_ITEM_ARTHAS_2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_MENU_ARTHAS_2, pCreature->GetGUID()); 
        }

        if(pInstance && pInstance->GetData(TYPE_PHASE) == 8)
        {
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, (pPlayer->isRussianLocale())? GOSSIP_ITEM_ARTHAS_3_RU:GOSSIP_ITEM_ARTHAS_3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_MENU_ARTHAS_3, pCreature->GetGUID()); 
        }

        if(pInstance && pInstance->GetData(TYPE_PHASE) == 9)
        {
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, (pPlayer->isRussianLocale())? GOSSIP_ITEM_ARTHAS_4_RU:GOSSIP_ITEM_ARTHAS_4, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_MENU_ARTHAS_4, pCreature->GetGUID()); 
        }

        return true; 
    }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_arthasAI(pCreature);
    }

    struct npc_arthasAI : public npc_escortAI
    {
        npc_arthasAI(Creature* pCreature) : npc_escortAI(pCreature)
        {
            m_pInstance = pCreature->GetInstanceScript();
            pCreature->SetSpeed(MOVE_RUN, 1, true);
            Reset();
        }

        InstanceScript* m_pInstance;

        uint64 m_uiUtherGUID;
        uint64 m_uiJainaGUID;
        uint64 m_uiPeople01GUID;
        uint64 m_uiPeople02GUID;
        uint64 m_uiMalganisGUID;
        uint64 m_uiMarine01GUID;
        uint64 m_uiMarine02GUID;
        uint64 m_uiMarine03GUID;
        uint64 m_uiMarine04GUID;
        uint64 m_uiPriest01GUID;
        uint64 m_uiPriest02GUID;
        uint64 m_uiHuman01GUID;
        uint64 m_uiHuman02GUID;
        uint64 m_uiHuman03GUID;

        uint32 culling_faction;
        uint32 m_uiStep;
        uint32 m_uiStepTimer;
        uint32 m_uiMoveTimer;
        uint32 m_uiHealTimer;
        uint32 m_uiExorcismTimer;
        uint32 m_uiSummonTimer;
        uint32 m_uiWaveCount;

        Creature* Malganis;
        Creature* pEpoch;
        bool StartEvent;
        bool MoveSoldier;

        float LastX;
        float LastY;
        float LastZ;

        void Reset()
        {
            me->SetSpeed(MOVE_RUN, 1, true);
            if(!m_pInstance) return;

            if(m_pInstance->GetData(TYPE_INTRO) == NOT_STARTED)
            {
                me->setFaction(35);
                RemoveGossip();
            }

            if(m_pInstance->GetData(TYPE_PHASE) == 11)
            {
                me->SetVisible(false);
            }
            SetDespawnAtFar(false);
            me->setActive(true);
        }

        void RemoveGossip()
        { 
            me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER | UNIT_NPC_FLAG_GOSSIP);
        }

        void MoveSoldiers()
        {
            if(Unit* Marine01 = Unit::GetUnit((*me), m_uiMarine01GUID))
            {
                Marine01->GetMotionMaster()->MovePoint(0, 2083.483f, 1282.313f, 141.198f);
                Marine01->setFaction(culling_faction);
            }

            if(Unit* Marine02 = Unit::GetUnit((*me), m_uiMarine02GUID))
            {
                Marine02->GetMotionMaster()->MovePoint(0, 2083.681f, 1292.809f, 141.141f);
                Marine02->setFaction(culling_faction);
            }

            if(Unit* Marine03 = Unit::GetUnit((*me), m_uiMarine03GUID))
            {
                Marine03->GetMotionMaster()->MovePoint(0, 2082.158f, 1290.406f, 141.261f);
                Marine03->setFaction(culling_faction);
            }

            if(Unit* Marine04 = Unit::GetUnit((*me), m_uiMarine04GUID))
            {
                Marine04->GetMotionMaster()->MovePoint(0, 2081.899f, 1285.122f, 141.302f);
                Marine04->setFaction(culling_faction);
            }

            if(Unit* Priest01 = Unit::GetUnit((*me), m_uiPriest01GUID))
            {
                Priest01->GetMotionMaster()->MovePoint(0, 2081.072f, 1292.233f, 141.329f);
                Priest01->setFaction(culling_faction);
            }

            if(Unit* Priest02 = Unit::GetUnit((*me), m_uiPriest02GUID))
            {
                Priest02->GetMotionMaster()->MovePoint(0, 2080.632f, 1283.004f, 141.358f);
                Priest02->setFaction(culling_faction);
            }
        }

        void EnableEscort()
        {
            SetEscortPaused(false);
        }

        void SummonPeople()
        {
            if(Creature* Cityman = me->SummonCreature(NPC_CITYMAN, 2091.977f, 1275.021f, 140.757f, 0.558f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 30000))
                m_uiPeople01GUID = Cityman->GetGUID();

            if(Creature* Crazyman = me->SummonCreature(NPC_CRAZYMAN, 2093.514f, 1275.842f, 140.408f, 3.801f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 30000))
                m_uiPeople02GUID =  Crazyman->GetGUID();
        }

        void DoAction(const int32 uiAction)
        {
            if (uiAction == 1)
            {
                SummonPeople();
                m_uiStep = 0;
                m_uiStepTimer = 100;
                StartEvent = true;
            }               
        }

        void EnterCombat(Unit* who)
        {
            DoCast(me, SPELL_ARTHAS_AURA);
        }

        void EnterEvadeMode()
        {
            if(!m_pInstance) return;

            me->RemoveAllAuras();
            me->DeleteThreatList();
            me->CombatStop(true);
            me->LoadCreaturesAddon();
            m_uiExorcismTimer = 7400;
            m_uiHealTimer = 100;

            me->SetLootRecipient(NULL);

            if(m_pInstance->GetData(TYPE_PHASE) > 4)
            {
                npc_escortAI::EnterEvadeMode();
            }

            if(m_pInstance->GetData(TYPE_PHASE) > 2 && m_pInstance->GetData(TYPE_PHASE) < 5)
            {
                me->GetMotionMaster()->MovePoint(POINT_LAST_POINT, LastX, LastY, LastZ);
            }
        }

        void AttackStart(Unit* pWho)
        {
            if(!pWho || pWho == me)
                return;

            if(m_pInstance && m_pInstance->GetData(TYPE_PHASE) == 4) return;

            npc_escortAI::AttackStart(pWho);
        }

        void MoveInLineOfSight(Unit* pWho)
        {
            if (!pWho)
                return;

            if (!me->HasUnitState(UNIT_STAT_STUNNED) && pWho->isTargetableForAttack() &&
                me->IsHostileTo(pWho) && pWho->isInAccessiblePlaceFor(me))
            {
                if (!me->canFly() && me->GetDistanceZ(pWho) > CREATURE_Z_ATTACK_RANGE)
                    return;

                float attackRadius = me->GetAttackDistance(pWho);
                if (me->IsWithinDistInMap(pWho, attackRadius) && me->IsWithinLOSInMap(pWho))
                {
                    if (!me->getVictim())
                    {
                        AttackStart(pWho);
                        pWho->RemoveAurasByType(SPELL_AURA_MOD_STEALTH);
                    }
                    else if (me->GetMap()->IsDungeon())
                    {
                        pWho->SetInCombatWith(me);
                        me->AddThreat(pWho, 0.0f);
                    }
                }
            }
        }

        void WaypointReached(uint32 uiPointId)
        {
            switch(uiPointId)
            {
            case 2:
                DoScriptText(SAY_INTRO18, me);
                SetRun(true);
                break;
            case 8:
                GetSoldier();
                SetEscortPaused(true);
                me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER | UNIT_NPC_FLAG_GOSSIP);
                m_pInstance->SetData(TYPE_INTRO, DONE);
                SetRun(false);
                break;
            case 9:
                DoScriptText(SAY_ENTER01, me);
                MoveSoldier = true;
                m_uiMoveTimer = 12000;
                break;
            case 10:
                SetEscortPaused(true);
                m_pInstance->SetData(TYPE_PHASE, 2);
                ResetStep(2000);

                if(Unit* Cityman = Unit::GetUnit((*me), m_uiPeople01GUID))
                {
                    me->SetUInt64Value(UNIT_FIELD_TARGET, Cityman->GetGUID());
                    Cityman->SetUInt64Value(UNIT_FIELD_TARGET, me->GetGUID());
                    Cityman->GetMotionMaster()->MovePoint(0, 2088.625f, 1279.191f, 140.743f);
                }
                break;
            case 14:
                if(Creature* Human01 = me->SummonCreature(NPC_CITY, 2397.308f, 1207.565f, 134.038f, 5.593f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 30000))
                    m_uiHuman01GUID = Human01->GetGUID();

                if(Creature* Human02 = me->SummonCreature(NPC_CITY, 2400.770f, 1207.362f, 134.038f, 3.454f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 30000))
                    m_uiHuman02GUID = Human02->GetGUID();

                if(Creature* Human03 = me->SummonCreature(NPC_CITY, 2400.547f, 1204.892f, 134.038f, 2.479f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 30000))
                    m_uiHuman03GUID = Human03->GetGUID();
                break;
            case 20:
                SetEscortPaused(true);
                me->setFaction(35);
                me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER | UNIT_NPC_FLAG_GOSSIP);
                SetRun(false);
                break;  
            case 21:
                DoScriptText(SAY_PHASE502, me);
                break;
            case 22:
                SetEscortPaused(true);
                m_pInstance->SetData(TYPE_PHASE, 6);
                ResetStep(1000);
                break;
            case 25:
                me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_READY1H);
                me->SummonCreature(NPC_TIME_RIFT, 2428.901f, 1192.164f, 148.076f, 5.09f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 29000);
                DoScriptText(SAY_PHASE508, me);
                break;
            case 26:
                me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_STAND);
                DoScriptText(SAY_PHASE509, me);
                break;
            case 29:
                me->SummonCreature(NPC_TIME_RIFT, 2413.773f, 1137.820f, 148.076f, 5.09f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 29000);
                me->SummonCreature(NPC_TIME_RIFT, 2404.990f, 1175.121f, 148.076f, 5.09f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 29000);
                DoScriptText(SAY_PHASE510, me);
                break;
            case 30:
                DoScriptText(SAY_PHASE513, me);
                break;
            case 31:
                ResetStep(1000);
                m_pInstance->SetData(TYPE_PHASE, 7);
                break; 
            case 32:
                SetEscortPaused(true);
                m_pInstance->SetData(TYPE_PHASE, 8);
                me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                SetRun(false);
                break;   
            case 36:
                DoScriptText(SAY_PHASE514, me);
                break;
            case 37:
                if(GameObject* pGate = m_pInstance->instance->GetGameObject(m_pInstance->GetData64(GO_SHKAF_GATE)))
                    pGate->SetGoState(GO_STATE_ACTIVE); 

                SetRun(true);              
                DoScriptText(SAY_PHASE515, me);
                break;
            case 45:
                DoScriptText(SAY_PHASE601, me);
                break;
            case 48:
                DoScriptText(SAY_PHASE602, me);
                break;
            case 51:
                SetEscortPaused(true);
                m_pInstance->SetData(TYPE_PHASE, 9);
                DoScriptText(SAY_PHASE604, me);
                me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER | UNIT_NPC_FLAG_GOSSIP);
                break;   
            case 53:
                SetEscortPaused(true);
                me->StopMoving();
                me->GetMotionMaster()->MovementExpired(false);
                me->setFaction(FACTION);
                DoScriptText(SAY_PHASE605, me);
                if(Creature* Malganis = Unit::GetCreature(*me, m_pInstance->GetData64(NPC_MALGANIS)))
                {
                    m_pInstance->SetData(TYPE_MALGANIS, IN_PROGRESS);
                    Malganis->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_OOC_NOT_ATTACKABLE);
                    AttackStart(Malganis);
                    if (Malganis->AI()) Malganis->AI()->AttackStart(me);
                }
                break;
            } 
        }

        void JumpNextStep(uint32 Timer)
        {
            m_uiStepTimer = Timer;
            m_uiStep++;
        }

        void GetSoldier()
        {
            if(Creature* pEscort01 = GetClosestCreatureWithEntry(me, NPC_MARINE, 50.0f))
            {
                m_uiMarine01GUID = pEscort01->GetGUID();
                pEscort01->UpdateEntry(NPC_CITYMAN);
                if(Creature* pEscort02 = GetClosestCreatureWithEntry(me, NPC_MARINE, 50.0f))
                {
                    m_uiMarine02GUID = pEscort02->GetGUID();
                    pEscort02->UpdateEntry(NPC_CITYMAN);

                    if(Creature* pEscort03 = GetClosestCreatureWithEntry(me, NPC_MARINE, 50.0f))
                    {
                        m_uiMarine03GUID = pEscort03->GetGUID();
                        pEscort03->UpdateEntry(NPC_CITYMAN);
                        if(Creature* pEscort04 = GetClosestCreatureWithEntry(me, NPC_MARINE, 50.0f))
                        {
                            m_uiMarine04GUID = pEscort04->GetGUID();
                            pEscort01->UpdateEntry(NPC_MARINE);
                            pEscort02->UpdateEntry(NPC_MARINE);
                            pEscort03->UpdateEntry(NPC_MARINE);
                        }
                    }
                }
            }

            if(Creature* pEscort05 = GetClosestCreatureWithEntry(me, NPC_PRIEST, 50.0f))
            {
                m_uiPriest01GUID = pEscort05->GetGUID();
                pEscort05->UpdateEntry(NPC_CITYMAN);
                if(Creature* pEscort06 = GetClosestCreatureWithEntry(me, NPC_PRIEST, 50.0f))
                {
                    m_uiPriest02GUID = pEscort06->GetGUID();
                    pEscort05->UpdateEntry(NPC_PRIEST);
                }
            }
        }

        void ResetStep(uint32 Timer)
        {
            m_uiStep = 0;
            m_uiStepTimer = Timer;
        }

        void IntroEvent()
        {
            switch(m_uiStep)
            {
            case 0:
                DoScriptText(SAY_INTRO01, me);
                JumpNextStep(2000);
                break;
            case 1:
                m_uiUtherGUID = m_pInstance->GetData64(NPC_UTHER);
                m_uiJainaGUID = m_pInstance->GetData64(NPC_JAINA);
                if(Creature* pUther = Unit::GetCreature(*me, m_uiUtherGUID))
                    DoScriptText(SAY_INTRO02, pUther);
                JumpNextStep(8000);
                break;
            case 2:
                me->AddUnitMovementFlag(MOVEMENTFLAG_WALKING);
                DoScriptText(SAY_INTRO03, me);
                me->SetUInt64Value(UNIT_FIELD_TARGET, 0);
                me->GetMotionMaster()->MovePoint(0, 1908.334f, 1315.354f, 149.551f);

                if(Creature* pUther = Unit::GetCreature(*me, m_uiUtherGUID))
                    pUther->GetMotionMaster()->MovePoint(0, 1903.600f, 1296.678f, 143.383f);

                JumpNextStep(2000);
                break;
            case 3:
                if(Creature* pJaina = Unit::GetCreature(*me, m_uiJainaGUID))
                    pJaina->GetMotionMaster()->MovePoint(0, 1899.641f, 1298.684f, 143.831f);

                JumpNextStep(7000);
                break;
            case 4:
                me->GetMotionMaster()->MovementExpired(false);
                me->GetMotionMaster()->MovePoint(0, 1911.087f, 1314.263f, 150.026f);
                JumpNextStep(1000);
                break;
            case 5:
                DoScriptText(SAY_INTRO04, me);
                JumpNextStep(10000);
                break;
            case 6:
                if(Creature* pUther = Unit::GetCreature(*me, m_uiUtherGUID))
                    DoScriptText(SAY_INTRO05, pUther);

                JumpNextStep(1000);
                break;
            case 7:
                if(Creature* pUther = Unit::GetCreature(*me, m_uiUtherGUID))
                    me->SetUInt64Value(UNIT_FIELD_TARGET, pUther->GetGUID());

                DoScriptText(SAY_INTRO06, me);
                JumpNextStep(4000);
                break;
            case 8:
                if(Creature* pUther = Unit::GetCreature(*me, m_uiUtherGUID))
                    DoScriptText(SAY_INTRO07, pUther);
                JumpNextStep(6000);
                break;
            case 9:
                DoScriptText(SAY_INTRO08, me);
                JumpNextStep(4000);
                break;
            case 10:
                if(Creature* pUther = Unit::GetCreature(*me, m_uiUtherGUID))
                    DoScriptText(SAY_INTRO09, pUther);
                JumpNextStep(8000);
                break;
            case 11:
                DoScriptText(SAY_INTRO10, me);
                JumpNextStep(4000);
                break;
            case 12:
                if(Creature* pUther = Unit::GetCreature(*me, m_uiUtherGUID))
                    DoScriptText(SAY_INTRO11, pUther);
                JumpNextStep(4000);
                break;
            case 13:
                DoScriptText(SAY_INTRO12, me);
                JumpNextStep(11000);
                break;
            case 14:
                if(Creature* pJaina = Unit::GetCreature(*me, m_uiJainaGUID))
                    DoScriptText(SAY_INTRO13, pJaina);
                JumpNextStep(3000);
                break;
            case 15:
                DoScriptText(SAY_INTRO14, me);
                JumpNextStep(9000);
                break;
            case 16:
                if(Creature* pUther = Unit::GetCreature(*me, m_uiUtherGUID))
                    DoScriptText(SAY_INTRO15, pUther);
                JumpNextStep(5000);
                break;
            case 17:
                if(Creature* pJaina = Unit::GetCreature(*me, m_uiJainaGUID))
                {
                    me->SetUInt64Value(UNIT_FIELD_TARGET, pJaina->GetGUID());
                    pJaina->GetMotionMaster()->MovePoint(0, 1794.357f, 1272.183f, 140.558f);
                }
                JumpNextStep(1000);
                break;
            case 18:
                DoScriptText(SAY_INTRO16, me);
                JumpNextStep(1000);
                break;
            case 19:
                if(Creature* pJaina = Unit::GetCreature(*me, m_uiJainaGUID))
                    DoScriptText(SAY_INTRO17, pJaina);
                JumpNextStep(3000);
                break;
            case 20:
                me->SetUInt64Value(UNIT_FIELD_TARGET, 0);
                CAST_AI(npc_arthasAI, me->AI())->Start(true, false);
                JumpNextStep(3000);
                break;
            }
        }

        void EnterEvent()
        {
            switch(m_uiStep)
            {
            case 0:
                if(Unit* Cityman = Unit::GetUnit((*me), m_uiPeople01GUID))
                    DoScriptText(SAY_ENTER02, Cityman);
                JumpNextStep(4000);
                break;
            case 1:
                me->GetMotionMaster()->MovePoint(0, 2087.689f, 1280.344f, 140.73f);
                DoScriptText(SAY_ENTER03, me);
                JumpNextStep(3000);
                break;
            case 2:
                if(Unit* Cityman = Unit::GetUnit((*me), m_uiPeople01GUID))
                    DoScriptText(SAY_ENTER04, Cityman);
                me->HandleEmoteCommand(37);
                JumpNextStep(1000);
                break;
            case 3:
                if(Unit* Cityman = Unit::GetUnit((*me), m_uiPeople01GUID))
                    me->DealDamage(Cityman, Cityman->GetMaxHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);
                if(Unit* Crazyman = Unit::GetUnit((*me), m_uiPeople02GUID))
                {
                    DoScriptText(SAY_ENTER05, Crazyman);
                    Crazyman->SetUInt64Value(UNIT_FIELD_TARGET, me->GetGUID());
                    me->SetUInt64Value(UNIT_FIELD_TARGET, Crazyman->GetGUID());
                    me->GetMotionMaster()->MovePoint(0, 2092.154f, 1276.645f, 140.52f);
                }
                JumpNextStep(3000);
                break;
            case 4:
                me->HandleEmoteCommand(37);
                JumpNextStep(1000);
                break;
            case 5:
                if(Unit* Crazyman = Unit::GetUnit((*me), m_uiPeople02GUID))
                    Crazyman->DealDamage(Crazyman, Crazyman->GetMaxHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);
                JumpNextStep(1000);
                break;
            case 6:
                me->SetUInt64Value(UNIT_FIELD_TARGET, 0);
                me->GetMotionMaster()->MovePoint(0, 2091.179f, 1278.065f, 140.476f);
                DoScriptText(SAY_ENTER06, me);
                JumpNextStep(3000);
                break;
            case 7:
                if(Creature* StalkerM = me->SummonCreature(20562, 2117.349f, 1288.624f, 136.271f, 1.37f, TEMPSUMMON_TIMED_DESPAWN, 60000))
                    StalkerM->CastSpell(StalkerM, 63793, false);
                JumpNextStep(1000);
                break;
            case 8:
                m_pInstance->SetData(TYPE_ENCOUNTER, IN_PROGRESS);
                if(Creature* TempMalganis = me->SummonCreature(NPC_MALGANIS_INTRO, 2117.349f, 1288.624f, 136.271f, 1.37f, TEMPSUMMON_TIMED_DESPAWN, 29000))
                {
                    m_uiMalganisGUID = TempMalganis->GetGUID();
                    DoScriptText(SAY_ENTER07, TempMalganis);
                    me->SetUInt64Value(UNIT_FIELD_TARGET, TempMalganis->GetGUID());
                    TempMalganis->SetUInt64Value(UNIT_FIELD_TARGET, me->GetGUID());
                    TempMalganis->setFaction(35);
                }
                JumpNextStep(11000);
                break;
            case 9:
                if(Unit* TempMalganis = Unit::GetUnit((*me), m_uiMalganisGUID))
                    DoScriptText(SAY_ENTER08, TempMalganis);
                JumpNextStep(17000);
                break;
            case 10:
                DoScriptText(SAY_ENTER09, me);
                JumpNextStep(7000);
                break;
            case 11:
                me->SetUInt64Value(UNIT_FIELD_TARGET, 0);
                DoScriptText(SAY_ENTER10, me);
                JumpNextStep(12000);
                break;
            case 12:
                me->GetMotionMaster()->MovePoint(0, 2084.584f, 1278.331f, 141.479f);
                JumpNextStep(4000);
                break;
            case 13:
                me->GetMotionMaster()->MovementExpired(false);
                me->GetMotionMaster()->MovePoint(0, 2087.414f, 1279.293f, 140.933f);
                JumpNextStep(2000);
                break;
            case 14:
                LastX = me->GetPositionX();
                LastY = me->GetPositionY();
                LastZ = me->GetPositionZ();
                if(IsHeroic())
                    m_pInstance->SetData(TYPE_BONUS, IN_PROGRESS);
                m_uiWaveCount = 0;
                SetRun(true);
                m_pInstance->SetData(TYPE_WING, RIGHT);
                me->setFaction(FACTION);
                m_uiSummonTimer = 100;
                m_pInstance->SetData(TYPE_PHASE, 3);
                break;
            }
        }

        void SummonWing()
        {
            m_uiWaveCount++;
            m_pInstance->DoUpdateWorldState(WORLD_STATE_COS_WAVE_COUNT, m_uiWaveCount);

            switch(m_uiWaveCount)
            {
            case 1:
                me->SummonCreature(NPC_GHOUL, 2340.058f, 1253.570f, 132.733f, 5.09f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 29000);
                me->SummonCreature(NPC_GHOUL, 2340.058f, 1253.570f, 132.733f, 5.09f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 29000);
                break;
            case 2:
                me->SummonCreature(NPC_GHOUL, 2340.058f, 1253.570f, 132.733f, 5.09f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 29000);
                me->SummonCreature(NPC_GHOUL, 2340.058f, 1253.570f, 132.733f, 5.09f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 29000);
                me->SummonCreature(NPC_NECROMANCER, 2340.058f, 1253.570f, 132.733f, 5.09f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 29000);
                me->SummonCreature(NPC_FIEND, 2340.058f, 1253.570f, 132.733f, 5.09f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 29000);
                break;
            case 3:
                m_pInstance->SetData(TYPE_WING, LEFT);
                me->SummonCreature(NPC_GHOUL, 2272.773f, 1331.824f, 124.171f, 3.12f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 29000);
                me->SummonCreature(NPC_NECROMANCER, 2272.773f, 1331.824f, 124.171f, 3.12f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 29000);
                me->SummonCreature(NPC_NECROMANCER, 2272.773f, 1331.824f, 124.171f, 3.12f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 29000);
                me->SummonCreature(NPC_FIEND, 2272.773f, 1331.824f, 124.171f, 3.12f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 29000);
                break;
            case 4:
                m_pInstance->SetData(TYPE_WING, RIGHT);
                me->SummonCreature(NPC_ACOLYTE, 2340.058f, 1253.570f, 132.733f, 5.09f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 29000);
                me->SummonCreature(NPC_NECROMANCER, 2340.058f, 1253.570f, 132.733f, 5.09f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 29000);
                me->SummonCreature(NPC_ACOLYTE, 2340.058f, 1253.570f, 132.733f, 5.09f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 29000);
                me->SummonCreature(NPC_FIEND, 2340.058f, 1253.570f, 132.733f, 5.09f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 29000);
                break;
            case 5:
                m_pInstance->SetData(TYPE_PHASE, 4);
                if(Creature* pMeathook = me->SummonCreature(NPC_MEATHOOK, 2203.64f, 1334.09f, 129.68f, 2.91f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 29000))
                {
                    DoScriptText(SAY_MEATHOOK_SPAWN, pMeathook);
                    pMeathook->RemoveUnitMovementFlag(MOVEMENTFLAG_WALKING);
                    pMeathook->GetMotionMaster()->MovePoint(0, 2161.47f, 1280.15f, 133.57f);
                }
                break;
            case 6:
                m_pInstance->SetData(TYPE_WING, LEFT);
                me->SummonCreature(NPC_GHOUL, 2272.773f, 1331.824f, 124.171f, 3.12f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 29000);
                me->SummonCreature(NPC_NECROMANCER, 2272.773f, 1331.824f, 124.171f, 3.12f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 29000);
                me->SummonCreature(NPC_NECROMANCER, 2272.773f, 1331.824f, 124.171f, 3.12f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 29000);
                me->SummonCreature(NPC_FIEND, 2272.773f, 1331.824f, 124.171f, 3.12f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 29000);
                me->SummonCreature(NPC_FIEND, 2272.773f, 1331.824f, 124.171f, 3.12f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 29000);
                break;
            case 7:
                m_pInstance->SetData(TYPE_WING, RIGHT);
                me->SummonCreature(NPC_CONSTRUCT, 2340.058f, 1253.570f, 132.733f, 5.09f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 29000);
                me->SummonCreature(NPC_GHOUL, 2340.058f, 1253.570f, 132.733f, 5.09f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 29000);
                me->SummonCreature(NPC_GHOUL, 2340.058f, 1253.570f, 132.733f, 5.09f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 29000);
                me->SummonCreature(NPC_GHOUL, 2340.058f, 1253.570f, 132.733f, 5.09f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 29000);
                break;
            case 8:
                m_pInstance->SetData(TYPE_WING, LEFT);
                me->SummonCreature(NPC_CONSTRUCT, 2272.773f, 1331.824f, 124.171f, 3.12f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 29000);
                me->SummonCreature(NPC_NECROMANCER, 2272.773f, 1331.824f, 124.171f, 3.12f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 29000);
                me->SummonCreature(NPC_GHOUL, 2272.773f, 1331.824f, 124.171f, 3.12f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 29000);
                me->SummonCreature(NPC_GHOUL, 2272.773f, 1331.824f, 124.171f, 3.12f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 29000);
                me->SummonCreature(NPC_NECROMANCER, 2272.773f, 1331.824f, 124.171f, 3.12f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 29000);
                break;
            case 9:
                m_pInstance->SetData(TYPE_WING, RIGHT);
                me->SummonCreature(NPC_CONSTRUCT, 2340.058f, 1253.570f, 132.733f, 5.09f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 29000);
                me->SummonCreature(NPC_FIEND, 2340.058f, 1253.570f, 132.733f, 5.09f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 29000);
                me->SummonCreature(NPC_NECROMANCER, 2340.058f, 1253.570f, 132.733f, 5.09f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 29000);
                me->SummonCreature(NPC_NECROMANCER, 2340.058f, 1253.570f, 132.733f, 5.09f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 29000);
                me->SummonCreature(NPC_GHOUL, 2340.058f, 1253.570f, 132.733f, 5.09f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 29000);
                break;
            case 10:
                m_pInstance->SetData(TYPE_PHASE, 4);
                if(Creature* pSalramm = me->SummonCreature(NPC_SALRAMM, 2203.64f, 1334.09f, 129.68f, 2.91f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 29000))
                {
                    DoScriptText(SAY_SALRAMM_SPAWN, pSalramm);
                    pSalramm->RemoveUnitMovementFlag(MOVEMENTFLAG_WALKING);
                    pSalramm->GetMotionMaster()->MovePoint(0, 2161.47f, 1280.15f, 133.57f);
                }
                break;
            }
        }

        void HouseEvent()
        {
            switch(m_uiStep)
            {
            case 0:
                if(Creature* Human = Unit::GetCreature(*me, m_uiHuman01GUID))
                {
                    me->SetUInt64Value(UNIT_FIELD_TARGET, Human->GetGUID());
                    Human->SetUInt64Value(UNIT_FIELD_TARGET, me->GetGUID());
                    DoScriptText(SAY_PHASE503, Human);
                }
                JumpNextStep(4000);
                break;
            case 1:
                DoScriptText(SAY_PHASE504, me);
                me->GetMotionMaster()->MovePoint(0, 2396.035f, 1206.942f, 134.038f);
                JumpNextStep(3000);
                break;
            case 2:
                me->HandleEmoteCommand(37);
                JumpNextStep(2000);
                break;
            case 3:
                DoScriptText(SAY_PHASE505, me);
                JumpNextStep(2000);
                break;
            case 4:
                if(Creature* Human = Unit::GetCreature(*me, m_uiHuman01GUID))
                    DoScriptText(SAY_PHASE506, Human);
                JumpNextStep(6000);
                break;
            case 5:
                me->SetUInt64Value(UNIT_FIELD_TARGET, 0);
                if(Creature* Human = Unit::GetCreature(*me, m_uiHuman01GUID))
                {
                    Human->SetUInt64Value(UNIT_FIELD_TARGET, 0);
                    Human->UpdateEntry(NPC_INFINITE_ADVERSARY);
                }
                if(Creature* Human2 = Unit::GetCreature(*me, m_uiHuman02GUID))
                    Human2->UpdateEntry(NPC_INFINITE_HUNTER);
                if(Creature* Human3 = Unit::GetCreature(*me, m_uiHuman03GUID))
                    Human3->UpdateEntry(NPC_INFINITE_AGENT);
                JumpNextStep(1000);
                break;
            case 6:
                SetRun(true);
                me->GetMotionMaster()->MovePoint(0, 2384.320f, 1202.779f, 134.040f);
                DoScriptText(SAY_PHASE507, me);
                JumpNextStep(5000);
                break;
            case 7:
                SetEscortPaused(false);
                me->setFaction(FACTION);
                m_pInstance->SetData(TYPE_PHASE, 5);
                JumpNextStep(1000);
                break;
            }
        }

        void EpochEvent()
        {
            switch(m_uiStep)
            {
            case 0:
                me->SummonCreature(NPC_TIME_RIFT_2, 2445.629f, 1111.500f, 148.076f, 3.229f, TEMPSUMMON_TIMED_DESPAWN, 9000);
                JumpNextStep(2000);
                break;
            case 1:
                pEpoch = me->SummonCreature(NPC_EPOCH, 2445.629f, 1111.500f, 148.076f, 3.229f, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 900000);
                if(pEpoch)
                {
                    pEpoch->setFaction(35);
                    DoScriptText(SAY_EPOCH_INTRO, pEpoch);
                    me->SetUInt64Value(UNIT_FIELD_TARGET, pEpoch->GetGUID());
                }
                JumpNextStep(20000);
                break;
            case 2:
                DoScriptText(SAY_ARTHAS_INTRO, me);
                JumpNextStep(6000);
                break;
            case 3:
                if(pEpoch)
                {
                    DoScriptText(SAY_EPOCH_AGGRO, pEpoch);
                    AttackStart(pEpoch);
                    if (pEpoch->AI()) pEpoch->AI()->AttackStart(me);
                    pEpoch->setFaction(14);
                }
                m_pInstance->SetData(TYPE_PHASE, 5);
                SetRun(false);
                JumpNextStep(6000);
                break;
            }
        }

        void MalganisEvent()
        {
            bool bNeedSpawn = false;

            switch(m_uiStep)
            {
            case 0:
                me->setFaction(35);
                me->GetMotionMaster()->MovePoint(0, 2302.326f, 1491.386f, 128.362f);
                if(Creature* Malganis = Unit::GetCreature(*me, m_pInstance->GetData64(NPC_MALGANIS)))
                {
                    DoScriptText(SAY_MALGANIS_ESCAPE01, Malganis);
                    Malganis->InterruptNonMeleeSpells(false);
                    Malganis->GetMotionMaster()->MovePoint(0, 2296.665f, 1502.362f, 128.362f);
                    me->SetUInt64Value(UNIT_FIELD_TARGET, Malganis->GetGUID());
                    Malganis->SetUInt64Value(UNIT_FIELD_TARGET, me->GetGUID());
                }
                JumpNextStep(10000);
                break;
            case 1:
                if(Creature* Malganis = Unit::GetCreature(*me, m_pInstance->GetData64(NPC_MALGANIS)))
                    DoScriptText(SAY_MALGANIS_ESCAPE02, Malganis);
                JumpNextStep(10000);
                break;
            case 2:
                DoScriptText(SAY_ARTHAS_OUTRO01, me);
                JumpNextStep(5000);
                break;
            case 3:
                if(Creature* Malganis = Unit::GetCreature(*me, m_pInstance->GetData64(NPC_MALGANIS)))
                    DoScriptText(SAY_MALGANIS_OUTRO, Malganis);
                JumpNextStep(20000);
                break;
            case 4:
                if(Creature* Malganis = Unit::GetCreature(*me, m_pInstance->GetData64(NPC_MALGANIS)))
                {
                    Malganis->SetVisible(false);
                    me->GetMotionMaster()->MovePoint(0, Malganis->GetPositionX(), Malganis->GetPositionY(), Malganis->GetPositionZ());
                }
                me->SetUInt64Value(UNIT_FIELD_TARGET, 0);
                me->RemoveUnitMovementFlag(MOVEMENTFLAG_WALKING);
                JumpNextStep(3000);
                break;
            case 5:
                DoScriptText(SAY_ARTHAS_OUTRO02, me);
                JumpNextStep(6000);
                break;
            case 6:
                me->GetMotionMaster()->MovePoint(0, 2298.298f, 1500.362f, 128.362f);
                DoScriptText(SAY_ARTHAS_OUTRO03, me);
                JumpNextStep(11000);
                break;
            case 7:
                me->GetMotionMaster()->MovePoint(0, 2243.311f, 1476.025f, 132.352f);
                {
                    Map *map = me->GetMap();
                    if (map)
                    {
                        Map::PlayerList const &PlayerList = map->GetPlayers();

                        if (!PlayerList.isEmpty())
                            for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                            {
                                if (i->getSource()->GetQuestStatus(QUEST_A_ROYAL_ESCORT) == QUEST_STATUS_INCOMPLETE ||
                                    i->getSource()->GetQuestStatus(QUEST_A_ROYAL_ESCORT) == QUEST_STATUS_COMPLETE)
                                {
                                    bNeedSpawn = true;
                                    break;
                                }
                            }
                    }
                }

                if (bNeedSpawn)
                    me->SummonCreature(30997, 2311.61f, 1497.85f, 128.01f, 4.14f, TEMPSUMMON_TIMED_DESPAWN, 1800000);
                JumpNextStep(11000);
                break;
            case 8:
                m_pInstance->SetData(TYPE_PHASE, 12);
                me->SetVisible(false);
                break;
            }
        }

        void UpdateAI(const uint32 uiDiff)
        {
            npc_escortAI::UpdateAI(uiDiff);

            if(!m_pInstance) return;

            if(StartEvent == true)
            {
                if(m_pInstance->GetData(TYPE_INTRO) != DONE)
                {
                    if(m_uiStepTimer < uiDiff)
                    {
                        IntroEvent();
                    }
                    else m_uiStepTimer -= uiDiff;
                }

                if(m_pInstance->GetData(TYPE_PHASE) == 2)
                {
                    if(m_uiStepTimer < uiDiff)
                    {
                        EnterEvent();
                    }
                    else m_uiStepTimer -= uiDiff;
                }

                if(MoveSoldier == true)
                {
                    if(m_uiMoveTimer < uiDiff)
                    {
                        MoveSoldiers();
                        MoveSoldier = false;
                    }
                    else m_uiMoveTimer -= uiDiff;
                }

                if(m_pInstance->GetData(TYPE_PHASE) == 3)
                {
                    if(m_uiSummonTimer < uiDiff)
                    {
                        SummonWing();
                        m_uiSummonTimer = 70000;
                    }
                    else m_uiSummonTimer -= uiDiff;
                }

                if(m_pInstance->GetData(TYPE_PHASE) == 4 && m_pInstance->GetData(TYPE_ENCOUNTER) == DONE)
                {
                    m_pInstance->SetData(TYPE_PHASE, 5);
                    SetRun(true);
                    EnableEscort();
                    DoScriptText(SAY_PHASE501, me);
                }

                if(m_pInstance->GetData(TYPE_PHASE) == 6)
                {
                    if(m_uiStepTimer < uiDiff)
                    {
                        HouseEvent();
                    }
                    else m_uiStepTimer -= uiDiff;
                }

                if(m_pInstance->GetData(TYPE_PHASE) == 7)
                {
                    if(m_uiStepTimer < uiDiff)
                    {
                        EpochEvent();
                    }
                    else m_uiStepTimer -= uiDiff;
                }

            }

            if(m_pInstance->GetData(TYPE_PHASE) == 10)
            {
                SetEscortPaused(true);
                ResetStep(1000);
                me->AttackStop();
                m_pInstance->SetData(TYPE_PHASE, 11);
            }

            if(m_pInstance->GetData(TYPE_PHASE) == 11)
            {
                if(m_uiStepTimer < uiDiff)
                {
                    MalganisEvent();
                }
                else m_uiStepTimer -= uiDiff;
            }

            if (!UpdateVictim())
                return;

            if(m_pInstance->GetData(TYPE_PHASE) > 9) return;

            if (m_uiExorcismTimer < uiDiff)
            {
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 30.0f, true))
                    DoCast(target, DUNGEON_MODE(SPELL_EXORCISM_N, SPELL_EXORCISM_H));

                m_uiExorcismTimer = 7300;
            }
            else m_uiExorcismTimer -= uiDiff;

            if (m_uiHealTimer < uiDiff)
            {
                if(HealthBelowPct(40.0f))
                {
                    DoCast(me, SPELL_HOLY_LIGHT);
                    m_uiHealTimer = 20000;
                }
            }
            else m_uiHealTimer -= uiDiff;

            return;
        }
    };
};

/*###
## npc_uther
###*/

class npc_uther : public CreatureScript
{
public:
    npc_uther() : CreatureScript("npc_uther") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_utherAI(pCreature);
    }

    struct npc_utherAI : public npc_escortAI
    {
        npc_utherAI(Creature* pCreature) : npc_escortAI(pCreature)
        {
            m_pInstance = pCreature->GetInstanceScript();
            Reset();
        }

        InstanceScript* m_pInstance;

        uint64 m_uiArthasGUID;
        uint32 m_uiStep;
        uint32 m_uiStepTimer;
        bool StartEvent;
  
        uint64 m_uiKnightGUID01;
        uint64 m_uiKnightGUID02;
        uint64 m_uiKnightGUID03;
 
        void Reset()
        {
            me->SetVisible(false);
            m_uiStep = 0;
            m_uiStepTimer = 100;
            SetWeather(WEATHER_STATE_FINE, 0.0f);
        }

        void SetWeather(uint32 weather, float grade)
        {
            Map* pMap = me->GetMap();

            if (!pMap || !pMap->IsDungeon())
                return;

            WorldPacket data(SMSG_WEATHER, (4+4+4));
            data << uint32(weather) << float(grade) << uint8(0);

            pMap->SendToPlayers(&data);
        }

        void DoAction(const int32 uiAction)
        {
            if (uiAction == 1)
            {
                SetWeather(WEATHER_STATE_MEDIUM_RAIN, 0.65f);
                StartEvent = true;
                me->SetVisible(true);
                CAST_AI(npc_utherAI, me->AI())->Start(false, true);

                if(Creature* Knight01 = me->SummonCreature(NPC_KNIGHT, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 110000))
                {
                    m_uiKnightGUID01 = Knight01->GetGUID();
                    Knight01->RemoveUnitMovementFlag(MOVEMENTFLAG_WALKING);
                    Knight01->GetMotionMaster()->MoveFollow(me, PET_FOLLOW_DIST, M_PI/2);
                }

                if(Creature* Knight02 = me->SummonCreature(NPC_KNIGHT, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 110000))
                {
                    m_uiKnightGUID02 = Knight02->GetGUID();
                    Knight02->RemoveUnitMovementFlag(MOVEMENTFLAG_WALKING);
                    Knight02->GetMotionMaster()->MoveFollow(me, PET_FOLLOW_DIST, M_PI/4);
                }

                if(Creature* Knight03 = me->SummonCreature(NPC_KNIGHT, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 110000))
                {
                    m_uiKnightGUID03 = Knight03->GetGUID();
                    Knight03->RemoveUnitMovementFlag(MOVEMENTFLAG_WALKING);
                    Knight03->GetMotionMaster()->MoveFollow(me, PET_FOLLOW_DIST, M_PI/3);
                }
            }
        }

        void WaypointReached(uint32 uiPointId)
        {
            switch(uiPointId)
            {
            case 3:
                m_uiArthasGUID = m_pInstance->GetData64(NPC_ARTHAS);
                if(Creature* pArthas = Unit::GetCreature(*me, m_uiArthasGUID))
                {
                    pArthas->RemoveUnitMovementFlag(MOVEMENTFLAG_WALKING);
                    pArthas->SetUInt64Value(UNIT_FIELD_TARGET, me->GetGUID());
                    pArthas->GetMotionMaster()->MovePoint(0, 1902.974f, 1291.635f, 143.337f);
                }
                break;
            case 4:
                SetRun(false);
                if(Creature *pArthas = Unit::GetCreature(*me, m_pInstance->GetData64(NPC_ARTHAS)))
                    if (pArthas->AI()) pArthas->AI()->DoAction(1);
                break;
            case 6:
                me->SetVisible(false);
                uint64 m_uiJainaGUID = m_pInstance->GetData64(NPC_JAINA);
                if(Creature* pJaina = Unit::GetCreature(*me, m_uiJainaGUID))
                    pJaina->SetVisible(false);
                break;
            }
        }

        void UpdateAI(const uint32 uiDiff)
        {
            npc_escortAI::UpdateAI(uiDiff);

            if(!m_pInstance) return;

            return;
        }
    };
};

/*###
## npc_chromi_middle
###*/

#define GOSSIP_ITEM_CHROMI1 "What do you think they're up to?"
#define GOSSIP_ITEM_CHROMI2 "What want me to do what?"
#define GOSSIP_ITEM_CHROMI3 "Very well, Chromie."

#define GOSSIP_ITEM_CHROMI1_RU "Что, по-твоему, они задумали?"
#define GOSSIP_ITEM_CHROMI2_RU "Что я могу сделать?"
#define GOSSIP_ITEM_CHROMI3_RU "Отлично, Хроми."

enum
{
    GOSSIP_TEXTID_CHROMI1            = 12953, 
    GOSSIP_TEXTID_CHROMI2            = 12949, 
    GOSSIP_TEXTID_CHROMI3            = 12950, 
    GOSSIP_TEXTID_CHROMI4            = 12952
};

class npc_chromi_middle : public CreatureScript
{
public:
    npc_chromi_middle() : CreatureScript("npc_chromi_middle") { }

    bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
    {
        pPlayer->PlayerTalkClass->ClearMenus();
        if(InstanceScript* m_pInstance = (pCreature->GetInstanceScript()))
            if(m_pInstance->GetData(TYPE_INTRO) != NOT_STARTED) return true;

        if (uiAction == GOSSIP_ACTION_INFO_DEF+1) 
        { 
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, (pPlayer->isRussianLocale())? GOSSIP_ITEM_CHROMI2_RU:GOSSIP_ITEM_CHROMI2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2); 

            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_CHROMI2, pCreature->GetGUID()); 
        } 

        if (uiAction == GOSSIP_ACTION_INFO_DEF+2) 
        { 
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, (pPlayer->isRussianLocale())? GOSSIP_ITEM_CHROMI3_RU:GOSSIP_ITEM_CHROMI3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+3); 

            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_CHROMI3, pCreature->GetGUID()); 
        } 

        if (uiAction == GOSSIP_ACTION_INFO_DEF+3) 
        { 
            if (InstanceScript* m_pInstance = pCreature->GetInstanceScript())
            {
                m_pInstance->DoUpdateWorldState(WORLD_STATE_COS_CRATE_ON, 0);
                m_pInstance->SetData(TYPE_INTRO, IN_PROGRESS);
                if (Creature *pUther = Unit::GetCreature(*pCreature, m_pInstance->GetData64(NPC_UTHER)))
                    pUther->AI()->DoAction(1);
            }

            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_CHROMI4, pCreature->GetGUID()); 
        } 

        return true; 
    }

    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
        if (pCreature->isQuestGiver())
            pPlayer->PrepareQuestMenu(pCreature->GetGUID());

        InstanceScript* pInstance = pCreature->GetInstanceScript();

        if (pPlayer && pPlayer->GetQuestStatus(QUEST_A_ROYAL_ESCORT) == QUEST_STATUS_COMPLETE && pInstance && pInstance->GetData(TYPE_INTRO) == NOT_STARTED)
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, (pPlayer->isRussianLocale())? GOSSIP_ITEM_CHROMI1_RU:GOSSIP_ITEM_CHROMI1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

        pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_CHROMI1, pCreature->GetGUID()); 

        return true; 
    }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_chromi_middleAI(pCreature);
    } 

    struct npc_chromi_middleAI : public ScriptedAI
    {
        npc_chromi_middleAI(Creature* pCreature) : ScriptedAI(pCreature)
        {
            m_pInstance = pCreature->GetInstanceScript();
            m_bUtherHere = false;
            Reset();
        }

        InstanceScript* m_pInstance;

        bool m_bUtherHere;

        void Reset()
        {
            m_bUtherHere = false;
        }

        void MoveInLineOfSight(Unit* pWho)
        {
            if (!m_bUtherHere && m_pInstance && pWho && pWho->GetTypeId() == TYPEID_PLAYER &&
                me->GetDistance2d(pWho) <= 15 && pWho->ToPlayer()->GetQuestStatus(QUEST_A_ROYAL_ESCORT) == QUEST_STATUS_INCOMPLETE)
            {
                m_pInstance->DoUpdateWorldState(WORLD_STATE_COS_CRATE_ON, 0);
                m_pInstance->SetData(TYPE_INTRO, IN_PROGRESS);
                if (Creature *pUther = Unit::GetCreature(*me, m_pInstance->GetData64(NPC_UTHER)))
                    if (pUther->AI()) pUther->AI()->DoAction(1);
                m_bUtherHere = true;
            }
        }
    };
};


/*###
## npc_arthas_marine
###*/

class npc_arthas_marine : public CreatureScript
{
public:
    npc_arthas_marine() : CreatureScript("npc_arthas_marine") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_arthas_marineAI(pCreature);
    }

    struct npc_arthas_marineAI : public ScriptedAI
    {
        npc_arthas_marineAI(Creature *c) : ScriptedAI(c)
        {
            Reset();
        }

        float LastX;
        float LastY;
        float LastZ;

        uint32 m_uiHealTimer;

        void Reset() 
        {
            m_uiHealTimer = 3000;
        }

        void EnterCombat(Unit* who)
        {
            LastX = me->GetPositionX();
            LastY = me->GetPositionY();
            LastZ = me->GetPositionZ();
        }

        void AttackStart(Unit* pWho)
        {
            if (!pWho)
                return;

            if (me->Attack(pWho, true))
            {
                me->AddThreat(pWho, 0.0f);
                me->SetInCombatWith(pWho);
                pWho->SetInCombatWith(me);

                if (IsCombatMovement())
                    me->GetMotionMaster()->MoveChase(pWho);
            }
        }

        void EnterEvadeMode()
        {
            me->RemoveAllAuras();
            me->DeleteThreatList();
            me->CombatStop(true);
            me->LoadCreaturesAddon();

            me->SetLootRecipient(NULL);
            me->GetMotionMaster()->MovePoint(POINT_LAST_POINT, LastX, LastY, LastZ);

            Reset();
        }

        void MoveInLineOfSight(Unit* pWho)
        {
            if (!pWho)
                return;

            if (!me->HasUnitState(UNIT_STAT_STUNNED) && pWho->isTargetableForAttack() &&
                me->IsHostileTo(pWho) && pWho->isInAccessiblePlaceFor(me))
            {
                if (!me->canFly() && me->GetDistanceZ(pWho) > CREATURE_Z_ATTACK_RANGE)
                    return;

                float attackRadius = me->GetAttackDistance(pWho);
                if (me->IsWithinDistInMap(pWho, attackRadius) && me->IsWithinLOSInMap(pWho))
                {
                    if (!me->getVictim())
                    {
                        AttackStart(pWho);
                        pWho->RemoveAurasByType(SPELL_AURA_MOD_STEALTH);
                    }
                    else if (me->GetMap()->IsDungeon())
                    {
                        pWho->SetInCombatWith(me);
                        me->AddThreat(pWho, 0.0f);
                    }
                }
            }
        }

        void UpdateAI(const uint32 uiDiff)
        {

            if (!UpdateVictim())
                return;

            if(m_uiHealTimer < uiDiff)
            {
                if(HealthBelowPct(40.0f))
                {
                    if(Creature* pHeal = GetClosestCreatureWithEntry(me, NPC_PRIEST, 50.0f))
                    {
                        if(pHeal->GetHealth() > (pHeal->GetMaxHealth() * 0.4f))
                        {
                            pHeal->InterruptNonMeleeSpells(false);
                            pHeal->CastSpell(me, SPELL_HEAL, false);
                            m_uiHealTimer = 3000;
                        }
                    }
                }
            }
            else m_uiHealTimer -= uiDiff;

            DoMeleeAttackIfReady();

            return;
        }
    };
};

/*###
## npc_dark_conversion
###*/

/*enum
{
   SAY_PEOPLE01         = -1594099, 
   SAY_PEOPLE02         = -1594100, 
   SAY_PEOPLE03         = -1594101, 
   SAY_PEOPLE04         = -1594102, 
   SAY_PEOPLE05         = -1594103, 
};*/

class npc_dark_conversion : public CreatureScript
{
public:
    npc_dark_conversion() : CreatureScript("npc_dark_conversion") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_dark_conversionAI(pCreature);
    }

    struct npc_dark_conversionAI : public ScriptedAI
    {
        npc_dark_conversionAI(Creature *pCreature) : ScriptedAI(pCreature)
        {
            m_pInstance = pCreature->GetInstanceScript();

            pCreature->setActive(true);

            if (m_pInstance && m_pInstance->GetData(TYPE_ENCOUNTER) == IN_PROGRESS)
                pCreature->UpdateEntry(NPC_ZOMBIE);

            Reset();
        }

        InstanceScript* m_pInstance;

        bool Special;
        bool Conversion;
        uint32 m_uiStep;
        uint32 m_uiStepTimer;

        void Reset() 
        {
            me->setFaction(35);
            Conversion = false;
            Special = false;
            m_uiStep = 1;
            m_uiStepTimer = 5000;

            if (m_pInstance && m_pInstance->GetData(TYPE_ENCOUNTER) == IN_PROGRESS)
                me->UpdateEntry(NPC_ZOMBIE);
        }

        void MalganisScared(Creature* target, float horizontalSpeed, float verticalSpeed)
        {
            float angle = target->GetAngle(me);
            float vsin = sin(angle);
            float vcos = cos(angle);

            float ox, oy, oz;
            me->GetPosition(ox, oy, oz);

            float g = 19.23f;
            float dh = verticalSpeed*verticalSpeed / (2*g);
            float time = sqrtf(dh/(0.124976 * verticalSpeed));

            float dis = time * horizontalSpeed;
            float fx = ox + dis * vcos;
            float fy = oy + dis * vsin;
            float fz = oz;

            me->UpdateGroundPositionZ(fx, fy, fz);

            me->RemoveUnitMovementFlag(MOVEMENTFLAG_WALKING);
            me->GetMotionMaster()->MovePoint(0, fx, fy, fz, false);
        }
 
        void DarkConversion(bool Move)
        {
            me->UpdateEntry(NPC_ZOMBIE);
            if(Move == true)
            {
                uint64 m_uiArthasGUID = m_pInstance->GetData64(NPC_ARTHAS);
                if(Creature* pArthas = Unit::GetCreature(*me, m_uiArthasGUID))
                    me->GetMotionMaster()->MovePoint(0, pArthas->GetPositionX(), pArthas->GetPositionY(), pArthas->GetPositionZ());
            }
        }

        void UpdateAI(const uint32 uiDiff)
        {
            if(!m_pInstance) return;

            if(m_pInstance->GetData(TYPE_ENCOUNTER) == IN_PROGRESS)
            {
                if(Creature* pMalganis = GetClosestCreatureWithEntry(me, NPC_MALGANIS_INTRO, 20.0f))
                {
                    if(Special == false)
                    {
                        float Dist = me->GetDistance2d(pMalganis->GetPositionX(), pMalganis->GetPositionY());
                        Dist = Dist + 2.0f;
                        MalganisScared(pMalganis, Dist, 1.0f);
                        me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_COWER);
                        m_uiStepTimer = 5000;
                        Special = true;
                    }
                }

                if(m_uiStepTimer < uiDiff && Conversion != true)
                {
                    Conversion = true;
                    if(Special != false)
                        DarkConversion(true);
                    else
                        DarkConversion(false);
                }
                else m_uiStepTimer -= uiDiff;

            }

            DoMeleeAttackIfReady();

            return;
        }
    };
};

void AddSC_culling_of_stratholme()
{
    new npc_chromi_middle();
    new npc_uther();
    new npc_arthas();
    new npc_arthas_priest();
    new npc_arthas_marine();
    new npc_dark_conversion();
}
