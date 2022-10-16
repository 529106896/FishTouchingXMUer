package com.example.exp_2;

import com.example.exp_2.model.OrdersVo;
import com.example.exp_2.util.JacksonUtil;
import com.example.exp_2.util.OrdersFactoty;
import org.junit.jupiter.api.Test;
import org.skyscreamer.jsonassert.JSONAssert;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.web.servlet.AutoConfigureMockMvc;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.boot.test.context.TestConfiguration;
import org.springframework.test.web.servlet.MockMvc;
import org.springframework.transaction.annotation.Transactional;

import static org.springframework.test.web.servlet.request.MockMvcRequestBuilders.*;
import static org.springframework.test.web.servlet.result.MockMvcResultMatchers.content;
import static org.springframework.test.web.servlet.result.MockMvcResultMatchers.status;

@SpringBootTest(classes = Exp2Application.class)
@AutoConfigureMockMvc
@Transactional
public class OrdersControllerIntegrationTest {

    @Autowired
    private MockMvc mvc;

    @Test
    public void getOrdersById() throws Exception {
        String responseString = this.mvc.perform(get("/orders/100"))
                .andExpect(status().isOk())
                .andExpect(content().contentType("application/json;charset=UTF-8"))
                .andReturn().getResponse().getContentAsString();

        String expectedResponse = "{\"errno\":0,\"errmsg\":\"成功\",\"data\":{\"id\":100,\"orderSn\":\"2016102545959\",\"pid\":0,\"orderType\":0,\"state\":3,\"subState\":0,\"gmtCreate\":\"2020-12-10 19:29:33\",\"gmtModified\":\"2020-12-10 19:29:33\",\"confirmTime\":\"string\",\"originPrice\":0,\"discountPrice\":0,\"freightPrice\":0,\"rebateNum\":0,\"message\":\"string\",\"regionId\":0,\"address\":\"string\",\"mobile\":\"13959288888\",\"consignee\":\"刘华\",\"couponId\":0,\"grouponId\":0,\"presaleId\":0,\"shipmentSn\":\"string\",\"orderItems\":[{\"skuId\":341,\"orderId\":100,\"name\":\"string\",\"quantity\":1,\"price\":0,\"discount\":0,\"couponActId\":0,\"beSharedId\":0},{\"skuId\":342,\"orderId\":100,\"name\":\"string\",\"quantity\":1,\"price\":0,\"discount\":0,\"couponActId\":0,\"beSharedId\":0}]}}";

        JSONAssert.assertEquals(expectedResponse, responseString, true);
    }

    @Test
    public void createOrderTest() throws Exception {
        OrdersVo o = OrdersFactoty.getInstance().createOrdersVo();

        String orderJson = JacksonUtil.toJson(o);

        String responseString = this.mvc.perform(post("/orders").contentType("application/json;charset=UTF-8").content(orderJson))
                .andExpect(status().isCreated())
                .andExpect(content().contentType("application/json;charset=UTF-8"))
                .andReturn().getResponse().getContentAsString();

        String expectedResponse = "{\"errno\":0,\"errmsg\":\"成功\"}";

        JSONAssert.assertEquals(expectedResponse, responseString, false);

        responseString = this.mvc.perform(get("/orders/search?consignee=" + o.getConsignee()))
                .andExpect(status().isOk())
                .andExpect(content().contentType("application/json;charset=UTF-8"))
                .andReturn().getResponse().getContentAsString();

        expectedResponse = "{\"errno\":0,\"errmsg\":\"成功\"}";

        JSONAssert.assertEquals(expectedResponse, responseString, false);
    }

}
