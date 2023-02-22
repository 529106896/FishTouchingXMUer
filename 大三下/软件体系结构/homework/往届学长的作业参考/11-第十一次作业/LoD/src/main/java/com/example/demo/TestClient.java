package com.example.demo;

import java.util.ArrayList;
import java.util.List;

/**
 * @author fairy
 */
public class TestClient {
    public static void main(String[] args) {
        List<Girl> listGirls = new ArrayList();
        //初始化女生
        for(int i=0;i<20;i++){
            listGirls.add(new Girl());
        }
        Teacher teacher= new Teacher();
        //老师发布命令
        teacher.command(new GroupLeader(listGirls));
    }
}
