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
         if (player->isInCombat())
		{
			ChatHandler(player).PSendSysMessage("You are in combat.");
		}
		else
		{
			player->RemoveArenaSpellCooldowns();
			go->Delete();
		}
            return false;
        }
};

void AddSC_coolown_object()
{
    new CooldownObject();
}
