

#include <iostream>
#include <string>

using namespace std;

int main() {
     // Variables / 变量
    string user;
    int classChoice,health, coins, damageOutput;
    bool validChoice = false;

    int energy = 100;
    

    cout << "Welcome to [      ], please enter your name traveler: \n";
    cin >> user;
    cout << "Greetings " << user << ", welcome to [      ]! \n";
    // Class Selection with Validation Loop / 带验证的职业选择循环 

    // Use a while loop to ensure the user picks a valid class
    while (!validChoice) {
    cout << "Pick your desired class and enter the corresponding number: \n"; 
    cout << "1. Knight \n";
    cout << "2. Mage \n";
    cout << "3. Thief \n";

    cin >> classChoice;

    switch (classChoice) {
        case 1:
            cout << "You have chosen the Knight class! \n";
            health = 150;
            validChoice = true;
            break;
        case 2:
            cout << "You have chosen the Mage class! \n";
            health = 100;
            validChoice = true;
            break;
        case 3:
            cout << "You have chosen the Thief class! \n";
            health = 80;
            validChoice = true;
            break;
        default:
            cout << "Invalid choice, please restart the program and choose a valid class. \n";
            break;
    }

    }    
    // Display initial stats / 显示初始属性
    cout << "Your health is: " << health << endl;

    if (classChoice == 1) {
        coins = 100;
        damageOutput = 8;
    } else if (classChoice == 2) {
        coins = 80;
        damageOutput = 10;
    } else if (classChoice == 3) {
        coins = 200;
        damageOutput = 6;
    }
    cout << "Your coins are: " << coins << endl;
    cout << "Your damage output is: " << damageOutput << endl;
    cout << "Your energy are: " << energy << endl;

    cout << "You are now suited for your first adventure. Good luck " << user << "!" << endl;
    string adventureChoice;
    cout << "Do you want to go on an adventure? (Y/N) \n";
    cin >> adventureChoice;
    if (adventureChoice == "Y" || adventureChoice == "y") {
        cout << "You have chosen to go on an adventure! \n";
        cout << "You stumble upon a forest and decide to explore it. \n";
        cout << "You encounter a wild monster! Do you want to fight or run? (fight/run) \n";
        string fightChoice;
        int monsterHealth = 25;
        cin >> fightChoice;

        if (fightChoice == "fight") {
            cout << "You have chosen to fight the monster! \n";
            cout << "You have defeated the monster and gained 50 coins! \n";
            coins += 50;    // Gain bounty / 获得赏金
            energy -=10;    // Combat costs energy/ 战斗消耗精力
            cout << "Your coins are now: " << coins << endl;
            cout << "Your energe are now: " << energy << endl;
        } else if (fightChoice == "run") {
            cout << "You have chosen to run away from the monster! \n";
            cout << "You are able to flee with a minor scratch. \n";
            health -= 5;
            cout << "Your health is now: " << health << endl;
        } else {
            cout << "Invalid choice, please restart the program and choose a valid option. \n";
        }
    } else if (adventureChoice == "N" || adventureChoice == "n") {
        cout << "You have chosen not to go on an adventure. Maybe next time! \n";
    } else {
        cout << "Invalid choice, please restart the program and choose a valid option. \n";
    }

    cout << "Would you like to view inventory and stats? (Y/N) \n";
    string inventoryChoice;
    cin >> inventoryChoice;
    if (inventoryChoice == "Y" || inventoryChoice == "y") {
        cout << "You have chosen to view your inventory! \n";
        cout << "Health: " << health << endl;
        cout << "Coins: " << coins << endl;
        cout << "Damage: " << damageOutput << endl;
        cout << "energy: " << energy << endl;
    } else if (inventoryChoice == "N" || inventoryChoice == "n") {
        cout << "You have chosen not to view your inventory. Maybe next time! \n";
    } else {
        cout << "Invalid choice, please restart the program and choose a valid option. \n";
    }
    
    
}
