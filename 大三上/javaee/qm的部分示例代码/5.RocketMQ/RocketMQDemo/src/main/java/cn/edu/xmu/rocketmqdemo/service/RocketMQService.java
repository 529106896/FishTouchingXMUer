package cn.edu.xmu.rocketmqdemo.service;

import cn.edu.xmu.rocketmqdemo.model.Log;
import cn.edu.xmu.rocketmqdemo.model.OrderStockEvent;
import cn.edu.xmu.rocketmqdemo.util.JacksonUtil;
import org.apache.rocketmq.client.producer.SendCallback;
import org.apache.rocketmq.client.producer.SendResult;
import org.apache.rocketmq.spring.core.RocketMQTemplate;
import org.apache.rocketmq.spring.support.RocketMQHeaders;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.messaging.Message;
import org.springframework.messaging.MessageHeaders;
import org.springframework.messaging.support.MessageBuilder;
import org.springframework.stereotype.Service;
import org.springframework.util.MimeTypeUtils;

import javax.annotation.Resource;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;

/**
 * @author Ming Qiu
 * @date Created in 2020/11/7 22:53
 **/
@Service
public class RocketMQService {

    private static final Logger logger = LoggerFactory.getLogger(RocketMQService.class);

    @Resource
    private RocketMQTemplate rocketMQTemplate;


    @Value("${rocketmqdemo.order-pay-topic.delay-level}")
    private int delayLevel;

    @Value("${rocketmqdemo.order-pay-topic.timeout}")
    private long timeout;

    public void sendLogMessage(Log log){

        String json = JacksonUtil.toJson(log);
        Message message = MessageBuilder.withPayload(json).build();
        logger.info("sendLogMessage: message = " + message);
        rocketMQTemplate.sendOneWay("log-topic:1", message);
    }

    public void sendOrderPayMessage(Long orderId){
        logger.info("sendOrderPayMessage: send message orderId = "+orderId+" delay ="+delayLevel+" time =" +LocalDateTime.now());
        rocketMQTemplate.asyncSend("order-pay-topic", MessageBuilder.withPayload(orderId.toString()).build(), new SendCallback() {
            @Override
            public void onSuccess(SendResult sendResult) {
                logger.info("sendOrderPayMessage: onSuccess result = "+ sendResult+" time ="+LocalDateTime.now());
            }

            @Override
            public void onException(Throwable throwable) {
                logger.info("sendOrderPayMessage: onException e = "+ throwable.getMessage()+" time ="+LocalDateTime.now());
            }
        }, timeout * 1000, delayLevel);
    }
}
