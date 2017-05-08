package com.simonlib.projects.organizer.ui;

import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v4.app.Fragment;
import android.support.v7.widget.GridLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import com.simonlib.projects.organizer.R;
import com.simonlib.projects.organizer.data.OrganizerDate;
import com.simonlib.projects.organizer.database.OrganizerDatabase;
import com.simonlib.projects.organizer.util.OrganizerUtil;

import java.util.List;
import java.util.Set;

public class OrganizerCalendarPage extends Fragment {

    private static final String SHIFT_FROM_CURRENT_MONTH_KEY = "shift_from_current_month_key";

    private OrganizerDate mDate;

    private static OnOrganizerDayClickListener mDayListener;

    public interface OnOrganizerDayClickListener {
        void onDayClicked(OrganizerDate date);
    }

    public OrganizerCalendarPage() {
    }

    public static void setOnOrganizerDayClickListener(OnOrganizerDayClickListener listener) {
        mDayListener = listener;
    }

    public static OrganizerCalendarPage newInstance(int shiftFromCurrentMonth) {
        OrganizerCalendarPage organizerPage = new OrganizerCalendarPage();

        Bundle bundle = new Bundle();
        bundle.putInt(SHIFT_FROM_CURRENT_MONTH_KEY, shiftFromCurrentMonth);
        organizerPage.setArguments(bundle);

        return organizerPage;
    }

    @Override
    public View onCreateView(LayoutInflater inflater, @Nullable ViewGroup container,
                             @Nullable Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.organizer_page_view, null);

        int shiftFromCurrentMonth = 0;
        Bundle bundle = getArguments();
        if (bundle != null) {
            shiftFromCurrentMonth = bundle.getInt(SHIFT_FROM_CURRENT_MONTH_KEY, 0);
        }
        mDate = OrganizerUtil.getOrganizerDateFromShift(shiftFromCurrentMonth);

        final OrganizerCalendarPageAdapter organizerGridAdapter = new OrganizerCalendarPageAdapter(getContext(), mDate);
        organizerGridAdapter.setOnOrganizerDayClickListener(mDayListener);

        final OrganizerDatabase database = new OrganizerDatabase(getContext());
        database.startReadableSession();
        database.getDatesWithEntriesForParticulatMonth(mDate.getMonth(), new OrganizerDatabase.LoadCallback() {
            @Override
            public void onDataLoaded(List data) {
                Set<OrganizerDate> dateSet = OrganizerUtil.getOnlyUniqueDatesFromListOfEntries(data);
                organizerGridAdapter.setNotEmptyDaysSet(dateSet);
                organizerGridAdapter.notifyDataSetChanged();
                database.stopSession();
            }
        });

        RecyclerView organizerGrid = (RecyclerView) view.findViewById(R.id.organizer_page_grid);
        organizerGrid.setLayoutManager(new GridLayoutManager(getContext(), 7));
        organizerGrid.setAdapter(organizerGridAdapter);

        TextView organizerNothingErrorText = (TextView) view.findViewById(R.id.organizer_nothing_error_text);

        return view;
    }
}
