package com.example.exp_4.model;

import lombok.Data;
import org.apache.ibatis.type.Alias;

import java.time.LocalDateTime;

@Data
@Alias("GoodsPo")
public class GoodsPo {

    private Integer id;

    private String name;

    private Integer brandId;

    private Integer categoryId;

    private Integer freightId;

    private Integer shopId;

    private String goodsSn;

    private String detail;

    private String imageUrl;

    private Boolean disabled;

    private LocalDateTime gmtCreate;

    private LocalDateTime gmtModified;
}
