class Menus
{
private:
    static int sums;
    int number;
    int price;
    char dish_name[30];
public:
    friend void Customer::order();
    void Search();
    void Set();
    void show();
};
