#include <iostream>
#include<string>
#include<windows.h>
using namespace std;
void setTextColor(int textcolor , int background) 
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, ( background <<4) | textcolor);
}
void clearScreen()
{
	system(" cls");
}

  const int MAX_CATEGORIES = 5;  //  no. of categories in the menu
  const int MAX_DISHES = 7;      //  number of dishes per category

// structure made for name and price of the items
struct Dish
 {
    string name;
    double price;
};

// Structure for category detail
struct Category
 {
    string name;
    Dish dishes[MAX_DISHES];  // Array of dishes in this category
    int dishnum;  // Number of dishes in this category
};

// Function to display categories
void displayCategories(const Category categories[], int categoryCount)
 {
    cout << "==== WELCOME TO OUR RESTAURANT ====" <<endl;
    cout << " :Food Categories: " <<endl;
    for (int i = 0; i < categoryCount; i++)
	 {
        cout << i + 1 << ". " << categories[i].name <<endl;
    }
    cout << "==================================";
    cout<<endl;
}

// Function to display dishes of a specific category
void displayDishes(const Category categories[], int categoryIndex)
 {
    cout << "Here are the dishes in the selected category: " <<endl;
    for (int i = 0; i < categories[categoryIndex].dishnum; i++) 
	{
        cout << i + 1 << ". " << categories[categoryIndex].dishes[i].name
             << " ( pkr " << categories[categoryIndex].dishes[i].price << ") " <<endl;
    }
}

// Function to take an order
void processOrder(const Category categories[], int categoryCount)
 {
    int categoryChoice, dishChoice;
    double total = 0;

    // Display categories
    displayCategories(categories, categoryCount);

    cout << "Enter the category number: ";
    cin >> categoryChoice;

    if (categoryChoice < 1 )
	 {
        cout << "Invalid category. try again " <<endl;
        
        return;
    }
    int categoryIndex = categoryChoice - 1; // use as array index is 0

    // Display dishes in the selected category
    displayDishes(categories, categoryIndex);

    while (true) 
	{
        cout << " Enter the dish number you want to add in your order (0 to finish)  " <<endl;
        cin >> dishChoice;

        if (dishChoice == 0) 
		break;   // to end the condition 

        if (dishChoice < 1 ) 
		{
            cout << "Invalid dish. Please try again " <<endl;
        } 
		else
		 {
            int quantity;
            cout << "Enter quantity for " << categories[categoryIndex].dishes[dishChoice - 1].name << " = ";
            cin >> quantity;
            if (quantity > 0)
			 {
                double itemTotal = quantity * categories[categoryIndex].dishes[dishChoice - 1].price;
                  total += itemTotal;
                cout << quantity << " x " << categories[categoryIndex].dishes[dishChoice - 1].name 
                << " added to your order. total bill =  pkr " << itemTotal <<endl;
            } 
			else
			 {
                cout << "Invalid quantity. Please try again " <<endl;
            }
        }
    }

    cout << "==== Order Summary ==== " <<endl;
    cout << "Total: pkr " << total <<endl;
}

// Function to add a category
void addCategory(Category categories[], int& categoryCount)
 {
    if (categoryCount>= MAX_CATEGORIES) 
	{
        cout << "Category limit reached!further categories cant be added " <<endl;
        
        return;
    }
    cout << "Enter the name of the new category: ";
    cin >> categories[categoryCount].name;
    categories[categoryCount].dishnum = 0;  // Initialize dish count to 0
    categoryCount++;
    cout << "Category added successfully " <<endl;
}

// Function to delete a category
void deleteCategory(Category categories[], int& categoryCount) 
{
    if (categoryCount <= 0) {
        cout << "No categories available to delete " <<endl;
        return;
    }

    displayCategories(categories, categoryCount);
    int choice;
    cout << "Enter the category number to delete  ";
    cin >> choice;

    if (choice < 1 )
	 {
        cout << "Invalid entry " <<endl;
        return;
    }

    // Shift categories to delete the chosen one
    for (int i = choice - 1; i < categoryCount - 1; i++)
	 {
        categories[i] = categories[i + 1];
    }
    categoryCount--;
    cout << "Category deleted successfully " <<endl;
}

// Function to modify a category name
void modifyCategory(Category categories[], int categoryCount) 
{
    if (categoryCount <= 0) {
        cout << "No categories available to modify " <<endl;
        return;
    }

    displayCategories(categories, categoryCount);
    int choice;
    cout << "Enter the category number to modify  ";
    cin >> choice;

    if (choice < 1 )
	 {
        cout << "Invalid choice " <<endl;
        return;
    }

    cout << "Enter the new name for category " << categories[choice - 1].name << ": ";
    cin >> categories[choice - 1].name;
    cout << "Category modified successfully " <<endl;
}

// Function to add a dish to a category
void addDish(Category categories[], int categoryIndex) 
{
    if (categoryIndex < 0) 
	{
        cout << "Invalid category index "<<endl;
        return;
    }

    if (categories[categoryIndex].dishnum >= MAX_DISHES)
	 {
        cout << "No space available for more dishes in this category " <<endl;
        return;
    }

    cout << "Enter dish name: ";
    cin >> categories[categoryIndex].dishes[categories[categoryIndex].dishnum].name;
    cout << "Enter price for " << categories[categoryIndex].dishes[categories[categoryIndex].dishnum].name << ": ";
    cin >> categories[categoryIndex].dishes[categories[categoryIndex].dishnum].price;
    categories[categoryIndex].dishnum++; 
    cout << "Dish added successfully " <<endl;
}

// Function to delete a dish from a category
void deleteDish(Category categories[], int categoryIndex)
 {
    if (categoryIndex < 0 )
	 {
        cout << "Invalid category index " <<endl;
        return;
    }

    if (categories[categoryIndex].dishnum == 0) 
	{
        cout << "No dishes available to delete " <<endl;
        return;
    }

    displayDishes(categories, categoryIndex);
    int dishChoice;
    cout << "Enter the dish number to delete: ";
    cin >> dishChoice;

    if (dishChoice < 1 )
	 {
        cout << "Invalid dish choice "<<endl;
        return;
    }

    // Shift dishes to delete the selected dish
    for (int i = dishChoice - 1; i < categories[categoryIndex].dishnum- 1; i++)
	 {
        categories[categoryIndex].dishes[i] = categories[categoryIndex].dishes[i+1];
    }
    categories[categoryIndex].dishnum--;   // decrease in the dish number
    cout << "Dish deleted successfully " <<endl;
}

// Function to modify a dish's name and price
void modifyDish(Category categories[], int categoryIndex) 
{
    if (categoryIndex < 0 )
	 {
        cout << "Invalid category index " <<endl;
        return;
    }

    if (categories[categoryIndex].dishnum == 0) 
	{
        cout << "No dishes available to modify "<<endl;
        return;
    }

    displayDishes(categories, categoryIndex);
    int dishChoice;
    cout << "Enter the dish number to modify: ";
    cin >> dishChoice;

    if (dishChoice < 1 ) 
	{
        cout << "Invalid dish choice " <<endl;
        return;
    }

    cout << "Enter the new name for " << categories[categoryIndex].dishes[dishChoice - 1].name << ": ";
    cin >> categories[categoryIndex].dishes[dishChoice - 1].name;

    cout << "Enter the new price for " << categories[categoryIndex].dishes[dishChoice - 1].name << ": ";
    cin >> categories[categoryIndex].dishes[dishChoice - 1].price;
    cout << "Dish modified successfully. " <<endl;
}

// Main function
int main()
 {
 	setTextColor(5 , 7);
 	clearScreen();
    Category categories[MAX_CATEGORIES] = 
	{
        {"Pakistani", {{"Biryani", 400}, {"Karahi", 650}, {"Haleem", 510}, {"Nihari",430}, {"Kebab", 200}}, 5},
        {"Afghani", {{"Kabuli Pulao",340}, {"Mantu", 600}, {"Ashak", 410}, {"Afghani Kebab", 650}, {"Bolani", 320}}, 5},
        {"Italian", {{"Pasta", 700}, {"Pizza", 990}, {"Lasagna", 700}, {"Risotto",700}, {"Bruschetta", 660}}, 5},
        {"French", {{"Croissant", 550}, {"Quiche", 350}, {"Ratatouille", 600}, {"Soufflé",420}, {"Crêpe", 780}}, 5}
    };

    int categoryCount = 4;  // Number of categories
    char anotherOper;

    do {
        // Display main menu
        cout << "==== Main Menu ======= " <<endl;
        cout << "1. Place an order " <<endl;
        cout << "2. Add a new category  ( add cat) " <<endl;
        cout << "3. Delete a category  ( delete cat )" <<endl;
        cout << "4. Modify a category  ( upgrade cat)" <<endl;
        cout << "5. Add a dish to a category ( add dish) " <<endl;
        cout << "6. Delete a dish from a category  ( delete dish)" <<endl;
        cout << "7. Modify a dish ( upgrade cat ) " <<endl;
        cout << "8. Exit " <<endl;
        cout << "Enter your choice ";
        int choice;
        cin >> choice;

        switch (choice)
		 {
            case 1:
                processOrder(categories, categoryCount);
                break;
            case 2:
                addCategory(categories, categoryCount);
                break;
            case 3:
                deleteCategory(categories, categoryCount);
                break;
            case 4:
                modifyCategory(categories, categoryCount);
                break;
            case 5:
			 {
                int catChoice;
                displayCategories(categories, categoryCount);
                cout << "Enter the category number to add a dish: ";
                cin >> catChoice;
                addDish(categories, catChoice - 1);
                break;
            }
            case 6: 
			{
                int catChoice;
                displayCategories(categories, categoryCount);
                cout << "Enter the category number to delete a dish: ";
                cin >> catChoice;
                deleteDish(categories, catChoice - 1);
                break;
            }
            case 7: 
			{
                int catChoice;
                displayCategories(categories, categoryCount);
                cout << "Enter the category number to modify a dish: ";
                cin >> catChoice;
                modifyDish(categories, catChoice - 1);
                break;
            }
            case 8:
                cout << "Exiting program." <<endl;
                break;
            default:
                cout << "Invalid choice. Please try again."<<endl;
        }

        if (choice != 8)
		 {
            cout << "Would you like to perform another operation? (y/n): "<<endl;
            cin >> anotherOper;
        }
    } 
	while (anotherOper == 'y');

    cout << "Thank you for your visit . Have a nice day! " <<endl;
    return 0;
}
