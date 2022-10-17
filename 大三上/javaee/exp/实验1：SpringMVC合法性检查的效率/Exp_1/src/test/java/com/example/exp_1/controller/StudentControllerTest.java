package com.example.exp_1.controller;

import com.example.exp_1.Exp1Application;
import com.example.exp_1.model.Student;
import com.example.exp_1.model.StudentVo;
import com.example.exp_1.service.StudentService;
import com.example.exp_1.util.JacksonUtil;
import com.example.exp_1.util.StudentFactory;
import org.junit.jupiter.api.Test;
import org.skyscreamer.jsonassert.JSONAssert;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.web.servlet.AutoConfigureMockMvc;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.boot.test.mock.mockito.MockBean;
import org.springframework.test.web.servlet.MockMvc;

import static org.mockito.BDDMockito.*;
import static org.springframework.test.web.servlet.request.MockMvcRequestBuilders.*;
import static org.springframework.test.web.servlet.request.MockMvcRequestBuilders.delete;
import static org.springframework.test.web.servlet.result.MockMvcResultMatchers.content;
import static org.springframework.test.web.servlet.result.MockMvcResultMatchers.status;

@SpringBootTest(classes = Exp1Application.class)
@AutoConfigureMockMvc
public class StudentControllerTest {

    @Autowired
    private MockMvc mvc;

    @MockBean
    private StudentService studentService;

    @Test
    public void createStudentTest() throws Exception {

        StudentVo s = StudentFactory.getInstance().createStudentVo();
        Student student = s.createStudent();
        student.setMajor("软件工程");
        student.setName("袁佳哲");
        student.setAge(20);
        student.setGender("男");
        student.setId("11920192203642");

        given(studentService.createStudent(any())).willReturn(student);

        String studentJson = JacksonUtil.toJson(s);

        String responseString = this.mvc.perform(post("/student").contentType("application/json;charset=UTF-8").content(studentJson))
                .andExpect(status().isCreated())
                .andExpect(content().contentType("application/json;charset=UTF-8"))
                .andReturn().getResponse().getContentAsString();

        String expectedResponse = "{\"errno\":0,\"data\":{\"name\":\"袁佳哲\",\"id\":\"11920192203642\",\"age\":20,\"major\":\"软件工程\",\"gender\":\"男\"},\"errmsg\":\"成功\"}";

        JSONAssert.assertEquals(expectedResponse, responseString, true);
    }

    @Test
    public void createStudentTest1() throws Exception {

        StudentVo s = StudentFactory.getInstance().createStudentVoWithoutName();
        Student student = s.createStudent();

        given(studentService.createStudent(any())).willReturn(student);

        String studentJson = JacksonUtil.toJson(s);

        String responseString = this.mvc.perform(post("/student").contentType("application/json;charset=UTF-8").content(studentJson))
                .andExpect(status().isBadRequest())
                .andExpect(content().contentType("application/json;charset=UTF-8"))
                .andReturn().getResponse().getContentAsString();

        String expectedResponse = "{\"errno\":0,\"errmsg\":\"学生姓名不能为空\",\"data\":null}";

        JSONAssert.assertEquals(expectedResponse, responseString, true);
    }

    @Test
    public void searchByNameTest() throws Exception {
        given(studentService.searchByName(eq("袁佳哲"))).willReturn(StudentFactory.getInstance().createStudent("袁佳哲"));

        String responseString = this.mvc.perform(get("/student/search?name=袁佳哲"))
                .andExpect(status().isOk())
                .andExpect(content().contentType("application/json;charset=UTF-8"))
                .andReturn().getResponse().getContentAsString();

        String expectedResponse = "{\"errno\":0,\"data\":{\"name\":\"袁佳哲\",\"id\":\"11920192203642\",\"age\":20,\"major\":\"软件工程\",\"gender\":\"男\"},\"errmsg\":\"成功\"}";

        JSONAssert.assertEquals(expectedResponse, responseString, true);
    }
}
