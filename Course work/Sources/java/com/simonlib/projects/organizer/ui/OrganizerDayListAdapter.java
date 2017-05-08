package com.simonlib.projects.organizer.ui;

import android.content.Context;
import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import com.simonlib.projects.organizer.R;
import com.simonlib.projects.organizer.data.OrganizerEntry;

import java.util.ArrayList;
import java.util.List;

public class OrganizerDayListAdapter extends RecyclerView.Adapter<OrganizerDayListAdapter.OrganizerDayListViewHolder> {

    private Context mContext;

    private List<OrganizerEntry> mPrevContent;
    private List<OrganizerEntry> mContent;
    private List<Integer> mSelectedContentIndex;
    private OrganizerDayListViewHolder.OnDayListClickListener mListener;

    public void setOnOrganizerDayClickListener(OrganizerDayListViewHolder.OnDayListClickListener listener) {
        mListener = listener;
    }

    public OrganizerDayListAdapter(Context context) {
        mContext = context;

        mContent = new ArrayList<>();
        mPrevContent = new ArrayList<>();
    }

    @Override
    public OrganizerDayListViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
        LayoutInflater layoutInflater = LayoutInflater.from(parent.getContext());
        View view = layoutInflater.inflate(R.layout.organizer_day_fragment_item, parent, false);

        OrganizerDayListViewHolder holder = new OrganizerDayListViewHolder(mContext, view);
        holder.setOnDayListClickListener(mListener);
        return holder;
    }

    @Override
    public void onBindViewHolder(OrganizerDayListViewHolder holder, int position) {
        OrganizerEntry entry = mContent.get(position);
        holder.bind(entry, isSelected(position));
    }

    @Override
    public int getItemCount() {
        return mContent == null ? 0 : mContent.size();
    }

    public void setOrganizerEntries(List<OrganizerEntry> content) {
        mPrevContent.clear();
        mPrevContent.addAll(mContent);

        mContent.clear();
        mContent.addAll(content);
    }

    public void toggleSelection(int position) {
        if (mSelectedContentIndex == null) {
            mSelectedContentIndex = new ArrayList<>();
        }

        if (isSelected(position)) {
            mSelectedContentIndex.remove((Integer)position);
        } else {
            mSelectedContentIndex.add(position);
        }
        notifyDataSetChanged();
    }

    public int getSelectedItemsCount() {
        return mSelectedContentIndex != null ? mSelectedContentIndex.size() : 0;
    }

    public List<OrganizerEntry> getSelectedEntries() {
        List<OrganizerEntry> selectedContent = new ArrayList<>();
        for (int index : mSelectedContentIndex) {
            selectedContent.add(mContent.get(index));
        }
        return selectedContent;
    }

    public boolean isSelected(int position) {
        if (mSelectedContentIndex != null) {
            for (int index : mSelectedContentIndex) {
                if (index == position) {
                    return true;
                }
            }
        }
        return false;
    }

    public void clearSelection() {
        mSelectedContentIndex.clear();
    }

    public void showDataSet() {
        notifyDataSetChanged();
/*
        if (mPrevContent.size() == 0) {
            return;
        }

        if (mContent.size() == mPrevContent.size() + 1) {
            notifyItemInserted(mContent.size()-1);
        }

        List<OrganizerEntry> prevContent = new ArrayList<>();
        prevContent.addAll(mPrevContent);

        for (int i = 0; i < mContent.size(); i++) {
            OrganizerEntry newEntry = mContent.get(i);
            if (newEntry.equals(prevContent.get(i)) && i < prevContent.size()) {
                prevContent.remove(newEntry);
            }
        }

        for (int i = 0; i < mContent.size(); i++) {
            OrganizerEntry newEntry = mContent.get(i);
            if (!newEntry.equals(prevContent.get(i)) || i >= prevContent.size()) {
                boolean exist = false;
                for (int j = 0; j < mPrevContent.size(); j++) {
                    if (newEntry.equals(mPrevContent.get(j))) {
                        notifyItemMoved(i, j);
                        prevContent.remove(newEntry);
                        i--;
                        exist = true;
                        break;
                    }
                }
                if (!exist) {
                    notifyItemInserted(i);
                }
            }
        }*/
    }


    static class OrganizerDayListViewHolder extends RecyclerView.ViewHolder {

        private Context mContext;

        private View mView;

        private TextView mItemContent;
        private OrganizerEntry mContent;
        private boolean mIsSelected;

        private OnDayListClickListener mListener;

        public interface OnDayListClickListener {
            void onItemListClick(int position);
            void onItemListLongClick(int position);
        }

        public void setOnDayListClickListener(OnDayListClickListener listener) {
            mListener = listener;
        }

        public OrganizerDayListViewHolder(Context context, View itemView) {
            super(itemView);
            mContext = context;
            mView = itemView;

            itemView.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                    if (mListener != null) {
                        mListener.onItemListClick(getLayoutPosition());
                    }
                }
            });
            itemView.setOnLongClickListener(new View.OnLongClickListener() {
                @Override
                public boolean onLongClick(View v) {
                    if (mListener != null) {
                        mListener.onItemListLongClick(getLayoutPosition());
                    }
                    return false;
                }
            });

            mItemContent = (TextView) itemView.findViewById(R.id.organizer_day_fragment_list_item_textview);
        }

        public void bind(OrganizerEntry entry, boolean isSelected) {
            mContent = entry;
            mIsSelected = isSelected;

            if (mIsSelected) {
                mView.setBackgroundColor(mContext.getResources().getColor(R.color.colorPrimaryLight));
            } else {
                mView.setBackgroundColor(mContext.getResources().getColor(R.color.colorPrimaryBackground));
            }

            mItemContent.setText(mContent.getEntry());
        }
    }
}
