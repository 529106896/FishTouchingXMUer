package com.example.exp_4.model;

import java.time.LocalDateTime;

public class Goods implements VoObject {

    private GoodsPo goodsPo;

    public Goods() {
        this.goodsPo = new GoodsPo();
    }

    public Goods(GoodsPo goodsPo) {
        this.goodsPo = goodsPo;
    }

    public GoodsPo getGoodsPo() {
        return this.goodsPo;
    }

    @Override
    public Object createVo() {
        return new GoodsRetVo(this);
    }

    public void setId(Integer id) {
        goodsPo.setId(id);
    }

    public Integer getId() {
        return goodsPo.getId();
    }

    public void setName(String name) {
        goodsPo.setName(name);
    }

    public String getName() {
        return goodsPo.getName();
    }

    public void setBrandId(Integer brandId) {
        goodsPo.setBrandId(brandId);
    }

    public Integer getBrandId() {
        return goodsPo.getBrandId();
    }

    public void setCategoryId(Integer categoryId) {
        goodsPo.setCategoryId(categoryId);
    }

    public Integer getCategoryId() {
        return goodsPo.getCategoryId();
    }

    public void setFreightId(Integer freightId) {
        goodsPo.setFreightId(freightId);
    }

    public Integer getFreightId() {
        return goodsPo.getFreightId();
    }

    public void setShopId(Integer shopId) {
        goodsPo.setShopId(shopId);
    }

    public Integer getShopId() {
        return goodsPo.getShopId();
    }

    public void setGoodsSn(String goodsSn) {
        goodsPo.setGoodsSn(goodsSn);
    }

    public String getGoodsSn() {
        return goodsPo.getGoodsSn();
    }

    public void setDetail(String detail) {
        goodsPo.setDetail(detail);
    }

    public String getDetail() {
        return goodsPo.getDetail();
    }

    public void setImageUrl(String imageUrl) {
        goodsPo.setImageUrl(imageUrl);
    }

    public String getImageUrl() {
        return goodsPo.getImageUrl();
    }

    public void setDisabled(Boolean disabled) {
        goodsPo.setDisabled(disabled);
    }

    public Boolean getDisabled() {
        return goodsPo.getDisabled();
    }

    public void setGmtCreate(LocalDateTime gmtCreate) {
        goodsPo.setGmtCreate(gmtCreate);
    }

    public LocalDateTime getGmtCreate() {
        return goodsPo.getGmtCreate();
    }

    public void setGmtModified(LocalDateTime gmtModified) {
        goodsPo.setGmtModified(gmtModified);
    }

    public LocalDateTime getGmtModified() {
        return goodsPo.getGmtModified();
    }

    public boolean canEqual(Object other) {
        return goodsPo.canEqual(other);
    }

    @Override
    public int hashCode() {
        return goodsPo.hashCode();
    }

    @Override
    public String toString() {
        return goodsPo.toString();
    }

    @Override
    public boolean equals(Object o) {
        return goodsPo.equals(((Goods)o).goodsPo);
    }
}
