/*Table structure for table `game_event_temp` */

DROP TABLE IF EXISTS `game_event_temp`;

CREATE TABLE `game_event_temp` (
  `entryOld` tinyint(3) unsigned NOT NULL,
  `entryNew` tinyint(3) unsigned NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

/*Data for the table `game_event_temp`, built at the stage [db:1180] */

insert into `game_event_temp` values (1,1),(2,2),(3,3),(4,4),(5,5),(6,6),(7,7),(8,8),(9,9),(10,10),(11,11),(12,12),(22,22),(17,17),(13,13),(14,14),(16,16),(15,15),(18,18),(19,19),(20,20),(21,21),(23,23),(24,26),(27,31),(30,34),(31,35),(32,36),(33,37),(34,38),(28,32),(36,40),(37,41),(38,42),(39,43),(40,44),(41,45),(26,30),(46,50),(47,51),(48,52),(49,53),(50,54),(55,55),(56,56),(57,57),(58,58),(59,59),(60,60),(61,61),(42,46),(43,47),(64,64),(65,65),(66,66),(67,67),(68,68),(69,69),(44,48),(29,33),(35,39),(45,49),(51,73),(52,74),(55,75),(56,76),(57,77),(58,78),(59,79),(60,80);

-- Update game_event_save
UPDATE `game_event_save`, `game_event_temp` SET `game_event_save`.`eventEntry` = `game_event_temp`.`entryNew` WHERE `game_event_save`.`eventEntry` = `game_event_temp`.`entryOld`;

-- Update game_event_condition_save
UPDATE `game_event_condition_save`, `game_event_temp` SET `game_event_condition_save`.`eventEntry` = `game_event_temp`.`entryNew` WHERE `game_event_condition_save`.`eventEntry` = `game_event_temp`.`entryOld`;

drop table `game_event_temp`;
