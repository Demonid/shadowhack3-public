SET @MAPID := 631;

ALTER TABLE `waypoint_data` ADD INDEX `idx_id` (`id`) ;
ALTER TABLE `creature_addon` ADD INDEX `idx_path` (`path_id`) ;
DELETE FROM `creature` WHERE `map` <> @MAPID;
DELETE FROM `creature_addon` WHERE `guid` NOT IN (SELECT `guid` FROM `creature`);
DELETE FROM `waypoint_data` WHERE `id` NOT IN (SELECT `path_id` FROM `creature_addon`);

DROP TRIGGER IF EXISTS `creature_after_update`;
CREATE TRIGGER `creature_after_update` AFTER UPDATE ON `creature`
FOR EACH ROW BEGIN
UPDATE `creature_addon` SET `guid`=NEW.guid WHERE `guid`=OLD.guid;
END;
SELECT @MAPID * 1000 INTO @temp_var;
UPDATE `creature` SET `guid` = @MAPID * 1000 WHERE `guid`=0;
UPDATE `creature` SET `guid`=@temp_var:=@temp_var+1 ORDER BY `guid` ASC;
DROP TRIGGER IF EXISTS `creature_after_update`;

UPDATE `waypoint_data` SET `id` = (SELECT `guid` FROM `creature_addon` WHERE `creature_addon`.`path_id` = `waypoint_data`.`id`);
UPDATE `creature_addon` SET `path_id` = `creature_addon`.`guid` WHERE `creature_addon`.`path_id` <> 0;