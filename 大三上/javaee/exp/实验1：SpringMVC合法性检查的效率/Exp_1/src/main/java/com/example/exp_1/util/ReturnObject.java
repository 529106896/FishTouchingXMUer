package com.example.exp_1.util;

import lombok.Data;

@Data
public class ReturnObject<T> {
    /**
     * 错误号
     */
    Integer errno = 0;

    /**
     * 错误消息
     */
    String errmsg = "";

    /**
     * 返回值
     */
    private T data = null;
}
