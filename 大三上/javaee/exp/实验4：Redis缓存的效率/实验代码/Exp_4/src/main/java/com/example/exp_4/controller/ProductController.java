package com.example.exp_4.controller;

import com.example.exp_4.model.GoodsRetVo;
import com.example.exp_4.model.ProductRetVo;
import com.example.exp_4.model.VoObject;
import com.example.exp_4.service.ProductService;
import com.example.exp_4.util.ResponseCode;
import com.example.exp_4.util.ResponseUtil;
import com.example.exp_4.util.ReturnObject;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import javax.servlet.http.HttpServletResponse;

@RestController
@RequestMapping(value = "/products", produces = "application/json;charset=UTF-8")
public class ProductController {

    @Autowired
    private ProductService productService;

    @Autowired
    private HttpServletResponse httpServletResponse;

    @GetMapping("/goods/{id}")
    public Object getGoodsById(@PathVariable("id") Integer id) {
        ReturnObject<VoObject> returnObject = productService.findGoodsById(id);
        ResponseCode code = returnObject.getCode();
        switch (code) {
            case RESOURCE_ID_NOT_EXIST:
                httpServletResponse.setStatus(HttpStatus.NOT_FOUND.value());
                return ResponseUtil.fail(returnObject.getCode(), returnObject.getErrmsg());
            case OK:
                GoodsRetVo goodsRetVo = (GoodsRetVo) returnObject.getData().createVo();
                //System.out.println(returnObject.getData());
                //System.out.println(returnObject.getData().createVo());
                return ResponseUtil.ok(goodsRetVo);
            default:
                return ResponseUtil.fail(code);
        }
    }

    @GetMapping("{id}")
    public Object getProductById(@PathVariable("id") Integer id) {
        ReturnObject<VoObject> returnObject = productService.findProductById(id);
        ResponseCode code = returnObject.getCode();
        switch (code) {
            case RESOURCE_ID_NOT_EXIST:
                httpServletResponse.setStatus(HttpStatus.NOT_FOUND.value());
                return ResponseUtil.fail(returnObject.getCode(), returnObject.getErrmsg());
            case OK:
                ProductRetVo productRetVo = (ProductRetVo) returnObject.getData().createVo();
                //System.out.println(returnObject.getData());
                //System.out.println(returnObject.getData().createVo());
                return ResponseUtil.ok(productRetVo);
            default:
                return ResponseUtil.fail(code);
        }
    }

    @GetMapping("/redis/{id}")
    public Object getProductByIdWithRedis(@PathVariable("id") Integer id) {
        ReturnObject<VoObject> returnObject = productService.findProductByIdWithRedis(id);
        ResponseCode code = returnObject.getCode();
        switch (code) {
            case RESOURCE_ID_NOT_EXIST:
                httpServletResponse.setStatus(HttpStatus.NOT_FOUND.value());
                return ResponseUtil.fail(returnObject.getCode(), returnObject.getErrmsg());
            case OK:
                ProductRetVo productRetVo = (ProductRetVo) returnObject.getData().createVo();
                //System.out.println(returnObject.getData());
                //System.out.println(returnObject.getData().createVo());
                return ResponseUtil.ok(productRetVo);
            default:
                return ResponseUtil.fail(code);
        }
    }
}
