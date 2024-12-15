#ifndef VIDA_H
#define VIDA_H

class Vida {
public:
    Vida(int maxHealth);
    ~Vida();
    void render();
    void setHealth(int health);
    int getHealth() const;

private:
    int maxHealth;
    int currentHealth;
};

#endif