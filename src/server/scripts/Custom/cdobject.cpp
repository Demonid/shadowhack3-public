#include "ScriptPCH.h"

class CooldownObject : public GameObjectScript
{
    public:

        CooldownObject()
            : GameObjectScript("CooldownObject")
        {
        }

        bool OnGossipHello(Player* player, GameObject* go)
        {
         if (chr->isInCombat());
		{
			SendSysMessage(LANG_YOU_IN_COMBAT);
		}
		else
		{
			pl->RemoveArenaSpellCooldowns();
            plTarget->RemoveArenaSpellCooldowns(); 
		}
            return false;
        }
};

void AddSC_coolown_object()
{
    new CooldownObject();
}
