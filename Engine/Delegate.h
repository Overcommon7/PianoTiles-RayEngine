#pragma once
#include "pch.h"
#include "Observable.h"

namespace RayEngine
{

    class Delegate
    {
        vector<pair<IObservable*, bool>> queries;
        vector<IObservable*> observers;
        bool invoking = false;
    public:
        inline void Invoke()
        {
            auto it = observers.begin();
            invoking = true;
            while (it != observers.end())
            {
                if ((*it) == nullptr) it = observers.erase(it);
                else
                {
                    (*it)->OnInvoke();
                    ++it;
                }
            }
            invoking = false;

            if (queries.empty())  return;

            for (const auto& [query, type] : queries)
            {
                if (type)
                    this->operator+=(query);
                else this->operator-=(query);
            }
 
            queries.clear();
        }

        inline void operator+=(IObservable* observer) 
        {
            if (invoking)
            {
                queries.push_back({ observer, true });
                return;
            }


            auto it = find(observers.begin(), observers.end(), observer);
            if (it == observers.end()) observers.push_back(observer);
        }

        inline void operator-=(IObservable* observer)
        {

            if (invoking)
            {
                queries.push_back({ observer, false });
                return;
            }

            auto it = find(observers.begin(), observers.end(), observer);
            if (it != observers.end()) observers.erase(it);
        }
    };

    template<class T>
    class Delegate1
    {
        vector<pair<IObservable1<T>*, bool>> queries;
        vector<IObservable1<T>*> observers;
        bool invoking = false;
    public:
        inline void Invoke(T& arg1)
        {
            auto it = observers.begin();
            invoking = true;
            while (it != observers.end())
            {
                if ((*it) == nullptr) it = observers.erase(it);
                else
                {
                    (*it)->OnInvoke(arg1);
                    ++it;
                }
            }
            invoking = false;

            if (queries.empty())  return;

            for (const auto& [query, type] : queries)
            {
                if (type)
                    this->operator+=(query);
                else this->operator-=(query);
            }

            queries.clear();
        }

        inline void operator+=(IObservable1<T>* observer)
        {
            if (invoking)
            {
                queries.push_back({ observer, true });
                return;
            }


            auto it = find(observers.begin(), observers.end(), observer);
            if (it == observers.end()) observers.push_back(observer);
        }

        inline void operator-=(IObservable1<T>* observer)
        {

            if (invoking)
            {
                queries.push_back({ observer, false });
                return;
            }

            auto it = find(observers.begin(), observers.end(), observer);
            if (it != observers.end()) observers.erase(it);
        }

    };

    template<class T1, class T2>
    class Delegate2
    {
        vector<pair<IObservable2<T1, T2>*, bool>> queries;
        vector<IObservable2<T1, T2>*> observers;
        bool invoking = false;
    public:
        inline void Invoke(T1& arg1, T2& arg2)
        {
            auto it = observers.begin();
            invoking = true;
            while (it != observers.end())
            {
                if ((*it) == nullptr) it = observers.erase(it);
                else
                {
                    (*it)->OnInvoke(arg1, arg2);
                    ++it;
                }
            }
            invoking = false;

            if (queries.empty())  return;

            for (const auto& [query, type] : queries)
            {
                if (type)
                    this->operator+=(query);
                else this->operator-=(query);
            }

            queries.clear();
        }

        inline void operator+=(IObservable2<T1, T2>* observer)
        {
            if (invoking)
            {
                queries.push_back({ observer, true });
                return;
            }


            auto it = find(observers.begin(), observers.end(), observer);
            if (it == observers.end()) observers.push_back(observer);
        }

        inline void operator-=(IObservable2<T1, T2>* observer)
        {

            if (invoking)
            {
                queries.push_back({ observer, false });
                return;
            }

            auto it = find(observers.begin(), observers.end(), observer);
            if (it != observers.end()) observers.erase(it);
        }
    };

    template<class T1, class T2, class T3>
    class Delegate3
    {
        vector<pair<IObservable3<T1, T2, T3>*, bool>> queries;
        vector<IObservable3<T1, T2, T3>*> observers;
        bool invoking = false;
    public:
        inline void Invoke(T1& arg1, T2& arg2, T3& arg3)
        {
            auto it = observers.begin();
            invoking = true;
            while (it != observers.end())
            {
                if ((*it) == nullptr) it = observers.erase(it);
                else
                {
                    (*it)->OnInvoke(arg1, arg2, arg3);
                    ++it;
                }
            }
            invoking = false;

            if (queries.empty())  return;

            for (const auto& [query, type] : queries)
            {
                if (type)
                    this->operator+=(query);
                else this->operator-=(query);
            }

            queries.clear();
        }

        inline void operator+=(IObservable3<T1, T2, T3>* observer)
        {
            if (invoking)
            {
                queries.push_back({ observer, true });
                return;
            }


            auto it = find(observers.begin(), observers.end(), observer);
            if (it == observers.end()) observers.push_back(observer);
        }

        inline void operator-=(IObservable3<T1, T2, T3>* observer)
        {

            if (invoking)
            {
                queries.push_back({ observer, false });
                return;
            }

            auto it = find(observers.begin(), observers.end(), observer);
            if (it != observers.end()) observers.erase(it);
        }
    };
}
