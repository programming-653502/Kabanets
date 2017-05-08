package com.simonlib.projects.organizer.database;

import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.support.v4.content.AsyncTaskLoader;

import com.simonlib.projects.organizer.data.OrganizerDate;
import com.simonlib.projects.organizer.data.OrganizerEntry;

import java.util.ArrayList;
import java.util.List;

public class OrganizerDatabaseLoader extends AsyncTaskLoader<List> {

//    private final ForceLoadContentObserver mObserver;

    private boolean mBindedToUI;

    private List<OrganizerEntry> mData;

    private SQLiteDatabase mDatabase;

    private String mTable;
    private String[] mProjection;
    private String mSelection;
    private String[] mSelectionArgs;
    private String mGroupBy;
    private String mHaving;
    private String mOrderBy;

    public OrganizerDatabaseLoader(Context context, SQLiteDatabase database,
                                   String table, String[] projection, String selection,
                                   String[] selectionArgs, String groupBy, String having,
                                   String orderBy) {
        super(context);

//        mObserver = new ForceLoadContentObserver();

        mDatabase = database;

        mTable = table;
        mProjection = projection;
        mSelection = selection;
        mSelectionArgs = selectionArgs;
        mGroupBy = groupBy;
        mHaving = having;
        mOrderBy = orderBy;
    }

    @Override
    public List<OrganizerEntry> loadInBackground() {
        List<OrganizerEntry> organizerEntryList = new ArrayList<>();

        Cursor cursor = mDatabase.query(mTable, mProjection, mSelection,
                mSelectionArgs, mGroupBy, mHaving, mOrderBy);

        // TODO: check this
        if (isLoadInBackgroundCanceled()) {
            return null;
        }

        if (cursor != null) {
            /*try {
                // Ensure the cursor window is filled.
                cursor.getCount();
                cursor.registerContentObserver(mObserver);
            } catch (RuntimeException ex) {
                cursor.close();
                throw ex;
            }*/

            if (cursor.moveToFirst()) {
                int textColumnIndex = cursor.getColumnIndex(OrganizerDatabaseContract.OrganizerEntry.TEXT_COLUMN_NAME);
                int dateColumnIndex = cursor.getColumnIndex(OrganizerDatabaseContract.OrganizerEntry.DATE_COLUMN_NAME);

                do {
                    // TODO: check this
                    if (isLoadInBackgroundCanceled()) {
                        return null;
                    }

                    OrganizerEntry organizerEntry = new OrganizerEntry();

                    if (textColumnIndex != -1) {
                        String text = cursor.getString(textColumnIndex);
                        organizerEntry.setEntry(text);
                    } else {
                        organizerEntry.setEntry("");
                    }

                    if (dateColumnIndex != -1) {
                        String date = cursor.getString(dateColumnIndex);
                        organizerEntry.setDate(OrganizerDate.parseSQLiteString(date));
                    } else {
                        organizerEntry.setDate(null);
                    }

                    organizerEntryList.add(organizerEntry);
                } while(cursor.moveToNext());
            }
        }

        return organizerEntryList;
    }

    @Override
    public void cancelLoadInBackground() {
        super.cancelLoadInBackground();
    }

    @Override
    public void deliverResult(List data) {
        if (mBindedToUI) {
            if (isReset()) {
                mData = null;
                return;
            }

            mData = data;

            if (isStarted()) {
                super.deliverResult(data);
            }
        } else {
            mData = data;
            super.deliverResult(data);
        }
    }

    @Override
    protected void onStartLoading() {
        if (mData != null) {
            deliverResult(mData);
        }
        if (takeContentChanged() || mData == null) {
            forceLoad();
        }
    }

    @Override
    protected void onStopLoading() {
        cancelLoad();
    }

    @Override
    public void onCanceled(List data) {
    }

    @Override
    protected void onReset() {
        super.onReset();

        // Ensure the loader is stopped
        onStopLoading();

        mData = null;
    }

    public void setItsBindedToUI(boolean bindedToUI) {
        mBindedToUI = bindedToUI;
    }

    public boolean isBindedToUI() {
        return mBindedToUI;
    }
}
