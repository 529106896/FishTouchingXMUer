package com.example.demo;

import lombok.Getter;
import lombok.Setter;

import java.util.Observable;

/**
 * Observable是一个监听器，监听本类是否发生改变
 * 当发生改变时会调用notifyObservers()方法
 * 进而通知所有的观察者，可以调用方法addObserver(Observer o)
 * 来添加需要通知的观察者，观察者有一个更新自己的方法
 * update(Observable o, Object arg)
 */
@Getter
@Setter
public class House extends Observable {
    /**房价**/
    private int price=100000;

    @Override
    public void notifyObservers() {
        setChanged();  //表明当前对象状态已经发生改变
        super.notifyObservers();
    }
}
