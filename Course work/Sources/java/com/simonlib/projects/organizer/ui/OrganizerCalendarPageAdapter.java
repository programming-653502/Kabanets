package com.simonlib.projects.organizer.ui;

import android.content.Context;
import android.support.v7.widget.RecyclerView;
import android.view.View;
import android.view.ViewGroup;

import com.simonlib.projects.organizer.data.OrganizerDate;
import com.simonlib.projects.organizer.util.OrganizerUtil;

import java.util.Calendar;
import java.util.Set;

public class OrganizerCalendarPageAdapter extends RecyclerView.Adapter<OrganizerCalendarPageAdapter.OrganizerDayListViewHolder> {
    private Context mContext;

    private OrganizerDate mDate;
    protected int mDaysCount;
    private int mFirstDayPosInWeek;
    private Set<OrganizerDate> mNotEmptyDaysSet;

    private OrganizerCalendarPage.OnOrganizerDayClickListener mListener;

    public OrganizerCalendarPageAdapter(Context context, OrganizerDate date) {
        mContext = context;

        mDaysCount = OrganizerUtil.getDaysCountInMonth(date);
        mDate = date;
        Calendar calendar = date.toCalendar();
        calendar.set(Calendar.DAY_OF_MONTH, 1);
        mFirstDayPosInWeek = calendar.get(Calendar.DAY_OF_WEEK) - 1;
        if (mFirstDayPosInWeek == 0) {
            mFirstDayPosInWeek = 7;
        }
    }

    public void setOnOrganizerDayClickListener(OrganizerCalendarPage.OnOrganizerDayClickListener listener) {
        mListener = listener;
    }

    public void setNotEmptyDaysSet(Set<OrganizerDate> notEmptyDaysSet) {
        mNotEmptyDaysSet = notEmptyDaysSet;
    }

    public Set<OrganizerDate> getNotEmptyDaysSet() {
        return mNotEmptyDaysSet;
    }

    @Override
    public OrganizerCalendarPageAdapter.OrganizerDayListViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
        OrganizerCalendarPageItem item = new OrganizerCalendarPageItem(mContext);
        OrganizerCalendarPageAdapter.OrganizerDayListViewHolder holder = new OrganizerCalendarPageAdapter.OrganizerDayListViewHolder(item);

        return holder;
    }

    @Override
    public void onBindViewHolder(OrganizerCalendarPageAdapter.OrganizerDayListViewHolder holder, int position) {
        final int dayOfItem = (position + 2) - mFirstDayPosInWeek;

        if (dayOfItem < 1) {
            holder.bindStub();
            return;
        }

        boolean f = findDayInDatesSet(dayOfItem);
        holder.bind(dayOfItem, !f);

        holder.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                mDate.setDay(dayOfItem);
                mListener.onDayClicked(mDate);
            }
        });
    }

    @Override
    public long getItemId(int position) {
        return 0;
    }

    @Override
    public int getItemCount() {
        return mDaysCount+mFirstDayPosInWeek-1;
    }

    private boolean findDayInDatesSet(int day) {
        if (mNotEmptyDaysSet != null) {
            for (OrganizerDate date : mNotEmptyDaysSet) {
                int d = date.getDay();
                if (d == day) {
                    return true;
                }
            }
        }
        return false;
    }

    class OrganizerDayListViewHolder extends RecyclerView.ViewHolder {

        private OrganizerCalendarPageItem mItemView;

        public OrganizerDayListViewHolder(OrganizerCalendarPageItem itemView) {
            super(itemView);
            mItemView = itemView;
        }

        public void bindStub() {
            mItemView.bindStub();
        }

        public void bind(int day, boolean isEmpty) {
            mItemView.bind(day, isEmpty);
        }

        public void setOnClickListener(View.OnClickListener onClickListener) {
            mItemView.setOnClickListener(onClickListener);
        }
    }
}
