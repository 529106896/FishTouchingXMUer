package com.example.exp_4.model;

import java.io.Serializable;
import java.time.LocalDateTime;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Product implements VoObject, Serializable {

    public enum Status {
        CREATED(0, "正常"),
        OFF_SHELVES(1, "已下架"),
        DELETED(2, "已删除");

        private static final Map<Integer, Status> statusMap;

        static {
            statusMap = new HashMap<>();
            for(Status enum1 : values()) {
                statusMap.put(enum1.code, enum1);
            }
        }

        private int code;
        private String description;

        Status(int code, String description) {
            this.code = code;
            this.description = description;
        }

        public static Status getStatusByCode(Integer code) {
            return statusMap.get(code);
        }

        public Integer getCode() {
            return code;
        }

        public String getDescription() {
            return description;
        }

    }

    private ProductPo productPo;

    public Product() {
        this.productPo = new ProductPo();
    }

    public Product(ProductPo productPo) {
        this.productPo = productPo;
    }

    public ProductPo getProductPo() {
        return this.productPo;
    }

    public void setId(Integer id) {
        productPo.setId(id);
    }

    public Integer getId() {
        return productPo.getId();
    }

    public void setGoodsId(Integer goodsId) {
        productPo.setGoodsId(goodsId);
    }

    public Integer getGoodsId() {
        return productPo.getGoodsId();
    }

    public void setName(String name) {
        productPo.setName(name);
    }

    public String getName() {
        return productPo.getName();
    }

    public void setProductSn(String productSn) {
        productPo.setProductSn(productSn);
    }

    public String getProductSn() {
        return productPo.getProductSn();
    }

    public void setOriginalPrice(Integer originalPrice) {
        productPo.setOriginalPrice(originalPrice);
    }

    public Integer getOriginalPrice() {
        return productPo.getOriginalPrice();
    }

    public void setWeight(Integer weight) {
        productPo.setWeight(weight);
    }

    public Integer getWeight() {
        return productPo.getWeight();
    }

    public void setImageUrl(String imageUrl) {
        productPo.setImageUrl(imageUrl);
    }

    public String getImageUrl() {
        return productPo.getImageUrl();
    }

    public void setState(Integer status) {
        productPo.setState(status);
    }

    public Integer getState() {
        return 0;
    }

    public void setDetail(String detail) {
        productPo.setDetail(detail);
    }

    public String getDetail() {
        return productPo.getDetail();
    }

    public void setDisabled(Boolean disabled) {
        productPo.setDisabled(disabled);
    }

    public Boolean getDisabled() {
        return productPo.getDisabled();
    }

    public void setGmtCreate(LocalDateTime gmtCreate) {
        productPo.setGmtCreate(gmtCreate);
    }

    public LocalDateTime getGmtCreate() {
        return productPo.getGmtCreate();
    }

    public void setGmtModified(LocalDateTime gmtModified) {
        productPo.setGmtModified(gmtModified);
    }

    public LocalDateTime getGmtModified() {
        return productPo.getGmtModified();
    }

    private List<Goods> goodsList;

    public void setGoodsList(List<Goods> goodsList) {
        this.goodsList = goodsList;
    }

    public List<Goods> getGoodsList() {
        return this.goodsList;
    }

    public boolean canEqual(Object other) {
        return productPo.canEqual(other);
    }

    @Override
    public Object createVo() {
        return new ProductRetVo(this);
    }

    @Override
    public int hashCode() {
        return productPo.hashCode();
    }

    @Override
    public String toString() {
        return productPo.toString();
    }

    @Override
    public boolean equals(Object o) {
        return productPo.equals(((Product)o).productPo);
    }

}
