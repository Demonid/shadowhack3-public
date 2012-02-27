/* https://bitbucket.org/cemak/renaissance
© Cemak 2011*/

#include "ScriptPCH.h"
#include "Config.h"

class npc_renaissance : public CreatureScript
{
public:
    npc_renaissance() : CreatureScript("npc_renaissance") { }

    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
        if (pCreature->isQuestGiver())
            pPlayer->PrepareQuestMenu(pCreature->GetGUID());

        pCreature->MonsterWhisper("Добро пожаловать на WoW-Circle!", pPlayer->GetGUID(), true);
		
		pPlayer->ADD_GOSSIP_ITEM(0, "Приветствие и основная информация", GOSSIP_SENDER_MAIN, 6); //как начать
		//pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Покупка Сумок"   , GOSSIP_SENDER_MAIN, 2); //Сумки
		
		if ((pPlayer->getClass() == CLASS_MAGE)){
			  pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Купить бесплатно Сет а7 на Мага"  , GOSSIP_SENDER_MAIN, 1); //Сет на мага a7
			  pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Купить бесплатно Нонсет а7 на Мага(Крит)"  , GOSSIP_SENDER_MAIN, 26); //Нонсет на мага a7
			  pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Купить бесплатно Нонсет а7 на Мага(Скорость)"  , GOSSIP_SENDER_MAIN, 27); //Нонсет на мага a7
			 }else if ((pPlayer->getClass() == CLASS_PALADIN))
           {
		      pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Купить бесплатно Сет а7 на Паладина (Возмездие)", GOSSIP_SENDER_MAIN, 4); //Сет на пала дд a7
	          pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Купить бесплатно Сет а7 на Паладина (Свет)", GOSSIP_SENDER_MAIN, 7); //Сет на холи пала a7
			  pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Купить бесплатно Нонсет а7 на Паладина (Возмездие)", GOSSIP_SENDER_MAIN, 45); //Нонсет на ретрика пала a7
			  pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Купить бесплатно Нонсет а7 на Паладина (Свет)", GOSSIP_SENDER_MAIN, 29); //Нонсет  на холи пала a7
		   }else if ((pPlayer->getClass() == CLASS_HUNTER))
           {
	          pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Купить бесплатно Сет а7 на Охотника", GOSSIP_SENDER_MAIN, 8); //Нонсет Сет на ханта a7
			  pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Купить бесплатно Нонсет а7 на Охотника", GOSSIP_SENDER_MAIN, 30); //Нонсет Сет на ханта a7
		   }else if ((pPlayer->getClass() == CLASS_DRUID))
           {
		      pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Купить бесплатно Сет а7 на Друида (Исцеление)", GOSSIP_SENDER_MAIN, 9); //Сет на друида хила a7
		      pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Купить бесплатно Сет а7 на Друида (Сила зверя)", GOSSIP_SENDER_MAIN, 10); //Сет на друида дд a7
	          pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Купить бесплатно Сет а7 на Друида (Баланс)", GOSSIP_SENDER_MAIN, 11); //Сет на друида рдд a7
			  pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Купить бесплатно Нонсет а7 на Друида (Исцеление)", GOSSIP_SENDER_MAIN, 31); //Нонсет  на друида хила a7
		      pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Купить бесплатно Нонсет а7 на Друида (Сила зверя)", GOSSIP_SENDER_MAIN, 32); //Нонсет на друида дд a7
	          pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Купить бесплатно Нонсет а7 на Друида (Баланс)", GOSSIP_SENDER_MAIN, 33); //Нонсет на друида рдд a7
		   }else if ((pPlayer->getClass() == CLASS_WARRIOR))
           {
	          pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Купить бесплатно Сет а7 на Война", GOSSIP_SENDER_MAIN, 12); //Сет на вара a7
			  pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Купить бесплатно Нонсет а7 на Война", GOSSIP_SENDER_MAIN, 34); //Нонсет на вара a7
		   }else if ((pPlayer->getClass() == CLASS_WARLOCK))
           {
	          pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Купить бесплатно Сет а7 на Чернокнижника", GOSSIP_SENDER_MAIN, 13); //Сет на лока a7
			  pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Купить бесплатно Нонсет а7 на Чернокнижника(На крит)", GOSSIP_SENDER_MAIN, 35); //Нонсет на лока a7
			  pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Купить бесплатно Нонсет а7 на Чернокнижника(На скорость)", GOSSIP_SENDER_MAIN, 36); //Нонсет на лока a7
		   }else if ((pPlayer->getClass() == CLASS_SHAMAN))
           {
	          pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Купить бесплатно Сет а7 на Шамана (Исцеление)", GOSSIP_SENDER_MAIN, 14); //Сет на шамана хила a7
	          pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Купить бесплатно Сет а7 на Шамана (Совершенствование)", GOSSIP_SENDER_MAIN, 15); //Сет на шамана рд a7
	          pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Купить бесплатно Сет а7 на Шамана (Стихия)", GOSSIP_SENDER_MAIN, 16); //Сет на шамана рдд a7
			  pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Купить бесплатно Нонсет а7 на Шамана (Исцеление)", GOSSIP_SENDER_MAIN, 37); //Нонсет на шамана хила a7
	          pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Купить бесплатно Нонсет а7 на Шамана (Совершенствование)", GOSSIP_SENDER_MAIN, 38); //Нонсет на шамана рд a7
	          pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Купить бесплатно Нонсет а7 на Шамана (Стихия)", GOSSIP_SENDER_MAIN, 39); //Нонсет на шамана рдд a7
		   }else if ((pPlayer->getClass() == CLASS_ROGUE))
           {
	          pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Купить бесплатно Сет а7 на Разбойника", GOSSIP_SENDER_MAIN, 17); //Сет на рогу a7
			  pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Купить бесплатно Нонсет а7 на Разбойника", GOSSIP_SENDER_MAIN, 40); //Нонсет на рогу a7
		   }else if ((pPlayer->getClass() == CLASS_PRIEST))
           {
	          pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Купить бесплатно Сет а7 на Жреца (Темная магия)", GOSSIP_SENDER_MAIN, 18); //Сет на приста ШП a7
	          pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Купить бесплатно Сет а7 на Жреца (Свет)", GOSSIP_SENDER_MAIN, 19); //Сет на приста свет a7
			  pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Купить бесплатно Нонсет а7 на Жреца (На крит)", GOSSIP_SENDER_MAIN, 41); //Нонсет на приста ШП a7
	          pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Купить бесплатно Нонсет а7 на Жреца (На скорость)", GOSSIP_SENDER_MAIN, 42); //Нонсет на приста свет a7
			  pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Купить бесплатно Нонсет а7 на Жреца (Свет)", GOSSIP_SENDER_MAIN, 43); //Нонсет на приста свет a7
		   }else if ((pPlayer->getClass() == CLASS_DEATH_KNIGHT))
           {
	          pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Купить бесплатно Сет а7 на Рыцаря смерти", GOSSIP_SENDER_MAIN, 20); //Сет на дк a7
			  pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Купить бесплатно Нонсет а7 на Рыцаря смерти", GOSSIP_SENDER_MAIN, 44); //Нонсет на дк a7
		   }
		   
		   //pPlayer->ADD_GOSSIP_ITEM(9, "Вылечи меня!"                     , GOSSIP_SENDER_MAIN, 3);
		   //pPlayer->ADD_GOSSIP_ITEM(5, "Обучить верховую езду на максимум", GOSSIP_SENDER_MAIN, 21); //Верховая езда
		   //pPlayer->ADD_GOSSIP_ITEM(9, "Обучить мои навыки защиты и оружия на максимум", GOSSIP_SENDER_MAIN, 23); //Навык макс.
	       pPlayer->ADD_GOSSIP_ITEM(7, "[Меню]Телепорта", GOSSIP_SENDER_MAIN, 5); 
           pPlayer->ADD_GOSSIP_ITEM(7, "[Меню]Баффов" , GOSSIP_SENDER_MAIN, 24);//Баффер 
		   if (pPlayer->GetTeam() == ALLIANCE ) {
			  pPlayer->ADD_GOSSIP_ITEM(5, "Телепорт в стартовую локацию", GOSSIP_SENDER_MAIN, 9991);
		   }else {
			  pPlayer->ADD_GOSSIP_ITEM(5, "Телепорт в стартовую локацию"     , GOSSIP_SENDER_MAIN, 9992);
		   }
		   pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Телепорт в DUEL ZONE", GOSSIP_SENDER_MAIN, 9993);
           //pPlayer->ADD_GOSSIP_ITEM(7, "[Меню]Превращений", GOSSIP_SENDER_MAIN, 46);	   
           //pPlayer->ADD_GOSSIP_ITEM(0, "Кто тебя создал ?", GOSSIP_SENDER_MAIN, 25); //кто тебя создал ?		   
         
        pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
    {
        pPlayer->PlayerTalkClass->ClearMenus();
        switch(uiAction)
      {
	    case 1:
	  	pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Купить бесплатно Сет а7_2 Level (251) на мага"  , GOSSIP_SENDER_MAIN, 1000); //Сет на мага a7
		
		pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
		
		break;
		
		case 2:
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Покупка_2 Сумок"   , GOSSIP_SENDER_MAIN, 1001); //Сумки
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;
	   
	   case 3:
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Купить бесплатно Сет а7 Level (251) на Шамана (Исцеление)"   , GOSSIP_SENDER_MAIN, 1002); //Сумки
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;
	   
	   case 4:
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Покупка_2 Сумок"   , GOSSIP_SENDER_MAIN, 1005); //Сумки
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;
	   
	   case 5:
		if (pPlayer->GetTeam() == ALLIANCE ) {
            pPlayer->ADD_GOSSIP_ITEM(5, "Пиратская Бухта."                 , GOSSIP_SENDER_MAIN, 4035);
            pPlayer->ADD_GOSSIP_ITEM(5, "Дарнасс."                         , GOSSIP_SENDER_MAIN, 1203);
            pPlayer->ADD_GOSSIP_ITEM(5, "Экзодар."                         , GOSSIP_SENDER_MAIN, 1216);
            pPlayer->ADD_GOSSIP_ITEM(5, "Штормград."                       , GOSSIP_SENDER_MAIN, 1206);
            pPlayer->ADD_GOSSIP_ITEM(5, "Стальгорн."                       , GOSSIP_SENDER_MAIN, 1224);
            pPlayer->ADD_GOSSIP_ITEM(5, "Гномреган."                       , GOSSIP_SENDER_MAIN, 1222);
            pPlayer->ADD_GOSSIP_ITEM(5, "Шаттрат."                         , GOSSIP_SENDER_MAIN, 1287);
            pPlayer->ADD_GOSSIP_ITEM(5, "Даларан."                         , GOSSIP_SENDER_MAIN, 1205);
            pPlayer->ADD_GOSSIP_ITEM(5, "Остров Кель'Данас."               , GOSSIP_SENDER_MAIN, 1288);
            if (sConfig->GetIntDefault("RealmID", 0) == 5)
            {
                pPlayer->ADD_GOSSIP_ITEM(5, "Стартовая локация."           , GOSSIP_SENDER_MAIN, 4039);
                pPlayer->ADD_GOSSIP_ITEM(5, "Арена награнда."              , GOSSIP_SENDER_MAIN, 4040);
            }
            pPlayer->ADD_GOSSIP_ITEM(7, "[Инстансы] ->"                    , GOSSIP_SENDER_MAIN, 5550);
            pPlayer->ADD_GOSSIP_ITEM(7, "[Инстансы WotLK] ->"              , GOSSIP_SENDER_MAIN, 5554);

        }  else {
            pPlayer->ADD_GOSSIP_ITEM(5, "Пиратская Бухта."                 , GOSSIP_SENDER_MAIN, 4035);
            pPlayer->ADD_GOSSIP_ITEM(5, "Оргриммар."                       , GOSSIP_SENDER_MAIN, 1215);
            pPlayer->ADD_GOSSIP_ITEM(5, "Луносвет."                        , GOSSIP_SENDER_MAIN, 1217);
            pPlayer->ADD_GOSSIP_ITEM(5, "Подгород."                        , GOSSIP_SENDER_MAIN, 1213);
            pPlayer->ADD_GOSSIP_ITEM(5, "Громовой утёс."                   , GOSSIP_SENDER_MAIN, 1225);
            pPlayer->ADD_GOSSIP_ITEM(5, "Гномреган."                       , GOSSIP_SENDER_MAIN, 1222);
            pPlayer->ADD_GOSSIP_ITEM(5, "Шаттрат."                         , GOSSIP_SENDER_MAIN, 1287);
            pPlayer->ADD_GOSSIP_ITEM(5, "Даларан."                         , GOSSIP_SENDER_MAIN, 1205);
            pPlayer->ADD_GOSSIP_ITEM(5, "Остров Кель'Данас."               , GOSSIP_SENDER_MAIN, 1288);
            if (sConfig->GetIntDefault("RealmID", 0) == 5)
            {
                pPlayer->ADD_GOSSIP_ITEM(5, "Стартовая локация."           , GOSSIP_SENDER_MAIN, 4039);
                pPlayer->ADD_GOSSIP_ITEM(5, "Арена награнда."              , GOSSIP_SENDER_MAIN, 4040);
            }
            pPlayer->ADD_GOSSIP_ITEM(7, "[Инстансы] ->"                    , GOSSIP_SENDER_MAIN, 5550);
            pPlayer->ADD_GOSSIP_ITEM(7, "[Инстансы WotLK] ->"              , GOSSIP_SENDER_MAIN, 5554);
        }
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;
	   
	   case 6:
		pPlayer->CLOSE_GOSSIP_MENU();
		pCreature->MonsterWhisper("Приветствую тебя, странник, на нашем сервере WoW-Circle: WoTLK Battle. Только у нас ты сможешь понять, что такое настоящая и качественная игра! У тебя в рюкзаке есть небольшая инструкция, прочитай её - она тебе поможет. Приятной игры!", pPlayer->GetGUID(), true);
       break;
/*	   case 6:
		pPlayer->ADD_GOSSIP_ITEM(0, "Приветствие и основная информация"   , GOSSIP_SENDER_MAIN, 1003); //Сумки
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;*/
	   
	   case 7:
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Покупка_2 Сумок"   , GOSSIP_SENDER_MAIN, 1006); //Сумки
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;
	   
	   case 8:
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Покупка_2 Сумок"   , GOSSIP_SENDER_MAIN, 1007); //Сумки*/
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;
	   
	   case 9:
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Покупка_2 Сумок"   , GOSSIP_SENDER_MAIN, 1008); //Сумки
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;
	   
	   case 10:
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Покупка_2 Сумок"   , GOSSIP_SENDER_MAIN, 1009); //Сумки
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;
	   
	   case 11:
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Покупка_2 Сумок"   , GOSSIP_SENDER_MAIN, 1010); //Сумки
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;
	   
	   case 12:
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Покупка_2 Сумок"   , GOSSIP_SENDER_MAIN, 1011); //Сумки
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;
	   
	   case 13:
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Покупка_2 Сумок"   , GOSSIP_SENDER_MAIN, 1012); //Сумки
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;
	   
	   case 14:
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Покупка_2 Сумок"   , GOSSIP_SENDER_MAIN, 1013); //Сумки
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;
	   
	   case 15:
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Покупка_2 Сумок"   , GOSSIP_SENDER_MAIN, 1014); //Сумки
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;
	   
	   case 16:
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Покупка_2 Сумок"   , GOSSIP_SENDER_MAIN, 1015); //Сумки
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;
	   
	   case 17:
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Покупка_2 Сумок"   , GOSSIP_SENDER_MAIN, 1016); //Сумки
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;
	   
	   case 18:
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Покупка_2 Сумок"   , GOSSIP_SENDER_MAIN, 1017); //Сумки
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;
	   
	   case 19:
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Покупка_2 Сумок"   , GOSSIP_SENDER_MAIN, 1018); //Сумки
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;
	   
	   case 20:
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Покупка_2 Сумок"   , GOSSIP_SENDER_MAIN, 1019); //Сумки
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;
	   
	    case 21:
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Покупка_2 Сумок"   , GOSSIP_SENDER_MAIN, 1020); //Сумки
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;
	   
	   case 22:
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Покупка_2 Сумок"   , GOSSIP_SENDER_MAIN, 1021); //Сумки
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;
	   
	   case 23:
	   pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Покупка_2 Сумок"   , GOSSIP_SENDER_MAIN, 1022); //Сумки
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;
	   
	   case 24:
		pPlayer->ADD_GOSSIP_ITEM(0, "[Бафф]Слово силы: Стойкость, Ранк 8", GOSSIP_SENDER_MAIN, 4000);
   				 pPlayer->ADD_GOSSIP_ITEM(0, "[Бафф]Великое благословение королей", GOSSIP_SENDER_MAIN, 4001);
        	     pPlayer->ADD_GOSSIP_ITEM(0, "[Бафф]Великое благословение могущества", GOSSIP_SENDER_MAIN,4002);
    			 pPlayer->ADD_GOSSIP_ITEM(0, "[Бафф]Великое благословение мудрости", GOSSIP_SENDER_MAIN, 4003);
    			 pPlayer->ADD_GOSSIP_ITEM(0, "[Бафф]Знак дикой природы, Ранк 9", GOSSIP_SENDER_MAIN, 4004);
    			 pPlayer->ADD_GOSSIP_ITEM(0, "[Бафф]Чародейский интеллект, Ранк 7", GOSSIP_SENDER_MAIN, 4005);
   				 pPlayer->ADD_GOSSIP_ITEM(0, "[Бафф]Шипы, Ранк 8", GOSSIP_SENDER_MAIN, 6007);
  				 pPlayer->ADD_GOSSIP_ITEM(0, "[Бафф]Божественный дух, Ранк 8", GOSSIP_SENDER_MAIN, 6008);
   				 pPlayer->ADD_GOSSIP_ITEM(0, "[Бафф]Защита от темной магии, Ранк 5", GOSSIP_SENDER_MAIN, 6009);	
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;
	   
	   case 25:
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Покупка_2 Сумок"   , GOSSIP_SENDER_MAIN, 1024); //Сумки
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;
	   
	   case 26:
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Покупка_2 Сумок"   , GOSSIP_SENDER_MAIN, 1025); //Сумки
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;
	   
	   case 27:
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Покупка_2 Сумок"   , GOSSIP_SENDER_MAIN, 1026); //Сумки
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;
	   
	   case 28:
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Покупка_2 Сумок"   , GOSSIP_SENDER_MAIN, 1027); //Сумки
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;
	   
	   case 45:
	   pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Покупка_2 Сумок"   , GOSSIP_SENDER_MAIN, 1028); //Сумки
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;
	   
	   case 29:
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Покупка_2 Сумок"   , GOSSIP_SENDER_MAIN, 1029); //Сумки
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;
	   
	   case 30:
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Покупка_2 Сумок"   , GOSSIP_SENDER_MAIN, 1030); //Сумки
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;
	   
	   case 31:
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Покупка_2 Сумок"   , GOSSIP_SENDER_MAIN, 1031); //Сумки
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;
	   
	   case 32:
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Покупка_2 Сумок"   , GOSSIP_SENDER_MAIN, 1032); //Сумки
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;
	   
	   case 33:
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Покупка_2 Сумок"   , GOSSIP_SENDER_MAIN, 1033); //Сумки
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;
	   
	   case 34:
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Покупка_2 Сумок"   , GOSSIP_SENDER_MAIN, 1034); //Сумки
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;
	   
	   case 35:
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Покупка_2 Сумок"   , GOSSIP_SENDER_MAIN, 1035); //Сумки
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;
	   
	   case 36:
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Покупка_2 Сумок"   , GOSSIP_SENDER_MAIN, 1036); //Сумки
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;
	   
	    case 37:
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Покупка_2 Сумок"   , GOSSIP_SENDER_MAIN, 1037); //Сумки
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;
	   
	    case 38:
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Покупка_2 Сумок"   , GOSSIP_SENDER_MAIN, 1038); //Сумки
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;
	   
	    case 39:
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Покупка_2 Сумок"   , GOSSIP_SENDER_MAIN, 1039); //Сумки
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;
	   
	   case 40:
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Покупка_2 Сумок"   , GOSSIP_SENDER_MAIN, 1040); //Сумки
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;
	   
	   case 41:
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Покупка_2 Сумок"   , GOSSIP_SENDER_MAIN, 1041); //Сумки
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;
	   
	   case 42:
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Покупка_2 Сумок"   , GOSSIP_SENDER_MAIN, 1042); //Сумки
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;
	   
	   case 43:
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Покупка_2 Сумок"   , GOSSIP_SENDER_MAIN, 1043); //Сумки
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;
	   
	   case 44:
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Покупка_2 Сумок"   , GOSSIP_SENDER_MAIN, 1044); //Сумки
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;
	   
	   case 46:
    pPlayer->ADD_GOSSIP_ITEM(4, "Иллидан", GOSSIP_SENDER_MAIN, 500);
    pPlayer->ADD_GOSSIP_ITEM(4, "Кил'джеден", GOSSIP_SENDER_MAIN, 501);
    pPlayer->ADD_GOSSIP_ITEM(4, "Акама", GOSSIP_SENDER_MAIN, 502);
    pPlayer->ADD_GOSSIP_ITEM(4, "Рыцарь смерти", GOSSIP_SENDER_MAIN, 503);
    pPlayer->ADD_GOSSIP_ITEM(4, "Таурен", GOSSIP_SENDER_MAIN, 504);
    pPlayer->ADD_GOSSIP_ITEM(4, "Нежить", GOSSIP_SENDER_MAIN, 505);
    pPlayer->ADD_GOSSIP_ITEM(4, "Человек", GOSSIP_SENDER_MAIN, 506);
    pPlayer->ADD_GOSSIP_ITEM(4, "Король Лич", GOSSIP_SENDER_MAIN, 507);
    pPlayer->ADD_GOSSIP_ITEM(4, "Тирион", GOSSIP_SENDER_MAIN, 508);
    pPlayer->ADD_GOSSIP_ITEM(4, "Утер", GOSSIP_SENDER_MAIN, 509);
    pPlayer->ADD_GOSSIP_ITEM(4, "Артас", GOSSIP_SENDER_MAIN, 510);
	///////////// From SPGM
	pPlayer->ADD_GOSSIP_ITEM(4, "Алгалон", GOSSIP_SENDER_MAIN, 711);
	pPlayer->ADD_GOSSIP_ITEM(4, "Судьболом", GOSSIP_SENDER_MAIN, 712);
	pPlayer->ADD_GOSSIP_ITEM(4, "Владыка Судеб Каззак", GOSSIP_SENDER_MAIN, 713);
	pPlayer->ADD_GOSSIP_ITEM(4, "Ониксия", GOSSIP_SENDER_MAIN, 714);
	pPlayer->ADD_GOSSIP_ITEM(4, "Таддиус", GOSSIP_SENDER_MAIN, 715);
	pPlayer->ADD_GOSSIP_ITEM(4, "Глут", GOSSIP_SENDER_MAIN, 716);
	pPlayer->ADD_GOSSIP_ITEM(4, "Мексна", GOSSIP_SENDER_MAIN, 717);
	pPlayer->ADD_GOSSIP_ITEM(4, "Сапфирион", GOSSIP_SENDER_MAIN, 718);
	pPlayer->ADD_GOSSIP_ITEM(4, "Нот Чумной", GOSSIP_SENDER_MAIN, 719);
	pPlayer->ADD_GOSSIP_ITEM(4, "Кель'Тузед", GOSSIP_SENDER_MAIN, 720);
	pPlayer->ADD_GOSSIP_ITEM(4, "Кель'тас Солнечный Скиталец", GOSSIP_SENDER_MAIN, 721);
	pPlayer->ADD_GOSSIP_ITEM(4, "К'Тун", GOSSIP_SENDER_MAIN, 722);
	pPlayer->ADD_GOSSIP_ITEM(4, "Тралл", GOSSIP_SENDER_MAIN, 723);
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
		 break;
		 
         case 1000: //сет на мага
	   pPlayer->CLOSE_GOSSIP_MENU();
	   pPlayer->AddItem(41947, 1);
	   pPlayer->AddItem(41966, 1);
	   pPlayer->AddItem(41954, 1);
	   pPlayer->AddItem(41972, 1);
	   pPlayer->AddItem(41960, 1);
	   break;
	   
       case 1001: //сумки
		pPlayer->CLOSE_GOSSIP_MENU();
		pPlayer->AddItem(23162, 4);
		break;
		
		case 1002: // Heal me!
		pPlayer->CLOSE_GOSSIP_MENU();
                if (pPlayer->HasAura(45523) )
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Я больше не могу - это сделать.", LANG_UNIVERSAL, NULL);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->CastSpell(pPlayer, 39321, true);
                    pPlayer->CastSpell(pPlayer, 45523, true);
                }
                break;
		 
  /*      case 1003:
		pPlayer->CLOSE_GOSSIP_MENU();
		pCreature->MonsterWhisper("Приветствую тебя, странник, на нашем сервере WoW-Circle: WoTLK Battle. Только у нас ты сможешь понять, что такое настоящая и качественная игра! У вас в рюкзаке есть небольшая инструкция, прочитайте её - она вам поможет. Приятной игры!", pPlayer->GetGUID(), false);
		 break;*/
		 
		 case 1005://Сет на ретри пала a7
		 pPlayer->CLOSE_GOSSIP_MENU();
		 pPlayer->AddItem(40831, 1);
		 pPlayer->AddItem(40872, 1);
		 pPlayer->AddItem(40792, 1);
		 pPlayer->AddItem(40812, 1);
		 pPlayer->AddItem(40852, 1);
		 break;
		 
         case 1006://Сет на холи пала a7
		 pPlayer->CLOSE_GOSSIP_MENU();
		 pPlayer->AddItem(40934, 1);
		 pPlayer->AddItem(40964, 1);
		 pPlayer->AddItem(40910, 1);
		 pPlayer->AddItem(40928, 1);
		 pPlayer->AddItem(40940, 1);
		 break;
		 
		 case 1007: //Сет на ханта a7
		 pPlayer->CLOSE_GOSSIP_MENU();
		 pPlayer->AddItem(41158, 1);
		 pPlayer->AddItem(41218, 1);
		 pPlayer->AddItem(41088, 1);
		 pPlayer->AddItem(41144, 1);
		 pPlayer->AddItem(41206, 1);
		 break;
		 
		 case 1008://Сет на друида хилла a7
		 pPlayer->CLOSE_GOSSIP_MENU();
		 pPlayer->AddItem(41322, 1);
		 pPlayer->AddItem(41276, 1);
		 pPlayer->AddItem(41311, 1);
		 pPlayer->AddItem(41288, 1);
		 pPlayer->AddItem(41299, 1);
		 break;
		 
         case 1009://Сет на друида дд a7
		 pPlayer->CLOSE_GOSSIP_MENU();
		 pPlayer->AddItem(41679, 1);
		 pPlayer->AddItem(41716, 1);
		 pPlayer->AddItem(41662, 1);
		 pPlayer->AddItem(41774, 1);
		 pPlayer->AddItem(41668, 1);
		 break;
		 
         case 1010://Сет на друида рдд a7
		 pPlayer->CLOSE_GOSSIP_MENU();
		 pPlayer->AddItem(41328, 1);
		 pPlayer->AddItem(41282, 1);
		 pPlayer->AddItem(41317, 1);
		 pPlayer->AddItem(41294, 1);
		 pPlayer->AddItem(41305, 1);
		 break;
		 
		 case 1011://Сет на вара a7
		 pPlayer->CLOSE_GOSSIP_MENU();
		 pPlayer->AddItem(40829, 1);
		 pPlayer->AddItem(40870, 1);
		 pPlayer->AddItem(40790, 1);
		 pPlayer->AddItem(40810, 1);
		 pPlayer->AddItem(40850, 1);
		 break;
		 
		 case 1012://Сет на лока a7
		 pPlayer->CLOSE_GOSSIP_MENU();
		 pPlayer->AddItem(41994, 1);
		 pPlayer->AddItem(42012, 1);
		 pPlayer->AddItem(41999, 1);
		 pPlayer->AddItem(42018, 1);
		 pPlayer->AddItem(42006, 1);
		 break;
		 
        case 1013://Сет на шамана хила a7
		 pPlayer->CLOSE_GOSSIP_MENU();
		 pPlayer->AddItem(41014, 1);
		 pPlayer->AddItem(41039, 1);
		 pPlayer->AddItem(40994, 1);
		 pPlayer->AddItem(41002, 1);
		 pPlayer->AddItem(41028, 1);
		 break;
		 
         case 1014://Сет на шамана дд a7
		 pPlayer->CLOSE_GOSSIP_MENU();
		 pPlayer->AddItem(41152, 1);
		 pPlayer->AddItem(41212, 1);
		 pPlayer->AddItem(41082, 1);
		 pPlayer->AddItem(41138, 1);
		 pPlayer->AddItem(41200, 1);
		 break;
		 
         case 1015://Сет на шамана рдд a7
		 pPlayer->CLOSE_GOSSIP_MENU();
		 pPlayer->AddItem(41020, 1);
		 pPlayer->AddItem(41045, 1);
		 pPlayer->AddItem(40995, 1);
		 pPlayer->AddItem(41008, 1);
		 pPlayer->AddItem(41034, 1);
		 break;	

         case 1016: //Сет на рогу a7
		  pPlayer->CLOSE_GOSSIP_MENU();
		  pPlayer->AddItem(41673, 1);
		  pPlayer->AddItem(41684, 1);
		  pPlayer->AddItem(41651, 1);
		  pPlayer->AddItem(41768, 1);
		  pPlayer->AddItem(41656, 1);
		  break;
		  
          case 1017://Сет на приста ШП a7
	  pPlayer->CLOSE_GOSSIP_MENU();
	  pPlayer->AddItem(41916, 1);
	  pPlayer->AddItem(41935, 1);
	  pPlayer->AddItem(41922, 1);
	  pPlayer->AddItem(41941, 1);
	  pPlayer->AddItem(41928, 1);
	  break;
	  
      case 1018: //Сет на приста свет a7
	  pPlayer->CLOSE_GOSSIP_MENU();
	  pPlayer->AddItem(41855, 1);
	  pPlayer->AddItem(41870, 1);
	  pPlayer->AddItem(41860, 1);
	  pPlayer->AddItem(41875, 1);
	  pPlayer->AddItem(41865, 1);
	  break;
	  
     case 1019: //сет на дк
	 pPlayer->CLOSE_GOSSIP_MENU();
	 pPlayer->AddItem(40830, 1);
	 pPlayer->AddItem(40871, 1);
	 pPlayer->AddItem(40791, 1);
	 pPlayer->AddItem(40811, 1);
	 pPlayer->AddItem(40851, 1);
	 break;
	
     case 1020: //Верховая езда
	 pPlayer->CLOSE_GOSSIP_MENU();
		      {
		        pPlayer->learnSpell(33388, false);
		        pPlayer->learnSpell(33391, false);
		        pPlayer->learnSpell(34090, false);
		        pPlayer->learnSpell(34091, false);
		        pPlayer->learnSpell(54197, false);
		      }	
			  return true;
	
	case 1022:
	pPlayer->CLOSE_GOSSIP_MENU();
		pPlayer->UpdateSkillsToMaxSkillsForLevel();
		pCreature->MonsterWhisper("Вы успешно приобрели навыки защиты и оружия.", pPlayer->GetGUID(), false);
		break;
		
	case 1025://маг крита
	pPlayer->CLOSE_GOSSIP_MENU();
	pPlayer->AddItem(41910, 1);
	pPlayer->AddItem(41899, 1);
	pPlayer->AddItem(41904, 1);
	pPlayer->AddItem(42043, 1);  //crit spd
	pPlayer->AddItem(42076, 1);
	break;
	
	case 1026://Маг скорость
	pPlayer->CLOSE_GOSSIP_MENU();
	pPlayer->AddItem(49181, 1);
	pPlayer->AddItem(49179, 1);
	pPlayer->AddItem(49183, 1);
	pPlayer->AddItem(42045, 1); //hast spd
	pPlayer->AddItem(42077, 1);

	break;
	
	case 1028://Пал возмездие
	pPlayer->CLOSE_GOSSIP_MENU();
	pPlayer->AddItem(40890, 1);
	pPlayer->AddItem(40883, 1);
	pPlayer->AddItem(40884, 1);
	pPlayer->AddItem(42041, 1);
	pPlayer->AddItem(42082, 1);
	break;
	
	case 1029://Пал хилл
	pPlayer->CLOSE_GOSSIP_MENU();
	pPlayer->AddItem(40984, 1);
	pPlayer->AddItem(40978, 1);
	pPlayer->AddItem(40979, 1);
	pPlayer->AddItem(42047, 1); //mp5 spd
	pPlayer->AddItem(42079, 1);
	break;
	
	case 1030://хант
	pPlayer->CLOSE_GOSSIP_MENU();
	pPlayer->AddItem(41226, 1);
	pPlayer->AddItem(41236, 1);
	pPlayer->AddItem(41231, 1);
	pPlayer->AddItem(42041, 1);
	pPlayer->AddItem(42082, 1);
	break;
	
	case 1031://дру хилл
	pPlayer->CLOSE_GOSSIP_MENU();
	pPlayer->AddItem(41626, 1);
	pPlayer->AddItem(41618, 1);
	pPlayer->AddItem(41622, 1);
	pPlayer->AddItem(42046, 1); //spirit spd
	pPlayer->AddItem(42080, 1);
	break;
	
	case 1032://дру дд
	pPlayer->CLOSE_GOSSIP_MENU();
	pPlayer->AddItem(41841, 1);
	pPlayer->AddItem(41833, 1);
	pPlayer->AddItem(41837, 1);
	pPlayer->AddItem(46374, 1);
	pPlayer->AddItem(42082, 1);
	break;
	
	case 1033://дру рдд
	pPlayer->CLOSE_GOSSIP_MENU();
	pPlayer->AddItem(41641, 1);
	pPlayer->AddItem(41631, 1);
	pPlayer->AddItem(41636, 1);
	pPlayer->AddItem(42045, 1); //hast spd
	pPlayer->AddItem(42077, 1);
	break;
	
	case 1034://вар
	pPlayer->CLOSE_GOSSIP_MENU();
	pPlayer->AddItem(40890, 1);
	pPlayer->AddItem(40883, 1);
	pPlayer->AddItem(40884, 1);
	pPlayer->AddItem(46374, 1);
	pPlayer->AddItem(42082, 1);
	break;
	
	case 1035://лок крита
	pPlayer->CLOSE_GOSSIP_MENU();
	pPlayer->AddItem(41910, 1);
	pPlayer->AddItem(41899, 1);
	pPlayer->AddItem(41904, 1);
	pPlayer->AddItem(42043, 1);  //crit spd
	pPlayer->AddItem(42076, 1);
	break;
	
	case 1036://лок скорость
	pPlayer->CLOSE_GOSSIP_MENU();
	pPlayer->AddItem(49181, 1);
	pPlayer->AddItem(49179, 1);
	pPlayer->AddItem(49183, 1);
	pPlayer->AddItem(42045, 1); //hast spd
	pPlayer->AddItem(42077, 1);
	break;
	
	case 1037://Шаман хил
	pPlayer->CLOSE_GOSSIP_MENU();
	pPlayer->AddItem(41061, 1);
	pPlayer->AddItem(41052, 1);
	pPlayer->AddItem(41056, 1);
	pPlayer->AddItem(42047, 1); //mp5 spd
	pPlayer->AddItem(42079, 1);
	break;
	
	case 1038://шаман дд
	pPlayer->CLOSE_GOSSIP_MENU();
	pPlayer->AddItem(41226, 1);
	pPlayer->AddItem(41236, 1);
	pPlayer->AddItem(41231, 1);
	pPlayer->AddItem(46374, 1);
	pPlayer->AddItem(42082, 1);
	break;
	
	case 1039://шаман рдд
	pPlayer->CLOSE_GOSSIP_MENU();
	pPlayer->AddItem(41066, 1);
	pPlayer->AddItem(41071, 1);
	pPlayer->AddItem(41076, 1);
	pPlayer->AddItem(42045, 1); //hast spd
	pPlayer->AddItem(42077, 1);
	break;
	
	case 1040://рога
	pPlayer->CLOSE_GOSSIP_MENU();
	pPlayer->AddItem(41841, 1);
	pPlayer->AddItem(41833, 1);
	pPlayer->AddItem(41837, 1);
	pPlayer->AddItem(46374, 1);
	pPlayer->AddItem(42082, 1);
	break;
	
	case 1041://прист крита
	pPlayer->CLOSE_GOSSIP_MENU();
	pPlayer->AddItem(41910, 1);
	pPlayer->AddItem(41899, 1);
	pPlayer->AddItem(41904, 1);
	pPlayer->AddItem(42043, 1);  //crit spd
	pPlayer->AddItem(42076, 1);
	break;
	
	case 1042://прист скорость
	pPlayer->CLOSE_GOSSIP_MENU();
	pPlayer->AddItem(49181, 1);
	pPlayer->AddItem(49179, 1);
	pPlayer->AddItem(49183, 1);
	pPlayer->AddItem(42045, 1); //hast spd
	pPlayer->AddItem(42077, 1);
	break;
	
	case 1043://прист хилл
	pPlayer->CLOSE_GOSSIP_MENU();
	pPlayer->AddItem(41894, 1);
	pPlayer->AddItem(41882, 1);
	pPlayer->AddItem(41886, 1);
	pPlayer->AddItem(42046, 1); //spirit spd
	pPlayer->AddItem(42080, 1);
	break;
	
	case 1044://дк
	pPlayer->CLOSE_GOSSIP_MENU();
	pPlayer->AddItem(40890, 1);
	pPlayer->AddItem(40883, 1);
	pPlayer->AddItem(40884, 1);
	pPlayer->AddItem(42041, 1);
	pPlayer->AddItem(42082, 1);
	break;
	
	case 4000:
	        pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->CastSpell(pPlayer, 48161, false);
            break;
 
        case 4001:
		pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->CastSpell(pPlayer, 25898, false);
            break;
 
        case 4002:
		pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->CastSpell(pPlayer, 48934, false);
            break;
 
        case 4003:
		pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->CastSpell(pPlayer, 48938, false);
            break;
 
        case 4004:
		pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->CastSpell(pPlayer, 48469, false);
            break;                              
                
                case 4005:
				pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->CastSpell(pPlayer, 42995, false);
            break;
 
                case 6007:
				pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->CastSpell(pPlayer, 53307, false);
            break;
 
                case 6008:
				pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->CastSpell(pPlayer, 48073, false);
            break;
 
                case 6009:
				pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->CastSpell(pPlayer, 48169, false);
            break;
		
        case 1024:
		pPlayer->CLOSE_GOSSIP_MENU();
        pCreature->MonsterWhisper("(c)Twink, thanks to Cemak.> ", pPlayer->GetGUID(), false);		
       break;
	   
	   case 5550: //Instances
                pPlayer->ADD_GOSSIP_ITEM(5, "Огненная пропасть."            , GOSSIP_SENDER_MAIN, 1248);
                pPlayer->ADD_GOSSIP_ITEM(5, "Пещеры стенаний."              , GOSSIP_SENDER_MAIN, 1249);
                pPlayer->ADD_GOSSIP_ITEM(5, "Тюрьма."                       , GOSSIP_SENDER_MAIN, 1253);
                pPlayer->ADD_GOSSIP_ITEM(5, "Мертвые копи."                 , GOSSIP_SENDER_MAIN, 1250);
                pPlayer->ADD_GOSSIP_ITEM(5, "Крепость Темного Клыка."       , GOSSIP_SENDER_MAIN, 1251);
                pPlayer->ADD_GOSSIP_ITEM(5, "Непроглядная Пучина."          , GOSSIP_SENDER_MAIN, 1252);
                pPlayer->ADD_GOSSIP_ITEM(5, "Лабиринты Иглошкурых."         , GOSSIP_SENDER_MAIN, 1254);
                pPlayer->ADD_GOSSIP_ITEM(5, "Курганы Иглошкурых."           , GOSSIP_SENDER_MAIN, 1256);
                pPlayer->ADD_GOSSIP_ITEM(5, "Монастырь Алого Ордена."       , GOSSIP_SENDER_MAIN, 1257);
                pPlayer->ADD_GOSSIP_ITEM(5, "Аукиндон."                     , GOSSIP_SENDER_MAIN, 4038);
                pPlayer->ADD_GOSSIP_ITEM(7, "[Ещё] ->"                      , GOSSIP_SENDER_MAIN, 5551);
                pPlayer->ADD_GOSSIP_ITEM(7, "<- [Главное меню]"             , GOSSIP_SENDER_MAIN, 724);

                pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());

                break;

            case 5551: //More Instances
                pPlayer->ADD_GOSSIP_ITEM(5, "Ульдаман."                  , GOSSIP_SENDER_MAIN, 1258);
                pPlayer->ADD_GOSSIP_ITEM(5, "Зул'Фаррак."                , GOSSIP_SENDER_MAIN, 1259);
                pPlayer->ADD_GOSSIP_ITEM(5, "Мародон."                   , GOSSIP_SENDER_MAIN, 1260);
                pPlayer->ADD_GOSSIP_ITEM(5, "Затонувший храм."           , GOSSIP_SENDER_MAIN, 1261);
                pPlayer->ADD_GOSSIP_ITEM(5, "Глубины Чёрной Горы."       , GOSSIP_SENDER_MAIN, 1262);
                pPlayer->ADD_GOSSIP_ITEM(5, "Забытый Город."             , GOSSIP_SENDER_MAIN, 1263);
                pPlayer->ADD_GOSSIP_ITEM(5, "Пик Чёрной горы."           , GOSSIP_SENDER_MAIN, 1264);
                pPlayer->ADD_GOSSIP_ITEM(5, "Стратхольм."                , GOSSIP_SENDER_MAIN, 1265);
                pPlayer->ADD_GOSSIP_ITEM(5, "Некроситет."                , GOSSIP_SENDER_MAIN, 1266);
                pPlayer->ADD_GOSSIP_ITEM(5, "Ан'кираж."                  , GOSSIP_SENDER_MAIN, 4037);
                pPlayer->ADD_GOSSIP_ITEM(7, "[Ещё] ->"                   , GOSSIP_SENDER_MAIN, 5553);
                pPlayer->ADD_GOSSIP_ITEM(7, "<- [Назад]"                 , GOSSIP_SENDER_MAIN, 5550);
                pPlayer->ADD_GOSSIP_ITEM(7, "<- [Главное меню]"          , GOSSIP_SENDER_MAIN, 724);

                pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());

                break;

            case 5553: //Instances 60-70
                pPlayer->ADD_GOSSIP_ITEM(5, "Каражан."                   , GOSSIP_SENDER_MAIN, 4007);
                pPlayer->ADD_GOSSIP_ITEM(5, "Логово Груула."             , GOSSIP_SENDER_MAIN, 4008);
                pPlayer->ADD_GOSSIP_ITEM(5, "Цитадель Адского Пламени."  , GOSSIP_SENDER_MAIN, 4009);
                pPlayer->ADD_GOSSIP_ITEM(5, "Резервуар Кривого Клыка."   , GOSSIP_SENDER_MAIN, 4010);
                pPlayer->ADD_GOSSIP_ITEM(5, "Крепость Бурь."             , GOSSIP_SENDER_MAIN, 4011);
                pPlayer->ADD_GOSSIP_ITEM(5, "Пещеры Времени."            , GOSSIP_SENDER_MAIN, 4012);
                pPlayer->ADD_GOSSIP_ITEM(5, "Зул'Аман."                  , GOSSIP_SENDER_MAIN, 4016);
                pPlayer->ADD_GOSSIP_ITEM(5, "Зул'Гуруб."                 , GOSSIP_SENDER_MAIN, 4034);
                pPlayer->ADD_GOSSIP_ITEM(5, "Чёрный Храм."               , GOSSIP_SENDER_MAIN, 4013);
                pPlayer->ADD_GOSSIP_ITEM(5, "Террасса Магистров."        , GOSSIP_SENDER_MAIN, 4017);
                pPlayer->ADD_GOSSIP_ITEM(5, "Плато Солнечного Колодца."  , GOSSIP_SENDER_MAIN, 4018);
                pPlayer->ADD_GOSSIP_ITEM(7, "<- [Назад]"                 , GOSSIP_SENDER_MAIN, 5550);
                pPlayer->ADD_GOSSIP_ITEM(7, "<- [Главное меню]"          , GOSSIP_SENDER_MAIN, 724);


                pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());

                break;

            case 5554: //Instances 75-80 NORTHREND
                pPlayer->ADD_GOSSIP_ITEM(5, "Крепость Утгард."                        , GOSSIP_SENDER_MAIN, 4019);
                pPlayer->ADD_GOSSIP_ITEM(5, "Нексус."                                 , GOSSIP_SENDER_MAIN, 4020);
                pPlayer->ADD_GOSSIP_ITEM(5, "Азжол-Неруб."                            , GOSSIP_SENDER_MAIN, 4021);
                pPlayer->ADD_GOSSIP_ITEM(5, "Ан'кахет: Старое Королевство."           , GOSSIP_SENDER_MAIN, 4022);
                pPlayer->ADD_GOSSIP_ITEM(5, "Крепость Драк'Тарон."                    , GOSSIP_SENDER_MAIN, 4023);
                pPlayer->ADD_GOSSIP_ITEM(5, "Аметистовая Цитадель."                   , GOSSIP_SENDER_MAIN, 4024);
                pPlayer->ADD_GOSSIP_ITEM(5, "Гун'Драк."                               , GOSSIP_SENDER_MAIN, 4025);
                pPlayer->ADD_GOSSIP_ITEM(5, "Вершина Утгард."                         , GOSSIP_SENDER_MAIN, 4026);
                pPlayer->ADD_GOSSIP_ITEM(5, "Ульдуар."                                , GOSSIP_SENDER_MAIN, 4027);
                pPlayer->ADD_GOSSIP_ITEM(7, "[Ещё] ->"                                , GOSSIP_SENDER_MAIN, 5555);
                pPlayer->ADD_GOSSIP_ITEM(7, "<- [Назад]"                              , GOSSIP_SENDER_MAIN, 5550);
                pPlayer->ADD_GOSSIP_ITEM(7, "<- [Главное меню]"                       , GOSSIP_SENDER_MAIN, 724);


                pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());

                break;

            case 5555: //Instances 75-80 NORTHREND more
                pPlayer->ADD_GOSSIP_ITEM(5, "Обсидиановое святилище."                , GOSSIP_SENDER_MAIN, 4028);
                pPlayer->ADD_GOSSIP_ITEM(5, "Наксрамас."                             , GOSSIP_SENDER_MAIN, 4029);
                pPlayer->ADD_GOSSIP_ITEM(5, "Колизей Серебрянного Авангарда."        , GOSSIP_SENDER_MAIN, 4032);
                pPlayer->ADD_GOSSIP_ITEM(5, "Склеп Аркавона."                        , GOSSIP_SENDER_MAIN, 4030);
                pPlayer->ADD_GOSSIP_ITEM(5, "Ледяная Корона: Рейд."                  , GOSSIP_SENDER_MAIN, 4031);
                pPlayer->ADD_GOSSIP_ITEM(5, "Ледяная Корона: Ледяные Залы."          , GOSSIP_SENDER_MAIN, 4033);
                pPlayer->ADD_GOSSIP_ITEM(5, "Логово Ониксии."                        , GOSSIP_SENDER_MAIN, 4036);
                pPlayer->ADD_GOSSIP_ITEM(7, "<- [Назад]"                             , GOSSIP_SENDER_MAIN, 5554);
                pPlayer->ADD_GOSSIP_ITEM(7, "<- [Главное меню]"                      , GOSSIP_SENDER_MAIN, 724);


                pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());

                break;

            case 5552: //Back To Main Menu
                if (pPlayer->GetTeam() == ALLIANCE ) {
					pPlayer->ADD_GOSSIP_ITEM(5, "Телепорт в стартовую локацию"           , GOSSIP_SENDER_MAIN, 9991);
                    pPlayer->ADD_GOSSIP_ITEM(5, "Пиратская Бухта."                       , GOSSIP_SENDER_MAIN, 4035);
                    pPlayer->ADD_GOSSIP_ITEM(5, "Дарнасс."                               , GOSSIP_SENDER_MAIN, 1203);
                    pPlayer->ADD_GOSSIP_ITEM(5, "Экзодар."                               , GOSSIP_SENDER_MAIN, 1216);
                    pPlayer->ADD_GOSSIP_ITEM(5, "Штормград."                             , GOSSIP_SENDER_MAIN, 1206);
                    pPlayer->ADD_GOSSIP_ITEM(5, "Стальгорн."                             , GOSSIP_SENDER_MAIN, 1224);
                    pPlayer->ADD_GOSSIP_ITEM(5, "Гномреган."                             , GOSSIP_SENDER_MAIN, 1222);
                    pPlayer->ADD_GOSSIP_ITEM(5, "Шаттрат."                               , GOSSIP_SENDER_MAIN, 1287);
                    pPlayer->ADD_GOSSIP_ITEM(5, "Даларан."                               , GOSSIP_SENDER_MAIN, 1205);
                    pPlayer->ADD_GOSSIP_ITEM(5, "Остров Кель'Данас."                     , GOSSIP_SENDER_MAIN, 1288);
                    if (sConfig->GetIntDefault("RealmID", 0) == 5)
                    {
                        pPlayer->ADD_GOSSIP_ITEM(5, "Стартовая локация."                 , GOSSIP_SENDER_MAIN, 4039);
                        pPlayer->ADD_GOSSIP_ITEM(5, "Арена награнда."                    , GOSSIP_SENDER_MAIN, 4040);
                    }
                    pPlayer->ADD_GOSSIP_ITEM(7, "[Инстансы] ->"                          , GOSSIP_SENDER_MAIN, 5550);
                    pPlayer->ADD_GOSSIP_ITEM(7, "[Инстансы WotLK] ->"                    , GOSSIP_SENDER_MAIN, 5554);

                }  else {
					pPlayer->ADD_GOSSIP_ITEM(5, "Телепорт в стартовую локацию"           , GOSSIP_SENDER_MAIN, 9992);
                    pPlayer->ADD_GOSSIP_ITEM(5, "Пиратская Бухта."                       , GOSSIP_SENDER_MAIN, 4035);
                    pPlayer->ADD_GOSSIP_ITEM(5, "Оргриммар."                             , GOSSIP_SENDER_MAIN, 1215);
                    pPlayer->ADD_GOSSIP_ITEM(5, "Луносвет."                              , GOSSIP_SENDER_MAIN, 1217);
                    pPlayer->ADD_GOSSIP_ITEM(5, "Подгород."                              , GOSSIP_SENDER_MAIN, 1213);
                    pPlayer->ADD_GOSSIP_ITEM(5, "Громовой утёс."                         , GOSSIP_SENDER_MAIN, 1225);
                    pPlayer->ADD_GOSSIP_ITEM(5, "Гномреган."                             , GOSSIP_SENDER_MAIN, 1222);
                    pPlayer->ADD_GOSSIP_ITEM(5, "Шаттрат.."                              , GOSSIP_SENDER_MAIN, 1287);
                    pPlayer->ADD_GOSSIP_ITEM(5, "Даларан."                               , GOSSIP_SENDER_MAIN, 1205);
                    pPlayer->ADD_GOSSIP_ITEM(5, "Остров Кель'Данас."                     , GOSSIP_SENDER_MAIN, 1288);
                    if (sConfig->GetIntDefault("RealmID", 0) == 5)
                    {
                        pPlayer->ADD_GOSSIP_ITEM(5, "Стартовая локация."                 , GOSSIP_SENDER_MAIN, 4039);
                        pPlayer->ADD_GOSSIP_ITEM(5, "Арена награнда."                    , GOSSIP_SENDER_MAIN, 4040);
                    }
                    pPlayer->ADD_GOSSIP_ITEM(7, "[Инстансы] ->"                          , GOSSIP_SENDER_MAIN, 5550);
                    pPlayer->ADD_GOSSIP_ITEM(7, "[Инстансы WotLK] ->"                    , GOSSIP_SENDER_MAIN, 5554);
                }

                    pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());

                break;
			case 9991: //Teleport to ALLIANCE start location
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, -8556.9277f, 2001.4152f, 102.2383f, 0.44f);
				break;

			case 9992: //Teleport to HORDE start location
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, -2265.1008f, -305.5836f, -8.4028f, 4.0881f);
				break;

			case 9993: //Teleport to DUEL ZONE
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, -3762.168213f, 1095.605103f, 133.408173f, 4.686316f);
				break;

            case 1203: // Teleport to Darnassus
                pPlayer->CLOSE_GOSSIP_MENU();
                pPlayer->TeleportTo(1, 9947.52f, 2482.73f, 1316.21f, 0.0f);
                break;

            case 1206: // Teleport to Stormwind
                pPlayer->CLOSE_GOSSIP_MENU();
                pPlayer->TeleportTo(0, -8960.14f, 516.266f, 96.3568f, 0.0f);
                break;

            case 1205: // Teleport to Dalaran
                pPlayer->CLOSE_GOSSIP_MENU();
                pPlayer->TeleportTo(571, 5804.14f, 624.770f, 647.7670f, 1.64f);
                break;

            case 1213: // Teleport to Undercity
                pPlayer->CLOSE_GOSSIP_MENU();
                pPlayer->TeleportTo(0, 1819.71f, 238.79f, 60.5321f, 0.0f);
                break;

            case 1215: // Teleport to Orgrimmar
                pPlayer->CLOSE_GOSSIP_MENU();
                pPlayer->TeleportTo(1, 1552.5f, -4420.66f, 8.94802f, 0.0f);
                break;

            case 1216: // Teleport to Exodar
                pPlayer->CLOSE_GOSSIP_MENU();
                pPlayer->TeleportTo(530, -4073.03f, -12020.4f, -1.47f, 0.0f);
                break;

            case 1217: // Teleport to Silvermoon
                pPlayer->CLOSE_GOSSIP_MENU();
                pPlayer->TeleportTo(530, 9338.74f, -7277.27f, 13.7895f, 0.0f);
                break;

            case 1222: // Teleport to Gnomeregan
                pPlayer->CLOSE_GOSSIP_MENU();
                pPlayer->TeleportTo(0, -5163.43f,660.40f,348.28f,4.65f);
                    break;

            case 1224: // Teleport to Ironforge
                pPlayer->CLOSE_GOSSIP_MENU();
                pPlayer->TeleportTo(0, -4924.07f, -951.95f, 501.55f, 5.40f);
                break;

            case 1225: // Teleport to Thunder Bluff
                pPlayer->CLOSE_GOSSIP_MENU();
                pPlayer->TeleportTo(1, -1280.19f,127.21f,131.35f,5.16f); 
                break;

            case 1248: // Teleport Player to Ragefire Chasm
                if( pPlayer->getLevel() >= 8)
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(1, 1800.53f,-4394.68f,-17.93f,5.49f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 8!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 1249: // Teleport to the Wailing Caverns
                if (pPlayer->getLevel() >= 10)
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(1, -722.53f,-2226.30f,16.94f,2.71f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 10!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 1250: // Teleport to the Deadmines
                if (pPlayer->getLevel() >= 10)
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(0, -11212.04f,1658.58f,25.67f,1.45f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 10!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 1251: // Teleport to Shadowfang Keep
                if (pPlayer->getLevel() >= 15)
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(0, -254.47f,1524.68f,76.89f,1.56f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 15!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 1252: // Teleport to Blackfathom Deeps
                if (pPlayer->getLevel() >= 15)
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(1, 4254.58f,664.74f,-29.04f,1.97f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 15!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 1253: // Teleport to the Stockade
                if (pPlayer->getLevel() >= 20)  
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(0, -8769.76f,813.08f,97.63f,2.26f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 20!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 1254: // Teleport to Razorfen Kraul
                if (pPlayer->getLevel() >= 24)    
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(1, -4484.04f,-1739.40f,86.47f,1.23f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 24!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 1255: // Teleport to Gnomeregan
                if (pPlayer->getLevel() >= 20)
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(0, -5162.62f,667.81f,248.05f,1.48f);   
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 20!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 1256: // Teleport to Razorfen Downs
                if (pPlayer->getLevel() >= 25)
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(1, -4645.08f,-2470.85f,85.53f,4.39f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 25!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 1257: // Teleport to the Scarlet Monastery
                if (pPlayer->getLevel() >= 25)   
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(0, 2843.89f,-693.74f,139.32f,5.11f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 25!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 1258://Teleport to Uldaman
                if (pPlayer->getLevel() >= 35)
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(0, -6119.70f,-2957.30f,204.11f,0.03f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 35!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 1259: // Teleport to Zul'Farrak
                if (pPlayer->getLevel() >= 35)
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(1, -6839.39f,-2911.03f,8.87f,0.41f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 35!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 1260: // Teleport to Maraudon
                if (pPlayer->getLevel() >= 40)
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(1, -1433.33f,2955.34f,96.21f,4.82f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 40!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 1261: // Teleport to the Sunken Temple
                if (pPlayer->getLevel() >= 45)
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(0, -10346.92f,-3851.90f,-43.41f,6.09f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 45!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 1262: // Teleport to Blackrock Depths
                if (pPlayer->getLevel() >= 45)     
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(0, -7301.03f,-913.19f,165.37f,0.08f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 45!", LANG_UNIVERSAL, NULL);
                }
                    break;

            case 1263: // Teleport to Dire Maul
                if (pPlayer->getLevel() >= 50)       
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(1, -3982.47f,1127.79f,161.02f,0.05f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 50!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 1264: // Teleport to Blackrock Spire
                if (pPlayer->getLevel() >= 50)    
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                pPlayer->TeleportTo(0, -7535.43f,-1212.04f,285.45f,5.29f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 50!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 1265: // Teleport to Stratholme
                if (pPlayer->getLevel() >= 50)     
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(0, 3263.54f,-3379.46f,143.59f,0.00f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 50!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 1266: // Teleport to Scholomance
                if (pPlayer->getLevel() >= 50)
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(0, 1219.01f,-2604.66f,85.61f,0.50f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 50!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 1287:// Shattrath City
                if( pPlayer->getLevel() >= 58)
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(530, -1850.209961f, 5435.821777f, -10.961435f, 3.403913f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 58!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 1288: // Teleport to Isle Of Quel'Danas
                if (pPlayer->getLevel() >= 65)    
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(530, 12947.4f,-6893.31f,5.68398f,3.09154f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 65!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 4007: // Karazhan
                if (pPlayer->getLevel() >= 70)   
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(0, -11118.8f, -2010.84f, 47.0807f, 0.0f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 70!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 4008: // Gruul's Lair
                if (pPlayer->getLevel() >= 65)    
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(530, 3539.007568f, 5082.357910f, 1.691071f, 0.0f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 65!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 4009: // Hellfire Citadel
                pPlayer->CLOSE_GOSSIP_MENU();
                pPlayer->TeleportTo(530, -305.816223f, 3056.401611f, -2.473183f, 2.01f);
                break;

            case 4010: // Coilfang Reservoir
                pPlayer->CLOSE_GOSSIP_MENU();
                pPlayer->TeleportTo(530, 517.288025f, 6976.279785f, 32.007198f, 0.0f);
                break;

            case 4011: // Tempest Keep
                if (pPlayer->getLevel() >= 70)   
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(530, 3089.579346f, 1399.046509f, 187.653458f, 4.794070f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 70!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 4012: // Caverns of Time
                if (pPlayer->getLevel() >= 66)
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(1, -8173.66f, -4746.36f, 33.8423f, 4.93989f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 66!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 4016: // Zul'Aman
                if (pPlayer->getLevel() >= 70)  
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(530, 6846.95f, -7954.5f, 170.028f, 4.61501f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 70!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 4013: // Black Temple
                if (pPlayer->getLevel() >= 70)   
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(530, -3610.719482f, 324.987579f, 37.400028f, 3.282981f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 70!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 4017: // magistrate
                if (pPlayer->getLevel() >= 70)   
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(530, 12884.6f, -7317.69f, 65.5023f, 4.799f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 70!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 4018: // Sunwell
                if (pPlayer->getLevel() >= 70)
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(530, 12574.1f, -6774.81f, 15.0904f, 3.13788f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 70!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 4019:// Utgarde Keep
                if (pPlayer->getLevel() >= 70)    
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(571, 1219.720f, -4865.28f, 41.25f, 0.31f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 70!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 4020: // The Nexus
                if (pPlayer->getLevel() >= 70)  
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(571, 3776.950f, 6953.80f, 105.05f, 0.345f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 70!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 4021: // Azjol-Nerub
                if (pPlayer->getLevel() >= 70)
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(571, 3675.430f, 2169.00f, 35.90f, 2.29f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 70!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 4022: // Ahn'kahet: The Old Kingdom
                if (pPlayer->getLevel() >= 70)
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(571, 3646.760f, 2045.17f, 1.79f, 4.37f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 70!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 4023: // Drak'Tharon Keep
                if (pPlayer->getLevel() >= 70)   
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(571, 4450.860f, -2045.25f, 162.83f, 0.00f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 70!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 4024: // The Violet Hold
                if (pPlayer->getLevel() >= 70)    
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(571, 5679.820f, 486.80f, 652.40f, 4.08f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 70!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 4025: // Gun' Drak
                if (pPlayer->getLevel() >= 70)    
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(571, 6937.540f, -4455.98f, 450.68f, 1.00f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 70!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 4026: // Utgarde Pinnacle
                if (pPlayer->getLevel() >= 70) 
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(571, 1245.690f, -4856.59f, 216.86f, 3.45f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 70!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 4027: // Ulduar
                if (pPlayer->getLevel() >= 70) 
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(571, 8976.240f, -1281.33f, 1059.01f, 0.58f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 70!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 4028: // The Obsidian Sanctum
                if (pPlayer->getLevel() >= 70)   
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(571, 3625.780f, 280.40f, -120.14f, 3.25f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 70!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 4029: // Naxxramas
                if (pPlayer->getLevel() >= 70)       
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(571, 3668.719f, -1262.460f, 243.63f, 5.03f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 70!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 4030: // Archavon's Valut
                if (pPlayer->getLevel() >= 70)
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(571, 5475.506f, 2840.60f, 418.67f, 6.25f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень не должен быть ниже бы уровня 70!", LANG_UNIVERSAL, NULL);
                } 
                break;

            case 4031: // Icecrown Raid
                if (pPlayer->getLevel() >= 70)
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(571, 5796.494f, 2075.29f, 636.06f, 3.59f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень не должен быть ниже бы уровня 70!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 4032: // Argent Coliseum
                if (pPlayer->getLevel() >= 70)
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(571, 8516.204f, 641.40f, 547.32f, 1.61f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень не должен быть ниже бы уровня 70!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 4033: // Icecrown Daily
                if (pPlayer->getLevel() >= 70)     
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(571, 5631.911f, 2011.72f, 798.26f, 4.59f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 70!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 4034: // Zul'Gurub
                if (pPlayer->getLevel() >= 50)     
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(0, -11916.153f, -1211.612f, 92.28f, 4.68f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 50!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 4035: // Booty Bay
                pPlayer->CLOSE_GOSSIP_MENU();
                pPlayer->TeleportTo(0, -14290.535f, 548.290f, 8.85f, 4.29f);
                break;

            case 4036: // Onyxia
                if (pPlayer->getLevel() >= 60)
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(1, -4712.451f, -3729.173f, 54.21f, 0.56f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 60!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 4037: // AQ
                if (pPlayer->getLevel() >= 50)
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(0, -8254.271f, 1536.794f, -4.80f, 5.67f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 50!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 4038:
                if (pPlayer->getLevel() >= 50)
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(0, -3354.630f, 4930.559f, -99.97f, 0.33f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 50!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 4039: // Start locations
                if (pPlayer->GetTeam() == ALLIANCE)
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(530, -2244.01f, 8698.61f, -2.73f, 5.16f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(530, -1236.92f, 7144.97f, 57.26f, 4.78f);
                }
                break;

            case 4040: // Nagrand Arena
                if (pPlayer->GetTeam() == ALLIANCE)
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(530, -2106.58f, 6749.17f, -3.65f, 5.27f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(530, -1971.01f, 6541.43f, 12.75f, 2.48f);
                }
                break;
            
			case 500:
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->SetDisplayId(21135);
			pPlayer->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.5f);
            break;
 
        case 501:
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->SetDisplayId(23200);
			pPlayer->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.1f);
            break;
 
        case 502:
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->SetDisplayId(20681);
			pPlayer->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.8f);
            break;
 
        case 503:
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->SetDisplayId(16508);
			pPlayer->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.8f);
            break;
 
        case 504:
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->SetDisplayId(17332);
			pPlayer->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.8f);
            break;                              
                
                case 505:
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->SetDisplayId(2789);
			pPlayer->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.8f);
            break;
 
                case 506:
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->SetDisplayId(16280);
			pPlayer->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.8f);
            break;
 
                case 507:
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->SetDisplayId(24191);
			pPlayer->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.8f);
            break;
 
                case 508:
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->SetDisplayId(22209);
			pPlayer->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.8f);
            break;
 
                case 509:
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->SetDisplayId(23889);
			pPlayer->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.8f);
            break;
 
				case 510:
                        pPlayer->CLOSE_GOSSIP_MENU();
                        pPlayer->SetDisplayId(24949);
						pPlayer->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.8f);
                        break;

			case 711: 
    pPlayer->CLOSE_GOSSIP_MENU();
	pPlayer->SetDisplayId(28641);
	pPlayer->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.2f);
break;

case 712: 
    pPlayer->CLOSE_GOSSIP_MENU();
	pPlayer->SetDisplayId(16630);
	pPlayer->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.1f);
break;

case 713: 
    pPlayer->CLOSE_GOSSIP_MENU();
	pPlayer->SetDisplayId(17887);
	pPlayer->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.10f);
break;

case 714: 
    pPlayer->CLOSE_GOSSIP_MENU();
	pPlayer->SetDisplayId(8570);
	pPlayer->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.1f);
break;

case 715: 
    pPlayer->CLOSE_GOSSIP_MENU();
	pPlayer->SetDisplayId(16137);
	pPlayer->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.2f);
break;

case 716: 
    pPlayer->CLOSE_GOSSIP_MENU();
	pPlayer->SetDisplayId(16064);
	pPlayer->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.2f);
break;

case 717: 
    pPlayer->CLOSE_GOSSIP_MENU();
	pPlayer->SetDisplayId(15928);
	pPlayer->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.15f);
break;

case 718: 
    pPlayer->CLOSE_GOSSIP_MENU();
	pPlayer->SetDisplayId(16033);
	pPlayer->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.1f);
break;

case 719: 
    pPlayer->CLOSE_GOSSIP_MENU();
	pPlayer->SetDisplayId(16590);
	pPlayer->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.7f);
break;

case 720: 
    pPlayer->CLOSE_GOSSIP_MENU();
		pPlayer->SetDisplayId(15945);
	pPlayer->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.2f);
break;

case 721: 
    pPlayer->CLOSE_GOSSIP_MENU();
	pPlayer->SetDisplayId(20023);
	pPlayer->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.5f);
break;

case 722: 
    pPlayer->CLOSE_GOSSIP_MENU();
	pPlayer->SetDisplayId(15786);
	pPlayer->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.1f);
break;

case 723: 
    pPlayer->CLOSE_GOSSIP_MENU();
	pPlayer->SetDisplayId(4527);
	pPlayer->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
break;

case 724:
pPlayer->ADD_GOSSIP_ITEM(0, "Приветствие и основная информация", GOSSIP_SENDER_MAIN, 6); //как начать
		//pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Покупка Сумок"   , GOSSIP_SENDER_MAIN, 2); //Сумки
		
		if ((pPlayer->getClass() == CLASS_MAGE)){
			  pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Купить бесплатно Сет а7 на Мага"  , GOSSIP_SENDER_MAIN, 1); //Сет на мага a7
			  pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Купить бесплатно Нонсет а7 на Мага(Крит)"  , GOSSIP_SENDER_MAIN, 26); //Нонсет на мага a7
			  pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Купить бесплатно Нонсет а7 на Мага(Скорость)"  , GOSSIP_SENDER_MAIN, 27); //Нонсет на мага a7
			 }else if ((pPlayer->getClass() == CLASS_PALADIN))
           {
		      pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Купить бесплатно Сет а7 на Паладина (Возмездие)", GOSSIP_SENDER_MAIN, 4); //Сет на пала дд a7
	          pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Купить бесплатно Сет а7 на Паладина (Свет)", GOSSIP_SENDER_MAIN, 7); //Сет на холи пала a7
			  pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Купить бесплатно Нонсет а7 на Паладина (Возмездие)", GOSSIP_SENDER_MAIN, 45); //Нонсет на ретрика пала a7
			  pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Купить бесплатно Нонсет а7 на Паладина (Свет)", GOSSIP_SENDER_MAIN, 29); //Нонсет  на холи пала a7
		   }else if ((pPlayer->getClass() == CLASS_HUNTER))
           {
	          pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Купить бесплатно Сет а7 на Охотника", GOSSIP_SENDER_MAIN, 8); //Нонсет Сет на ханта a7
			  pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Купить бесплатно Нонсет а7 на Охотника", GOSSIP_SENDER_MAIN, 30); //Нонсет Сет на ханта a7
		   }else if ((pPlayer->getClass() == CLASS_DRUID))
           {
		      pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Купить бесплатно Сет а7 на Друида (Исцеление)", GOSSIP_SENDER_MAIN, 9); //Сет на друида хила a7
		      pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Купить бесплатно Сет а7 на Друида (Сила зверя)", GOSSIP_SENDER_MAIN, 10); //Сет на друида дд a7
	          pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Купить бесплатно Сет а7 на Друида (Баланс)", GOSSIP_SENDER_MAIN, 11); //Сет на друида рдд a7
			  pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Купить бесплатно Нонсет а7 на Друида (Исцеление)", GOSSIP_SENDER_MAIN, 31); //Нонсет  на друида хила a7
		      pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Купить бесплатно Нонсет а7 на Друида (Сила зверя)", GOSSIP_SENDER_MAIN, 32); //Нонсет на друида дд a7
	          pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Купить бесплатно Нонсет а7 на Друида (Баланс)", GOSSIP_SENDER_MAIN, 33); //Нонсет на друида рдд a7
		   }else if ((pPlayer->getClass() == CLASS_WARRIOR))
           {
	          pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Купить бесплатно Сет а7 на Война", GOSSIP_SENDER_MAIN, 12); //Сет на вара a7
			  pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Купить бесплатно Нонсет а7 на Война", GOSSIP_SENDER_MAIN, 34); //Нонсет на вара a7
		   }else if ((pPlayer->getClass() == CLASS_WARLOCK))
           {
	          pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Купить бесплатно Сет а7 на Чернокнижника", GOSSIP_SENDER_MAIN, 13); //Сет на лока a7
			  pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Купить бесплатно Нонсет а7 на Чернокнижника(На крит)", GOSSIP_SENDER_MAIN, 35); //Нонсет на лока a7
			  pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Купить бесплатно Нонсет а7 на Чернокнижника(На скорость)", GOSSIP_SENDER_MAIN, 36); //Нонсет на лока a7
		   }else if ((pPlayer->getClass() == CLASS_SHAMAN))
           {
	          pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Купить бесплатно Сет а7 на Шамана (Исцеление)", GOSSIP_SENDER_MAIN, 14); //Сет на шамана хила a7
	          pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Купить бесплатно Сет а7 на Шамана (Совершенствование)", GOSSIP_SENDER_MAIN, 15); //Сет на шамана рд a7
	          pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Купить бесплатно Сет а7 на Шамана (Стихия)", GOSSIP_SENDER_MAIN, 16); //Сет на шамана рдд a7
			  pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Купить бесплатно Нонсет а7 на Шамана (Исцеление)", GOSSIP_SENDER_MAIN, 37); //Нонсет на шамана хила a7
	          pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Купить бесплатно Нонсет а7 на Шамана (Совершенствование)", GOSSIP_SENDER_MAIN, 38); //Нонсет на шамана рд a7
	          pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Купить бесплатно Нонсет а7 на Шамана (Стихия)", GOSSIP_SENDER_MAIN, 39); //Нонсет на шамана рдд a7
		   }else if ((pPlayer->getClass() == CLASS_ROGUE))
           {
	          pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Купить бесплатно Сет а7 на Разбойника", GOSSIP_SENDER_MAIN, 17); //Сет на рогу a7
			  pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Купить бесплатно Нонсет а7 на Разбойника", GOSSIP_SENDER_MAIN, 40); //Нонсет на рогу a7
		   }else if ((pPlayer->getClass() == CLASS_PRIEST))
           {
	          pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Купить бесплатно Сет а7 на Жреца (Темная магия)", GOSSIP_SENDER_MAIN, 18); //Сет на приста ШП a7
	          pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Купить бесплатно Сет а7 на Жреца (Свет)", GOSSIP_SENDER_MAIN, 19); //Сет на приста свет a7
			  pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Купить бесплатно Нонсет а7 на Жреца (На крит)", GOSSIP_SENDER_MAIN, 41); //Нонсет на приста ШП a7
	          pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Купить бесплатно Нонсет а7 на Жреца (На скорость)", GOSSIP_SENDER_MAIN, 42); //Нонсет на приста свет a7
			  pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Купить бесплатно Нонсет а7 на Жреца (Свет)", GOSSIP_SENDER_MAIN, 43); //Нонсет на приста свет a7
		   }else if ((pPlayer->getClass() == CLASS_DEATH_KNIGHT))
           {
	          pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Купить бесплатно Сет а7 на Рыцаря смерти", GOSSIP_SENDER_MAIN, 20); //Сет на дк a7
			  pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Купить бесплатно Нонсет а7 на Рыцаря смерти", GOSSIP_SENDER_MAIN, 44); //Нонсет на дк a7
		   }
		   
		   //pPlayer->ADD_GOSSIP_ITEM(9, "Вылечи меня!"                     , GOSSIP_SENDER_MAIN, 3);
		   //pPlayer->ADD_GOSSIP_ITEM(5, "Обучить верховую езду на максимум", GOSSIP_SENDER_MAIN, 21); //Верховая езда
		   //pPlayer->ADD_GOSSIP_ITEM(9, "Обучить мои навыки защиты и оружия на максимум", GOSSIP_SENDER_MAIN, 23); //Навык макс.
	       pPlayer->ADD_GOSSIP_ITEM(7, "[Меню]Телепорта", GOSSIP_SENDER_MAIN, 5); 
           pPlayer->ADD_GOSSIP_ITEM(7, "[Меню]Баффов" , GOSSIP_SENDER_MAIN, 24); //Баффер  
		   if (pPlayer->GetTeam() == ALLIANCE ) {
			  pPlayer->ADD_GOSSIP_ITEM(5, "Телепорт в стартовую локацию", GOSSIP_SENDER_MAIN, 9991);
		   }else {
			  pPlayer->ADD_GOSSIP_ITEM(5, "Телепорт в стартовую локацию"     , GOSSIP_SENDER_MAIN, 9992);
		   }
		   pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Телепорт в DUEL ZONE", GOSSIP_SENDER_MAIN, 9993);
           //pPlayer->ADD_GOSSIP_ITEM(7, "[Меню]Превращений", GOSSIP_SENDER_MAIN, 46);	   
           //pPlayer->ADD_GOSSIP_ITEM(0, "Кто тебя создал ?", GOSSIP_SENDER_MAIN, 25); //кто тебя создал ?		 
break;

			}
			
        return true;
    }
};

void AddSC_npc_renaissance()
{
    new npc_renaissance;
}
