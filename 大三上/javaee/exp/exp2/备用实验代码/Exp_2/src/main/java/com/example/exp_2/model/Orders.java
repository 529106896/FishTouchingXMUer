package com.example.exp_2.model;


import java.time.LocalDateTime;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Orders implements VoObject {

    /**
     * 订单状态
     */
    public enum Status {
        CREATED(0,"已创建"),
        TIMEOUT(1,"超时"),
        CANCELED(2,"已取消"),
        PAYED(3, "已支付");

        private static final Map<Integer, Orders.Status> stateMap;

        static { //由类加载机制，静态块初始加载对应的枚举属性到map中，而不用每次取属性时，遍历一次所有枚举值
            stateMap = new HashMap();
            for (Status enum1 : values()) {
                stateMap.put(enum1.code, enum1);
            }
        }

        private int code;
        private String description;

        Status(int code, String description) {
            this.code=code;
            this.description=description;
        }

        public static Status getStatusByCode(Integer code){
            return stateMap.get(code);
        }

        public Integer getCode(){
            return code;
        }

        public String getDescription() {return description;}

    }

    /**
     * 订单类型
     */
    public enum Type {
        NORMAL(0,"普通"),
        GROUPON(1,"团购"),
        PRESALE(2,"预售");

        private static final Map<Integer, Type> typeMap;

        static { //由类加载机制，静态块初始加载对应的枚举属性到map中，而不用每次取属性时，遍历一次所有枚举值
            typeMap = new HashMap();
            for (Orders.Type enum1 : values()) {
                typeMap.put(enum1.code, enum1);
            }
        }

        private int code;
        private String description;

        Type(int code, String description) {
            this.code=code;
            this.description=description;
        }

        public static Orders.Type getTypeByCode(Integer code){
            return typeMap.get(code);
        }

        public Integer getCode(){
            return code;
        }

        public String getDescription() {return description;}

    }

    public enum Deleted {
        UNDELETED(0,"可以访问"),
        DELETED(1, "禁止访问");

        private int code;
        private String description;
        private static final Map<Integer, Deleted> deletedMap;

        Deleted(int code, String description) {
            this.code = code;
            this.description = description;
        }

        static { //由类加载机制，静态块初始加载对应的枚举属性到map中，而不用每次取属性时，遍历一次所有枚举值
            deletedMap = new HashMap();
            for (Deleted enum1 : values()) {
                deletedMap.put(enum1.code, enum1);
            }
        }

        public static Deleted getDisabledByCode(Integer code) {
            return deletedMap.get(code);
        }

        public Integer getCode() {
            return code;
        }

        public String getDescription() {
            return description;
        }

    }

    private OrdersPo ordersPo;

    public Orders() {
        this.ordersPo = new OrdersPo();
    }

    public Orders(OrdersPo ordersPo) {
        this.ordersPo = ordersPo;
    }

    @Override
    public Object createVo() {
        return new OrdersRetVo(this);
    }

    public OrdersPo getOrdersPo() {
        return this.ordersPo;
    }

    public Integer getId() {
        return ordersPo.getId();
    }

    public void setId(Integer id) {
        ordersPo.setId(id);
    }

    public Integer getCustomerId() {
        return ordersPo.getCustomerId();
    }

    public void setCustomerId(Integer customerId) {
        ordersPo.setCustomerId(customerId);
    }

    public Integer getShopId() {
        return ordersPo.getShopId();
    }

    public void setShopId(Integer shopId) {
        ordersPo.setShopId(shopId);
    }

    public String getOrderSn() {
        return ordersPo.getOrderSn();
    }

    public void setOrderSn(String orderSn) {
        ordersPo.setOrderSn(orderSn);
    }

    public Integer getPid() {
        return ordersPo.getPid();
    }

    public void setPid(Integer pid) {
        ordersPo.setPid(pid);
    }

    public String getConsignee() {
        return ordersPo.getConsignee();
    }

    public void setConsignee(String consignee) {
        ordersPo.setConsignee(consignee);
    }

    public Integer getRegionId() {
        return ordersPo.getRegionId();
    }

    public void setRegionId(Integer regionId) {
        ordersPo.setRegionId(regionId);
    }

    public String getAddress() {
        return ordersPo.getAddress();
    }

    public void setAddress(String address) {
        ordersPo.setAddress(address);
    }

    public String getMobile() {
        return ordersPo.getMobile();
    }

    public void setMobile(String mobile) {
        ordersPo.setMobile(mobile);
    }

    public String getMessage() {
        return ordersPo.getMessage();
    }

    public void setMessage(String message) {
        ordersPo.setMessage(message);
    }

    public Type getOrderType() {
        return Type.getTypeByCode(ordersPo.getOrderType());
    }

    public void setOrderType(Type orderType) {
        ordersPo.setOrderType(orderType.getCode());
    }

    public Integer getFreightPrice() {
        return ordersPo.getFreightPrice();
    }

    public void setFreightPrice(Integer freightPrice) {
        ordersPo.setFreightPrice(freightPrice);
    }

    public Integer getCouponId() {
        return ordersPo.getCouponId();
    }

    public void setCouponId(Integer couponId) {
        ordersPo.setCouponId(couponId);
    }

    public Integer getCouponActivityId() {
        return ordersPo.getCouponActivityId();
    }

    public void setCouponActivityId(Integer couponActivityId) {
        ordersPo.setCouponActivityId(couponActivityId);
    }

    public Integer getDiscountPrice() {
        return ordersPo.getDiscountPrice();
    }

    public void setDiscountPrice(Integer discountPrice) {
        ordersPo.setDiscountPrice(discountPrice);
    }

    public Integer getOriginPrice() {
        return ordersPo.getOriginPrice();
    }

    public void setOriginPrice(Integer originPrice) {
        ordersPo.setOriginPrice(originPrice);
    }

    public Integer getPresaleId() {
        return ordersPo.getPresaleId();
    }

    public void setPresaleId(Integer presaleId) {
        ordersPo.setPresaleId(presaleId);
    }

    public Integer getGrouponDiscount() {
        return ordersPo.getGrouponDiscount();
    }

    public void setGrouponDiscount(Integer grouponDiscount) {
        ordersPo.setGrouponDiscount(grouponDiscount);
    }

    public Integer getRebateNum() {
        return ordersPo.getRebateNum();
    }

    public void setRebateNum(Integer rebateNum) {
        ordersPo.setRebateNum(rebateNum);
    }

    public LocalDateTime getConfirmTime() {
        return ordersPo.getConfirmTime();
    }

    public void setConfirmTime(LocalDateTime confirmTime) {
        ordersPo.setConfirmTime(confirmTime);
    }

    public String getShipmentSn() {
        return ordersPo.getShipmentSn();
    }

    public void setShipmentSn(String shipmentSn) {
        ordersPo.setShipmentSn(shipmentSn);
    }

    public Status getState() {
        return Status.getStatusByCode(ordersPo.getState());
    }

    public void setState(Status state) {
        ordersPo.setState(state.getCode());
    }

    public Status getSubState() {
        return Status.getStatusByCode(ordersPo.getSubstate());
    }

    public void setSubState(Status subState) {
        ordersPo.setState(subState.getCode());
    }

    public Deleted getBeDeleted() {
        return Deleted.getDisabledByCode(ordersPo.getBeDeleted());
    }

    public void setBeDeleted(Deleted deleted) {
        ordersPo.setBeDeleted(deleted.getCode());
    }

    public Integer getGrouponId() {
        return ordersPo.getGrouponId();
    }

    public void setGrouponId(Integer grouponId) {
        ordersPo.setGrouponId(grouponId);
    }

    public LocalDateTime getGmtCreate() {
        return ordersPo.getGmtCreate();
    }

    public void setGmtCreate(LocalDateTime gmtCreate) {
        ordersPo.setGmtCreate(gmtCreate);
    }

    public LocalDateTime getGmtModified() {
        return ordersPo.getGmtModified();
    }

    public void setGmtModified(LocalDateTime gmtModified) {
        ordersPo.setGmtModified(gmtModified);
    }

    public List<OrderItem> orderItemList;

    public List<OrderItem> getOrderItemList() {
        return orderItemList;
    }

    public void setOrderItemList(List<OrderItem> orderItemList) {
        this.orderItemList = orderItemList;
    }

    public boolean canEqual(Object other) {
        return ordersPo.canEqual(other);
    }

    @Override
    public int hashCode() {
        return ordersPo.hashCode();
    }

    @Override
    public String toString() {
        return ordersPo.toString();
    }

    @Override
    public boolean equals(Object o) {
        return ordersPo.equals(((Orders)o).ordersPo);
    }


}
