// projeect.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
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
public:
    Room()
    {
        number = 0;
        beds = 0;
        isBusy = 0;
        strcpy(startDate , "");
        strcpy(endDate , "");
        strcpy(name , "");
    }
    Room(int _number,int _beds)
    {
        number = _number;
        beds = _beds;
        isBusy = 0;
        strcpy(startDate, "");
        strcpy(endDate, "");
        strcpy(name, "");
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
            }
        }
    }
    RoomList(const RoomList& other)
    {
        for (size_t i = 0; i < totalApps; i++)
        {
            this->list[i] = other.list[i];
        }
    }
    RoomList& operator =(const RoomList& other)
    {
        for (size_t i = 0; i < totalApps; i++)
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
    //int syears = (_date[0]-48) * 1000 + (_date[1]-48) * 100 + (_date[2]-48) * 10 + (_date[3]-48);
    //int smonths = ((_date[4] - 48) * 10 + _date[5] - 48);
    //int sdays = ((_date[6] - 48) * 10 + _date[7] - 48);
    
    //TEST
    Room a = Room(253, 5);
    Room b = Room(243, 3);
    Room c = Room(233, 2);
    
    RoomList arr;
    arr.setTotalApps(3);
    ;
    arr.addRoom(a);
    arr.addRoom(b);
    arr.addRoom(c);
    ;
    arr.registrationOfGuest(243, "20220501", "20220508", "Denis");
    arr.registrationOfGuest(253, "20220502", "20220510", "Alex");
    arr.registrationOfGuest(233, "20220501", "20220509", "Valeri");
    arr.freeList("20220510");
    arr.leaveTheRoom(253);
    arr.freeList("20220510");

}

