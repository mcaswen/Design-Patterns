#include "public/2.Composite.h"
#include <unordered_map>
#include <memory>

void MoveControl::SetUp(bool value)
{
    _isUp = value;
}

void MoveControl::SetDown(bool value)
{
    _isDown = value;
}

void MoveControl::SetLeft(bool value)
{
    _isLeft = value;
}

void MoveControl::SetRight(bool value)
{
    _isRight = value;
}

void MoveControl::Update()
{
    for (auto component : _components)
    {
        component->Update();
    }
}

void MoveControl::AddComponent(std::shared_ptr<MoveControl> component)
{
    _components.push_back(component);
}

void MoveControl::RemoveComponent(std::shared_ptr<MoveControl> component)
{
    _components.erase(std::remove(_components.begin(), _components.end(), component), _components.end());
}

MoveControlArrow::MoveControlArrow()
{
    _keyStates["Up"] = false;
    _keyStates["Down"] = false;
    _keyStates["Left"] = false;
    _keyStates["Right"] = false;
}

void MoveControlArrow::Update()
{
    SetDown(_keyStates["Down"]);
    SetUp(_keyStates["Up"]);
    SetLeft(_keyStates["Left"]);
    SetRight(_keyStates["Right"]);
}

MoveControlWASD::MoveControlWASD()
{
    _keyStates["W"] = false;
    _keyStates["S"] = false;
    _keyStates["A"] = false;
    _keyStates["D"] = false;
}

void MoveControlWASD::Update()
{
    SetUp(_keyStates["W"]);
    SetDown(_keyStates["S"]);
    SetLeft(_keyStates["A"]);
    SetRight(_keyStates["D"]);
}

void Player::Update()
{
    _moveControl->Update();
}

int main()
{
    std::shared_ptr<MoveControlArrow> arrowControl = std::make_shared<MoveControlArrow>();
    std::shared_ptr<MoveControlWASD> wasdControl = std::make_shared<MoveControlWASD>();

    std::shared_ptr<MoveControl> compositeControl = std::make_shared<MoveControl>();
    compositeControl->AddComponent(arrowControl);
    // compositeControl->AddComponent(wasdControl);
    
    std::unique_ptr<Player> player = std::make_unique<Player>(compositeControl);
    // 游戏主循环
    while (true)
    {
        player->Update();
        // 其他游戏逻辑...
    }

    return 0;
}