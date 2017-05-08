package com.simonlib.projects.organizer.ui;

import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentTransaction;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;

import com.simonlib.projects.organizer.R;
import com.simonlib.projects.organizer.R;
import com.simonlib.projects.organizer.data.OrganizerDate;
import com.simonlib.projects.organizer.ui.OrganizerCalendarFragment;

public class OrganizerActivity extends AppCompatActivity {

    private boolean mIsOrganizerCalendarFragmentOpen;
    private boolean mIsOrganizerDayFragmentOpen;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.organizer_activity);

        Toolbar toolbar = (Toolbar) findViewById(R.id.organizer_toolbar);
        setSupportActionBar(toolbar);

        resolveAreFragmentsOpened();
        showOrganizerCalendarFragment();
    }

    protected boolean isOrganizerDayFragmentOpen() {
        return mIsOrganizerDayFragmentOpen;
    }

    protected boolean isOrganizerCalendarFragmentOpen() {
        return mIsOrganizerCalendarFragmentOpen;
    }

    protected void showOrganizerDayFragment(OrganizerDate date) {
        if (!mIsOrganizerDayFragmentOpen) {
            FragmentManager fragmentManager = getSupportFragmentManager();
            FragmentTransaction transaction = fragmentManager.beginTransaction();
            transaction.replace(R.id.organizer_activity_content, OrganizerDayFragment.newInstance(date),
                    OrganizerDayFragment.ORGANIZER_DAY_FRAGMENT_TAG);
            transaction.commit();

            mIsOrganizerDayFragmentOpen = true;
            mIsOrganizerCalendarFragmentOpen = false;
        }
    }

    protected boolean closeOrganizerDayFragment() {
        if (isOrganizerDayFragmentOpen()) {
            FragmentManager fragmentManager = getSupportFragmentManager();
            Fragment organizerDayFragment = fragmentManager.findFragmentByTag(OrganizerDayFragment.ORGANIZER_DAY_FRAGMENT_TAG);
            FragmentTransaction transaction = fragmentManager.beginTransaction();
            transaction.remove(organizerDayFragment);

            transaction.commit();

            mIsOrganizerDayFragmentOpen = false;

            showOrganizerCalendarFragment();

            /*OrganizerCalendarFragment organizerCalendarFragment =
                    (OrganizerCalendarFragment) fragmentManager.findFragmentByTag(OrganizerCalendarFragment.ORGANIZER_CALENDAR_FRAGMENT_TAG);
            organizerCalendarFragment.updateToolbar();*/

            return true;
        }

        return false;
    }

    protected void showOrganizerCalendarFragment() {
        if (!mIsOrganizerCalendarFragmentOpen && !mIsOrganizerDayFragmentOpen) {
            FragmentManager fragmentManager = getSupportFragmentManager();
            FragmentTransaction transaction = fragmentManager.beginTransaction();
            transaction.add(R.id.organizer_activity_content, OrganizerCalendarFragment.newInstance(),
                    OrganizerCalendarFragment.ORGANIZER_CALENDAR_FRAGMENT_TAG);
            transaction.commit();

            mIsOrganizerCalendarFragmentOpen = true;
        }
    }

    private void resolveAreFragmentsOpened() {
        FragmentManager fragmentManager = getSupportFragmentManager();
        Fragment organizerCalendarFragment = fragmentManager.findFragmentByTag(OrganizerCalendarFragment.ORGANIZER_CALENDAR_FRAGMENT_TAG);
        mIsOrganizerCalendarFragmentOpen = !(organizerCalendarFragment == null);

        Fragment organizerDayFragment = fragmentManager.findFragmentByTag(OrganizerDayFragment.ORGANIZER_DAY_FRAGMENT_TAG);
        mIsOrganizerDayFragmentOpen = !(organizerDayFragment == null);
    }

    @Override
    public void onBackPressed() {
        //getSupportFragmentManager().popBackStack();
        boolean fragmentClosed = closeOrganizerDayFragment();
        if (!fragmentClosed) {
            onBackPressed();
        }
    }
}