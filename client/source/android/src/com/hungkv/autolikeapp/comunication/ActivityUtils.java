package com.hungkv.autolikeapp.comunication;

import android.content.Context;
import android.content.Intent;
import android.util.Log;
import android.content.BroadcastReceiver;
import android.content.IntentFilter;

import com.hungkv.autolikeapp.database.DatabaseHandler;
import com.hungkv.autolikeapp.database.Transaction;
import com.hungkv.autolikeapp.listener.SmsReceiver;

public class ActivityUtils implements SmsReceiver.SmsListener {

    private static native void sendToQt(String message);

    private static final String TAG = "ActivityUtils";
    public static final String BROADCAST_NAME_ACTION = "com.hungkv.autolikeapp.comunication.qtandroidservice.broadcast.name";

    public DatabaseHandler handler;

    public void registerServiceBroadcastReceiver(Context context) {
        IntentFilter intentFilter = new IntentFilter();
        intentFilter.addAction(BROADCAST_NAME_ACTION);
        context.registerReceiver(serviceMessageReceiver, intentFilter);
        Log.i(TAG, "Registered broadcast receiver");
        handler = new DatabaseHandler(context,DatabaseHandler.DATABASE_NAME,null,1);
        Log.i(TAG, "Initialize database handler");
        SmsReceiver.bindingListener(this);
    }

    private BroadcastReceiver serviceMessageReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            Log.i(TAG, "In OnReceive broadcast receiver");
            if (BROADCAST_NAME_ACTION.equals(intent.getAction())) {
                String name = intent.getStringExtra("name");
                Log.i(TAG, "Service received name: " + name);
                String message = name;
                sendToQt(message);
                Log.i(TAG, "Service sent back message: " + message);
            }
        }
    };

    @Override
    public void onSmsComing(Transaction transaction) {
        Log.i(TAG, "onSmsComming : "+transaction.getCode());
    }
}
