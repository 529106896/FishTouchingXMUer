package com.example.exp_5.model;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

@Data
@ApiModel(description = "商品SKU视图对象")
public class GoodsSKUVo {

    private static Logger logger = LoggerFactory.getLogger(GoodsSKUVo.class);

//    @ApiModelProperty(value = "商品id")
//    private Integer id;

    @ApiModelProperty(value = "商品SPUid")
    private Integer goodsSpuId;

    @ApiModelProperty(value = "SKU序号")
    private String skuSn;

    @ApiModelProperty(value = "名称")
    private String name;

    @ApiModelProperty(value = "商品原价")
    private Integer originalPrice;

    @ApiModelProperty(value = "配置参数JSON")
    private String configuration;

    @ApiModelProperty(value = "重量")
    private Integer weight;

    @ApiModelProperty(value = "图片链接")
    private String imageUrl;

    @ApiModelProperty(value = "库存量")
    private Integer inventory;

    @ApiModelProperty(value = "详细描述")
    private String detail;

    @ApiModelProperty(value = "商品状态")
    private String state;

    @ApiModelProperty(value = "能否访问")
    private Integer disabled;

    public GoodsSKU createGoodsSKU() {
        GoodsSKU goodsSKU = new GoodsSKU();
        goodsSKU.setGoodsSpuId(this.goodsSpuId);
        goodsSKU.setSkuSn(this.skuSn);
        goodsSKU.setName(this.name);
        goodsSKU.setOriginalPrice(this.originalPrice);
        goodsSKU.setConfiguration(this.configuration);
        goodsSKU.setWeight(this.weight);
        goodsSKU.setImageUrl(this.imageUrl);
        goodsSKU.setInventory(this.inventory);
        goodsSKU.setDetail(this.detail);
        goodsSKU.setDisabled(this.disabled);
        goodsSKU.setState(GoodsSKU.Status.UNPUBLISHED);

        return goodsSKU;
    }

}
