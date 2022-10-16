package com.example.exp_2.service;

import com.example.exp_2.Exp2Application;
import com.example.exp_2.dao.OrdersDao;
import com.example.exp_2.model.Orders;
import com.example.exp_2.model.OrdersPo;
import com.example.exp_2.model.OrdersVo;
import com.example.exp_2.model.VoObject;
import com.example.exp_2.util.OrdersFactoty;
import com.example.exp_2.util.ResponseCode;
import com.example.exp_2.util.ReturnObject;
import org.junit.jupiter.api.Test;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.transaction.annotation.Transactional;

import java.util.List;

@SpringBootTest(classes = Exp2Application.class)
@Transactional
public class OrdersServiceTest {

    private Logger logger = LoggerFactory.getLogger(OrdersServiceTest.class);

    @Autowired
    private OrdersService ordersService;

    @Autowired
    private OrdersDao ordersDao;

    @Test
    public void createOrdersTest() {

        OrdersVo ordersVo = OrdersFactoty.getInstance().createOrdersVo();

        Orders orders = ordersVo.createOrders();

        ReturnObject<Orders> retObj = ordersDao.createOrders(orders);

        ReturnObject<List<Orders>> ordersPos = ordersDao.findOrders(orders.getOrdersPo());

        List<Orders> ordersList = ordersPos.getData();

        for (Orders o : ordersList) {
            logger.info("createOrdersTest: orders = " + o);
        }

        //logger.info("createOrdersTest: retOrders = ");
//        ReturnObject<VoObject> retOrders = null;
//
//        if (retObj.getCode().equals(ResponseCode.OK)) {
//            retOrders = new ReturnObject<>(retObj.getData());
//        } else {
//            retOrders = new ReturnObject<>(retObj.getCode(), retObj.getErrmsg());
//        }
//        logger.info("createOrdersTest: retOrders = " + retOrders.getData());

    }
}
