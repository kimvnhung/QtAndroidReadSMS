package com.hungkv.autolikeapp.listener;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.os.Build;
import android.os.Bundle;
import android.telephony.SmsMessage;
import android.util.Log;

import java.util.ArrayList;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

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
                    //Log.d(TAG, "Message : "+msg+"\nPhone : "+phone);
                    if(msg.charAt(msg.length()-1) == '\n'){
                        msg = msg.substring(0,msg.length()-1)+" ";
                    }
                    if(arrangedList.size() == 0){
                        arrangedList.add(new SmsTemplate(phone));
                        arrangedList.get(arrangedList.size()-1).addMessage(messages[i]);
                    }else{
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
                }

                Log.i(TAG,"arrangedList.size : "+arrangedList.size());

                for (int i=0 ; i<arrangedList.size(); i++){
                    SmsTemplate temp = arrangedList.get(i);
                    if(temp.getMessages().size()%3 == 0){
                        ArrayList<SmsMessage> list = temp.getMessages();
                        for (int j=0; j*3 + 2 <list.size();j++){
                            String msg = list.get(j).getMessageBody()+list.get(j+1).getMessageBody()+list.get(j+2).getMessageBody();
                            //Log.i(TAG,"Message at j = "+j+" : "+msg);
                            msg = msg.replace("\n","");
                            if (msg.contains(CODE_PREFIX)){
                                int index = msg.indexOf(CODE_PREFIX);
                                String code = msg.substring(index);
                                int value = 0;

                                try {
                                    //value = Integer.parseInt();
                                    Pattern pattern = Pattern.compile("\\+\\d{1,3}((,\\d{3}){0,4})\\sVND");
                                    Matcher matcher = pattern.matcher(msg);
                                    if (matcher.find())
                                    {
                                        Log.i(TAG, "Matcher : "+matcher.group());
                                        String valueSt = matcher.group().substring(1,matcher.group().length()-4);
                                        value = Integer.parseInt(valueSt.replace(",",""));
                                        Log.i(TAG, "value : "+value);
                                    }else {
                                        Log.i(TAG, "No matching regex");
                                    }
                                }catch (NumberFormatException e){
                                    Log.e(TAG, "Error : "+e.getMessage());
                                }catch (Exception e){
                                    Log.e(TAG, "Error : "+e.getMessage());
                                }
                                String time = "";
                                Pattern timePatern = Pattern.compile("(luc)(\\s(\\d+\\W\\d+\\W\\d+))+");
                                Matcher matcherTime = timePatern.matcher(msg);
                                if(matcherTime.find()){
                                    time = matcherTime.group().substring(4);
                                    Log.i(TAG, "Time : "+time);
                                }else {
                                    Log.e(TAG,"No matching regex time");
                                }
                                Transaction transaction = new Transaction(temp.getPhone(),code,value,time);
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
