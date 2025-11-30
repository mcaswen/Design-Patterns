#include "public/3.Prototype.h"

Spell* Spell::Clone()
{
    // 返回一个 Spell 对象的副本，这里不提供具体实现
    return new Spell(*this);
}

void Weapon::Attack()
{
    // 不会在外部创建 Spell 实例, 而在Attack内部通过原型复制一份
    // 防止 Spell 被创建而攻击无法执行造成的性能浪费
    if (!_spellPrototype || !CanAttack()) return; 

    // 使用原型创建一个新的法术实例
    Spell* spell = _spellPrototype->Clone();
    // 施放法术的逻辑
    // ...
    delete spell; // 假设施放后销毁法术实例
}

void Weapon::HandleEvent()
{
    // if (event.buttonFlags.button == _trigger)
    {
        Attack(); //无需检查逻辑
    }
}