class Customer : public Person
{
private:
    int desk;
    char dishes[20];
    int queues;
    char write_evaluate[200];
    static int total;
public:
    Customer();
    void order();
    void write();

};
