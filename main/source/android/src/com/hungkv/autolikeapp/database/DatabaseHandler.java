package com.hungkv.autolikeapp.database;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.util.Log;
import android.widget.Toast;

import java.util.ArrayList;
import java.util.List;

public class DatabaseHandler extends SQLiteOpenHelper {

    private static String TAG = DatabaseHandler.class.getName();

    private Context mContext;
    private static final int DATABASE_VERSION = 1 ;
    public static String DATABASE_NAME = "AutoLikeAgency.db";

    public static final String TABLE_NAME_AGENCY = "Agency";
    public static final String COLUMN_ID = "_id";
    public static final String COLUMN_PHONE = "_phone";
    public static final String COLUMN_TRANSACTION_CODE = "_transaction_code";
    public static final String COLUMN_VALUE = "_value";
    public static final String COLUMN_TIME = "_time";
    public static final String COLUMN_UPDATE_TIME = "_update_time";
    public static final String COLUMN_STATUS = "_status";



    public DatabaseHandler(Context context, String name, SQLiteDatabase.CursorFactory factory, int version) {
        super(context, name, factory, DATABASE_VERSION);
        this.DATABASE_NAME= name;
        this.mContext = context;
        Log.i(TAG,this.mContext.getDatabasePath(this.getDatabaseName()).getAbsolutePath());
        Log.i(TAG,this.mContext.getDatabasePath(this.getDatabaseName()).getPath());

    }

    @Override
    public void onCreate(SQLiteDatabase sqLiteDatabase) {
        String query = "CREATE TABLE " + TABLE_NAME_AGENCY + "("+
                COLUMN_ID +" INTEGER PRIMARY KEY AUTOINCREMENT, "+
                COLUMN_PHONE+" TEXT, "+
                COLUMN_TRANSACTION_CODE+" TEXT, "+
                COLUMN_VALUE+" INTEGER,"+
                COLUMN_TIME+" TEXT, " +
                COLUMN_UPDATE_TIME + " TEXT, " +
                COLUMN_STATUS + " INTEGER "+
                "); ";
        sqLiteDatabase.execSQL(query);
        Log.i(TAG,"Create table success");

    }

    @Override
    public void onUpgrade(SQLiteDatabase sqLiteDatabase, int i, int i1) {
        sqLiteDatabase.execSQL("DROP TABLE IF EXISTS " + TABLE_NAME_AGENCY);
        onCreate(sqLiteDatabase);
    }

    //xóa toàn bộ data trong database (kể cả các bảng)
    public void resetAllData(){
        SQLiteDatabase db =getWritableDatabase();

        try {

            // query to obtain the names of all tables in your database
            Cursor c = db.rawQuery("SELECT name FROM sqlite_master WHERE type='table'", null);
            List<String> tables = new ArrayList<>();

            // iterate over the result set, adding every table name to a list
            while (c.moveToNext()) {
                tables.add(c.getString(0));
            }

            // call DROP TABLE on every table name
            for (String table : tables) {
                String dropQuery = "DROP TABLE IF EXISTS " + table;
                db.execSQL(dropQuery);
            }
        }catch (Exception e){
            e.getMessage();
            Toast.makeText(mContext,"Eror: resetAllData()",Toast.LENGTH_LONG).show();
        }
        onCreate(db);

    }

    //lấy danh sách các bảng trong database
    public String[] getListTableInDatabase(){
        SQLiteDatabase db = getWritableDatabase();

        // query to obtain the names of all tables in your database
        Cursor c = db.rawQuery("SELECT name FROM sqlite_master WHERE type='table'", null);
        List<String> tables = new ArrayList<>();

        // iterate over the result set, adding every table name to a list
        while (c.moveToNext()) {
            tables.add(c.getString(0));
        }
        String[] result = new String[tables.size()];
        for (int i=0;i<result.length;i++){
            result[i] = tables.get(i);
        }
        c.close();
        return result;
    }

    //Xóa bảng
    public void dropTable(String table){
        SQLiteDatabase db = getWritableDatabase();
        String drop = "DROP TABLE IF EXISTS " + table;
        db.execSQL(drop);
    }

    //thêm từ
    public void insertTransaction(Transaction transaction) {
        Log.i(TAG, "insertTransaction - "+transaction.getCode());
        ContentValues values = new ContentValues();
        values.put(COLUMN_PHONE, transaction.getPhone());
        values.put(COLUMN_TRANSACTION_CODE, transaction.getCode());
        values.put(COLUMN_VALUE, transaction.getValue());
        values.put(COLUMN_TIME, transaction.getTime());
        values.put(COLUMN_UPDATE_TIME, transaction.getUpdateTime());
        values.put(COLUMN_STATUS, transaction.getStatus());

        SQLiteDatabase db = getWritableDatabase();

        db.insert(TABLE_NAME_AGENCY, null, values);

        db.close();
    }

    //xoas
    public boolean deleteTransaction(int id){
        Log.i(TAG, "deleteTransaction - "+id);
        SQLiteDatabase db = getWritableDatabase();

        try {
            String deleteQuery = "DELETE FROM " + TABLE_NAME_AGENCY +" WHERE "+COLUMN_ID +" = "+id;


            db.execSQL(deleteQuery);
            db.close();
            return true;
        }catch (Exception e){
            e.getMessage();
            Toast.makeText(mContext,"Error: deleteWord(String id)",Toast.LENGTH_LONG).show();
        }

        db.close();
        return false;
    }

    //cap nhat
    public boolean updateTransaction(Transaction transaction){
        Log.i(TAG, "updateTransaction - "+transaction.getCode());
        SQLiteDatabase db = getWritableDatabase();

        try {
            String updateQuery = "UPDATE "+ TABLE_NAME_AGENCY+ " SET " +
                    COLUMN_PHONE +"='"+transaction.getPhone()+"' , "+
                    COLUMN_TRANSACTION_CODE+"='"+transaction.getCode()+"',"+
                    COLUMN_VALUE+"= "+transaction.getValue()+" ,"+
                    COLUMN_TIME+"= '"+transaction.getTime()+"' ," +
                    COLUMN_UPDATE_TIME+"='"+transaction.getUpdateTime()+"' ," +
                    COLUMN_STATUS +" = "+transaction.getStatus()+" WHERE "+
                    COLUMN_ID+"= "+transaction.getId();

            db.execSQL(updateQuery);
            db.close();
            return true;
        }catch (Exception e){
            e.getMessage();
            Toast.makeText(mContext,"Error: updateWord(NouveauMot nouveauMot)",Toast.LENGTH_LONG).show();
        }
        db.close();
        return false;
    }

public boolean updateTransactionStatus(Transaction transaction){
        Log.i(TAG, "updateTransactionStatus - "+transaction.getCode());
        ArrayList<Transaction> listSpecialTrans = getSpecialTransaction(transaction);
        int counter = 0;
        Log.d(TAG,"List Special Size : "+listSpecialTrans.size());
        for(int i=0;i<listSpecialTrans.size();i++){
            listSpecialTrans.get(i).setStatus(transaction.getStatus());//Accept
            if(updateTransaction(listSpecialTrans.get(i))){
                counter++;
            }
        }
        Log.d(TAG,"Update successed : "+counter);
        if (counter == listSpecialTrans.size()){
            return true;
        }
        return false;
    }

    //tra ve danh sach tat ca transaction
    public ArrayList<Transaction> getAllTransaction(){
        SQLiteDatabase db = getWritableDatabase();
        ArrayList<Transaction> result= new ArrayList<>();
        try {
            String query = "SELECT * FROM "+TABLE_NAME_AGENCY+" WHERE 1";
            Cursor c = db.rawQuery(query,null);
            c.moveToFirst();

            while (!c.isAfterLast()){
                Transaction transaction = new Transaction(
                        c.getInt(c.getColumnIndex(COLUMN_ID)),
                        c.getString(c.getColumnIndex(COLUMN_PHONE)),
                        c.getString(c.getColumnIndex(COLUMN_TRANSACTION_CODE)),
                        c.getInt(c.getColumnIndex(COLUMN_VALUE)),
                        c.getString(c.getColumnIndex(COLUMN_TIME)),
                        c.getString(c.getColumnIndex(COLUMN_UPDATE_TIME)),
                        c.getInt(c.getColumnIndex(COLUMN_STATUS))
                );

                result.add(transaction);
                c.moveToNext();
            }
        }catch (Exception e){
            e.getMessage();
            Toast.makeText(mContext,"Error: getAllTransactiion",Toast.LENGTH_LONG).show();
        }
        return result;
    }

    public ArrayList<Transaction> getSpecialTransaction(Transaction transaction){
        SQLiteDatabase db = getWritableDatabase();
        ArrayList<Transaction> result= new ArrayList<>();
        try {
            String query = "SELECT * FROM "+TABLE_NAME_AGENCY+" WHERE "+
                    COLUMN_PHONE +" = '"+transaction.getPhone()+"' AND "+
                    COLUMN_TRANSACTION_CODE+" = '"+transaction.getCode()+"' AND "+
                    COLUMN_VALUE+" = "+transaction.getValue();
            Cursor c = db.rawQuery(query,null);
            c.moveToFirst();

            while (!c.isAfterLast()){
                Transaction trans = new Transaction(
                        c.getInt(c.getColumnIndex(COLUMN_ID)),
                        c.getString(c.getColumnIndex(COLUMN_PHONE)),
                        c.getString(c.getColumnIndex(COLUMN_TRANSACTION_CODE)),
                        c.getInt(c.getColumnIndex(COLUMN_VALUE)),
                        c.getString(c.getColumnIndex(COLUMN_TIME)),
                        c.getString(c.getColumnIndex(COLUMN_UPDATE_TIME)),
                        c.getInt(c.getColumnIndex(COLUMN_STATUS))
                );

                result.add(trans);
                c.moveToNext();
            }
        }catch (Exception e){
            e.getMessage();
            Toast.makeText(mContext,"Error: getAllTransactiion",Toast.LENGTH_LONG).show();
        }
        return result;
    }
}
