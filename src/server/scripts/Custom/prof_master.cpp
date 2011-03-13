#include "ScriptPCH.h"
#include "ScriptedEscortAI.h"
#include "ScriptMgr.h"
#include "World.h"
#include "Chat.h"
#include "Language.h"

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

class prof_master : public CreatureScript
{
    public:
        prof_master() : CreatureScript("prof_master") { }

    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
        uint32 freeProfs = pPlayer->GetFreePrimaryProfessionPoints()+1;
        if (freeProfs >= sWorld->getIntConfig(CONFIG_MAX_PRIMARY_TRADE_SKILL))
        {
            pPlayer->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Хочу изучить профессию!", GOSSIP_SENDER_MAIN, 10);
            pPlayer->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Закрыть меню!", GOSSIP_SENDER_MAIN, 20);
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
            case 9:
            {
                uint32 freeProfs = player->GetFreePrimaryProfessionPoints()+1;
                if (freeProfs >= sWorld->getIntConfig(CONFIG_MAX_PRIMARY_TRADE_SKILL))
                {
                    player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Хочу изучить профессию!", GOSSIP_SENDER_MAIN, 10);
                    player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Закрыть меню!", GOSSIP_SENDER_MAIN, 30);
                }
                else
                {
                    creature->MonsterSay("Ата-та по рукам! Нельзя так много проф юзать!", LANG_UNIVERSAL, NULL);
                    player->CLOSE_GOSSIP_MENU();
                }
        
                player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());    
                break;
            }
            case 10:
            {
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Хочу изучить Jewelcrafting (Ювелирное дело)!", GOSSIP_SENDER_MAIN, 11);
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Хочу изучить Enchanting (Наложение чар)!", GOSSIP_SENDER_MAIN, 12);
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Хочу изучить Engineering (Инженерное дело)!", GOSSIP_SENDER_MAIN, 13);
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Хочу изучить Blacksmith (Кузнечное дело)!", GOSSIP_SENDER_MAIN, 14);
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Хочу изучить Leatherworking (Кожевничество)!", GOSSIP_SENDER_MAIN, 15);
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Хочу изучить Inscription (Начертание)!", GOSSIP_SENDER_MAIN, 16);
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Хочу изучить Alchemy (Алхимия)!", GOSSIP_SENDER_MAIN, 17);
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Хочу изучить Mining (Горное дело)!", GOSSIP_SENDER_MAIN, 18);
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Хочу изучить Herbalism (Травничество)!", GOSSIP_SENDER_MAIN, 19);
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Хочу изучить Tailoring (Шитье)!", GOSSIP_SENDER_MAIN, 20);
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Вернуться в главное меню!", GOSSIP_SENDER_MAIN, 9);
                player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,creature->GetGUID());
                break;
            }
            case 11:
            {
                player->CastSpell(player, jewelcrafting, true);

                player->SetSkill(755, player->GetSkillStep(755), 450, 450);
                ((ChatHandler*)player)->HandleLearnSkillRecipesHelper(player,755);
                creature->MonsterSay("Операция выполнена успешно, Jewelcrafting выучен!", LANG_UNIVERSAL, NULL);
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Вернуться в главное меню!", GOSSIP_SENDER_MAIN, 9);
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Закрыть меню!", GOSSIP_SENDER_MAIN, 30);
                player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,creature->GetGUID());
                break;
            }
            case 12:
            {
                player->CastSpell(player, enchanting, true);

                player->SetSkill(333, player->GetSkillStep(333), 450, 450);
                ((ChatHandler*)player)->HandleLearnSkillRecipesHelper(player,333);
                creature->MonsterSay("Операция выполнена успешно, Enchanting выучен!", LANG_UNIVERSAL, NULL);
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Вернуться в главное меню!", GOSSIP_SENDER_MAIN, 9);
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Закрыть меню!", GOSSIP_SENDER_MAIN, 30);
                player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,creature->GetGUID());
                break;
            }
            case 13:
            {
                player->CastSpell(player, engineering, true);

                player->SetSkill(202, player->GetSkillStep(202), 450, 450);
                ((ChatHandler*)player)->HandleLearnSkillRecipesHelper(player,202);
                creature->MonsterSay("Операция выполнена успешно, Engineering выучен!", LANG_UNIVERSAL, NULL);
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Вернуться в главное меню!", GOSSIP_SENDER_MAIN, 9);
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Закрыть меню!", GOSSIP_SENDER_MAIN, 30);
                player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,creature->GetGUID());
                break;
            }
            case 14:
            {
                player->CastSpell(player, blacksmith, true);

                player->SetSkill(164, player->GetSkillStep(164), 450, 450);
                ((ChatHandler*)player)->HandleLearnSkillRecipesHelper(player,164);
                creature->MonsterSay("Операция выполнена успешно, Blacksmith выучен!", LANG_UNIVERSAL, NULL);
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Вернуться в главное меню!", GOSSIP_SENDER_MAIN, 9);
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Закрыть меню!", GOSSIP_SENDER_MAIN, 30);
                player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,creature->GetGUID());
                break;
            }
            case 15:
            {
                player->CastSpell(player, leatherworking, true);

                player->SetSkill(165, player->GetSkillStep(165), 450, 450);
                ((ChatHandler*)player)->HandleLearnSkillRecipesHelper(player,165);
                creature->MonsterSay("Операция выполнена успешно, Leatherworking выучен!", LANG_UNIVERSAL, NULL);
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Вернуться в главное меню!", GOSSIP_SENDER_MAIN, 9);
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Закрыть меню!", GOSSIP_SENDER_MAIN, 30);
                player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,creature->GetGUID());
                break;
            }
            case 16:
            {
                player->CastSpell(player, inscription, true);

                player->SetSkill(773, player->GetSkillStep(773), 450, 450);
                ((ChatHandler*)player)->HandleLearnSkillRecipesHelper(player,773);
                creature->MonsterSay("Операция выполнена успешно, Inscription выучен!", LANG_UNIVERSAL, NULL);
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Вернуться в главное меню!", GOSSIP_SENDER_MAIN, 9);
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Закрыть меню!", GOSSIP_SENDER_MAIN, 30);
                player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,creature->GetGUID());
                break;
            }
            case 17:
            {
                player->CastSpell(player, alchemy, true);

                player->SetSkill(171, player->GetSkillStep(171), 450, 450);
                ((ChatHandler*)player)->HandleLearnSkillRecipesHelper(player,171);
                creature->MonsterSay("Операция выполнена успешно, Alchemy выучен!", LANG_UNIVERSAL, NULL);
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Вернуться в главное меню!", GOSSIP_SENDER_MAIN, 9);
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Закрыть меню!", GOSSIP_SENDER_MAIN, 30);
                player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,creature->GetGUID());
                break;
            }
            case 18:
            {
                player->CastSpell(player, mining, true);

                player->SetSkill(186, player->GetSkillStep(186), 450, 450);
                ((ChatHandler*)player)->HandleLearnSkillRecipesHelper(player,186);
                creature->MonsterSay("Операция выполнена успешно, Mining выучен!", LANG_UNIVERSAL, NULL);
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Вернуться в главное меню!", GOSSIP_SENDER_MAIN, 9);
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Закрыть меню!", GOSSIP_SENDER_MAIN, 30);
                player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,creature->GetGUID());
                break;
            }
            case 19:
            {
                player->CastSpell(player, herbalism, true);

                player->SetSkill(182, player->GetSkillStep(182), 450, 450);
                ((ChatHandler*)player)->HandleLearnSkillRecipesHelper(player,182);
                creature->MonsterSay("Операция выполнена успешно, Herbalism выучен!", LANG_UNIVERSAL, NULL);
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Вернуться в главное меню!", GOSSIP_SENDER_MAIN, 9);
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Закрыть меню!", GOSSIP_SENDER_MAIN, 30);
                player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,creature->GetGUID());
                break;
            }
            case 20:
            {
                player->CastSpell(player, tailor, true);

                player->SetSkill(197, player->GetSkillStep(197), 450, 450);
                ((ChatHandler*)player)->HandleLearnSkillRecipesHelper(player,197);
                creature->MonsterSay("Операция выполнена успешно, Tailoring выучен!", LANG_UNIVERSAL, NULL);
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Вернуться в главное меню!", GOSSIP_SENDER_MAIN, 9);
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Закрыть меню!", GOSSIP_SENDER_MAIN, 30);
                player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,creature->GetGUID());
                break;
            }
            case 30:
            {
                player->CLOSE_GOSSIP_MENU();
                break;
            }
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