#include "ScriptPCH.h"
#include "ScriptedEscortAI.h"
#include "ScriptMgr.h"
#include "World.h"
#include "Chat.h"
#include "Language.h"
struct prof
{
    uint32 id;
    char* name;
    uint32 skill;
};

enum Spells
{
    blacksmith            = 65282,
    jewelcrafting         = 65286,
    engineering           = 61464,
    enchanting            = 65285,
    leatherworking        = 65284,
    alchemy               = 65281,
    mining                = 65289,
    herbalism             = 65288,
    inscription           = 65287,
    tailor                = 65283
};

const prof profs[] = 
{
    // id                           name                   skill
    {0         ,        "EMPTY! IF REALEASED - BUGG",       0  },
    {blacksmith,        "Blacksmith (Кузнечное дело)",      164},
    {jewelcrafting,     "Jewelcrafting (Ювелирное дело)",   755},
    {engineering,       "Engineering (Инженерное дело)",    202},
    {enchanting,        "Enchanting (Наложение чар)",       333},
    {leatherworking,    "Leatherworking (Кожевничество)",   165},
    {alchemy,           "Alchemy (Алхимия)",                171},
    {mining,            "Mining (Горное дело)",             186},
    {herbalism,         "Herbalism (Травничество)",         182},
    {inscription,       "Inscription (Начертание)",         773},
    {tailor,            "Tailoring (Шитье)",                197}
};

#define MAXPROF 10+1

class prof_master : public CreatureScript
{
    public:
        prof_master() : CreatureScript("prof_master") { }

    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
        uint32 freeProfs = pPlayer->GetFreePrimaryProfessionPoints()+1;
        if (freeProfs >= sWorld->getIntConfig(CONFIG_MAX_PRIMARY_TRADE_SKILL))
        {
            pPlayer->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Хочу изучить профессию!", GOSSIP_SENDER_MAIN, 110);
            pPlayer->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Закрыть меню!", GOSSIP_SENDER_MAIN, 130);
        }
        else
            pCreature->MonsterWhisper("Ата-та по рукам! Нельзя так много проф юзать!", pPlayer->GetGUID(), true);
    
        pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        if(action == 130)
        {
            player->CLOSE_GOSSIP_MENU();
            return true;
        }
        player->PlayerTalkClass->GetGossipMenu().ClearMenu();
        switch(action)
        {
            case 19:
            {
                uint32 freeProfs = player->GetFreePrimaryProfessionPoints()+1;
                if (freeProfs >= sWorld->getIntConfig(CONFIG_MAX_PRIMARY_TRADE_SKILL))
                {
                    player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Хочу изучить профессию!", GOSSIP_SENDER_MAIN, 110);
                    player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Закрыть меню!", GOSSIP_SENDER_MAIN, 130);
                }
                else
                {
                    creature->MonsterWhisper("Ата-та по рукам! Нельзя так много проф юзать!", player->GetGUID(), true);
                    player->CLOSE_GOSSIP_MENU();
                }
        
                player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());    
                break;
            }
            case 110:
            {
                for (uint8 i=1; i<MAXPROF; ++i)
                {
                    char text[255];
                    snprintf( text, 255,     "Хочу изучить %s!", profs[i].name );
                    player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, text, GOSSIP_SENDER_MAIN, i);
                }
                player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,creature->GetGUID());
                break;
            }
            default:
                // wtf bug
                if(action == 0)
                {
                    player->CLOSE_GOSSIP_MENU();
                    return true;
                }
                if (action<=MAXPROF)
                {
                    player->CastSpell(player, profs[action].id, true);
                    player->SetSkill(profs[action].skill, player->GetSkillStep(profs[action].skill), 450, 450);
                    ((ChatHandler*)player)->HandleLearnSkillRecipesHelper(player,profs[action].skill);
                    char text[255];
                    snprintf( text, 255,     "Операция выполнена успешно, %s изучен", profs[action].name);
                    creature->MonsterWhisper(text, player->GetGUID(), true);
                    player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Вернуться в главное меню!", GOSSIP_SENDER_MAIN, 19);
                    player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Закрыть меню!", GOSSIP_SENDER_MAIN, 130);
                    player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,creature->GetGUID());
                }
                break;
        }
        return true;
    }
    
    bool GossipSelect_prof_master(Player *player, Creature *_Creature, uint32 sender, uint32 action )
    {
        if (sender == GOSSIP_SENDER_MAIN)
        OnGossipSelect(player, _Creature, 0, action);

        return true;
    }
};

void AddSC_prof_master()
{
    new prof_master;
}