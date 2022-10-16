package com.example.exp_1.model;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

@Data
public class Student {
    //@ApiModelProperty(value = "学生名称")
    private String name;

    //@ApiModelProperty(value = "学生学号")
    private String id;

    //@ApiModelProperty(value = "学生年龄")
    private Integer age;

    //@ApiModelProperty(value = "学生专业")
    private String major;

    //@ApiModelProperty(value = "学生性别")
    private String gender;
}
