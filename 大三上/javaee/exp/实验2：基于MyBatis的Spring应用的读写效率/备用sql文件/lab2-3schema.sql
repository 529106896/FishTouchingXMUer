--
-- Table structure for table `goods_sku`
--

DROP TABLE IF EXISTS `goods_sku`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `goods_sku` (
  `id` bigint NOT NULL AUTO_INCREMENT,
  `goods_spu_id` bigint DEFAULT NULL,
  `sku_sn` varchar(128) DEFAULT NULL,
  `name` varchar(128) DEFAULT NULL,
  `original_price` bigint DEFAULT NULL,
  `configuration` varchar(500) DEFAULT NULL,
  `weight` bigint DEFAULT NULL,
  `image_url` varchar(255) DEFAULT NULL,
  `inventory` int DEFAULT NULL,
  `detail` varchar(500) DEFAULT NULL,
  `disabled` tinyint DEFAULT NULL,
  `gmt_create` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `gmt_modified` datetime DEFAULT NULL,
  `state` tinyint DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=680 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;


--
-- Table structure for table `orders`
--

DROP TABLE IF EXISTS `orders`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `orders` (
  `id` bigint NOT NULL AUTO_INCREMENT,
  `customer_id` bigint DEFAULT NULL,
  `shop_id` bigint DEFAULT NULL,
  `order_sn` varchar(128) DEFAULT NULL,
  `pid` bigint DEFAULT NULL,
  `consignee` varchar(64) DEFAULT NULL,
  `region_id` bigint DEFAULT NULL,
  `address` varchar(500) DEFAULT NULL,
  `mobile` varchar(128) DEFAULT NULL,
  `message` varchar(500) DEFAULT NULL,
  `order_type` tinyint DEFAULT NULL,
  `freight_price` bigint DEFAULT NULL,
  `coupon_id` bigint DEFAULT NULL,
  `coupon_activity_id` bigint DEFAULT NULL,
  `discount_price` bigint DEFAULT NULL,
  `origin_price` bigint DEFAULT NULL,
  `presale_id` bigint DEFAULT NULL,
  `groupon_discount` bigint DEFAULT NULL,
  `rebate_num` int DEFAULT NULL,
  `confirm_time` datetime DEFAULT NULL,
  `shipment_sn` varchar(128) DEFAULT NULL,
  `state` tinyint DEFAULT NULL,
  `substate` tinyint DEFAULT NULL,
  `be_deleted` tinyint DEFAULT NULL,
  `gmt_create` datetime DEFAULT CURRENT_TIMESTAMP,
  `gmt_modified` datetime DEFAULT NULL,
  `groupon_id` bigint DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=38050 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `order_item`
--

DROP TABLE IF EXISTS `order_item`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `order_item` (
  `id` bigint NOT NULL AUTO_INCREMENT,
  `order_id` bigint DEFAULT NULL,
  `goods_sku_id` bigint DEFAULT NULL,
  `quantity` int DEFAULT NULL,
  `price` bigint DEFAULT NULL,
  `discount` bigint DEFAULT NULL,
  `name` varchar(128) DEFAULT NULL,
  `coupon_activity_id` bigint DEFAULT NULL,
  `be_share_id` bigint DEFAULT NULL,
  `gmt_create` datetime DEFAULT CURRENT_TIMESTAMP,
  `gmt_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=39403 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;