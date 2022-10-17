package com.example.exp_2.model;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * SKU = Stock Keeping Unit 库存量单位
 * SPU = Standard Product Unit 标准化产品单元
 *
 * @author 529106896
 */

@Data
@ApiModel(description = "商品SKU对象")
public class GoodsSKURetVo {

    @ApiModelProperty(value = "商品id")
    private Integer id;

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

    public GoodsSKURetVo(GoodsSKU goodsSKU) {
        this.id = goodsSKU.getId();
        this.goodsSpuId = goodsSKU.getGoodsSpuId();
        this.skuSn = goodsSKU.getSkuSn();
        this.name = goodsSKU.getName();
        this.originalPrice = goodsSKU.getOriginalPrice();
        this.configuration = goodsSKU.getConfiguration();
        this.weight = goodsSKU.getWeight();
        this.imageUrl = goodsSKU.getImageUrl();
        this.inventory = goodsSKU.getInventory();
        this.detail = goodsSKU.getDetail();
        this.disabled = goodsSKU.getDisabled();

        if (null != goodsSKU.getState()) {
            this.state = goodsSKU.getState().getDescription();
        }
    }

}
