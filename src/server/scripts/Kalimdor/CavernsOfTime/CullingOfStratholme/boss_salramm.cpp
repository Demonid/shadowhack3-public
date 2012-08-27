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
SDName: Boss salramm
SDAuthor: Tartalo
SD%Complete: 80
SDComment: TODO: Intro
SDCategory:
Script Data End */

#include "ScriptPCH.h"
#include "culling_of_stratholme.h"

enum Yells
{
    SAY_SALRAMM_AGGRO       = -1594130,   
    SAY_SALRAMM_DEATH       = -1594131,  
    SAY_SALRAMM_SLAY01      = -1594132, 
    SAY_SALRAMM_SLAY02      = -1594133, 
    SAY_SALRAMM_SLAY03      = -1594134,
    SAY_SALRAMM_STEAL01     = -1594135,
    SAY_SALRAMM_STEAL02     = -1594136,
    SAY_SALRAMM_STEAL03     = -1594137,
    SAY_SUMMON01            = -1594138,
    SAY_SUMMON02            = -1594139,
    SAY_BOOM01              = -1594140,
    SAY_BOOM02              = -1594141,

    NPC_GNOUL               = 27733
};

enum SalrammSpells
{
    SPELL_SB_N              = 57725,
    SPELL_SB_H              = 58827,
    SPELL_FLESH             = 58845,
    SPELL_STEAL             = 52708,
    SPELL_GNOUL_BLOW        = 58825,
    SPELL_SUMMON_GNOUL      = 52451,
};

class boss_salramm : public CreatureScript
{
public:
    boss_salramm() : CreatureScript("boss_salramm") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_salrammAI (pCreature);
    }

    struct boss_salrammAI : public ScriptedAI
    {
        boss_salrammAI(Creature *c) : ScriptedAI(c)
        {
            pInstance = c->GetInstanceScript();
            Reset();
        }

        InstanceScript* pInstance;

        uint32 ShadowBoltTimer;
        uint32 FleshTimer;
        uint32 StealTimer;
        uint32 SummonTimer;

        void Reset() 
        {
            ShadowBoltTimer = 5000;
            FleshTimer = (urand(7000, 9000));
            StealTimer = (urand(9000, 17000));
            SummonTimer = (urand(12000, 17000));
            if(pInstance)
                pInstance->SetData64(NPC_SALRAMM, me->GetGUID());
        }

        void EnterCombat(Unit* /*who*/)
        {
            DoScriptText(SAY_SALRAMM_AGGRO, me);
        }

        void JustDied(Unit * /*killer*/)
        {
            DoScriptText(SAY_SALRAMM_DEATH, me);
            if(pInstance)
                pInstance->SetData(TYPE_ENCOUNTER, DONE);
        }

        void KilledUnit(Unit* /*pVictim*/)
        {
            DoScriptText(RAND(SAY_SALRAMM_SLAY01, SAY_SALRAMM_SLAY02, SAY_SALRAMM_SLAY03), me);
        }

        void SpellHitTarget(Unit *target, const SpellEntry *spell)
        {
            if(spell->Id == SPELL_GNOUL_BLOW)
                if(target->GetTypeId() != TYPEID_PLAYER && target->GetEntry() == NPC_GNOUL)
                    target->SetDisplayId(11686);
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (ShadowBoltTimer < diff)
            {
                DoCast(me->getVictim(), DUNGEON_MODE(SPELL_SB_N, SPELL_SB_H));

                ShadowBoltTimer = (urand(5000, 6000));
            }else ShadowBoltTimer -= diff;

            if (FleshTimer < diff)
            {
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 50.0f, true))
                    DoCast(target, SPELL_FLESH);

                FleshTimer = 7300;
            }else FleshTimer -= diff;

            if (StealTimer < diff)
            {
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 50.0f, true))
                    DoCast(target, SPELL_STEAL);

                DoScriptText(RAND(SAY_SALRAMM_STEAL01, SAY_SALRAMM_STEAL02, SAY_SALRAMM_STEAL03), me);

                StealTimer = (urand(8000, 11000));
            }else StealTimer -= diff;

            if (SummonTimer < diff)
            {
                DoScriptText(RAND(SAY_SUMMON01, SAY_SUMMON02), me);

                me->InterruptNonMeleeSpells(false);
                DoCast(me, SPELL_SUMMON_GNOUL);

                SummonTimer = (urand(12000, 17000));
            }else SummonTimer -= diff;

            DoMeleeAttackIfReady();
        }
    };

};

void AddSC_boss_salramm()
{
    new boss_salramm();
}
