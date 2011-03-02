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

enum Spells
{
	SPELL_COURSE      = 60588,
	SPELL_STRIKE      = 60590
};


class boss_infinite_corruptor : public CreatureScript
{
public:
    boss_infinite_corruptor() : CreatureScript("boss_infinite_corruptor") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_infinite_corruptorAI(pCreature);
    }

    struct boss_infinite_corruptorAI : public ScriptedAI
    {
        boss_infinite_corruptorAI(Creature *c) : ScriptedAI(c)
        {
            m_pInstance = c->GetInstanceScript();
            Reset();
        }

        InstanceScript* m_pInstance;

		uint32 m_uiStrikeTimer;
		uint32 m_uiCourseTimer;

		void Reset() 
		{
			m_uiCourseTimer = 7000;
			m_uiStrikeTimer = 5000;
		}

		void EnterCombat(Unit* who)
		{
			if(m_pInstance)
				m_pInstance->SetData(TYPE_BONUS, SPECIAL);
		}

		void JustDied(Unit *killer)
		{
			if(m_pInstance)
				m_pInstance->SetData(TYPE_BONUS, DONE);
		}

		void EnterEvadeMode()
		{
			if(!m_pInstance) return;

			me->RemoveAllAuras();
			me->DeleteThreatList();
			me->CombatStop(true);
			me->LoadCreaturesAddon();
			if(m_pInstance)
				m_pInstance->SetData(TYPE_BONUS, IN_PROGRESS);

			if(me->isAlive())
				me->GetMotionMaster()->MoveTargetedHome();  //Q: should we avoid it? simply ScriptedAI::EnterEvadeMode

			me->SetLootRecipient(NULL);

			Reset();
		}

		void UpdateAI(const uint32 diff)
		{
			if (!UpdateVictim())
				return;

			DoMeleeAttackIfReady();

			if (m_uiCourseTimer < diff)
			{
				if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 60.0f, true))
					DoCast(target, SPELL_COURSE);

				m_uiCourseTimer = 17000;
			}else m_uiCourseTimer -= diff;

			if (m_uiStrikeTimer < diff)
			{
				DoCastVictim(SPELL_STRIKE);

				m_uiStrikeTimer = 5000;
			}else m_uiStrikeTimer -= diff;
		}
    };

};


void AddSC_boss_infinite_corruptor()
{
    new boss_infinite_corruptor();
}
