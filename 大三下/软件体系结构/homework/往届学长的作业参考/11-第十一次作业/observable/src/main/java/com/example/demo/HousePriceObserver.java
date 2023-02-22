package com.example.demo;
import java.util.Observable;
import java.util.Observer;

public class HousePriceObserver implements Observer {
    private String name;

    HousePriceObserver(String name) {
        this.name = name;
    }
//    @Override
//    public void update(Observable o, Object arg) {
//        House house = null;
//        if (o instanceof House) {
//            house = (House)o;
//        }
//        assert house != null;
//        System.out.println(this.name + "观察到目前的房价更改为："+house.getPrice());
//    }
    @Override
    public void update(Observable o, Object arg) {
        this.updateMyself(o);
    }

    /**如果更新自己行为的方法名在之前已经定义好，那么需要在update方法中调用即可，相当于代理方法*/
    private void updateMyself(Observable o){
        House house = null;
        if (o instanceof House) {
            house = (House)o;
        }
        assert house != null;
        System.out.println(this.name + "观察到目前的房价更改为："+house.getPrice());
    }
}
