package com.simonlib.projects.organizer.ui;

import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentStatePagerAdapter;

import com.simonlib.projects.organizer.ui.OrganizerCalendarPage;

public class OrganizerViewPagerAdapter extends FragmentStatePagerAdapter {

    private static final int MAX_MONTH = 48;
    private static final int START_MONTH = MAX_MONTH / 2;

    public OrganizerViewPagerAdapter(FragmentManager fm) {
        super(fm);
    }

    public void setOnOrganizerDayClickListener(OrganizerCalendarPage.OnOrganizerDayClickListener listener) {
        OrganizerCalendarPage.setOnOrganizerDayClickListener(listener);
    }

    @Override
    public Fragment getItem(int position) {
        OrganizerCalendarPage organizerCalendarPage = OrganizerCalendarPage.newInstance(getRealShift(position));
        return organizerCalendarPage;
    }

    @Override
    public int getCount() {
        return MAX_MONTH;
    }

    protected static int getStartPage() {
        return START_MONTH;
    }

    protected static int getRealShift(int currentShift) {
        return currentShift - START_MONTH;
    }
}

