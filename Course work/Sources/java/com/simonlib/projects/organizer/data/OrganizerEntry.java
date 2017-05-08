package com.simonlib.projects.organizer.data;

public class OrganizerEntry {

    private OrganizerDate mDate;
    private String mEntry;

    public OrganizerDate getDate() {
        return mDate;
    }

    public void setDate(OrganizerDate date) {
        mDate = date;
    }

    public String getEntry() {
        return mEntry;
    }

    public void setEntry(String entry) {
        mEntry = entry;
    }
}
