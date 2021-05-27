package com.hungkv.autolikeapp.comunication;

import android.content.Context;
import android.content.Intent;
import android.util.Log;
import android.os.IBinder;
import org.qtproject.qt5.android.bindings.QtService;
import android.content.IntentFilter;

public class QtAndroidService extends QtService
{
    private static final String TAG = "QtAndroidService";
    public static final String LOG_KEY = "log";

    @Override
    public void onCreate() {
        super.onCreate();
        Log.d(TAG, "Creating Service");
    }

    @Override
    public void onDestroy() {
        super.onDestroy();
        Log.d(TAG, "Destroying Service");
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        int ret = super.onStartCommand(intent, flags, startId);

        String name = new String(intent.getByteArrayExtra("name"));
        Intent sendToUiIntent = new Intent();
        sendToUiIntent.setAction(ActivityUtils.BROADCAST_NAME_ACTION);
        sendToUiIntent.putExtra("name", name);
        Log.d(TAG, "Service sending broadcast");
        sendBroadcast(sendToUiIntent);

        return ret;
    }

    @Override
    public IBinder onBind(Intent intent) {
        return super.onBind(intent);
    }
}
