package com.example.exp_1.controller;

import com.example.exp_1.Exp1Application;
import com.example.exp_1.model.StudentVo;
import com.example.exp_1.util.JacksonUtil;
import com.example.exp_1.util.StudentFactory;
import org.junit.jupiter.api.Test;
import org.skyscreamer.jsonassert.JSONAssert;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.web.servlet.AutoConfigureMockMvc;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.http.codec.cbor.Jackson2CborDecoder;
import org.springframework.test.web.servlet.MockMvc;

import static org.springframework.test.web.servlet.request.MockMvcRequestBuilders.post;
import static org.springframework.test.web.servlet.result.MockMvcResultMatchers.content;
import static org.springframework.test.web.servlet.result.MockMvcResultMatchers.status;


@SpringBootTest(classes = Exp1Application.class)
@AutoConfigureMockMvc
public class BindingResultStudentControllerTest {
    @Autowired
    private MockMvc mvc;

    @Test
    public void createStudentTest() throws Exception {
        StudentVo s = StudentFactory.getInstance().createStudentVo();

        String studentJson = JacksonUtil.toJson(s);

        String responseString = this.mvc.perform(post("/bindingresult/student").contentType("application/json;charset=UTF-8").content(studentJson))
                .andExpect(status().isCreated())
                .andExpect(content().contentType("application/json;charset=UTF-8"))
                .andReturn().getResponse().getContentAsString();

        String expectedResponse = "{\"errno\":0,\"data\":{\"name\":\"王小明\",\"id\":\"11920192203642\",\"age\":18,\"major\":\"软件工程\",\"gender\":\"男\"},\"errmsg\":\"成功\"}";

        JSONAssert.assertEquals(responseString, expectedResponse, true);
    }

    @Test
    public void createStudentTest1() throws Exception {

        StudentVo s = StudentFactory.getInstance().createStudentVoWithoutName();

        String studentJson = JacksonUtil.toJson(s);

        String responseString = this.mvc.perform(post("/bindingresult/student").contentType("application/json;charset=UTF-8").content(studentJson))
                .andExpect(status().isBadRequest())
                .andExpect(content().contentType("application/json;charset=UTF-8"))
                .andReturn().getResponse().getContentAsString();

        String expectedResponse = "{\"errno\":0,\"errmsg\":\"学生姓名不能为空\",\"data\":null}";

        JSONAssert.assertEquals(expectedResponse, responseString, true);
    }

}
