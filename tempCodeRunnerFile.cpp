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
    while (!file2.eof()){
        drink d;
        d.readDrink(file2);
    }
    file2.close();
}