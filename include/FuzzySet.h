#pragma once

#include <string>
#include <unordered_map>
#include <initializer_list>
#include <ostream>

#include "boost/numeric/ublas/vector.hpp"
#include "boost/numeric/ublas/matrix.hpp"

namespace FuzzyLogic
{
    template<typename T>
    class FuzzySet
    {
    public:
        FuzzySet(std::wstring name, const boost::numeric::ublas::vector<T>& values, const boost::numeric::ublas::vector<std::wstring>& terms);
        FuzzySet(std::wstring name, const boost::numeric::ublas::vector<T>& values, const std::initializer_list<std::wstring>& terms);
        FuzzySet(std::wstring name, const std::initializer_list<T>& values, const std::initializer_list<std::wstring>& terms);
        FuzzySet(std::wstring name, const std::unordered_map<std::wstring, T> set);

        boost::numeric::ublas::vector<T> getUblasVectorValues() const;
        boost::numeric::ublas::vector<std::wstring> getUblasVectorTerms() const;
        std::wstring getName() const;
        std::unordered_map<std::wstring, T> getSet() const;

        template<typename U>
        friend std::wostream& operator<<(std::wostream& out, const FuzzySet<U>& fs);

        T operator[](std::wstring term) const
        {
            return set_.at(term);
        }

    private:
        std::wstring set_name_;
        std::unordered_map<std::wstring, T> set_;
    };




    template<typename T>
    FuzzySet<T>::FuzzySet(std::wstring name, const boost::numeric::ublas::vector<T>& values, const boost::numeric::ublas::vector<std::wstring>& terms)
    {
        for (size_t i = 0; i < values.size(); ++i)
            set_[terms[i]] = values[i];

        set_name_ = name;
    }

    //template<typename T>
    //FuzzySet<T>::FuzzySet(std::wstring name, const std::initializer_list<T>& values, const std::vector<std::wstring>& terms)
    //{
    //    for (size_t i = 0; i < values.size(); ++i)
    //        set_[terms[i]] = values[i];
    //    set_name_ = name;
    //}

    template<typename T>
    FuzzySet<T>::FuzzySet(std::wstring name, const boost::numeric::ublas::vector<T>& values, const std::initializer_list<std::wstring>& terms)
    {
        for (size_t i = 0; i < values.size(); ++i)
            set_[terms[i]] = values(i);
        set_name_ = name;
    }

    template<typename T>
    FuzzySet<T>::FuzzySet(std::wstring name, const std::initializer_list<T>& values, const std::initializer_list<std::wstring>& terms)
    {
        for (size_t i = 0; i < values.size(); ++i)
            set_[terms[i]] = values[i];
        set_name_ = name;
    }

    template<typename T>
    FuzzySet<T>::FuzzySet(std::wstring name, const std::unordered_map<std::wstring, T> set)
    {
        set_ = set;
        set_name_ = name;
    }



    template<typename T>
    boost::numeric::ublas::vector<T> FuzzySet<T>::getUblasVectorValues() const
    {
        boost::numeric::ublas::vector<T> out(set_.size());
        size_t i = 0;
        for (const auto& item : set_)
        {
            out[i] = item.second;
            i++;
        }

        return out;
    }

    template<typename T>
    inline boost::numeric::ublas::vector<std::wstring> FuzzySet<T>::getUblasVectorTerms() const
    {
        boost::numeric::ublas::vector<std::wstring> out(set_.size());
        size_t i = 0;
        for (const auto& item : set_)
        {
            out[i] = item.first;
            i++;
        }

        return out;
    }

    template<typename T>
    inline std::wstring FuzzySet<T>::getName() const
    {
        return set_name_;
    }

    template<typename T>
    inline std::unordered_map<std::wstring, T> FuzzySet<T>::getSet() const
    {
        return set_;
    }

    template<typename U>
    inline std::wostream& operator<<(std::wostream& out, const FuzzySet<U>& fs)
    {
        out << fs.set_name_ << L" = ";
        for (const auto& item : fs.set_)
            out << item.second << L'/' << item.first << ' ';

        return out;
    }
   
    //template<typename U>
    //inline U FuzzySet<U>::operator[](std::wstring term)
    //{
    //    return set_[term];
    //}
}

