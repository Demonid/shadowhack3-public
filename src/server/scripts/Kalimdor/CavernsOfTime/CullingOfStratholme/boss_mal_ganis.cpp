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

/* Script Data Start
SDName: Boss mal_ganis
SDAuthor: Tartalo
SD%Complete: 80
SDComment: TODO: Intro & outro
SDCategory:
Script Data End */

#include "ScriptPCH.h"
#include "culling_of_stratholme.h"

/*enum Yells
{
	SAY_INTRO_1                                 = -1595009,
	SAY_INTRO_2                                 = -1595010,
	SAY_AGGRO                                   = -1595011,
	SAY_KILL_1                                  = -1595012,
	SAY_KILL_2                                  = -1595013,
	SAY_KILL_3                                  = -1595014,
	SAY_SLAY_1                                  = -1595015,
	SAY_SLAY_2                                  = -1595016,
	SAY_SLAY_3                                  = -1595017,
	SAY_SLAY_4                                  = -1595018,
	SAY_SLEEP_1                                 = -1595019,
	SAY_SLEEP_2                                 = -1595020,
	SAY_30HEALTH                                = -1595021,
	SAY_15HEALTH                                = -1595022,
	SAY_ESCAPE_SPEECH_1                         = -1595023,
	SAY_ESCAPE_SPEECH_2                         = -1595024,
	SAY_OUTRO                                   = -1595025,
};*/

enum Says
{
	SAY_MALGANIS_AGGRO       = -1594170,  
	SAY_MALGANIS_SLAY01      = -1594172, 
	SAY_MALGANIS_SLAY02      = -1594173, 
	SAY_MALGANIS_SLAY03      = -1594174,
	SAY_MALGANIS_SLAY04      = -1594175,
	SAY_MALGANIS_SLAY05      = -1594176,
	SAY_MALGANIS_SLAY06      = -1594177,
	SAY_MALGANIS_SLAY07      = -1594166,
	SAY_MALGANIS_SLEEP01     = -1594185,
	SAY_MALGANIS_SLEEP02     = -1594186,
	SAY_MALGANIS_Sleep       = -1594178,
	SAY_MALGANIS_15HP        = -1594179,
};

enum MalGanisSpells
{
	SPELL_SWAMP_N                          = 52720,
	SPELL_SWAMP_H                          = 58852,
	SPELL_MIND_BLAST_N                     = 52722,
	SPELL_MIND_BLAST_H                     = 58850,
	SPELL_SLEEP_N                          = 52721,
	SPELL_SLEEP_H                          = 58849,
	SPELL_VAMPIRE                          = 52723
};

class boss_mal_ganis : public CreatureScript
{
public:
    boss_mal_ganis() : CreatureScript("boss_mal_ganis") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_mal_ganisAI (pCreature);
    }

    struct boss_mal_ganisAI : public ScriptedAI
    {
		boss_mal_ganisAI(Creature *c) : ScriptedAI(c)
		{
			pInstance = c->GetInstanceScript();
			Reset();
		}

		bool Sleep;
		bool Vampire;
		uint32 Phase;
		Creature* Malganis;
		Creature* Arthas;

		uint32 Swamp_Timer;
		uint32 MindBlast_Timer;
		uint32 Sleep_Timer;
		uint32 Vampire_Timer;

		InstanceScript* pInstance;

		void Reset() 
		{ 
			Sleep = false;
			Vampire = false;
			Swamp_Timer = 6300;
			MindBlast_Timer = 11300;
			Sleep_Timer = 17300;
			Vampire_Timer = 30000;
		}

		void AttackStart(Unit* who)
		{
			if(pInstance->GetData(TYPE_PHASE) > 9) return;

			if(pInstance->GetData(TYPE_MALGANIS) != IN_PROGRESS) return;

			if(!who || who == me)
				return;

			me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_OOC_NOT_ATTACKABLE);

			ScriptedAI::AttackStart(who);
		}

		void KillCreditMalganis()
		{
			Map *map = me->GetMap();
            if (!map || !map->IsDungeon())
                return;

			Map::PlayerList const& players = map->GetPlayers();
			if (!players.isEmpty())
			{
				for(Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
				{
					if(Player* pPlayer = itr->getSource())
					{
						pPlayer->KilledMonsterCredit(31006, 0);
						if (pInstance->GetData(TYPE_DIFF)==DUNGEON_DIFFICULTY_HEROIC)
						{
							pPlayer->KilledMonsterCredit(31217, 0);//ger
						}
						else
						{
							pPlayer->KilledMonsterCredit(26533, 0);//normal
						};
						//pPlayer->KilledMonsterCredit(me->GetEntry(), me->GetGUID());
					}
				}
			}
			if (pInstance)
				pInstance->DoUpdateAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_BE_SPELL_TARGET, 58630);
		}

		void EnterEvadeMode()
		{
			me->RemoveAllAuras();
			me->DeleteThreatList();
			me->CombatStop(true);
			me->LoadCreaturesAddon();

			if(pInstance->GetData(TYPE_PHASE) > 9)
			{
				KillCreditMalganis();
				me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
				if (Creature* pArthas = Unit::GetCreature(*me, pInstance->GetData64(NPC_ARTHAS)))
				{
					me->SetInCombatWith(pArthas);
				}
			}
			else
				me->RemoveFromWorld();

			me->SetLootRecipient(NULL);
		}

		void EnterCombat(Unit* who)
		{
			if(pInstance->GetData(TYPE_PHASE) > 9) return;
			me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_OOC_NOT_ATTACKABLE);

			DoScriptText(SAY_MALGANIS_AGGRO, me);
		}

		void KilledUnit(Unit* pVictim)
		{
			switch(rand()%7)
			{
			    case 0: DoScriptText(SAY_MALGANIS_SLAY01, me); break;
			    case 1: DoScriptText(SAY_MALGANIS_SLAY02, me); break;
			    case 2: DoScriptText(SAY_MALGANIS_SLAY03, me); break;
			    case 3: DoScriptText(SAY_MALGANIS_SLAY04, me); break;
			    case 4: DoScriptText(SAY_MALGANIS_SLAY05, me); break;
			    case 5: DoScriptText(SAY_MALGANIS_SLAY06, me); break;
			    case 6: DoScriptText(SAY_MALGANIS_SLAY07, me); break;
			}
			if (pVictim->GetGUID() == pInstance->GetData64(NPC_ARTHAS))
			{
				pInstance->SetData(TYPE_MALGANIS, FAIL);
				EnterEvadeMode();
				me->RemoveFromWorld();
				me->SetLootRecipient(NULL);
			}
		}

		void UpdateAI(const uint32 diff)
		{
			if(pInstance->GetData(TYPE_PHASE) > 9) return;

			if (!UpdateVictim())
				return;

			DoMeleeAttackIfReady();

			if (Swamp_Timer < diff)
			{
				if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 20.0f, true))
					DoCast(target, DUNGEON_MODE(SPELL_SWAMP_N, SPELL_SWAMP_H));

				Swamp_Timer = 7300;
			}
            else Swamp_Timer -= diff;

			if (MindBlast_Timer < diff)
			{
				if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 50.0f, true))
					DoCast(target, DUNGEON_MODE(SPELL_MIND_BLAST_N, SPELL_MIND_BLAST_H));

				MindBlast_Timer = 11300;
			}
            else MindBlast_Timer -= diff;

			if(HealthBelowPct(40.0f))
			{
				if(!Sleep)
				{
					Sleep = true;
					DoScriptText(SAY_MALGANIS_Sleep, me); 
				}

				if (Sleep_Timer < diff)
				{
					if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 45.0f, true))
						DoCast(target, DUNGEON_MODE(SPELL_SLEEP_N, SPELL_SLEEP_H));

                    DoScriptText(RAND(SAY_MALGANIS_SLEEP01, SAY_MALGANIS_SLEEP02), me);

					Sleep_Timer = 17300;
				}
                else Sleep_Timer -= diff;
			}

			if(HealthBelowPct(25.0f))
			{
				if(Vampire == false)
				{
					Vampire = true;
					DoScriptText(SAY_MALGANIS_15HP, me); 
					DoCast(me, SPELL_VAMPIRE);
				}

				if (Vampire_Timer < diff)
				{
					DoCast(me, SPELL_VAMPIRE);

					Vampire_Timer = 30000;
				}
                else Vampire_Timer -= diff;

			}

			if(HealthBelowPct(5.0f))
			{ 
				pInstance->SetData(TYPE_PHASE, 10);
				pInstance->SetData(TYPE_MALGANIS, DONE);
				EnterEvadeMode();
			}

		}

		void DamageTaken(Unit* /*pDoneBy*/, uint32 &uiDamage)
		{
			if (uiDamage > me->GetHealth())
			{
				uiDamage = 0;

				pInstance->SetData(TYPE_PHASE, 10);
				pInstance->SetData(TYPE_MALGANIS, DONE);
				EnterEvadeMode();
			}
		}
    };

};

void AddSC_boss_mal_ganis()
{
    new boss_mal_ganis();
}
