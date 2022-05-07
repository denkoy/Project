// projeect.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;
#pragma warning(disable : 4996)
class Room
{
    int number;
    int beds;
    bool isBusy;
    char startDate[15];
    char endDate[15];
    char name[30];
    int totalDays = 0;
public:
    Room()
    {
        number = 0;
        beds = 0;
        isBusy = 0;
        strcpy(startDate , "");
        strcpy(endDate , "");
        strcpy(name , "");
        totalDays = 0;
    }
    Room(int _number,int _beds)
    {
        number = _number;
        beds = _beds;
        isBusy = 0;
        strcpy(startDate, "");
        strcpy(endDate, "");
        strcpy(name, "");
        totalDays = 0;
    }
    int getNumber()
    {
        return number;
    }
    int getBeds()
    {
        return beds;
    }
    bool getisBusy()
    {
        return isBusy;
    }
    void setBeds(const int _beds)
    {
        beds = _beds;
    }
    char* getStartDate()
    {
        return startDate;
    }
    char* getEndDate()
    {
        return endDate;
    }
    char* getName()
    {
        return name;
    }
    void setTotalDays(const int _totalDays)
    {
        totalDays = _totalDays;
    }
    void setisBusy(const bool _isBusy)
    {
        isBusy = _isBusy;
    }
    void setstartDate(const char _start[])
    {
        strcpy(startDate, _start);
    }
    void setendDate(const char _end[])
    {
        strcpy(endDate, _end);
    }
    void setName(const char _name[])
    {
        strcpy(name, _name);
    }

    //Извежда справка за използването на стаи в даден период и я записва в 
    //текстов файл с име report - YYYY - MM - DD.txt, където YYYY - MM - DD е
      //  началната дата на периода.Извежда се списък, в който за всяка стая,
      //  използвана в дадения период, се извежда и броя на дните, в които е
        //била използвана.
    friend ostream& operator << (ostream& out, const Room& room)
    {
        out << "room number: " << room.number << ", total days of reservation: " << room.totalDays << endl;

        return out;
    }
};
class RoomList
{
private:
    Room* list;
    int totalApps;
public:
    RoomList()
    {
        list = nullptr;
        totalApps = 0;
    }
    void addRoom(Room room)
    {
        for(int i  = 0; i < totalApps; i++)
        {
            if (list[i].getNumber() == 0)
            {
                list[i] = room;
                break;
            }
        }
    }
    void setTotalApps(const int apps)
    {
        totalApps = apps;
        list = new Room[apps];
    }
    int getTotalApps()
    {
        return totalApps;
    }
    /*Регистриране на гост
        Регистриране на гости в стая с даден номер за въведен период, може
        да се въвежда и бележка за резервацията и се добавя името на госта
        (само едно име на стая).*/
    void registrationOfGuest(const int _number,const char _startDate[],const char _endDate[],const char _name[])
    {
        for (int i = 0; i < totalApps; i++)
        {
            if (_number == list[i].getNumber())
            {
                list[i].setendDate(_endDate);
                list[i].setstartDate(_startDate);
                list[i].setName(_name);
                list[i].setisBusy(1);
                break;
            }
        }
    }
    //Извежда списък на свободните стаи за дадена дата
    void freeList(const char _date[])
    {
        int curryears = (_date[0] - 48) * 1000 + (_date[1] - 48) * 100 + (_date[2] - 48) * 10 + (_date[3] - 48);
        int currmonths = ((_date[4] - 48) * 10 + _date[5] - 48);
        int currdays = ((_date[6] - 48) * 10 + _date[7] - 48);
        cout << "Free rooms" << endl;
        for (int i = 0; i < totalApps; i++)
        {
            int syears = (list[i].getStartDate()[0] - 48) * 1000 + (list[i].getStartDate()[1] - 48) * 100 + (list[i].getStartDate()[2] - 48) * 10 + (list[i].getStartDate()[3] - 48);
            int smonths = ((list[i].getStartDate()[4] - 48) * 10 + list[i].getStartDate()[5] - 48);
            int sdays = ((list[i].getStartDate()[6] - 48) * 10 + list[i].getStartDate()[7] - 48);
            int eyears = (list[i].getEndDate()[0] - 48) * 1000 + (list[i].getEndDate()[1] - 48) * 100 + (list[i].getEndDate()[2] - 48) * 10 + (list[i].getEndDate()[3] - 48);
            int emonths = ((list[i].getEndDate()[4] - 48) * 10 + list[i].getEndDate()[5] - 48);
            int edays = ((list[i].getEndDate()[6] - 48) * 10 + list[i].getEndDate()[7] - 48);
            
            if (curryears < syears || curryears > eyears || list[i].getStartDate() =="")
            {
                cout << "Number: " << list[i].getNumber() << endl;
            }
            else
            {
                if ((currmonths < smonths || currmonths > emonths))
                {
                    cout << "Number: " << list[i].getNumber() << endl;;
                }
                else
                {
                    if ((currdays < sdays || currdays > edays))
                    {
                        cout << "Number: " << list[i].getNumber() << endl;;
                    }

                }
            }
        }
    }
    //
    //Освобождаване на заета стая с даден номер.
    void leaveTheRoom(const int _number)
    {
        for(int i = 0; i < totalApps; i++)
        {
            if (_number == list[i].getNumber())
            {
                list[i].setisBusy(0);
                list[i].setName("");
                list[i].setstartDate("");
                list[i].setendDate("");
                break;
            }
        }
    }
    void IsItBusyForThisPeriod(const char _startDate[],const char _endDate[])
    {
        ofstream listing("report.txt");
        if (!listing.is_open())
        {
            cout << "Error" << endl;
        }
        int syears = (_startDate[0] - 48) * 1000 + (_startDate[1] - 48) * 100 + (_startDate[2] - 48) * 10 + (_startDate[3] - 48);
        int smonths = ((_startDate[4] - 48) * 10 + _startDate[5] - 48);
        int sdays = ((_startDate[6] - 48) * 10 + _startDate[7] - 48);
        int eyears = (_endDate[0] - 48) * 1000 + (_endDate[1] - 48) * 100 + (_endDate[2] - 48) * 10 + (_endDate[3] - 48);
        int emonths = ((_endDate[4] - 48) * 10 + _endDate[5] - 48);
        int edays = ((_endDate[6] - 48) * 10 + _endDate[7] - 48);
        for (int i = 0; i < totalApps; i++)
        {
            int currsyears = (list[i].getStartDate()[0] - 48) * 1000 + (list[i].getStartDate()[1] - 48) * 100 + (list[i].getStartDate()[2] - 48) * 10 + (list[i].getStartDate()[3] - 48);
            int currsmonths = ((list[i].getStartDate()[4] - 48) * 10 + list[i].getStartDate()[5] - 48);
            int currsdays = ((list[i].getStartDate()[6] - 48) * 10 + list[i].getStartDate()[7] - 48);
            int curreyears = (list[i].getEndDate()[0] - 48) * 1000 + (list[i].getEndDate()[1] - 48) * 100 + (list[i].getEndDate()[2] - 48) * 10 + (list[i].getEndDate()[3] - 48);
            int curremonths = ((list[i].getEndDate()[4] - 48) * 10 + list[i].getEndDate()[5] - 48);
            int curredays = ((list[i].getEndDate()[6] - 48) * 10 + list[i].getEndDate()[7] - 48);
            //Proverka dali e celiqt period na prestoi e  izvun zadadeniq period.

            if ((currsyears < syears && curreyears < syears) || (currsyears > eyears && curreyears > eyears))
            {
                ;
            }
            else
            {
                if ((currsmonths < smonths && curremonths < smonths && (syears-currsyears<=0)) || (currsmonths > emonths && curremonths > emonths && (eyears - curreyears >= 0)))
                {
                    ;
                }
                else
                {
                    if ((currsdays < sdays && curredays < sdays && (smonths - currsmonths <= 0)) || (currsdays > edays && curredays > edays) && (emonths - curremonths >= 0))
                    {
                        ;
                    }
                    else
                    {
                        
                        const int totalDays = (((curreyears - currsyears) * 365) + ((curremonths - currsmonths) * 30) + ((curredays - currsdays))); 
                        list[i].setTotalDays(totalDays);
                        listing << list[i] << endl;
                    }
                }
            }
        }
        listing.close();
    }
   /* Намиране на подходяща свободна стая с въведен минимален брой
        легла в даден период.При наличие на повече свободни стаи се
        предпочитат такива с по - малко на брой легла.*/
    void searchForARoom(const int minimumBeds, const char _startDate[], const char _endDate[])
    {
        Room currentMinimalAvailableRoom;
        currentMinimalAvailableRoom.setBeds(100000);
        int syears = (_startDate[0] - 48) * 1000 + (_startDate[1] - 48) * 100 + (_startDate[2] - 48) * 10 + (_startDate[3] - 48);
        int smonths = ((_startDate[4] - 48) * 10 + _startDate[5] - 48);
        int sdays = ((_startDate[6] - 48) * 10 + _startDate[7] - 48);
        int eyears = (_endDate[0] - 48) * 1000 + (_endDate[1] - 48) * 100 + (_endDate[2] - 48) * 10 + (_endDate[3] - 48);
        int emonths = ((_endDate[4] - 48) * 10 + _endDate[5] - 48);
        int edays = ((_endDate[6] - 48) * 10 + _endDate[7] - 48);
        for (int i = 0; i < totalApps; i++)
        {
            int currsyears = (list[i].getStartDate()[0] - 48) * 1000 + (list[i].getStartDate()[1] - 48) * 100 + (list[i].getStartDate()[2] - 48) * 10 + (list[i].getStartDate()[3] - 48);
            int currsmonths = ((list[i].getStartDate()[4] - 48) * 10 + list[i].getStartDate()[5] - 48);
            int currsdays = ((list[i].getStartDate()[6] - 48) * 10 + list[i].getStartDate()[7] - 48);
            int curreyears = (list[i].getEndDate()[0] - 48) * 1000 + (list[i].getEndDate()[1] - 48) * 100 + (list[i].getEndDate()[2] - 48) * 10 + (list[i].getEndDate()[3] - 48);
            int curremonths = ((list[i].getEndDate()[4] - 48) * 10 + list[i].getEndDate()[5] - 48);
            int curredays = ((list[i].getEndDate()[6] - 48) * 10 + list[i].getEndDate()[7] - 48);
            if ((currsyears < syears && curreyears<syears)||(currsyears > eyears && curreyears>eyears)|| list[i].getisBusy() == 0)
            {
                if (list[i].getBeds() >= minimumBeds && currentMinimalAvailableRoom.getBeds() > list[i].getBeds())
                {
                    currentMinimalAvailableRoom = list[i];
                }
  
            }
            else
            {
                if ((currsmonths < smonths && curremonths<smonths &&syears-currsyears >= 0&&syears-curreyears>=0) || (currsmonths > emonths && curremonths > emonths && eyears-curreyears<=0&& eyears - currsyears <= 0))
                {
                    if (list[i].getBeds() >= minimumBeds && currentMinimalAvailableRoom.getBeds() > list[i].getBeds())
                    {
                        currentMinimalAvailableRoom = list[i];
                    }
                }
                else
                {
                    if ((currsdays < sdays && curredays<sdays &&smonths-currsmonths>=0&& smonths - curremonths >= 0)|| (currsdays > edays && curredays > edays&&emonths-curremonths<=0&&emonths-currsmonths<=0))
                    {
                        if (list[i].getBeds() >= minimumBeds && currentMinimalAvailableRoom.getBeds() > list[i].getBeds())
                        {
                            currentMinimalAvailableRoom = list[i];
                        }
                    }
                }
            }
        }
        if (currentMinimalAvailableRoom.getBeds() == 100000)
        {
            cout << "No available room";
        }
        else
        {
            cout << "Room " << currentMinimalAvailableRoom.getNumber() << " is available for your perimeters of stay." << endl;
        }
    }
    /*Обявява стаята с даден номер за временно недостъпна за даден
        период от време(например за ремонт или основно почистване), като се
        добавя бележка.В стаята няма регистриран гост, но никой не може да
        бъде настанен в нея*/
    void closeTemporary(const int numberOfRoom,const char _startDate[],const char _endDate[])
    {
        for (int i = 0; i < totalApps; i++)
        {
            if (numberOfRoom == list[i].getNumber())
            {
                if (list[i].getisBusy() == 1)
                {
                    cout << "You can't close BUSY room for maintenance!" << endl;
                    break;
                }
                cout << "Room is now temporary closed for maintenance" << endl;
                list[i].setisBusy(1);
                list[i].setstartDate(_startDate);
                list[i].setendDate(_endDate);
                break;
            }
        }
    }
    RoomList(const RoomList& other)
    {
        for (int i = 0; i < totalApps; i++)
        {
            this->list[i] = other.list[i];
        }
    }
    RoomList& operator =(const RoomList& other)
    {
        for (int i = 0; i < totalApps; i++)
        {
            this->list[i] = other.list[i];
        }
    }
    ~RoomList()
    {
        delete list;
    }

};



int main()
{
  




    //char _date[15];
    //strcpy(_date, "19242233");
  /*  char currStartDate[15];
    int syears = (currStartDate[0]-48) * 1000 + (currStartDate[1]-48) * 100 + (currStartDate[2]-48) * 10 + (currStartDate[3]-48);
    int smonths = ((currStartDate[4] - 48) * 10 + currStartDate[5] - 48);
    int sdays = ((currStartDate[6] - 48) * 10 + currStartDate[7] - 48);*/
    
    //TEST
    Room a = Room(253, 5);
    Room b = Room(243, 6);
    Room c = Room(233, 7);
    
    RoomList arr;
    arr.setTotalApps(3);
    ;
    arr.addRoom(a);
    arr.addRoom(b);
    arr.addRoom(c);
    ;
    //test of IsItBusyForThisPeriod
    //arr.registrationOfGuest(243, "20220508", "20220509", "Denis");
    //arr.registrationOfGuest(253, "20220511", "20220515", "Alex");
    //arr.registrationOfGuest(233, "20220517", "20230519", "Valeri");
    //arr.IsItBusyForThisPeriod("20220510", "20220515");
    ;
    //test of searchForAroom
    //arr.registrationOfGuest(253, "20220516", "20220619", "Genis");
    //arr.registrationOfGuest(243, "20220301", "20220507", "Denis");
    //arr.registrationOfGuest(233, "20220505", "20220507", "Valeri");
    //arr.searchForARoom(5, "20220508", "20220515");
    ;
    //test of temporaryclose
    //arr.closeTemporary(253, "20221202", "20221205");
    //arr.IsItBusyForThisPeriod("20221202", "20221205");
}

