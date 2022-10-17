package com.example.exp_4.util;

import lombok.Getter;

/**
 * 返回对象
 * @author Jiazhe Yuan
 */
@Getter
public class ReturnObject<T> {

    // 错误号，默认为0
    ResponseCode code = ResponseCode.OK;

    // 自定义的错误码
    String errmsg = null;

    // 要返回的值
    private T data = null;

    public ReturnObject() {
    }

    public ReturnObject(T data) {
        this();
        this.data = data;
    }

    public ReturnObject(ResponseCode code) {
        this.code = code;
    }

    public ReturnObject(ResponseCode code, String errmsg) {
        this(code);
        this.errmsg = errmsg;
    }

    public String getErrmsg() {
        if(null != this.errmsg) {
            return this.errmsg;
        }else {
            return this.code.getMessage();
        }
    }
}
