package com.example.exp_5.model;

import lombok.Data;

@Data
public class OrderItemRetVo {
    private Integer skuId;

    private Integer orderId;

    private String name;

    private Integer quantity;

    private Integer price;

    private Integer discount;

    private Integer beSharedId;

    private Integer couponActId;

    public OrderItem createOrderItem() {
        OrderItem orderItem = new OrderItem();
        orderItem.setGoodsSkuId(this.skuId);
        orderItem.setOrderId(this.orderId);
        orderItem.setName(this.name);
        orderItem.setQuantity(this.quantity);
        orderItem.setPrice(this.price);
        orderItem.setDiscount(this.discount);
        orderItem.setBeShareId(this.beSharedId);
        orderItem.setCouponActivityId(this.couponActId);
        return orderItem;
    }

    public OrderItemRetVo(OrderItem orderItem) {

        if (null != orderItem.getGoodsSkuId()) {
            this.skuId = orderItem.getGoodsSkuId();
        }
        else {
            this.skuId = 0;
        }

        if (null != orderItem.getOrderId()) {
            this.orderId = orderItem.getOrderId();
        } else {
            this.orderId = 0;
        }

        if (null != orderItem.getName()) {
            this.name = orderItem.getName();
        } else {
            this.name = "string";
        }

        if (null != orderItem.getQuantity()) {
            this.quantity = orderItem.getQuantity();
        } else {
            this.quantity = 0;
        }

        if (null != orderItem.getPrice()) {
            this.price = orderItem.getPrice();
        } else {
            this.price = 0;
        }

        if (null != orderItem.getDiscount()) {
            this.discount = orderItem.getDiscount();
        } else {
            this.discount = 0;
        }

        if (null != orderItem.getBeShareId()) {
            this.beSharedId = orderItem.getBeShareId();
        } else {
            this.beSharedId = 0;
        }

        if (null != orderItem.getCouponActivityId()) {
            this.couponActId = orderItem.getCouponActivityId();
        } else {
            this.couponActId = 0;
        }
    }
}
