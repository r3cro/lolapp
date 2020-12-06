#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <ostream>
using namespace std;

//created these incase they are in some wack order and can't run
void menu();
void removeBed();
void createBed();
void listBeds();
void save();
void load_data();

//create a bed structure to be cool
struct Bed {
    int bed_id; // hospital room/bed number
    string bed_location; // hospital name
    string hospital_phone_number;
};

static vector<Bed> vect; // this is where i will be storing all data while the program is running
static int running = 1; // used to keep program running until exiting through the menu

void createBed() {

    int id;
    string location, phone;

    cout << "Enter Bed ID: \n";
    cin >> id;
    cout << "Enter Bed Location: \n";
    cin >> location;
    cout << "Enter Contact Phone Number: \n";
    cin >> phone;

    vect.push_back({id, location, phone});
}

void removeBed() {
    int line;
    cout << "Enter the bed you want to delete from the system.\n";
    cin >> line;
    if(line==0) { // prevents people from removing line 0 - does weird stuff if its removed
        cout << "You can not delete the template bed\n";
        menu();
        return;
    }
    vect.erase(vect.begin() + line);
}

void listBeds() { //lists all beds that are currently in memory, with the nth line in front of each bed so you know what you're removing quickly
    int s = vect.size();
    for(int i=0;i<s;i++) {
        cout << i  << ": "<< vect[i].bed_id << ", " << vect[i].bed_location << ", " << vect[i].hospital_phone_number << endl;
    }
}

void load_data() { // gets all the available beds from file and loads them into memory
    int bedid;
    string bedloc;
    string bedphone;

    ifstream dataFile;
    dataFile.open("output.txt", ios::in);

    if(dataFile.peek()==ifstream::traits_type::eof()) { //creates template bedsetup (if file is empty) to give an example when running program and to scare code bugs away
        vect.push_back({0, "Template", "777-777-7777"});
    }

    while(dataFile.is_open() && !dataFile.eof()) {
        dataFile >> bedid >> bedloc >> bedphone;

        Bed tempBed; //getting data from file and storing it in temp variables to put into vector
        tempBed.bed_id = bedid;
        tempBed.bed_location = bedloc;
        tempBed.hospital_phone_number = bedphone;

        vect.push_back(tempBed);
    }
    dataFile.close();
    ofstream ofs;
    ofs.open("output.txt", ofstream::out | ofstream::trunc);
    ofs.close();
}

void save() { // saves vector from memory into a file in order to retain empty beds after program restart
    ofstream output_file ("output.txt", ios::app | ios::in | ios::out);
    if(output_file.is_open()) {
        int s = vect.size();
        cout << s;
        for(int i=0;i<s;i++) {
            output_file << endl << vect[i].bed_id << " " << vect[i].bed_location << " " << vect[i].hospital_phone_number;
        }
        output_file.close();
    }
}

void menu() { //landing page, allowing for selection choosing
    cout << "Vestigia >> Home Page\n";
    cout << "Pick an option 1-5.\n";
    cout << "1. Create an empty bed listing\n";
    cout << "2. Remove an empty bed listing\n";
    cout << "3. List all empty bed listings;\n";
    cout << "4. Exit\n";

    int option;
    cin >> option;

    //SWITCH INSTEAD OF ELSE IF BECAUSE ELSE IF IS HARDER TO READ AND LOOKS UGLY--also not using bool values for my selection choosing so switch works better in this situation, also allows for a response to any wrong answer
    switch (option) {
        case 1:
            cout << "Creating bed\n";
            createBed();
            break;
        case 2:
            cout << "Removing bed\n";
            removeBed();
            break;
        case 3:
            cout << "Listing beds\n";
            listBeds();
            break;
        case 4:
            cout << "Exiting program\n";
            running = 0;
            break;
        default: // incase there is a typo or a wrong number is entered restarts the option choosing process.
            cout << "Invalid option\n";
            menu();
            break;
    }
}

int main() {
    load_data(); // load all data stored into output.txt into a new vector for editing
    while (running == 1) { //makes sure the program stays running even after you finish a task
        menu();
    }
    save(); // save current vector into ouput.txt
    return 0;
}