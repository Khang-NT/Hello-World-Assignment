//
// Created by root on 28/05/2016.
//

#ifndef ASSIGNMENT_DATETIMEFORMAT_HPP
#define ASSIGNMENT_DATETIMEFORMAT_HPP


#include <string>
#include <ctime>

using namespace std;

class DateTimeFormat {
public:
    /**
     * Date time format: <br>
     *       yyyy: year <br>
     *       MM: month<br>
     *       dd: day<br>
     *       hh: hour 12<br>
     *       HH: hour 24<br>
     *       mm: minute<br>
     *       ss: second<br>
     *       aa: am/pm<br>
     *       <br>
     *       Example: dd/MM/yyyy hh:mm:sss aa  -->   29/06/2016 01:16:54s pm <br>
     *               yyyy.MM.dd HHhmmm       -->   2016.06.29 13h16m
     *
     * @param time time stamp in seconds.
     * @param formatToken format token.
     * @return (string) the time formated.
     */
    static string format(long int time, string formatToken);
};


#endif //ASSIGNMENT_DATETIMEFORMAT_HPP
