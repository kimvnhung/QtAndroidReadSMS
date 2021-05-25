package com.hungkv.autolikeapp.database;

public class Transaction {
    private int id;
    private String phone;
    private String code;
    private int value;
    private String time;
    private String updateTime;
    private boolean status;

    public Transaction(int id, String phone, String code, int value, String time, String updateTime, boolean status) {
        this.id = id;
        this.phone = phone;
        this.code = code;
        this.value = value;
        this.time = time;
        this.updateTime = updateTime;
        this.status = status;
    }

    public Transaction(String phone, String code, int value, String time) {
        this.id = -1;
        this.phone = phone;
        this.code = code;
        this.value = value;
        this.time = time;
        this.updateTime = "";
        this.status = false;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getPhone() {
        return phone;
    }

    public void setPhone(String phone) {
        this.phone = phone;
    }

    public String getCode() {
        return code;
    }

    public void setCode(String code) {
        this.code = code;
    }

    public int getValue() {
        return value;
    }

    public void setValue(int value) {
        this.value = value;
    }

    public String getTime() {
        return time;
    }

    public void setTime(String time) {
        this.time = time;
    }

    public String getUpdateTime() {
        return updateTime;
    }

    public void setUpdateTime(String updateTime) {
        this.updateTime = updateTime;
    }

    public boolean isStatus() {
        return status;
    }

    public void setStatus(boolean status) {
        this.status = status;
    }

    public String getDisplayValue()
    {
        String rt = "";
        int para = value;
        while (para/1000 > 0){
            rt += para < value?(para%1000 +","):(para%1000);
            para /= 1000;
        }
        rt += para;
        return rt;
    }
}
