// Implementation of the Range Minimum Query algorithms presented in [1].

// [1] M.A. Bender, M. Farach-Colton:
//     The LCA Problem Revisited.
//     LATIN 2000, LNCS 1776, 88-94, 2000.


#include <iomanip>
#include <iostream>

#include "naiveRmq.hpp"
#include "noPreRmq.hpp"
#include "rmqTest.h"
#include "segTreeRmq.hpp"


using namespace std;


// Prints the given time (in milliseconds) into the given stream using
// appropriate units.
void printTime(int64_t time, ostream& out)
{
    constexpr int64_t milSec = 1;
    constexpr int64_t decSec = 100 * milSec;
    constexpr int64_t second = 10 * decSec;
    constexpr int64_t minute = 60 * second;
    constexpr int64_t hour = 60 * minute;
    constexpr int64_t day = 24 * hour;

    if (time < second)
    {
        out << setw(3) << time << " ms";
    }
    else if (time <= minute)
    {
        int64_t dSecs = (time + decSec - 1) / decSec;
        int64_t secs = dSecs / 10;
        dSecs = dSecs % 10;

        out << setw(2) << secs << "." << dSecs << " s";
    }
    else if (time <= hour)
    {
        int64_t secs = (time + second - 1) / second;
        int64_t mins = secs / 60;
        secs = secs % 60;

        out << setw(2) << mins << " min " << setw(2) << secs << " s";
    }
    else if (time <= day)
    {
        int64_t mins = (time + minute - 1) / minute;
        int64_t hours = mins / 60;
        mins = mins % 60;

        out << setw(2) << hours << " h " << setw(2) << " min";
    }
    else // time > day
    {
        int64_t hours = (time + hour - 1) / hour;
        int64_t days = hours / 24;
        hours = hours % 24;

        out << days << " d " << setw(2) << hour << " h";
    }
    out << flush;
}

int main()
{
    const size_t   dataSize = 20000;
    const size_t   queries  = 1000000;
    const unsigned seed     = 19082017;

    cout << "   Size: " << dataSize << endl;
    cout << "Queries: " << queries << endl;


    cout << "\n*** Reference ***";
    {
        pair<size_t, size_t> timePair =
            RMQTest::getRuntime<RMQ<int>>(dataSize, queries, seed);

        cout << "\nP: "; printTime(timePair.first, cout);
        cout << "\nQ: "; printTime(timePair.second, cout);
        cout << endl;
    }

    cout << "\n*** No Pre-Processing ***";
    {
        pair<size_t, size_t> timePair =
            RMQTest::getRuntime<NoPreRMQ<int>>(dataSize, queries, seed);

        cout << "\nP: "; printTime(timePair.first, cout);
        cout << "\nQ: "; printTime(timePair.second, cout);
        cout << endl;
    }

    cout << "\n*** Naive ***";
    {
        pair<size_t, size_t> timePair =
            RMQTest::getRuntime<NaiveRMQ<int>>(dataSize, queries, seed);

        cout << "\nP: "; printTime(timePair.first, cout);
        cout << "\nQ: "; printTime(timePair.second, cout);

        // Verify correctnes.
        bool correct =
            RMQTest::verifyAlgorithms
            <
                NoPreRMQ<int>,
                NaiveRMQ<int>
            >
            (dataSize, queries, seed);
        cout << "\nC: " << (correct ? "Yes" : "No");

        cout << endl;
    }

    cout << "\n*** Segment Tree ***";
    {
        pair<size_t, size_t> timePair =
            RMQTest::getRuntime<SegTreeRMQ<int>>(dataSize, queries, seed);

        cout << "\nP: "; printTime(timePair.first, cout);
        cout << "\nQ: "; printTime(timePair.second, cout);

        // Verify correctnes.
        bool correct =
            RMQTest::verifyAlgorithms
            <
                NoPreRMQ<int>,
                SegTreeRMQ<int>
            >
            (dataSize, queries, seed);
        cout << "\nC: " << (correct ? "Yes" : "No");

        cout << endl;
    }
}
