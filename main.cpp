#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;

// === PART 1: TYPEDEF, ENUM, STRUCTS ===
typedef double Dollars;//creates the alias for data type double dollars

enum Brand { NIKE, ADIDAS, NEW_BALANCE, PUMA, OTHER };//creates the enum for the minimum required shoes

string brandToString(Brand b) {//this switch case statement takes the values from the enum and changes them into a string based on the case given
    switch (b) {
        case NIKE: return "NIKE";
        case ADIDAS: return "ADIDAS";
        case NEW_BALANCE: return "NEW_BALANCE";
        case PUMA: return "PUMA";
        case OTHER: return "OTHER";
        default: return "UNKNOWN";
    }
}

struct Sneaker { //creates the class/struct for the Sneakers. Inside there is all the sneaker info
    Brand brand;
    string model;
    Dollars resalePrice;
    int condition; // from 1 to 10 
    string releaseDate;
};

// === Function Prototypes === none of these functions have been defined yet, only created. explained later
//THE VOID FUNCTIONS DO NOT RETURN ANYTHING
void inputSneaker(Sneaker& s);//lets you input the amount of sneakers you have in a for loop that comes later
void printSneaker(const Sneaker& s, int index);//outputs your sneakers 
void wearSneaker(Sneaker& s);//adds the wear condition to the sheo price
double averageResale(const Sneaker sneakers[], int count);//average the resale value of all your shoes
int countMintCondition(const Sneaker sneakers[], int count);//used to count the amounf of muint condition shoes in your list
int findMostValuable(const Sneaker sneakers[], int count);//searches all your shoes for the priciest one
void exportCollection(const Sneaker sneakers[], int count, const string& filename);//exports your collection to a txt file
void searchSneaker(const Sneaker sneakers[], int count, const string& keyword);// lets you search for sneakers

int main() {

    const int MAX_SNEAKERS = 10;
    Sneaker sneakers[MAX_SNEAKERS];//creates an array in the Sneaker Struct bassed on the amount of max sneakers the user imported
    int sneakerCount;

    cout << "How many sneakers do you want to enter (max 10)? ";
    cin >> sneakerCount;
    cin.ignore(); // flush newline

    for (int i = 0; i < sneakerCount; ++i) {//loop that allows the user to onput sneakers based on their sneakercount entered earlier
        cout << "\nEnter sneaker #" << (i + 1) << ":\n";
        inputSneaker(sneakers[i]);
    }

    // === DISPLAY INVENTORY ===
    cout << "\n=== INVENTORY ===\n";
    for (int i = 0; i < sneakerCount; ++i) {
        printSneaker(sneakers[i], i + 1);
    }

    int valuableIndex = findMostValuable(sneakers, sneakerCount);
    cout << "\nMost Valuable: " << sneakers[valuableIndex].model
         << " at $" << fixed << setprecision(2) << sneakers[valuableIndex].resalePrice << endl;

    cout << "Average Price: $" << fixed << setprecision(2)
         << averageResale(sneakers, sneakerCount) << endl;

    cout << "Mint Sneakers: " << countMintCondition(sneakers, sneakerCount) << endl;

    // === SIMULATE WEAR ===
    char wear;
    cout << "\nApply wear simulation? (y/n): ";
    cin >> wear;

    if (tolower(wear) == 'y') {
        for (int i = 0; i < sneakerCount; ++i)
            wearSneaker(sneakers[i]);

        cout << "\nAfter wear...\nCondition of all sneakers reduced by 1\nPrice dropped by 5%\n";

        cout << "\n=== UPDATED INVENTORY ===\n";
        for (int i = 0; i < sneakerCount; ++i) {
            printSneaker(sneakers[i], i + 1);
        }
    }

    // === BONUS: SEARCH ===
    cin.ignore(); // flush newline
    string keyword;
    cout << "\nSearch sneakers by model name keyword (or press Enter to skip): ";
    getline(cin, keyword);
    if (!keyword.empty()) {
        searchSneaker(sneakers, sneakerCount, keyword);
    }

    // === BONUS: FILE EXPORT ===
    char exportOpt;
    cout << "\nExport collection to file? (y/n): ";
    cin >> exportOpt;
//converts the Y character to lowercase so it is case insensitive, then exports
    if (tolower(exportOpt) == 'y') {
        exportCollection(sneakers, sneakerCount, "SneakerCollection.txt");
        cout << "Exported to SneakerCollection.txt\n";
    }

    return 0;
}

// === Function Definitions ===
void inputSneaker(Sneaker& s) {
    int brandInput;
    cout << "Select a brand: 0-NIKE, 1-ADIDAS, 2-NEW_BALANCE, 3-PUMA, 4-OTHER: ";
    cin >> brandInput;
    s.brand = static_cast<Brand>(brandInput);

    cin.ignore(); // flush newline
    do {
        cout << "Model: ";
        getline(cin, s.model);
        if (s.model.length() > 30)
            cout << "Model name too long. Max 30 characters.\n";
    } while (s.model.length() > 30);

    cout << "Resale Price: ";
    cin >> s.resalePrice;

    do {
        cout << "Condition (1–10): ";
        cin >> s.condition;
        if (s.condition < 1 || s.condition > 10)
            cout << "Invalid. Enter between 1 and 10.\n";
    } while (s.condition < 1 || s.condition > 10);

    cin.ignore(); // flush newline
    cout << "Release Date (MM/DD/YYYY): ";
    getline(cin, s.releaseDate);
}

void printSneaker(const Sneaker& s, int index) {
    cout << left << setw(3) << index
         << setw(12) << brandToString(s.brand)
         << setw(30) << s.model.substr(0, 29)
         << "$" << right << setw(7) << fixed << setprecision(2) << s.resalePrice << "  "
         << setw(3) << s.condition << "   "
         << s.releaseDate << endl;
}

void wearSneaker(Sneaker& s) {
    if (s.condition > 1) s.condition--;
    s.resalePrice *= 0.95; // depreciate by 5%
}

double averageResale(const Sneaker sneakers[], int count) {
    double sum = 0;
    for (int i = 0; i < count; ++i)
        sum += sneakers[i].resalePrice;
    return sum / count;
}

int countMintCondition(const Sneaker sneakers[], int count) {
    int mint = 0;
    for (int i = 0; i < count; ++i)
        if (sneakers[i].condition == 10) mint++;
    return mint;
}

int findMostValuable(const Sneaker sneakers[], int count) {
    int index = 0;
    for (int i = 1; i < count; ++i)
        if (sneakers[i].resalePrice > sneakers[index].resalePrice)
            index = i;
    return index;
}

void exportCollection(const Sneaker sneakers[], int count, const string& filename) {
    ofstream file(filename.c_str());
    file << "Sneaker Collection Export\n\n";
    for (int i = 0; i < count; ++i) {
        file << (i + 1) << ". " << brandToString(sneakers[i].brand)
             << " | " << sneakers[i].model
             << " | $" << fixed << setprecision(2) << sneakers[i].resalePrice
             << " | Condition: " << sneakers[i].condition
             << " | Released: " << sneakers[i].releaseDate << endl;
    }
    file.close();
}

void searchSneaker(const Sneaker sneakers[], int count, const string& keyword) {
    cout << "\nSearch Results for \"" << keyword << "\":\n";
    bool found = false;
    for (int i = 0; i < count; ++i) {
        if (sneakers[i].model.find(keyword) != string::npos) {
            printSneaker(sneakers[i], i + 1);
            found = true;
        }
    }
    if (!found) {
        cout << "No sneakers found matching that keyword.\n";
    }
}
