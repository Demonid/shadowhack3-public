/*
 * Copyright (C) 2010-2011 Izb00shka <http://izbooshka.net/>
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

/*###
## npc_cs_gnoul
###*/

enum
{
	SPELL_FLESH        = 52352
};
class npc_cs_gnoul : public CreatureScript
{
public:
    npc_cs_gnoul() : CreatureScript("npc_cs_gnoul") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_cs_gnoulAI(pCreature);
    }

    struct npc_cs_gnoulAI : public ScriptedAI
    {
       npc_cs_gnoulAI(Creature *pCreature) : ScriptedAI(pCreature)
       {
           m_pInstance = pCreature->GetInstanceScript();
           Reset();
       }

       InstanceScript* m_pInstance;

       uint32 m_uiFleshTimer;

       uint32 WaypointId;
       uint32 MoveTimer;

       void Reset() 
       { 
         me->RemoveUnitMovementFlag(MOVEMENTFLAG_WALKING);
         MoveTimer = (urand(100, 5000));
         m_uiFleshTimer = (urand(3000, 10000));
         WaypointId = 1;
       }

       void MoveToPoint(float X, float Y, float Z)
       {
           me->GetMotionMaster()->MovementExpired(false);
           me->GetMotionMaster()->MovePoint(0, X, Y, Z);
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

            if (IsCombatMovementAllowed())
                me->GetMotionMaster()->MoveChase(pWho);
          }
       }

       void EnterEvadeMode()
       {
          me->RemoveAllAuras();
          me->DeleteThreatList();
          me->CombatStop(true);
          me->LoadCreaturesAddon();
          m_uiFleshTimer = (urand(3000, 10000));

          me->SetLootRecipient(NULL);
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

       void JumpNextStep(uint32 Time)
       {
         MoveTimer = Time;
         WaypointId++;
       }

       void UpdateAI(const uint32 uiDiff)
       {
            if (!UpdateVictim())
            {
              if(MoveTimer < uiDiff)
              {   
                 if(m_pInstance->GetData(TYPE_WING) == RIGHT)
                 {
                    switch(WaypointId)
                    {
                      case 1:
                         MoveToPoint(2356.659f, 1185.501f, 130.636f);
                         JumpNextStep(10000);
                         break; 
                      case 2:
                         MoveToPoint(2301.735f, 1179.265f, 136.944f);
                         JumpNextStep(8000);
                         break;  
                      case 3:
                         MoveToPoint(2234.787f, 1180.638f, 136.344f);
                         JumpNextStep(9000);
                         break; 
                      case 4:
                         MoveToPoint(2178.313f, 1244.350f, 136.107f);
                         JumpNextStep(12000);
                         break; 
                      case 5:
                         MoveToPoint(2163.553f, 1277.814f, 133.444f);
                         JumpNextStep(5000);
                         break; 
                      case 6:
                         MoveToPoint(2083.952f, 1287.716f, 141.146f);
                         JumpNextStep(5000);
                         break; 
                    }
                 }

                 if(m_pInstance->GetData(TYPE_WING) == LEFT)
                 {
                    switch(WaypointId)
                    {
                      case 1:
                         MoveToPoint(2188.318f, 1331.410f, 130.003f);
                         JumpNextStep(10000);
                         break; 
                      case 2:
                         MoveToPoint(2165.351f, 1279.156f, 133.388f);
                         JumpNextStep(8000);
                         break;  
                      case 3:
                         MoveToPoint(2083.952f, 1287.716f, 141.146f);
                         JumpNextStep(9000);
                         break; 
                    }
                 }

               } else MoveTimer -= uiDiff;
            }

            if (!UpdateVictim())
                return;

            if(m_uiFleshTimer < uiDiff)
            {       
               DoCast(me->getVictim(), SPELL_FLESH);
               m_uiFleshTimer = (urand(3000, 10000));
            }
            else m_uiFleshTimer -= uiDiff;

            DoMeleeAttackIfReady();

            return;
       }
    };

};

/*###
## npc_cs_necromancer
###*/

enum
{
  SPELL_SHADOW_BOLT        = 15472,
  SPELL_COURSE             = 20812,
  SPELL_DRAIN_MANA         = 58770
};
class npc_cs_necromancer : public CreatureScript
{
public:
    npc_cs_necromancer() : CreatureScript("npc_cs_necromancer") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_cs_necromancerAI(pCreature);
    }

    struct npc_cs_necromancerAI : public ScriptedAI
    {
       npc_cs_necromancerAI(Creature *pCreature) : ScriptedAI(pCreature)
       {
           m_pInstance = pCreature->GetInstanceScript();
           SetCombatMovement(false);
           Reset();
       }

       InstanceScript* m_pInstance;

       uint32 m_uiShadowBoltTimer;
       uint32 m_uiCourseTimer;

       uint32 WaypointId;
       uint32 MoveTimer;

       void Reset() 
       { 
         me->RemoveUnitMovementFlag(MOVEMENTFLAG_WALKING);
         MoveTimer = (urand(100, 5000));
         m_uiCourseTimer = (urand(7000, 17000));
         m_uiShadowBoltTimer = (urand(3000, 10000));
         WaypointId = 1;
       }

       void EnterCombat(Unit* pWho)
       {
         me->GetMotionMaster()->MovementExpired(false);
    	 me->StopMoving();
       }

       void MoveToPoint(float X, float Y, float Z)
       {
           me->GetMotionMaster()->MovementExpired(false);
           me->GetMotionMaster()->MovePoint(0, X, Y, Z);
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
          me->GetMotionMaster()->MovementExpired(false);
       }

       void EnterEvadeMode()
       {
          me->RemoveAllAuras();
          me->DeleteThreatList();
          me->CombatStop(true);
          me->LoadCreaturesAddon();
          m_uiShadowBoltTimer = (urand(3000, 10000));
          m_uiCourseTimer = (urand(7000, 17000));

          me->SetLootRecipient(NULL);
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

       void JumpNextStep(uint32 Time)
       {
         MoveTimer = Time;
         WaypointId++;
       }

       void UpdateAI(const uint32 uiDiff)
       {
            if (!UpdateVictim())
            {
              if(MoveTimer < uiDiff)
              {   
                 if(m_pInstance->GetData(TYPE_WING) == RIGHT)
                 {
                    switch(WaypointId)
                    {
                      case 1:
                         MoveToPoint(2356.659f, 1185.501f, 130.636f);
                         JumpNextStep(10000);
                         break; 
                      case 2:
                         MoveToPoint(2301.735f, 1179.265f, 136.944f);
                         JumpNextStep(8000);
                         break;  
                      case 3:
                         MoveToPoint(2234.787f, 1180.638f, 136.344f);
                         JumpNextStep(9000);
                         break; 
                      case 4:
                         MoveToPoint(2178.313f, 1244.350f, 136.107f);
                         JumpNextStep(12000);
                         break; 
                      case 5:
                         MoveToPoint(2163.553f, 1277.814f, 133.444f);
                         JumpNextStep(5000);
                         break; 
                      case 6:
                         MoveToPoint(2083.952f, 1287.716f, 141.146f);
                         JumpNextStep(5000);
                         break; 
                    }
                 }

                 if(m_pInstance->GetData(TYPE_WING) == LEFT)
                 {
                    switch(WaypointId)
                    {
                      case 1:
                         MoveToPoint(2188.318f, 1331.410f, 130.003f);
                         JumpNextStep(10000);
                         break; 
                      case 2:
                         MoveToPoint(2165.351f, 1279.156f, 133.388f);
                         JumpNextStep(8000);
                         break;  
                      case 3:
                         MoveToPoint(2083.952f, 1287.716f, 141.146f);
                         JumpNextStep(9000);
                         break; 
                    }
                 }

               } else MoveTimer -= uiDiff;
            }

            if (!UpdateVictim())
                return;

            if(m_uiShadowBoltTimer < uiDiff)
            {       
               DoCast(me->getVictim(), SPELL_SHADOW_BOLT);
               m_uiShadowBoltTimer  = (urand(3000, 5000));
            }
            else m_uiShadowBoltTimer -= uiDiff;

            if(m_uiCourseTimer < uiDiff)
            {    
               me->InterruptNonMeleeSpells(false);
               if(Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 30, true))   
                  DoCast(target, SPELL_COURSE);
               m_uiCourseTimer  = (urand(7000, 17000));
            }
            else m_uiCourseTimer -= uiDiff;

            DoMeleeAttackIfReady();

            return;
       }
    };

};

/*###
## npc_cs_field
###*/

enum
{
  SPELL_BLOW              = 52491,
  SPELL_SCARAB            = 52496
};
class npc_cs_field : public CreatureScript
{
public:
    npc_cs_field() : CreatureScript("npc_cs_field") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_cs_fieldAI(pCreature);
    }

    struct npc_cs_fieldAI : public ScriptedAI
    {
       npc_cs_fieldAI(Creature *pCreature) : ScriptedAI(pCreature)
       {
           m_pInstance = pCreature->GetInstanceScript();
           Reset();
       }

       InstanceScript* m_pInstance;

       uint32 m_uiScarabTimer;
       uint32 m_uiBlowTimer;

       uint32 WaypointId;
       uint32 MoveTimer;

       void Reset() 
       { 
         me->RemoveUnitMovementFlag(MOVEMENTFLAG_WALKING);
         MoveTimer = (urand(100, 5000));
         m_uiBlowTimer = (urand(7000, 17000));
         m_uiScarabTimer = (urand(3000, 10000));
         WaypointId = 1;
       }

       void MoveToPoint(float X, float Y, float Z)
       {
           me->GetMotionMaster()->MovementExpired(false);
           me->GetMotionMaster()->MovePoint(0, X, Y, Z);
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

            if (IsCombatMovementAllowed())
                me->GetMotionMaster()->MoveChase(pWho);
          }
       }

       void EnterEvadeMode()
       {
          me->RemoveAllAuras();
          me->DeleteThreatList();
          me->CombatStop(true);
          me->LoadCreaturesAddon();
          m_uiScarabTimer = (urand(3000, 10000));
          m_uiBlowTimer = (urand(7000, 17000));

          me->SetLootRecipient(NULL);
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

       void JumpNextStep(uint32 Time)
       {
         MoveTimer = Time;
         WaypointId++;
       }

       void UpdateAI(const uint32 uiDiff)
       {
            if (!UpdateVictim())
            {
              if(MoveTimer < uiDiff)
              {   
                 if(m_pInstance->GetData(TYPE_WING) == RIGHT)
                 {
                    switch(WaypointId)
                    {
                      case 1:
                         MoveToPoint(2356.659f, 1185.501f, 130.636f);
                         JumpNextStep(10000);
                         break; 
                      case 2:
                         MoveToPoint(2301.735f, 1179.265f, 136.944f);
                         JumpNextStep(8000);
                         break;  
                      case 3:
                         MoveToPoint(2234.787f, 1180.638f, 136.344f);
                         JumpNextStep(9000);
                         break; 
                      case 4:
                         MoveToPoint(2178.313f, 1244.350f, 136.107f);
                         JumpNextStep(12000);
                         break; 
                      case 5:
                         MoveToPoint(2163.553f, 1277.814f, 133.444f);
                         JumpNextStep(5000);
                         break; 
                      case 6:
                         MoveToPoint(2083.952f, 1287.716f, 141.146f);
                         JumpNextStep(5000);
                         break; 
                    }
                 }

                 if(m_pInstance->GetData(TYPE_WING) == LEFT)
                 {
                    switch(WaypointId)
                    {
                      case 1:
                         MoveToPoint(2188.318f, 1331.410f, 130.003f);
                         JumpNextStep(10000);
                         break; 
                      case 2:
                         MoveToPoint(2165.351f, 1279.156f, 133.388f);
                         JumpNextStep(8000);
                         break;  
                      case 3:
                         MoveToPoint(2083.952f, 1287.716f, 141.146f);
                         JumpNextStep(9000);
                         break; 
                    }
                 }

               } else MoveTimer -= uiDiff;
            }

            if (!UpdateVictim())
                return;

            if(m_uiScarabTimer < uiDiff)
            {    
               if(Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 40, true))   
                  DoCast(target, SPELL_SCARAB);
               m_uiScarabTimer  = (urand(3000, 5000));
            }
            else m_uiScarabTimer -= uiDiff;

            if(m_uiBlowTimer < uiDiff)
            {    
               me->InterruptNonMeleeSpells(false);
               if(Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))   
                  DoCast(target, SPELL_BLOW);
               m_uiBlowTimer  = (urand(7000, 17000));
            }
            else m_uiBlowTimer -= uiDiff;

            DoMeleeAttackIfReady();

            return;
       }
    };

};

/*###
## npc_cs_alocyte
###*/

enum
{
  SPELL_SHADOW             = 17234,
  SPELL_COLD               = 15244,
  SPELL_FIRE               = 14145,
  SPELL_COURSEA            = 39621
};
class npc_cs_acolyte : public CreatureScript
{
public:
    npc_cs_acolyte() : CreatureScript("npc_cs_acolyte") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_cs_acolyteAI(pCreature);
    }

	struct npc_cs_acolyteAI : public ScriptedAI
	{
		npc_cs_acolyteAI(Creature *pCreature) : ScriptedAI(pCreature)
		{
			m_pInstance = pCreature->GetInstanceScript();
			SetCombatMovement(false);
			Reset();
		}

		InstanceScript* m_pInstance;

		uint32 m_uiColdTimer;
		uint32 m_uiFireTimer;
		uint32 m_uiCourseTimer;
		uint32 m_uiShadowTimer;

		uint32 WaypointId;
		uint32 MoveTimer;

		void Reset() 
		{ 
			me->RemoveUnitMovementFlag(MOVEMENTFLAG_WALKING);
			MoveTimer = (urand(100, 5000));
			m_uiColdTimer = (urand(7000, 17000));
			m_uiFireTimer = (urand(3000, 10000));
			m_uiCourseTimer = (urand(5000, 12000));
			m_uiShadowTimer = (urand(1000, 3000));
			WaypointId = 1;
		}

		void MoveToPoint(float X, float Y, float Z)
		{
			me->GetMotionMaster()->MovementExpired(false);
			me->GetMotionMaster()->MovePoint(0, X, Y, Z);
		}

		void EnterCombat(Unit* pWho)
		{
			me->GetMotionMaster()->MovementExpired(false);
			me->StopMoving();
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
			me->GetMotionMaster()->MovementExpired(false);
		}

		void EnterEvadeMode()
		{
			me->RemoveAllAuras();
			me->DeleteThreatList();
			me->CombatStop(true);
			me->LoadCreaturesAddon();
			m_uiColdTimer = (urand(7000, 17000));
			m_uiFireTimer = (urand(3000, 10000));
			m_uiCourseTimer = (urand(5000, 12000));
			m_uiShadowTimer = (urand(1000, 3000));

			me->SetLootRecipient(NULL);
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

		void JumpNextStep(uint32 Time)
		{
			MoveTimer = Time;
			WaypointId++;
		}

		void UpdateAI(const uint32 uiDiff)
		{
			if (!UpdateVictim())
			{
				if(MoveTimer < uiDiff)
				{   
					if(m_pInstance->GetData(TYPE_WING) == RIGHT)
					{
						switch(WaypointId)
						{
						case 1:
							MoveToPoint(2356.659f, 1185.501f, 130.636f);
							JumpNextStep(10000);
							break; 
						case 2:
							MoveToPoint(2301.735f, 1179.265f, 136.944f);
							JumpNextStep(8000);
							break;  
						case 3:
							MoveToPoint(2234.787f, 1180.638f, 136.344f);
							JumpNextStep(9000);
							break; 
						case 4:
							MoveToPoint(2178.313f, 1244.350f, 136.107f);
							JumpNextStep(12000);
							break; 
						case 5:
							MoveToPoint(2163.553f, 1277.814f, 133.444f);
							JumpNextStep(5000);
							break; 
						case 6:
							MoveToPoint(2083.952f, 1287.716f, 141.146f);
							JumpNextStep(5000);
							break; 
						}
					}

					if(m_pInstance->GetData(TYPE_WING) == LEFT)
					{
						switch(WaypointId)
						{
						case 1:
							MoveToPoint(2188.318f, 1331.410f, 130.003f);
							JumpNextStep(10000);
							break; 
						case 2:
							MoveToPoint(2165.351f, 1279.156f, 133.388f);
							JumpNextStep(8000);
							break;  
						case 3:
							MoveToPoint(2083.952f, 1287.716f, 141.146f);
							JumpNextStep(9000);
							break; 
						}
					}

				} else MoveTimer -= uiDiff;
			}

			if (!UpdateVictim())
				return;

			if(m_uiShadowTimer < uiDiff)
			{       
				DoCast(me->getVictim(), SPELL_SHADOW);
				m_uiShadowTimer  = (urand(3000, 8000));
			}
			else m_uiShadowTimer -= uiDiff;

			if(m_uiCourseTimer < uiDiff)
			{    
				if(Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 80, true))   
					DoCast(target, SPELL_COURSEA);
				m_uiCourseTimer  = (urand(7000, 13000));
			}
			else m_uiCourseTimer -= uiDiff;

			if(m_uiColdTimer < uiDiff)
			{    
				if(Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 15, true))   
					DoCast(target, SPELL_COLD);
				m_uiColdTimer  = (urand(13000, 17000));
			}
			else m_uiColdTimer -= uiDiff;

			if(m_uiFireTimer < uiDiff)
			{    
				if(Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 20, true))   
					DoCast(target, SPELL_FIRE);
				m_uiFireTimer  = (urand(6000, 11000));
			}
			else m_uiFireTimer -= uiDiff;

			DoMeleeAttackIfReady();

			return;
		}
	};

};

/*###
## npc_cs_butcher
###*/

enum
{
	SPELL_CLOUD       = 52525
};
class npc_cs_butcher : public CreatureScript
{
public:
    npc_cs_butcher() : CreatureScript("npc_cs_butcher") { }

	CreatureAI* GetAI(Creature* pCreature) const
	{
		return new npc_cs_butcherAI(pCreature);
	}

	struct npc_cs_butcherAI : public ScriptedAI
	{
		npc_cs_butcherAI(Creature *pCreature) : ScriptedAI(pCreature)
		{
			m_pInstance = pCreature->GetInstanceScript();
			Reset();
		}

		InstanceScript* m_pInstance;

		uint32 WaypointId;
		uint32 MoveTimer;

		void Reset() 
		{ 
			DoCast(me, SPELL_CLOUD);
			me->RemoveUnitMovementFlag(MOVEMENTFLAG_WALKING);
			MoveTimer = (urand(100, 5000));
			WaypointId = 1;
		}

		void MoveToPoint(float X, float Y, float Z)
		{
			me->GetMotionMaster()->MovementExpired(false);
			me->GetMotionMaster()->MovePoint(0, X, Y, Z);
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

				if (IsCombatMovementAllowed())
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
			DoCast(me, SPELL_CLOUD);
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

		void JumpNextStep(uint32 Time)
		{
			MoveTimer = Time;
			WaypointId++;
		}

		void UpdateAI(const uint32 uiDiff)
		{
			if (!UpdateVictim())
			{
				if(MoveTimer < uiDiff)
				{   
					if(m_pInstance->GetData(TYPE_WING) == RIGHT)
					{
						switch(WaypointId)
						{
						case 1:
							MoveToPoint(2356.659f, 1185.501f, 130.636f);
							JumpNextStep(10000);
							break; 
						case 2:
							MoveToPoint(2301.735f, 1179.265f, 136.944f);
							JumpNextStep(8000);
							break;  
						case 3:
							MoveToPoint(2234.787f, 1180.638f, 136.344f);
							JumpNextStep(9000);
							break; 
						case 4:
							MoveToPoint(2178.313f, 1244.350f, 136.107f);
							JumpNextStep(12000);
							break; 
						case 5:
							MoveToPoint(2163.553f, 1277.814f, 133.444f);
							JumpNextStep(5000);
							break; 
						case 6:
							MoveToPoint(2083.952f, 1287.716f, 141.146f);
							JumpNextStep(5000);
							break; 
						}
					}

					if(m_pInstance->GetData(TYPE_WING) == LEFT)
					{
						switch(WaypointId)
						{
						case 1:
							MoveToPoint(2188.318f, 1331.410f, 130.003f);
							JumpNextStep(10000);
							break; 
						case 2:
							MoveToPoint(2165.351f, 1279.156f, 133.388f);
							JumpNextStep(8000);
							break;  
						case 3:
							MoveToPoint(2083.952f, 1287.716f, 141.146f);
							JumpNextStep(9000);
							break; 
						}
					}

				} else MoveTimer -= uiDiff;
			}

			if (!UpdateVictim())
				return;

			DoMeleeAttackIfReady();

			return;
		}
	};

};
class npc_time_riftCS : public CreatureScript
{
public:
    npc_time_riftCS() : CreatureScript("npc_time_riftCS") { }

	CreatureAI* GetAI(Creature* pCreature) const
	{
		return new npc_time_riftCSAI(pCreature);
	}

	struct npc_time_riftCSAI : public ScriptedAI
	{
		npc_time_riftCSAI(Creature *pCreature) : ScriptedAI(pCreature) 
		{
			m_pInstance = pCreature->GetInstanceScript();
			Reset();
		}

		InstanceScript* m_pInstance;

		uint32 Step;
		uint32 m_uiStepTimer;
		Creature* Drakonian01;
		Creature* Drakonian02;
		Creature* Drakonian03;

		void Reset() 
		{
			m_uiStepTimer = 1000;
			Step = 1;
		}

		void UpdateAI(const uint32 uiDiff)
		{
			if (m_uiStepTimer < uiDiff)
			{
				switch(Step)
				{
				case 1:
					if (Creature* pArthas = Unit::GetCreature(*me, m_pInstance->GetData64(NPC_ARTHAS)))
					{
						if (Drakonian01 = me->SummonCreature(NPC_INFINITE_ADVERSARY,(me->GetPositionX()-2)+rand()%4, (me->GetPositionY()-2)+rand()%4, me->GetPositionZ(),3.229f,TEMPSUMMON_TIMED_OR_DEAD_DESPAWN,900000))
							Drakonian01->GetMotionMaster()->MovePoint(0, pArthas->GetPositionX(), pArthas->GetPositionY(), pArthas->GetPositionZ());
						if (Drakonian02 = me->SummonCreature(NPC_INFINITE_HUNTER,(me->GetPositionX()-2)+rand()%4, (me->GetPositionY()-2)+rand()%4, me->GetPositionZ(),3.229f,TEMPSUMMON_TIMED_OR_DEAD_DESPAWN,900000))
							Drakonian02->GetMotionMaster()->MovePoint(0, pArthas->GetPositionX(), pArthas->GetPositionY(), pArthas->GetPositionZ());
						if (Drakonian03 = me->SummonCreature(NPC_INFINITE_AGENT,(me->GetPositionX()-2)+rand()%4, (me->GetPositionY()-2)+rand()%4, me->GetPositionZ(),3.229f,TEMPSUMMON_TIMED_OR_DEAD_DESPAWN,900000))
							Drakonian03->GetMotionMaster()->MovePoint(0, pArthas->GetPositionX(), pArthas->GetPositionY(), pArthas->GetPositionZ());
					}
					m_uiStepTimer = 3000;
					Step++;
					break;
				case 2:
					me->RemoveFromWorld();
					Step++; 
					break;
				}
			} else m_uiStepTimer -= uiDiff;
		}
	};

};

void AddSC_trash_culling_of_stratholme()
{
	new npc_cs_gnoul();
	new npc_cs_necromancer();
	new npc_cs_field();
	new npc_cs_acolyte();
	new npc_cs_butcher();
	new npc_time_riftCS();
}
