package com.simonlib.projects.organizer.ui;

import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v4.app.Fragment;
import android.support.v7.app.ActionBar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.view.ActionMode;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import com.simonlib.projects.organizer.R;
import com.simonlib.projects.organizer.data.OrganizerDate;
import com.simonlib.projects.organizer.data.OrganizerEntry;
import com.simonlib.projects.organizer.database.OrganizerDatabase;
import com.simonlib.projects.organizer.util.OrganizerUtil;
import com.simonlib.projects.organizer.ui.OrganizerDayListAdapter.OrganizerDayListViewHolder;

import java.util.ArrayList;
import java.util.List;

public class OrganizerDayFragment extends Fragment implements OrganizerDayListViewHolder.OnDayListClickListener {

    public static final String ORGANIZER_DAY_FRAGMENT_TAG = "com.simonlib.projects.taskmanager.organizer.OrganizerDayFragment";

    private static final String DATE_KEY = "date_key";

    private RecyclerView mEntryListView;
    private EditText mEntryEditView;
    private TextView mNothingToShowView;
    private Button mSubmitButton;

    private ActionMode mActionMode;
    private OrganizerActionModeCallback mActionModeCallback;

    private OrganizerDayListAdapter mAdapter;

    private List<OrganizerEntry> mContentEntries = new ArrayList<>();

    private OrganizerDate mDate;

    public static OrganizerDayFragment newInstance(OrganizerDate date) {
        OrganizerDayFragment organizerDayFragment = new OrganizerDayFragment();
        Bundle bundle = new Bundle();
        bundle.putParcelable(DATE_KEY, date);
        organizerDayFragment.setArguments(bundle);

        return organizerDayFragment;
    }

    @Override
    public void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setHasOptionsMenu(true);
    }

    private boolean mUpdateMode = false;
    private OrganizerEntry mEntryToUpdate;

    private View.OnClickListener submitOnClickListener = new View.OnClickListener() {
        @Override
        public void onClick(View v) {
            final OrganizerEntry entry = new OrganizerEntry();
            entry.setEntry(mEntryEditView.getText().toString());
            entry.setDate(mDate);

            mEntryEditView.setText("");

            if (mUpdateMode) {
                final OrganizerDatabase database = new OrganizerDatabase(getContext());
                database.startWritableSession();
                database.updateEntryInDatabase(entry, mEntryToUpdate, new OrganizerDatabase.UpdateCallback() {
                    @Override
                    public void onDataUpdated(boolean success) {
                        mUpdateMode = false;
                        mEntryToUpdate = null;

                        //if (success) {
                            mContentEntries.add(entry);
                            updateUI();
                        //}
                        database.stopSession();
                    }
                });
            } else {
                final OrganizerDatabase database = new OrganizerDatabase(getContext());
                database.startWritableSession();
                database.putEntryInDatabase(entry, new OrganizerDatabase.InsertCallback() {
                    @Override
                    public void onDataInserted(boolean success) {
                        if (success) {
                            mContentEntries.add(entry);
                            updateUI();
                        }
                        database.stopSession();
                        }
                });
            }
        }
    };

    @Override
    public View onCreateView(LayoutInflater inflater, @Nullable ViewGroup container,
                             @Nullable Bundle savedInstanceState) {
        View root = inflater.inflate(R.layout.organizer_day_fragment, null);

        Bundle bundle = getArguments();
        if (bundle != null) {
            mDate = bundle.getParcelable(DATE_KEY);
        }

        if (savedInstanceState != null) {
            mDate = savedInstanceState.getParcelable(DATE_KEY);
        }

        mEntryListView = (RecyclerView) root.findViewById(R.id.organizer_day_fragment_list);
        mNothingToShowView = (TextView) root.findViewById(R.id.organizer_day_fragment_nothing_textview);
        mEntryEditView = (EditText) root.findViewById(R.id.organizer_day_fragment_entry_edit);
        mSubmitButton = (Button) root.findViewById(R.id.organizer_day_fragment_entry_submit);

        mEntryListView.setLayoutManager(new LinearLayoutManager(getActivity()));

        mSubmitButton.setOnClickListener(submitOnClickListener);

        refreshDataFromDB();
        updateUI();
        return root;
    }

    @Override
    public void onResume() {
        super.onResume();
        updateToolbar();
    }

    @Override
    public void onSaveInstanceState(Bundle outState) {
        outState.putParcelable(DATE_KEY, mDate);
    }

    public void updateUI() {
        if (mContentEntries.isEmpty()) {
            mEntryListView.setVisibility(View.GONE);
            mNothingToShowView.setVisibility(View.VISIBLE);
        } else {
            mEntryListView.setVisibility(View.VISIBLE);
            mNothingToShowView.setVisibility(View.GONE);

            if (mAdapter == null) {
                mAdapter = new OrganizerDayListAdapter(getContext());
                mAdapter.setOnOrganizerDayClickListener(this);
                mEntryListView.setAdapter(mAdapter);
            }

            mAdapter.setOrganizerEntries(mContentEntries);
            mAdapter.showDataSet();
        }
    }

    protected void updateToolbar() {
        ActionBar actionBar = ((AppCompatActivity)getActivity()).getSupportActionBar();
        if (actionBar != null) {
            actionBar.setDisplayShowTitleEnabled(true);
            actionBar.setDisplayHomeAsUpEnabled(true);

            if (mDate != null) {
                actionBar.setTitle(OrganizerUtil.convertOrganizerDateToDisplayText(mDate));
            }
        }
    }

    private void refreshDataFromDB() {
        String dbString = OrganizerUtil.convertOrganizerDateToSQLiteDate(mDate);
        final OrganizerDatabase database = new OrganizerDatabase(getContext());
        database.startReadableSession();
        database.registerLoaderForOrganizerDayFragment(getLoaderManager(), new OrganizerDatabase.LoadCallback() {
                    @Override
                    public void onDataLoaded(List data) {
                        if (data == null) {
                            mContentEntries.clear();
                        } else {
                            mContentEntries = data;
                        }
                        updateUI();
                        database.stopSession();
                    }
                }, dbString);
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
    public void onItemListClick(int position) {
        if (mActionMode != null) {
            toggleItemSelection(position);
        }
    }

    @Override
    public void onItemListLongClick(int position) {
        if (mActionMode == null) {
            mActionModeCallback = new OrganizerActionModeCallback();
            mActionMode = ((AppCompatActivity) getActivity()).startSupportActionMode(mActionModeCallback);
        }
        toggleItemSelection(position);
    }

    private void toggleItemSelection(int position) {
        mAdapter.toggleSelection(position);
        int count = mAdapter.getSelectedItemsCount();

        if (count == 0) {
            mActionMode.finish();
            mActionMode = null;
        } else {
            if (count == 1) {
                mActionModeCallback.setEditItemVisibility(true);
            } else {
                mActionModeCallback.setEditItemVisibility(false);
            }
        }
    }

    private class OrganizerActionModeCallback implements ActionMode.Callback {

        private MenuItem mDeleteItem;
        private MenuItem mEditItem;

        public OrganizerActionModeCallback() {
        }

        @Override
        public boolean onCreateActionMode(ActionMode mode, Menu menu) {
            mode.getMenuInflater().inflate(R.menu.organizer_day_fragment_action_mode, menu);
            mEditItem = menu.findItem(R.id.action_edit);
            mDeleteItem = menu.findItem(R.id.action_delete);
            return true;
        }

        @Override
        public boolean onPrepareActionMode(ActionMode mode, Menu menu) {
            return false;
        }

        @Override
        public boolean onActionItemClicked(ActionMode mode, MenuItem item) {
            final List<OrganizerEntry> entryList = mAdapter.getSelectedEntries();

            switch (item.getItemId()) {
                case R.id.action_edit:
                    if (entryList.size() == 1) {
                        OrganizerEntry entry = entryList.get(0);
                        String text = entry.getEntry();
                        mEntryEditView.setText(text);
                        mContentEntries.remove(entry);

                        mUpdateMode = true;
                        mEntryToUpdate = entry;
                        mActionMode.finish();
                        mActionMode = null;
                    }
                    break;
                case R.id.action_delete:
                    final OrganizerDatabase database = new OrganizerDatabase(getContext());
                    database.startWritableSession();
                    database.deleteEntriesFromDatabase(entryList, new OrganizerDatabase.DeleteCallback() {
                        @Override
                        public void onDataDeleted(boolean success) {
                            //if (success) {
                                for (OrganizerEntry entry : entryList) {
                                    mContentEntries.remove(entry);
                                }
                                mActionMode.finish();
                                mActionMode = null;
                            //}
                            database.stopSession();
                        }
                    });
                    break;
            }
            return false;
        }

        @Override
        public void onDestroyActionMode(ActionMode mode) {
            mActionMode = null;

            mAdapter.clearSelection();
            updateUI();
        }

        public void setEditItemVisibility(boolean visibility) {
            if (mEditItem != null)
                mEditItem.setVisible(visibility);
        }
    }
}
