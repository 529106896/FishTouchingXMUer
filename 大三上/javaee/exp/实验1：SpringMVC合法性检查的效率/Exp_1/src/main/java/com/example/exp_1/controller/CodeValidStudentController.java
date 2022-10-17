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
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.*;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * 手写校验输入合法性检查的学生控制器
 * @author Jiazhe Yuan
 */

@RestController
@RequestMapping(value = "/codevalid/student", produces = "application/json;charset=UTF-8")
public class CodeValidStudentController {

    private final Logger logger = LoggerFactory.getLogger(CodeValidStudentController.class);

    @Autowired
    private StudentService studentService;

    @Autowired
    private HttpServletResponse httpServletResponse;

    @PostMapping("")
    public Object createStudent(@RequestBody StudentVo studentVo){
        httpServletResponse.setContentType("application/json;charset=UTF-8");
        if(null == studentVo.getName() || studentVo.getName().equals("") || studentVo.getName().trim().length() == 0){
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
