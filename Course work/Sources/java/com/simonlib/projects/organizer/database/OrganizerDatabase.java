package com.simonlib.projects.organizer.database;

import android.content.ContentValues;
import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v4.app.LoaderManager;
import android.support.v4.content.Loader;

import com.simonlib.projects.organizer.data.OrganizerEntry;
import com.simonlib.projects.organizer.util.OrganizerUtil;


import java.util.ArrayList;
import java.util.List;

public class OrganizerDatabase {

    private Context mContext;

    private static SQLiteDatabase mDatabase;

    private static int mCountOfOpenConnections = 0;

    public interface LoadCallback {
        void onDataLoaded(List data);
    }

    public interface InsertCallback {
        void onDataInserted(boolean success);
    }

    public interface DeleteCallback {
        void onDataDeleted(boolean success);
    }

    public interface UpdateCallback {
        void onDataUpdated(boolean success);
    }

    public OrganizerDatabase(Context context) {
        mContext = context;
    }

    public void startReadableSession() {
        mCountOfOpenConnections++;

        if (mDatabase == null || !mDatabase.isReadOnly()) {
            OrganizerDatabaseHelper databaseHelper = new OrganizerDatabaseHelper(mContext);
            mDatabase = databaseHelper.getReadableDatabase();
        }
    }

    public void startWritableSession() {
        mCountOfOpenConnections++;

        if (mDatabase == null || mDatabase.isReadOnly()) {
            OrganizerDatabaseHelper databaseHelper = new OrganizerDatabaseHelper(mContext);
            mDatabase = databaseHelper.getWritableDatabase();
        }
    }

    public void stopSession() {
        mCountOfOpenConnections--;

        if (mCountOfOpenConnections < 0) {
            mCountOfOpenConnections = 0;
        }

        if (mCountOfOpenConnections == 0) {
            if (mDatabase != null) {
                mDatabase.close();
                mDatabase = null;
            }
        }
    }

    public void putEntryInDatabase(OrganizerEntry entry, @Nullable InsertCallback callback) {
        String sqlDate = OrganizerUtil.convertOrganizerDateToSQLiteDate(entry.getDate());

        ContentValues contentValues = new ContentValues();
        contentValues.put(OrganizerDatabaseContract.OrganizerEntry.DATE_COLUMN_NAME, sqlDate);
        contentValues.put(OrganizerDatabaseContract.OrganizerEntry.TEXT_COLUMN_NAME, entry.getEntry());

        new OrganizerDatabaseAsyncOperations(mContext, mDatabase).putEntryInDatabase(contentValues, callback);
    }

    public void deleteEntriesFromDatabase(List<OrganizerEntry> entries, @Nullable DeleteCallback callback) {
        List<Bundle> bundles = new ArrayList<>();
        for (OrganizerEntry entry : entries) {
            String sqlDate = OrganizerUtil.convertOrganizerDateToSQLiteDate(entry.getDate());

            Bundle bundle = new Bundle();
            bundle.putString(OrganizerDatabaseAsyncOperations.SELECTION_ARGS_KEY,
                    OrganizerDatabaseContract.OrganizerEntry.DATE_COLUMN_NAME + "=?"
                + " AND " + OrganizerDatabaseContract.OrganizerEntry.TEXT_COLUMN_NAME + "=?");
            bundle.putStringArray(OrganizerDatabaseAsyncOperations.SELECTIONARGS_ARGS_KEY,
                    new String[] {sqlDate, entry.getEntry()});

            bundles.add(bundle);
        }

        new OrganizerDatabaseAsyncOperations(mContext, mDatabase).deleteEntriesFromDatabase(bundles, callback);
    }

    public void updateEntryInDatabase(OrganizerEntry newEntry, OrganizerEntry oldEntry, UpdateCallback callback) {
        String sqlNewDate = OrganizerUtil.convertOrganizerDateToSQLiteDate(newEntry.getDate());
        String sqlOldDate = OrganizerUtil.convertOrganizerDateToSQLiteDate(oldEntry.getDate());

        ContentValues contentValues = new ContentValues();
        contentValues.put(OrganizerDatabaseContract.OrganizerEntry.DATE_COLUMN_NAME, sqlNewDate);
        contentValues.put(OrganizerDatabaseContract.OrganizerEntry.TEXT_COLUMN_NAME, newEntry.getEntry());

        Bundle bundle = new Bundle();
        bundle.putString(OrganizerDatabaseAsyncOperations.SELECTION_ARGS_KEY,
                OrganizerDatabaseContract.OrganizerEntry.DATE_COLUMN_NAME + "=?"
                        + " AND " + OrganizerDatabaseContract.OrganizerEntry.TEXT_COLUMN_NAME + "=?");
        bundle.putStringArray(OrganizerDatabaseAsyncOperations.SELECTIONARGS_ARGS_KEY,
                new String[] {sqlOldDate, oldEntry.getEntry()});

        new OrganizerDatabaseAsyncOperations(mContext, mDatabase).updateEntryInDatabase(contentValues, bundle, callback);
    }

    public Loader registerLoaderForOrganizerDayFragment(LoaderManager loaderManager,
                                                        LoadCallback callback, String date) {
        Bundle bundleForLoader = new Bundle();
        bundleForLoader.putString(OrganizerDatabaseAsyncOperations.SELECTION_ARGS_KEY,
                OrganizerDatabaseContract.OrganizerEntry.DATE_COLUMN_NAME + "=?");
        bundleForLoader.putStringArray(OrganizerDatabaseAsyncOperations.SELECTIONARGS_ARGS_KEY,
                new String[] {date});

        return new OrganizerDatabaseAsyncOperations(mContext, mDatabase).startBindedToUILoader(loaderManager, callback, bundleForLoader);
    }

    public void getEntryFromDatabaseByDate(LoadCallback callback, String date) {
        Bundle bundleForLoader = new Bundle();
        bundleForLoader.putString(OrganizerDatabaseAsyncOperations.SELECTION_ARGS_KEY, OrganizerDatabaseContract.OrganizerEntry.DATE_COLUMN_NAME + "=?");
        bundleForLoader.putStringArray(OrganizerDatabaseAsyncOperations.SELECTIONARGS_ARGS_KEY, new String[] {date});

        new OrganizerDatabaseAsyncOperations(mContext, mDatabase).startStandAloneLoader(callback, bundleForLoader);
    }

    public void getDatesWithEntries(LoadCallback callback) {
        Bundle bundleForLoader = new Bundle();
        bundleForLoader.putStringArray(OrganizerDatabaseAsyncOperations.PROJECTION_ARGS_KEY,
                new String[] {OrganizerDatabaseContract.OrganizerEntry.DATE_COLUMN_NAME});

        new OrganizerDatabaseAsyncOperations(mContext, mDatabase).startStandAloneLoader(callback, bundleForLoader);
    }

    public void getDatesWithEntriesForParticulatMonth(int month, LoadCallback callback) {
        String monthStr;
        if (month < 10) {
            monthStr = "0"+month;
        } else {
            monthStr = ""+month;
        }

        Bundle bundleForLoader = new Bundle();
        bundleForLoader.putStringArray(OrganizerDatabaseAsyncOperations.PROJECTION_ARGS_KEY,
                new String[] {OrganizerDatabaseContract.OrganizerEntry.DATE_COLUMN_NAME});
        bundleForLoader.putString(OrganizerDatabaseAsyncOperations.SELECTION_ARGS_KEY,
                "strftime('%m', " + OrganizerDatabaseContract.OrganizerEntry.DATE_COLUMN_NAME + ") = ?");
        bundleForLoader.putStringArray(OrganizerDatabaseAsyncOperations.SELECTIONARGS_ARGS_KEY,
                new String[] {monthStr});

        new OrganizerDatabaseAsyncOperations(mContext, mDatabase).startStandAloneLoader(callback, bundleForLoader);
    }

}
