package com.example.exp_4;

import org.junit.jupiter.api.Test;
import org.skyscreamer.jsonassert.JSONAssert;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.web.servlet.AutoConfigureMockMvc;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.web.servlet.MockMvc;
import org.springframework.transaction.annotation.Transactional;

import static org.springframework.test.web.servlet.request.MockMvcRequestBuilders.*;
import static org.springframework.test.web.servlet.result.MockMvcResultMatchers.*;

@SpringBootTest(classes = Exp4Application.class)
@AutoConfigureMockMvc
@Transactional
public class ProductControllerIntegrationTest {

    @Autowired
    private MockMvc mvc;

    @Test
    public void getGoodsById() throws Exception {

        String responseString = this.mvc.perform(get("/products/goods/1"))
                .andExpect(status().isOk())
                .andExpect(content().contentType("application/json;charset=UTF-8"))
                .andReturn().getResponse().getContentAsString();

        String expectResponse = "{\"errno\":0,\"errmsg\":\"成功\",\"data\":{\"id\":1,\"name\":\"mobilephone\",\"goodsSn\":\"string\",\"imageUrl\":\"string\",\"state\":0,\"gmtCreate\":\"2021-10-26 20:47:21\",\"gmtModified\":\"string\",\"disable\":false}}";

        JSONAssert.assertEquals(expectResponse, responseString, true);
    }

    @Test
    public void getProductByIdWithRedis() throws Exception {
        String responseString = this.mvc.perform(get("/products/redis/1"))
                .andExpect(status().isOk())
                .andExpect(content().contentType("application/json;charset=UTF-8"))
                .andReturn().getResponse().getContentAsString();

        String expectResponse = "{\"errno\":0,\"errmsg\":\"成功\",\"data\":{\"id\":1,\"name\":\"xiaomi\",\"skuSn\":\"string\",\"detail\":\"string\",\"imageUrl\":\"string\",\"originalPrice\":0,\"price\":0,\"inventory\":0,\"state\":0,\"weight\":0,\"gmtCreate\":\"2021-10-27 23:06:11\",\"gmtModified\":\"string\",\"goods\":{\"id\":1,\"name\":\"mobilephone\",\"goodsSn\":\"string\",\"imageUrl\":\"string\",\"state\":0,\"gmtCreate\":\"2021-10-26 20:47:21\",\"gmtModified\":\"string\",\"disable\":false},\"disable\":false,\"shareable\":false}}";

        JSONAssert.assertEquals(expectResponse, responseString, true);
    }

    @Test
    public void getProductById() throws Exception {
        String responseString = this.mvc.perform(get("/products/1"))
                .andExpect(status().isOk())
                .andExpect(content().contentType("application/json;charset=UTF-8"))
                .andReturn().getResponse().getContentAsString();

        String expectResponse = "{\"errno\":0,\"errmsg\":\"成功\",\"data\":{\"id\":1,\"name\":\"xiaomi\",\"skuSn\":\"string\",\"detail\":\"string\",\"imageUrl\":\"string\",\"originalPrice\":0,\"price\":0,\"inventory\":0,\"state\":0,\"weight\":0,\"gmtCreate\":\"2021-10-27 23:06:11\",\"gmtModified\":\"string\",\"goods\":{\"id\":1,\"name\":\"mobilephone\",\"goodsSn\":\"string\",\"imageUrl\":\"string\",\"state\":0,\"gmtCreate\":\"2021-10-26 20:47:21\",\"gmtModified\":\"string\",\"disable\":false},\"disable\":false,\"shareable\":false}}";

        JSONAssert.assertEquals(expectResponse, responseString, true);

        String responseString1 = this.mvc.perform(get("/products/3"))
                .andExpect(status().isOk())
                .andExpect(content().contentType("application/json;charset=UTF-8"))
                .andReturn().getResponse().getContentAsString();

        String expectResponse1 = "{\"errno\":0,\"errmsg\":\"成功\",\"data\":{\"id\":3,\"name\":\"iphone\",\"skuSn\":\"string\",\"detail\":\"string\",\"imageUrl\":\"string\",\"originalPrice\":0,\"price\":0,\"inventory\":0,\"state\":0,\"weight\":0,\"gmtCreate\":\"2021-10-27 23:28:28\",\"gmtModified\":\"string\",\"goods\":{\"id\":1,\"name\":\"mobilephone\",\"goodsSn\":\"string\",\"imageUrl\":\"string\",\"state\":0,\"gmtCreate\":\"2021-10-26 20:47:21\",\"gmtModified\":\"string\",\"disable\":false},\"disable\":false,\"shareable\":false}}";

        JSONAssert.assertEquals(expectResponse1, responseString1, true);
    }
}
