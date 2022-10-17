package com.example.exp_5.model;

import lombok.Data;
import org.apache.ibatis.type.Alias;

import java.time.LocalDateTime;

@Data
@Alias("GoodsSKUPo")
public class GoodsSKUPo {

    private Integer id;

    private Integer goodsSpuId;

    private String skuSn;

    private String name;

    private Integer originalPrice;

    private String configuration;

    private Integer weight;

    private String imageUrl;

    private Integer inventory;

    private String detail;

    private Integer disabled;

    private LocalDateTime gmtCreate;

    private LocalDateTime gmtModified;

    private Integer state;
}
