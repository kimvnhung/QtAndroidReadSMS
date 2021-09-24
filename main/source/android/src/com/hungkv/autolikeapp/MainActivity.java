package com.hungkv.autolikeapp;

import android.util.Log;
import android.os.Bundle;
import android.content.Intent;
import android.annotation.TargetApi;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.provider.Telephony;


import com.hungkv.autolikeapp.communication.QtAndroidService;
import com.hungkv.autolikeapp.database.DatabaseHandler;

import org.qtproject.qt5.android.bindings.QtActivity;

public class MainActivity extends QtActivity
{
    private static final String TAG = MainActivity.class.getName();
    public static native void emitToUI(String message);

    private DatabaseHandler handler;

    @Override
    protected void onStart() {
        super.onStart();
        Log.i(TAG, "onStart");
        //QtAndroidService.sendToQt("onStart");
        //startBackgroundService();
        activeMainActivity();

    }

    @Override
    protected void onResume() {
        super.onResume();
//        if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.KITKAT) {
//            if (!Telephony.Sms.getDefaultSmsPackage(this).equals(this.getPackageName())) {
//                AlertDialog.Builder builder = new AlertDialog.Builder(MainActivity.this);
//                builder.setMessage("This app is not set as your default messaging app. Do you want to set it as default?")
//                        .setCancelable(false)
//                        .setTitle("Alert!")
//                        .setNegativeButton("No", new DialogInterface.OnClickListener() {
//                            @Override
//                            public void onClick(DialogInterface dialog, int which) {
//                                dialog.dismiss();
//                            }
//                        })
//                        .setPositiveButton("Yes", new DialogInterface.OnClickListener() {
//                            public void onClick(DialogInterface dialog, int id) {
//                                Intent intent = new Intent(Telephony.Sms.Intents.ACTION_CHANGE_DEFAULT);
//                                intent.putExtra(Telephony.Sms.Intents.EXTRA_PACKAGE_NAME, getPackageName());
//                                startActivity(intent);
//                            }
//                        });
//                builder.show();
//            }
//        }
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
