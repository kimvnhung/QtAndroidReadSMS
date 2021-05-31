package com.hungkv.autolikeapp.comunication;

import android.app.Notification;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.app.Service;
import android.content.Intent;
import android.os.Build;
import android.os.IBinder;
import android.util.Log;
import android.widget.Toast;

import com.hungkv.autolikeapp.Constants;
import org.qtproject.qt5.android.bindings.QtActivity;
import com.hungkv.autolikeapp.R;
import com.hungkv.autolikeapp.database.DatabaseHandler;
import com.hungkv.autolikeapp.database.Transaction;
import com.hungkv.autolikeapp.listener.SmsReceiver;

public class QtAndroidService extends Service implements SmsReceiver.SmsListener
{
    private static native void sendToQt(String message);
    private static final String TAG = "QtAndroidService";

    private DatabaseHandler handler;

    private int NonSeenTransaction = 0;

    @Override
    public void onCreate() {
        super.onCreate();
        Log.i(TAG, "Creating Service");
        handler = new DatabaseHandler(this,DatabaseHandler.DATABASE_NAME,null,1);
        Log.i(TAG, "Initialize database handler");
        SmsReceiver.bindingListener(this);

        String path = this.getDatabasePath(handler.getDatabaseName()).getAbsolutePath();
        if(path.length() > 0){
            sendToQt(Constants.INFO.DATABASE_DECLARE_INFO+path);
            Log.i(TAG,"Sent path : "+path);
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
        switch (action){
            case Constants.ACTION.START_BACKGROUND_SERVICE_ACTION:
                Log.i(TAG, "Start Background Service");
                stopForeground(true);
                Log.i(TAG,"Stop Foreground Serivice");

                NonSeenTransaction = 0;
                return rt;
            case Constants.ACTION.START_FOREGROUND_ACTION:
                Log.i(TAG,Constants.JAVA_LOG+"Start Foreground Service");
                Toast.makeText(this,"Start Foreground",Toast.LENGTH_LONG).show();
                showNotification();

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
        }
        return START_STICKY;
    }

    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }

    //Notification Setting Up
    Notification status;

    private void showNotification(){
        //setup normal notification view and expand view
//        RemoteViews normalView = new RemoteViews(getPackageName(), R.layout.status_bar);
//        RemoteViews expandView = new RemoteViews(getPackageName(), R.layout.status_bar_expanded);

        //Reopen app intent
        Intent notificationIntent = new Intent(this, QtActivity.class);
        notificationIntent.setAction(Constants.ACTION.OPEN_QT_ACTIVITY_ACTION);
        notificationIntent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK
                | Intent.FLAG_ACTIVITY_CLEAR_TASK);
        PendingIntent pendingIntent = PendingIntent.getActivity(this, 0,
                notificationIntent, 0);

        Intent closeIntent = new Intent(this, QtAndroidService.class);
        closeIntent.setAction(Constants.ACTION.STOP_FOREGROUND_ACTION);
        PendingIntent pcloseIntent = PendingIntent.getService(this, 0,
                closeIntent, 0);

        if (Build.VERSION.SDK_INT>=26){
            NotificationManager notificationManager = (NotificationManager) getSystemService(NOTIFICATION_SERVICE);
            NotificationChannel channel = new NotificationChannel(Constants.NOTIFICATION.NOTIFICATION_CHANNEL_ID,
                    Constants.NOTIFICATION.NOTIFICATION_CHANNEL_NAME,
                    NotificationManager.IMPORTANCE_DEFAULT);
            channel.setDescription(Constants.NOTIFICATION.NOTIFICATION_DESCRIPTION);
            notificationManager.createNotificationChannel(channel);
            status = new Notification.Builder(this,Constants.NOTIFICATION.NOTIFICATION_CHANNEL_ID)
                    .setSmallIcon(R.drawable.ic_launcher)
                    .setContentTitle("Auto Like Status")
                    .setContentText("You have "+NonSeenTransaction+" new transaction"+(NonSeenTransaction>1?"s":"")+"!")
                    .build();

        }else {
            status = new Notification.Builder(this)
                    .setSmallIcon(R.drawable.ic_launcher)
                    .setContentTitle("Auto Like Status")
                    .setContentText("You have "+NonSeenTransaction+" new transaction"+(NonSeenTransaction>1?"s":"")+"!")
                    .setPriority(Notification.PRIORITY_LOW)
                    .build();
        }

//        status.contentView = normalView;
//        status.bigContentView = expandView;

        status.flags = Notification.FLAG_ONGOING_EVENT;
        status.icon = R.drawable.ic_launcher;
        status.contentIntent = pendingIntent;

        startForeground(Constants.NOTIFICATION.FOREGROUND_SERVICE, status);
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
        for (String st: handler.getListTableInDatabase()) {
            Log.i(TAG,"Tables from java: "+st);
        }
        for (Transaction tr : handler.getAllTransaction()){
            Log.i(TAG,tr.toString());
        }

        //Counter
        NonSeenTransaction++;
    }
}
