package com.example.exp_2.dao;

import com.example.exp_2.Exp2Application;
import com.example.exp_2.dao.OrdersDao;
import com.example.exp_2.mapper.OrdersMapper;
import com.example.exp_2.model.OrderItemPo;
import com.example.exp_2.model.Orders;
import com.example.exp_2.model.OrdersPo;
import com.example.exp_2.model.OrdersVo;
import com.example.exp_2.util.OrdersFactoty;
import org.junit.jupiter.api.Test;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.transaction.annotation.Transactional;

import java.util.ArrayList;
import java.util.List;

@SpringBootTest(classes = Exp2Application.class)
public class OrdersDaoTest {

    private Logger logger = LoggerFactory.getLogger(OrdersDaoTest.class);

    @Autowired
    private OrdersMapper ordersMapper;

    @Test
    public void findOrdersTest() {
        OrdersPo ordersPo = new OrdersPo();
        ordersPo.setId(100);
        List<OrdersPo> ordersPos = ordersMapper.findOrdersTest(ordersPo);
        for(OrdersPo o : ordersPos) {
            logger.info("findOrdersTest : ordersPo = " + o);
        }
    }

    @Test
    public void findOrderItemTest() {
        OrderItemPo orderItemPo = new OrderItemPo();
        orderItemPo.setOrderId(100);

        List<OrderItemPo> orderItemPos = ordersMapper.findOrderItemsTest(orderItemPo);

        for(OrderItemPo o : orderItemPos) {
            logger.info("findOrderItemsTest : orderItemPo = " + o);
        }
    }

    @Test
    public void findOrdersWithItemTest() {
        OrdersPo ordersPo = new OrdersPo();
        ordersPo.setId(100);
        List<OrdersPo> ordersPos = ordersMapper.findOrdersWithItemTest(ordersPo);

        for (OrdersPo o : ordersPos) {
            logger.info("findOrdersWithItemTest : ordersPo = " + o);
        }
    }

    @Test
    @Transactional
    public void createOrderItemTest() {
        OrderItemPo orderItemPo = new OrderItemPo();
        orderItemPo.setOrderId(99999);

        int isCreateSuccess = ordersMapper.createOrderItem(orderItemPo);

        if (isCreateSuccess == 1) {
            logger.info("createOrderItemTest : orderItemPo = " + orderItemPo);
            List<OrderItemPo> orderItemPos = ordersMapper.findOrderItemsTest(orderItemPo);
            for(OrderItemPo o : orderItemPos) {
                logger.info("findOrderItemsTest : orderItemPo = " + o);
            }
        }
    }

    @Test
    @Transactional
    public void createOrders() {
        OrdersVo ordersVo = OrdersFactoty.getInstance().createOrdersVo();
    }


}
