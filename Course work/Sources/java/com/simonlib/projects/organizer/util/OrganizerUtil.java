package com.simonlib.projects.organizer.util;

import com.simonlib.projects.organizer.data.OrganizerDate;
import com.simonlib.projects.organizer.data.OrganizerEntry;

import java.util.Calendar;
import java.util.GregorianCalendar;
import java.util.HashSet;
import java.util.List;
import java.util.Locale;
import java.util.Set;

import static java.lang.Math.abs;

public class OrganizerUtil {

    public static int getDaysCountInMonth(OrganizerDate date) {
        Calendar calendar = date.toCalendar();
        int daysCountInMonth = calendar.getActualMaximum(Calendar.DAY_OF_MONTH);
        return daysCountInMonth;
    }

    public static OrganizerDate getOrganizerDateFromShift(int shift) {
        Calendar calendar = getCalendarFromShift(shift);
        OrganizerDate date = OrganizerDate.fromCalendar(calendar);
        return date;
    }

    public static int getMonthNumberFromShift(int shift) {
        int currentMonth =  getCalendarFromShift(shift).get(Calendar.MONTH);
        return currentMonth;
    }

    public static int getYearFromShift(int shiftMonth) {
        int currentYear =  getCalendarFromShift(shiftMonth).get(Calendar.YEAR);
        return currentYear;
    }

    public static Calendar getCalendarFromShift(int shiftMonth) {
        Calendar calendar = new GregorianCalendar();
        int currentMonth = calendar.get(Calendar.MONTH);
        calendar.set(Calendar.MONTH, currentMonth + shiftMonth);

        return calendar;
    }

    public static String getMonthName(int month) {
        Calendar calendar = new GregorianCalendar();
        calendar.set(Calendar.MONTH, month);

        return calendar.getDisplayName(Calendar.MONTH,
                Calendar.SHORT, Locale.ENGLISH);
    }

    public static String convertOrganizerDateToDisplayText(final OrganizerDate date) {
        Calendar calendar = date.toCalendar();
        String displayText = calendar.getDisplayName(Calendar.MONTH, Calendar.LONG, Locale.getDefault()) + " " +
                calendar.get(Calendar.DAY_OF_MONTH) + ", " + calendar.get(Calendar.YEAR);
        return displayText;
    }

    public static String convertOrganizerDateToSQLiteDate(final OrganizerDate date) {
        int day = date.getDay();
        int month = date.getMonth();
        int year = date.getYear();

        String monthStr;
        if (month < 10) {
            monthStr = "0"+month;
        } else {
            monthStr = ""+month;
        }

        String dayStr;
        if (day < 10) {
            dayStr = "0"+day;
        } else {
            dayStr = ""+day;
        }

        String dbString = year + "-" + monthStr + "-" + dayStr;
        return dbString;
    }

    public static Set<OrganizerDate> getOnlyUniqueDatesFromListOfEntries(List<OrganizerEntry> entries) {
        Set<OrganizerDate> datesSet = new HashSet<>();
        for (OrganizerEntry entry : entries) {
            datesSet.add(entry.getDate());
        }
        return datesSet;
    }
}
