package com.example.exp_1.util;

import com.example.exp_1.model.Student;
import com.example.exp_1.model.StudentVo;

public class StudentFactory {
    private static StudentFactory instance = null;

    public static StudentFactory getInstance() {
        if(instance == null){
            synchronized (StudentFactory.class){
                if(instance == null){
                    instance = new StudentFactory();
                }
            }
        }
        return instance;
    }

    public StudentVo createStudentVo(){
        StudentVo s = new StudentVo();
        s.setName("王小明");
        s.setId("11920192203642");
        s.setAge(18);
        s.setMajor("软件工程");
        s.setGender("男");
        return s;
    }

    public Student createStudent(String name){
        Student student = new Student();
        student.setName(name);
        student.setId("11920192203642");
        student.setAge(20);
        student.setMajor("软件工程");
        student.setGender("男");
        return student;
    }

    public StudentVo createStudentVoWithoutName(){
        StudentVo student = new StudentVo();
        student.setName("");
        student.setId("11920192203642");
        student.setAge(20);
        student.setMajor("软件工程");
        student.setGender("男");
        return student;
    }
}
