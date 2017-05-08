package com.simonlib.projects.organizer.data;

import android.os.Parcel;
import android.os.Parcelable;

import java.util.Calendar;
import java.util.GregorianCalendar;

public class OrganizerDate implements Parcelable {

    private int mDay;
    private int mMonth;
    private int mYear;

    public int getDay() {
        return mDay;
    }

    public void setDay(int day) {
        mDay = day;
    }

    public int getMonth() {
        return mMonth;
    }

    public void setMonth(int month) {
        mMonth = month;
    }

    public int getYear() {
        return mYear;
    }

    public void setYear(int year) {
        mYear = year;
    }

    public static OrganizerDate parseSQLiteString(final String source) throws NumberFormatException {
        String yearStr = source.substring(0,4);
        String monthStr = source.substring(5,7);
        String dayStr = source.substring(8,10);

        int year = Integer.parseInt(yearStr);
        int month = Integer.parseInt(monthStr);
        int day = Integer.parseInt(dayStr);

        OrganizerDate date = new OrganizerDate();
        date.setDay(day);
        date.setMonth(month);
        date.setYear(year);

        return date;
    }

    public static OrganizerDate fromCalendar(final Calendar calendar) {
        OrganizerDate date = new OrganizerDate();
        date.setDay(calendar.get(Calendar.DAY_OF_MONTH));
        date.setMonth(calendar.get(Calendar.MONTH));
        date.setYear(calendar.get(Calendar.YEAR));
        return date;
    }

    public Calendar toCalendar() {
        Calendar calendar = new GregorianCalendar();
        calendar.set(Calendar.DAY_OF_MONTH, mDay);
        calendar.set(Calendar.MONTH, mMonth);
        calendar.set(Calendar.YEAR, mYear);

        return calendar;
    }

    @Override
    public boolean equals(Object object) {
        if (object instanceof OrganizerDate) {
            if (toString().equals(object.toString())) {
                return true;
            }
        }

        return false;
    }

    @Override
    public String toString() {
        return mDay + " " + mMonth + " " + mYear;
    }

    @Override
    public void writeToParcel(Parcel dest, int flags) {
        dest.writeInt(mDay);
        dest.writeInt(mMonth);
        dest.writeInt(mYear);
    }

    @Override
    public int describeContents() {
        return 0;
    }

    public static final Creator<OrganizerDate> CREATOR = new Creator<OrganizerDate>() {
        @Override
        public OrganizerDate createFromParcel(Parcel in) {
            OrganizerDate date = new OrganizerDate();
            date.setDay(in.readInt());
            date.setMonth(in.readInt());
            date.setYear(in.readInt());
            return date;
        }

        @Override
        public OrganizerDate[] newArray(int size) {
            return new OrganizerDate[size];
        }
    };
}
