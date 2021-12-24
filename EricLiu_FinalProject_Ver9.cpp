/*
Eric Liu
FInal Project - Ramen Shop Summary App
ICS4U - 03
Dr.N
*/

#include <iostream>
#include <exception>
#include <stdexcept>
#include <iomanip>
using namespace std;

class Ramen //declares base class Ramen
{
private:  //declares private member variables
    string name;
    string contactNum;

public:
    //declares public variables for earning calculations
    double basePrice;
    double bill;
    static double totalEarning;

    void inputInfo() //member function that inputs basic information for the customer when a subclass constructor is invoked
    {
        cout << "Enter the name of customer: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter the phone number of customer: ";
        cin >> contactNum;
    }

    //static function that can be used anywhere in the program to test the character type input validity
    //ab are the default, correct input characters. Letter c would be the user's input, to test if the input is valid
    static void charValidity(const char &a, const char &b, char &c)
    {
        while(c != a && c != b) //while loop that keeps prompting user for input until the correct input is made
        {
            cout << "Invalid input, please input a character from the available choices: ";
            cin >> c;
            c = toupper(c);
        }
    }

    //function that tests the integer input validity, and returns the matching bool statement for the integer inputted
    bool intValidity(int &i)
    {
        while(i != 1 && i != 0)
        {
            cout << "The digit inputted is not 1 or 0, please re-enter:";
            cin >> i;
        }
        if(i == 1)
            return true;
        else
            return false;
    }

    //virtual function for displaying the order
    virtual void displayOrder()
    {
        cout << "Ramen sold";
    }

    //function that displays the customer's basic information
    void displayInfo()
    {
        cout << "Name: " << name << endl;
        cout << "Phone number: " << contactNum << endl;
    }

    //function that prints if toppings are added to the orders
    void additionalToppings(const int &i, const string &toppingName)
    {
        if(i == 1)
            cout << "Additional Topping: " << toppingName;
        else
            cout << "No Additional Toppings";
    }

    //static function that is designed to throw an exception when a non-numeric character is inputted instead of int type
    static void isNumeric(int &i)
    {
        while(cin.fail()) //keeps prompting the user for input until the right type of input is made
        {
            try{
                throw runtime_error("Error: This input is not a numeric value");
            }
            catch(runtime_error &msg){
                cout << "\n++++++++++++++++++++++++++++++++++++++++++" << endl;
                cout << msg.what() << endl;
                cout << "++++++++++++++++++++++++++++++++++++++++++" << endl;
            }
            cin.clear();
            cin.ignore();
            cout << "Please input again: ";
            cin >> i;
        }
    }
};

class Tonkotsu : public Ramen  //declares the subclass Tonkotsu, a type of ramen
{
private:  //declares private variables for this subclass
    char style;
    int tamago;  //also named egg in English

public:
    Tonkotsu()  //declares the subclass constructor that sets all the attributes of the Tonkotsu Ramen order
    {
        inputInfo();  //calls the base class function to input basic information
        basePrice = 14.99;  //sets the base price

        cout << "Style of Tonkotsu Ramen (input O for original, R for Red): ";
        cin >> style;
        style = toupper(style);
        Ramen::charValidity('O', 'R', style);  //tests the input validity for the style of ramen

        cout << "Extra tamago(egg) topping? (input 1 for yes - $2.50 extra, 0 for no): ";
        cin >> tamago;
        Ramen::isNumeric(tamago);  //tests the input validity for extra egg topping(int)

        if(Ramen::intValidity(tamago))   //if the input is valid and 1 is entered, additional price is added
            bill = basePrice + 2.50;
        else  //if input is valid but 0 is entered, no additional price is added
            bill = basePrice;

        Ramen::totalEarning += bill;  //adds the current bill to the overall earning
    }

    void displayOrder()  //overridden function that displays the order for Tonkotsu
    {
        displayInfo();  //displays basic information

        //displays particular attributes of the ramen
        cout << "Ramen type: " << "Tonkotsu ";
        if(style == 'O')
            cout << "Original " << endl;
        else
            cout << "Red" << endl;

        additionalToppings(tamago, "Tamago");  //prints if additional cost is added

        cout << "\nThe total bill for this customer is: $" << bill << endl;
    }
};

class Shoyu : public Ramen  //declares the subclass Shoyu, another type of ramen
{
private:  //declares private variables for this subclass
    char baseBroth;
    int karaage;  //fried chicken in other words

public:
    Shoyu() //declares the subclass constructor that sets all the attributes of the Shoyu Ramen order
    {
        inputInfo();  //calls the base class function to input basic information of customer
        basePrice = 11.99;  //setting the base price

        cout << "Type of base used for the broth(C for chicken, P for pork): ";
        cin >> baseBroth;
        baseBroth = toupper(baseBroth);
        Ramen::charValidity('C', 'P', baseBroth);   //tests the input validity for the base broth of ramen

        cout << "Extra karaage(fried chicken) as topping? (Input 1 for yes  - $3.50 extra, 0 for no) ";
        cin >> karaage;
        Ramen::isNumeric(karaage);  //tests the input validity for extra karaage topping(int type)

        if(Ramen::intValidity(karaage))   //if the input is valid and 1 is entered, additional price is added
            bill = basePrice + 3.50;
        else   //if the input is valid and 0 is entered, no additional cost
            bill = basePrice;

        Ramen::totalEarning += bill; //adds the bill to total earning
    }

    void displayOrder()  //overridden function that displays the order for Shoyu
    {
        displayInfo();  //display basic information

        cout << "Ramen type: " << "Shoyu ";  //displays particular attributes of the shoyu ramen
        if(baseBroth == 'C')
            cout << "Chicken" << endl;
        else
            cout << "Pork" << endl;

        additionalToppings(karaage, "Karaage");  //prints if a topping is added
        cout << "\nThe total bill for this customer is: $" << bill << endl;
    }
};
double Ramen::totalEarning = 0;

int main()
{
    int Counter = 0;  //counts how many orders are created
    int firstDeletion = 0;  //if the first deletion is index 0, the next order 1 deletion's index is shifted 1 to the right
    char ramenType;
    bool running = true;
    int option;

    cout << "Welcome to the Ramen Shop Summary App!" << endl;

    Ramen *orders[100];  //declares an object pointers array that holds a total of 100 object pointers
    for(int i = 0; i < 100; i++)  //initialize all object pointers to nullptr
        orders[i] = nullptr;

    while(running)  //keep iterating until user quits
    {
        cout << "\n--------------Options Menu--------------" << endl;
        cout << "1. Add Customer Bill" << endl << "2. Remove Customer Bill" << endl;
        cout << "3. Display Customer Bills" << endl << "4. Quit" << endl;
        cout << "\nPlease enter a command: ";

        cin >> option;
        while((option < 1 || option > 4) || cin.fail())  //tests the input validation
        {
            if(cin.fail())
                Ramen::isNumeric(option);  //if a string or character is inputted instead of int, throw exception

            else  //if input is out of range
            {
                cout << "\nThis is not a valid command, please enter again: ";
                cin >> option;
            }
        }

        if(option == 1)  //if option is 1
        {
            cout << "\n---------------------------------------------------------------------------" << endl;
            cout << right << setw(45) << "Adding Customer Bills" << endl;
            cout << "---------------------------------------------------------------------------" << endl;

            cout << "\nPlease input type of ramen purchased(T for Tonkotsu - $14.99, S for Shoyu - $11.99): ";
            cin >> ramenType;
            ramenType = toupper(ramenType);
            Ramen::charValidity('T', 'S', ramenType);  //tests if the input validity for type of ramen is valid

            //if and else statements that reassigns the address of object pointer according to user input
            if(ramenType == 'T')
                orders[Counter] = new Tonkotsu();
            else
                orders[Counter] = new Shoyu();

            Counter++; //increment Counter
        }

        if(option == 2)  //if option is 2
        {
            cout << "\n---------------------------------------------------------------------------" << endl;
            cout << right << setw(45) << "Deleting Customer Bills" << endl;
            cout << "---------------------------------------------------------------------------" << endl;

            int index;
            cout << "Which order do you wish to delete? ";
            cin >> index;

            //keep asking for re-enter until the inputted order number is numeric and between 1 to 100
            while((index < 1 || index > 100) || cin.fail())
            {
                if(cin.fail())  //if non numeric value is entered, throw exception
                    Ramen::isNumeric(index);

                else //since only 100 object pointers are held in the array, inputs bigger than 100 or smaller than 1 are not available
                {
                    cout << "This order is not available, please re-enter: ";
                    cin >> index;
                }
            }
            //converts user input into the matching element/index number
            index = index - 1 + firstDeletion;

            while(orders[index] == nullptr) //keeps adding the index until the next non-null pointer is found
            {
                index++;
                try{       //if up until index 99 there is still no available order to remove, then the object pointers array must have held
                             //an amount of non-NULL pointers that are less than the amount indicated by the value of index.

                    if(index == 99)  //the order will be deemed unavailable to remove and throws exception
                        throw string("\nThis order is not available to delete");
                }
                catch(string &msg){   //catches the exception and outputs the message
                    cout << msg  << endl;
                    break;
                }
            }
            if(orders[index] != nullptr)  //if the inputted index has a pointer with non-NULL address
            {
                if(index == 0)
                    //if you removed the first order (the first object pointer or index 0 of the array) initially,
                    //the next order 1 to remove is the object pointer after index 0.
                    firstDeletion = 1;

                Ramen::totalEarning -= orders[index] -> bill;  //removes the particular bill from the total earning
                orders[index] = nullptr;  //reassign the object pointer to 0 address
                cout <<  "\n++++++++++++++++++++++++++++++++++++++++" << endl;
                cout << "The order has been successfully removed" << endl;
                cout << "++++++++++++++++++++++++++++++++++++++++" << endl;
            }
        }

        if(option == 3)  //if inputted option is 3
        {
            cout << "\n---------------------------------------------------------------------------" << endl;
            cout << right << setw(45) << "Displaying Customer Bills" << endl;
            cout << "---------------------------------------------------------------------------" << endl;

            int orderNum = 1;
            int numOfNULL = 0;
            for(int i = 0; i < 100; i++)  //loops through the object pointers array and displays all available orders
            {
                if(orders[i] != nullptr)  //prints the order if the object pointer is non-NULL
                {
                    cout << "\nOrder #" << orderNum << endl;
                    orders[i] -> displayOrder();  //calls the function to display the order
                    cout << "\n--------------------------------------------------------" << endl;
                    ++orderNum;
                }
                else
                    numOfNULL++;

                //when all pointers in the array are nullptrs, then there are no orders
                if(numOfNULL == 100)
                {
                    cout << "\n+++++++++++++++++++++++++++++" << endl;
                    cout << "There are currently no orders" << endl;
                    cout << "+++++++++++++++++++++++++++++" << endl;
                    continue;
                }
            }
        }

        if(option == 4)  //if option is 4
        {
            cout << "---------------------------------------------------------------------" << endl;
            cout << "\nThe total earning from the bills is $" << Ramen::totalEarning << endl;  //prints the total earning
            cout << "\nThank you for using the Ramen Shop Summary App!" << endl;
            running = false;
            for(int i = 0; i < 100; i++) //delete the allocated memory of each object pointer
                delete orders[i];
            delete []*orders;  //delete the allocated memory of the object pointers array
        }
    }
    return 0;
}
