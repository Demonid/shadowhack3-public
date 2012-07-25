class npc_helper : public CreatureScript
{
public:
    npc_helper() : CreatureScript("npc_helper") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (creature->GetOwnerGUID() != player->GetGUID())
        {
            player->CLOSE_GOSSIP_MENU();

            player->TextEmote("�������� ���� ��� ������� ������������ ������ ���������.");

            creature->HandleEmoteCommand(EMOTE_ONESHOT_ATTACK_UNARMED);
            creature->DealDamage(player, urand(1000, 2000), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);
            player->HandleEmoteCommand(EMOTE_ONESHOT_WOUND_CRITICAL);
            return true;
        }

        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "�������", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);

        if (player->getPowerType() == POWER_MANA)
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "������������ �������� � ����", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+36);
        else
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "������������ ��������", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+36);

        player->SEND_GOSSIP_MENU(68, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();

        switch (action)
        {
            case GOSSIP_ACTION_INFO_DEF+1:
                OnGossipHello(player, creature);
                break;
            case GOSSIP_ACTION_INFO_DEF+2:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "<- �����", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "�����", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+3);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "������", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+10);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "���������", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+22);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "�������", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+30);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "��������", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+42);
                player->SEND_GOSSIP_MENU(68, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+3:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "<- �����", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "PvE ���������", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+4);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "PvP ���������", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+7);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "��������", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+31);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "�����", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+32);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "�����", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+33);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "��������", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+39);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "������", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+40);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "����������", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+41);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "�����", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+34);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "����", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+35);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "� ������ ����", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+37);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "�������", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+38);
                player->SEND_GOSSIP_MENU(68, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+4:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "<- �����", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+3);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "�������� Tier 9", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+5);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "�������� Tier 10", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+6);
                player->SEND_GOSSIP_MENU(68, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+5:
                player->GetSession()->sSendListInventory(50001, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+6:
                player->GetSession()->sSendListInventory(50003, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+7:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "<- �����", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+3);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "�������� 7 ������ �����", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+8);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "�������� 8 ������ �����", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+9);
                player->SEND_GOSSIP_MENU(68, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+8:
                player->GetSession()->sSendListInventory(50000, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+9:
                player->GetSession()->sSendListInventory(50002, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+10:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "<- �����", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "��������", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+11);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "���������", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+12);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "��������", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+13);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "�������", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+14);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "��������", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+15);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "����", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+16);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "����", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+17);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "������", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+18);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "�������������", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+19);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "������", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+20);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "�����", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+21);
                player->SEND_GOSSIP_MENU(68, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+11:
                player->GetSession()->sSendListInventory(50013, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+12:
                player->GetSession()->sSendListInventory(50008, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+13:
                player->GetSession()->sSendListInventory(50007, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+14:
                player->GetSession()->sSendListInventory(50012, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+15:
                player->GetSession()->sSendListInventory(50011, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+16:
                player->GetSession()->sSendListInventory(50005, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+17:
                player->GetSession()->sSendListInventory(50009, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+18:
                player->GetSession()->sSendListInventory(50010, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+19:
                player->GetSession()->sSendListInventory(50006, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+20:
                player->GetSession()->sSendListInventory(50004, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+21:
                player->GetSession()->sSendListInventory(50014, creature->GetGUID());
                break;
             case GOSSIP_ACTION_INFO_DEF+22:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "<- �����", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Ƹ����", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+23);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "������", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+24);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "�������", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+25);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "�����", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+26);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "���������", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+27);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "������", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+28);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "���������", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+29);
                player->SEND_GOSSIP_MENU(68, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+23:
                player->GetSession()->sSendListInventory(50017, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+24:
                player->GetSession()->sSendListInventory(50019, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+25:
                player->GetSession()->sSendListInventory(50015, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+26:
                player->GetSession()->sSendListInventory(50016, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+27:
                player->GetSession()->sSendListInventory(50020, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+28:
                player->GetSession()->sSendListInventory(50021, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+29:
                player->GetSession()->sSendListInventory(50018, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+30:
                switch(player->getClass())
                {
                    case 1:
                        player->GetSession()->sSendListInventory(50022, creature->GetGUID());
                    break;
                    case 2:
                        player->GetSession()->sSendListInventory(50023, creature->GetGUID());
                    break;
                    case 3:
                        player->GetSession()->sSendListInventory(50024, creature->GetGUID());
                    break;
                    case 4:
                        player->GetSession()->sSendListInventory(50025, creature->GetGUID());
                    break;
                    case 5:
                        player->GetSession()->sSendListInventory(50026, creature->GetGUID());
                    break;
                    case 6:
                        player->GetSession()->sSendListInventory(50027, creature->GetGUID());
                    break;
                    case 7:
                        player->GetSession()->sSendListInventory(50028, creature->GetGUID());
                    break;
                    case 8:
                        player->GetSession()->sSendListInventory(50029, creature->GetGUID());
                    break;
                    case 9:
                        player->GetSession()->sSendListInventory(50030, creature->GetGUID());
                    break;
                    case 11:
                        player->GetSession()->sSendListInventory(50031, creature->GetGUID());
                    break;
                }
                break;
            case GOSSIP_ACTION_INFO_DEF+31:
                player->GetSession()->sSendListInventory(50035, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+32:
                player->GetSession()->sSendListInventory(50034, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+33:
                player->GetSession()->sSendListInventory(50033, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+34:
                player->GetSession()->sSendListInventory(50036, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+35:
                player->GetSession()->sSendListInventory(50032, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+36:
                player->CLOSE_GOSSIP_MENU();
                if (player->isInCombat())
                {
                    ChatHandler(player).PSendSysMessage("|cfff4b25e�������� ������:|r |cfffcedbb�� � ��� � �� ������ ������������ ���� ������.|r");
                    return true;
                }
                if (player->getPowerType() == POWER_MANA && player->GetHealth() == player->GetMaxHealth() && player->GetPower(POWER_MANA) == player->GetMaxPower(POWER_MANA))
                {
                    ChatHandler(player).PSendSysMessage("|cfff4b25e�������� ������:|r |cfffcedbb���� �������� � ���� - ������.|r");
                    return true;
                }
                if (player->GetHealth() == player->GetMaxHealth())
                {
                    ChatHandler(player).PSendSysMessage("|cfff4b25e�������� ������:|r |cfffcedbb���� �������� - ������.|r");
                    return true;
                }

                if (player->GetNonInCombatTimer() > 29000)
                {
                    creature->CastSpell(player, 24208, true);

                    if (player->getPowerType() == POWER_MANA)
                        player->SetPower(POWER_MANA, player->GetMaxPower(POWER_MANA));
                }
                else
                {
                    uint32 nonCombatTime = (30000 - player->GetNonInCombatTimer()) / 1000;
                    std::string end;
                    end = ending(nonCombatTime, "������.", "�������.", "�������.");
                    ChatHandler(player).PSendSysMessage("|cfff4b25e�������� ������:|r |cfffcedbb�� ������� ���� � ���. � ����� �������� ��� ������ ����� %i %s|r", nonCombatTime, end);
                }
                break;
            case GOSSIP_ACTION_INFO_DEF+37:
                player->GetSession()->sSendListInventory(50037, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+38:
                player->GetSession()->sSendListInventory(50038, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+39:
                player->GetSession()->sSendListInventory(50039, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+40:
                player->GetSession()->sSendListInventory(50040, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+41:
                player->GetSession()->sSendListInventory(50041, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+42:
                player->GetSession()->sSendListInventory(50042, creature->GetGUID());
                break;
        }

        return true;
    }
};

void AddSC_npc_helper()
{
    new npc_helper;
}