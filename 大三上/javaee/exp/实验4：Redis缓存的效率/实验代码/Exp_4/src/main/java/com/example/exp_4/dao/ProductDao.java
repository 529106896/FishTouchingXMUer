package com.example.exp_4.dao;

import com.example.exp_4.mapper.ProductMapper;
import com.example.exp_4.model.Goods;
import com.example.exp_4.model.GoodsPo;
import com.example.exp_4.model.Product;
import com.example.exp_4.model.ProductPo;
import com.example.exp_4.util.RedisUtil;
import com.example.exp_4.util.ReturnObject;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Repository;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

@Repository
public class ProductDao {

    @Autowired
    private ProductMapper productMapper;

    @Autowired
    private RedisUtil redisUtil;

    // 这里使用@Value，括号内是$，说明这个信息要从配置文件中读取
    @Value("${exp_4.product.expiretime}")
    private long productTimeout;

    public ReturnObject<List<Goods>> findGoods(GoodsPo goodsPo) {
        List<GoodsPo> goodsPoList = productMapper.findGoods(goodsPo);
        List<Goods> retGoods = new ArrayList<>(goodsPoList.size());

        for(GoodsPo g : goodsPoList) {
            Goods goods = new Goods(g);
            //System.out.println(goods);
            retGoods.add(goods);
        }

        return new ReturnObject<>(retGoods);
    }

    public ReturnObject<List<Product>> findProduct(ProductPo productPo) {
        List<ProductPo> productPoList = productMapper.findProduct(productPo);
        List<Product> retProducts = new ArrayList<>(productPoList.size());

        for(ProductPo p : productPoList) {
            Product product = new Product(p);
            List<GoodsPo> goodsPoList = p.getGoodsPoList();
            List<Goods> goodsList = new ArrayList<>(goodsPoList.size());
            for(GoodsPo g : goodsPoList) {
                Goods goods = new Goods(g);
                goodsList.add(goods);
            }
            product.setGoodsList(goodsList);
            retProducts.add(product);
        }

        return new ReturnObject<>(retProducts);
    }

    public ReturnObject<List<Product>> findProductWithRedis(ProductPo productPo) {

        //long startTime = System.currentTimeMillis();
        List<Product> retProduct = null;
        String key = null;
        if(null != productPo.getId()) {
            key = "p_" + productPo.getId();
            Product product = (Product) redisUtil.get(key);
            if(null != product) {
                retProduct = new ArrayList<>(1);
                retProduct.add(product);
                //long endTime1 = System.currentTimeMillis();
                //System.out.println("With Redis, total time: " + (endTime1 - startTime));
                return new ReturnObject<>(retProduct);
            }
        }

        List<ProductPo> productPoList = productMapper.findProduct(productPo);
        retProduct = new ArrayList<>(productPoList.size());

        for(ProductPo p : productPoList) {
            Product product = new Product(p);
            List<GoodsPo> goodsPoList = p.getGoodsPoList();
            List<Goods> goodsList = new ArrayList<>(goodsPoList.size());
            for(GoodsPo g : goodsPoList) {
                Goods goods = new Goods(g);
                goodsList.add(goods);
            }
            product.setGoodsList(goodsList);
            retProduct.add(product);
        }

        if(null != productPo.getId()) {
            if(retProduct.size() != 0) {
                redisUtil.set(key, retProduct.get(0), productTimeout);
            } else {
                redisUtil.set(key, null, productTimeout);
            }
        }
        //long endTime = System.currentTimeMillis();
        //System.out.println("Without Redis, total time: " + (endTime - startTime));

        return new ReturnObject<>(retProduct);
    }
}
