/*
Date and Time Utility - C++ Console Application
Features:
- Display current date and time (local and UTC)
- Format date/time output
- Calculate difference between two dates
- Parse date input from user (YYYY-MM-DD)
Author: BLACKBOXAI
*/

#include &lt;iostream&gt;
#include &lt;iomanip&gt;
#include &lt;ctime&gt;
#include &lt;chrono&gt;
#include &lt;sstream&gt;

using namespace std;

// Function to display current local date and time
void displayCurrentDateTime() {
    time_t now = time(nullptr);
    tm *ltm = localtime(&now);
    cout &lt;&lt; "Current Local Date and Time: ";
    cout &lt;&lt; put_time(ltm, "%Y-%m-%d %H:%M:%S") &lt;&lt; endl;

    tm *gtm = gmtime(&now);
    cout &lt;&lt; "Current UTC Date and Time:   ";
    cout &lt;&lt; put_time(gtm, "%Y-%m-%d %H:%M:%S") &lt;&lt; endl;
}

// Function to parse a date string (yyyy-mm-dd) into tm struct
bool parseDate(const string &dateStr, tm &t) {
    istringstream ss(dateStr);
    ss >> get_time(&t, "%Y-%m-%d");
    if (ss.fail()) {
        return false;
    }
    t.tm_hour = 0;
    t.tm_min = 0;
    t.tm_sec = 0;
    t.tm_isdst = -1;
    return true;
}

// Function to calculate and display difference between two dates
void calculateDateDifference() {
    string date1Str, date2Str;
    tm date1 = {}, date2 = {};
    cout &lt;&lt; "Enter first date (YYYY-MM-DD): ";
    cin &gt;&gt; date1Str;
    if (!parseDate(date1Str, date1)) {
        cout &lt;&lt; "Invalid date format!" &lt;&lt; endl;
        return;
    }

    cout &lt;&lt; "Enter second date (YYYY-MM-DD): ";
    cin &gt;&gt; date2Str;
    if (!parseDate(date2Str, date2)) {
        cout &lt;&lt; "Invalid date format!" &lt;&lt; endl;
        return;
    }

    time_t time1 = mktime(&date1);
    time_t time2 = mktime(&date2);

    if (time1 == -1 || time2 == -1) {
        cout &lt;&lt; "Error computing time." &lt;&lt; endl;
        return;
    }

    double diffSeconds = difftime(time2, time1);
    int days = static_cast&lt;int&gt;(diffSeconds / (60 * 60 * 24));
    cout &lt;&lt; "Difference between " &lt;&lt; date1Str &lt;&lt; " and " &lt;&lt; date2Str &lt;&lt; " is: "
         &lt;&lt; days &lt;&lt; " day(s)." &lt;&lt; endl;
}

// Main menu
void printMenu() {
    cout &lt;&lt; "\\nDate and Time Utility\\n";
    cout &lt;&lt; "1. Display current date and time\\n";
    cout &lt;&lt; "2. Calculate difference between two dates\\n";
    cout &lt;&lt; "3. Exit\\n";
    cout &lt;&lt; "Select an option: ";
}

int main() {
    int choice;
    do {
        printMenu();
        cin &gt;&gt; choice;

        switch(choice) {
            case 1:
                displayCurrentDateTime();
                break;
            case 2:
                calculateDateDifference();
                break;
            case 3:
                cout &lt;&lt; "Exiting...\\n";
                break;
            default:
                cout &lt;&lt; "Invalid option. Try again.\\n";
        }
    } while(choice != 3);

    return 0;
}

