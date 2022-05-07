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
    void setNumber(const int _num)
    {
        number = _num;
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
                cout << _name << ", you sucessfully reserved a room!" << endl;
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
                cout << "ROOM RELEASED!" << endl;
                break;
            }
        }
    }
    void IsItBusyForThisPeriod(const char _startDate[],const char _endDate[])
    {
        char date[20];
        char arr[25] = "report-";
        int tempi = 0;
        for (int i = 0; i <= 14; i++)
        {
            if (i == 4 || i == 7)
            {
                date[i] = '-';
            }
            else if (i == 10)
            {
                date[i] = '.';
            }
            else if (i == 11 || i == 13)
            {
                date[i] = 't';
            }
            else if (i == 12)
            {
                date[i] = 'x';
            }
            else if (i == 14)
            {
                date[i] = '\0';
            }
            else {
                date[i] = _startDate[tempi];
                tempi++;
            }
        }
        strcat(arr, date);



        ofstream listing(arr);
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
  
    RoomList array;

    fstream list("listOfRooms.txt");
    ;
   if (!list.is_open())
    {
        cout << "Error :(";
        return 0;
    }
    int numOfRooms = 0;
    int temp = 1;
    char charNumOfRooms[50];
    list.getline(charNumOfRooms, 50);
    //prevrushtame char v int (na broq na staite)
    for (int i = strlen(charNumOfRooms) - 1; i >= 0; i--)
    {
        
        numOfRooms += ((charNumOfRooms[i] - 48) * temp);
        temp *= 10;
    }
    array.setTotalApps(numOfRooms);
    
    while (!list.eof()) 
    {
        char tempRoom[1000];
        list.getline(tempRoom, 1000);
        //NNN BBB;
        char charRoomNumber[10];
        char charRoomBeds[10];
        int lastI = 0;
        ; //vzimame nomera na staqta
        for (int i = 0; i < 1000; i++)
        {
            if (tempRoom[i] == ' ')
            {
                lastI = i;
                charRoomNumber[i] = '\0';
                break;
            }
            charRoomNumber[i] = tempRoom[i];     
        }
        ;  //vzimame broq na leglata
        int tempI = 0;
        for (int i = lastI + 1; i < 1000; i++)
        {
            if (tempRoom[i] ==' ' || tempRoom[i] == '\0')
            {
                charRoomBeds[tempI] = '\0';
                break;
            }
            charRoomBeds[tempI] = tempRoom[i];
            tempI++;
        }
        //obrushtame char masivite v intove
        int roomNumber = 0;
        int roomBeds = 0;
        int temp2 = 1;
        int temp3 = 1;
        for (int i = strlen(charRoomNumber)-1; i >= 0; i--)
        {

            roomNumber += (charRoomNumber[i] - 48) * temp2;
            temp2 *= 10;
        }
        for (int i = strlen(charRoomBeds)-1; i >= 0; i--)
        {

            roomBeds += (charRoomBeds[i] - 48) * temp3;
            temp3 *= 10;
        }
        Room temp;
        temp.setBeds(roomBeds);
        temp.setNumber(roomNumber);
        array.addRoom(temp);
    }
    list.close();

    //MENU OF THE HOTEL
    cout << "WELCOME TO THE HOTEL MANAGEMENT MACHINE" << endl;
    cout << "Made by Denis Bakir 1MI0800176" << endl;
    cout << "List of available commands:" << endl;
    cout << "REGISTRATION - in order to register guests." << endl;
    cout << "FREELIST - gives you list of free rooms for a current date." << endl;
    cout << "RELEASE - in order to release a room." << endl;
    cout << "REFERENCE - gives you a reference when was a room reserved" << endl;
    cout << "SEARCH - finds you a room with minimum selected beds for a current period" << endl;
    cout << "CLOSEAROOM - closes a room for maintenance" << endl;
    cout << "EXIT - to EXIT the MANAGEMENT MACHINE" << endl;
    cout << "ATTENTION!!! THE PERSON WHO IS WORKING WITH THE PROGRAM IS OBLIGED TO PROVIDE RIGHT VALUES TO THE VARIABLES" << endl;
    while (true)
    {
        cout << "Please select your command: ";
        char command[100];
        cin.getline(command, 100);
        if (strcmp(command, "EXIT") == 0)
        {
            cout <<"See you soon!" << endl;
            break;
        }
        else if(strcmp(command, "REGISTRATION") == 0)
        {
            cout << "In order to register guest please write the number of room which you want to reserve, start date, end date, and FIRST name" << endl;
            int number;
            cout << "Number: "; cin >> number;
            cin.ignore();
            char startDate[10];
            cout << "Start date in format YYYYMMDD: "; cin.getline(startDate, 10);
            char endDate[10];
            cout << "End date in format YYYYMMDD: "; cin.getline(endDate, 10);
            char Name[50];
            cout << "First Name: "; cin.getline(Name, 10);
            array.registrationOfGuest(number, startDate, endDate, Name);
        }
        else if (strcmp(command, "FREELIST") == 0)
        {
            cout << "In order to see all free appartments for a current date please select a date." << endl;
            char date[10];
            cout << "Date in YYYYMMDD format: "; cin.getline(date, 10);
            array.freeList(date);
        }
        else if (strcmp(command, "RELEASE") == 0)
        {
            cout << "In order to release a room please type room number." << endl;
            int roomNum;
            cout << "Room number: "; cin>>roomNum;
            cin.ignore();
            array.leaveTheRoom(roomNum);
        }
        else if (strcmp(command, "REFERENCE") == 0)
        {
            cout << "In order to make a reference if a room is busy in a current period please type start date and end date" << endl;
            cout << "ATTENTION!!! If a part of your selected period overlaps with a period of a reservation the room would appear as USED in your selected period" << endl;
            char startDate[10];
            cout << "Start date in format YYYYMMDD: "; cin.getline(startDate, 10);
            char endDate[10];
            cout << "End date in format YYYYMMDD: "; cin.getline(endDate, 10);
            cout << "ATTENTION!!! YOUR REFERNCE WILL APPEAR AS TXT FILE IN YOUR REPOSITORY!" << endl;
            array.IsItBusyForThisPeriod(startDate,endDate);
        }
        else if (strcmp(command, "SEARCH") == 0)
        {
            cout << "In order to search for a room with minimum beds please select: minimum beds, start date, end date." << endl;
            int minimumbeds;
            cout << "Minimum beds: "; cin >> minimumbeds;
            cin.ignore();
            char startDate[10];
            cout << "Start date in format YYYYMMDD: "; cin.getline(startDate, 10);
            char endDate[10];
            cout << "End date in format YYYYMMDD: "; cin.getline(endDate, 10);
            array.searchForARoom(minimumbeds,startDate, endDate);
        }
        else if (strcmp(command, "CLOSEAROOM") == 0)
        {
            cout << "In order to close a room for a maintenance please select number of a room and period of closure." << endl;
            int num;
            cout << "Number of room: "; cin >> num;
            cin.ignore();
            char startDate[10];
            cout << "Start date in format YYYYMMDD: "; cin.getline(startDate, 10);
            char endDate[10];
            cout << "End date in format YYYYMMDD: "; cin.getline(endDate, 10);
            array.closeTemporary(num, startDate, endDate);
        }
        else
        {
            cout << "Wrong command, try again!" << endl;
        }
    }
    //char _date[15];
    //strcpy(_date, "19242233");
  /*  char currStartDate[15];
    int syears = (currStartDate[0]-48) * 1000 + (currStartDate[1]-48) * 100 + (currStartDate[2]-48) * 10 + (currStartDate[3]-48);
    int smonths = ((currStartDate[4] - 48) * 10 + currStartDate[5] - 48);
    int sdays = ((currStartDate[6] - 48) * 10 + currStartDate[7] - 48);*/
    
    //TEST
   /* Room a = Room(253, 5);
    Room b = Room(243, 6);
    Room c = Room(233, 7);
    
    RoomList arr;
    arr.setTotalApps(3);
    ;
    arr.addRoom(a);
    arr.addRoom(b);
    arr.addRoom(c);
    ;
   // test of IsItBusyForThisPeriod
    arr.registrationOfGuest(243, "20220508", "20220509", "Denis");
    arr.registrationOfGuest(253, "20220511", "20220515", "Alex");
    arr.registrationOfGuest(233, "20220517", "20230519", "Valeri");
    ;
    arr.IsItBusyForThisPeriod("20220510", "20220515");*/
    
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

