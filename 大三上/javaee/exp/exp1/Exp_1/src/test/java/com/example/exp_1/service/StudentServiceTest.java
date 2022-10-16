package com.example.exp_1.service;

import com.example.exp_1.Exp1Application;
import com.example.exp_1.model.Student;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;

import static org.junit.jupiter.api.Assertions.*;

@SpringBootTest(classes = Exp1Application.class)
public class StudentServiceTest {

    @Autowired
    private StudentService studentService;

    @Test
    void searchByName()
    {
        Student student = studentService.searchByName("李云龙");
        assertEquals("11920192203642", student.getId());
        assertEquals("男", student.getGender());
        assertEquals("软件工程", student.getMajor());
        assertEquals(20, student.getAge());
    }

}
