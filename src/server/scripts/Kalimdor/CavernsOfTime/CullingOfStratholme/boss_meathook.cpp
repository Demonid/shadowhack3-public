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
SDName: Boss meathook
SDAuthor: Tartalo
SD%Complete: 100
SDComment: It may need timer adjustment
SDCategory:
Script Data End */

#include "ScriptPCH.h"
#include "culling_of_stratholme.h"

enum MeathookSpells
{
    SPELL_CHAIN_N                 = 52696,
    SPELL_CHAIN_H                 = 58823,
    SPELL_EXPLODED_N              = 52666,
    SPELL_EXPLODED_H              = 58824,
    SPELL_FRENZY                  = 58841,
};

enum MeathookTexts
{
    SAY_MEATHOOK_AGGRO       = -1594111,   
    SAY_MEATHOOK_DEATH       = -1594112,  
    SAY_MEATHOOK_SLAY01      = -1594113, 
    SAY_MEATHOOK_SLAY02      = -1594114, 
    SAY_MEATHOOK_SLAY03      = -1594115,
};

class boss_meathook : public CreatureScript
{
public:
    boss_meathook() : CreatureScript("boss_meathook") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_meathookAI (pCreature);
    }

    struct boss_meathookAI : public ScriptedAI
    {
        boss_meathookAI(Creature *c) : ScriptedAI(c)
        {
            pInstance = c->GetInstanceScript();
            Reset();
        }

        uint32 Chain_Timer;
        uint32 Exploded_Timer;
        uint32 Frenzy_Timer;

        InstanceScript* pInstance;

        void Reset() 
        {
            Chain_Timer = 6300;
            Exploded_Timer = 5000;
            Frenzy_Timer = 22300;
        }

        void EnterCombat(Unit* who)
        {
            DoScriptText(SAY_MEATHOOK_AGGRO, me);
        }

        void JustDied(Unit *killer)
        {
            DoScriptText(SAY_MEATHOOK_DEATH, me);
            if(pInstance)
                pInstance->SetData(TYPE_PHASE, 3);
        }

        void KilledUnit(Unit* pVictim)
        {
            DoScriptText(RAND(SAY_MEATHOOK_SLAY01, SAY_MEATHOOK_SLAY02, SAY_MEATHOOK_SLAY03), me);
        }

        void UpdateAI(const uint32 diff)
        {

            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();

            if (Chain_Timer < diff)
            {
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 50.0f, true))
                    DoCast(target, DUNGEON_MODE(SPELL_CHAIN_N, SPELL_CHAIN_H));

                Chain_Timer = 6300;
            }else Chain_Timer -= diff;

            if (Exploded_Timer < diff)
            {
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 10.0f, true))
                    DoCast(target, DUNGEON_MODE(SPELL_EXPLODED_N, SPELL_EXPLODED_H));

                Exploded_Timer = 5000;
            }else Exploded_Timer -= diff;

            if (Frenzy_Timer < diff)
            {       
                me->InterruptNonMeleeSpells(false);
                DoCast(me,SPELL_FRENZY);

                Frenzy_Timer = 23300;
            }else Frenzy_Timer -= diff;
        }
    };

};

void AddSC_boss_meathook()
{
    new boss_meathook();
}
