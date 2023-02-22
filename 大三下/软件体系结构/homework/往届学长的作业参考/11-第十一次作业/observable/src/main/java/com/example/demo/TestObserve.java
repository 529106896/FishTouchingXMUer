package com.example.demo;

public class TestObserve {
    public static void main(String[] args) {
        //通知者
        House house = new House();
        //观察者
        HousePriceObserver work1 = new HousePriceObserver("观察者A");
        HousePriceObserver work2 = new HousePriceObserver("观察者B");
        HousePriceObserver work3 = new HousePriceObserver("观察者C");
        //添加需要通知的观察者
        house.addObserver(work1);
        house.addObserver(work2);
        house.addObserver(work3);
        System.out.println("房价为："+house.getPrice());
        //通知者的状态发生改变
        house.setPrice(200000);
        //通知观察者
        house.notifyObservers();
        System.out.println("房价为："+house.getPrice());
    }
}
