package com.example.exp_4.mapper;

import com.example.exp_4.model.GoodsPo;
import com.example.exp_4.model.ProductPo;
import org.apache.ibatis.annotations.Mapper;

import java.util.List;

@Mapper
public interface ProductMapper {

    /**
     * 根据id查找Goods
     * @param goodsPo 参数是由id的GoodsPo对象
     * @return 返回一个完整的GoodsPo
     */
    List<GoodsPo> findGoods(GoodsPo goodsPo);

    List<ProductPo> findProduct(ProductPo productPo);
}
