# DesignPatterns
Problem Statement
 __________________________________________________
|    Welcome to ABC pizza center                   |
| What would you like to try today ?               |
|1. Special pizza                                  |
|2. Onion Pizza                                    |
|3. Capsicum Pizza                                 |
|4. Cheese Pizza                                   |
|                 press number to select item      |
|__________________________________________________|

 __________________________________________________
|    Special Pizza         <ESC> for previous menu |
| Select Size of Pizza                             |
|1. Small             -  0  +                      |
|2. Medium            -  0  +                      |
|3. Large             -  0  +                      |
|                          <ENT> to confirm        |
| press number to select item + and - for quantity |
|__________________________________________________|

 __________________________________________________
|    Your Order Details    <ESC> for previous menu |
|                                                  |
|1. Small Special pizza: 2 Nos.                    |
|2. Medium Onion pizza : 1 Nos.                    |
|3. Large Cheeese pizza: 1 Nos.                    |
|                          <ENT> for Order         |
|                                                  |
|__________________________________________________|
  
1. Builder Design pattern
reference: blackbox.ai

The Builder Design Pattern is a creational design pattern that allows for the step-by-step construction of complex objects. It separates the construction of a complex object from its representation, enabling the same construction process to create different representations. This pattern is particularly useful when an object requires multiple steps to be created, and you want to avoid a large constructor with many parameters.

Key Components of the Builder Pattern
Product: This is the complex object that is being built.
Builder Interface: This defines the methods for creating the parts of the product.
Concrete Builder: This implements the builder interface and provides specific implementations for the methods to construct the parts of the product.
Director: This class is responsible for managing the construction process. It uses a builder to construct the product.

Example:

Consider we want to create a console app with 50x10 char display showing the following screens

 __________________________________________________  -> Main Menu
|    Welcome to ABC pizza center                   |
| What would you like to try today ?               |
|1. Special pizza                                  |
|2. Onion Pizza                                    |
|3. Capsicum Pizza                                 |
|4. Cheese Pizza                                   |
|                                                  |
|                  press number to select item     |
|__________________________________________________|

 __________________________________________________  -> Size Selection
|    Special Pizza         <ESC> for previous menu |
| Select Size of Pizza                             |
|1. Small             -  0  +                      |
|2. Medium            -  0  +                      |
|3. Large             -  0  +                      |
|                          <ENT> to confirm        |
| press number to select item + and - for quantity |
|                                                  |
|__________________________________________________|

 __________________________________________________  -> Order Details
|    Your Order Details    <ESC> for previous menu |
|                                                  |
|1. Small Special pizza: 2 Nos.                    |
|2. Medium Onion pizza : 1 Nos.                    |
|3. Large Cheeese pizza: 1 Nos.                    |
|                          <ENT> for Order         |
|                                                  |
|                                                  |
|__________________________________________________|


In order to build the screens we can use builder design pattern to get string for display

Product: Screen

Builder Interface: ScreenBuilder

Concreate Builder(s) : MainMenuScreen, SizeSelectionScreen, OrderDetailsScreen

Director: ScreenDirector

Please refer BuilderDesignPattern.cpp for details
