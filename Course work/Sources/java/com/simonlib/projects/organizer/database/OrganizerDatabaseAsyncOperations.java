package com.simonlib.projects.organizer.database;

import android.content.ContentValues;
import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.os.AsyncTask;
import android.os.Bundle;
import android.support.v4.app.LoaderManager;
import android.support.v4.content.Loader;

import java.util.List;

public class OrganizerDatabaseAsyncOperations {

    private static final int ORGANIZER_BASE_LOADER = 1;

    private Context mContext;

    private SQLiteDatabase mDatabase;

    public static final String PROJECTION_ARGS_KEY = "projection";
    public static final String SELECTION_ARGS_KEY = "selection";
    public static final String SELECTIONARGS_ARGS_KEY = "selection_args";
    public static final String GROUPBY_ARGS_KEY = "group_by";
    public static final String HAVING_ARGS_KEY = "having";
    public static final String ORDERBY_ARGS_KEY = "order_by";

    public OrganizerDatabaseAsyncOperations(Context context, SQLiteDatabase database) {
        mContext = context;
        mDatabase = database;
    }

    public void putEntryInDatabase(ContentValues contentValues, OrganizerDatabase.InsertCallback callback) {
        new PutToDatabaseTask(callback, contentValues).execute();
    }

    public void deleteEntriesFromDatabase(List<Bundle> bundles, OrganizerDatabase.DeleteCallback callback) {
        new DeleteFromDatabaseTask(callback, bundles).execute();
    }

    public void updateEntryInDatabase(ContentValues values, Bundle bundle, OrganizerDatabase.UpdateCallback callback) {
        new UpdateInDatabaseTask(callback, values, bundle).execute();
    }

    protected void startStandAloneLoader(OrganizerDatabase.LoadCallback callback, Bundle bundleForLoader) {
        DatabaseLoaderCallback loaderCallback = new DatabaseLoaderCallback(callback);
        OrganizerDatabaseLoader loader = (OrganizerDatabaseLoader) loaderCallback.onCreateLoader(ORGANIZER_BASE_LOADER, bundleForLoader);
        loader.registerListener(ORGANIZER_BASE_LOADER, loaderCallback);
        loader.setItsBindedToUI(false);
        loader.forceLoad();
    }

    protected Loader startBindedToUILoader(LoaderManager loaderManager, OrganizerDatabase.LoadCallback callback, Bundle bundleForLoader) {
        return loaderManager.initLoader(ORGANIZER_BASE_LOADER, bundleForLoader, new DatabaseLoaderCallback(callback));
    }

    private class DatabaseLoaderCallback implements LoaderManager.LoaderCallbacks<List>,
            Loader.OnLoadCompleteListener<List> {

        private OrganizerDatabase.LoadCallback mExternalCallback;

        public DatabaseLoaderCallback(OrganizerDatabase.LoadCallback externalCallback) {
            mExternalCallback = externalCallback;
        }

        @Override
        public Loader<List> onCreateLoader(int id, Bundle args) {

            OrganizerDatabaseLoader loader = null;

            String table = OrganizerDatabaseContract.OrganizerEntry.TABLE_NAME;
            String[] projection = args.getStringArray(PROJECTION_ARGS_KEY);
            String selection = args.getString(SELECTION_ARGS_KEY);
            String[] selectionArgs = args.getStringArray(SELECTIONARGS_ARGS_KEY);
            String groupBy = args.getString(GROUPBY_ARGS_KEY);
            String having = args.getString(HAVING_ARGS_KEY);
            String orderBy = args.getString(ORDERBY_ARGS_KEY);

            switch (id) {
                case ORGANIZER_BASE_LOADER:
                    loader = new OrganizerDatabaseLoader(mContext, mDatabase, table, projection, selection,
                            selectionArgs, groupBy, having, orderBy);
                    loader.setItsBindedToUI(true);
                    break;
            }

            return loader;
        }

        @Override
        public void onLoadFinished(Loader<List> loader, List data) {
            switch (loader.getId()) {
                case ORGANIZER_BASE_LOADER:
                    mExternalCallback.onDataLoaded(data);
                    break;
            }
        }

        @Override
        public void onLoaderReset(Loader<List> loader) {
            switch (loader.getId()) {
                case ORGANIZER_BASE_LOADER:
                    mExternalCallback.onDataLoaded(null);
                    break;
            }
        }

        @Override
        public void onLoadComplete(Loader<List> loader, List data) {
            onLoadFinished(loader, data);
        }
    }

    private class PutToDatabaseTask extends AsyncTask<Void, Void, Long> {

        private ContentValues mValues;

        private OrganizerDatabase.InsertCallback mCallback;

        public PutToDatabaseTask(OrganizerDatabase.InsertCallback callback, ContentValues values) {
            mValues = values;
            mCallback = callback;
        }

        @Override
        protected Long doInBackground(Void... params) {
            long rowId = mDatabase.insert(OrganizerDatabaseContract.OrganizerEntry.TABLE_NAME,
                    null, mValues);
            return rowId;
        }

        @Override
        protected void onPostExecute(Long result) {
            if (mCallback != null) {
                if (result != -1) {
                    mCallback.onDataInserted(true);
                } else {
                    mCallback.onDataInserted(false);
                }
            }
        }
    }

    private class DeleteFromDatabaseTask extends AsyncTask<Void, Void, Boolean> {

        private List<Bundle> mBundls;

        private OrganizerDatabase.DeleteCallback mCallback;

        public DeleteFromDatabaseTask(OrganizerDatabase.DeleteCallback callback, List<Bundle> bundls) {
            mBundls = bundls;
            mCallback = callback;
        }

        @Override
        protected Boolean doInBackground(Void... params) {
            boolean success = true;
            for (Bundle bundle : mBundls) {
                int result = mDatabase.delete(OrganizerDatabaseContract.OrganizerEntry.TABLE_NAME,
                        bundle.getString(SELECTION_ARGS_KEY), bundle.getStringArray(SELECTIONARGS_ARGS_KEY));
                if (result == 0) {
                    success = false;
                    break;
                }
            }
            return success;
        }

        @Override
        protected void onPostExecute(Boolean result) {
            if (mCallback != null) {
                mCallback.onDataDeleted(result);
            }
        }
    }

    private class UpdateInDatabaseTask extends AsyncTask<Void, Void, Boolean> {

        private ContentValues mValues;
        private Bundle mBundle;

        private OrganizerDatabase.UpdateCallback mCallback;

        public UpdateInDatabaseTask(OrganizerDatabase.UpdateCallback callback, ContentValues values, Bundle bundle) {
            mValues = values;
            mBundle = bundle;
            mCallback = callback;
        }

        @Override
        protected Boolean doInBackground(Void... params) {
            boolean success = true;
            int result = mDatabase.update(OrganizerDatabaseContract.OrganizerEntry.TABLE_NAME,
                    mValues, mBundle.getString(SELECTION_ARGS_KEY), mBundle.getStringArray(SELECTIONARGS_ARGS_KEY));
            if (result == 0) {
                success = false;
            }
            return success;
        }

        @Override
        protected void onPostExecute(Boolean result) {
            if (mCallback != null) {
                mCallback.onDataUpdated(result);
            }
        }
    }
}
