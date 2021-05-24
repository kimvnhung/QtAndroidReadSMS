package com.hungkv.autolikeapp.listener;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.os.Build;
import android.os.Bundle;
import android.telephony.SmsMessage;
import android.util.Log;
import java.util.regex.Pattern;

public class SmsReceiver extends BroadcastReceiver {

    private static final String SMS_RECEIVED = "android.provider.Telephony.SMS_RECEIVED";
    private  static final String TAG = SmsReceiver.class.getName();

    private static SmsListener listener;

    @Override
    public void onReceive(Context context, Intent intent) {
        Log.d(TAG, "onReceived : ");
        if (intent.getAction().equals(SMS_RECEIVED)) {
            Bundle data  = intent.getExtras();
            if (data != null){
                Object[] pdus = (Object[]) data.get("pdus");
                final SmsMessage[] messages = new SmsMessage[pdus.length];

                for (int i=0 ; i<pdus.length ; i++){
                    if(Build.VERSION.SDK_INT >= Build.VERSION_CODES.M){
                        String format = data.getString("format");
                        messages[i] = SmsMessage.createFromPdu((byte[]) pdus[i],format);
                    }else {
                        messages[i] = SmsMessage.createFromPdu((byte[]) pdus[i]);
                    }

                    String msg = messages[i].getMessageBody();
                    String phone = messages[i].getOriginatingAddress();
                    Log.d(TAG, "Message : "+msg+"\nPhone : "+phone);
                }

            }
        }
    }

    public static void bindingListener(SmsListener pListener){
        listener = pListener;
    }

    public interface SmsListener{
        void onSmsComing(String msg);
    }
}
