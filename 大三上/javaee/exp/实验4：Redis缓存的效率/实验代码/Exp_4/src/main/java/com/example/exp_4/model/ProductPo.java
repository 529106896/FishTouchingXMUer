package com.example.exp_4.model;

import lombok.Data;
import org.apache.ibatis.type.Alias;

import java.time.LocalDateTime;
import java.util.List;

@Data
@Alias("ProductPo")
public class ProductPo {

    private Integer id;

    private String name;

    private Integer goodsId;

    private String productSn;

    private Integer originalPrice;

    private Integer weight;

    private String imageUrl;

    private Integer state;

    private String detail;

    private Boolean disabled;

    private LocalDateTime gmtCreate;

    private LocalDateTime gmtModified;

    private List<GoodsPo> goodsPoList;
}
