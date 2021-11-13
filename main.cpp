#include "Review.h"
#include "File.h"
#include "iostream"
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

//what we need to work with: review_id, review_text, upvotes, app_version, posted_date

void openFile()
{

    File file;

    vector<Review> review;
    vector<Review> teste;

    file.readFile(&review, "teste.csv");

    // file.writeTxt(&review);

    file.writeBin(&review);

    file.readBinary(&teste);
}

int main()
{
    openFile();
    cout << "Fim" << endl;
    return 0;
}