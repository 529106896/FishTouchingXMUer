package com.example.exp_2;

import com.fasterxml.jackson.annotation.JsonFormat;
import org.junit.jupiter.api.Test;

import java.time.LocalDateTime;
import java.util.Date;

public class DateTimeTest {

    @JsonFormat(shape=JsonFormat.Shape.STRING, pattern="yyyy-MM-dd HH:mm:ss")
    private LocalDateTime myDateTime;

    @Test
    public void testDateTime() {
        myDateTime = LocalDateTime.now();
        System.out.println(myDateTime.toString().replaceAll("T", " "));
    }
}
