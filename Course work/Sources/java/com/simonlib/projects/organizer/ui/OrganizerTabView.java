package com.simonlib.projects.organizer.ui;

import android.content.Context;
import android.support.annotation.Nullable;
import android.support.v4.view.ViewPager;
import android.util.AttributeSet;
import android.view.View;
import android.widget.FrameLayout;
import android.widget.TextView;

import com.simonlib.projects.organizer.R;
import com.simonlib.projects.organizer.util.OrganizerUtil;

public class OrganizerTabView extends FrameLayout {

    private ViewPager mViewPager;

    private TextView mMonthNameTextView;
    private TextView mYearTextView;
    private int mCurrentMonth;
    private int mCurrentYear;

    public OrganizerTabView(Context context) {
        super(context);
    }

    @Override
    public void onFinishInflate() {
        super.onFinishInflate();

        inflateContent();
    }

    public OrganizerTabView(Context context, @Nullable AttributeSet attrs) {
        super(context, attrs);
    }

    /*public void bind() {
        if (!isHasContent()) {
            inflateContent();
        }
    }*/

    public void synchronizeWithViewPager(ViewPager viewPager) {
        mViewPager = viewPager;

        mViewPager.addOnPageChangeListener(onPageChangeListener);
    }

    private void inflateContent() {
        View rootView = inflate(getContext(), R.layout.organizer_tab_view, null);
        addView(rootView);

        mMonthNameTextView = (TextView) rootView.findViewById(R.id.organizer_tab_month_textview);
        mYearTextView = (TextView) rootView.findViewById(R.id.organizer_tab_year_textview);

        rootView.findViewById(R.id.organizer_tab_previous_button)
                .setOnClickListener(new OnClickListener() {
                    @Override
                    public void onClick(View v) {
                        mViewPager.setCurrentItem(mViewPager.getCurrentItem() - 1, true);
                    }
                });

        rootView.findViewById(R.id.organizer_tab_next_button)
                .setOnClickListener(new OnClickListener() {
                    @Override
                    public void onClick(View v) {
                        mViewPager.setCurrentItem(mViewPager.getCurrentItem() + 1, true);
                    }
                });
    }

    private boolean isHasContent() {
        if (getChildCount() > 0) {
            return true;
        } else {
            return false;
        }
    }

    private void refreshMonthName() {
        mMonthNameTextView.setText(OrganizerUtil.getMonthName(mCurrentMonth));
        mYearTextView.setText(Integer.toString(mCurrentYear));
    }

    ViewPager.OnPageChangeListener onPageChangeListener = new ViewPager.OnPageChangeListener() {
        @Override
        public void onPageScrolled(int position, float positionOffset, int positionOffsetPixels) {
            int shift = OrganizerViewPagerAdapter.getRealShift(position);
            mCurrentMonth = OrganizerUtil.getMonthNumberFromShift(shift);
            mCurrentYear = OrganizerUtil.getYearFromShift(shift);

            /*AnimationSet set = new AnimationSet(false);
            set.addAnimation(new AlphaAnimation(1.0f, 0.0f));
            mMonthNameTextView.setAnimation(set);
            mMonthNameTextView.startAnimation(set);*/

            refreshMonthName();
        }

        @Override
        public void onPageSelected(int position) {
           /* mCurrentMonth = OrganizerUtil.getMonthNumberFromShift(position);
            refreshMonthName();*/
        }

        @Override
        public void onPageScrollStateChanged(int state) {
        }
    };
}
