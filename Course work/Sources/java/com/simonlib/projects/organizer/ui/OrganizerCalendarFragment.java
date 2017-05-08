package com.simonlib.projects.organizer.ui;

import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v4.app.Fragment;
import android.support.v4.view.ViewPager;
import android.support.v7.app.ActionBar;
import android.support.v7.app.AppCompatActivity;
import android.view.LayoutInflater;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;

import com.simonlib.projects.organizer.ui.OrganizerActivity;
import com.simonlib.projects.organizer.ui.OrganizerCalendarPage;
import com.simonlib.projects.organizer.ui.OrganizerTabView;
import com.simonlib.projects.organizer.ui.OrganizerViewPagerAdapter;
import com.simonlib.projects.organizer.R;
import com.simonlib.projects.organizer.data.OrganizerDate;

public class OrganizerCalendarFragment extends Fragment implements OrganizerCalendarPage.OnOrganizerDayClickListener {

    public static final String ORGANIZER_CALENDAR_FRAGMENT_TAG = "com.simonlib.projects.taskmanager.organizer.ui.OrganizerCalendarFragment";

    public OrganizerCalendarFragment() {

    }

    public static OrganizerCalendarFragment newInstance() {
        OrganizerCalendarFragment organizerCalendarFragment = new OrganizerCalendarFragment();

        return organizerCalendarFragment;
    }

    @Override
    public View onCreateView(LayoutInflater inflater, @Nullable ViewGroup container,
                             @Nullable Bundle savedInstanceState) {
        View root = inflater.inflate(R.layout.organizer_calendar_fragment, null);

        OrganizerViewPagerAdapter organizerViewPagerAdapter = new OrganizerViewPagerAdapter(getFragmentManager());
        organizerViewPagerAdapter.setOnOrganizerDayClickListener(this);

        ViewPager organizerViewPager = (ViewPager) root.findViewById(R.id.organizer_view_pager);
        organizerViewPager.setAdapter(organizerViewPagerAdapter);
        organizerViewPager.setCurrentItem(OrganizerViewPagerAdapter.getStartPage());

        OrganizerTabView organizerTabView = (OrganizerTabView) root.findViewById(R.id.organizer_tab_view);
        organizerTabView.synchronizeWithViewPager(organizerViewPager);

        return root;
    }

    @Override
    public void onResume() {
        super.onResume();
        updateToolbar();
    }

    protected void updateToolbar() {
        ActionBar actionBar = ((AppCompatActivity)getActivity()).getSupportActionBar();
        if (actionBar != null) {
            actionBar.setDisplayShowTitleEnabled(true);
            actionBar.setDisplayHomeAsUpEnabled(false);

            actionBar.setTitle(getString(R.string.app_name));
        }
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch(item.getItemId()) {
            case android.R.id.home:
                ((OrganizerActivity)getActivity()).closeOrganizerDayFragment();
                break;
        }

        return false;
    }

    @Override
    public void onDayClicked(OrganizerDate date) {
        ((OrganizerActivity) getActivity()).showOrganizerDayFragment(date);
    }
}
