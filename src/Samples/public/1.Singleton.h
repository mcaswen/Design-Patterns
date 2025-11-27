#include <mutex>

// 推荐写法
class Singleton 
{
    public:
        // 禁止拷贝和赋值运算符
        Singleton(const Singleton&) = delete;
        Singleton& operator=(const Singleton&) = delete;

        Singleton(Singleton&&) = delete;
        Singleton& operator=(Singleton&&) = delete;

        Singleton& GetInstance();

    private:
        // 私有构造函数
        Singleton() {}
        ~Singleton() {}

};

// C++11 之前的写法
class SingletonBeforeCpp11 
{
    public:
        // C++11后才支持
        // SingletonBeforeCpp11(const SingletonBeforeCpp11&) = delete;
        // SingletonBeforeCpp11& operator=(const SingletonBeforeCpp11&) = delete;

        static SingletonBeforeCpp11* GetInstance();
        static SingletonBeforeCpp11* GetInstance2();
        static void InitInstance();
        static void Destroy();

    private:
        static std::mutex _mutex;

        static std::once_flag _onceFlag;

        static SingletonBeforeCpp11* _instance;

        // 私有构造函数
        SingletonBeforeCpp11() {}
        ~SingletonBeforeCpp11() {}
            
        SingletonBeforeCpp11(const SingletonBeforeCpp11&) = delete;
        SingletonBeforeCpp11& operator=(const SingletonBeforeCpp11&) = delete;
        
        // static SingletonBeforeCpp11 _instance = nullptr; // 无法初始化

};

class SingletonDoubleChecked 
{
    public:
        static SingletonDoubleChecked* GetInstance();
        static void Destroy();

    private:
        static SingletonDoubleChecked* _instance;
        static pthread_mutex_t _mutex;
    
        // 私有构造函数
        SingletonDoubleChecked() {}
        ~SingletonDoubleChecked() {}
        
        // 防止拷贝
        SingletonDoubleChecked(const SingletonDoubleChecked&);
        SingletonDoubleChecked& operator=(const SingletonDoubleChecked&);
};
