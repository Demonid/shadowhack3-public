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
SDName: Boss epoch
SDAuthor: Tartalo
SD%Complete: 80
SDComment: TODO: Intro, consecutive attacks to a random target durin time wrap, adjust timers
SDCategory:
Script Data End */

#include "ScriptPCH.h"
#include "culling_of_stratholme.h"

enum Spells
{
    SPELL_COURSE           = 52772,
    SPELL_TIME_STOP        = 58848,
    SPELL_TIME_WARP        = 52766,
    SPELL_SPIKE_N          = 52771,
    SPELL_SPIKE_H          = 58830,  
};

enum Texts
{
    SAY_EPOCH_DEATH        = -1594119,  
    SAY_EPOCH_SLAY01       = -1594120, 
    SAY_EPOCH_SLAY02       = -1594121, 
    SAY_EPOCH_SLAY03       = -1594122,
    SAY_EPOCH_WARP01       = -1594123, 
    SAY_EPOCH_WARP02       = -1594124, 
    SAY_EPOCH_WARP03       = -1594125
};


class boss_epoch : public CreatureScript
{
public:
    boss_epoch() : CreatureScript("boss_epoch") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_epochAI (pCreature);
    }

    struct boss_epochAI : public ScriptedAI
    {
        boss_epochAI(Creature *c) : ScriptedAI(c)
        {
            pInstance = c->GetInstanceScript();
        }

        uint32 Spike_Timer;
        uint32 Warp_Timer;
        uint32 Stop_Timer;
        uint32 Course_Timer;
        uint64 m_uiArthasGUID;

        InstanceScript* pInstance;

        void Reset()
        {
            Course_Timer = 9300;
            Stop_Timer = 21300;
            Warp_Timer = 25300;
            Spike_Timer = 5300;
        }

        void JustDied(Unit * /*killer*/)
        {
            DoScriptText(SAY_EPOCH_DEATH, me);
        }

        void KilledUnit(Unit* /*pVictim*/)
        {
            switch(rand()%3)
            {
            case 0: DoScriptText(SAY_EPOCH_SLAY01, me); break;
            case 1: DoScriptText(SAY_EPOCH_SLAY02, me); break;
            case 2: DoScriptText(SAY_EPOCH_SLAY03, me); break;
            }
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();

            if (Course_Timer < diff)
            {
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 50, true))
                    DoCast(target, SPELL_COURSE);

                Course_Timer = 9300;
            }else Course_Timer -= diff;

            if (Spike_Timer < diff)
            {

                DoCastVictim(DUNGEON_MODE(SPELL_SPIKE_N, SPELL_SPIKE_H));

                Spike_Timer = 5300;
            }else Spike_Timer -= diff;

            if (Stop_Timer < diff)
            {
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                    DoCast(target, SPELL_TIME_STOP);

                Stop_Timer = 21300;
            }else Stop_Timer -= diff;

            if (Warp_Timer < diff)
            {
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                    DoCast(target, SPELL_TIME_WARP);

                switch(rand()%3)
                {
                case 0: DoScriptText(SAY_EPOCH_WARP01, me); break;
                case 1: DoScriptText(SAY_EPOCH_WARP02, me); break;
                case 2: DoScriptText(SAY_EPOCH_WARP03, me); break;
                }

                Warp_Timer = 25300;
            }else Warp_Timer -= diff;

        }
    };

};

void AddSC_boss_epoch()
{
    new boss_epoch();
}
