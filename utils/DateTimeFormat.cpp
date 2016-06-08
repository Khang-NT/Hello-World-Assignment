//
// Created by root on 28/05/2016.
//

#include "DateTimeFormat.hpp"

string addZero(string time) {
    return time.size() == 2 ? time : "0" + time;
}

void replaceString(std::string &subject, const std::string &search,
                   const std::string &replace) {
    size_t pos = 0;
    while ((pos = subject.find(search, pos)) != std::string::npos) {
        subject.replace(pos, search.length(), replace);
        pos += replace.length();
    }
}


string DateTimeFormat::format(long int time, string formatToken) {
    time_t epoch_time_as_time_t = time;
    tm *timeStruct = localtime(&epoch_time_as_time_t);

    replaceString(formatToken, "yyyy", to_string(1900 + timeStruct->tm_year));
    replaceString(formatToken, "MM", addZero(to_string(timeStruct->tm_mon + 1)));
    replaceString(formatToken, "dd", addZero(to_string(timeStruct->tm_mday)));

    replaceString(formatToken, "hh", addZero(to_string(timeStruct->tm_hour + 1 > 12 ?
                                                       timeStruct->tm_hour + 1 - 12 : timeStruct->tm_hour + 1)));
    replaceString(formatToken, "HH", addZero(to_string(timeStruct->tm_hour + 1)));
    replaceString(formatToken, "mm", addZero(to_string(timeStruct->tm_min + 1)));
    replaceString(formatToken, "ss", addZero(to_string(timeStruct->tm_sec + 1)));
    replaceString(formatToken, "aa", timeStruct->tm_hour + 1 >= 12 ? "pm" : "am");
    return formatToken;
}
