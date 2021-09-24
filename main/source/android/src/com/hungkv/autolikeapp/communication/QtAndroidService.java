package com.hungkv.autolikeapp.communication;

import android.app.Notification;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.PendingIntent;
import org.qtproject.qt5.android.bindings.QtService;
import android.content.Context;
import android.content.Intent;
import android.os.Build;
import android.os.IBinder;
import android.util.Log;
import android.widget.Toast;
import org.json.JSONObject;
import android.database.Cursor;
import android.net.Uri;

import java.util.Timer;
import java.util.TimerTask;
import java.util.Date;

import com.hungkv.autolikeapp.Constants;
import com.hungkv.autolikeapp.MainActivity;
import com.hungkv.autolikeapp.R;
import com.hungkv.autolikeapp.database.DatabaseHandler;
import com.hungkv.autolikeapp.database.Transaction;
import com.hungkv.autolikeapp.listener.SmsReceiver;

public class QtAndroidService extends QtService implements SmsReceiver.SmsListener
{

    private static native void emitToBackground(String action, String data);
    private static native void emitToBackground(String action);
    private static final String TAG = "QtAndroidService";

    private static DatabaseHandler handler;

    private int NonSeenTransaction = 0;
    private int UpdateQueueCounter = 0;

    TimerTask serviceClock = new TimerTask() {
        @Override
        public void run() {
            emitToBackground(Constants.ACTION.SERVICE_CLOCK_ACTION);
        }
    };

    Timer operator  = new Timer();

    @Override
    public void onCreate() {
        super.onCreate();
        Log.i(TAG, "Creating Service");

        //binding sms listener
        SmsReceiver.bindingListener(this);

        //initialize database
        if(handler == null){
            handler = new DatabaseHandler(this,DatabaseHandler.DATABASE_NAME,null,1);
            Log.i(TAG, "Initialize database handler");
        }

    }

    @Override
    public void onDestroy() {
        super.onDestroy();
        Log.i(TAG, "Destroying Service");

    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        int rt = super.onStartCommand(intent,flags,startId);
        if (intent == null){
            return rt;
        }

        String action = intent.getAction();
        if(action != null){
            switch (action){
                case Constants.ACTION.START_BACKGROUND_SERVICE_ACTION:
                    Log.i(TAG, "Start Background Service");
                    String path = this.getDatabasePath(handler.getDatabaseName()).getAbsolutePath();
                    if(path.length() > 0){
                        emitToBackground(Constants.INFO.DATABASE_DECLARE_INFO,path);
                        Log.i(TAG,"Sent path : "+path);
                        Log.d(TAG, "Start service clock");
                        operator.schedule(serviceClock,500,3000);
                    }

                    NonSeenTransaction = 0;
                    return rt;
                case Constants.ACTION.START_FOREGROUND_ACTION:
                    Log.i(TAG,Constants.JAVA_LOG+"Start Foreground Service");
                    Toast.makeText(this,"Start Foreground",Toast.LENGTH_LONG).show();

                    break;
                case Constants.ACTION.STOP_FOREGROUND_ACTION:
                    Log.i(TAG,Constants.JAVA_LOG+"Stop Foreground Service");
                    stopForeground(true);
                    stopSelf();
                    break;
                case Constants.ACTION.LOG_ACTION:
                    String message = new String(intent.getByteArrayExtra("message"));
                    Log.i(TAG, Constants.QT_LOG + message);
                    break;
                case Constants.ACTION.ACTIVITY_STOPPED_ACTION:
                    break;
                case Constants.ACTION.ACTIVITY_STARTED_ACTION:
                    break;
                case Constants.ACTION.UPDATE_TRANSACTION_ACTION:
                    String jsonTrans = new String(intent.getByteArrayExtra("Transaction"));
                    try {
                        JSONObject trans = new JSONObject(jsonTrans);
                        Transaction transaction = new Transaction(trans.getInt(Constants.TRANSACTION.ID),
                                trans.getString(Constants.TRANSACTION.PHONE),
                                trans.getString(Constants.TRANSACTION.CODE),
                                trans.getInt(Constants.TRANSACTION.VALUE),
                                trans.getString(Constants.TRANSACTION.TIME),
                                trans.getString(Constants.TRANSACTION.UPDATE_TIME),
                                trans.getInt(Constants.TRANSACTION.STATUS),
                                trans.getString(Constants.TRANSACTION.SMS_CONTENT));
                        handler.updateTransaction(transaction);
                        emitToBackground(Constants.ACTION.REFRESH_UI_ACTION);
                    } catch (Exception e){
                        Log.e(TAG, Constants.JAVA_LOG+" : "+e.getMessage() );
                    }
                    break;
                case Constants.ACTION.UPDATE_TRANSACTION_STATUS_ACTION:
                    path = this.getDatabasePath(handler.getDatabaseName()).getAbsolutePath();
                    Log.d(TAG, path);
                    jsonTrans = new String(intent.getByteArrayExtra("Transaction"));
                    try {
                        if(jsonTrans.equals("")){
                            Log.d(TAG,"jsonTrans empty");
                            break;
                        }
                        JSONObject trans = new JSONObject(jsonTrans);
                        Transaction transaction = new Transaction(trans.getInt(Constants.TRANSACTION.ID),
                                trans.getString(Constants.TRANSACTION.PHONE),
                                trans.getString(Constants.TRANSACTION.CODE),
                                trans.getInt(Constants.TRANSACTION.VALUE),
                                trans.getString(Constants.TRANSACTION.TIME),
                                trans.getString(Constants.TRANSACTION.UPDATE_TIME),
                                trans.getInt(Constants.TRANSACTION.STATUS),
                                trans.getString(Constants.TRANSACTION.SMS_CONTENT));
                        handler.updateTransactionStatus(transaction);
                        emitToBackground(Constants.ACTION.REFRESH_UI_ACTION);
                        Log.d(TAG, jsonTrans);
                    } catch (Exception e){
                        Log.e(TAG, Constants.JAVA_LOG+" : "+e.getMessage() );
                    }
                    break;
                case Constants.INFO.UPDATE_DATA_INFO:
                    Log.d(TAG, "Update DAta info");
                    break;
                case Constants.ACTION.DELETE_SMS_ACTION:
                    try {
                        String keys = new String(intent.getByteArrayExtra("Keys"));
                        if(keys.equals("")){
                            break;
                        }
                        Log.d(TAG,"Deleting SMS from inbox");
                        Uri uriSms = Uri.parse("content://sms/inbox");
                        Cursor c = this.getContentResolver().query(uriSms,
                                new String[] { "_id", "thread_id", "address",
                                        "person", "date", "body" }, null, null, null);

                        if (c != null && c.moveToFirst()) {
                            do {
                                long id = c.getLong(0);
                                String address = c.getString(2);
                                String date = c.getString(4);

                                if (keys.contains(address)){
                                    Date dateObj = new Date(Long.parseLong(date));
                                    //add 30 days
                                    dateObj.setTime(dateObj.getTime()+30*24*60*60*1000);
                                    if (dateObj.before(new Date())){
                                        Log.d(TAG,"Delete sms wit address : "+address);
                                        this.getContentResolver().delete(
                                                Uri.parse("content://sms/" + id), null, null);
                                    }
                                }


                            } while (c.moveToNext());
                        }
                    } catch (Exception e) {
                        Log.e(TAG,"Could not delete SMS from inbox: " + e.getMessage());
                    }
                    break;
                case Constants.ACTION.NOTIFY_CONNECTION_ACTION:
                    emitToBackground(Constants.INFO.INTERNET_CONNECTED);
                    Log.i(TAG, "Internet Connected");
                    break;
            }
        }

        return START_STICKY;
    }

    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }


    private void notifyMessage() {
        try {
            NotificationManager m_notificationManager = (NotificationManager)getSystemService(Context.NOTIFICATION_SERVICE);
            Notification.Builder m_builder;
            if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.O) {
                int importance = NotificationManager.IMPORTANCE_DEFAULT;
                NotificationChannel notificationChannel = new NotificationChannel(Constants.NOTIFICATION.NOTIFICATION_CHANNEL_ID
                        , Constants.NOTIFICATION.NOTIFICATION_CHANNEL_NAME, importance);
                m_notificationManager.createNotificationChannel(notificationChannel);
                m_builder = new Notification.Builder(this, notificationChannel.getId());
            } else {
                m_builder = new Notification.Builder(this);
            }

            m_builder.setSmallIcon(R.drawable.ic_launcher)
                    .setSmallIcon(R.drawable.ic_launcher)
                    .setContentTitle("Auto Like Status")
                    .setContentText("You have "+NonSeenTransaction+" new transaction"+(NonSeenTransaction>1?"s":"")+"!")
                    .setPriority(Notification.PRIORITY_LOW)
                    .build();

            m_notificationManager.notify(0, m_builder.build());
        } catch (Exception e) {
            e.printStackTrace();
        }
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
    //End Setting

    @Override
    public void onSmsComing(Transaction transaction) {
        Log.i(TAG, "onSmsComming : "+transaction.getCode());
        handler.insertTransaction(transaction);

        //Counter
        NonSeenTransaction++;
        UpdateQueueCounter++;

        if (NonSeenTransaction >= 5){
            //notify();
        }

        emitToBackground(Constants.ACTION.UPDATE_TO_SERVER);

    }
}

