

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

    // 开始第一关 (Level 1: Forest) 
    cout << "\nYou are now suited for your first adventure. Good luck " << user << "!" << endl;
    cout << "\n=== LEVEL 1: THE FOREST ===" << endl;
    cout << "QUEST: Get a wolf's head" << endl;

    bool levelOneComplete = false;
    int choice;

    // The main loop for Level 1 / 第一关的主循环
    // Continues until the quest is complete or the player dies / 只要任务没完成且玩家存活，就一直循环
    while (!levelOneComplete && health > 0) {
        cout << "\n--- Level 1 Menu ---" << endl;
        cout << "1. Hunt (-5 Energy, +10 Coins)" << endl;
        cout << "2. Explore (-5 Energy, +10 Health)" << endl;
        cout << "3. Fight (Duel with a wolf)" << endl;
        cout << "4. View Inventory and Stats" << endl;
        cout << "Enter your choice (1-4): ";
        cin >> choice;

        switch (choice) {
            case 1: // Hunt / 打猎
                if (energy >= 5) {
                    cout << "\nYou hunt and kill a bird! \n";
                    coins += 10;
                    energy -= 5;
                    cout << "Result: +10 Coins, -5 Energy. \n";
                } else {
                    cout << "\nYou are too tired to hunt! You need at least 5 energy. \n";
                }
                break;

            case 2: // Explore / 探索
                if (energy >= 5) {
                    cout << "\nYou go fishing! \n";
                    health += 10;
                    energy -= 5;
                    cout << "Result: +10 Health, -5 Energy. \n";
                } else {
                    cout << "\nYou are too tired to explore! You need at least 5 energy. \n";
                }
                break;

            case 3: { // Fight the Wolf / 打狼
                cout << "\nYou engage in a duel with a wolf! \n";
                int wolfHealth = 60;
                
                
                // fight loop
                while (wolfHealth > 0 && health > 0) {
                    
                    cout << "\nWolf Health: " << wolfHealth << endl;
                    cout << "Your Health: " << health << " | Your Energy: " << energy << endl;
                    cout << "1. Light attack (-10 energy, deals 15 dmg to wolf HP)" << endl;
                    cout << "2. Strong attack (-20 energy, deals 40 dmg to wolf HP)" << endl;
                    
                    int attackChoice;
                    cin >> attackChoice;

                    if (attackChoice == 1) {
                        if (energy >= 10) { 
                            energy -= 10;
                            wolfHealth -= 15; 
                            cout << "You used a Light Attack!" << endl;
                        } else {
                            cout << "Not enough energy!" << endl;
                        }
                    } else if (attackChoice == 2) {
                         if (energy >= 20) {
                            energy -= 20;
                            wolfHealth -= 40;
                            cout << "You used a Strong Attack!" << endl;
                        } else {
                            cout << "Not enough energy!" << endl;
                        }
                    } else {
                        cout << "Invalid attack choice." << endl;
                    }
                }

                // 判断战斗结果
                if (wolfHealth <= 0) {
                    cout << "\nYou have won the duel!" << endl;
                    energy += 100; 
                    cout << "You gained +100 Energy." << endl;
                    cout << "Take the wolf's head" << endl;
                    cout << "\nQuest Completed! You got the wolf's head." << endl;
                    levelOneComplete = true; // finsih tesk完成任务，跳出第一关大循环
                } // end if 结束 if

                break; 
            } // End Fight Case

            case 4: // View Stats / 查看属性
                cout << "\n--- STATS ---" << endl;
                cout << "Health: " << health << endl;
                cout << "Energy: " << energy << endl;
                cout << "Coins: " << coins << endl;
                cout << "Damage: " << damageOutput << endl;
                break;

            default:
                cout << "Invalid choice. Please pick 1-4." << endl;
                break;
        }
    }

    // end 关卡结束判定
    if (health <= 0) {
        cout << "\nYou have died. GAME OVER." << endl;
    } else if (levelOneComplete) {
        cout << "\nCongratulations " << user << "! You are moving on to Level 2: The Village!" << endl;
        // add next level code后续可以在这里加上进入第二关的代码
    }

    return 0;
}
