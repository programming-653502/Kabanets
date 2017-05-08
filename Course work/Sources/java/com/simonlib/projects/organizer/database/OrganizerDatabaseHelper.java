package com.simonlib.projects.organizer.database;

import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

public class OrganizerDatabaseHelper extends SQLiteOpenHelper {

    private static final int DATABASE_VERSION = 1;

    public OrganizerDatabaseHelper(Context context) {
        super(context, OrganizerDatabaseContract.DATABASE_NAME, null, DATABASE_VERSION);
    }

    @Override
    public void onCreate(SQLiteDatabase db) {
        db.execSQL(OrganizerDatabaseContract.SQL_CREATE_TABLE);
    }

    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
        db.execSQL(OrganizerDatabaseContract.SQL_DELETE_TABLE);
        onCreate(db);
    }
}
