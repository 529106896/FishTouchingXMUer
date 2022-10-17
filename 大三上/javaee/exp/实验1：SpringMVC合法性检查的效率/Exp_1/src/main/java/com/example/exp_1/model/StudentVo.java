package com.example.exp_1.model;

import lombok.Data;

import javax.validation.constraints.NotBlank;

@Data
public class StudentVo {
    //@ApiModelProperty(value = "学生名称")
    @NotBlank(message = "学生姓名不能为空")
    private String name;

    //@ApiModelProperty(value = "学生学号")
    private String id;

    //@ApiModelProperty(value = "学生年龄")
    private Integer age;

    //@ApiModelProperty(value = "学生专业")
    private String major;

    //@ApiModelProperty(value = "学生性别")
    private String gender;

    public Student createStudent(){
        Student student = new Student();
        student.setName(this.name);
        student.setId(this.id);
        student.setAge(this.age);
        student.setMajor(this.major);
        student.setGender(this.gender);
        return student;
    }
}
