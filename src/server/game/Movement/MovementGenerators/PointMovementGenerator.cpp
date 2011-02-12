/*
 * Copyright (C) 2010-2011 Izb00shka <http://izbooshka.net/>
 * Copyright (C) 2008-2011 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
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

#include "PointMovementGenerator.h"
#include "Errors.h"
#include "Creature.h"
#include "CreatureAI.h"
#include "DestinationHolderImp.h"
#include "TemporarySummon.h"
#include "World.h"
#include "Spell.h"

//----- Point Movement Generator
template<class T>
void PointMovementGenerator<T>::Initialize(T &unit)
{
    if (!unit.IsStopped())
        unit.StopMoving();

    Traveller<T> traveller(unit);
    i_destinationHolder.SetDestination(traveller, i_x, i_y, i_z, !m_usePathfinding);

    if(m_usePathfinding)
    {
        PathInfo path(&unit, i_x, i_y, i_z, m_straightPath);
        PointPath pointPath = path.getFullPath();

        float speed = traveller.Speed() * 0.001f; // in ms
        uint32 traveltime = uint32(pointPath.GetTotalLength() / speed);
        unit.SendMonsterMoveByPath(pointPath, 1, pointPath.size(), traveltime);
    }

}


template<class T>
bool PointMovementGenerator<T>::Update(T &unit, const uint32 &diff)
{
    if (!&unit)
        return false;

    if (unit.HasUnitState(UNIT_STAT_ROOT | UNIT_STAT_STUNNED))
    {
        if (unit.HasUnitState(UNIT_STAT_CHARGING))
            return false;
        else
            return true;
    }

    Traveller<T> traveller(unit);

    i_destinationHolder.UpdateTraveller(traveller, diff, false);

    if (i_destinationHolder.HasArrived())
    {
        unit.ClearUnitState(UNIT_STAT_MOVE);
        arrived = true;
        return false;
    }

    return true;
}

template<class T>
void PointMovementGenerator<T>:: Finalize(T &unit)
{
    if (unit.HasUnitState(UNIT_STAT_CHARGING))
    {
        unit.ClearUnitState(UNIT_STAT_CHARGING | UNIT_STAT_JUMPING);

        if (m_target)
        {
            switch (m_chargeSpell)
            {
                case 61490:
                case 30151:
                case 61685:
                case 100:
                case 6178:
                case 11578:
                {
                    SpellEntry const *spellInfo = sSpellStore.LookupEntry(m_chargeSpell);
                    if (!spellInfo)
                    {
                        sLog->outError("EffectCharge: unknown spell %u", m_chargeSpell);
                        break;
                    }

                    for (uint8 j = 0; j < MAX_SPELL_EFFECTS; ++j)
                    {
                        if (spellInfo->Effect[j] != SPELL_EFFECT_TRIGGER_SPELL)
                            continue;

                        uint32 triggered_spell_id = spellInfo->EffectTriggerSpell[j];

                        SpellEntry const *trigger_spellInfo = sSpellStore.LookupEntry(triggered_spell_id);
                        if (!trigger_spellInfo)
                        {
                            sLog->outError("EffectTriggerSpell of spell %u: triggering unknown spell id %i", spellInfo->Id, triggered_spell_id);
                            continue;
                        }

                        if (unit.GetTypeId() == TYPEID_PLAYER && spellInfo->CategoryRecoveryTime && trigger_spellInfo->CategoryRecoveryTime
                            && spellInfo->Category == trigger_spellInfo->Category)
                            unit.ToPlayer()->RemoveSpellCooldown(trigger_spellInfo->Id);

                        if (unit.IsWithinMeleeRange(m_target))
                            unit.CastSpell(m_target, trigger_spellInfo, true, 0, 0, 0);
                    }
                    break;                
                }
                default: break;
            }
        }
    }
    if (arrived) // without this crash!
        MovementInform(unit);
}

template<class T>
void PointMovementGenerator<T>::MovementInform(T & /*unit*/)
{
}

template <> void PointMovementGenerator<Creature>::MovementInform(Creature &unit)
{
    if (id == EVENT_FALL_GROUND)
    {
        unit.setDeathState(JUST_DIED);
        unit.SetFlying(true);
    }
    unit.AI()->MovementInform(POINT_MOTION_TYPE, id);
}

template void PointMovementGenerator<Player>::Initialize(Player&);
template bool PointMovementGenerator<Player>::Update(Player &, const uint32 &diff);
template void PointMovementGenerator<Player>::MovementInform(Player&);
template void PointMovementGenerator<Player>::Finalize(Player&);

template void PointMovementGenerator<Creature>::Initialize(Creature&);
template bool PointMovementGenerator<Creature>::Update(Creature&, const uint32 &diff);
template void PointMovementGenerator<Creature>::Finalize(Creature&);

void AssistanceMovementGenerator::Finalize(Unit &unit)
{
    unit.ToCreature()->SetNoCallAssistance(false);
    unit.ToCreature()->CallAssistance();
    if (unit.isAlive())
        unit.GetMotionMaster()->MoveSeekAssistanceDistract(sWorld->getIntConfig(CONFIG_CREATURE_FAMILY_ASSISTANCE_DELAY));
}

