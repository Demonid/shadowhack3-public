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

#include "ScriptPCH.h"

/*####
## npc_valkyr_battle_maiden
####*/
#define SPELL_VALKYR_REVIVE 51918
#define VALK_WHISPER -1608999

class npc_valkyr_battle_maiden : public CreatureScript
{
public:
    npc_valkyr_battle_maiden() : CreatureScript("npc_valkyr_battle_maiden") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_valkyr_battle_maidenAI (pCreature);
    }

    struct npc_valkyr_battle_maidenAI : public PassiveAI
    {
        npc_valkyr_battle_maidenAI(Creature *c) : PassiveAI(c) {}

        uint32 FlyBackTimer;
        float x, y, z;
        uint32 phase;

        void Reset()
        {
            me->setActive(true);
            me->SetVisible(false);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            me->SetFlying(true);
            FlyBackTimer = 500;
            phase = 0;

            me->GetPosition(x, y, z);
            z += 4; x -= 3.5; y -= 5;
            me->GetMotionMaster()->Clear(false);
            me->GetMap()->CreatureRelocation(me, x, y, z, 0.0f);
        }

        void UpdateAI(const uint32 diff)
        {
            if (FlyBackTimer <= diff)
            {
                Player *plr = NULL;
                if (me->isSummon())
                    if (Unit *summoner = CAST_SUM(me)->GetSummoner())
                        if (summoner->GetTypeId() == TYPEID_PLAYER)
                            plr = CAST_PLR(summoner);

                if (!plr)
                    phase = 3;

                switch(phase)
                {
                    case 0:
                        me->RemoveUnitMovementFlag(MOVEMENTFLAG_WALKING);
                        me->HandleEmoteCommand(EMOTE_STATE_FLYGRABCLOSED);
                        FlyBackTimer = 500;
                        break;
                    case 1:
                        plr->GetClosePoint(x, y, z, me->GetObjectSize(), 0.0f, 0.0f, me);
                        z += 2.5; x -= 2; y -= 1.5;
                        me->GetMotionMaster()->MovePoint(0, x, y, z);
                        me->SetUInt64Value(UNIT_FIELD_TARGET, plr->GetGUID());
                        me->SetVisible(true);
                        FlyBackTimer = 4500;
                        break;
                    case 2:
                        if (!plr->isRessurectRequested())
                        {
                            me->HandleEmoteCommand(EMOTE_ONESHOT_CUSTOMSPELL01);
                            DoCast(plr, SPELL_VALKYR_REVIVE, true);
                            DoScriptText(VALK_WHISPER, me, plr);
                        }
                        FlyBackTimer = 5000;
                        break;
                    case 3:
                        me->SetVisible(false);
                        FlyBackTimer = 3000;
                        break;
                    case 4:
                        me->DisappearAndDie();
                        break;
                    default:
                        //Nothing To DO
                        break;
                }
                ++phase;
            } else FlyBackTimer-=diff;
        }
    };

};

class npc_scourge_sky_darkener : public CreatureScript
{
public:
    npc_scourge_sky_darkener() : CreatureScript("npc_scourge_sky_darkener") {}

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_scourge_sky_darkenerAI (pCreature);
    }

    struct npc_scourge_sky_darkenerAI : public ScriptedAI
    {
        npc_scourge_sky_darkenerAI(Creature* pCreature) : ScriptedAI(pCreature) { Reset(); }

        uint32 m_uiAttackTimer;

        void Reset()
        {
            m_uiAttackTimer=9000;
        }

        void UpdateAI(const uint32 diff)
        {
            if (m_uiAttackTimer <= diff)
            {
                me->CastSpell(me, 75, true);
                float rx = rand()% 420 + 1902;
                float ry = -(rand() % 177 + 5757);
                float ground_Z = me->GetMap()->GetHeight(rx, ry, me->GetPositionZ());
                me->SummonGameObject(190691, rx, ry, ground_Z, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 15);
                m_uiAttackTimer = urand(1, 2000) + 8000;
            }
            else m_uiAttackTimer -= diff;
        }
    };
};

enum eAcherusTeleportSpells
{
    SPELL_PORT_29580 = 54700,
    SPELL_PORT_29581 = 54724,
    SPELL_PORT_29588 = 54742,
    SPELL_PORT_29589 = 54745,
};

class npc_acherus_teleport : public CreatureScript
{
public:
    npc_acherus_teleport() : CreatureScript("npc_acherus_teleport") {}

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_acherus_teleportAI (pCreature);
    }

    struct npc_acherus_teleportAI : public ScriptedAI
    {
        npc_acherus_teleportAI(Creature* pCreature) : ScriptedAI(pCreature) { Reset(); }

        uint32 m_uiAttackTimer;

        void Reset()
        {
            m_uiAttackTimer=3000;
        }

        void UpdateAI(const uint32 diff)
        {
            if (m_uiAttackTimer <= diff)
            {
                switch (me->GetEntry())
                {
                    case 29580:
                        me->CastSpell(me, SPELL_PORT_29580, false);
                        break;
                    case 29581:
                        me->CastSpell(me, SPELL_PORT_29581, false);
                        break;
                    case 29588:
                        me->CastSpell(me, SPELL_PORT_29588, false);
                        break;
                    case 29589:
                        me->CastSpell(me, SPELL_PORT_29589, false);
                        break;
                    default:
                        break;
                }
                m_uiAttackTimer=3000;
            }
            else m_uiAttackTimer -= diff;
        }
    };
};

void AddSC_the_scarlet_enclave()
{
    new npc_valkyr_battle_maiden();
    new npc_scourge_sky_darkener();
    new npc_acherus_teleport();
}
