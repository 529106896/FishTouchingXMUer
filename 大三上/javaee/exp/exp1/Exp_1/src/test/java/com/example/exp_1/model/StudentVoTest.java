package com.example.exp_1.model;

import com.example.exp_1.util.StudentFactory;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

public class StudentVoTest {

    @Test
    public void createStudentTest(){
        StudentVo studentVo = StudentFactory.getInstance().createStudentVo();
        Student student = studentVo.createStudent();
        assertEquals("王小明", student.getName());
        assertEquals("11920192203642", student.getId());
        assertEquals("软件工程", student.getMajor());
        assertEquals(18, student.getAge());
        assertEquals("男", student.getGender());
    }

}
