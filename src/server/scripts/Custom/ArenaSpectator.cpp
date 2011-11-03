#include "Chat.h"
#include "ScriptMgr.h"
#include "Battleground.h"
#include "Map.h"
#include "Group.h"

class ArenaSpectatorCommandScript : public CommandScript
{
public:
    ArenaSpectatorCommandScript() : CommandScript("ArenaSpectatorCommandScript") {}

    ChatCommand* GetCommands() const
    {
        static ChatCommand arenaspecCommandTable[] =
        {
            { "reset",          SEC_GAMEMASTER,     false,  HandleArenaSpecResetCommand,        "", NULL    },
            { "watch",           SEC_GAMEMASTER,     false,  HandleArenaSpecWatchCommand,       "", NULL    },
            { NULL,             0,                  false,  NULL,                               "", NULL    }
        };

        static ChatCommand commandTable[] =
        {
            { "spectator",      SEC_GAMEMASTER,     false,  NULL,               "", arenaspecCommandTable   },
            { NULL,             0,                  false,  NULL,               "", NULL                    },
        };

        return commandTable;
    }

    static bool HandleArenaSpecResetCommand(ChatHandler *handler, const char* /*args*/)
    {
        if (!sWorld->getBoolConfig(CONFIG_ARENA_SPECTATOR_UPDATES))
        {
            handler->PSendSysMessage("Disabled!");
            handler->SetSentErrorMessage(true);
            return false;
        }

        Player *p = handler->GetSession()->GetPlayer();
        if (!p || !p->InArena())
        {
            handler->PSendSysMessage("Need to be in arena");
            handler->SetSentErrorMessage(true);
            return false;
        }

        Map::PlayerList const &PlList = p->GetMap()->GetPlayers();

        if (PlList.isEmpty())
            return true;

        for (Map::PlayerList::const_iterator i = PlList.begin(); i != PlList.end(); ++i)
        {
            if (Player* pPlayer = i->getSource())
            {
                if (pPlayer->isGameMaster())
                    continue;

                pPlayer->m_arenaSpectatorFlags = 0xFFFF;
            }
        }

        return true;
    }

    static bool HandleArenaSpecWatchCommand(ChatHandler *handler, const char* args)
    {
        if (!sWorld->getBoolConfig(CONFIG_ARENA_SPECTATOR_UPDATES))
        {
            handler->PSendSysMessage("Disabled!");
            handler->SetSentErrorMessage(true);
            return false;
        }

        Player *p = handler->GetSession()->GetPlayer();
        if (!p || !p->InArena())
        {
            handler->PSendSysMessage("Need to be in arena");
            handler->SetSentErrorMessage(true);
            return false;
        }

        Player *t = sObjectAccessor->FindPlayerByName(args);
        if (!t || t->GetBattleground()->GetInstanceID() != p->GetBattleground()->GetInstanceID())
            return false;

        p->StopCastingBindSight();
        p->CastSpell(t, 6277, true);
        return true;
    }
};

void AddSC_ArenaSpectator()
{
    new ArenaSpectatorCommandScript();
}