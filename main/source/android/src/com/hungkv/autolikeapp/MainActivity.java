package com.hungkv.autolikeapp;

import android.util.Log;
import android.os.Bundle;
import android.content.Intent;


import com.hungkv.autolikeapp.comunication.QtAndroidService;
import com.hungkv.autolikeapp.database.DatabaseHandler;

import org.qtproject.qt5.android.bindings.QtActivity;

public class MainActivity extends QtActivity
{
    private static final String TAG = MainActivity.class.getName();

    private DatabaseHandler handler;

    @Override
    protected void onStart() {
        super.onStart();
        Log.i(TAG, "onStart");
        //QtAndroidService.sendToQt("onStart");
        //startBackgroundService();
        activeMainActivity();

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

    private void activeMainActivity(){
        Intent activeIntent = new Intent(this,QtAndroidService.class);
        activeIntent.setAction(Constants.ACTION.ACTIVITY_STARTED_ACTION);
        startService(activeIntent);
    }

    private void deactiveMainActivity(){
        Intent deactiveIntent = new Intent(this, QtAndroidService.class);
        deactiveIntent.setAction(Constants.ACTION.ACTIVITY_STOPPED_ACTION);
        startService(deactiveIntent);
    }

    @Override
    protected void onPause() {
        super.onPause();
        Log.i(TAG,"onStop");
    }

    @Override
    protected void onStop() {
        super.onStop();
        Log.i(TAG,"onStop");
        //startForegroundService();
        //QtAndroidService.sendToQt("onStop");
        deactiveMainActivity();
    }
}
