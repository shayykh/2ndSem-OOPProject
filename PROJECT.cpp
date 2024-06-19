#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Order;
class Restaurant;

class Menu
{
protected:
  vector<string> items;
  vector<float> prices;
  static int size;

public:
  Menu()
  {
    items = {"Curry", "Rice", "Pasta", "Pizza", "Burger"};
    prices = {10.0, 5.0, 15.0, 20.0, 8.0};
  }

  void display()
  {
    cout << "=====================================" << endl;
    cout << "| Item          | Price (Rs) |" << endl;
    cout << "=====================================" << endl;
    for (int i = 0; i < size; ++i)
    {
      cout << "| " << setw(13) << left << items[i] << " | " << setw(10) << fixed
           << setprecision(2) << right << prices[i] << " |" << endl;
    }
    cout << "=====================================" << endl;
  }

  friend float calcBill(Menu &menu, Order &order);

  void add()
  {
    string item;
    float price;
    cout << "Enter the item you would like to add: ";
    cin >> item;

    bool validPrice = false;
    do
    {
      cout << "Enter the item price you would like to add: ";
      cin >> price;
      if (price <= 0)
      {
        cout << "Price must be a positive number. Please try again.\n";
      }
      else
      {
        validPrice = true;
      }
    } while (!validPrice);

    items.push_back(item);
    prices.push_back(price);
  }
};
int Menu::size = 5;

class Employee
{
protected:
  int id;
  string name;
  string phoneNo;
  int age;
  string password;
  double salary;

public:
  Employee() {}
  Employee(int id, string name, string phoneNo, int age, string password) : id(id), name(name), phoneNo(phoneNo), age(age), password(password) {}
  virtual void display() = 0;
  virtual void updateSalary(double newSalary) = 0;
};

class Manager : public Employee 
{
public:
  Manager(string name, string phoneNo, int age, string password) : Employee(1, name, phoneNo, age, password)
  {
    salary = 75000;
  }

  void updateSalary(double newSalary)
  {
    salary = newSalary;
  }

  friend int checkCredentials(Manager m);

  double getSalary() { return salary; }
  void display()
  {
    cout << "Name: " << name << "\nDesignation: Manager" << "\nPhoneNo: " << phoneNo << "\nAge: " << age << endl;
  }
};
class Waiter : public Employee
{
private:
  int orderCount = 0;

public:
  Waiter() {}
  Waiter(int id, string name, string phoneNo, int age, string password) : Employee(id, name, phoneNo, age, password) {}

  void increaseOC()
  {
    ++orderCount;
  }

  void updateSalary(double newSalary)
  {
    salary = newSalary;
  }

  double calcSalary()
  {
    double basic = 18000; // basic Salary for waiters
    double bonus = 0;

    if (orderCount >= 5 && orderCount <= 10)
    {
      bonus = 3000;
    }
    else if (orderCount > 10)
    {
      bonus = 5000;
    }

    salary = basic + bonus;
    return salary;
  }

  void display()
  {
    cout << "Name: " << name << "\nDesignation: Waiter" << "\nPhoneNo: " << phoneNo << "\nAge: " << age << "\nTotal orders taken: " << orderCount << "Salary: " << calcSalary() << endl;
  }
  friend int checkCredentials(Waiter waiters[]);
};

static int empNo = 5;

void DeclareWaiters(Waiter waiters[])
{
  string name[5] = {"John", "Jane", "Alice", "Bob", "Emily"};

  string phone[5] = {"1234567890", "9876543210", "1112223333", "9998887777", "5554443333"};

  int age[5] = {30, 25, 35, 40, 28};

  string password[5] = {"password123", "qwerty", "abcdef", "123456", "password"};

  for (int i = 0; i < 5; i++)
  {
    waiters[i] = Waiter(i, name[i], phone[i], age[i], password[i]);
  }
}

void addEmployee(Waiter waiters[])
{
  string name, phone, password;
  int age;
  cout << "Enter name: ";
  cin >> name;
  cout << "Enter Phone: ";
  cin >> phone;
  cout << "Enter Age: ";
  cin >> age;
  cout << "Enter new password: ";
  cin >> password;
  waiters[empNo] = Waiter(empNo, name, phone, age, password);
  empNo++;
}

int checkCredentials(Manager m)
{
  string name, password;
  cout << "Enter employee name: ";
  cin >> name;
  cout << "Enter employee password: ";
  cin >> password;

  if (name == m.name && password == m.password)
  {
    return 1;
  }

  return -1;
}

int checkCredentials(Waiter waiters[])
{
  string name, password;
  cout << "Enter employee name: ";
  cin >> name;
  cout << "Enter employee password: ";
  cin >> password;

  for (int i = 0; i < empNo; i++)
  {
    if (name == waiters[i].name && password == waiters[i].password)
    {
      return i;
    }
  }

  return -1;
}

class Table
{
  int id;
  int seats;
  bool occupied;

public:
  int getId() { return id; }
  int getSeats() const {
        return seats;
    }

  Table() {}

  Table(int i, int s) : id(i), occupied(false)
  {
    if (s % 2 == 0 && s < 11) // seats always in odd number and less than 11
    {
      seats = s;
    }
    else
    {
      seats = 2;
    }
  }

  bool isEmpty() { return (!occupied); }

  void assigned() { occupied = true; }

  void free() { occupied = false; }
};

void DeclareTable(Table tables[])
{
  int id = 0;
  for (int i = 0; i < 4; i++) // declaring 2 seats table
  {
    tables[id] = Table(id, 2);
    id++;
  }
  for (int i = 0; i < 4; i++) // 4 seats
  {
    tables[id] = Table(id, 4);
    id++;
  }
  for (int i = 0; i < 4; i++) // 6 seats
  {
    tables[id] = Table(id, 6);
    id++;
  }
  for (int i = 0; i < 4; i++) // 8 seats
  {
    tables[id] = Table(id, 8);
    id++;
  }
  for (int i = 0; i < 2; i++) // 10 seats
  {
    tables[id] = Table(id, 10);
    id++;
  }
}


int assignTable(Table tables[], int n) {
    if (n > 10) {
        cout << "Sorry! Table not availabe for this number of people\n";
        return -1;
    }

    if (n % 2 != 0) {
        n += 1; // rounding off n
    }

    for (int i = 0; i < 18; ++i) {
        if (tables[i].isEmpty() && tables[i].getSeats() >= n) {
            tables[i].assigned();
            cout << "Your table is: " << tables[i].getId() << endl;
            return tables[i].getId();
        }
    }

    cout << "All Tables are busy!\n";
    return -1;
}

class Order
{
private:
  string *items;
  int *quantity;
  int size;
  int tableNo;

public:
  float bill = 0;
  Order() {}
  Order(int n, int table)
  {
    tableNo = table;
    size = n;
    items = new string[n];
    quantity = new int[n];
    cout << "Enter the items ordered by the customer along with the quantity: "
         << endl;

    for (int i = 0; i < n; i++)
    {
      cout << "Item " << i + 1 << ": \n";
      cout << "name: ";
      cin >> items[i];
      cout << "quantity: ";
      cin >> quantity[i];
    }
  }
  int getTableNo() { return tableNo; }
  float getBill() { return bill; }
  friend float calcBill(Menu &menu, Order &order);
  friend double calctotalIncome(Restaurant &R, Order orders[]);

  ~Order()
  {
   // delete[] items;
   // delete[] quantity;
  }
}; // end of order class

class Restaurant
{
protected:
  double totalIncome;
  double InventoryCost = 210000; // Estimated cost of inventory
  const int utilityBill = 50000; // Estimated monthly utility expenses
  double tax;
  double totalSalary;
  double totalProfit;

public:
  Menu *menu;
  Restaurant(Menu *m)
  {
    menu = m;
  }
  friend double calctotalIncome(Restaurant &R, Order orders[]);
  double calcTotalSalary(Waiter waiters[])
  {
    double total = 0;
    for (int i = 0; i < empNo; i++)
    {
      total += waiters[i].calcSalary();
    }

    totalSalary = total;
    return total;
  }

  double calcTax()
  {
    return totalIncome * 0.2; // 20% overall taxes
  }

  double calcTotalProfit()
  {
    totalProfit = totalIncome - calcTax() - utilityBill -
                  totalSalary;
    return totalProfit;
  }

  void displayExpenses()
  {
    cout << "EXPENSES: \n";
    cout << "Inventory cost: " << InventoryCost << "\nUtlity bills: " << utilityBill << endl;
  }
};

static int orderNo = 0;

float calcBill(Menu &menu, Order &order)
{
  for (int i = 0; i < order.size; i++)
  {
    for (int j = 0; j < menu.items.size(); j++)
    {
      if (order.items[i] == menu.items[j])
      {
        order.bill += (menu.prices[j] * order.quantity[i]);
        break;
      }
    }
  }

  return order.bill;
}

double calctotalIncome(Restaurant &R, Order orders[])
{
  int ti = 0;
  for (int i = 0; i < orderNo; i++)
  {
    ti += orders[i].bill;
  }

  R.totalIncome = ti + 750000; // this amt as income of whole month
  return R.totalIncome;
}

int main()
{

  Menu menu;
  Restaurant HalalGuyz(&menu);
  Manager manager("Faizan", "03218207972", 19, "abcx123");
  Waiter waiters[10];
  DeclareWaiters(waiters);
  Table tables[18];
  DeclareTable(tables);
  Order orders[20];
  int choice;
  bool z=true;
  while(z==true){
  cout << "Welcome To ABC" << endl;
  cout << "Would you like to deal with orders or look into technicalities?(1: order,2: resturant details,3: Exit): ";
  cin >> choice;

try{
    if(choice!=1 && choice!=2 && choice !=3){
        throw(0);
    }
    else{
  switch (choice)
  {
  case 1:
  {
    int waiterId = checkCredentials(waiters);
    if (waiterId == -1)
    {
      break;
    }
    cout << "For New Customers: \n1: dine-in  2: takeaway\n"
         << endl
         << "For present Customers: \n3.Generate Bill\n";
    cin >> choice;
    if (choice == 1)
    {
      HalalGuyz.menu->display();
      int personCount;
      cout << "Enter count of persons: ";
      cin >> personCount;
      cout << "Finding table... \n";
      int tableId = assignTable(tables, personCount);
      if (tableId == -1)
      {
        break;
      }

      int n;
      cout << "Enter the number of items\n";
      cin >> n;
      cout << "Order No #" << orderNo << endl;
      orders[orderNo++] = Order(n, tableId);
    }
    else if (choice == 2)
    {
      HalalGuyz.menu->display();
      int n;
      cout << "Enter the number of items\n";
      cin >> n;
      cout << "Order No #" << orderNo << endl;
      // -1 table No for takeaway orders
      orders[orderNo++] = Order(n, -1);
      cout << "Bill of this Takeaway Order is: " << calcBill(menu, orders[orderNo - 1]) << endl;
    }
    else if (choice == 3) // Bill calc only for Dine-in
    {
      int orderNumber;
      cout << "Enter Order no: ";
      cin >> orderNumber;
      cout << "Bill of order " << orderNumber << " is: " << calcBill(menu, orders[orderNumber]) << endl;
      waiters[waiterId].increaseOC();
      tables[orders[orderNumber].getTableNo()].free();
    }
  }
  break;

  case 2:
  {
    if (checkCredentials(manager) == -1)
    {
      break;
    }

    int ch;
    cout << "Would you like to:\n 1.View all employee details \n 2.Add item to the menu \n 3.Add an employee \n 4.View Salary \n 5. Restaurant Expenses and Profit"
         << endl;
    cin >> ch;
    if (ch == 1)
    {

      for (int i = 0; i < empNo; i++)
      {
        waiters[i].display();
        cout << endl;
      }
    }
    else if (ch == 2)
    {
      menu.add();
    }
    else if (ch == 3)
    {
      addEmployee(waiters);
    }
    else if (ch == 4)
    {
      cout << "Manager's Salary: " << manager.getSalary() << endl;
      for (int i = 0; i < empNo; i++)
      {
        cout << "Salary of Waiter " << i + 1 << " is: " << waiters[i].calcSalary() << endl;
      }
    }
    else if (ch == 5)
    {
      HalalGuyz.displayExpenses();
      cout << "Total Income: " << calctotalIncome(HalalGuyz, orders) << endl
           << "Total Tax: " << HalalGuyz.calcTax() << endl
           << "Total Salaries: " << HalalGuyz.calcTotalSalary(waiters) << endl
           << "Total Profit: " << HalalGuyz.calcTotalProfit() << endl;
    }
  }
  break;
  case (3):
   z=false;
   break;
  default:
    break;
  } 
  }}
  catch(...){
    cout<<"Incorrect input";
  }
 
  }
   exit(0);
  return 0;
  }