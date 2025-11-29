#define MouseButtonFlags int


class Spell
{
public:
    Spell* Clone(); // 复制一份
};

class Weapon
{
protected:
    Spell* _spellPrototype;
    MouseButtonFlags _trigger;

public:
    void Attack();
    void HandleEvent();
    bool CanAttack();

    void SetSpellPrototype(Spell* spell);
    void SetTrigger(MouseButtonFlags trigger);
    void GetTrigger();
};