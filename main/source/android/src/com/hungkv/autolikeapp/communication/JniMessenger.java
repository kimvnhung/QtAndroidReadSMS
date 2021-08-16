package com.hungkv.autolikeapp.communication;

import android.content.Context;
import android.util.Log;

import com.hungkv.autolikeapp.database.DatabaseHandler;
import com.hungkv.autolikeapp.database.Transaction;
import com.hungkv.autolikeapp.listener.SmsReceiver;

public class JniMessenger implements SmsReceiver.SmsListener
{
    private static final String TAG = JniMessenger.class.getName();
    public DatabaseHandler handler;


    private static native void callFromJava(String message);

    public JniMessenger() {

    }

    public void registerDatbaseHandler(Context context) {
        handler = new DatabaseHandler(context,DatabaseHandler.DATABASE_NAME,null,1);
        Log.i(TAG, "Initialize database handler");
        SmsReceiver.bindingListener(this);
    }


    public static void printFromJava(String message)
    {
        Log.i(TAG,"This is printed from JAVA, message is: " + message);
        if (message.equals("abcXYZ")){
            callFromJava("REFRESH_DATA");
        }
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
