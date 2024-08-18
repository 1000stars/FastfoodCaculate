#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class order
{
protected:
    string name;
    float baseprice;
};

class drink : protected order
{
private:
public:
    drink() = default;
    drink(string Name, float Price)
    {
        name = Name;
        baseprice = Price;
    }
    // Getter
    string getName() { return name; }
    float getbaseprice() { return baseprice; }
    void addDrink(ofstream &outfille);
    void readDrink(ifstream &infile);
};

void drink::addDrink(ofstream &outfile)
{
    outfile.write(name.c_str(), sizeof(name));
    outfile.write(reinterpret_cast<char *>(&baseprice), sizeof(baseprice));
}

void drink::readDrink(ifstream &infile)
{
    char buffer[50];
    infile.read(buffer, sizeof(name));
    infile.read(reinterpret_cast<char *>(&baseprice), sizeof(baseprice));
}

class food : protected order
{

public:
    food() = default;
    food(string Name, float Price)
    {
        name = Name;
        baseprice = Price;
    }
    string getName() { return name; }
    float getbaseprice() { return baseprice; }
    void addFood(ofstream &outfile);
    void readFood(ifstream &infile);
};

void food::addFood(ofstream &outfile)
{
    outfile.write(name.c_str(), sizeof(name));
    outfile.write(reinterpret_cast<char *>(&baseprice), sizeof(baseprice));
}

void food::readFood(ifstream &infile)
{
    char buffer[50];
    infile.read(buffer, sizeof(name));
    infile.read(reinterpret_cast<char *>(&baseprice), sizeof(baseprice));
}

void admin();
void update();             // use in admin function
void add(vector<food> &a); // use in update function
void add(vector<drink> &b);
void changeMenu(); // use in update funtion

void menufood();
void menudrink();

void readfromfile();
vector<food> f;
vector<drink> d;

int main()
{
    int choice;
    char x;
    readfromfile();

    do
    {
        cout << "1. Order" << endl;
        cout << "2. Admin" << endl;

        cout << "Enter choice: ";
        cin >> x;

        switch (x)
        {
        case '1':
            break;
        case '2':
            admin();

            break;
        default:
            cout << "Please try again" << endl;
        }
        cout << "Press any key to continue or n to close app\n ";
        cin >> x;
    } while (x != 'n');
}

void readfromfile()
{
    ifstream file1;
    file1.open("FoodMenu.txt", ios::in | ios::binary);
    while (!file1.eof())
    {
        food f;
        f.readFood(file1);
    }
    file1.close();

    ifstream file2;
    file2.open("DrinkMenu.txt", ios::in | ios::binary);
    while (!file2.eof())
    {
        drink d;
        d.readDrink(file2);
    }
    file2.close();
}

void menufood()
{
    for (int i; i < f.size(); ++i)
    {
        cout << f.at(i).getName() << "\t" << f[i].getbaseprice();
    }
}
void menudrink()
{
    for (int i = 0; i < d.size(); i++)
    {
        cout << d.at(i).getName() << "\t" << d[i].getbaseprice();
    }
}
void admin()
{
    ifstream file;
    string password, pass;
    cout << "Password: ";
    cin >> password;
    file.open("password.txt");
    while (file >> pass)
    {
        if (password != pass)
        {
            return;
        }
    }
    file.close();
    update();
}

void update()
{
    char choice;
    do
    {
        cout << "1. Add food and drink" << endl;
        cout << "2. Change menu " << endl;
        cout << "3. Exit\n\n";
        cout << "ENTER CHOICE: ";
        cin >> choice;

        switch (choice)
        {
        case '1':
            cout << "Food or drink  f/d ";
            cin >> choice;
            if (choice == 'f')
            {
                add(f);
            }
            else if (choice == 'd')
            {
                add(d);
            }
            else
            {
                cout << "Please try a again!!" << endl;
            }
            break;
        case '2':
            break;
        }
    } while (choice != '3');
}

void add(vector<food> &a)
{
    cout << "Name: ";
    string name;
    getline(cin, name);
    cout << "Price";
    float price;
    cin >> price;
    ofstream file1;
    file1.open("FoodMenu.txt", ios::app | ios::binary);
    if (!file1.is_open())
    {
        cout << "Error opening file for writing" << endl;
        return;
    }
    food(name, price).addFood(file1);
    file1.close();
    a.push_back(food(name, price));
}

void add(vector<drink> &b)
{
    cout << "Name: ";
    string name;
    getline(cin, name);
    cout << "Price";
    float price;
    cin >> price;
    ofstream file2;
    file2.open("DrinkMenu.txt", ios::app | ios::binary);
    if (!file2.is_open())
    {
        cout << "Error opening file for writng";
        return;
    }
    drink(name, price).addDrink(file2);
    file2.close();
    b.push_back(drink(name, price));
}
