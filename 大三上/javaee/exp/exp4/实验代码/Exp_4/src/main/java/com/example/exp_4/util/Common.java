package com.example.exp_4.util;

import com.example.exp_4.model.VoObject;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 * 通用工具类
 * @author Jiazhe Yuan
 */
public class Common {

    private static Logger logger = LoggerFactory.getLogger(Common.class);

    /**
     * 处理返回对象
     * @param returnObject 返回的对象
     * @return
     */
    public static Object getRetObject(ReturnObject<VoObject> returnObject) {
        ResponseCode code = returnObject.getCode();
        if (code == ResponseCode.OK) {
            VoObject data = returnObject.getData();
            if (data != null) {
                Object voObj = data.createVo();
                logger.info("getRetObject: voObj =" + voObj);
                return ResponseUtil.ok(voObj);
            } else {
                return ResponseUtil.ok();
            }
        }
        return ResponseUtil.fail(returnObject.getCode(), returnObject.getErrmsg());
    }
}
