package com.example.exp_2.util;

import com.example.exp_2.model.OrderItemVo;
import com.example.exp_2.model.OrdersVo;

import java.util.ArrayList;
import java.util.List;

public class OrdersFactoty {

    private static OrdersFactoty instance = null;

    public static OrdersFactoty getInstance() {
        if (instance == null) {
            synchronized (OrdersFactoty.class) {
                if (instance == null) {
                    instance = new OrdersFactoty();
                }
            }
        }
        return instance;
    }

    public OrdersVo createOrdersVo() {
        OrdersVo o = new OrdersVo();
        o.setConsignee("袁佳哲");
        o.setRegionId(5);
        o.setAddress("映雪三208");
        o.setMobile("18603899634");
        o.setMessage("123456");
        o.setCouponId(6);
        o.setPresaleId(7);
        o.setGrouponId(8);
        o.setOrderItemList(createOrderItemVoList());
        return o;
    }

    private List<OrderItemVo> createOrderItemVoList() {
        List<OrderItemVo> orderItemVoList = new ArrayList<>();
        OrderItemVo orderItemVo = new OrderItemVo();
        orderItemVo.setSkuId(1);
        orderItemVo.setQuantity(1);
        orderItemVo.setCouponActId(1);
        orderItemVoList.add(orderItemVo);

        orderItemVo = new OrderItemVo();
        orderItemVo.setSkuId(2);
        orderItemVo.setQuantity(2);
        orderItemVo.setCouponActId(2);
        orderItemVoList.add(orderItemVo);

        orderItemVo = new OrderItemVo();
        orderItemVo.setSkuId(3);
        orderItemVo.setQuantity(3);
        orderItemVo.setCouponActId(3);
        orderItemVoList.add(orderItemVo);

        orderItemVo = new OrderItemVo();
        orderItemVo.setSkuId(4);
        orderItemVo.setQuantity(4);
        orderItemVo.setCouponActId(4);
        orderItemVoList.add(orderItemVo);
        return orderItemVoList;
    }
}
