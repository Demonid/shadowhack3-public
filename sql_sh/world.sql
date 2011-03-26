UPDATE `creature_template` SET `spell1` = 6474, `spell2` = 0 WHERE `entry` = 2630;

-- Anti-Magic Zone
REPLACE INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `Health_mod`, `Mana_mod`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES (28306, 0, 0, 0, 0, 0, 20242, 0, 0, 0, 'Anti-Magic Zone', '', '', 0, 80, 80, 0, 2, 2, 0, 1, 1.14286, 1, 0, 420, 630, 0, 158, 1.1, 2000, 2000, 1, 33554434, 0, 0, 0, 0, 0, 0, 336, 504, 126, 11, 1024, 0, 0, 0, 0, 0, 0, 0, 0, 0, 50461, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 2.70535, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, '', 11403);

-- (12577) Arcane Concentration (Rank 5)
DELETE FROM `spell_proc_event` WHERE `entry` IN (12577);
INSERT INTO `spell_proc_event` VALUES (12577, 0x00, 0x03, 0x00000000, 0x00000000, 0x00000000, 0x00010000, 0x00000001, 0, 10, 0);

-- (12576) Arcane Concentration (Rank 4)
DELETE FROM `spell_proc_event` WHERE `entry` IN (12576);
INSERT INTO `spell_proc_event` VALUES (12576, 0x00, 0x03, 0x00000000, 0x00000000, 0x00000000, 0x00010000, 0x00000001, 0, 8, 0);

-- (12575) Arcane Concentration (Rank 3)
DELETE FROM `spell_proc_event` WHERE `entry` IN (12575);
INSERT INTO `spell_proc_event` VALUES (12575, 0x00, 0x03, 0x00000000, 0x00000000, 0x00000000, 0x00010000, 0x00000001, 0, 6, 0);

-- (12574) Arcane Concentration (Rank 2)
DELETE FROM `spell_proc_event` WHERE `entry` IN (12574);
INSERT INTO `spell_proc_event` VALUES (12574, 0x00, 0x03, 0x00000000, 0x00000000, 0x00000000, 0x00010000, 0x00000001, 0, 4, 0);

-- (12573) Arcane Concentration (Rank 1)
DELETE FROM `spell_proc_event` WHERE `entry` IN (12573);
INSERT INTO `spell_proc_event` VALUES (12573, 0x00, 0x03, 0x00000000, 0x00000000, 0x00000000, 0x00010000, 0x00000001, 0, 2, 0);

-- scriptname for Nibelung
UPDATE `creature_template` SET `ScriptName`='npc_valkyr' WHERE (`entry`='38392');

-- item requirements custom patch
ALTER TABLE `item_template`
DROP COLUMN `userating`;

CREATE TABLE IF NOT EXISTS `item_requirements` (
  `entry` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT 0,
  `reqrating` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT 0,
  `reqitem` MEDIUMINT(8) NOT NULL DEFAULT 0,
  PRIMARY KEY (`entry`)
) ENGINE=MYISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;
	
UPDATE `spell_bonus_data` SET `direct_bonus`='0' WHERE (`entry`='45297');
UPDATE `spell_bonus_data` SET `direct_bonus`='0' WHERE (`entry`='45284');