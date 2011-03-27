/*
 * Copyright (C) 2008-2011 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2006-2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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
SDName: Loch_Modan
SD%Complete: 100
SDComment: Quest support: 3181
SDCategory: Loch Modan
EndScriptData */

/* ContentData
npc_mountaineer_pebblebitty
EndContentData */

#include "ScriptPCH.h"

/*######
## npc_mountaineer_pebblebitty
######*/

#define GOSSIP_MP "Open the gate please, i need to get to Searing Gorge"
#define GOSSIP_MP_RU "Откройте ворота, пожалуйста! Мне нужно пройти в Тлеющее ущелье."

#define GOSSIP_MP1 "But i need to get there, now open the gate!"
#define GOSSIP_MP2 "Ok, so what is this other way?"
#define GOSSIP_MP3 "Doesn't matter, i'm invulnerable."
#define GOSSIP_MP4 "Yes..."
#define GOSSIP_MP5 "Ok, i'll try to remember that."
#define GOSSIP_MP6 "A key? Ok!"

#define GOSSIP_MP1_RU "Но мне нужно пройти, так что открывай ворота!"
#define GOSSIP_MP2_RU "Ладно, а другая дорога есть?"
#define GOSSIP_MP3_RU "Неважно, я неуязвим."
#define GOSSIP_MP4_RU "Абсолютно!"
#define GOSSIP_MP5_RU "Ладно, постараюсь запомнить."
#define GOSSIP_MP6_RU "Ключ? Хорошо!"

#define MP_RUDESAY -1900000

class npc_mountaineer_pebblebitty : public CreatureScript
{
public:
    npc_mountaineer_pebblebitty() : CreatureScript("npc_mountaineer_pebblebitty") { }

    bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
    {
        pPlayer->PlayerTalkClass->ClearMenus();
        switch (uiAction)
        {
            case GOSSIP_ACTION_INFO_DEF+1:
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, (pPlayer->isRussianLocale())? GOSSIP_MP1_RU:GOSSIP_MP1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                pPlayer->SEND_GOSSIP_MENU(1833, pCreature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+2:
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, (pPlayer->isRussianLocale())? GOSSIP_MP2_RU:GOSSIP_MP2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
                pPlayer->SEND_GOSSIP_MENU(1834, pCreature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+3:
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, (pPlayer->isRussianLocale())? GOSSIP_MP3_RU:GOSSIP_MP3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
                pPlayer->SEND_GOSSIP_MENU(1835, pCreature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+4:
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, (pPlayer->isRussianLocale())? GOSSIP_MP4_RU:GOSSIP_MP4, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
                pPlayer->SEND_GOSSIP_MENU(1836, pCreature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+5:
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, (pPlayer->isRussianLocale())? GOSSIP_MP5_RU:GOSSIP_MP5, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
                pPlayer->SEND_GOSSIP_MENU(1837, pCreature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+6:
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, (pPlayer->isRussianLocale())? GOSSIP_MP6_RU:GOSSIP_MP6, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
                pPlayer->SEND_GOSSIP_MENU(1838, pCreature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+7:
                pPlayer->CLOSE_GOSSIP_MENU();
                break;
        }
        return true;
    }

    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
        if (pCreature->isQuestGiver())
            pPlayer->PrepareQuestMenu(pCreature->GetGUID());

        if (!pPlayer->GetQuestRewardStatus(3181))
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, (pPlayer->isRussianLocale())? GOSSIP_MP_RU:GOSSIP_MP, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

        pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());

        return true;
    }

    CreatureAI* GetAI(Creature *pCreature) const
    {
        return new npc_mountaineer_pebblebittyAI(pCreature);
    }

    struct npc_mountaineer_pebblebittyAI : public ScriptedAI
    {
        npc_mountaineer_pebblebittyAI(Creature *c) : ScriptedAI(c) {}

        void ReceiveEmote(Player* pPlayer, uint32 uiTextEmote)
        {
            me->HandleEmoteCommand(uiTextEmote);

            if (uiTextEmote == TEXTEMOTE_RUDE)
			    DoScriptText(MP_RUDESAY, me, pPlayer);
        }
    };

};

void AddSC_loch_modan()
{
    new npc_mountaineer_pebblebitty();
}
