package com.example.exp_1.controller;

import com.example.exp_1.util.ResponseCode;
import com.example.exp_1.util.ReturnObject;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.validation.FieldError;
import org.springframework.web.bind.MethodArgumentNotValidException;
import org.springframework.web.bind.annotation.ExceptionHandler;
import org.springframework.web.bind.annotation.ResponseStatus;
import org.springframework.web.bind.annotation.RestControllerAdvice;

import javax.servlet.http.HttpServletResponse;

@RestControllerAdvice(basePackageClasses = StudentController.class)
public class ControllerExceptionHandler {

    private final Logger logger = LoggerFactory.getLogger(ControllerExceptionHandler.class);

    @Autowired
    private HttpServletResponse httpServletResponse;

    @ExceptionHandler(value = MethodArgumentNotValidException.class)
    @ResponseStatus(HttpStatus.BAD_REQUEST)
    public Object methodArgumentNotValid(MethodArgumentNotValidException exception){

        ReturnObject retObj = new ReturnObject();
        StringBuffer msg = new StringBuffer();

        for (FieldError error : exception.getBindingResult().getFieldErrors()) {
            msg.append(error.getDefaultMessage());
            msg.append(";");
        }
        logger.info("methodArgumentNotValid: msg = "+ msg.toString());
        retObj.setErrmsg("学生姓名不能为空");
        retObj.setErrno(ResponseCode.OK);
        httpServletResponse.setContentType("application/json;charset=UTF-8");
        return retObj;
    }
}
