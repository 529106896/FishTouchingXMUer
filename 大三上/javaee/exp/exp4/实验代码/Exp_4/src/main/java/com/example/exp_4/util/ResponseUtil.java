package com.example.exp_4.util;

import java.util.HashMap;
import java.util.Map;

/**
 * 用于组件返回结果
 * @author Jiazhe Yuan
 */
public class ResponseUtil {

    /**
     * 没有数据的成功返回
     * @return 只有错误码和提示信息的对象
     */
    public static Object ok() {
        Map<String ,Object> obj = new HashMap<String, Object>();
        obj.put("errno", ResponseCode.OK.getCode());
        obj.put("errmsg", ResponseCode.OK.getMessage());
        return obj;
    }

    /**
     * 有数据的成功返回
     * @param data 要返回的数据
     * @return 有错误码、提示信息、数据的对象
     */
    public static Object ok(Object data) {
        Map<String ,Object> obj = new HashMap<String, Object>();
        obj.put("errno", ResponseCode.OK.getCode());
        obj.put("errmsg", ResponseCode.OK.getMessage());
        obj.put("data", data);
        return obj;
    }

    /**
     * 使用预定错误返回码与错误提示信息的返回
     * @param code 要返回的错误码
     * @return 有错误码、对应错误信息的对象
     */
    public static Object fail(ResponseCode code) {
        Map<String ,Object> obj = new HashMap<String, Object>();
        obj.put("errno", ResponseCode.OK.getCode());
        obj.put("errmsg", ResponseCode.OK.getMessage());
        return obj;
    }

    /**
     * 使用错误码、自定义错误信息的返回
     * @param code 要返回的错误码
     * @param errmsg 要返回的错误信息
     * @return 有错误码、对应错误信息的对象
     */
    public static Object fail(ResponseCode code, String errmsg) {
        Map<String ,Object> obj = new HashMap<String, Object>();
        obj.put("errno", ResponseCode.OK.getCode());
        obj.put("errmsg", errmsg);
        return obj;
    }
}
