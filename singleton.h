#ifndef SINGLETON_H
#define SINGLETON_H
/***********************************************************************
 * Module:  线程安全单例模板
 * Author:  wwq(Owen)
 * Modified: 2015年7月17日星期五
 * Purpose: 数据models 都是单例
 ***********************************************************************/
#include <mutex>

template<typename T>
class Singleton
{
 public:
	template<typename... Args>
	static T& instance(Args&&... args)
	{
		//线程安全， 只执行一次
		std::call_once(m_flag, [](Args&&... args){
								init(std::forward<Args>(args)...);
							}, std::forward<Args>(args)...);

		return *value_;
	}

 private:
  //不能在外面构造，复制，赋值
  Singleton();
  Singleton(const Singleton& other);
  Singleton &operator=(const Singleton& other);
  ~Singleton();

  template <typename... Args>
  static void init(Args&&... args)
  {
    value_ = new T(std::forward<Args>(args)...);
    ::atexit(destroy);
  }

  //内存，资源释放
  static void destroy()
  {
    delete value_;
  }

 private:
  //调用一次标志
  static std::once_flag m_flag;//调用一次标志
  static T* value_;
};


template<typename T>
T* Singleton<T>::value_ = NULL;

template<typename T>
std::once_flag Singleton<T>::m_flag;

#endif // SINGLETON_H

