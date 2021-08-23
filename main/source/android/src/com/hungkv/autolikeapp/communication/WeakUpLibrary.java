package com.hungkv.autolike.communication;

public class WeakUpLibrary {
    static{
        System.loadLibrary("Updater_armeabi-v7a");
    }

    private static native void callLibrary();


    public WeakUpLibrary() {}

    public static void checkConnection(String msg){
        System.out.println("From Qt :"+msg);
        callLibrary();
    }
}
