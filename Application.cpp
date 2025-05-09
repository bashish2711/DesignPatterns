#include <iostream>
#include <cstring>

#define homescreen "__________________________________________________|    Welcome to ABC pizza center                 || What would you like to try today ?             ||1.                                              ||2.                                              ||3. Capsicum Pizza                               ||4. Cheese Pizza                                 ||                 press number to select item    ||________________________________________________|"
#define quantityscreen "__________________________________________________|    Special Pizza        <ESC> for previous menu|| Select Size of Pizza                           ||1. Small             -  0  +                    ||2. Medium            -  0  +                    ||3. Large             -  0  +                    ||                          < N > to confirm      ||press number to select item + and - for quantity||________________________________________________|"
#define orderscreen "__________________________________________________|    Your Order Details   <ESC> for previous menu||                                                ||1. Small Special pizza: 2 Nos.                  ||2. Medium Onion pizza : 1 Nos.                  ||3. Large Cheeese pizza: 1 Nos.                  ||                          < N > for Order       ||                                                ||________________________________________________|"

using namespace std;

typedef uint8_t U8;
typedef int8_t S8;
typedef char CHAR;
typedef uint32_t U32;

class Console
{
public:
    void show(CHAR *str)
    {
        for (U32 i = 0; str[i] != 0; i++)
        {
            if ((i % 50) == 0)
            {
                putchar('\n');
            }
            putchar(str[i]);
        }
    }
};

// Abstract State class
class State
{
protected:
    State *m_nextState;
    State *m_prevState;

public:
    virtual void display() = 0;
    virtual State *handleInput(U8 key) = 0;
    virtual void setNextState(State *state)
    {
        m_nextState = state;
    }

    virtual void setPreviousState(State *state)
    {
        m_prevState = state;
    }
};

class OrderInfo
{
public:
    typedef enum
    {
        eSmall,
        eMedium,
        eLarge,
    } EPizzaSizeTypes;

    static void setSelectedPizza(U8 type)
    {
        m_type = type;
    }

    static void setSelectedSize(U8 size)
    {
        m_sizeType = size;
    }

    static U8 getSelectedSize()
    {
        return m_sizeType;
    }

    static CHAR *getSelectedPizzaName()
    {
        return pizza[m_type].name;
    }

    static void incrementPizzaSizeCount()
    {
        ++pizza[m_type].typesCount[m_sizeType];
    }

    static void decrementPizzaSizeCount()
    {
        --pizza[m_type].typesCount[m_sizeType];
    }

    static U8 getCountForSize(U8 size_type)
    {
        U8 count = pizza[m_type].typesCount[size_type];
        return count;
    }

    typedef struct
    {
        CHAR name[20];
        U8 typesCount[5];
    } Pizza;
    static Pizza pizza[5];

private:
    static U8 m_type;
    static U8 m_sizeType;
};
U8 OrderInfo::m_type = 0;
U8 OrderInfo::m_sizeType = 0;
OrderInfo::Pizza OrderInfo::pizza[5] = {
    {"Special Pizza", {0, 0, 0}},
    {"Onion Pizza", {0, 0, 0}},
    {"Capsicum Pizza", {0, 0, 0}},
    {"Cheese Pizza", {0, 0, 0}}};

// Concrete States
class HomeScreen : public State
{

public:
    HomeScreen(const S8 *companyName)
        : m_pizzaNamesLocation{154, 204, 254, 304},
          m_companyNameLocation(66),
          m_companyName(companyName)
    {
        memcpy(m_buffer, homescreen, 450U);
        for (U32 indexLoc = 0; indexLoc < 4; indexLoc++)
        {
            U32 index = m_pizzaNamesLocation[indexLoc];
            for (U32 i = 0; OrderInfo::pizza[indexLoc].name[i] != 0; i++, index++)
            {
                m_buffer[index] = OrderInfo::pizza[indexLoc].name[i];
            }
        }
        U32 index = m_companyNameLocation;
        for (U32 i = 0; m_companyName[i] != 0; i++, index++)
        {
            m_buffer[index] = m_companyName[i];
        }
    };
    void display() override
    {
        m_buffer[450] = 0;
        m_console.show(m_buffer);
    }

    State *handleInput(U8 key) override
    {
        if (('1' <= key) && (key <= '4'))
        {
            U32 indexLoc = key - '0' - 1U;
            OrderInfo::setSelectedPizza(indexLoc);
            return m_nextState;
        }
        return this;
    }

private:
    CHAR m_buffer[451];
    U32 m_pizzaNamesLocation[4];
    U32 m_companyNameLocation;
    const S8 *m_companyName;
    Console m_console;
};

class QuantityScreen : public State
{

public:
    QuantityScreen() : m_textboxLocations{175, 225, 275},
                       selectedPizzaLocation(55)
    {
        memcpy(m_buffer, quantityscreen, 450U);
    };

    void display() override
    {
        const S8 asciiArray[10] = "012345678";

        U32 index = selectedPizzaLocation;
        CHAR *name = OrderInfo::getSelectedPizzaName();
        for (U32 i = 0; name[i] != 0; i++, index++)
        {
            m_buffer[index] = name[i];
        }

        for (U32 index = 0U; index < 3U; index++)
        {
            memcpy(&m_buffer[m_textboxLocations[index]], &asciiArray[OrderInfo::getCountForSize(index)], 1U);
        }
        m_buffer[450] = 0;
        m_console.show(m_buffer);
    }

    State *handleInput(U8 key) override
    {
        if ((key >= '1') && (key <= '3'))
        {
            OrderInfo::setSelectedSize(key - '0' - 1U);
        }
        if ('+' == key)
        {
            OrderInfo::incrementPizzaSizeCount();
        }
        if ('-' == key)
        {
            OrderInfo::decrementPizzaSizeCount();
        }
        if ('N' == key)
        {
            return m_nextState;
        }
        if ('P' == key)
        {
            return m_prevState;
        }
        return this;
    }

private:
    CHAR m_buffer[451];
    U32 m_textboxLocations[4];
    U32 selectedPizzaLocation;
    Console m_console;
};

class OrderScreen : public State
{
public:
    OrderScreen() :
    m_pizzaSizeLocations{154, 204, 254},
    m_pizzaCountLocation{175, 225, 275},
    m_pizzaNameLocations{125,210,260}
    {
        memcpy(m_buffer, orderscreen, 450U);
    };

public:
    void display() override
    {
        const S8 asciiArray[10] = "012345678";
        const CHAR *sizeTypeNameArray[3] = {"Small ", "Medium", "Large "};
        U32 sizeTypeArrayIndex = 0;
        for(U32 pizzaSize=0;pizzaSize < 3; pizzaSize++, sizeTypeArrayIndex++)
        {
            const CHAR *name = sizeTypeNameArray[sizeTypeArrayIndex];
            U32 index = m_pizzaSizeLocations[pizzaSize];
            for (U32 i = 0; name[i] != 0; i++)
            {
                m_buffer[index+i] = name[i];
            }

            for (U32 pizzaType = 0U; pizzaType < 4; pizzaType++)
            {
                CHAR *name = OrderInfo::pizza[pizzaType].name;
                U32 index = m_pizzaNameLocations[pizzaType];
                for (U32 i = 0; name[i] != 0; i++)
                {
                    m_buffer[index+i] = name[i];
                }
                

                for (U32 index = 0U; index < 3U; index++)
                {
                    m_buffer[m_pizzaCountLocation[index]] = asciiArray[OrderInfo::getCountForSize(index)];
                }
            }
        }
        m_buffer[450] = 0;
        m_console.show(m_buffer);
    }

    State *handleInput(U8 key) override
    {
        if ('N' == key)
        {
            return m_nextState;
        }
        if ('P' == key)
        {
            return m_prevState;
        }
        return this;
    }

private:
    CHAR m_buffer[1000];
    U32 m_pizzaSizeLocations[4];
    U32 m_pizzaCountLocation[4];
    U32 m_pizzaNameLocations[4];
    Console m_console;
};

// Context
class PizzaOrderingSystem
{
    State *currentState;
    const S8 companyName[4];

    HomeScreen homeScreen;
    QuantityScreen quantityScreen;
    OrderScreen orderScreen;

public:
    PizzaOrderingSystem() : currentState(&homeScreen),
                            companyName("XYZ"),
                            homeScreen(companyName)
    {
        homeScreen.setNextState(&quantityScreen);
        homeScreen.setPreviousState(&homeScreen);
        quantityScreen.setNextState(&orderScreen);
        quantityScreen.setPreviousState(&homeScreen);
        orderScreen.setNextState(&homeScreen);
        orderScreen.setPreviousState(&quantityScreen);
    }

    void run()
    {
        U8 key;
        while (true)
        {
            currentState->display();
            cin >> key;
            currentState = currentState->handleInput(key);
        }
    }
};

int main()
{
    PizzaOrderingSystem system;
    system.run();
    return 0;
}
