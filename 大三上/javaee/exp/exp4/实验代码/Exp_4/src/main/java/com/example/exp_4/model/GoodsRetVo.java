package com.example.exp_4.model;

import lombok.Data;

@Data
public class GoodsRetVo {

    private Integer id;

    private String name;

    private String goodsSn;

    private String imageUrl;

    private Integer state;

    private String gmtCreate;

    private String gmtModified;

    private Boolean disable;

    public GoodsRetVo(Goods goods) {

        this.id = goods.getId();

        if(null != goods.getName()) {
            this.name = goods.getName();
        } else {
            this.name = "string";
        }

        if(null != goods.getGoodsSn()) {
            this.goodsSn = goods.getGoodsSn();
        } else {
            this.goodsSn = "string";
        }

        if(null != goods.getImageUrl()) {
            this.imageUrl = goods.getImageUrl();
        } else {
            this.imageUrl = "string";
        }

        this.state = 0;

        if(null != goods.getGmtCreate()) {
            if(goods.getGmtCreate().toString().contains("T")) {
                this.gmtCreate = goods.getGmtCreate().toString().replaceAll("T", " ");
            } else {
                this.gmtCreate = goods.getGmtCreate().toString();
            }
        } else {
            this.gmtCreate = "string";
        }

        if(null != goods.getGmtModified()) {
            if(goods.getGmtModified().toString().contains("T")) {
                this.gmtModified = goods.getGmtModified().toString().replaceAll("T", " ");
            } else {
                this.gmtModified = goods.getGmtModified().toString();
            }
        } else {
            this.gmtModified = "string";
        }

        if(null != goods.getDisabled()) {
            this.disable = goods.getDisabled();
        } else {
            this.disable = false;
        }


    }
}
