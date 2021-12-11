#ifndef REVIEW_H_INCLUDED
#define REVIEW_H_INCLUDED

#pragma once
#include <iostream>

using namespace std;

class Review
{
private:
    string review_id;
    string review_text;
    int upvotes;
    string app_version;
    string posted_date;

public:
    Review() {}

    // create a Review destructor
    ~Review() {}

    string getReview_id() { return review_id; }
    void setReview_id(string review_id) { this->review_id = review_id; }
    string getReview_text() { return review_text; }
    void setReview_text(string review_text) { this->review_text = review_text; }
    int getUpvotes() { return upvotes; }
    void setUpvotes(int upvotes) { this->upvotes = upvotes; }
    string getAppVersion() { return app_version; }
    void setAppVersion(string app_version) { this->app_version = app_version; }
    string getPostedDate() { return posted_date; }
    void setPostedDate(string posted_date) { this->posted_date = posted_date; }
};

#endif