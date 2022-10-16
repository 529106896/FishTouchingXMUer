package com.example.exp_4.util;

/**
 * 返回的错误码
 * @author Jiazhe Yuan
 */
public enum ResponseCode {

    OK(0, "成功"),
    FIELD_NOT_VALID(503, "字段不合法"),
    RESOURCE_ID_NOT_EXIST(504, "操作的资源id不存在"),
    RESOURCE_ID_OUT_SCOPE(505, "操作的资源id不是自己的对象");


    private final int code;
    private final String message;

    ResponseCode(int code, String message) {
        this.code = code;
        this.message = message;
    }

    public int getCode() {
        return code;
    }

    public String getMessage() {
        return message;
    }
}
