package com.simonlib.projects.organizer.ui;

import android.content.Context;
import android.graphics.Color;
import android.view.View;
import android.widget.FrameLayout;
import android.widget.LinearLayout;
import android.widget.TextView;

import com.simonlib.projects.organizer.R;

public class OrganizerCalendarPageItem extends FrameLayout {

    private int mDay = 0;
    private boolean mIsEmptyDay;

    public OrganizerCalendarPageItem(Context context) {
        super(context);
    }

    public void bindStub() {
        TextView dayTextView = (TextView) findViewById(R.id.organizer_page_item_day);
        if (dayTextView != null)
            dayTextView.setText("");
    }

    public void bind(int day, boolean isEmptyDay) {
        mDay = day;
        mIsEmptyDay = isEmptyDay;

        if (!isHasContent()) {
            inflateContent();
        }

        TextView dayTextView = (TextView) findViewById(R.id.organizer_page_item_day);
        if (dayTextView != null) {
            dayTextView.setText("" + day);
            if (!mIsEmptyDay)
                dayTextView.setTextColor(Color.RED);
        }
    }

    private View inflateContent() {
        View rootView = inflate(getContext(), R.layout.organizer_page_item, null);
        addView(rootView);
        return rootView;
    }

    private boolean isHasContent() {
        if (getChildCount() > 0) {
            return true;
        } else {
            return false;
        }
    }
}
