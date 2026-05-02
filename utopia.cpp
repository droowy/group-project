// ============================================================
//  MEDIEVAL QUEST - Levels 1 & 2
//  CS 002 Honors Project
// ============================================================
 
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
 
using namespace std;
 
// ==================== Function Declarations ====================
void displayWelcome(string &user);
void chooseClass(int &classChoice, int &health, int &energy, int &combatSkills, int &coins);
void displayStats(int health, int energy, int combatSkills, int coins);
void displayInventory(int healthPotions, int fish, int rabbitMeat, bool wolfHead, bool energyPotion);
 
// Combat helpers / 战斗通用
int doLightAttack(int &energy, int costEnergy, int baseDmg);
int doStrongAttack(int &energy, int costEnergy, int baseDmg);
 
// Level 1 / 第一关
void playLevelOne(int &health, int &energy, int &coins, int &fish, bool &wolfHead, bool &levelOneDone);
void displayLevelOneMenu();
void huntBird(int &coins, int &energy);
void exploreFishing(int &energy, int &fish);
void fightWolf(int &health, int &energy, bool &wolfHead, bool &levelOneDone);
 
// Market / 市场
void enterMarket(int &coins, int &healthPotions);
 
// Level 2 / 第二关
void playLevelTwo(int &health, int &energy, int &coins, int &healthPotions, int &fish,
                  int &rabbitMeat, bool wolfHead, bool &energyPotion, bool &levelTwoDone);
void displayLevelTwoMenu();
void huntRabbit(int &energy, int &rabbitMeat);
void exploreVendor();
void fightBandit(int &health, int &energy, bool &energyPotion, bool &levelTwoDone);
void useHealthPotion(int &health, int &healthPotions);
void useFish(int &health, int &fish);
void useRabbitMeat(int &health, int &rabbitMeat);
 
// End game / 结束
void displayEndGame(string user, int health, bool levelTwoDone);
 
// ==================== MAIN ====================
int main() {
    srand(time(0));
 
    string user;
    int classChoice;
    int health, energy, combatSkills, coins;
 
    // Inventory / 库存
    int healthPotions = 0;
    int fish = 0;
    int rabbitMeat = 0;
    bool wolfHead = false;
    bool energyPotion = false;
 
    // Game state / 游戏状态
    bool levelOneDone = false;
    bool levelTwoDone = false;
 
    // Setup / 设置
    displayWelcome(user);
    chooseClass(classChoice, health, energy, combatSkills, coins);
    displayStats(health, energy, combatSkills, coins);
 
    // Level 1 / 第一关
    playLevelOne(health, energy, coins, fish, wolfHead, levelOneDone);
 
    // Level 2 (only if Level 1 done) / 第二关
    if (levelOneDone && health > 0) {
        cout << "\n[The forest path leads to a small village...]" << endl;
        enterMarket(coins, healthPotions);
        playLevelTwo(health, energy, coins, healthPotions, fish, rabbitMeat,
                     wolfHead, energyPotion, levelTwoDone);
    }
 
    displayEndGame(user, health, levelTwoDone);
    return 0;
}
 
// ==================== SETUP ====================
 
void displayWelcome(string &user) {
    cout << "===============================================" << endl;
    cout << "       WELCOME TO MEDIEVAL QUEST" << endl;
    cout << "===============================================" << endl;
    cout << "Please enter your name, traveler: ";
    cin >> user;
    cout << "\nGreetings " << user << "! Your adventure begins.\n" << endl;
}
 
void chooseClass(int &classChoice, int &health, int &energy, int &combatSkills, int &coins) {
    bool valid = false;
    while (!valid) {
        cout << "Choose your class:" << endl;
        cout << "1. Knight  (HP 150, EN 100, CS 8,  Coins 100)" << endl;
        cout << "2. Mage    (HP 100, EN 100, CS 10, Coins 80)" << endl;
        cout << "3. Thief   (HP 80,  EN 100, CS 6,  Coins 200)" << endl;
        cout << "Enter 1, 2, or 3: ";
        cin >> classChoice;
 
        switch (classChoice) {
            case 1:
                cout << "\nYou are a KNIGHT!\n" << endl;
                health = 150; energy = 100; combatSkills = 8; coins = 100;
                valid = true;
                break;
            case 2:
                cout << "\nYou are a MAGE!\n" << endl;
                health = 100; energy = 100; combatSkills = 10; coins = 80;
                valid = true;
                break;
            case 3:
                cout << "\nYou are a THIEF!\n" << endl;
                health = 80; energy = 100; combatSkills = 6; coins = 200;
                valid = true;
                break;
            default:
                cout << "Invalid choice.\n" << endl;
                break;
        }
    }
}
 
void displayStats(int health, int energy, int combatSkills, int coins) {
    cout << "\n--- STATS ---" << endl;
    cout << "Health:        " << health << endl;
    cout << "Energy:        " << energy << endl;
    cout << "Combat Skills: " << combatSkills << endl;
    cout << "Coins:         " << coins << endl;
}
 
void displayInventory(int healthPotions, int fish, int rabbitMeat, bool wolfHead, bool energyPotion) {
    cout << "\n--- INVENTORY ---" << endl;
    cout << "Health Potions: " << healthPotions << endl;
    cout << "Fish:           " << fish << endl;
    cout << "Rabbit Meat:    " << rabbitMeat << endl;
    cout << "Wolf's Head:    " << (wolfHead ? "YES" : "no") << endl;
    cout << "Energy Potion:  " << (energyPotion ? "YES" : "no") << endl;
}
 
// ==================== COMBAT HELPERS ====================
 
// Light attack: returns damage (0 if not enough energy) / 轻攻击
int doLightAttack(int &energy, int costEnergy, int baseDmg) {
    if (energy < costEnergy) {
        cout << "Not enough energy! (need " << costEnergy << ")" << endl;
        return 0;
    }
    energy -= costEnergy;
    int damage = baseDmg + (rand() % 6);  // small variance / 小范围浮动
    cout << "Light Attack! Damage: " << damage << endl;
    return damage;
}
 
// Strong attack / 强攻击
int doStrongAttack(int &energy, int costEnergy, int baseDmg) {
    if (energy < costEnergy) {
        cout << "Not enough energy! (need " << costEnergy << ")" << endl;
        return 0;
    }
    energy -= costEnergy;
    int damage = baseDmg + (rand() % 11);
    cout << "Strong Attack! Damage: " << damage << endl;
    return damage;
}
 
// ==================== LEVEL 1 - FOREST ====================
 
void displayLevelOneMenu() {
    cout << "\n--- Level 1 (Forest) ---" << endl;
    cout << "1. Hunt (kill a bird, +10 coins, -5 EN)" << endl;
    cout << "2. Explore (go fishing, +1 fish, -5 EN)" << endl;
    cout << "3. Fight (duel a wolf)" << endl;
    cout << "4. View Stats" << endl;
    cout << "5. View Inventory" << endl;
    cout << "Choice: ";
}
 
void huntBird(int &coins, int &energy) {
    if (energy < 5) { cout << "Too tired! (need 5 EN)" << endl; return; }
    energy -= 5;
    coins += 10;
    cout << "You killed a bird! +10 coins, -5 EN." << endl;
}
 
void exploreFishing(int &energy, int &fish) {
    if (energy < 5) { cout << "Too tired! (need 5 EN)" << endl; return; }
    energy -= 5;
    fish++;
    cout << "You caught a fish! +1 Fish, -5 EN." << endl;
}
 
void fightWolf(int &health, int &energy, bool &wolfHead, bool &levelOneDone) {
    cout << "\nA wolf lunges at you!" << endl;
    int wolfHealth = 60;
    int choice;
    bool ranAway = false;
 
    while (wolfHealth > 0 && health > 0 && !ranAway) {
        cout << "\nWolf HP: " << wolfHealth << " | Your HP: " << health << " | EN: " << energy << endl;
        cout << "1. Light attack (-10 EN)" << endl;
        cout << "2. Strong attack (-20 EN)" << endl;
        cout << "3. Run" << endl;
        cout << "Choice: ";
        cin >> choice;
 
        bool playerActed = false;
 
        if (choice == 1) {
            int dmg = doLightAttack(energy, 10, 18);
            if (dmg > 0) { wolfHealth -= dmg; playerActed = true; }
        } else if (choice == 2) {
            int dmg = doStrongAttack(energy, 20, 35);
            if (dmg > 0) { wolfHealth -= dmg; playerActed = true; }
        } else if (choice == 3) {
            cout << "You run from the wolf! Quest not complete." << endl;
            ranAway = true;
            continue;
        } else {
            cout << "Invalid choice." << endl;
        }
 
        // Wolf counter-attack / 狼反击
        if (playerActed && wolfHealth > 0) {
            int wolfDmg = (rand() % 11) + 5;
            health -= wolfDmg;
            cout << "The wolf bites you for " << wolfDmg << " damage!" << endl;
        }
    }
 
    if (wolfHealth <= 0 && health > 0) {
        cout << "\nThe wolf falls dead!" << endl;
        energy += 40;
        cout << "+40 EN restored." << endl;
 
        int after;
        bool decided = false;
        while (!decided) {
            cout << "\n1. Take the wolf's tail (keep exploring)" << endl;
            cout << "2. Take the wolf's head (complete quest!)" << endl;
            cout << "Choice: ";
            cin >> after;
            if (after == 1) {
                cout << "Keep exploring." << endl;
                decided = true;
            } else if (after == 2) {
                wolfHead = true;
                levelOneDone = true;
                cout << "*** QUEST COMPLETE! ***" << endl;
                decided = true;
            } else {
                cout << "Invalid choice." << endl;
            }
        }
    }
}
 
void playLevelOne(int &health, int &energy, int &coins, int &fish, bool &wolfHead, bool &levelOneDone) {
    cout << "\n=== LEVEL 1: THE FOREST ===" << endl;
    cout << "QUEST: Get a wolf's head" << endl;
 
    int choice;
    while (!levelOneDone && health > 0) {
        displayLevelOneMenu();
        cin >> choice;
        switch (choice) {
            case 1: huntBird(coins, energy); break;
            case 2: exploreFishing(energy, fish); break;
            case 3: fightWolf(health, energy, wolfHead, levelOneDone); break;
            case 4: displayStats(health, energy, 0, coins); break;
            case 5: displayInventory(0, fish, 0, wolfHead, false); break;
            default: cout << "Invalid choice." << endl;
        }
    }
}
 
// ==================== MARKET ====================
 
void enterMarket(int &coins, int &healthPotions) {
    cout << "\n========== MARKET ==========" << endl;
    cout << "A blacksmith waves you over." << endl;
 
    int choice;
    bool shopping = true;
    while (shopping) {
        cout << "\nYour coins: " << coins << endl;
        cout << "1. Health Potion (-50 coins, +20 HP)" << endl;
        cout << "0. Leave market" << endl;
        cout << "Choice: ";
        cin >> choice;
 
        if (choice == 0) {
            cout << "You leave the market." << endl;
            shopping = false;
        } else if (choice == 1) {
            if (coins >= 50) {
                coins -= 50;
                healthPotions++;
                cout << "Bought a Health Potion." << endl;
            } else {
                cout << "Not enough coins!" << endl;
            }
        } else {
            cout << "Invalid choice." << endl;
        }
    }
}
 
// ==================== LEVEL 2 - VILLAGE ====================
 
void displayLevelTwoMenu() {
    cout << "\n--- Level 2 (Village) ---" << endl;
    cout << "1. Hunt (trap a rabbit, +1 rabbit meat, -10 EN)" << endl;
    cout << "2. Explore (talk to a vendor)" << endl;
    cout << "3. Fight (duel a bandit)" << endl;
    cout << "4. View Stats" << endl;
    cout << "5. View Inventory" << endl;
    cout << "6. Use Health Potion (+20 HP)" << endl;
    cout << "7. Eat Fish (+40 HP)" << endl;
    cout << "8. Eat Rabbit Meat (+50 HP)" << endl;
    cout << "Choice: ";
}
 
void huntRabbit(int &energy, int &rabbitMeat) {
    if (energy < 10) { cout << "Too tired! (need 10 EN)" << endl; return; }
    energy -= 10;
    rabbitMeat++;
    cout << "You trapped a rabbit! +1 Rabbit Meat, -10 EN." << endl;
}
 
void exploreVendor() {
    cout << "\n--- Vendor ---" << endl;
    cout << "VENDOR: \"The bandit guards an Energy Potion in his coin purse." << endl;
    cout << "         Take that, not his hat!\"" << endl;
}
 
void fightBandit(int &health, int &energy, bool &energyPotion, bool &levelTwoDone) {
    cout << "\nA bandit blocks your path, dagger drawn!" << endl;
    int banditHealth = 100;
    int choice;
    bool ranAway = false;
 
    while (banditHealth > 0 && health > 0 && !ranAway) {
        cout << "\nBandit HP: " << banditHealth << " | Your HP: " << health << " | EN: " << energy << endl;
        cout << "1. Light attack (-20 EN)" << endl;
        cout << "2. Strong attack (-40 EN)" << endl;
        cout << "3. Run" << endl;
        cout << "Choice: ";
        cin >> choice;
 
        bool playerActed = false;
 
        if (choice == 1) {
            int dmg = doLightAttack(energy, 20, 20);
            if (dmg > 0) { banditHealth -= dmg; playerActed = true; }
        } else if (choice == 2) {
            int dmg = doStrongAttack(energy, 40, 40);
            if (dmg > 0) { banditHealth -= dmg; playerActed = true; }
        } else if (choice == 3) {
            cout << "You flee from the bandit! Quest not complete." << endl;
            ranAway = true;
            continue;
        } else {
            cout << "Invalid choice." << endl;
        }
 
        // Bandit counter-attack / 强盗反击
        if (playerActed && banditHealth > 0) {
            int dmg = (rand() % 11) + 10;
            health -= dmg;
            cout << "The bandit slashes you for " << dmg << " damage!" << endl;
        }
    }
 
    if (banditHealth <= 0 && health > 0) {
        cout << "\nThe bandit collapses!" << endl;
        energy += 60;
        cout << "+60 EN restored." << endl;
 
        int after;
        bool decided = false;
        while (!decided) {
            cout << "\n1. Take the bandit's hat (keep exploring)" << endl;
            cout << "2. Take the bandit's coin purse (complete quest!)" << endl;
            cout << "Choice: ";
            cin >> after;
            if (after == 1) {
                cout << "Keep exploring." << endl;
                decided = true;
            } else if (after == 2) {
                cout << "Inside the coin purse: an ENERGY POTION! +100 EN!" << endl;
                energy += 100;
                energyPotion = true;
                levelTwoDone = true;
                cout << "*** QUEST COMPLETE! ***" << endl;
                decided = true;
            } else {
                cout << "Invalid choice." << endl;
            }
        }
    }
}
 
void useHealthPotion(int &health, int &healthPotions) {
    if (healthPotions > 0) {
        healthPotions--;
        health += 20;
        cout << "Used a Health Potion! +20 HP." << endl;
    } else {
        cout << "You don't have any Health Potions!" << endl;
    }
}
 
void useFish(int &health, int &fish) {
    if (fish > 0) {
        fish--;
        health += 40;
        cout << "Ate a fish! +40 HP." << endl;
    } else {
        cout << "You don't have any fish!" << endl;
    }
}
 
void useRabbitMeat(int &health, int &rabbitMeat) {
    if (rabbitMeat > 0) {
        rabbitMeat--;
        health += 50;
        cout << "Ate rabbit meat! +50 HP." << endl;
    } else {
        cout << "You don't have any rabbit meat!" << endl;
    }
}
 
void playLevelTwo(int &health, int &energy, int &coins, int &healthPotions, int &fish,
                  int &rabbitMeat, bool wolfHead, bool &energyPotion, bool &levelTwoDone) {
    cout << "\n=== LEVEL 2: THE VILLAGE ===" << endl;
    cout << "QUEST: Recover an energy potion from the bandit" << endl;
 
    int choice;
    while (!levelTwoDone && health > 0) {
        displayLevelTwoMenu();
        cin >> choice;
        switch (choice) {
            case 1: huntRabbit(energy, rabbitMeat); break;
            case 2: exploreVendor(); break;
            case 3: fightBandit(health, energy, energyPotion, levelTwoDone); break;
            case 4: displayStats(health, energy, 0, coins); break;
            case 5: displayInventory(healthPotions, fish, rabbitMeat, wolfHead, energyPotion); break;
            case 6: useHealthPotion(health, healthPotions); break;
            case 7: useFish(health, fish); break;
            case 8: useRabbitMeat(health, rabbitMeat); break;
            default: cout << "Invalid choice." << endl;
        }
    }
}
 
// ==================== END ====================
 
void displayEndGame(string user, int health, bool levelTwoDone) {
    cout << "\n=========================================" << endl;
    if (levelTwoDone) {
        cout << "Congratulations " << user << "!" << endl;
        cout << "You completed Levels 1 and 2!" << endl;
        cout << "[More adventures await in future levels...]" << endl;
    } else if (health <= 0) {
        cout << "You have died, " << user << ". GAME OVER." << endl;
    }
    cout << "=========================================" << endl;
}
