package com.hungkv.autolikeapp.comunication;

import android.content.Context;
import android.content.Intent;
import android.util.Log;
import android.content.BroadcastReceiver;
import android.content.IntentFilter;

public class ActivityUtils {

    private static native void sendToQt(String message);

    private static final String TAG = "ActivityUtils";
    public static final String BROADCAST_NAME_ACTION = "com.hungkv.autolikeapp.comunication.qtandroidservice.broadcast.name";

    public void registerServiceBroadcastReceiver(Context context) {
        IntentFilter intentFilter = new IntentFilter();
        intentFilter.addAction(BROADCAST_NAME_ACTION);
        context.registerReceiver(serviceMessageReceiver, intentFilter);
        Log.i(TAG, "Registered broadcast receiver");
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
}
