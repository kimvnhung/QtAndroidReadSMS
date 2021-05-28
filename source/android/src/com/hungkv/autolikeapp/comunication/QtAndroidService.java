package com.hungkv.autolikeapp.comunication;

import android.content.Context;
import android.content.Intent;
import android.util.Log;
import android.app.Service;
import android.os.IBinder;

import com.hungkv.autolikeapp.database.DatabaseHandler;
import com.hungkv.autolikeapp.database.Transaction;
import com.hungkv.autolikeapp.listener.SmsReceiver;

public class QtAndroidService extends Service implements SmsReceiver.SmsListener
{
    private static native void sendToQt(String message);
    private static final String TAG = "QtAndroidService";

    private static final String DATABASE_PREFIX = "DATABASE_AVAILABLE";
     private static final String UPDATE_DATA = "UPDATE_DATA";

    private DatabaseHandler handler;

    @Override
    public void onCreate() {
        super.onCreate();
        Log.i(TAG, "Creating Service");
        handler = new DatabaseHandler(this,DatabaseHandler.DATABASE_NAME,null,1);
        String path = this.getDatabasePath(handler.getDatabaseName()).getAbsolutePath();
        if(path.length() > 0){
            sendToQt(DATABASE_PREFIX+path);
            Log.i(TAG,"Sent path : "+path);
            sendToQt(UPDATE_DATA);
        }
        Log.i(TAG, "Initialize database handler");
        SmsReceiver.bindingListener(this);
    }

    @Override
    public void onDestroy() {
        super.onDestroy();
        Log.i(TAG, "Destroying Service");
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        int ret = super.onStartCommand(intent, flags, startId);

        String name = new String(intent.getByteArrayExtra("name"));
        Log.i(TAG, "Service received name: " + name);
        //sendToQt(UPDATE_DATA);
        return ret;
    }

    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }

    @Override
    public void onSmsComing(Transaction transaction) {
        Log.i(TAG, "onSmsComming : "+transaction.getCode());
        handler.insertTransaction(transaction);
        for (String st: handler.getListTableInDatabase()) {
            Log.i(TAG,"Tables from java: "+st);
        }
        for (Transaction tr : handler.getAllTransaction()){
            Log.i(TAG,tr.toString());
        }
    }
}
