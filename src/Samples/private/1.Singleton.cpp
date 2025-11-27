#include "public/1.Singleton.h"

Singleton& Singleton::GetInstance()
{
    static Singleton instance; // C++11之后才支持并推荐的单例模式

    return instance;
}

SingletonBeforeCpp11* SingletonBeforeCpp11::_instance = nullptr; // 定义或初始化是允许的，私有属性只限制读写/访问
std::mutex SingletonBeforeCpp11::_mutex;
std::once_flag SingletonBeforeCpp11::_onceFlag;

SingletonBeforeCpp11* SingletonBeforeCpp11::GetInstance()
{
    // 用到的时候再创建（懒加载）
    // 但是多线程不安全
    // 加一把锁，一次只允许一个线程通过，
    std::lock_guard<std::mutex> lock(_mutex);

    if (!_instance)
    {
        _instance = new SingletonBeforeCpp11();
    }

    return _instance;
}

SingletonBeforeCpp11* SingletonBeforeCpp11::GetInstance2()
{
    // 从语义上保证只会初始化一次
    std::call_once(_onceFlag, InitInstance);
    return _instance;
}

void SingletonBeforeCpp11::InitInstance()
{
    _instance = new SingletonBeforeCpp11();
}

void SingletonBeforeCpp11::Destroy()
{
    delete _instance;
    _instance = nullptr;
}

//在程序生命周期结束时
// SingletonBeforeCpp11::Destroy();

// 双重检查锁定：静态成员初始化
SingletonDoubleChecked* SingletonDoubleChecked::_instance = nullptr;
pthread_mutex_t SingletonDoubleChecked::_mutex = PTHREAD_MUTEX_INITIALIZER;

SingletonDoubleChecked* SingletonDoubleChecked::GetInstance() 
{
    // 第一次检查：避免每次调用都加锁
    if (_instance == nullptr) 
    {
        // 加锁确保线程安全
        pthread_mutex_lock(&_mutex);
        
        // 第二次检查：防止多个线程同时通过第一次检查
        if (_instance == nullptr) {
            _instance = new SingletonDoubleChecked();
        }
        
        pthread_mutex_unlock(&_mutex);
    }
    return _instance;
}

// 手动清理资源
void SingletonDoubleChecked::Destroy() {
    pthread_mutex_lock(&_mutex);
    
    if (_instance != nullptr) {
        delete _instance;
        _instance = nullptr;
    }
    
    pthread_mutex_unlock(&_mutex);
    pthread_mutex_destroy(&_mutex);
}

