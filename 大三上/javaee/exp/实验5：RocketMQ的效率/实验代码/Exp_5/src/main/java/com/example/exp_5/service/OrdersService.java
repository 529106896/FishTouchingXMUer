package com.example.exp_5.service;

import com.example.exp_5.dao.OrdersDao;
import com.example.exp_5.model.Orders;
import com.example.exp_5.model.OrdersPo;
import com.example.exp_5.model.OrdersVo;
import com.example.exp_5.model.VoObject;
import com.example.exp_5.util.ResponseCode;
import com.example.exp_5.util.ReturnObject;
import org.apache.rocketmq.client.producer.SendCallback;
import org.apache.rocketmq.client.producer.SendResult;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.messaging.support.MessageBuilder;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;
import org.apache.rocketmq.spring.core.RocketMQTemplate;
import com.example.exp_5.util.JacksonUtil;
import javax.annotation.Resource;
import java.time.LocalDateTime;
import java.util.List;

@Service
public class OrdersService {
    private Logger logger = LoggerFactory.getLogger(OrdersService.class);

    @Autowired
    private OrdersDao ordersDao;


    @Resource
    private RocketMQTemplate rocketMQTemplate;

    @Value("${rocketmqdemo.order-topic.delay-level}")
    private int delayLevel;

    @Value("${rocketmqdemo.order-topic.timeout}")
    private long timeout;
    /**
     * 获取订单信息
     * @param id 订单id
     * @return 订单对象
     */
    public ReturnObject<VoObject> findById(Integer id) {
        OrdersPo queryObj = new OrdersPo();
        queryObj.setId(id);
        ReturnObject<VoObject> retOrders = null;
        ReturnObject<List<Orders>> returnObject = ordersDao.findOrders(queryObj);

        if(returnObject.getCode().equals(ResponseCode.OK)) {
            if (returnObject.getData().size() == 1) {
                retOrders = new ReturnObject<>(returnObject.getData().get(0));
            }else {
                retOrders = new ReturnObject<>(ResponseCode.RESOURCE_ID_NOTEXIST);
            }
        }else {
            retOrders = new ReturnObject<>(returnObject.getCode(), returnObject.getErrmsg());
        }
        return retOrders;
    }

    @Transactional
    public ReturnObject<VoObject> createOrders(OrdersVo ordersVo) {
        logger.info("createOrders: ordersVo = " + ordersVo);
        Orders orders = ordersVo.createOrders();
        logger.info("createOrders: orders = " + orders);
        ReturnObject<Orders> retObj = ordersDao.createOrders(orders);
        ReturnObject<VoObject> retOrders = null;
        if(retObj.getCode().equals(ResponseCode.OK)) {
            retOrders = new ReturnObject<>(retObj.getData());
        }else {
            retOrders = new ReturnObject<>(retObj.getCode(), retObj.getErrmsg());
        }
        logger.info("createOrders: retOrders = " + retOrders.getData());
        return retOrders;
    }

    public ReturnObject<VoObject> sendCreateOrderMessage(OrdersVo ordersVo) {
        logger.info("sendCreateOrderMessage : send meaasage ordersVo" + ordersVo + " delay ="+delayLevel+" time =" + LocalDateTime.now());
        ReturnObject<VoObject>[] retOrders = new ReturnObject[]{null};
        String json = JacksonUtil.toJson(ordersVo);
	    retOrders[0] =new ReturnObject<>(ordersVo.createOrders());
        rocketMQTemplate.asyncSend("orders-topic", MessageBuilder.withPayload(json).build(), new SendCallback() {
            @Override
            public void onSuccess(SendResult sendResult) {
                logger.info("sendCreateOrderMessage: onSuccess result = "+sendResult+" time = " + LocalDateTime.now());
                retOrders[0] =new ReturnObject<>(ordersVo.createOrders());
            }

            @Override
            public void onException(Throwable throwable) {
                logger.info("sendCreateMessage: onException e = "+ throwable.getMessage()+ " time="+LocalDateTime.now());
                retOrders[0] =new ReturnObject<>(ResponseCode.FIELD_NOTVALID);
            }
        });
        return retOrders[0];
    }      

    public ReturnObject<VoObject> searchByConsignee(String Consignee) {
        OrdersPo queryObj = new OrdersPo();
        queryObj.setConsignee(Consignee);
        ReturnObject<VoObject> retOrders = null;
        ReturnObject<List<Orders>> returnObject = ordersDao.findOrders(queryObj);
        logger.info("searchByConsignee: returnObject = " + returnObject.getCode());
        if (returnObject.getCode().equals(ResponseCode.OK)) {
            if (returnObject.getData().size() == 1) {
                retOrders = new ReturnObject<>(returnObject.getData().get(0));
            }else{
                retOrders = new ReturnObject<>();
            }
        }else{
            retOrders = new ReturnObject<>(returnObject.getCode(), returnObject.getErrmsg());
        }
        logger.info("searchByConsignee: retOrders = " + retOrders);
        return retOrders;
    }
}
