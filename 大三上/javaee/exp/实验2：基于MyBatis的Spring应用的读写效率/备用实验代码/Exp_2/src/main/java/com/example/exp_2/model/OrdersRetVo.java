package com.example.exp_2.model;

import lombok.Data;

import java.util.ArrayList;
import java.util.List;

/**
 * 订单视图对象
 */

@Data
public class OrdersRetVo {
    private Integer id;

    private String orderSn;

    private Integer pid;

    private Integer orderType;

    private Integer state;

    private Integer subState;

    private String gmtCreate;

    private String gmtModified;

    private String confirmTime;

    private Integer originPrice;

    private Integer discountPrice;

    private Integer freightPrice;

    private Integer rebateNum;

    private String message;

    private Integer regionId;

    private String address;

    private String mobile;

    private String consignee;

    private Integer couponId;

    private Integer grouponId;

    private Integer presaleId;

    private String shipmentSn;

    private List<OrderItemRetVo> orderItems;

    public OrdersRetVo(Orders orders) {

        this.id = orders.getId();

        this.orderSn = orders.getOrderSn();

        if (orders.getPid() != null) {
            this.pid = orders.getPid();
        } else {
            this.pid = 0;
        }

        if (null != orders.getOrderType()) {
            this.orderType = orders.getOrderType().getCode();
        } else {
            this.orderType = 0;
        }

        if (null != orders.getState()) {
           this.state = orders.getState().getCode();
        } else {
            this.state = 0;
        }

        if (null != orders.getSubState()) {
            this.subState = orders.getSubState().getCode();
        } else {
            this.subState = 0;
        }

        if (null != orders.getGmtCreate()) {
            if (orders.getGmtCreate().toString().contains("T"))
            {
                this.gmtCreate = orders.getGmtCreate().toString().replaceAll("T", " ");
            } else {
                this.gmtCreate = orders.getGmtCreate().toString();
            }
        } else {
            this.gmtCreate = "string";
        }

        if (null != orders.getGmtModified())
        {
            if (orders.getGmtModified().toString().contains("T"))
            {
                this.gmtModified = orders.getGmtModified().toString().replaceAll("T", " ");
            } else {
                this.gmtModified = orders.getGmtModified().toString();
            }
        } else {
            this.gmtModified = "string";
        }


        //this.gmtModified = orders.getGmtModified().toString().replaceAll("T", " ");

        if (null != orders.getConfirmTime()) {
            this.confirmTime = orders.getConfirmTime().toString();
        }
        else {
            this.confirmTime = "string";
        }

        if (orders.getOriginPrice() != null){
            this.originPrice = orders.getOriginPrice();
        } else {
            this.originPrice = 0;
        }

        if (this.discountPrice != null) {
            this.discountPrice = orders.getDiscountPrice();
        } else {
            this.discountPrice = 0;
        }

        if (null != orders.getFreightPrice()) {
            this.freightPrice = orders.getFreightPrice();
        }else {
            this.freightPrice = 0;
        }

        if (null != orders.getRebateNum()) {
            this.rebateNum = orders.getRebateNum();
        } else {
            this.rebateNum = 0;
        }

        if (null != orders.getMessage()) {
            this.message = orders.getMessage();
        } else
        {
            this.message = "string";
        }

        if (null != orders.getRegionId()) {
            this.regionId = orders.getRegionId();
        } else {
            this.regionId = 0;
        }

        if (null != orders.getAddress())
        {
            this.address = orders.getAddress();
        }
        else {
            this.address = "string";
        }

        this.mobile = orders.getMobile();

        this.consignee = orders.getConsignee();

        if (orders.getCouponId() != null) {
            this.couponId = orders.getCouponId();
        }
        else {
            this.couponId = 0;
        }

        if (orders.getPresaleId() != null) {
            this.presaleId = orders.getPresaleId();
        } else {
            this.presaleId = 0;
        }

        if (orders.getShipmentSn() != null) {
            this.shipmentSn = orders.getShipmentSn();
        } else {
            this.shipmentSn = "string";
        }

        if (orders.getGrouponId() != null) {
            this.grouponId = orders.getGrouponId();
        } else {
            this.grouponId = 0;
        }

        if (null != orders.getOrderItemList()) {
            List<OrderItemRetVo> orderItemList = new ArrayList<>(orders.getOrderItemList().size());

            for (OrderItem orderItem : orders.getOrderItemList()) {
                OrderItemRetVo orderItemRetVo = new OrderItemRetVo(orderItem);
                orderItemList.add(orderItemRetVo);
            }
            this.orderItems = orderItemList;
        }
    }

//    public Orders createOrders() {
//        Orders orders = new Orders();
//        orders.setId(this.id);
//        orders.setOrderSn(this.orderSn);
//        orders.setPid(this.pid);
//        orders.setOrderType(Orders.Type.NORMAL);
//        orders.setState(Orders.Status.CREATED);
//        orders.setSubState(Orders.Status.CREATED);
//    }

}