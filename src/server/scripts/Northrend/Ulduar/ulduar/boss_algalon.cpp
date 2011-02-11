/*
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

/* ScriptData
SDName: Algalon
Author:
SD%Complete: 33%
SDComment: TODO: Boss Phases 2 (melee) and 3 (final speech); trash scripts and whole encounter mechanic; check if all spells supported by core
EndScriptData */

#include "ScriptPCH.h"
#include "ulduar.h"

#define GAMEOBJECT_GIVE_OF_THE_OBSERVER 194821

enum SpellsAlgalon
{
    SPELL_ASCEND                    = 64487,    // can not be shielded of by anything (bubble etc.) - except maybe phaseout
    SPELL_BERSERK                   = 47008,    // check also 60670, 65126, 62535, 62555
    SPELL_BIG_BANG                  = 64443,    // may be bubbled out
    H_SPELL_BIG_BANG                = 64584,
    SPELL_COSMIC_SMASH_VISUAL_STATE = 62300,
    SPELL_COSMIC_SMASH_SPELLTRIGGER = 62301,    // triggers 62293 and 62295 from SRC_NEARBY_ENTRY with entry supplied elsewhere; casted by boss
    //SPELL_COSMIC_SMASH_SUMMON_AST1  = 62293,
    //SPELL_COSMIC_SMASH_SUMMON_AST2  = 62295,
    SPELL_COSMIC_SMASH_MISSILE      = 62304,    // triggers 62311 upon DST_NEARBY_ENTRY with entry supplied elsewhere; RAID25=64597
//    SPELL_COSMIC_SMASH_DAMAGE       = 62311,    // triggered by 62304; RAID25=64596
    H_SPELL_COSMIC_SMASH_SPELLTRIGGER = 64598,
// to check: 64421, 64428, 64434, 64435
    SPELL_PHASE_PUNCH_DAMAGE        = 64412,
//    SPELL_PHASE_PUNCH_PHASEOUT      = 64417,    // target outs-of-phase when got 5x 64412, 10 sec; to trigger by core!
    SPELL_QUANTUM_STRIKE            = 64395,
    H_SPELL_QUANTUM_STRIKE          = 64592,
    SPELL_TRIGGER_3_ADDS            = 62266,    // to wake Living Constellations? unit entry to be supplied elsewhere
    SPELL_BLACK_HOLE_TARGET_VISUAL  = 62348,    // ? visual aura
    SPELL_ALGALON_EVENT_BEAM        = 64367,    // ? on aggro
    SPELL_ALGALON_EVENT_BEAM_CLIMAX = 64580,    // ???
//    SPELL_REMOVE_PLAYER_FROM_PHASE  = 64445,    // ? triggered by Big Bang. Aura dispels 62168?
};
enum SpellsOthers
{
    SPELL_BLACK_HOLE_EXPLOSION      = 64122,    // Collapsing Star on death; RAID25=65108
    SPELL_SUMMON_BLACK_HOLE         = 62189,    // Collapsing Star on death
// to check: 62003, 64135
    SPELL_BLACK_HOLE_TRIGGER        = 62185,    // Black Hole on self (in creature_addon?)
//    SPELL_BLACK_HOLE_PHASEOUT       = 62168,    // Black Hole protects near players 10 sec; IS TRIGGERED by 62185!
    SPELL_BLACK_HOLE_DAMAGE         = 62169,    // Black Hole itself damages them 10 sec
    SPELL_BLACK_HOLE_CREDIT         = 65312,    // criteria of timed ach:3002,3003
    SPELL_DESPAWN_BLACK_HOLE        = 64391,    // ? when collided with Living Constellation or hit by SPELL_BIG_BANG
    SPELL_ARCANE_BARAGE             = 64599,    // Living Constellation attack
    H_SPELL_ARCANE_BARAGE           = 64607,
    //SPELL_CONSTELLATION_PHASE_TRIGGER = 65508,    // ???
    //SPELL_CONSTELLATION_PHASE_EFFECT  = 65509,
    SPELL_SUMMON_UNLEASHED_DARK_MATTER = 64450,    // summon 34097 (Phase 2)
};

enum Creatures
{
    CREATURE_COLLAPSING_STAR        = 32955,    // 176.4k HP on 25; 88.2k HP on 10.
    CREATURE_BLACK_HOLE             = 32953,
    CREATURE_LIVING_CONSTELLATION   = 33052,
    CREATURE_DARK_MATTER            = 33089,
    CREATURE_UNLEASHED_DARK_MATTER  = 34097,
    CREATURE_ALGALON_STALKER_ASTEROID_TARGET01 = 33104,
    CREATURE_ALGALON_STALKER_ASTEROID_TARGET02 = 33105,
};

enum Yells
{
    SAY_AGGRO                                   = -1603000, //DB: old were at -1620000
    SAY_SLAY_1                                  = -1603001,
    SAY_SLAY_2                                  = -1603002,
    SAY_ENGADED_FOR_FIRST_TIME                  = -1603003,
    SAY_PHASE_2                                 = -1603004,
    SAY_SUMMON_COLLAPSING_STAR                  = -1603005,
    SAY_DEATH_1                                 = -1603006,
    SAY_DEATH_2                                 = -1603007,
    SAY_DEATH_3                                 = -1603008,
    SAY_DEATH_4                                 = -1603009,
    SAY_DEATH_5                                 = -1603010,
    SAY_BERSERK                                 = -1603011,
    SAY_BIG_BANG_1                              = -1603012,
    SAY_BIG_BANG_2                              = -1603013,
    SAY_TIMER_1                                 = -1603014,
    SAY_TIMER_2                                 = -1603015,
    SAY_TIMER_3                                 = -1603016,
    SAY_SUMMON_1                                = -1603017,
    SAY_SUMMON_2                                = -1603018,
    SAY_SUMMON_3                                = -1603019,
};

enum Events
{
    EVENT_QUANTUM_STRIKE    = 1,
    EVENT_ASCEND,
    EVENT_COLLAPSING_STAR,
    EVENT_BIG_BANG,
    EVENT_COSMIC_SMASH,
    EVENT_PHASE_PUNCH,
    EVENT_BERSERK,
};

class boss_algalon : public CreatureScript
{
public:
    boss_algalon() : CreatureScript("boss_algalon") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_algalonAI(pCreature);
    }

    struct boss_algalonAI : public BossAI
    {
        boss_algalonAI(Creature *c) : BossAI(c, BOSS_ALGALON)
        {
            Summon = false; // not in reset. intro speech done only once.
        }

        uint32 Phase;
        uint32 uiPhase_timer;
        uint32 uiStep;

        uint64 BlackHoleGUID;

        bool Enrage;
        bool Summon;

        void EnterCombat(Unit* who)
        {
            if (Summon)
            {
                _EnterCombat();
                DoScriptText(SAY_AGGRO, me);
                me->InterruptSpell(CURRENT_CHANNELED_SPELL);
                events.ScheduleEvent(EVENT_QUANTUM_STRIKE, urand(4*IN_MILLISECONDS, 14*IN_MILLISECONDS));
                events.ScheduleEvent(EVENT_PHASE_PUNCH, 9*IN_MILLISECONDS);
                events.ScheduleEvent(EVENT_COLLAPSING_STAR, urand(15*IN_MILLISECONDS, 20*IN_MILLISECONDS));
                events.ScheduleEvent(EVENT_COSMIC_SMASH, urand(30*IN_MILLISECONDS, 60*IN_MILLISECONDS));
                events.ScheduleEvent(EVENT_BIG_BANG, 90*IN_MILLISECONDS);
                events.ScheduleEvent(EVENT_BERSERK, 360*IN_MILLISECONDS);
                events.ScheduleEvent(EVENT_ASCEND, 480*IN_MILLISECONDS);
            }
            else
            {
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                me->SetReactState(REACT_PASSIVE);
                uiStep = 1;
                instance->SetBossState(BOSS_ALGALON, IN_PROGRESS);
            }
        }

        void KilledUnit(Unit * /*victim*/)
        {
            DoScriptText(RAND(SAY_SLAY_1,SAY_SLAY_2), me);
        }

        void Reset()
        {
            _Reset();
            Phase = 1;

            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

            BlackHoleGUID = 0;

            uiPhase_timer = 0;
            Enrage = false;
        }

        void JumpToNextStep(uint32 uiTimer)
        {
            uiPhase_timer = uiTimer;
            ++uiStep;
        }

        void DespawnCollapsingStar()
        {
            summons.DespawnAll();
        }

        void JustSummoned(Creature* pSummoned)
        {
            if (pSummoned->GetEntry() == CREATURE_COLLAPSING_STAR)
            {
                Unit* pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0);
                if (me->getVictim() && pSummoned->AI())
                    pSummoned->AI()->AttackStart(pTarget ? pTarget : me->getVictim());
                summons.Summon(pSummoned);
            }
        }

        void SummonCollapsingStar(Unit* target)
        {
            DoScriptText(SAY_SUMMON_COLLAPSING_STAR, me);
            me->SummonCreature(CREATURE_COLLAPSING_STAR,target->GetPositionX()+15.0f,target->GetPositionY()+15.0f,target->GetPositionZ(),0, TEMPSUMMON_TIMED_DESPAWN, 100000);
            // DoScriptText(SAY_BLACK_HOLE, me);    //Q: define SAY_BLACK_HOLE in DB then uncomment
            me->SummonCreature(CREATURE_BLACK_HOLE,target->GetPositionX()+15.0f,target->GetPositionY()+15.0f,target->GetPositionZ(),0, TEMPSUMMON_TIMED_DESPAWN, 27000);
        }

        void UpdateAI(const uint32 diff)
        {
            //Return since we have no target
            if (!UpdateVictim())
                return;

            if (Phase == 1 && HealthBelowPct(20)) EnterPhaseTwo();

            if (HealthBelowPct(2))
            {
                me->SummonGameObject(GAMEOBJECT_GIVE_OF_THE_OBSERVER, 1634.258667f, -295.101166f, 417.321381f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0);

                // ToDo: all textes sequentially with intervals, the speech Algalon gives when beaten down to 2% and before spawning the loot chest
                // Algalon itself becomes passive and unattackable but not dead
                DoScriptText(SAY_DEATH_1, me);
                DoScriptText(SAY_DEATH_2, me);
                DoScriptText(SAY_DEATH_3, me);
                DoScriptText(SAY_DEATH_4, me);
                DoScriptText(SAY_DEATH_5, me);

                me->DisappearAndDie();

                instance->SetBossState(BOSS_ALGALON, DONE);

                return;
            }

            if (Phase == 1)
            {
                if (!Summon)
                {
                    if (uiPhase_timer <= diff)
                    {
                        switch(uiStep)
                        {
                            case 1:
                                DoScriptText(SAY_SUMMON_1, me);
                                JumpToNextStep(3000);
                                break;
                            case 2:
                                DoScriptText(SAY_SUMMON_2, me);
                                JumpToNextStep(3000);
                                break;
                            case 3:
                                DoScriptText(SAY_SUMMON_3, me);
                                JumpToNextStep(3000);
                                break;
                            case 4:
                                DoScriptText(SAY_ENGADED_FOR_FIRST_TIME, me);
                                JumpToNextStep(3000);
                                break;
                            case 5:
                                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                                me->SetReactState(REACT_AGGRESSIVE);
                                Summon = true;
                                break;
                        }
                    } else uiPhase_timer -= diff;

                    return;
                }

                events.Update(diff);
                if (me->HasUnitState(UNIT_STAT_CASTING)) return;
                while(uint32 eventId = events.ExecuteEvent())
                {
                    switch(eventId)
                    {
                    case EVENT_QUANTUM_STRIKE:
                        DoCastVictim(RAID_MODE(SPELL_QUANTUM_STRIKE,H_SPELL_QUANTUM_STRIKE), true);
                        events.ScheduleEvent(EVENT_QUANTUM_STRIKE, urand(4*IN_MILLISECONDS,14*IN_MILLISECONDS));
                        break;
                    case EVENT_PHASE_PUNCH:
                        DoCastVictim(SPELL_PHASE_PUNCH_DAMAGE, true);
                        events.ScheduleEvent(EVENT_PHASE_PUNCH, 9*IN_MILLISECONDS); // maybe 8 in the Phase 2
                        break;
                    case EVENT_COSMIC_SMASH:
                        DoCast(SelectUnit(SELECT_TARGET_RANDOM, 0), RAID_MODE(SPELL_COSMIC_SMASH_SPELLTRIGGER,H_SPELL_COSMIC_SMASH_SPELLTRIGGER), true);
                        events.ScheduleEvent(EVENT_COSMIC_SMASH, urand(30*IN_MILLISECONDS, 60*IN_MILLISECONDS));
                        break;
                    case EVENT_COLLAPSING_STAR:
                        DoScriptText(SAY_SUMMON_COLLAPSING_STAR, me);
                        //ToDo: summon 3 Collapsing Stars OR 3 Living Constellations
                        events.ScheduleEvent(EVENT_COLLAPSING_STAR, urand(15*IN_MILLISECONDS, 20*IN_MILLISECONDS));
                        break;
                    case EVENT_BIG_BANG:
                        DoScriptText(RAND(SAY_BIG_BANG_1,SAY_BIG_BANG_2), me);
                        DoCastVictim(RAID_MODE(SPELL_BIG_BANG,H_SPELL_BIG_BANG), true);
                        events.ScheduleEvent(EVENT_BIG_BANG, 90*IN_MILLISECONDS);
                        break;
                    case EVENT_BERSERK:
                        DoScriptText(SAY_BERSERK, me);
                        DoCast(SPELL_BERSERK);
                        events.ScheduleEvent(EVENT_BERSERK, 30*60*IN_MILLISECONDS);
                        break;
                    case EVENT_ASCEND:
                        DoCastVictim(SPELL_ASCEND,true);
                        events.ScheduleEvent(EVENT_ASCEND, 480*IN_MILLISECONDS);
                        break;
                    }
                }

                EnterEvadeIfOutOfCombatArea(diff);
            }

            if (Phase == 2)
            {
                if (Enrage)
                {
                    //if (Ascend_Timer <= diff)
                    //{
                    //    DoCast(me, SPELL_ASCEND);
                    //    DoScriptText(SAY_BERSERK, me);
                    //    Ascend_Timer = urand(360000,365000);
                    //    Enrage = false;
                    //} else Ascend_Timer -= diff;
                }
            }

            DoMeleeAttackIfReady();
        }
        
        void EnterPhaseTwo()
        {
            //ToDo: summon 4 Black Holes with long lifetime
            events.CancelEvent(EVENT_COLLAPSING_STAR);
            Phase = 2;
            DoScriptText(SAY_PHASE_2, me);
        }
    };

};

// Collapsing Star
// Spawn in three. Loses 1% health every 1 sec. When dies (no matter of what), SPELL_BLACK_HOLE_EXPLOSION and spawns CREATURE_BLACK_HOLE
// All raid members are damaged with explosion.
// Does not attack at all?
class mob_collapsing_star : public CreatureScript
{
public:
    mob_collapsing_star() : CreatureScript("mob_collapsing_star") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new mob_collapsing_starAI(pCreature);
    }

    struct mob_collapsing_starAI : public ScriptedAI
    {
        mob_collapsing_starAI(Creature *pCreature) : ScriptedAI(pCreature)
        {
            pInstance = pCreature->GetInstanceScript();
            HealthLeech = pCreature->CountPctFromMaxHealth(3);
            LifeTimer = 3000;
        }

        InstanceScript* pInstance;

        uint32 LifeTimer;   // this may be set higher like 4-6k, then HealthLeech is to be corrected (in this case to 4-6%)
        uint32 HealthLeech;

        void UpdateAI(const uint32 diff)
        {
            if (LifeTimer <= diff)
            {
                me->DealDamage(me, HealthLeech); // ModifyHealth(HealthLeech);
                LifeTimer = 3000;
            }
            else LifeTimer -= diff;
        }

        void DamageTaken(Unit* who, uint32 &dmg)    //Q: can this be moved to JustDied()?
        {
            if (dmg < me->GetHealth()) return;
            dmg=0;
            DoCast(SPELL_BLACK_HOLE_EXPLOSION);
            if (Creature* bh = DoSummon(CREATURE_BLACK_HOLE, me, 0.0f, 180*IN_MILLISECONDS, TEMPSUMMON_TIMED_DESPAWN))    //Q: check BH life time
            {
                // any notifies for Black Hole if needed
                // should it be added to Algalon summon list?
            }
            me->DespawnOrUnsummon();    // DisappearAndDie() ?
        }
    };

};

// Living Constellation
// Living Constellations spawn in threes, and wander around, following normal threat table.
// They attack with Arcane damage, which although not negligible, can be healed through.
// If a Living Constellation "walks" into a Black Hole spawned by a Collapsing Star, both despawn.

// Black Hole
// Collapsing Stars spawn Black Holes on the location where they died.
// While inside, raid members will take ~2,000 arcane damage every 1 second and will be attacked by Dark Matters.
// If the entire raid enters a Black Hole, Algalon will go Berserk.

// Dark Matter
// 1st phase: While inside of a Black Hole, raid members will take ~2,000 arcane damage every 1 second
/// and will be attacked by Dark Matters. Try not to enter the Black Holes too early (but certainly not too late!),
//  and avoid the Dark Matters. (So for 1st Boss phase, these are in PHASE=16 to attack players under SPELL_BLACK_HOLE_PHASEOUT).
// 2nd phase: Four Black Holes will appear and they will periodically spawn Dark Matters. (So PHASE=0 now.)

void AddSC_boss_algalon()
{
    new boss_algalon();
    new mob_collapsing_star();
}
