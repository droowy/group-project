// ============================================================
//  MEDIEVAL QUEST - Levels 1 & 2
//  CS 002 Honors Project
// ============================================================
/* changes:
- when the player consumes an item that increases health, limit to the max **need to do
- comsumables are automatically used, only weapons are stored in the inventory
        **inventory is only for the user to know what weapon is being used
        can use one weapon at a time, cannot store > 1
- add condition for strong attacks
- 50% chance of getting health or coins in explore and hunt options
*/
 
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
 
using namespace std;

const int KNIGHTCOMBATSKILLS = 1;
const int MAGECOMBATSKILLS = 2;
const int THIEFCOMBATSKILLS = 4;
const int KNIGHTMAXHEALTH = 150;
const int MAGEMAXHEALTH = 100;
const int THIEFMAXHEALTH = 80;
const int KNIGHTMAXENERGY = 90;
const int MAGEMAXENERGY = 50;
const int THIEFMAXENERGY = 30;

// ==================== Function Declarations ====================
void displayWelcome(string &user);
void chooseClass(int &classChoice, int &health, int &energy, int &combatSkills, int &coins);
void displayStats(int health, int energy, int combatSkills, int coins);
void displayInventory(string &weapon);
 
// Combat helpers / 战斗通用
int doLightAttack(int baseDmg, int combatSkills);
int doStrongAttack(int baseDmg, int combatSkills);
 
// Level 1 / 第一关
void playLevelOne(int &health, int &energy, int &coins, bool &wolfHead, bool &levelOneDone, int &combatSkills, int classChoice, string &weapon);
void displayLevelOneMenu();
void huntBird(int &coins, int &energy, int classChoice);
void exploreFishing(int &energy, int &health, int classChoice);
void fightWolf(int &health, int combatSkills, bool &wolfHead, bool &levelOneDone, int &coins);
 
// Market / 市场
void enterMarket(int &coins, int &combatSkills, int &health, string &weapon);
 
// Level 2 / 第二关
void playLevelTwo(int &health, int &energy, int &coins, bool &energyPotion, bool &levelTwoDone, int &combatSkills, int classChoice, string &weapon);
void displayLevelTwoMenu();
void huntRabbit(int &energy, int &coins, int classChoice);
void exploreVillager();
void fightBandit(int &health, int combatSkills, int &energy, bool &energyPotion, bool &levelTwoDone);
 
// End game / 结束
void displayEndGame(string user, int health, bool levelTwoDone);
 
// ==================== MAIN ====================
int main() {
    srand(time(0));
 
    string user;
    int classChoice;
    int health, energy, combatSkills, coins;

    // Inventory: player starts with no weapons, i.e. base combat skills
    string weapon = "bare-handed";

 
    // Quest condition
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
    playLevelOne(health, energy, coins, wolfHead, levelOneDone, combatSkills, classChoice, weapon);
 
    // Level 2 (only if Level 1 done) / 第二关
    if (levelOneDone && health > 0) {
        cout << "\n[The forest path leads to a small village...]" << endl;
        enterMarket(coins, combatSkills, health, weapon);
        playLevelTwo(health, energy, coins, energyPotion, levelTwoDone, combatSkills, classChoice, weapon);
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
        cout << "Choose your class:" << endl; //if less health, deal more damage and vice versa, CS are attack multipliers
        cout << "1. Knight  (HP 150, EN 90, CS 1,  Coins 100)" << endl;
        cout << "2. Mage    (HP 100, EN 50, CS 2,  Coins 80)" << endl;
        cout << "3. Thief   (HP 80,  EN 30, CS 4,  Coins 140)" << endl;
        cout << "Enter 1, 2, or 3: ";
        cin >> classChoice;
 
        switch (classChoice) {
            case 1:
                cout << "\nYou are a KNIGHT!\n" << endl;
                health = KNIGHTMAXHEALTH; energy = KNIGHTMAXENERGY; combatSkills = KNIGHTCOMBATSKILLS; coins = 100;
                valid = true;
                break;
            case 2:
                cout << "\nYou are a MAGE!\n" << endl;
                health = MAGEMAXHEALTH; energy = MAGEMAXENERGY; combatSkills = MAGECOMBATSKILLS; coins = 80;
                valid = true;
                break;
            case 3:
                cout << "\nYou are a THIEF!\n" << endl;
                health = THIEFMAXHEALTH; energy = THIEFMAXENERGY; combatSkills = THIEFCOMBATSKILLS; coins = 140;
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
 
void displayInventory(string &weapon) {
    cout << "\n--- INVENTORY ---" << endl;
    cout << "Your weapon: " << weapon << endl;
}
 
// ==================== COMBAT HELPERS ====================
 
// Light attack / 轻攻击
int doLightAttack(int baseDmg, int combatSkills) {
    int damage = (baseDmg + (rand() % 3)) * combatSkills;  // small variance / 小范围浮动
    cout << "Light Attack! Damage: " << damage << endl;
    return damage;

}
 
// Strong attack / 强攻击
/*ADD CONDITION: YOU CAN ONLY DEAL 3 STRONG ATTACKS PER FIGHT*/
int doStrongAttack(int baseDmg, int combatSkills) {
    int damage = (baseDmg + (rand() % 3)) * combatSkills;
    cout << "Strong Attack! Damage: " << damage << endl;
    return damage;
}
 
// ==================== LEVEL 1 - FOREST ====================
 
void displayLevelOneMenu() {
    cout << "\n--- Level 1 (Forest) ---" << endl;
    cout << "1. Hunt (kill a bird)" << endl;
    cout << "2. Explore (go fishing)" << endl;
    cout << "3. Fight (duel a wolf)" << endl;
    cout << "4. View Stats" << endl;
    cout << "5. View Inventory" << endl;
    cout << "Choice: ";
}
 
void huntBird(int &coins, int &energy, int classChoice) {
    
    int takeEnergy, i = (rand() % 100);

    if (classChoice == 1) {
        takeEnergy = KNIGHTMAXENERGY * 0.1;
    } else if (classChoice == 2) {
        takeEnergy = MAGEMAXENERGY * 0.1;
    } else if (classChoice == 3) {
        takeEnergy = THIEFMAXENERGY * 0.1;
    }

    if (energy < takeEnergy) { cout << "Too tired!" << endl; return; }

    if (i % 2 == 0) {
        energy -= takeEnergy;
        coins += 5;
        cout << "Good aim!" << endl;
        cout << "You hunted a bird and sold it for 5 coins" << endl;
        cout << "-"<< takeEnergy << " EN" << endl;
    } else {
        energy -= takeEnergy;
        cout << "You missed the shot!" << endl;
        cout << "The bird flew away..." << endl;
        cout << "-"<< takeEnergy << " EN" << endl;
    }
}
 
void exploreFishing(int &energy, int &health, int classChoice) {
    
    int takeEnergy, i = (rand() % 100);

    if (classChoice == 1) {
        takeEnergy = KNIGHTMAXENERGY * 0.1;
    } else if (classChoice == 2) {
        takeEnergy = MAGEMAXENERGY * 0.1;
    } else if (classChoice == 3) {
        takeEnergy = THIEFMAXENERGY * 0.1;
    }

    if (energy < takeEnergy) { cout << "Too tired!" << endl; return; }

    if (i % 2 == 0) {
        energy -= takeEnergy;
        health += 5;
        cout << "You're lucky!" << endl;
        cout << "You consumed the fish, +5 HP" << endl;
        cout << "-"<< takeEnergy << " EN" << endl;
    } else {
        energy -= takeEnergy;
        cout << "You're unlucky today, there's no fish!" << endl;
        cout << "Try something else?" << endl;
        cout << "-"<< takeEnergy << " EN" << endl;
    }
}
 
void fightWolf(int &health, int combatSkills, bool &wolfHead, bool &levelOneDone, int &coins) {
    cout << "\nA wolf lunges at you!" << endl;
    int initialWolfHealth = 115 + ((rand() % 15) + 10);
    int wolfHealth = initialWolfHealth;
    int choice;
    bool ranAway = false;
 
    while (wolfHealth > 0 && health > 0 && !ranAway) {
        cout << "\nWolf HP: " << wolfHealth << " | Your HP: " << health << " | CS: " << combatSkills << endl;
        cout << "1. Light attack" << endl;
        cout << "2. Strong attack" << endl;
        cout << "3. Run" << endl;
        cout << "Choice: ";
        cin >> choice;
 
        bool playerActed = false;
 
        if (choice == 1) {
            int dmg = doLightAttack(10, combatSkills);
            if (dmg > 0) { wolfHealth -= dmg; playerActed = true; }
        } else if (choice == 2) {
            int dmg = doStrongAttack(15, combatSkills);
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
            int wolfDmg = (rand() % 4) + 2;
            if (wolfHealth <= (initialWolfHealth / 2)) { //if wolf loses more than half health > counter attack doubles
                wolfDmg = wolfDmg * 2;
            }
            health -= wolfDmg;
            cout << "The wolf bites you for " << wolfDmg << " damage!" << endl;
        }
    }
 
    if (wolfHealth <= 0 && health > 0) {
        cout << "\nThe wolf falls dead!" << endl;
 
        int after;
        bool decided = false;
        while (!decided) {
            cout << "\n1. Take the wolf's tail" << endl;
            cout << "2. Take the wolf's head" << endl;
            cout << "Choice: ";
            cin >> after;
            if (after == 1) {
                cout << "Keep exploring." << endl;
                decided = true;
            } else if (after == 2) {
                wolfHead = true;
                levelOneDone = true;
                coins += 40;
                cout << "*** QUEST COMPLETE! You received 40 coins ***" << endl;
                decided = true;
            } else {
                cout << "Invalid choice." << endl;
            }
        }
    }
}
 
void playLevelOne(int &health, int &energy, int &coins, bool &wolfHead, bool &levelOneDone, int &combatSkills, int classChoice, string &weapon) {
    cout << "\n=== LEVEL 1: THE FOREST ===" << endl;
    cout << "QUEST: Get a wolf's head" << endl;
 
    int choice;
    while (!levelOneDone && health > 0) {
        displayLevelOneMenu();
        cin >> choice;
        switch (choice) {
            case 1: huntBird(coins, energy, classChoice); break;
            case 2: exploreFishing(energy, health, classChoice); break;
            case 3: fightWolf(health, combatSkills, wolfHead, levelOneDone, coins); break;
            case 4: displayStats(health, energy, combatSkills, coins); break;
            case 5: displayInventory(weapon); break;
            default: cout << "Invalid choice." << endl;
        }
    }
}
 
// ==================== MARKET ====================
 
void enterMarket(int &coins, int &combatSkills, int &health, string &weapon) {
    cout << "\n========== MARKET ==========" << endl;
    cout << "A blacksmith waves you over." << endl;
 
    const int tartPrice = (coins / 2); //can buy a max of 2 times
    const int tartHealth = (health * 0.15);
    const int swordPrice = (coins * 0.55); //can buy once on the first time

    int choice;
    bool shopping = true;
    while (shopping) {
        cout << "\nYour coins: " << coins << endl;
        cout << "1. Fruit tart (-" << tartPrice << " coins, +" << tartHealth << " HP)" << endl;
        cout << "2. Sword (-" << swordPrice << " coins, +1 CS)" << endl;
        cout << "0. Leave market" << endl;
        cout << "Choice: ";
        cin >> choice;
 
        if (choice == 0) {
            cout << "You leave the market." << endl;
            shopping = false;
        } else if (choice == 1) {
            if (coins >= tartPrice) {
                coins -= tartPrice;
                health += tartHealth;
                cout << "You purchased a fruit tart!" << endl;
                cout << "Your health is now: " << health << endl;
            } else {
                cout << "Not enough coins!" << endl;
            }
        } else if (choice == 2) {
            if (coins >= 110) {
                coins -= swordPrice;
                combatSkills++;
                weapon = "sword";
                cout << "You are now fighting with a sword!" << endl;
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
    cout << "1. Hunt (trap a rabbit)" << endl;
    cout << "2. Explore (talk to a villager)" << endl;
    cout << "3. Fight (duel a bandit)" << endl;
    cout << "4. View Stats" << endl;
    cout << "5. View Inventory" << endl;
    cout << "Choice: ";
}
 
void huntRabbit(int &energy, int &coins, int classChoice) {
    
    int takeEnergy, i = (rand() % 100);

    if (classChoice == 1) {
        takeEnergy = KNIGHTMAXENERGY * 0.2;
    } else if (classChoice == 2) {
        takeEnergy = MAGEMAXENERGY * 0.2;
    } else if (classChoice == 3) {
        takeEnergy = THIEFMAXENERGY * 0.2;
    }

    if (energy < takeEnergy) { cout << "Too tired!" << endl; return; }
    
    if (i % 2 == 0) {
        energy -= takeEnergy;
        coins += 10;
        cout << "A rabbit fell in your trap!" << endl;
        cout << "You sold the rabbit for 10 coins" << endl;
        cout << "-"<< takeEnergy << " EN" << endl;
    } else {
        energy -= takeEnergy;
        cout << "The rabbit fleed your trap" << endl;
        cout << "-"<< takeEnergy << " EN" << endl;
    }
}

void exploreVillager() {
    cout << "\n--- Villager ---" << endl;
    cout << "VILLAGER: \"The bandit guards an Energy Potion in his coin purse." << endl;
    cout << "         Take that, not his hat!\"" << endl;
}
 
void fightBandit(int &health, int combatSKills, int &energy, bool &energyPotion, bool &levelTwoDone, int classChoice) {
    cout << "\nA bandit blocks your path, dagger drawn!" << endl;
    int initialBanditHealth = 115 + ((rand() % 35) + 25);
    int banditHealth = initialBanditHealth;
    int choice;
    bool ranAway = false;
 
    while (banditHealth > 0 && health > 0 && !ranAway) {
        cout << "\nBandit HP: " << banditHealth << " | Your HP: " << health << " | CS: " << combatSKills << endl;
        cout << "1. Light attack" << endl;
        cout << "2. Strong attack" << endl;
        cout << "3. Run" << endl;
        cout << "Choice: ";
        cin >> choice;
 
        bool playerActed = false;
 
        if (choice == 1) {
            int dmg = doLightAttack(10, combatSKills);
            if (classChoice == 3) {
                dmg += 4;
            }
            if (dmg > 0) { banditHealth -= dmg; playerActed = true; }
        } else if (choice == 2) {
            int dmg = doStrongAttack(15, combatSKills);
            if (classChoice == 3) {
                dmg += 6;
            }
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
            int banditDmg = (rand() % 6) + 4;
            if (banditHealth <= (initialBanditHealth / 2)) { //if bandit loses more than half health > counter attack doubles
                banditDmg = banditDmg * 2;
            }
            health -= banditDmg;
            cout << "The bandit slashes you for " << banditDmg << " damage!" << endl;
        }
    }
 
    if (banditHealth <= 0 && health > 0) {
        cout << "\nThe bandit collapses!" << endl;
 
        int after;
        bool decided = false;
        while (!decided) {
            cout << "\n1. Take the bandit's knife" << endl;
            cout << "2. Take the bandit's coin purse" << endl;
            cout << "Choice: ";
            cin >> after;
            if (after == 1) {
                cout << "The knife is broken... keep exploring." << endl;
                decided = true;
            } else if (after == 2) {
                cout << "Inside the coin purse: an ENERGY POTION!" << endl;
                if (classChoice == 1) {
                    energy = KNIGHTMAXENERGY;
                } else if (classChoice == 2) {
                    energy = MAGEMAXENERGY;
                } else if (classChoice == 3) {
                    energy = THIEFMAXENERGY;
                }
                energyPotion = true;
                levelTwoDone = true;
                cout << "*** QUEST COMPLETE! Your max energy has been restored! ***" << endl;
                decided = true;
            } else {
                cout << "Invalid choice." << endl;
            }
        }
    }
}

void playLevelTwo(int &health, int &energy, int &coins, bool &energyPotion, bool &levelTwoDone, int &combatSkills, int classChoice, string &weapon) {
    cout << "\n=== LEVEL 2: THE VILLAGE ===" << endl;
    cout << "QUEST: Recover an energy potion from the bandit" << endl;
 
    int choice;
    while (!levelTwoDone && health > 0) {
        displayLevelTwoMenu();
        cin >> choice;
        switch (choice) {
            case 1: huntRabbit(energy, coins, classChoice); break;
            case 2: exploreVillager(); break;
            case 3: fightBandit(health, combatSkills, energy, energyPotion, levelTwoDone, classChoice); break;
            case 4: displayStats(health, energy, combatSkills, coins); break;
            case 5: displayInventory(weapon); break;
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
