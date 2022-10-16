package com.example.exp_1.service;

import com.example.exp_1.model.Student;
import com.example.exp_1.model.StudentVo;
import org.springframework.stereotype.Service;

@Service
public class StudentService {

    public Student searchByName(String name){
        Student student = createStudent(name);
        return student;
    }

    private Student createStudent(String name){
        Student s = new Student();
        s.setName(name);
        s.setId("11920192203642");
        s.setGender("男");
        s.setAge(20);
        s.setMajor("软件工程");
        return s;
    }

    /**
     * 新增学生
     * @param studentVo 新学生信息
     * @return 新学生
     */
    public Student createStudent(StudentVo studentVo)
    {
        Student student = studentVo.createStudent();
        student.setMajor("软件工程");
        return student;
    }
}
