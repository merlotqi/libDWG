/**
 * libDWG - A C++ library for reading and writing DWG and DXF files in CAD.
 *
 * This file is part of libDWG.
 *
 * libDWG is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * libDWG is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * For more information, visit the project's homepage or contact the author.
 */

#pragma once

#include "DelegateT.h"
#include <memory>
#include <mutex>
#include <type_traits>
#include <vector>

namespace dwg {

// Delegate class template for function signatures with a return type and arguments.
template<typename Return, typename... Args>
class Delegate;

// Specialization of Delegate for function signatures with a return type and arguments.
template<typename Return, typename... Args>
class Delegate<Return(Args...)>
{
    // Alias for shared pointer to a DelegateT instance.
    typedef std::shared_ptr<DelegateT<Return, Args...>> ptr;

    // A list of all delegates that can be invoked.
    std::vector<ptr> invoke_delegates;

    // Mutex for thread-safe operations on the delegate list.
    std::mutex _mutex;

public:
    // Default constructor.
    Delegate() = default;

    // Destructor, clears the list of delegates.
    ~Delegate()
    {
        clear();
    }

    // Clears all delegates from the list.
    void clear()
    {
        invoke_delegates.clear();
    }

    // Add a static function delegate.
    template<typename Fun>
    void add(Fun _fun)
    {
        // Lock the mutex for thread safety.
        std::unique_lock<std::mutex> l(this->_mutex);

        // Create a new delegate from the function.
        ptr oneDelegate(new_delegate(_fun));

        // If the delegate is valid.
        if (oneDelegate)
        {
            // Check if this delegate is already in the list.
            for (auto &_invokeObj: invoke_delegates)
            {
                if (oneDelegate->compare(_invokeObj.get()))
                {
                    return;
                }
            }
            // Add the delegate to the list.
            invoke_delegates.emplace_back(oneDelegate);
        }
    }

    // Add a class member function delegate.
    template<typename T, typename Fun>
    void add(T *_object, Fun _fun)
    {
        // Lock the mutex for thread safety.
        std::unique_lock<std::mutex> l(this->_mutex);

        // Create a new delegate from the object and function.
        ptr oneDelegate(new_delegate(_object, _fun));

        // If the delegate is valid.
        if (oneDelegate)
        {
            // Check if this delegate is already in the list.
            for (auto &_invokeObj: invoke_delegates)
            {
                if (oneDelegate->compare(_invokeObj.get()))
                {
                    return;
                }
            }
            // Add the delegate to the list.
            invoke_delegates.emplace_back(oneDelegate);
        }
    }

    // Remove a static function delegate.
    template<typename Fun>
    void remove(Fun _fun)
    {
        // Lock the mutex for thread safety.
        std::unique_lock<std::mutex> l(this->_mutex);

        // Create a new delegate from the function.
        ptr oneDelegate(new_delegate(_fun));

        // If the delegate is valid.
        if (oneDelegate)
        {
            // Iterate through the list and remove matching delegates.
            auto it = invoke_delegates.begin();
            while (it != invoke_delegates.end())
            {
                if (oneDelegate->compare(it->get()))
                {
                    // Erase the matching delegate.
                    invoke_delegates.erase(it);
                    return;
                }
                ++it;
            }
        }
    }

    // Remove a class member function delegate.
    template<typename T, typename Fun>
    void remove(T *_object, Fun _fun)
    {
        // Lock the mutex for thread safety.
        std::unique_lock<std::mutex> l(this->_mutex);

        // Create a new delegate from the object and function.
        ptr oneDelegate(new_delegate(_object, _fun));

        // If the delegate is valid.
        if (oneDelegate)
        {
            // Iterate through the list and remove matching delegates.
            auto it = invoke_delegates.begin();
            while (it != invoke_delegates.end())
            {
                if (oneDelegate->compare(it->get()))
                {
                    // Erase the matching delegate.
                    invoke_delegates.erase(it);
                    return;
                }
                ++it;
            }
        }
    }

    // Invoke all stored delegates with the given arguments.
    std::vector<Return> operator()(Args... args)
    {
        // Create a vector to store the return values.
        std::vector<Return> vecRt;

        // Iterate through each delegate and invoke it if valid.
        for (auto &_invokeObj: invoke_delegates)
        {
            if (_invokeObj && _invokeObj->canInvoke())
            {
                // Invoke the delegate and store the result.
                vecRt.push_back(_invokeObj->invoke(std::forward<Args>(args)...));
            }
        }
        return vecRt;
    }
};

// Specialization of Delegate for function signatures returning void.
template<typename... Args>
class Delegate<void(Args...)>
{
    // Alias for shared pointer to a DelegateT instance (void return type).
    typedef std::shared_ptr<DelegateT<void, Args...>> ptr;

    // A list of all delegates that can be invoked.
    std::vector<ptr> invoke_delegates;

    // Mutex for thread-safe operations on the delegate list.
    std::mutex _mutex;

public:
    // Default constructor.
    Delegate() = default;

    // Destructor, clears the list of delegates.
    ~Delegate()
    {
        clear();
    }

    // Clears all delegates from the list.
    void clear()
    {
        invoke_delegates.clear();
    }

    // Add a static function delegate.
    template<typename Fun>
    void add(Fun &&_fun)
    {
        // Lock the mutex for thread safety.
        _mutex.lock();

        // Create a new delegate from the function.
        ptr oneDelegate(new_delegate(_fun));

        // If the delegate is valid.
        if (oneDelegate)
        {
            // Check if this delegate is already in the list.
            for (auto &_invokeObj: invoke_delegates)
            {
                if (oneDelegate->compare(_invokeObj.get()))
                {
                    _mutex.unlock();
                    return;
                }
            }
            // Add the delegate to the list.
            invoke_delegates.emplace_back(oneDelegate);
        }
        _mutex.unlock();
    }

    // Add a class member function delegate.
    template<typename T, typename Fun>
    void add(T *_object, Fun &&_fun)
    {
        // Lock the mutex for thread safety.
        _mutex.lock();

        // Create a new delegate from the object and function.
        ptr oneDelegate(new_delegate(_object, _fun));

        // If the delegate is valid.
        if (oneDelegate)
        {
            // Check if this delegate is already in the list.
            for (auto &_invokeObj: invoke_delegates)
            {
                if (oneDelegate->compare(_invokeObj.get()))
                {
                    _mutex.unlock();
                    return;
                }
            }
            // Add the delegate to the list.
            invoke_delegates.emplace_back(oneDelegate);
        }
        _mutex.unlock();
    }

    // Remove a static function delegate.
    template<typename Fun>
    void remove(Fun &&_fun)
    {
        // Lock the mutex for thread safety.
        _mutex.lock();

        // Create a new delegate from the function.
        ptr oneDelegate(new_delegate(_fun));

        // If the delegate is valid.
        if (oneDelegate)
        {
            // Iterate through the list and remove matching delegates.
            auto it = invoke_delegates.begin();
            while (it != invoke_delegates.end())
            {
                if (oneDelegate->compare(it->get()))
                {
                    // Erase the matching delegate.
                    invoke_delegates.erase(it);
                    _mutex.unlock();
                    return;
                }
                ++it;
            }
        }
        _mutex.unlock();
    }

    // Remove a class member function delegate.
    template<typename T, typename Fun>
    void remove(T *_object, Fun &&_fun)
    {
        // Lock the mutex for thread safety.
        _mutex.lock();

        // Create a new delegate from the object and function.
        ptr oneDelegate(new_delegate(_object, _fun));

        // If the delegate is valid.
        if (oneDelegate)
        {
            // Iterate through the list and remove matching delegates.
            auto it = invoke_delegates.begin();
            while (it != invoke_delegates.end())
            {
                if (oneDelegate->compare(it->get()))
                {
                    // Erase the matching delegate.
                    invoke_delegates.erase(it);
                    _mutex.unlock();
                    return;
                }
                ++it;
            }
        }
        _mutex.unlock();
    }

    // Invoke all stored delegates with the given arguments.
    void operator()(Args... args)
    {
        // Iterate through each delegate and invoke it if valid.
        for (auto &_invokeObj: invoke_delegates)
        {
            if (_invokeObj && _invokeObj->canInvoke())
            {
                // Invoke the delegate.
                _invokeObj->invoke(std::forward<Args>(args)...);
            }
        }
    }
};

}// namespace dwg