/*
 * Copyright (C) 2008-2011 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2006-2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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

/* ScriptData
SDName: Icecrown
SD%Complete: 70
SDComment: Quest support: 12807
SDCategory: Icecrown
EndScriptData */

/* ContentData
npc_arete
EndContentData */

#include "ScriptPCH.h"

/*######
## npc_arete
######*/

#define GOSSIP_ARETE_ITEM1 "Lord-Commander, I would hear your tale."
#define GOSSIP_ARETE_ITEM2 "<You nod slightly but do not complete the motion as the Lord-Commander narrows his eyes before he continues.>"
#define GOSSIP_ARETE_ITEM3 "I thought that they now called themselves the Scarlet Onslaught?"
#define GOSSIP_ARETE_ITEM4 "Where did the grand admiral go?"
#define GOSSIP_ARETE_ITEM5 "That's fine. When do I start?"
#define GOSSIP_ARETE_ITEM6 "Let's finish this!"
#define GOSSIP_ARETE_ITEM7 "That's quite a tale, Lord-Commander."

enum eArete
{
    GOSSIP_TEXTID_ARETE1        = 13525,
    GOSSIP_TEXTID_ARETE2        = 13526,
    GOSSIP_TEXTID_ARETE3        = 13527,
    GOSSIP_TEXTID_ARETE4        = 13528,
    GOSSIP_TEXTID_ARETE5        = 13529,
    GOSSIP_TEXTID_ARETE6        = 13530,
    GOSSIP_TEXTID_ARETE7        = 13531,

    QUEST_THE_STORY_THUS_FAR    = 12807
};

class npc_arete : public CreatureScript
{
public:
    npc_arete() : CreatureScript("npc_arete") { }

    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
        if (pCreature->isQuestGiver())
            pPlayer->PrepareQuestMenu(pCreature->GetGUID());

        if (pPlayer->GetQuestStatus(QUEST_THE_STORY_THUS_FAR) == QUEST_STATUS_INCOMPLETE)
        {
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ARETE_ITEM1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_ARETE1, pCreature->GetGUID());
            return true;
        }

        pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
    {
        pPlayer->PlayerTalkClass->ClearMenus();
        switch(uiAction)
        {
            case GOSSIP_ACTION_INFO_DEF+1:
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ARETE_ITEM2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_ARETE2, pCreature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+2:
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ARETE_ITEM3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
                pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_ARETE3, pCreature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+3:
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ARETE_ITEM4, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
                pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_ARETE4, pCreature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+4:
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ARETE_ITEM5, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
                pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_ARETE5, pCreature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+5:
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ARETE_ITEM6, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
                pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_ARETE6, pCreature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+6:
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ARETE_ITEM7, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
                pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_ARETE7, pCreature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+7:
                pPlayer->CLOSE_GOSSIP_MENU();
                pPlayer->AreaExploredOrEventHappens(QUEST_THE_STORY_THUS_FAR);
                break;
        }

        return true;
    }
};

/*######
## npc_dame_evniki_kapsalis
######*/

enum eDameEnvikiKapsalis
{
    TITLE_CRUSADER    = 123
};

class npc_dame_evniki_kapsalis : public CreatureScript
{
public:
    npc_dame_evniki_kapsalis() : CreatureScript("npc_dame_evniki_kapsalis") { }

    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
        if (pPlayer->HasTitle(TITLE_CRUSADER))
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, GOSSIP_TEXT_BROWSE_GOODS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRADE);

        pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
    {
        pPlayer->PlayerTalkClass->ClearMenus();
        if (uiAction == GOSSIP_ACTION_TRADE)
            pPlayer->SEND_VENDORLIST(pCreature->GetGUID());
        return true;
    }
};

/*######
## npc_argent_tournament_post
######*/

enum eArgentTournamentPost
{
    SPELL_ROPE_BEAM                 = 63413,
    NPC_GORMOK_THE_IMPALER          = 35469,
    NPC_ICEHOWL                     = 35470
};

class npc_argent_tournament_post : public CreatureScript
{
public:
    npc_argent_tournament_post() : CreatureScript("npc_argent_tournament_post") { }

    struct npc_argent_tournament_postAI : public ScriptedAI
    {
        npc_argent_tournament_postAI(Creature* pCreature) : ScriptedAI(pCreature) {}

        void UpdateAI(const uint32 /*uiDiff*/)
        {
            if (me->IsNonMeleeSpellCasted(false))
                return;

            if (Creature* pTarget = me->FindNearestCreature(NPC_GORMOK_THE_IMPALER, 6.0f))
                DoCast(pTarget, SPELL_ROPE_BEAM);

            if (Creature* pTarget2 = me->FindNearestCreature(NPC_ICEHOWL, 6.0f))
                DoCast(pTarget2, SPELL_ROPE_BEAM);

            if (!UpdateVictim())
                return;
        }
    };

    CreatureAI *GetAI(Creature *creature) const
    {
        return new npc_argent_tournament_postAI(creature);
    }
};

/*######
## npc_alorah_and_grimmin
######*/

enum ealorah_and_grimmin
{
    SPELL_CHAIN                     = 68341,
    NPC_FJOLA_LIGHTBANE             = 36065,
    NPC_EYDIS_DARKBANE              = 36066,
    NPC_PRIESTESS_ALORAH            = 36101,
    NPC_PRIEST_GRIMMIN              = 36102
};

class npc_alorah_and_grimmin : public CreatureScript
{
public:
    npc_alorah_and_grimmin() : CreatureScript("npc_alorah_and_grimmin") { }

    struct npc_alorah_and_grimminAI : public ScriptedAI
    {
        npc_alorah_and_grimminAI(Creature* pCreature) : ScriptedAI(pCreature) {}

        bool uiCast;

        void Reset()
        {
            uiCast = false;
        }

        void UpdateAI(const uint32 /*uiDiff*/)
        {
            if (uiCast)
                return;
            uiCast = true;
            Creature* pTarget = NULL;

            switch(me->GetEntry())
            {
                case NPC_PRIESTESS_ALORAH:
                    pTarget = me->FindNearestCreature(NPC_EYDIS_DARKBANE, 10.0f);
                    break;
                case NPC_PRIEST_GRIMMIN:
                    pTarget = me->FindNearestCreature(NPC_FJOLA_LIGHTBANE, 10.0f);
                    break;
            }
            if (pTarget)
                DoCast(pTarget, SPELL_CHAIN);

            if (!UpdateVictim())
                return;
        }
    };

    CreatureAI *GetAI(Creature *creature) const
    {
        return new npc_alorah_and_grimminAI(creature);
    }
};

/*######
## npc_guardian_pavilion
######*/

enum eGuardianPavilion
{
    SPELL_TRESPASSER_H                            = 63987,
    AREA_SUNREAVER_PAVILION                       = 4676,

    AREA_SILVER_COVENANT_PAVILION                 = 4677,
    SPELL_TRESPASSER_A                            = 63986,
};

class npc_guardian_pavilion : public CreatureScript
{
public:
    npc_guardian_pavilion() : CreatureScript("npc_guardian_pavilion") { }

    struct npc_guardian_pavilionAI : public Scripted_NoMovementAI
    {
        npc_guardian_pavilionAI(Creature* pCreature) : Scripted_NoMovementAI(pCreature) {}

        void MoveInLineOfSight(Unit* pWho)
        {
            if (me->GetAreaId() != AREA_SUNREAVER_PAVILION && me->GetAreaId() != AREA_SILVER_COVENANT_PAVILION)
                return;

            if (!pWho || pWho->GetTypeId() != TYPEID_PLAYER || !me->IsHostileTo(pWho) || !me->isInBackInMap(pWho, INTERACTION_DISTANCE))
                return;

            if (pWho->HasAura(SPELL_TRESPASSER_H) || pWho->HasAura(SPELL_TRESPASSER_A))
                return;

            if (pWho->ToPlayer()->GetTeamId() == TEAM_ALLIANCE)
                pWho->CastSpell(pWho, SPELL_TRESPASSER_H, true);
            else
                pWho->CastSpell(pWho, SPELL_TRESPASSER_A, true);

        }
    };

    CreatureAI *GetAI(Creature *creature) const
    {
        return new npc_guardian_pavilionAI(creature);
    }
};
/*######
## npc_argent_tournament_mount
######*/

enum eArgentTournament
{
	QUEST_THE_ARGENT_TOURNAMENT_A	=	13667,	// pre-qs
	QUEST_THE_ARGENT_TOURNAMENT_H	=	13668,
	QUEST_MASTERY_OF_MELEE_A		=	13828,	// melee target
	QUEST_MASTERY_OF_MELEE_H		=	13829,
	QUEST_MASTERY_OF_THE_SBREAKER_A	=	13835,	// shield target
	QUEST_MASTERY_OF_THE_SBREAKER_H	=	13838,
	QUEST_MASTERY_OF_THE_CHARGE_A	=	13837,	// charge target
	QUEST_MASTERY_OF_THE_CHARGE_H	=	13839,
	QUEST_LEARNING_THE_REINS_A		=	13625,	// all 3 target types
	QUEST_LEARNING_THE_REINS_H		=	13677,
	QUEST_THE_ASPIRANTS_CHALLENGE_A	=	13679,	// defeat summoned mob: valiant
	QUEST_THE_ASPIRANTS_CHALLENGE_H	=	13680,
	QUEST_THE_GRAND_MELEE_HUMAN		=	13665,	// Valiant
	QUEST_THE_GRAND_MELEE_NELF		=	13761,
	QUEST_THE_GRAND_MELEE_DWARF		=	13745,
	QUEST_THE_GRAND_MELEE_GNOME		=	13750,
	QUEST_THE_GRAND_MELEE_DRAENEI	=	13756,
	QUEST_THE_GRAND_MELEE_ORC		=	13767,
	QUEST_THE_GRAND_MELEE_TROLL		=	13772,
	QUEST_THE_GRAND_MELEE_UNDEAD	=	13782,
	QUEST_THE_GRAND_MELEE_TAUREN	=	13777,
	QUEST_THE_GRAND_MELEE_BELF		=	13787,
	QUEST_THE_VALIANTS_CHALLENGE_HUMAN	=	13699,	// defeat summoned mob: champion
	QUEST_THE_VALIANTS_CHALLENGE_DRAENEI=	13724,
	QUEST_THE_VALIANTS_CHALLENGE_GNOME	=	13723,
	QUEST_THE_VALIANTS_CHALLENGE_NELF	=	13725,
	QUEST_THE_VALIANTS_CHALLENGE_DWARF	=	13713,
	QUEST_THE_VALIANTS_CHALLENGE_TAUREN	=	13728,
	QUEST_THE_VALIANTS_CHALLENGE_UNDEAD	=	13729,
	QUEST_THE_VALIANTS_CHALLENGE_ORC	=	13726,
	QUEST_THE_VALIANTS_CHALLENGE_BELF	=	13731,
	QUEST_THE_VALIANTS_CHALLENGE_TROLL	=	13727,
	QUEST_AMONG_THE_CHAMPIONS_LUURI_H	=	13811,	// Champion, lev3
	QUEST_AMONG_THE_CHAMPIONS_LUURI_A	=	13790,
	QUEST_AMONG_THE_CHAMPIONS_ILLYRIE_H	=	13814,
	QUEST_AMONG_THE_CHAMPIONS_ILLYRIE_A	=	13793,
    QUEST_VALIANT_OF_ORGRIMMAR          =   13707, // ranking
    QUEST_VALIANT_OF_SENJIN             =   13708,
    QUEST_VALIANT_OF_THUNDER_BLUFF      =   13709,
    QUEST_VALIANT_OF_UNDERCITY          =   13710,
    QUEST_VALIANT_OF_SILVERMOON         =   13711,
    QUEST_VALIANT_OF_STORMWIND          =   13593,
    QUEST_VALIANT_OF_IRONFORGE          =   13703,
    QUEST_VALIANT_OF_GNOMEREGAN         =   13704,
    QUEST_VALIANT_OF_THE_EXODAR         =   13705,
    QUEST_VALIANT_OF_DARNASSUS          =   13706,
    QUEST_ALLIANCE_TOURNAMENT_ELIGIBILITY_MARKER = 13686,
    QUEST_HORDE_TOURNAMENT_ELIGIBILITY_MARKER    = 13687,

	NPC_MELEE_TARGET					=	33229,
	NPC_CHARGE_TARGET					=	33272,
	NPC_RANGED_TARGET					=	33243,
	NPC_SENJIN_VALIANT					=	33285,
	NPC_ORGRIMMAR_VALIANT				=	33306,
	NPC_SILVERMOON_VALIANT				=	33382,
	NPC_THUNDER_BLUFF_VALIANT			=	33383,
	NPC_UNDERCITY_VALIANT				=	33384,
	NPC_GNOMEREGAN_VALIANT				=	33558,
	NPC_STORMWIND_VALIANT				=	33561,
	NPC_EXODAR_VALIANT					=	33562,
	NPC_IRONFORGE_VALIANT				=	33564,
	NPC_DARNASSUS_VALIANT				=	33559,
	NPC_DARNASSUS_CHAMPION				=	33738,
	NPC_GNOMEREGAN_CHAMPION				=	33740,
	NPC_EXODAR_CHAMPION					=	33739,
	NPC_IRONFORGE_CHAMPION				=	33743,
	NPC_STORMWIND_CHAMPION				=	33747,
	NPC_UNDERCITY_CHAMPION				=	33749,
	NPC_SILVERMOON_CHAMPION				=	33746,
	NPC_THUNDER_BLUFF_CHAMPION			=	33748,
	NPC_SENJIN_CHAMPION					=	33745,
	NPC_ORGRIMMAR_CHAMPION				=	33744,
    NPC_ARGENT_VALIANT                  =	33448,
	NPC_ARGENT_CHAMPION					=	33707,

	SPELL_TOURNAMENT_THRUST	=	62544,
	SPELL_TOURNAMENT_CHARGE	=	63010,
	SPELL_TOURNAMENT_SHIELD_BREAKER	=	62575,
	SPELL_TOURNAMENT_DEFEND			=	62552,
	SPELL_LANCE_EQUIPPED	=	62853,
	SPELL_MOUNTED_MELEE_VICTORY_MV1	=	62770,
	SPELL_MOUNTED_MELEE_VICTORY_MC	=	63596,
    SPELL_TOURNAMENT_QUEST_BLOCK_DUMMY_HIT = 62672,
    SPELL_TOURNAMENT_QUEST_SPECIAL_ATTACK_DUMMY_HIT = 62673,
    SPELL_TOURNAMENT_QUEST_CHARGE_DUMMY_HIT = 62658,
    SPELL_VULNERABLE        =   62665,
//	SPELL_REMOVE_LANCE		=	68474,

	AREA_ARGENT_TOURNAMENT_GROUNDS	=	4658,
	AREA_THE_RING_OF_CHAMPIONS		=	4669,
	AREA_THE_ASPIRANTS_RING			=	4670,
	AREA_THE_ARGENT_VALIANTS_RING	=	4671,
	AREA_THE_ALLIANCE_VALIANTS_RING	=	4672,
	AREA_THE_HORDE_VALIANTS_RING	=	4673,

	VEHICLEID_TOURNAMENT_MOUNT	= 349,

	ITEM_TOURNAMENT_LANCE		= 46106,
	ITEM_MARK_OF_THE_VALIANT	= 45127,
	ITEM_MARK_OF_THE_CHAMPION	= 45500,

	ACTION_TOURNAMENT_AREA_CHANGE = 14,
	ACTION_BEGIN_TOURNAMENT_DUEL  = 15,
	ACTION_LEAVE_COMBAT			  = 16
};

#define ARGENT_TOURNAMENT_AREA(a) (a == AREA_ARGENT_TOURNAMENT_GROUNDS || a == AREA_THE_RING_OF_CHAMPIONS || a == AREA_THE_ASPIRANTS_RING || a == AREA_THE_ARGENT_VALIANTS_RING || a == AREA_THE_ALLIANCE_VALIANTS_RING || a == AREA_THE_HORDE_VALIANTS_RING)
#define TEXTID_ATM_WRONG_AREA	10080
#define TEXTID_ATM_NO_LANCE		10081
#define TEXTID_ATM_NO_QUEST		10082
#define TEXTID_ATM_WRONG_START	10083

class npc_argent_tournament_mount : public CreatureScript
{
public:
    npc_argent_tournament_mount() : CreatureScript("npc_argent_tournament_mount") {}

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_argent_tournament_mountAI (pCreature);
    }

    struct npc_argent_tournament_mountAI : public ScriptedAI
    {

	    npc_argent_tournament_mountAI(Creature* pCreature) : ScriptedAI(pCreature)
	    { Reset(); }

	    uint64 m_DriverGUID;
	    uint32 m_uiTimer;
	    uint8 beforeUnSummon;
	    bool zoneOK, noPlayer;

	    void UpdateAI(const uint32 uiDiff)
	    {
		    if (noPlayer) return;
		    if (m_uiTimer < uiDiff)
		    {
			    zoneOK = ARGENT_TOURNAMENT_AREA(me->GetAreaId());   //Q: remove this when quest-mount-area-restriction will be implemented
			    if (! zoneOK)
			    {
				    if (--beforeUnSummon == 0) { me->ForcedDespawn(); Reset(); }
				    else if ((beforeUnSummon & 3) == 3) me->Say(TEXTID_ATM_WRONG_AREA, LANG_UNIVERSAL, m_DriverGUID);   //Q: session->Notify()?
			    }
			    else beforeUnSummon = 10;
			    m_uiTimer = 2000;
		    }
		    else m_uiTimer -= uiDiff;
	    }

	    void DoAction(const int32 param)
	    {
    //		sLog.outBasic("ATM: DoAction %i",param);
		    if (Player *driver = Unit::GetPlayer(*me, m_DriverGUID))
		    {
			    switch(param)
			    {
			    case ACTION_TOURNAMENT_AREA_CHANGE:
				    zoneOK = (ARGENT_TOURNAMENT_AREA(driver->GetAreaId()));
				    if (zoneOK) beforeUnSummon = 10;
				    break;
			    case ACTION_LEAVE_COMBAT:
				    driver->CombatStopWithPets(true);
				    driver->DeleteThreatList();
				    me->CombatStop(true);
				    me->DeleteThreatList();
	    //			me->SetReactState(REACT_PASSIVE);
				    break;
			    }
		    }
	    }

	    void PassengerBoarded(Unit *who, int8 seatId, bool apply)
	    {
		    if (!who)
			    return;

		    m_DriverGUID = who->GetGUID();

		    if (!who->ToPlayer())
			    return;

		    if (apply)
		    {
			    Player *rider = who->ToPlayer();
   			    if (! (rider->HasAura(SPELL_LANCE_EQUIPPED)))
                {
        		    me->Say(TEXTID_ATM_NO_LANCE, LANG_UNIVERSAL, m_DriverGUID);
	        	    me->RemoveCharmedBy(who);
	        	    Reset();
                    return;
                }
			    noPlayer = false;
			    me->InitCharmInfo();
			    me->SetReactState(REACT_PASSIVE);
		    }
		    else if (who->HasAura(SPELL_TOURNAMENT_DEFEND)) who->RemoveAura(SPELL_TOURNAMENT_DEFEND,0,0,AURA_REMOVE_BY_EXPIRE);
	    }

	    void OnCharmed(bool apply) {}

	    bool CanAIAttack(const Unit* /*whom*/) { return false; }

	    void EnterCombat(Unit *enemy)   //Q: this disables PvP; reconceed when duels enabled
	    {
            if (!enemy)
                return;

		    if (noPlayer) return;
		    if (!enemy->IsVehicle()) return;
            if (! enemy->GetCharmerOrOwnerPlayerOrPlayerItself()) return;
		    enemy->GetCharmerOrOwnerPlayerOrPlayerItself()->CombatStopWithPets(true);
		    enemy->DeleteThreatList();
		    DoAction(ACTION_LEAVE_COMBAT);
	    }

	    void Reset()
	    {
		    m_DriverGUID = 0;
		    m_uiTimer = 2*IN_MILLISECONDS;
		    beforeUnSummon = 10;	// in units of m_uiTimer; = 20 sec
		    zoneOK = noPlayer = true;
	    }
    };
};

enum eArgentTournamentTargets
{
	SPELL_TOURNAMENT_COUNTERATTACK	=	62709,
	SPELL_TOURNAMENT_DEFEND_NPC		=	64100
};

/*######
## npc_tournament_melee_target
######*/

class npc_tournament_melee_target : public CreatureScript
{
public:
    npc_tournament_melee_target() : CreatureScript("npc_tournament_melee_target") {}

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_tournament_melee_targetAI (pCreature);
    }

    struct npc_tournament_melee_targetAI : public Scripted_NoMovementAI
    {
	    npc_tournament_melee_targetAI(Creature* pCreature) : Scripted_NoMovementAI(pCreature) {}

	    bool CanAIAttack(const Unit* /*whom*/) { return false; }

	    void SpellHit(Unit *who, const SpellEntry *spell)
	    {
            if (!who)
                return;

		    if (spell->Id == SPELL_TOURNAMENT_THRUST)
		    {
			    who->CastSpell(me, SPELL_TOURNAMENT_COUNTERATTACK, true);
                if (who->GetCharmerOrOwnerPlayerOrPlayerItself()) who->GetCharmerOrOwnerPlayerOrPlayerItself()->KilledMonsterCredit(me->GetEntry(), me->GetGUID());
		    }
	    }

        void EnterCombat(Unit* enemy)
        {
            if (!enemy)
                return;

            DoStopAttack();
            me->SetFullHealth();
		    enemy->CombatStop(true);
		    enemy->DeleteThreatList();
        }
    };
};

/*######
## npc_tournament_other_target
######*/

class npc_tournament_other_target : public CreatureScript
{
public:
    npc_tournament_other_target() : CreatureScript("npc_tournament_other_target") {}

    CreatureAI* GetAI_npc_tournament_other_target(Creature* pCreature)
    {
        return new npc_tournament_other_targetAI (pCreature);
    }
    struct npc_tournament_other_targetAI : public Scripted_NoMovementAI
    {
	    npc_tournament_other_targetAI(Creature* pCreature) : Scripted_NoMovementAI(pCreature)
	    { Reset(); }

	    uint32 ui_Timer;
	    bool isProtected;

	    bool CanAIAttack(const Unit* /*whom*/) { return false; }

	    void UpdateAI(const uint32 uiDiff)
	    {
    //Q: probably a "[DND]Defend Aura" should be used for SPELL_TOURNAMENT_DEFEND_NPC and UpdateAI() removed
		    if (ui_Timer < uiDiff)
		    {
			    Reset();
		    }
		    else ui_Timer -= uiDiff;
	    }

	    void SpellHit(Unit *who,const SpellEntry *spell)
	    {
            if (!(spell->Id == SPELL_TOURNAMENT_SHIELD_BREAKER || spell->Id == SPELL_TOURNAMENT_CHARGE)) return;
		    if (isProtected)
            {
                isProtected = false;
                DoCast(SPELL_VULNERABLE);
            }
            else if (Player *quester = who->GetCharmerOrOwnerPlayerOrPlayerItself())
            {
                switch(me->GetEntry())
                {
                case NPC_RANGED_TARGET:
                    if (spell->Id == SPELL_TOURNAMENT_SHIELD_BREAKER) quester->KilledMonsterCredit(NPC_RANGED_TARGET, me->GetGUID());
                    break;
                case NPC_CHARGE_TARGET:
                    if (spell->Id == SPELL_TOURNAMENT_CHARGE) quester->KilledMonsterCredit(NPC_CHARGE_TARGET, me->GetGUID());
                    break;
                }
			    Reset();
		    }
	    }

	    void EnterCombat(Unit* who)
	    {
            DoStopAttack();
            me->SetFullHealth();
		    who->CombatStop(true);
		    who->DeleteThreatList();
	    }

        void Reset() { ui_Timer = urand(10000,30000); me->RemoveAllAuras(); DoCast(SPELL_TOURNAMENT_DEFEND_NPC); isProtected = true; }
    };
};

/*######
## npc_tournament_adviser
######*/

enum eTournamentAdviser
{
	NPC_JERAN_LOCKWOOD		=	33973,
	NPC_VALIS_WINDCHASER	=	33974,
	NPC_RUGAN_STEELBELLY	=	33972,

	SPELL_JERAN_LOCKWOOD_CREDIT		=	64113,
	SPELL_VALIS_WINDCHASER_CREDIT	=	64115,
	SPELL_RUGAN_STEELBELLY_CREDIT	=	64114,
};

class npc_tournament_adviser : public CreatureScript
{
public:
    npc_tournament_adviser() : CreatureScript("npc_tournament_adviser") {}

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_tournament_adviserAI(pCreature);
    }

    struct TournamentAdviser
    {
	    char *gossip_item[2];
	    uint32 gossip_textid[3];
	    uint32 helpinQuest[2];
	    uint32 questCredit;

	    TournamentAdviser(char* si1, char* si2, uint32 ti1, uint32 ti2,uint32 ti3, uint32 qa, uint32 qh, uint32 qc)
	    {
		    gossip_item[0] = si1; gossip_item[1]=si2;
		    gossip_textid[0] = ti1; gossip_textid[1] = ti2; gossip_textid[2] = ti3;
		    helpinQuest[0] = qa; helpinQuest[1] = qh;
		    questCredit = qc;
	    }

	    TournamentAdviser() {}
    };

    struct npc_tournament_adviserAI : public ScriptedAI
    {
	    npc_tournament_adviserAI(Creature *c) : ScriptedAI(c)
	    {
		    switch (c->GetEntry())
		    {
		    case NPC_JERAN_LOCKWOOD:
			    dialog = TournamentAdviser("Show me how to train with a Melee Target.","Tell me more about Defend and Thrust.",1000004,1000005,1000006,QUEST_MASTERY_OF_MELEE_A,QUEST_MASTERY_OF_MELEE_H,SPELL_JERAN_LOCKWOOD_CREDIT);
			    break;
		    case NPC_VALIS_WINDCHASER:
			    dialog = TournamentAdviser("Show me how to train with a Ranged Target.","Tell me more about using the Shield-Breaker.",1000007,1000008,1000009,QUEST_MASTERY_OF_THE_SBREAKER_A,QUEST_MASTERY_OF_THE_SBREAKER_H,SPELL_VALIS_WINDCHASER_CREDIT);
			    break;
		    case NPC_RUGAN_STEELBELLY:
			    dialog = TournamentAdviser("Show me how to train with a Charge Target.","Tell me more about the Charge.",1000010,1000011,1000012,QUEST_MASTERY_OF_THE_CHARGE_A,QUEST_MASTERY_OF_THE_CHARGE_H,SPELL_RUGAN_STEELBELLY_CREDIT);
			    break;
		    default:
			    sLog->outError("npc_tournament_adviserAI: wrong script assigned to entry %u, correct your DB!",c->GetEntry());
		    }
	    }

        TournamentAdviser dialog;
    };

    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
	    if (pCreature->isGossip())
	    {
	        if (pPlayer->GetQuestStatus(QUEST_THE_ARGENT_TOURNAMENT_A) == QUEST_STATUS_COMPLETE || pPlayer->GetQuestStatus(QUEST_THE_ARGENT_TOURNAMENT_H) == QUEST_STATUS_COMPLETE)
		    {
			    if (pPlayer->GetVehicle() && (pPlayer->GetVehicle()->GetVehicleInfo()->m_ID == VEHICLEID_TOURNAMENT_MOUNT) && pPlayer->HasAura(SPELL_LANCE_EQUIPPED))
			    {
                    npc_tournament_adviserAI* pMyAI = CAST_AI(npc_tournament_adviserAI, pCreature->AI());
				    pPlayer->PrepareGossipMenu(pCreature);
				    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, pMyAI->dialog.gossip_item[0], GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
				    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, pMyAI->dialog.gossip_item[1], GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
				    pPlayer->SEND_GOSSIP_MENU(pMyAI->dialog.gossip_textid[0], pCreature->GetGUID());
				    return true;
			    }
		    }
	    }
	    else sLog->outError("npc_tournament_adviser: gossip disabled for entry %u, correct your DB!",pCreature->GetEntry());
	    return false;
    }

    bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
    {
	    pPlayer->PrepareGossipMenu(pCreature);
        npc_tournament_adviserAI* pMyAI = CAST_AI(npc_tournament_adviserAI, pCreature->AI());
	    switch(uiAction)
	    {
	    case GOSSIP_ACTION_INFO_DEF+1:
		    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, pMyAI->dialog.gossip_item[1], GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
		    pPlayer->SEND_GOSSIP_MENU(pMyAI->dialog.gossip_textid[1], pCreature->GetGUID());
		    if (pPlayer->GetQuestStatus(pMyAI->dialog.helpinQuest[0]) == QUEST_STATUS_INCOMPLETE
                || pPlayer->GetQuestStatus(pMyAI->dialog.helpinQuest[1]) == QUEST_STATUS_INCOMPLETE)
                pPlayer->CastSpell(pPlayer, pMyAI->dialog.questCredit, true);
		    break;
	    case GOSSIP_ACTION_INFO_DEF+2:
		    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, pMyAI->dialog.gossip_item[0], GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
		    pPlayer->SEND_GOSSIP_MENU(pMyAI->dialog.gossip_textid[2], pCreature->GetGUID());
		    break;
	    }
	    return true;
    }
};

/*######
## npc_squire_david
######*/

enum eSquireDavid
{
    GOSSIP_TEXTID_SQUIRE    = 14407
};

#define GOSSIP_SQUIRE_ITEM_1 "I am ready to fight!"
#define GOSSIP_SQUIRE_ITEM_2 "How do the Argent Crusader raiders fight?"

class npc_squire_david : public CreatureScript
{
public:
    npc_squire_david() : CreatureScript("npc_squire_david") {}

    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
	    if (pPlayer->isInCombat()) return false;
	    if (! pPlayer->GetVehicle()) return false;
	    if (pPlayer->GetVehicle()->GetVehicleInfo()->m_ID != VEHICLEID_TOURNAMENT_MOUNT) return false;
	    if (! pPlayer->HasAura(SPELL_LANCE_EQUIPPED)) return false;
        if (pPlayer->GetQuestStatus(QUEST_THE_ASPIRANTS_CHALLENGE_H) == QUEST_STATUS_INCOMPLETE ||
            pPlayer->GetQuestStatus(QUEST_THE_ASPIRANTS_CHALLENGE_A) == QUEST_STATUS_INCOMPLETE)//We need more info about it.
        {
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SQUIRE_ITEM_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SQUIRE_ITEM_2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
	        pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_SQUIRE, pCreature->GetGUID());
		    return true;
        }
	    return false;
    }

    bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
    {
        pPlayer->PlayerTalkClass->ClearMenus();
        if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
        {
            pPlayer->CLOSE_GOSSIP_MENU();
            Creature* av = pCreature->SummonCreature(NPC_ARGENT_VALIANT, 8575.451f, 952.472f, 547.554f, 0.38f,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT,300000);
            if (av && av->AI())
            {
	            av->AI()->SetGUID(pPlayer->GetGUID());
	            av->AI()->DoAction(ACTION_BEGIN_TOURNAMENT_DUEL);
            }
        }
	    return false;
        //else
            //pPlayer->SEND_GOSSIP_MENU(???, pCreature->GetGUID()); Missing text
    }
};

/*######
## npc_squire_danny
######*/

enum eSquireDanny
{
    GOSSIP_TEXTID_SQUIRE_C    = 14421
};

// #define GOSSIP_SQUIRE_ITEM_1 "I am ready to fight!"
#define GOSSIP_SQUIRE_ITEM_3 "How do the Argent Champion raiders fight?"

class npc_squire_danny : public CreatureScript
{
public:
    npc_squire_danny() : CreatureScript("npc_squire_danny") {}

    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
	    if (pPlayer->isInCombat()) return false;
	    if (! pPlayer->GetVehicle()) return false;
	    if (pPlayer->GetVehicle()->GetVehicleInfo()->m_ID != VEHICLEID_TOURNAMENT_MOUNT) return false;
	    if (! pPlayer->HasAura(SPELL_LANCE_EQUIPPED)) return false;
        if (pPlayer->GetQuestStatus(QUEST_THE_VALIANTS_CHALLENGE_HUMAN) == QUEST_STATUS_INCOMPLETE ||
		    pPlayer->GetQuestStatus(QUEST_THE_VALIANTS_CHALLENGE_GNOME) == QUEST_STATUS_INCOMPLETE ||
		    pPlayer->GetQuestStatus(QUEST_THE_VALIANTS_CHALLENGE_NELF) == QUEST_STATUS_INCOMPLETE ||
		    pPlayer->GetQuestStatus(QUEST_THE_VALIANTS_CHALLENGE_DWARF) == QUEST_STATUS_INCOMPLETE ||
		    pPlayer->GetQuestStatus(QUEST_THE_VALIANTS_CHALLENGE_DRAENEI) == QUEST_STATUS_INCOMPLETE ||
		    pPlayer->GetQuestStatus(QUEST_THE_VALIANTS_CHALLENGE_UNDEAD) == QUEST_STATUS_INCOMPLETE ||
		    pPlayer->GetQuestStatus(QUEST_THE_VALIANTS_CHALLENGE_ORC) == QUEST_STATUS_INCOMPLETE ||
		    pPlayer->GetQuestStatus(QUEST_THE_VALIANTS_CHALLENGE_BELF) == QUEST_STATUS_INCOMPLETE ||
		    pPlayer->GetQuestStatus(QUEST_THE_VALIANTS_CHALLENGE_TROLL) == QUEST_STATUS_INCOMPLETE ||
            pPlayer->GetQuestStatus(QUEST_THE_VALIANTS_CHALLENGE_TAUREN) == QUEST_STATUS_INCOMPLETE)
        {
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SQUIRE_ITEM_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SQUIRE_ITEM_3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
	        pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_SQUIRE_C, pCreature->GetGUID());
		    return true;
        }
	    return false;
    }

    bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
    {
        pPlayer->PlayerTalkClass->ClearMenus();
        if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
        {
            pPlayer->CLOSE_GOSSIP_MENU();
		    Creature *ac = pCreature->SummonCreature(NPC_ARGENT_CHAMPION, 8558.37f, 1113.10f, 556.787f, 1.932f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 300000);
            if (ac && ac->AI())
            {
		        ac->AI()->SetGUID(pPlayer->GetGUID());
		        ac->AI()->DoAction(ACTION_BEGIN_TOURNAMENT_DUEL);
            }
        }
	    return false;
        //else
            //pPlayer->SEND_GOSSIP_MENU(???, pCreature->GetGUID()); Missing text
    }
};

/*######
## npc_tournament_duellist
######*/

enum eTournamentDuellist
{
    SPELL_CHARGE                = 63010,
    SPELL_SHIELD_BREAKER        = 65147,
	SPELL_TOURNAMENT_THRUST_NPC	= 68505,
	EQUIPID_ARGENT_LANCE		= 10011
};

#define GOSSIP_TEXTID_DUELLIST	1000013
#define TEXTID_DUELLIST_LOSE	-1999957
#define TEXTID_DUELLIST_WIN		-1999958
#define GOSSIP_DUELLIST_ITEM "I am ready to fight!"

class npc_tournament_duellist : public CreatureScript
{
public:
    npc_tournament_duellist() : CreatureScript("npc_tournament_duellist") {}

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_tournament_duellistAI (pCreature);
    }

    struct npc_tournament_duellistAI : public ScriptedAI
    {
	    enum eDuellistMotions
	    {
		    POINT_START_COMBAT = 1,
		    POINT_TRY_DISTANCE = 2
	    };

	    npc_tournament_duellistAI(Creature *pCreature) : ScriptedAI(pCreature)
	    {
		    switch(pCreature->GetEntry())
		    {
		    case NPC_ARGENT_VALIANT:
			    allowed_area = AREA_THE_ASPIRANTS_RING;
			    x0=8600.97f; y0=964.09f; z0=547.55401f;
			    isChampion = false;
			    pCreature->LoadCreaturesAddon();
			    pCreature->LoadEquipment(EQUIPID_ARGENT_LANCE);
			    break;
		    case NPC_ARGENT_CHAMPION:
			    allowed_area = AREA_THE_ARGENT_VALIANTS_RING;
			    x0=8558.37f; y0=1113.10f; z0=556.787f;
			    pCreature->LoadCreaturesAddon();
			    pCreature->LoadEquipment(EQUIPID_ARGENT_LANCE);
			    isChampion = true;
			    break;
		    case NPC_STORMWIND_VALIANT:
		    case NPC_IRONFORGE_VALIANT:
		    case NPC_GNOMEREGAN_VALIANT:
		    case NPC_EXODAR_VALIANT:
		    case NPC_DARNASSUS_VALIANT:
			    allowed_area = AREA_THE_ALLIANCE_VALIANTS_RING;
			    x0=8660.467f; y0=723.503f; z0=547.5120f;
			    isChampion = false;
			    break;
		    case NPC_ORGRIMMAR_VALIANT:
		    case NPC_SENJIN_VALIANT:
		    case NPC_UNDERCITY_VALIANT:
		    case NPC_THUNDER_BLUFF_VALIANT:
		    case NPC_SILVERMOON_VALIANT:
			    allowed_area = AREA_THE_HORDE_VALIANTS_RING;
			    x0=8337.792f; y0=719.068f; z0=553.7016f;
			    isChampion = false;
			    break;
		    case NPC_DARNASSUS_CHAMPION:
		    case NPC_GNOMEREGAN_CHAMPION:
		    case NPC_EXODAR_CHAMPION:
		    case NPC_IRONFORGE_CHAMPION:
		    case NPC_STORMWIND_CHAMPION:
		    case NPC_UNDERCITY_CHAMPION:
		    case NPC_SILVERMOON_CHAMPION:
		    case NPC_THUNDER_BLUFF_CHAMPION:
		    case NPC_SENJIN_CHAMPION:
		    case NPC_ORGRIMMAR_CHAMPION:
			    allowed_area = AREA_THE_RING_OF_CHAMPIONS;
			    x0=8429.03f; y0=951.40f; z0=544.6752f;
			    isChampion = true;
			    break;
		    default:
			    sLog->outError("npc_tournament_duellist: wrong script assignment to entry %u, correct your DB!",pCreature->GetEntry());
		    }
		    if (isChampion)
		    {
			    mxChargeTime = 4000;        // cd 2s + gcd 2s
			    mxShieldBreakerTime = 6000; // cd 0!
			    mxDefendTime = 10000;       // cd 3s
			    mxThrustTime = 2500;        // cd 2s
			    miRunOffTime = 5000;
			    mxRunOffTime = 12000;
		    }
		    else
		    {
			    mxChargeTime = 7000;
			    mxShieldBreakerTime = 10000;
			    mxDefendTime = 20000;
			    mxThrustTime = 3000;
			    miRunOffTime = 10000;
			    mxRunOffTime = 20000;
		    }
            enemyGUID = 0;
            uiChargeTimer = mxChargeTime;
            uiShieldBreakerTimer = mxShieldBreakerTime;
            uiDefendTimer = mxDefendTime;
            uiThrustTimer = mxThrustTime;
            uiRunOffTimer = urand(miRunOffTime,mxRunOffTime);
            zoneOK = noEnemy = true;
            myO = pCreature->GetOrientation();
            pCreature->RemoveUnitMovementFlag(MOVEMENTFLAG_WALKING);
	    }

	    float x0,y0,z0,myO;
	    uint64 enemyGUID;
	    uint32 uiChargeTimer, uiShieldBreakerTimer, uiDefendTimer, uiThrustTimer, uiRunOffTimer;
	    uint32 mxChargeTime,  mxShieldBreakerTime,  mxDefendTime,  mxThrustTime,  miRunOffTime, mxRunOffTime;
	    uint32 allowed_area;
	    bool zoneOK, noEnemy, isChampion;

	    void UpdateAI(const uint32 uiDiff)
	    {
		    if (noEnemy) return;
		    Player *enemyPlayer = Player::GetPlayer(*me, enemyGUID);
		    if (!enemyPlayer || !enemyPlayer->GetVehicleBase()) { WinCombat(); return; }

            if (uiChargeTimer <= uiDiff)
            {
			    if (!me->isMoving()) DoCast(enemyPlayer->GetVehicleBase(),SPELL_CHARGE);
                uiChargeTimer = mxChargeTime;
            } else uiChargeTimer -= uiDiff;

            if (uiShieldBreakerTimer <= uiDiff)
            {
			    if (!me->isMoving()) DoCast(enemyPlayer->GetVehicleBase(),SPELL_SHIELD_BREAKER);
                uiShieldBreakerTimer = mxShieldBreakerTime;
            } else uiShieldBreakerTimer -= uiDiff;

		    if (uiThrustTimer <= uiDiff)
		    {
			    if (!me->isMoving()) DoCast(enemyPlayer->GetVehicleBase(),SPELL_TOURNAMENT_THRUST_NPC);
                uiThrustTimer = mxThrustTime;
		    } else uiThrustTimer -= uiDiff;

		    if (uiDefendTimer <= uiDiff)
		    {
			    DoCast(SPELL_TOURNAMENT_DEFEND);
			    uiDefendTimer = mxDefendTime;
		    } else uiDefendTimer -= uiDiff;

		    if (uiRunOffTimer <= uiDiff)
		    {
			    float xn, yn, zn;
			    enemyPlayer->GetNearPoint(enemyPlayer,xn,yn,zn,0.0f,10.0f,me->GetAngle(x0,y0));
			    me->GetMotionMaster()->MovePoint(POINT_TRY_DISTANCE,xn,yn,zn+0.02f);
			    uiRunOffTimer = urand(miRunOffTime,mxRunOffTime);
		    } else uiRunOffTimer -= uiDiff;

    //		me->SetFacingToObject(me->getVictim());
		    DoMeleeAttackIfReady();
	    }

	    void DoAction(const int32 param)
	    {
		    switch(param)
		    {
		    case ACTION_BEGIN_TOURNAMENT_DUEL:
			    float x,y,z;
			    me->RemoveFlag(UNIT_NPC_FLAGS,UNIT_NPC_FLAG_GOSSIP);
			    x = me->GetPositionX();
			    y = me->GetPositionY();
			    z = me->GetPositionZ();
			    me->GetMotionMaster()->MovePoint(POINT_START_COMBAT,0.5*(x0+x),0.5*(y0+y),0.5*(z0+z));
			    break;
		    }
	    }

	    void MovementInform(uint32 mtType, uint32 data)
	    {
		    if (mtType == POINT_MOTION_TYPE)
		    {
    //			sLog.outBasic("duellist: point motion, reached; data =%i",data);
			    Player *enemy = Player::GetPlayer(*me, enemyGUID);
			    if (!enemy) return;
			    Creature *mount = enemy->GetVehicleCreatureBase();
			    me->SetFacingToObject(mount);
			    //me->SendUpdateToPlayer(enemy);
			    switch(data)
			    {
			    case POINT_START_COMBAT:
                    noEnemy = false;
                    DoCast(SPELL_TOURNAMENT_DEFEND);
				    me->setFaction(14);
				    me->SetReactState(REACT_AGGRESSIVE);
				    if (mount)
				    {
					    me->AddThreat(mount,0.0f);
					    AttackStart(mount);
					    me->GetMotionMaster()->MoveChase(mount,ATTACK_DISTANCE);
				    }
				    break;
			    case POINT_TRY_DISTANCE:
				    if (urand(0,2)) uiChargeTimer = 0;
				    else uiShieldBreakerTimer = 0;
    //				sLog.outBasic("npc_tournament_duellist timers: charge %u, sbreak %u",uiChargeTimer,uiShieldBreakerTimer);
				    break;
			    }
		    }
	    }

	    void JustReachedHome()
	    {
		    me->SetFlag(UNIT_NPC_FLAGS,UNIT_NPC_FLAG_GOSSIP);
            me->RemoveUnitMovementFlag(MOVEMENTFLAG_WALKING);
            if (me->HasAura(SPELL_TOURNAMENT_DEFEND)) me->RemoveAurasDueToSpell(SPELL_TOURNAMENT_DEFEND);
            Reset();
	    }

	    void DamageTaken(Unit *enemy, uint32 &dmg)
	    {
		    if (me->GetHealth() > dmg) return;
		    dmg = 0;
            DoStopAttack();
		    me->RestoreFaction();
            me->SetFullHealth();
		    uint64 eGUID = enemyGUID;
		    EnterEvadeMode();
            if (me->isSummon()) me->DespawnOrUnsummon(500);
		    Creature *enemyMount = enemy->ToCreature();
		    if (!enemyMount) return;
		    if (!enemyMount->IsVehicle()) return;
		    if (enemyMount->GetVehicleKit()->GetVehicleInfo()->m_ID != VEHICLEID_TOURNAMENT_MOUNT) return;
		    if (!enemyMount->GetVehicleKit()->GetPassenger(0)) return;
		    if (enemyMount->GetVehicleKit()->GetPassenger(0)->GetGUID() != eGUID) return;
            Player *quester = Player::GetPlayer(*me, eGUID);
		    DoScriptText(TEXTID_DUELLIST_LOSE,me,quester);
            if (isChampion)
                if (me->GetEntry() == NPC_ARGENT_CHAMPION) quester->KilledMonsterCredit(NPC_ARGENT_CHAMPION,me->GetGUID());
                else quester->CastSpell(quester,SPELL_MOUNTED_MELEE_VICTORY_MC,false);
            else
                if (me->GetEntry() == NPC_ARGENT_VALIANT) quester->KilledMonsterCredit(NPC_ARGENT_VALIANT,me->GetGUID());
                else quester->CastSpell(quester,SPELL_MOUNTED_MELEE_VICTORY_MV1,false);
		    if (enemyMount->AI()) enemyMount->AI()->DoAction(ACTION_LEAVE_COMBAT);
	    }

	    void SetGUID(const uint64 &guid, int32 id) { enemyGUID = guid; }

	    void Reset()
	    {
            me->SetOrientation(myO);
		    enemyGUID = 0;
		    uiChargeTimer = mxChargeTime;
		    uiShieldBreakerTimer = mxShieldBreakerTime;
		    uiDefendTimer = mxDefendTime;
		    uiThrustTimer = mxThrustTime;
		    uiRunOffTimer = urand(miRunOffTime,mxRunOffTime);
		    zoneOK = noEnemy = true;
	    }

	    void WinCombat()
	    {
		    DoScriptText(TEXTID_DUELLIST_WIN,me);
		    me->RestoreFaction();
            DoStopAttack();
            if (me->isSummon()) me->DespawnOrUnsummon(500);
		    else EnterEvadeMode();
	    }
    };

    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
        if (pCreature->GetEntry() == NPC_ARGENT_VALIANT || pCreature->GetEntry() == NPC_ARGENT_CHAMPION) return false;
	    if (! pPlayer->GetVehicle() || ! pPlayer->HasAura(SPELL_LANCE_EQUIPPED)) return false;
	    if (pPlayer->isInCombat()) return false;
	    if (pPlayer->GetVehicle()->GetVehicleInfo()->m_ID != VEHICLEID_TOURNAMENT_MOUNT) return false;
	    Creature *mount = pPlayer->GetVehicleCreatureBase();
    //	uint32 quest;
        bool questOK;
	    switch (pCreature->GetEntry())
	    {
		    case NPC_STORMWIND_VALIANT:
		    case NPC_IRONFORGE_VALIANT:
		    case NPC_GNOMEREGAN_VALIANT:
		    case NPC_EXODAR_VALIANT:
		    case NPC_DARNASSUS_VALIANT:
                questOK = (pPlayer->GetQuestStatus(QUEST_THE_GRAND_MELEE_HUMAN) == QUEST_STATUS_INCOMPLETE
                    || pPlayer->GetQuestStatus(QUEST_THE_GRAND_MELEE_DWARF) == QUEST_STATUS_INCOMPLETE
                    || pPlayer->GetQuestStatus(QUEST_THE_GRAND_MELEE_GNOME) == QUEST_STATUS_INCOMPLETE
                    || pPlayer->GetQuestStatus(QUEST_THE_GRAND_MELEE_NELF) == QUEST_STATUS_INCOMPLETE
                    || pPlayer->GetQuestStatus(QUEST_THE_GRAND_MELEE_DRAENEI) == QUEST_STATUS_INCOMPLETE);
                break;
		    case NPC_ORGRIMMAR_VALIANT:
		    case NPC_SENJIN_VALIANT:
		    case NPC_UNDERCITY_VALIANT:
		    case NPC_THUNDER_BLUFF_VALIANT:
		    case NPC_SILVERMOON_VALIANT:
			    questOK = (pPlayer->GetQuestStatus(QUEST_THE_GRAND_MELEE_ORC) == QUEST_STATUS_INCOMPLETE
                    || pPlayer->GetQuestStatus(QUEST_THE_GRAND_MELEE_TROLL) == QUEST_STATUS_INCOMPLETE
                    || pPlayer->GetQuestStatus(QUEST_THE_GRAND_MELEE_UNDEAD) == QUEST_STATUS_INCOMPLETE
                    || pPlayer->GetQuestStatus(QUEST_THE_GRAND_MELEE_BELF) == QUEST_STATUS_INCOMPLETE
                    || pPlayer->GetQuestStatus(QUEST_THE_GRAND_MELEE_TAUREN) == QUEST_STATUS_INCOMPLETE);
			    break;
		    case NPC_DARNASSUS_CHAMPION:
		    case NPC_GNOMEREGAN_CHAMPION:
		    case NPC_EXODAR_CHAMPION:
		    case NPC_IRONFORGE_CHAMPION:
		    case NPC_STORMWIND_CHAMPION:
                questOK = (pPlayer->GetQuestStatus(QUEST_AMONG_THE_CHAMPIONS_ILLYRIE_A) == QUEST_STATUS_INCOMPLETE
                    || pPlayer->GetQuestStatus(QUEST_AMONG_THE_CHAMPIONS_LUURI_A) == QUEST_STATUS_INCOMPLETE);
                break;
		    case NPC_UNDERCITY_CHAMPION:
		    case NPC_SILVERMOON_CHAMPION:
		    case NPC_THUNDER_BLUFF_CHAMPION:
		    case NPC_SENJIN_CHAMPION:
		    case NPC_ORGRIMMAR_CHAMPION:
                questOK = (pPlayer->GetQuestStatus(QUEST_AMONG_THE_CHAMPIONS_ILLYRIE_H) == QUEST_STATUS_INCOMPLETE
                    || pPlayer->GetQuestStatus(QUEST_AMONG_THE_CHAMPIONS_LUURI_H) == QUEST_STATUS_INCOMPLETE);
			    break;
	    }
	    if (! questOK) return false;
	    pPlayer->PrepareGossipMenu(pCreature);
	    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_DUELLIST_ITEM, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
	    pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_DUELLIST, pCreature->GetGUID());
	    return true;
    }

    bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
    {
        pPlayer->PlayerTalkClass->ClearMenus();
	    if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
	    {
		    pPlayer->CLOSE_GOSSIP_MENU();
		    pCreature->AI()->SetGUID(pPlayer->GetGUID());
		    pCreature->AI()->DoAction(ACTION_BEGIN_TOURNAMENT_DUEL);
	    }
	    return false;
    }
};

/*struct questgiver_argent_tournamentAI : public ScriptedAI
{
	questgiver_argent_tournamentAI(Creature *pCreature): ScriptedAI(pCreature){}
};

bool GossipHello_questgiver_argent_tournament(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->isQuestGiver())
    {	
//        Object *pObject = (Object*)pCreature;
        QuestRelations QR = objmgr.mCreatureQuestRelations;
        QuestRelations QIR = objmgr.mCreatureQuestInvolvedRelations;

        QuestMenu &qm = pPlayer->PlayerTalkClass->GetQuestMenu();
        qm.ClearMenu();

        for (QuestRelations::const_iterator i = QIR.lower_bound(pCreature->GetEntry()); i != QIR.upper_bound(pCreature->GetEntry()); ++i)
        {
            uint32 quest_id = i->second;
            QuestStatus status = pPlayer->GetQuestStatus(quest_id);
            if (!pPlayer->GetQuestRewardStatus(quest_id)) qm.AddMenuItem(quest_id, DIALOG_STATUS_UNK2);
        }

//        bool EligibilityAlliance = pPlayer->GetQuestStatus(QUEST_ALLIANCE_TOURNAMENT_ELIGIBILITY_MARKER) == QUEST_STATUS_COMPLETE;
//        bool EligibilityHorde = pPlayer->GetQuestStatus(QUEST_HORDE_TOURNAMENT_ELIGIBILITY_MARKER) == QUEST_STATUS_COMPLETE;

        for (QuestRelations::const_iterator i = QR.lower_bound(pCreature->GetEntry()); i != QR.upper_bound(pCreature->GetEntry()); ++i)
        {
            uint32 quest_id = i->second;
            Quest const* pQuest = objmgr.GetQuestTemplate(quest_id);
            if (!pQuest) continue;
            QuestStatus status = pPlayer->GetQuestStatus(quest_id);
            switch(quest_id)
            {
            case QUEST_VALIANT_OF_ORGRIMMAR:
            case QUEST_VALIANT_OF_SENJIN:
            case QUEST_VALIANT_OF_THUNDER_BLUFF:
            case QUEST_VALIANT_OF_UNDERCITY:
            case QUEST_VALIANT_OF_SILVERMOON:
                if(pPlayer->GetQuestStatus(QUEST_HORDE_TOURNAMENT_ELIGIBILITY_MARKER) != QUEST_STATUS_COMPLETE)
                {
                    if(pQuest->IsAutoComplete() && pPlayer->CanTakeQuest(pQuest, false)) qm.AddMenuItem(quest_id, DIALOG_STATUS_UNK2);
                    else if(status == QUEST_STATUS_NONE && pPlayer->CanTakeQuest(pQuest, false)) qm.AddMenuItem(quest_id, DIALOG_STATUS_CHAT);
                }
                break;
            case QUEST_VALIANT_OF_STORMWIND:
            case QUEST_VALIANT_OF_IRONFORGE:
            case QUEST_VALIANT_OF_GNOMEREGAN:
            case QUEST_VALIANT_OF_DARNASSUS:
            case QUEST_VALIANT_OF_THE_EXODAR:
                if(pPlayer->GetQuestStatus(QUEST_ALLIANCE_TOURNAMENT_ELIGIBILITY_MARKER) != QUEST_STATUS_COMPLETE)
               {
                    if(pQuest->IsAutoComplete() && pPlayer->CanTakeQuest(pQuest, false)) qm.AddMenuItem(quest_id, DIALOG_STATUS_UNK2);
                    else if(status == QUEST_STATUS_NONE && pPlayer->CanTakeQuest(pQuest, false)) qm.AddMenuItem(quest_id, DIALOG_STATUS_CHAT);
                }
                break;
            default:
                if (pQuest->IsAutoComplete() && pPlayer->CanTakeQuest(pQuest, false)) qm.AddMenuItem(quest_id, DIALOG_STATUS_UNK2);
                else if (status == QUEST_STATUS_NONE && pPlayer->CanTakeQuest(pQuest, false)) qm.AddMenuItem(quest_id, DIALOG_STATUS_CHAT);
                break;
            }
        }
    }
    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    return true;
}

CreatureAI* GetAI_questgiver_argent_tournament(Creature* pCreature)
{
    return new questgiver_argent_tournamentAI (pCreature);
} */

void AddSC_icecrown()
{
    new npc_arete();
    new npc_dame_evniki_kapsalis();
    new npc_argent_tournament_post();
    new npc_alorah_and_grimmin();
    new npc_guardian_pavilion();
    new npc_argent_tournament_mount();
    new npc_tournament_melee_target();
    new npc_tournament_other_target();
    new npc_tournament_adviser();
    new npc_squire_david();
    new npc_squire_danny();
    new npc_tournament_duellist();
}
