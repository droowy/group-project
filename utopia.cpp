#include <iostream>
#include <string>

using namespace std;

//  Function Declarations  函数声明 
void displayWelcome(string &user);
void chooseClass(int &classChoice, int &health, int &coins, int &damageOutput);
void displayStats(int health, int energy, int coins, int damageOutput);
void hunt(int &coins, int &energy);
void explore(int &health, int &energy);
void fightWolf(int &health, int &energy, bool &levelOneComplete);
void doLightAttack(int &energy, int &wolfHealth);
void doStrongAttack(int &energy, int &wolfHealth);
void displayLevelOneMenu();
void playLevelOne(string user, int &health, int &energy, int &coins, int damageOutput);
void displayEndGame(string user, int health, bool levelOneComplete);

//  Main  主函数 
int main() {
    // Variables  变量
    string user;
    int classChoice, health, coins, damageOutput;
    int energy = 100;

    // Welcome the player  欢迎玩家
    displayWelcome(user);

    // Pick a class  选择职业
    chooseClass(classChoice, health, coins, damageOutput);

    // Show initial stats  显示初始属性
    displayStats(health, energy, coins, damageOutput);

    // Play Level 1  玩第一关
    bool levelOneComplete = false;
    cout << "\nYou are now suited for your first adventure. Good luck " << user << "!" << endl;
    cout << "\n=== LEVEL 1: THE FOREST ===" << endl;
    cout << "QUEST: Get a wolf's head" << endl;

    // Main level loop  第一关的主循环
    int choice;
    while (!levelOneComplete && health > 0) {
        displayLevelOneMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                hunt(coins, energy);
                break;
            case 2:
                explore(health, energy);
                break;
            case 3:
                fightWolf(health, energy, levelOneComplete);
                break;
            case 4:
                displayStats(health, energy, coins, damageOutput);
                break;
            default:
                cout << "Invalid choice. Please pick 1-4." << endl;
                break;
        }
    }

    // End game results  关卡结束判定
    displayEndGame(user, health, levelOneComplete);

    return 0;
}

//  Function  函数定义 

// Display welcome message and get user's name / 显示欢迎信息并获取玩家名字
void displayWelcome(string &user) {
    cout << "Welcome to [      ], please enter your name traveler: \n";
    cin >> user;
    cout << "Greetings " << user << ", welcome to [      ]! \n";
}

// Let the player pick a class / 让玩家选择职业
void chooseClass(int &classChoice, int &health, int &coins, int &damageOutput) {
    bool validChoice = false;

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
                coins = 100;
                damageOutput = 8;
                validChoice = true;
                break;
            case 2:
                cout << "You have chosen the Mage class! \n";
                health = 100;
                coins = 80;
                damageOutput = 10;
                validChoice = true;
                break;
            case 3:
                cout << "You have chosen the Thief class! \n";
                health = 80;
                coins = 200;
                damageOutput = 6;
                validChoice = true;
                break;
            default:
                cout << "Invalid choice, please pick a valid class. \n";
                break;
        }
    }
}

// Display the player's stats  显示玩家属性
void displayStats(int health, int energy, int coins, int damageOutput) {
    cout << "\n--- STATS ---" << endl;
    cout << "Health: " << health << endl;
    cout << "Energy: " << energy << endl;
    cout << "Coins: " << coins << endl;
    cout << "Damage: " << damageOutput << endl;
}

// Hunt  打猎动作
void hunt(int &coins, int &energy) {
    if (energy >= 5) {
        cout << "\nYou hunt and kill a bird! \n";
        coins += 10;
        energy -= 5;
        cout << "Result: +10 Coins, -5 Energy. \n";
    } else {
        cout << "\nYou are too tired to hunt! You need at least 5 energy. \n";
    }
}

// Explore  探索动作
void explore(int &health, int &energy) {
    if (energy >= 5) {
        cout << "\nYou go fishing! \n";
        health += 10;
        energy -= 5;
        cout << "Result: +10 Health, -5 Energy. \n";
    } else {
        cout << "\nYou are too tired to explore! You need at least 5 energy. \n";
    }
}

// Display the Level 1 menu  显示第一关菜单
void displayLevelOneMenu() {
    cout << "\n--- Level 1 Menu ---" << endl;
    cout << "1. Hunt (-5 Energy, +10 Coins)" << endl;
    cout << "2. Explore (-5 Energy, +10 Health)" << endl;
    cout << "3. Fight (Duel with a wolf)" << endl;
    cout << "4. View Inventory and Stats" << endl;
    cout << "Enter your choice (1-4): ";
}

// Light attack on the wolf  对狼使用轻攻击
void doLightAttack(int &energy, int &wolfHealth) {
    if (energy >= 10) {
        energy -= 10;
        wolfHealth -= 15;
        cout << "You used a Light Attack!" << endl;
    } else {
        cout << "Not enough energy!" << endl;
    }
}

// Strong attack on the wolf  对狼使用强攻击
void doStrongAttack(int &energy, int &wolfHealth) {
    if (energy >= 20) {
        energy -= 20;
        wolfHealth -= 40;
        cout << "You used a Strong Attack!" << endl;
    } else {
        cout << "Not enough energy!" << endl;
    }
}

// Fight the wolf  与狼战斗
void fightWolf(int &health, int &energy, bool &levelOneComplete) {
    cout << "\nYou engage in a duel with a wolf! \n";
    int wolfHealth = 60;
    int attackChoice;

    // Fight loop  战斗循环
    while (wolfHealth > 0 && health > 0) {
        cout << "\nWolf Health: " << wolfHealth << endl;
        cout << "Your Health: " << health << " | Your Energy: " << energy << endl;
        cout << "1. Light attack (-10 energy, deals 15 dmg to wolf HP)" << endl;
        cout << "2. Strong attack (-20 energy, deals 40 dmg to wolf HP)" << endl;
        cin >> attackChoice;

        if (attackChoice == 1) {
            doLightAttack(energy, wolfHealth);
        } else if (attackChoice == 2) {
            doStrongAttack(energy, wolfHealth);
        } else {
            cout << "Invalid attack choice." << endl;
        }
    }

    // Determine fight result  判断战斗结果
    if (wolfHealth <= 0) {
        cout << "\nYou have won the duel!" << endl;
        energy += 100;
        cout << "You gained +100 Energy." << endl;
        cout << "Take the wolf's head" << endl;
        cout << "\nQuest Completed! You got the wolf's head." << endl;
        levelOneComplete = true;
    }
}

// Display end game message  显示结束游戏信息
void displayEndGame(string user, int health, bool levelOneComplete) {
    if (health <= 0) {
        cout << "\nYou have died. GAME OVER." << endl;
    } else if (levelOneComplete) {
        cout << "\nCongratulations " << user << "! You are moving on to Level 2: The Village!" << endl;
    }
}
