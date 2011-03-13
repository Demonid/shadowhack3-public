#include "ScriptPCH.h"
#include "ScriptedEscortAI.h"
#include "ScriptMgr.h"
#include "World.h"
#include "Chat.h"
#include "Language.h"
struct prof
{
    uint32 id;
    std::string name;
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
            pPlayer->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Закрыть меню!", GOSSIP_SENDER_MAIN, 120);
        }
        else
            pCreature->MonsterWhisper("Ата-та по рукам! Нельзя так много проф юзать!", LANG_UNIVERSAL, NULL);
    
        pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
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
                    creature->MonsterSay("Ата-та по рукам! Нельзя так много проф юзать!", LANG_UNIVERSAL, NULL);
                    player->CLOSE_GOSSIP_MENU();
                }
        
                player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());    
                break;
            }
            case 110:
            {
                for (uint8 i=1; i<MAXPROF; ++i)
                {
                    std::string text= "Хочу изучить ";
                    text+=profs[i].name;
                    text+="!";
                    player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, text, GOSSIP_SENDER_MAIN, i);
                }
                player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,creature->GetGUID());
                break;
            }
            case 130:
            {
                player->CLOSE_GOSSIP_MENU();
                break;
            }
            default:
                if (action<=MAXPROF)
                {
                    player->CastSpell(player, profs[action].id, true);
                    player->SetSkill(profs[action].skill, player->GetSkillStep(profs[action].skill), 450, 450);
                    ((ChatHandler*)player)->HandleLearnSkillRecipesHelper(player,profs[action].skill);
                    std::string text = "Операция выполнена успешно, ";
                    text+=profs[action].name;
                    text+=" изучен";
                    creature->MonsterSay(text.c_str(), LANG_UNIVERSAL, NULL);
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