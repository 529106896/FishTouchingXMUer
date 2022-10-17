package com.example.exp_1.controller;

import com.example.exp_1.model.Student;
import com.example.exp_1.model.StudentVo;
import com.example.exp_1.service.StudentService;
import com.example.exp_1.util.ResponseCode;
import com.example.exp_1.util.ResponseUtil;
import com.example.exp_1.util.ReturnObject;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.validation.BindingResult;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import javax.servlet.http.HttpServletResponse;

@RestController
@RequestMapping(value = "/bindingresult/student", produces = "application/json;charset=UTF-8")
public class BindingResultStudentController {
    private final Logger logger = LoggerFactory.getLogger(BindingResultStudentController.class);

    @Autowired
    private StudentService studentService;

    @Autowired
    private HttpServletResponse httpServletResponse;

    @PostMapping("")
    public Object createStudent(@Validated @RequestBody StudentVo studentVo, BindingResult bindingResult) {
        httpServletResponse.setContentType("application/json;charset=UTF-8");
        if (bindingResult.hasErrors()){
            logger.info("学生姓名不能为空");
            httpServletResponse.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            ReturnObject retObj = new ReturnObject();
            retObj.setErrmsg("学生姓名不能为空");
            retObj.setErrno(ResponseCode.OK);
            return retObj;
        }

        Student new_Student = studentService.createStudent(studentVo);
        httpServletResponse.setStatus(HttpServletResponse.SC_CREATED);
        return ResponseUtil.ok(new_Student);
    }
}
