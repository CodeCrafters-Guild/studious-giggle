#include <iostream>
#include <vector>
#include <iomanip>

// Define a structure for menu items
struct MenuItem
{
    std::string name;
    double price;
};

// Define a structure for an order item
struct OrderItem
{
    std::string itemName;
    int quantity;
};

// Function to display the menu
void displayMenu(const std::vector<MenuItem> &menu)
{
    std::cout << "Menu:\n";
    for (const auto &item : menu)
    {
        std::cout << item.name << " - $" << std::fixed << std::setprecision(2) << item.price << "\n";
    }
    std::cout << std::endl;
}

// Function to generate an invoice based on the order
void generateInvoice(const std::vector<OrderItem> &order, const std::vector<MenuItem> &menu)
{
    double totalAmount = 0.0;

    std::cout << "\nInvoice:\n";
    std::cout << "--------------------------------------\n";
    std::cout << std::setw(20) << "Item" << std::setw(10) << "Quantity" << std::setw(15) << "Price" << std::setw(15) << "Total\n";
    std::cout << "--------------------------------------\n";

    for (const auto &orderItem : order)
    {
        // Find the corresponding menu item
        auto menuItem = std::find_if(menu.begin(), menu.end(), [&orderItem](const MenuItem &item)
                                     { return item.name == orderItem.itemName; });

        if (menuItem != menu.end())
        {
            double itemTotal = menuItem->price * orderItem.quantity;
            totalAmount += itemTotal;

            std::cout << std::setw(20) << orderItem.itemName << std::setw(10) << orderItem.quantity
                      << std::setw(15) << std::fixed << std::setprecision(2) << menuItem->price
                      << std::setw(15) << std::fixed << std::setprecision(2) << itemTotal << "\n";
        }
    }

    std::cout << "--------------------------------------\n";
    std::cout << std::setw(45) << "Total:" << std::setw(15) << std::fixed << std::setprecision(2) << totalAmount << "\n";
    std::cout << "--------------------------------------\n\n";
}

int main()
{
    // Sample menu items
    std::vector<MenuItem> menu = {
        {"Burger", 5.99},
        {"Pizza", 8.49},
        {"Pasta", 7.99},
        {"Salad", 4.99}};

    // Initialize an empty order
    std::vector<OrderItem> order;

    // Display the menu
    displayMenu(menu);

    // Take orders
    char addMore;
    do
    {
        OrderItem orderItem;
        std::cout << "Enter item name: ";
        std::cin >> orderItem.itemName;
        std::cout << "Enter quantity: ";
        std::cin >> orderItem.quantity;

        // Add the item to the order
        order.push_back(orderItem);

        std::cout << "Do you want to add more items? (y/n): ";
        std::cin >> addMore;
    } while (addMore == 'y' || addMore == 'Y');

    // Generate and display the invoice
    generateInvoice(order, menu);

    return 0;
}
