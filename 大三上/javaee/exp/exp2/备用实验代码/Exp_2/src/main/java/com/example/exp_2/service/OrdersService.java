package com.example.exp_2.service;

import com.example.exp_2.dao.OrdersDao;
import com.example.exp_2.model.Orders;
import com.example.exp_2.model.OrdersPo;
import com.example.exp_2.model.OrdersVo;
import com.example.exp_2.model.VoObject;
import com.example.exp_2.util.ResponseCode;
import com.example.exp_2.util.ReturnObject;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.List;

@Service
public class OrdersService {
    private Logger logger = LoggerFactory.getLogger(OrdersService.class);

    @Autowired
    private OrdersDao ordersDao;

    /**
     * 获取订单信息
     * @param id 订单id
     * @return 订单对象
     */
    public ReturnObject<VoObject> findById(Integer id) {
        OrdersPo queryObj = new OrdersPo();
        queryObj.setId(id);
        ReturnObject<VoObject> retOrders = null;
        ReturnObject<List<Orders>> returnObject = ordersDao.findOrders(queryObj);

        if(returnObject.getCode().equals(ResponseCode.OK)) {
            if (returnObject.getData().size() == 1) {
                retOrders = new ReturnObject<>(returnObject.getData().get(0));
            }else {
                retOrders = new ReturnObject<>(ResponseCode.RESOURCE_ID_NOTEXIST);
            }
        }else {
            retOrders = new ReturnObject<>(returnObject.getCode(), returnObject.getErrmsg());
        }
        return retOrders;
    }

    @Transactional
    public ReturnObject<VoObject> createOrders(OrdersVo ordersVo) {
        logger.info("createOrders: ordersVo = " + ordersVo);
        Orders orders = ordersVo.createOrders();
        logger.info("createOrders: orders = " + orders);
        ReturnObject<Orders> retObj = ordersDao.createOrders(orders);
        ReturnObject<VoObject> retOrders = null;
        if(retObj.getCode().equals(ResponseCode.OK)) {
            retOrders = new ReturnObject<>(retObj.getData());
        }else {
            retOrders = new ReturnObject<>(retObj.getCode(), retObj.getErrmsg());
        }
        logger.info("createOrders: retOrders = " + retOrders.getData());
        return retOrders;
    }

    public ReturnObject<VoObject> searchByConsignee(String Consignee) {
        OrdersPo queryObj = new OrdersPo();
        queryObj.setConsignee(Consignee);
        ReturnObject<VoObject> retOrders = null;
        ReturnObject<List<Orders>> returnObject = ordersDao.findOrders(queryObj);
        //logger.info("searchByConsignee: returnObject = " + returnObject.getCode());
        if (returnObject.getCode().equals(ResponseCode.OK)) {
            if (returnObject.getData().size() == 1) {
                retOrders = new ReturnObject<>(returnObject.getData().get(0));
            }else{
                retOrders = new ReturnObject<>();
            }
        }else{
            retOrders = new ReturnObject<>(returnObject.getCode(), returnObject.getErrmsg());
        }
        logger.info("searchByConsignee: retOrders = " + retOrders);
        return retOrders;
    }
}
