#pragma once
#include "pch.h"
#include "Observable.h"

namespace RayEngine
{

    class Delegate
    {
        vector<IObservable*> observers;
    public:
        inline void Invoke()
        {
            auto it = observers.begin();
            while (it != observers.end())
            {
                if ((*it) == nullptr) it = observers.erase(it);
                else
                {
                    try
                    {
                        (*it)->OnInvoke();
                        ++it;
                    }
                    catch (std::exception&)
                    {
                        it = observers.erase(it);
                    }
                }
            }
        }

        inline void operator+=(IObservable* observer) 
        {
            auto it = find(observers.begin(), observers.end(), observer);
            if (it == observers.end()) observers.push_back(observer);
        }

        inline void operator-=(IObservable* observer)
        {
            auto it = find(observers.begin(), observers.end(), observer);
            if (it != observers.end()) observers.erase(it);
        }
    };

    template<class T>
    class Delegate1
    {
        vector<IObservable1<T>*> observers;
    public:
        inline void Invoke(T& arg1)
        {
            auto it = observers.begin();
            while (it != observers.end())
            {
                if ((*it) == nullptr) it = observers.erase(it);
                else
                {
                    try
                    {
                        (*it)->OnInvoke(arg1);
                        ++it;
                    }
                    catch (std::exception&)
                    {
                        it = observers.erase(it);
                    }
                }
            }
                
        }

        inline void operator+=(IObservable1<T>* observer)
        {
            auto it = find(observers.begin(), observers.end(), observer);
            if (it == observers.end()) observers.push_back(observer);
        }

        inline void operator-=(IObservable1<T>* observer)
        {
            auto it = find(observers.begin(), observers.end(), observer);
            if (it != observers.end()) observers.erase(it);
        }


    };

    template<class T1, class T2>
    class Delegate2
    {
        vector<IObservable2<T1, T2>*> observers;
    public:
        inline void Invoke(T1& arg1, T2& arg2)
        {
            auto it = observers.begin();
            while (it != observers.end())
            {
                if ((*it) == nullptr) it = observers.erase(it);
                else
                {
                    try
                    {
                        (*it)->OnInvoke(arg1, arg2);
                        ++it;
                    }
                    catch (std::exception&)
                    {
                        it = observers.erase(it);
                    }
                }
            }
        }

        inline void operator+=(IObservable2<T1, T2>* observer)
        {
            auto it = find(observers.begin(), observers.end(), observer);
            if (it == observers.end()) observers.push_back(observer);
        }

        inline void operator-=(IObservable2<T1, T2>* observer)
        {
            auto it = find(observers.begin(), observers.end(), observer);
            if (it != observers.end()) observers.erase(it);
        }
    };

    template<class T1, class T2, class T3>
    class Delegate3
    {
        vector<IObservable3<T1, T2, T3>*> observers;
    public:
        inline void Invoke(T1& arg1, T2& arg2, T3& arg3)
        {
            auto it = observers.begin();
            while (it != observers.end())
            {
                if ((*it) == nullptr) it = observers.erase(it);
                else
                {
                    try
                    {
                        (*it)->OnInvoke(arg1, arg2, arg3);
                        ++it;
                    }
                    catch (std::exception&)
                    {
                        it = observers.erase(it);
                    }
                }
            }
        }

        inline void operator+=(IObservable3<T1, T2, T3>* observer)
        {
            auto it = find(observers.begin(), observers.end(), observer);
            if (it == observers.end()) observers.push_back(observer);
        }

        inline void operator-=(IObservable3<T1, T2, T3>* observer)
        {
            auto it = find(observers.begin(), observers.end(), observer);
            if (it != observers.end()) observers.erase(it);
        }
    };
}
