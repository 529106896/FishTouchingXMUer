package com.example.exp_5.dao;
import com.example.exp_5.mapper.OrdersMapper;
import com.example.exp_5.model.OrderItem;
import com.example.exp_5.model.OrderItemPo;
import com.example.exp_5.model.Orders;
import com.example.exp_5.model.OrdersPo;
import com.example.exp_5.util.ReturnObject;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Repository;

import java.util.ArrayList;
import java.util.List;

import static com.example.exp_5.util.Common.genSeqNum;

@Repository
public class OrdersDao {
    private Logger logger = LoggerFactory.getLogger(OrdersDao.class);

    @Autowired
    private OrdersMapper ordersMapper;

    public ReturnObject<List<Orders>> findOrders(OrdersPo ordersPo) {

        logger.info("findOrders: ordersPo.id = " + ordersPo.getId());

        List<OrdersPo> ordersPos = ordersMapper.findOrders(ordersPo);

        List<Orders> retOrders = new ArrayList<>(ordersPos.size());

        for (OrdersPo o : ordersPos) {
            logger.info("findOrders: ordersPo = " + o);
            List<OrderItemPo> orderItemPos = o.getOrderItemPoList();
            Orders orders = new Orders(o);
            //logger.info("findOrders: ordersPo.state = " + o.getState());
            //logger.info("findOrders: orders.state = " + orders.getState());
            List<OrderItem> orderItemList = new ArrayList<>(orderItemPos.size());
            for (OrderItemPo orderItemPo : orderItemPos) {
                OrderItem orderItem = new OrderItem(orderItemPo);
                orderItemList.add(orderItem);
            }
            orders.setOrderItemList(orderItemList);
            retOrders.add(orders);
        }
        return new ReturnObject<>(retOrders);
    }

    public ReturnObject<Orders> createOrders(Orders orders){
        OrdersPo ordersPo = orders.getOrdersPo();
        String seqNum = genSeqNum();
        ordersPo.setOrderSn(seqNum);

        int ret = ordersMapper.createOrders(ordersPo);
        if(orders.getOrderItemList()!=null){
            for (OrderItem orderItem : orders.getOrderItemList()){
                OrderItemPo orderItemPo = orderItem.getOrderItemPo();
                orderItemPo.setOrderId(orders.getId());
                orderItemPo.setPrice(5);
                ret = ordersMapper.createOrderItem(orderItemPo);
            }
        }
        ReturnObject<Orders> returnObject = new ReturnObject<>(orders);
        return returnObject;
    }
}