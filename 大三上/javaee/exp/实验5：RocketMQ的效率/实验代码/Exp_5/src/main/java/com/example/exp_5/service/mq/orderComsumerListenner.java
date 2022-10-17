package com.example.exp_5.service.mq;


import com.example.exp_5.dao.OrdersDao;
import com.example.exp_5.model.OrdersVo;
import com.example.exp_5.util.JacksonUtil;
import org.apache.rocketmq.spring.annotation.ConsumeMode;
import org.apache.rocketmq.spring.annotation.RocketMQMessageListener;
import org.apache.rocketmq.spring.core.RocketMQListener;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.time.LocalDateTime;

/**
 * 消息消费者
 *
 */
@Service
@RocketMQMessageListener(topic = "orders-topic",consumeMode = ConsumeMode.CONCURRENTLY,consumeThreadMax = 10,consumerGroup = "order-group")
public class orderComsumerListenner implements RocketMQListener<String> {
    private static final Logger logger = LoggerFactory.getLogger(orderComsumerListenner.class);

    @Autowired
    private OrdersDao ordersDao;


    @Override
    public void onMessage(String s) {
        OrdersVo ordersVo = JacksonUtil.toObj(s,OrdersVo.class);
        ordersDao.createOrders(ordersVo.createOrders());
        logger.info("onMessage : got message ordersVo = " + ordersVo + " time = "+ LocalDateTime.now());
    }
}
