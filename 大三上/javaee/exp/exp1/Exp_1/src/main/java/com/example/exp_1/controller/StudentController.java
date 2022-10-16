package com.example.exp_1.controller;

import com.example.exp_1.model.Student;
import com.example.exp_1.model.StudentVo;
import com.example.exp_1.service.StudentService;
import com.example.exp_1.util.ResponseUtil;
import org.apache.juli.logging.Log;
import org.apache.juli.logging.LogFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.*;

/**
 * 学生控制器
 * 这个控制器是为了JavaEE实验一所做
 * 我们用这个Controller去抛出Exception，用RestControllerAdvice去接收
 */

@RestController
@RequestMapping(value = "/student", produces = "application/json;charset=UTF-8")
public class StudentController {

    private final Log logger = LogFactory.getLog(StudentController.class);

    @Autowired
    private StudentService studentService;

    @GetMapping("search")
    public Object searchStudentByName(@RequestParam String name){
        Student student = studentService.searchByName(name);
        return ResponseUtil.ok(student);
    }

    @PostMapping("")
    @ResponseStatus(HttpStatus.CREATED)
    public Object createStudent(@Validated @RequestBody StudentVo studentVo){
        Student new_student = studentService.createStudent(studentVo);
        return ResponseUtil.ok(new_student);
    }

}
