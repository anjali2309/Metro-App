#include <bits/stdc++.h>
using namespace std;

class station
{
public:
    unordered_map<string, int> nbrs;
};

class metro
{
    unordered_map<string, station> stns;

public:
    int numStations()
    {
        return stns.size();
    }

    bool containsStation(string sname)
    {
        return stns.find(sname) != stns.end();
    }

    void addStation(string sname)
    {
        station s;
        stns.insert({sname, s});
    }

    void removeStation(string sname)
    {
        // removing the station from neighbors list of all stations
        for (auto i : stns)
        {
            if (i.second.nbrs.find(sname) != i.second.nbrs.end())
            {
                i.second.nbrs.erase(sname);
            }
        }

        // removing station from stations list.
        stns.erase(sname);
    }

    int numEdges()
    {
        int count = 0;
        for (auto i : stns)
        {
            count += i.second.nbrs.size();
        }
        return count / 2;
    }

    bool containEdge(string stn1, string stn2)
    {
        if (stns[stn1].nbrs.find(stn2) != stns[stn1].nbrs.end())
        {
            return true;
        }
        return false;
    }

    void addEdge(string stn1, string stn2, int value)
    {
        // Checking if both stations are present and not have edge between them.
        if (stns.find(stn1) == stns.end() || stns.find(stn2) == stns.end() || stns[stn1].nbrs[stn2])
            return;

        // adding station1 to neighbors of station 2 && vice versa.
        stns[stn1].nbrs[stn2] = value;
        stns[stn2].nbrs[stn1] = value;
    }

    void removeEdge(string stn1, string stn2)
    {
        // Checking if both stations are present and not have edge between them.
        if (stns.find(stn1) == stns.end() || stns.find(stn2) == stns.end() || stns[stn1].nbrs[stn2])
            return;

        // removing station1 from neighbors of station 2 && vice versa.
        stns[stn1].nbrs.erase(stn2);
        stns[stn2].nbrs.erase(stn1);
    }

    void display_map()
    {
        cout << "\t Delhi Metro Map" << endl;
        cout << "\t------------------" << endl;
        cout << "----------------------------------------------------\n"
             << endl;

        for (auto i : stns)
        {
            string str = i.first + " =>\n";
            for (auto j : stns[i.first].nbrs)
            {
                str = str + "\t" + j.first + "\t";
                if (j.first.length() < 16)
                    str = str + "\t";
                if (j.first.length() < 8)
                    str = str + "\t";
                str = str + to_string(j.second) + "\n";
            }
            cout << str << endl;
        }
        cout << "\t------------------" << endl;
        cout << "---------------------------------------------------\n"
             << endl;
    }

    void displayStations()
    {
        cout << "\n***********************************************************************\n"
             << endl;
        int num = 1;
        for (auto i : stns)
        {
            cout << num << ". " << i.first << endl;
            num++;
        }
        cout << "\n***********************************************************************\n"
             << endl;
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Create_Metro_Map()
    {
        addStation("Noida Sector 62~B");
        addStation("Botanical Garden~B");
        addStation("Yamuna Bank~B");
        addStation("Rajiv Chowk~BY");
        addStation("Vaishali~B");
        addStation("Moti Nagar~B");
        addStation("Janak Puri West~BO");
        addStation("Dwarka Sector 21~B");
        addStation("Huda City Center~Y");
        addStation("Saket~Y");
        addStation("Vishwavidyalaya~Y");
        addStation("Chandni Chowk~Y");
        addStation("New Delhi~YO");
        addStation("AIIMS~Y");
        addStation("Shivaji Stadium~O");
        addStation("DDS Campus~O");
        addStation("IGI Airport~O");
        addStation("Rajouri Garden~BP");
        addStation("Netaji Subhash Place~PR");
        addStation("Punjabi Bagh West~P");

        addEdge("Noida Sector 62~B", "Botanical Garden~B", 8);
        addEdge("Botanical Garden~B", "Yamuna Bank~B", 10);
        addEdge("Yamuna Bank~B", "Vaishali~B", 8);
        addEdge("Yamuna Bank~B", "Rajiv Chowk~BY", 6);
        addEdge("Rajiv Chowk~BY", "Moti Nagar~B", 9);
        addEdge("Moti Nagar~B", "Janak Puri West~BO", 7);
        addEdge("Janak Puri West~BO", "Dwarka Sector 21~B", 6);
        addEdge("Huda City Center~Y", "Saket~Y", 15);
        addEdge("Saket~Y", "AIIMS~Y", 6);
        addEdge("AIIMS~Y", "Rajiv Chowk~BY", 7);
        addEdge("Rajiv Chowk~BY", "New Delhi~YO", 1);
        addEdge("New Delhi~YO", "Chandni Chowk~Y", 2);
        addEdge("Chandni Chowk~Y", "Vishwavidyalaya~Y", 5);
        addEdge("New Delhi~YO", "Shivaji Stadium~O", 2);
        addEdge("Shivaji Stadium~O", "DDS Campus~O", 7);
        addEdge("DDS Campus~O", "IGI Airport~O", 8);
        addEdge("Moti Nagar~B", "Rajouri Garden~BP", 2);
        addEdge("Punjabi Bagh West~P", "Rajouri Garden~BP", 2);
        addEdge("Punjabi Bagh West~P", "Netaji Subhash Place~PR", 3);
    }

    // bool haspath(string vname1, string vname2, unordered_map<string,bool> processed){
    //     if(containEdge(vname1, vname2)) return true;

    //     processed[vname1] = true;

    // }
};

class dikstraPair
{
    string vname;
    string psf;
    int cost;

public:
    // Overloading - operator.
    int operator-(dikstraPair o)
    {
        return o.cost - cost;
    }
};

int main()
{
    metro g;
    g.Create_Metro_Map();
    while (true)
    {
        cout << "\t\t\t\t~~LIST OF ACTIONS~~\n\n"
             << endl;
        cout << "1. LIST ALL THE STATIONS IN THE MAP" << endl;
        cout << "2. SHOW THE METRO MAP" << endl;
        cout << "3. GET SHORTEST DISTANCE FROM A 'SOURCE' STATION TO 'DESTINATION' STATION" << endl;
        cout << "4. GET SHORTEST TIME TO REACH FROM A 'SOURCE' STATION TO 'DESTINATION' STATION" << endl;
        cout << "5. GET SHORTEST PATH (DISTANCE WISE) TO REACH FROM A 'SOURCE' STATION TO 'DESTINATION' STATION" << endl;
        cout << "6. GET SHORTEST PATH (TIME WISE) TO REACH FROM A 'SOURCE' STATION TO 'DESTINATION' STATION" << endl;
        cout << "7. EXIT THE MENU" << endl;
        cout << "\nENTER YOUR CHOICE FROM THE ABOVE LIST (1 to 7) : ";

        int choice = -1;
        cin >> choice;
        cout << "\n***********************************************************\n";
        if (choice == 7)
            break;
        switch (choice)
        {
        case 1:
            g.displayStations();
            break;
        case 2:
            g.display_map();
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        default:
            cout << "Please enter a valid option! " << endl;
            cout << "The options you can choose are from 1 to 6. " << endl;
        }
    }
}