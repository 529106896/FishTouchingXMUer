package com.example.exp_5.model;

import lombok.Data;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.util.ArrayList;
import java.util.List;
import java.io.Serializable;

@Data
public class OrdersVo implements Serializable {

    private static Logger logger = LoggerFactory.getLogger(OrdersVo.class);

    private String consignee;

    private Integer regionId;

    private String address;

    //@NotBlank
    private String mobile;

    private String message;

    private Integer couponId;

    private Integer presaleId;

    private Integer grouponId;

    private List<OrderItemVo> orderItemList;

    public Orders createOrders() {
        Orders orders = new Orders();
        orders.setConsignee(this.consignee);
        orders.setRegionId(this.regionId);
        orders.setAddress(this.address);
        orders.setMessage(this.message);
        orders.setMobile(this.mobile);
        orders.setCouponId(this.couponId);
        orders.setGrouponId(this.grouponId);
        orders.setPresaleId(this.presaleId);

        if(null != this.orderItemList) {
            logger.info("createOrders : this.orderItemList = " + this.orderItemList);
            List<OrderItem> newOrderItemList = new ArrayList<>(this.orderItemList.size());

            for(OrderItemVo orderItemVo : this.orderItemList) {
                OrderItem orderItem = orderItemVo.createOrderItem();
                newOrderItemList.add(orderItem);
            }
            orders.setOrderItemList(newOrderItemList);
        }

//        logger.info("createOrders : orders = " + orders);
//        logger.info("createOrders : orders.List = " + orders.getOrderItemList());
        return orders;
    }
}
