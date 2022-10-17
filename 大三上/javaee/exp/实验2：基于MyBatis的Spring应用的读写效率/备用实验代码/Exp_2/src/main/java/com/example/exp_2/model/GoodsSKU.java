package com.example.exp_2.model;

import java.time.LocalDateTime;
import java.util.HashMap;
import java.util.Map;

public class GoodsSKU implements VoObject {

    public enum Status {
        UNPUBLISHED(0,"未发布"),
        PUBLISHED(1,"发布"),
        DELETED(2,"废弃");

        private static final Map<Integer, Status> stateMap;

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

    public enum Disabled {
        UNDELETED(0,"可以访问"),
        DELETED(1, "禁止访问");

        private int code;
        private String description;
        private static final Map<Integer, Disabled> disabledMap;

        Disabled(int code, String description) {
            this.code = code;
            this.description = description;
        }

        static { //由类加载机制，静态块初始加载对应的枚举属性到map中，而不用每次取属性时，遍历一次所有枚举值
            disabledMap = new HashMap();
            for (Disabled enum1 : values()) {
                disabledMap.put(enum1.code, enum1);
            }
        }

        public static Disabled getDisabledByCode(Integer code) {
            return disabledMap.get(code);
        }

        public Integer getCode() {
            return code;
        }

        public String getDescription() {
            return description;
        }

    }

    private GoodsSKUPo goodsSKUPo;

    public GoodsSKU() {
        this.goodsSKUPo = new GoodsSKUPo();
    }

    public GoodsSKU(GoodsSKUPo goodsSKUPo) {
        this.goodsSKUPo = goodsSKUPo;
    }

    @Override
    public Object createVo() {
        return new GoodsSKURetVo(this);
    }

    public GoodsSKUPo getGoodsSKUPo() {
        return this.goodsSKUPo;
    }

    public Integer getId() {
        return goodsSKUPo.getId();
    }

    public void setId(Integer id) {
        goodsSKUPo.setId(id);
    }

    public Integer getGoodsSpuId() {
        return goodsSKUPo.getGoodsSpuId();
    }

    public void setGoodsSpuId(Integer goodsSpuId) {
        goodsSKUPo.setGoodsSpuId(goodsSpuId);
    }

    public String getSkuSn() {
        return goodsSKUPo.getSkuSn();
    }

    public void setSkuSn(String skuSn) {
        goodsSKUPo.setSkuSn(skuSn);
    }

    public String getName() {
        return goodsSKUPo.getName();
    }

    public void setName(String name) {
        goodsSKUPo.setName(name);
    }

    public Integer getOriginalPrice() {
        return goodsSKUPo.getOriginalPrice();
    }

    public void setOriginalPrice(Integer originalPrice) {
        goodsSKUPo.setOriginalPrice(originalPrice);
    }

    public String getConfiguration() {
        return goodsSKUPo.getConfiguration();
    }

    public void setConfiguration(String configuration) {
        goodsSKUPo.setConfiguration(configuration);
    }

    public Integer getWeight() {
        return goodsSKUPo.getWeight();
    }

    public void setWeight(Integer weight) {
        goodsSKUPo.setWeight(weight);
    }

    public String getImageUrl() {
        return goodsSKUPo.getImageUrl();
    }

    public void setImageUrl(String imageUrl) {
        goodsSKUPo.setImageUrl(imageUrl);
    }

    public Integer getInventory() {
        return goodsSKUPo.getInventory();
    }

    public void setInventory(Integer inventory) {
        goodsSKUPo.setInventory(inventory);
    }

    public String getDetail() {
        return goodsSKUPo.getDetail();
    }

    public void setDetail(String detail) {
        goodsSKUPo.setDetail(detail);
    }

    public Integer getDisabled() {
        return goodsSKUPo.getDisabled();
    }

    public void setDisabled(Integer disabled) {
        goodsSKUPo.setDisabled(disabled);
    }

    public Status getState() {
        return Status.getStatusByCode(goodsSKUPo.getState());
    }

    public void setState(Status state) {
        goodsSKUPo.setState(state.getCode());
    }

    public LocalDateTime getGmtCreate() {
        return goodsSKUPo.getGmtCreate();
    }

    public void setGmtCreate(LocalDateTime gmtCreate) {
        goodsSKUPo.setGmtCreate(gmtCreate);
    }

    public LocalDateTime getGmtModified() {
        return goodsSKUPo.getGmtModified();
    }

    public void setGmtModified(LocalDateTime gmtModified) {
        goodsSKUPo.setGmtModified(gmtModified);
    }

    public boolean canEqual(Object other) {
        return goodsSKUPo.canEqual(other);
    }

    @Override
    public int hashCode() {
        return goodsSKUPo.hashCode();
    }

    @Override
    public String toString() {
        return goodsSKUPo.toString();
    }

    @Override
    public boolean equals(Object o) {
        return goodsSKUPo.equals(((GoodsSKU)o).goodsSKUPo);
    }

}

