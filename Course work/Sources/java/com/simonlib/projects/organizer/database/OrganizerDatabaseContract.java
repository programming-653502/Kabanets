package com.simonlib.projects.organizer.database;

import android.provider.BaseColumns;

public class OrganizerDatabaseContract {

    private OrganizerDatabaseContract() {}

    public static final String DATABASE_NAME = "Organizer.db";

    public static final String SQL_CREATE_TABLE =
            "CREATE TABLE " + OrganizerEntry.TABLE_NAME + " ("
            + OrganizerEntry._ID + " INTEGER PRIMARY KEY, "
            + OrganizerEntry.DATE_COLUMN_NAME + " " + OrganizerEntry.DATE_COLUMN_TYPE + ", "
            + OrganizerEntry.TEXT_COLUMN_NAME + " " + OrganizerEntry.TEXT_COLUMN_TYPE + ")";

    public static final String SQL_DELETE_TABLE =
            "DROP TABLE IF EXISTS " + OrganizerEntry.TABLE_NAME;

    public static class OrganizerEntry implements BaseColumns {
        public static final String TABLE_NAME = "organizer_table";
        public static final String DATE_COLUMN_NAME = "organizer_column_date";
        public static final String DATE_COLUMN_TYPE = "TEXT";
        public static final String TEXT_COLUMN_NAME = "organizer_column_text";
        public static final String TEXT_COLUMN_TYPE = "TEXT";
    }
}
