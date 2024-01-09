CREATE DATABASE  IF NOT EXISTS `atm` /*!40100 DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci */ /*!80016 DEFAULT ENCRYPTION='N' */;
USE `atm`;
-- MySQL dump 10.13  Distrib 8.0.32, for Win64 (x86_64)
--
-- Host: 127.0.0.1    Database: atm
-- ------------------------------------------------------
-- Server version	8.0.31

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `asiakas`
--

DROP TABLE IF EXISTS `asiakas`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `asiakas` (
  `idasiakas` int NOT NULL AUTO_INCREMENT,
  `Henkilotunnus` varchar(45) NOT NULL,
  `Etunimi` varchar(45) NOT NULL,
  `Sukunimi` varchar(45) NOT NULL,
  `Puhelinnumero` varchar(45) NOT NULL,
  `Osoite` varchar(45) NOT NULL,
  PRIMARY KEY (`idasiakas`),
  UNIQUE KEY `henkilötunnus_UNIQUE` (`Henkilotunnus`),
  UNIQUE KEY `Puhelinnumero_UNIQUE` (`Puhelinnumero`)
) ENGINE=InnoDB AUTO_INCREMENT=9 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `asiakas`
--

LOCK TABLES `asiakas` WRITE;
/*!40000 ALTER TABLE `asiakas` DISABLE KEYS */;
INSERT INTO `asiakas` VALUES (1,'120167-454V','Matti','Mattinen','0401234567','Mattisenkuja 34, Mattila'),(2,'031289-567H','Maija','Maijanen','0402345678','Maijankatu 44, Maijala'),(3,'030598-155K','Krista','Kristallivuori','0501234567','Kristallikatu 7, 00100 Helsinki'),(4,'060699-895G','Erika','Eskelinen','050 598 1236','Poropolku 1, Kittilä'),(5,'050494-568E','Jarmo','Rantanen','050 598 1255','Kiertotie 2, Kerava'),(6,'030390-123C','Heikki-Mikael','Häkkinen','050 598 5894','Vaahterakatu 3, Karkkila'),(7,'230989-423D','Kaisa','Kelloniemi','050 598 2323','Ruusupolku 7, Jyväskylä'),(8,'230989-424E','Mikko','Metsälä','050 598 2324','Kielokangas 8, Jyväskylä');
/*!40000 ALTER TABLE `asiakas` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Temporary view structure for view `asiakkaantiedot`
--

DROP TABLE IF EXISTS `asiakkaantiedot`;
/*!50001 DROP VIEW IF EXISTS `asiakkaantiedot`*/;
SET @saved_cs_client     = @@character_set_client;
/*!50503 SET character_set_client = utf8mb4 */;
/*!50001 CREATE VIEW `asiakkaantiedot` AS SELECT 
 1 AS `IdAsiakas`,
 1 AS `Etunimi`,
 1 AS `Sukunimi`,
 1 AS `IdKortti`,
 1 AS `Kortti_nro`,
 1 AS `IdTili`,
 1 AS `DebitTilinro`,
 1 AS `DebitSaldo`,
 1 AS `CreditTilinro`,
 1 AS `CreditSaldo`,
 1 AS `CreditLuottoraja`*/;
SET character_set_client = @saved_cs_client;

--
-- Temporary view structure for view `asiakkaantilitapahtumat`
--

DROP TABLE IF EXISTS `asiakkaantilitapahtumat`;
/*!50001 DROP VIEW IF EXISTS `asiakkaantilitapahtumat`*/;
SET @saved_cs_client     = @@character_set_client;
/*!50503 SET character_set_client = utf8mb4 */;
/*!50001 CREATE VIEW `asiakkaantilitapahtumat` AS SELECT 
 1 AS `idAsiakas`,
 1 AS `Etunimi`,
 1 AS `Sukunimi`,
 1 AS `kortti_nro`,
 1 AS `idKortti`,
 1 AS `idTili`,
 1 AS `DebitTilinro`,
 1 AS `DebitSaldo`,
 1 AS `CreditTilinro`,
 1 AS `CreditSaldo`,
 1 AS `CreditLuottoraja`,
 1 AS `PVM`,
 1 AS `Tapahtuma`,
 1 AS `Maara`,
 1 AS `idTilitapahtumat`*/;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `kortti`
--

DROP TABLE IF EXISTS `kortti`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `kortti` (
  `idKortti` int NOT NULL AUTO_INCREMENT,
  `Pin` varchar(255) NOT NULL,
  `Kortti_nro` varchar(45) NOT NULL,
  `idasiakas` int NOT NULL,
  `idTili` int NOT NULL,
  PRIMARY KEY (`idKortti`,`idasiakas`,`idTili`),
  KEY `fk_Kortti_Asiakas_idx` (`idasiakas`),
  KEY `fk_Kortti_Tili` (`idTili`),
  CONSTRAINT `fk_Kortti_Asiakas` FOREIGN KEY (`idasiakas`) REFERENCES `asiakas` (`idasiakas`),
  CONSTRAINT `fk_Kortti_Tili1` FOREIGN KEY (`idTili`) REFERENCES `tili` (`idTili`)
) ENGINE=InnoDB AUTO_INCREMENT=14 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `kortti`
--

LOCK TABLES `kortti` WRITE;
/*!40000 ALTER TABLE `kortti` DISABLE KEYS */;
INSERT INTO `kortti` VALUES (1,'$2a$10$gWQDHwJ5gpI1JOWFQV0yCeHZtbV0O/DcIT29Aq2cdOT6UxbeXqHH2','FI7777777',1,2),(3,'$2a$10$bVqD0j5QIdboFzspw6vf1u6YJNFlitgbEL2XfwGA/WyKjPLKSPOLe','FI888888',1,2),(4,'$2a$10$N2J09BcvCq3zXAZcyMvGXewzBNnG7dnUb0LH8/5DImHzyKrX1bfqi','FI9999',3,2),(5,'$2a$10$ko5IcfdsEojXCZiQekWzR.OuyCHYb1XjpB7vNRewD6MZKUpWR3SnG','FI12341234',1,2),(8,'$2a$10$lJWqgAq4RV/CX6OXlnHduekfag1oBl4OlzRHhBXHxFJ0MpMviR3li','FI235648',4,4),(9,'$2a$10$SwIC3LwdUcknhGWIWkBj4e3pXwKJMnN8L1ZofiGel.1O9vF92L0Pe','FI235598',5,5),(10,'$2a$10$U75oQ8WPcSxXCGpTUhaG5Oq6gZQnwHcC1xQ32Way.ELAo23BXoFlq','FI238998',6,6),(11,'$2a$10$Rr0XLXCUHHGgCPyc70tYVeJcvopfxyp1.qlhgmm0W5.k8aVMiSICC','FI526599D',7,7),(11,'$2a$10$bIkpRThTNu2STCB5MSWg9.4Z4nBZkYAGPs8tf4dwwLh6hsLXWrOOa','FI526599C',7,8),(12,'$2a$10$buI2ju4oUX5LQ.eG8lhUUu6XgzKcRplzSan9tLj6eGUa3I4kzfCxa','FI526600',8,9);
/*!40000 ALTER TABLE `kortti` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tili`
--

DROP TABLE IF EXISTS `tili`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `tili` (
  `idTili` int NOT NULL AUTO_INCREMENT,
  `DebitTilinro` varchar(45) DEFAULT NULL,
  `DebitSaldo` decimal(15,2) unsigned DEFAULT NULL,
  `CreditTilinro` varchar(45) DEFAULT NULL,
  `CreditSaldo` decimal(15,2) unsigned DEFAULT NULL,
  `CreditLuottoraja` decimal(15,2) unsigned DEFAULT NULL,
  PRIMARY KEY (`idTili`),
  UNIQUE KEY `Tilinumero_UNIQUE` (`DebitTilinro`) /*!80000 INVISIBLE */,
  UNIQUE KEY `CreditTilinro_UNIQUE` (`CreditTilinro`)
) ENGINE=InnoDB AUTO_INCREMENT=10 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tili`
--

LOCK TABLES `tili` WRITE;
/*!40000 ALTER TABLE `tili` DISABLE KEYS */;
INSERT INTO `tili` VALUES (2,'FI655740123456',2.00,NULL,NULL,NULL),(3,'FI678989123456',2261.08,'FI688989123456',14860.98,15000.00),(4,'FI5523562564236512',4138.68,NULL,NULL,NULL),(5,'FI5523562564238954',8886.43,NULL,NULL,NULL),(6,NULL,NULL,'FI5523562564238896',813.06,1500.00),(7,'FI5523562564235542',23428.08,NULL,NULL,NULL),(8,NULL,NULL,'FI5523562564235543',681.21,2000.00),(9,'FI5523562564231222',860.98,NULL,NULL,NULL);
/*!40000 ALTER TABLE `tili` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tilitapahtumat`
--

DROP TABLE IF EXISTS `tilitapahtumat`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `tilitapahtumat` (
  `idTilitapahtumat` int NOT NULL AUTO_INCREMENT,
  `Pvm` datetime NOT NULL,
  `Tapahtuma` varchar(45) NOT NULL,
  `Maara` decimal(15,2) NOT NULL,
  `idTili` int NOT NULL,
  PRIMARY KEY (`idTilitapahtumat`,`idTili`),
  KEY `fk_Tilitapahtumat_Tili1_idx` (`idTili`) /*!80000 INVISIBLE */,
  CONSTRAINT `fk_Tilitapahtumat_Tili1` FOREIGN KEY (`idTili`) REFERENCES `tili` (`idTili`)
) ENGINE=InnoDB AUTO_INCREMENT=150 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tilitapahtumat`
--

LOCK TABLES `tilitapahtumat` WRITE;
/*!40000 ALTER TABLE `tilitapahtumat` DISABLE KEYS */;
INSERT INTO `tilitapahtumat` VALUES (1,'2023-03-28 00:00:00','K-Market',-16.20,2),(2,'2023-03-26 00:00:00','Kela',250.28,2),(3,'2023-02-25 00:00:00','R-kioski',-12.50,3),(79,'2023-03-31 00:00:00','Palkka',3200.00,4),(80,'2023-04-02 20:48:32','Kallen Kioski',-25.00,4),(81,'2023-04-03 09:48:32','R-Kioski',-16.80,4),(82,'2023-04-03 15:00:02','Prisma Mäntylä',-150.18,4),(83,'2023-04-03 17:05:20','Finnkino',-22.90,4),(84,'2023-04-03 20:05:20','CoffeeHouse',-15.74,4),(85,'2023-04-04 12:05:00','Tilisiirto',250.00,4),(86,'2023-04-04 12:15:00','Tilisiirto',25.00,4),(87,'2023-04-05 12:27:56','Ikea',-120.00,4),(88,'2023-04-06 07:03:00','Julkinen liikenne',-2.05,4),(89,'2023-04-06 13:07:14','Sale Joutsenlampi',-33.05,4),(92,'2023-04-12 19:29:06','Ikea',-100.00,8),(93,'2023-03-31 00:00:00','Palkka',3500.00,7),(94,'2023-04-01 00:00:00','Vuokra',-925.28,7),(94,'2023-04-12 20:01:41','Systembolaget',-45.55,8),(95,'2023-04-12 19:30:58','Kalles Godis',-10.00,7),(97,'2023-04-13 15:17:39','Kahvila KultaKatriina',-32.24,7),(101,'2023-04-13 15:31:56','Taidemuseo Taivaanrannanmaalari',-52.82,7),(102,'2023-04-13 15:33:52','Suomalainen Kirjakauppa',-68.45,7),(103,'2023-04-13 15:34:36','Citymarket Markkala',-255.99,7),(104,'2023-04-13 18:23:21','Kahvila Pannu',-15.60,8),(105,'2023-04-13 18:23:30','Kahvila Pannu',-15.60,4),(106,'2023-04-13 18:25:06','Tilisiirto',150.00,7),(107,'2023-04-13 18:26:03','Tilisiirto',150.00,4),(108,'2023-04-13 18:28:29','Sale Myllytulli',-6.20,4),(110,'2023-04-13 18:42:35','Syntymäpäivälahja',150.00,7),(111,'2023-04-13 18:43:31','Kansallisbaletti',-155.99,7),(112,'2023-04-13 18:44:42','ABC',-77.71,8),(113,'2023-04-13 18:47:26','Vepsäläinen',-203.12,8),(114,'2023-04-13 18:48:49','Kultajousi',-88.99,8),(115,'2023-04-13 18:49:09','Hesburger',-25.80,8),(116,'2023-04-13 18:50:12','ebookers',-550.00,8),(117,'2023-04-13 18:50:40','Verkkokauppa',-55.00,8),(118,'2023-04-13 18:51:27','Kallen Kioski',-5.50,8),(119,'2023-04-13 18:51:47','Tokmanni',-15.50,8),(120,'2023-04-13 18:52:24','Tokmanni',-15.50,7),(121,'2023-04-13 18:52:50','Finnkino',-16.80,7),(122,'2023-04-13 18:53:08','R-Kioski',-22.22,7),(123,'2023-04-01 18:55:03','Finnkino',-15.50,6),(124,'2023-04-03 12:13:15','Ikea',-150.58,6),(125,'2023-04-03 14:33:01','Stystembolaget',-28.22,6),(126,'2023-04-05 08:15:13','R-Kioski',-2.05,6),(127,'2023-04-05 11:01:01','Bistro Pain Au Chocolat',-32.43,6),(128,'2023-04-05 13:42:59','Suomalainen Kirjakauppa',-65.00,6),(129,'2023-04-16 15:21:11','R-Kioski',-3.80,6),(130,'2023-04-16 15:39:06','Julkinen liikenne',-2.05,6),(131,'2023-04-16 15:41:06','R-Kioski',-10.00,6),(132,'2023-04-20 10:14:22','Kallen Kiska',-2.50,6),(139,'2023-04-20 10:15:58','Koivurannan Kahvila',-36.82,6),(141,'2023-04-22 20:00:43','Fantasia Pelit',-45.61,6),(142,'2023-04-22 20:31:29','Kertun Kukkakauppa',-35.88,6),(143,'2023-04-22 20:37:43','Kertun Kukkakauppa',-48.26,4),(144,'2023-04-23 22:24:55','Koivurannan Kahvila',-36.82,6),(145,'2023-04-23 20:33:34','Tanelin taksi',-55.20,6),(146,'2023-04-23 21:33:34','R-Kioski',-12.52,6),(147,'2023-04-23 22:02:15','R-Kioski',-8.20,6),(148,'2023-04-23 22:42:31','R-Kioski',-12.52,4),(149,'2023-04-24 07:58:50','Kahvila Pannu',-4.80,4);
/*!40000 ALTER TABLE `tilitapahtumat` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping events for database 'atm'
--

--
-- Dumping routines for database 'atm'
--
/*!50003 DROP PROCEDURE IF EXISTS `LisaaTapahtuma` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_0900_ai_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`automaatti`@`localhost` PROCEDURE `LisaaTapahtuma`(
IN idAcc INT,
IN Transact VARCHAR(45),
IN Amount DECIMAL(15,2)
)
BEGIN
DECLARE testi1, testi2 INT DEFAULT 0;

START TRANSACTION;
UPDATE Tili SET DebitSaldo = DebitSaldo+Amount WHERE idTili = idAcc AND (DebitSaldo+Amount) >= 0;
SET testi1 = ROW_COUNT();
UPDATE Tili SET CreditSaldo = CreditSaldo+Amount WHERE idTili = idAcc AND (CreditSaldo+Amount) >= 0;
SET testi2 = ROW_COUNT();
	IF (testi1 > 0 OR testi2 > 0) THEN
		COMMIT;
		INSERT INTO Tilitapahtumat(idTilitapahtumat, Pvm, Tapahtuma, Maara, idTili) VALUES(NULL, CURRENT_TIMESTAMP(), Transact, Amount, idAcc);
    ELSE
		SELECT 'Tilillä ei ole riittävästi saldoa.';
        ROLLBACK;
	END IF;
END ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `LisaaTapahtuma2` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_0900_ai_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`automaatti`@`localhost` PROCEDURE `LisaaTapahtuma2`(
IN idTili INT,
IN tapahtuma VARCHAR(45),
IN maara DECIMAL(15,2)
)
BEGIN
DECLARE testi1, testi2 INT DEFAULT 0;

START TRANSACTION;
UPDATE Tili SET DebitSaldo = DebitSaldo+maara WHERE idTili AND (DebitSaldo+maara) >= 0;
SET testi1 = ROW_COUNT();
UPDATE Tili SET CreditSaldo = CreditSaldo+maara WHERE idTili AND (CreditSaldo+maara) >= 0;
SET testi2 = ROW_COUNT();
	IF (testi1 > 0 OR testi2 > 0) THEN
		COMMIT;
		INSERT INTO Tilitapahtumat(idTilitapahtumat, Pvm, Tapahtuma, Maara, idTili) VALUES(NULL, CURRENT_TIMESTAMP(), tapahtuma, maara, idTili);
    ELSE
		SELECT 'Tilillä ei ole riittävästi saldoa.';
        ROLLBACK;
	END IF;
END ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;

--
-- Final view structure for view `asiakkaantiedot`
--

/*!50001 DROP VIEW IF EXISTS `asiakkaantiedot`*/;
/*!50001 SET @saved_cs_client          = @@character_set_client */;
/*!50001 SET @saved_cs_results         = @@character_set_results */;
/*!50001 SET @saved_col_connection     = @@collation_connection */;
/*!50001 SET character_set_client      = utf8mb4 */;
/*!50001 SET character_set_results     = utf8mb4 */;
/*!50001 SET collation_connection      = utf8mb4_0900_ai_ci */;
/*!50001 CREATE ALGORITHM=UNDEFINED */
/*!50013 DEFINER=`automaatti`@`localhost` SQL SECURITY DEFINER */
/*!50001 VIEW `asiakkaantiedot` AS select `asiakas`.`idasiakas` AS `IdAsiakas`,`asiakas`.`Etunimi` AS `Etunimi`,`asiakas`.`Sukunimi` AS `Sukunimi`,`kortti`.`idKortti` AS `IdKortti`,`kortti`.`Kortti_nro` AS `Kortti_nro`,`tili`.`idTili` AS `IdTili`,`tili`.`DebitTilinro` AS `DebitTilinro`,`tili`.`DebitSaldo` AS `DebitSaldo`,`tili`.`CreditTilinro` AS `CreditTilinro`,`tili`.`CreditSaldo` AS `CreditSaldo`,`tili`.`CreditLuottoraja` AS `CreditLuottoraja` from ((`asiakas` join `kortti` on((`asiakas`.`idasiakas` = `kortti`.`idasiakas`))) join `tili` on((`kortti`.`idTili` = `tili`.`idTili`))) */;
/*!50001 SET character_set_client      = @saved_cs_client */;
/*!50001 SET character_set_results     = @saved_cs_results */;
/*!50001 SET collation_connection      = @saved_col_connection */;

--
-- Final view structure for view `asiakkaantilitapahtumat`
--

/*!50001 DROP VIEW IF EXISTS `asiakkaantilitapahtumat`*/;
/*!50001 SET @saved_cs_client          = @@character_set_client */;
/*!50001 SET @saved_cs_results         = @@character_set_results */;
/*!50001 SET @saved_col_connection     = @@collation_connection */;
/*!50001 SET character_set_client      = utf8mb4 */;
/*!50001 SET character_set_results     = utf8mb4 */;
/*!50001 SET collation_connection      = utf8mb4_0900_ai_ci */;
/*!50001 CREATE ALGORITHM=UNDEFINED */
/*!50013 DEFINER=`automaatti`@`localhost` SQL SECURITY DEFINER */
/*!50001 VIEW `asiakkaantilitapahtumat` AS select `asiakas`.`idasiakas` AS `idAsiakas`,`asiakas`.`Etunimi` AS `Etunimi`,`asiakas`.`Sukunimi` AS `Sukunimi`,`kortti`.`Kortti_nro` AS `kortti_nro`,`kortti`.`idKortti` AS `idKortti`,`tili`.`idTili` AS `idTili`,`tili`.`DebitTilinro` AS `DebitTilinro`,`tili`.`DebitSaldo` AS `DebitSaldo`,`tili`.`CreditTilinro` AS `CreditTilinro`,`tili`.`CreditSaldo` AS `CreditSaldo`,`tili`.`CreditLuottoraja` AS `CreditLuottoraja`,date_format(`tilitapahtumat`.`Pvm`,'%T %d.%m.%Y') AS `PVM`,`tilitapahtumat`.`Tapahtuma` AS `Tapahtuma`,`tilitapahtumat`.`Maara` AS `Maara`,`tilitapahtumat`.`idTilitapahtumat` AS `idTilitapahtumat` from (((`asiakas` join `kortti` on((`asiakas`.`idasiakas` = `kortti`.`idasiakas`))) join `tili` on((`kortti`.`idTili` = `tili`.`idTili`))) join `tilitapahtumat` on((`tili`.`idTili` = `tilitapahtumat`.`idTili`))) */;
/*!50001 SET character_set_client      = @saved_cs_client */;
/*!50001 SET character_set_results     = @saved_cs_results */;
/*!50001 SET collation_connection      = @saved_col_connection */;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2023-04-24  8:09:24
