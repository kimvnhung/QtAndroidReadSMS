package com.hungkv.autolikeapp;

import android.util.Log;
import android.os.Bundle;
import android.content.Intent;


import com.hungkv.autolikeapp.comunication.QtAndroidService;

import org.qtproject.qt5.android.bindings.QtActivity;

public class MainActivity extends QtActivity
{
    private static final String TAG = MainActivity.class.getName();

    @Override
    protected void onStart() {
        super.onStart();
        Log.i(TAG, "onStart");
        //QtAndroidService.sendToQt("onStart");
        //startBackgroundService();
    }

    private void startBackgroundService(){
        Intent serviceIntent = new Intent(this,QtAndroidService.class);
        serviceIntent.setAction(Constants.ACTION.START_BACKGROUND_SERVICE_ACTION);
        startService(serviceIntent);
    }

    private void startForegroundService() {
        Intent serviceIntent = new Intent(this, QtAndroidService.class);
        serviceIntent.setAction(Constants.ACTION.START_FOREGROUND_ACTION);
        startService(serviceIntent);
    }

    @Override
    protected void onStop() {
        super.onStop();
        Log.i(TAG,"onStop");
        //startForegroundService();
        //QtAndroidService.sendToQt("onStop");
    }
}
