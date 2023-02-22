package com.example.demo;

import java.util.List;

/**
 * @author fairy
 */
public class GroupLeader {
    private List<Girl> listGirls;
    /**传递全班的女生*/
    public GroupLeader(List<Girl> _listGirls){
        this.listGirls = _listGirls;
    }
    /**有清查女生的工作*/
    public void countGirls(){
        System.out.println("女生数量是："+listGirls.size());
    }
}
