package com.example.exp_5.controller;

import com.example.exp_5.model.OrdersRetVo;
import com.example.exp_5.model.OrdersVo;
import com.example.exp_5.model.VoObject;
import com.example.exp_5.service.OrdersService;
import com.example.exp_5.util.ResponseCode;
import com.example.exp_5.util.ResponseUtil;
import com.example.exp_5.util.ReturnObject;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.validation.BindingResult;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.*;

import javax.servlet.http.HttpServletResponse;

import static com.example.exp_5.util.Common.*;

@RestController
@RequestMapping(value = "/orders", produces = "application/json;charset=UTF-8")
public class OrdersController {

    private final Logger logger = LoggerFactory.getLogger(OrdersController.class);

    @Autowired
    private OrdersService ordersService;

    @Autowired
    private HttpServletResponse httpServletResponse;

    @GetMapping("{id}")
    public Object getOrdersById(@PathVariable("id") Integer id) {
        ReturnObject<VoObject> returnObject = ordersService.findById(id);
        ResponseCode code = returnObject.getCode();
        switch (code){
            case RESOURCE_ID_NOTEXIST:
                httpServletResponse.setStatus(HttpStatus.NOT_FOUND.value());
                return ResponseUtil.fail(returnObject.getCode(), returnObject.getErrmsg());
            case OK:
                OrdersRetVo ordersRetVo = (OrdersRetVo) returnObject.getData().createVo();
                return ResponseUtil.ok(ordersRetVo);
            default:
                return ResponseUtil.fail(code);
        }
    }

    @PostMapping("")
    public Object createOrders(@Validated @RequestBody OrdersVo ordersVo, BindingResult bindingResult) {

        Object returnObject = processFieldErrors(bindingResult, httpServletResponse);
        if (null != returnObject) {
            return returnObject;
        }
        ReturnObject<VoObject> returnObject1 = ordersService.createOrders(ordersVo);
        httpServletResponse.setStatus(HttpStatus.CREATED.value());
        return getRetObject(returnObject1);
    }

    @PostMapping("rocketmq")
    public Object createOrdersWithRocketMQ(@Validated @RequestBody OrdersVo ordersVo, BindingResult bindingResult) {

        Object returnObject = processFieldErrors(bindingResult, httpServletResponse);
        if (null != returnObject) {
            return returnObject;
        }
        ReturnObject<VoObject> returnObject1=ordersService.sendCreateOrderMessage(ordersVo);
        //ReturnObject<VoObject> returnObject1 = ordersService.createOrders(ordersVo);
        httpServletResponse.setStatus(HttpStatus.CREATED.value());
        return getRetObject(returnObject1);
    }

    @GetMapping("search")
    public Object searchByConsignee(@RequestParam String consignee) {
        ReturnObject<VoObject> returnObject = ordersService.searchByConsignee(consignee);
        return getRetObject(returnObject);
    }

}
