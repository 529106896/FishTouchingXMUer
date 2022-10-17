package com.example.exp_5.model;

import java.time.LocalDateTime;

public class OrderItem {

    private OrderItemPo orderItemPo;

    public OrderItem() {
        this.orderItemPo = new OrderItemPo();
    }

    public OrderItem(OrderItemPo orderItemPo) {
        this.orderItemPo = orderItemPo;
    }

    public OrderItemPo getOrderItemPo() {
        return this.orderItemPo;
    }

    public Integer getId() {
        return orderItemPo.getId();
    }

    public void setId(Integer id) {
        orderItemPo.setId(id);
    }

    public Integer getOrderId() {
        return orderItemPo.getOrderId();
    }

    public void setOrderId(Integer orderId) {
        orderItemPo.setOrderId(orderId);
    }

    public Integer getGoodsSkuId() {
        return orderItemPo.getGoodsSkuId();
    }

    public void setGoodsSkuId(Integer goodsSkuId) {
        orderItemPo.setGoodsSkuId(goodsSkuId);
    }

    public Integer getQuantity() {
        return orderItemPo.getQuantity();
    }

    public void setQuantity(Integer quantity) {
        orderItemPo.setQuantity(quantity);
    }

    public Integer getPrice() {
        return orderItemPo.getPrice();
    }

    public void setPrice(Integer price) {
        orderItemPo.setPrice(price);
    }

    public Integer getDiscount() {
        return orderItemPo.getDiscount();
    }

    public void setDiscount(Integer discount) {
        orderItemPo.setDiscount(discount);
    }

    public String getName() {
        return orderItemPo.getName();
    }

    public void setName(String name) {
        orderItemPo.setName(name);
    }

    public Integer getCouponActivityId() {
        return orderItemPo.getCouponActivityId();
    }

    public void setCouponActivityId(Integer couponActivityId) {
        orderItemPo.setCouponActivityId(couponActivityId);
    }

    public Integer getBeShareId() {
        return orderItemPo.getBeShareId();
    }

    public void setBeShareId(Integer beShareId) {
        orderItemPo.setBeShareId(beShareId);
    }

    public LocalDateTime getGmtCreate() {
        return orderItemPo.getGmtCreate();
    }

    public void setGmtCreate(LocalDateTime gmtCreate) {
        orderItemPo.setGmtCreate(gmtCreate);
    }

    public LocalDateTime getGmtModified() {
        return orderItemPo.getGmtModified();
    }

    public void setGmtModified(LocalDateTime gmtModified) {
        orderItemPo.setGmtModified(gmtModified);
    }

}
