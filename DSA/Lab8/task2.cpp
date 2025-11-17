#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

class combatant {
public:
    string name;
    int hp;
    int attack;

    combatant() {}
    combatant(string n, int h, int a) {
        name = n;
        hp = h;
        attack = a;
    }
};

struct node {
    combatant data;
    node* left;
    node* right;
};

class bst {
    node* root;

    node* insertnode(node* root, combatant c) {
        if (root == NULL) {
            node* newnode = new node;
            newnode->data = c;
            newnode->left = newnode->right = NULL;
            return newnode;
        }
        if (c.name < root->data.name)
            root->left = insertnode(root->left, c);
        else if (c.name > root->data.name)
            root->right = insertnode(root->right, c);
        return root;
    }

    node* findmin(node* root) {
        while (root && root->left != NULL)
            root = root->left;
        return root;
    }

    node* deletenode(node* root, string name) {
        if (root == NULL) return root;

        if (name < root->data.name)
            root->left = deletenode(root->left, name);
        else if (name > root->data.name)
            root->right = deletenode(root->right, name);
        else {
            if (root->left == NULL) {
                node* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == NULL) {
                node* temp = root->left;
                delete root;
                return temp;
            }
            node* temp = findmin(root->right);
            root->data = temp->data;
            root->right = deletenode(root->right, temp->data.name);
        }
        return root;
    }

    void inorder(node* root) {
        if (root != NULL) {
            inorder(root->left);
            cout << root->data.name << "(" << root->data.hp << "HP) ";
            inorder(root->right);
        }
    }

public:
    bst() {
        root = NULL;
    }

    void insert(combatant c) {
        root = insertnode(root, c);
    }

    void remove(string name) {
        root = deletenode(root, name);
    }

    node* getroot() {
        return root;
    }

    bool isempty() {
        return root == NULL;
    }

    node* getfrontline() {
        return findmin(root);
    }

    void showteam() {
        inorder(root);
        cout << endl;
    }
};

class battlequest {
    bst heroes;
    bst enemies;
    int round;

public:
    battlequest() {
        round = 1;
        srand(time(0));

        heroes.insert(combatant("Saad", 25, 5));
        heroes.insert(combatant("Aizen", 30, 6));
        heroes.insert(combatant("Ahmed", 28, 7));
        heroes.insert(combatant("Danial", 22, 8));
        heroes.insert(combatant("Elvish", 26, 6));

        enemies.insert(combatant("Dev", 24, 5));
        enemies.insert(combatant("Trojan", 30, 7));
        enemies.insert(combatant("Kapkan", 18, 4));
        enemies.insert(combatant("Mira", 20, 6));
        enemies.insert(combatant("Deimos", 22, 5));
    }

    void displayteams() {
        cout << "\nHeroes: ";
        heroes.showteam();
        cout << "Enemies: ";
        enemies.showteam();
    }

    void attackturn(node* attacker, node* defender, bst& defendteam) {
        int bonus = rand() % 5; 
        int damage = attacker->data.attack + bonus;
        defender->data.hp -= damage;

        cout << attacker->data.name << " attacks " << defender->data.name
             << " for " << damage << " damage! ";

        if (defender->data.hp <= 0) {
            cout << defender->data.name << " is defeated!\n";
            defendteam.remove(defender->data.name);
        } else {
            cout << defender->data.name << " has " << defender->data.hp << " HP left.\n";
        }
    }

    void startbattle() {
        cout << "\n=== BattleQuest: BST Arena ===\n";
        while (!heroes.isempty() && !enemies.isempty()) {
            cout << "\n--- Round " << round << " ---\n";
            displayteams();

            node* hero = heroes.getfrontline();
            node* enemy = enemies.getfrontline();

            if (hero && enemy) {
                cout << "\nPlayer's Turn:\n";
                attackturn(hero, enemy, enemies);
            }

            if (!enemies.isempty()) {
                hero = heroes.getfrontline();
                enemy = enemies.getfrontline();
                if (hero && enemy) {
                    cout << "\nEnemy's Turn:\n";
                    attackturn(enemy, hero, heroes);
                }
            }

            round++;
        }

        if (heroes.isempty() && enemies.isempty())
            cout <<endl<< "Both teams are down! It's a draw!\n";
        else if (enemies.isempty())
            cout <<endl<< "Heroes win the battle!\n";
        else
            cout <<endl<< "Enemies win the battle!\n";
    }
};

int main() {
    battlequest game;
    game.startbattle();
    return 0;
}
