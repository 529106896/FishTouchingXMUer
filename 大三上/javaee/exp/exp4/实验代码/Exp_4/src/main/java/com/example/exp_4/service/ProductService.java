package com.example.exp_4.service;

import com.example.exp_4.dao.ProductDao;
import com.example.exp_4.model.*;
import com.example.exp_4.util.ResponseCode;
import com.example.exp_4.util.ReturnObject;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class ProductService {

    //private Logger logger = LoggerFactory.getLogger()

    @Autowired
    private ProductDao productDao;

    public ReturnObject<VoObject> findGoodsById(Integer id) {

        GoodsPo queryObj = new GoodsPo();
        queryObj.setId(id);

        ReturnObject<VoObject> retGoods = null;
        ReturnObject<List<Goods>> returnObject = productDao.findGoods(queryObj);

        if(returnObject.getCode().equals(ResponseCode.OK)) {
            if(returnObject.getData().size() == 1) {
                retGoods = new ReturnObject<>(returnObject.getData().get(0));
                //System.out.println(retGoods.getData());
                //System.out.println(returnObject.getData().get(0));
            } else {
                retGoods = new ReturnObject<>(ResponseCode.RESOURCE_ID_NOT_EXIST);
            }
        } else {
            retGoods = new ReturnObject<>(returnObject.getCode(), returnObject.getErrmsg());
        }

        return retGoods;
    }

    public ReturnObject<VoObject> findProductById(Integer id) {
        ProductPo queryObj = new ProductPo();
        queryObj.setId(id);

        ReturnObject<VoObject> retProduct = null;
        ReturnObject<List<Product>> returnObject = productDao.findProduct(queryObj);

        if(returnObject.getCode().equals(ResponseCode.OK)) {
            if(returnObject.getData().size() == 1) {
                retProduct = new ReturnObject<>(returnObject.getData().get(0));
            } else {
                retProduct = new ReturnObject<>(ResponseCode.RESOURCE_ID_NOT_EXIST);
            }
        } else {
            retProduct = new ReturnObject<>(returnObject.getCode(), returnObject.getErrmsg());
        }

        return retProduct;
    }

    public ReturnObject<VoObject> findProductByIdWithRedis(Integer id) {
        ProductPo queryObj = new ProductPo();
        queryObj.setId(id);

        ReturnObject<VoObject> retProduct = null;
        ReturnObject<List<Product>> returnObject = productDao.findProductWithRedis(queryObj);

        if(returnObject.getCode().equals(ResponseCode.OK)) {
            if(returnObject.getData().size() == 1) {
                retProduct = new ReturnObject<>(returnObject.getData().get(0));
            } else {
                retProduct = new ReturnObject<>(ResponseCode.RESOURCE_ID_NOT_EXIST);
            }
        } else {
            retProduct = new ReturnObject<>(returnObject.getCode(), returnObject.getErrmsg());
        }

        return retProduct;
    }
}
