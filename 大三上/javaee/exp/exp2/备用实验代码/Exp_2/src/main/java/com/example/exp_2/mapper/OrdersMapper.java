package com.example.exp_2.mapper;

import com.example.exp_2.model.OrderItemPo;
import com.example.exp_2.model.OrdersPo;
import org.apache.ibatis.annotations.Mapper;

import java.util.List;

@Mapper
public interface OrdersMapper {

    /**
     * 创建OrdersPo对象
     * @param ordersPo ordersPo对象
     * @return 1 成功
     */
    int createOrders(OrdersPo ordersPo);

    /**
     * 创建OrdersItemPo对象
     * @param orderItemPo orderItemPo对象
     * @return 1 成功
     */
    int createOrderItem(OrderItemPo orderItemPo);

    /**
     * 用OrdersPo对象找
     * @param ordersPo 条件对象，所有条件为AND，仅有索引的值可以作为条件
     * @return OrdersPo对象列表
     */
    List<OrdersPo> findOrders(OrdersPo ordersPo);


    // 以下为测试用Mapper接口，打包时记得删掉
    List<OrdersPo> findOrdersTest(OrdersPo ordersPo);
    List<OrderItemPo> findOrderItemsTest(OrderItemPo orderItemPo);
    List<OrdersPo> findOrdersWithItemTest(OrdersPo ordersPo);
    //List<Orders>
}
