package com.example.exp_2.model;

import lombok.Data;

@Data
public class OrderItemVo {
    private Integer skuId;

    private Integer quantity;

    private Integer couponActId;

    public OrderItem createOrderItem() {
        OrderItem orderItem = new OrderItem();
        orderItem.setGoodsSkuId(this.skuId);
        orderItem.setQuantity(this.quantity);
        orderItem.setCouponActivityId(this.couponActId);
        return orderItem;
    }
}
