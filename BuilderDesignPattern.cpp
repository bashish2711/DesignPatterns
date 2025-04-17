#include <iostream>
#include <string>
#include <vector>
#include <iomanip> // For std::setw

// Product
class Screen
{
public:
    std::string title;
    std::string subtitle;
    std::vector<std::string> options;
    std::string footer;

    void display() const {
        const int width = 50; // Width of the screen
        std::string border(width, '_'); // Create a border using '_'

        std::cout << " " << border << " " << "\n";
        std::cout << "| " << std::setw(width - 1) << std::left << title << "|\n"; // Title
        std::cout << "| " << std::setw(width - 1) << std::left << subtitle << "|\n"; // Subtitle
        for (const auto& option : options) {
            std::cout << "| " << std::setw(width - 1) << std::left << option << "|\n"; // Options
        }
        std::cout << "| " << std::setw(width - 1) << std::right << footer << "|\n"; // Footer
        std::cout << "|" << border << "|" << "\n"; // Close the border
    }
};

// Builder interface

class ScreenBuilder
{
public:
    virtual ~ScreenBuilder() = default;
    virtual void buildTitle() = 0;
    virtual void buildSubtitle() = 0;
    virtual void buildOptions() = 0;
    virtual void buildFooter() = 0;
    virtual Screen getScreen() = 0; // Return by value
};

// Concreate Builders

class MainMenuBuilder : public ScreenBuilder
{
private:
    Screen screen;

public:
    void buildTitle() override
    {
        screen.title = "Welcome to ABC pizza center";
    }

    void buildSubtitle() override
    {
        screen.subtitle = "What would you like to try today ?";
    }

    void buildOptions() override
    {
        screen.options = {
            "1. Special pizza",
            "2. Onion Pizza",
            "3. Capsicum Pizza",
            "4. Cheese Pizza",
            };
    }

    void buildFooter() override
    {
        screen.footer = "press number to select item";
    }

    Screen getScreen() override
    {
        return screen; // Return by value
    }
};

class SizeSelectionBuilder : public ScreenBuilder
{
private:
    Screen screen;

public:
    void buildTitle() override
    {
        screen.title = "Special Pizza         <ESC> for previous menu";
    }
    void buildSubtitle() override
    {
        screen.subtitle = "Select Size of Pizza";
    }
    void buildOptions() override
    {
        screen.options = {     
            "1. Small             -  0  +",
            "2. Medium            -  0  +",
            "3. Large             -  0  +",
            "<ENT> to confirm"};
    }

    void buildFooter() override
    {
        screen.footer = "press number to select item + and - for quantity";
    }

    Screen getScreen() override
    {
        return screen; // Return by value
    }
};

class OrderDetailsBuilder : public ScreenBuilder
{
private:
    Screen screen;

public:
    void buildTitle() override
    {
        screen.title = "Your Order Details    <ESC> for previous menu";
    }

    void buildSubtitle() override
    {
        screen.subtitle = "Total Amount : 1000 Rupees";
    }

    void buildOptions() override
    {
        screen.options = {
            "1. Small Special pizza: 2 Nos.",
            "2. Medium Onion pizza : 1 Nos.",
            "3. Large Cheese pizza: 1 Nos.",
            "<ENT> for Order"};
    }

    void buildFooter() override
    {
        screen.footer = "";
    }

    Screen getScreen() override
    {
        return screen; // Return by value
    }
};

// Director

class ScreenDirector
{
private:
    ScreenBuilder *builder;

public:
    void setBuilder(ScreenBuilder *newBuilder)
    {
        builder = newBuilder;
    }

    Screen constructScreen()
    {
        builder->buildTitle();
        builder->buildSubtitle();
        builder->buildOptions();
        builder->buildFooter();
        return builder->getScreen(); // Return by value
    }
};

int main()
{
    char key;
    ScreenDirector director;

    // Build the main menu screen
    MainMenuBuilder mainMenuBuilder;
    director.setBuilder(&mainMenuBuilder);
    Screen mainMenuScreen = director.constructScreen(); // Stack allocation
    mainMenuScreen.display();
    std::cin >> key;
    // Build the size selection screen
    SizeSelectionBuilder sizeSelectionBuilder;
    director.setBuilder(&sizeSelectionBuilder);
    Screen sizeSelectionScreen = director.constructScreen(); // Stack allocation
    sizeSelectionScreen.display();
    std::cin >> key;
    // Build the order details screen
    OrderDetailsBuilder orderDetailsBuilder;
    director.setBuilder(&orderDetailsBuilder);
    Screen orderDetailsScreen = director.constructScreen(); // Stack allocation
    orderDetailsScreen.display();

    return 0;
}