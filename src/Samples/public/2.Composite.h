#include <memory>
#include <vector>
#include <unordered_map>

class MoveControl
{
private:
    bool _isUp;
    bool _isDown;
    bool _isLeft;
    bool _isRight;

    std::vector<std::shared_ptr<MoveControl>> _components;

public:
    MoveControl() : _isUp(false), _isDown(false), _isLeft(false), _isRight(false) {}

    void SetUp(bool value);
    void SetDown(bool value);
    void SetLeft(bool value);
    void SetRight(bool value);
    virtual void Update();
    void AddComponent(std::shared_ptr<MoveControl> component);
    void RemoveComponent(std::shared_ptr<MoveControl> component);
};

class MoveControlArrow : public MoveControl
{
private:
    std::unordered_map <std::string, bool> _keyStates = {};

public:
    MoveControlArrow();
    void Update() override;

};

class MoveControlWASD : public MoveControl
{
private:
    std::unordered_map <std::string, bool> _keyStates = {};

public:
    MoveControlWASD();
    void Update() override;
};

class Player
{
private:
    std::shared_ptr<MoveControl> _moveControl;

public:
    Player(std::shared_ptr<MoveControl> moveControl) : _moveControl(moveControl) {}

    void Update();
};