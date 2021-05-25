package com.hungkv.autolikeapp.listener;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.os.Build;
import android.os.Bundle;
import android.telephony.SmsMessage;
import android.util.Log;

import com.hungkv.autolikeapp.database.Transaction;


public class SmsReceiver extends BroadcastReceiver {

    private static final String SMS_RECEIVED = "android.provider.Telephony.SMS_RECEIVED";
    private static final String TAG = SmsReceiver.class.getName();
    private static final String CODE_PREFIX = "ALIKE";

    private static SmsListener listener;

    @Override
    public void onReceive(Context context, Intent intent) {
        Log.d(TAG, "onReceived : ");
        if (intent.getAction().equals(SMS_RECEIVED)) {
            Bundle data  = intent.getExtras();
            if (data != null){
                Object[] pdus = (Object[]) data.get("pdus");
                final SmsMessage[] messages = new SmsMessage[pdus.length];

                ArrayList<SmsTemplate> arrangedList = new ArrayList<>();


                //Collect message to same phone
                for (int i=0 ; i<pdus.length ; i++){
                    if(Build.VERSION.SDK_INT >= Build.VERSION_CODES.M){
                        String format = data.getString("format");
                        messages[i] = SmsMessage.createFromPdu((byte[]) pdus[i],format);
                    }else {
                        messages[i] = SmsMessage.createFromPdu((byte[]) pdus[i]);
                    }

                    String  msg = messages[i].getMessageBody();
                    String phone = messages[i].getOriginatingAddress();
                    Log.d(TAG, "Message : "+msg+"\nPhone : "+phone);
                    for (int j=0 ; j < arrangedList.size(); j++){
                        if(arrangedList.get(j).getPhone().equals(phone)){
                            arrangedList.get(j).addMessage(messages[i]);
                            break;
                        }

                        if (j == arrangedList.size()-1){
                            arrangedList.add(new SmsTemplate(phone));
                            arrangedList.get(arrangedList.size()-1).addMessage(messages[i]);
                            break;
                        }
                    }
                }

                for (int i=0 ; i<arrangedList.size(); i++){
                    SmsTemplate temp = arrangedList.get(i);
                    if(temp.getMessages().size()%3 == 0){
                        ArrayList<SmsMessage> list = temp.getMessages();
                        for (int j=0; j*3 + 2 <list.size();j++){
                            String msg = list.get(j).getMessageBody()+list.get(j+1).getMessageBody()+list.get(j+2).getMessageBody();
                            if (msg.contains(CODE_PREFIX)){
                                int index = msg.indexOf(CODE_PREFIX);
                                String code = msg.substring(index);
                                int value = 0;
                                try {
                                    String[] splitString = msg.split("\\+\\d+.+VND");
                                    //value = Integer.parseInt();
                                }catch (NumberFormatException e){
                                    Log.e(TAG, "Error : "+e.getMessage());
                                }
                                Transaction transaction = new Transaction(temp.getPhone(),code,)
                            }
                        }
                    }
                }

            }
        }
    }



    public static void bindingListener(SmsListener pListener){
        listener = pListener;
    }

    private class SmsTemplate{
        private String phone;
        private ArrayList<SmsMessage> messages;

        public SmsTemplate(String phone) {
            this.phone = phone;
            this.messages = new ArrayList<>();
        }

        public String getPhone() {
            return phone;
        }

        public void setPhone(String phone) {
            this.phone = phone;
        }

        public void addMessage(SmsMessage sms) {
            this.messages.add(sms);
        }

        public ArrayList<SmsMessage> getMessages() {
            return messages;
        }
    }

    public interface SmsListener{
        void onSmsComing(Transaction transaction);
    }
}
