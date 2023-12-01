#include "poly.h"
#include <algorithm>
#include <iostream>
#include <thread>
#include <map>

//#define DEBUG

polynomial::polynomial() : terms( {{0,0}} ) {}

template <typename Iter>
polynomial::polynomial(Iter begin, Iter end)
{
    while (begin != end)
    {
        terms.push_back(*begin);
        begin++;
        // //We want to maintain descending sort order when inserting
        // auto insertionPoint = std::lower_bound(terms.begin(), terms.end(), *it, [](const auto& a, const auto& b) {
        //     return a.first > b.first;
        // });
        // terms.insert(insertionPoint, *it);
    }
}

void polynomial::print() const
{
    for (const auto& term : terms) {
        std::cout << term.second << "x^" << term.first << " + ";
    }
    std::cout << std::endl;
}

polynomial::polynomial(const polynomial &other)
{
    terms = other.terms;
}

polynomial& polynomial::operator=(const polynomial &other)
{
    //Deep copy of other polynomial
    //Handle self assignment
    if (this == &other)
    {
        return *this;
    }
    terms.clear();
    terms = other.terms;

    return *this;

}

size_t polynomial::find_degree_of() const
{
    //Ascending order polynomial
    return terms.back().first;
}

std::vector<std::pair<power, coeff>> polynomial::canonical_form() const
{
    std::vector<std::pair<size_t, int>> canonicalTerms = terms;

    // Remove zero coefficients
    canonicalTerms.erase(std::remove_if(canonicalTerms.begin(), canonicalTerms.end(),
        [](const auto& term) { return term.second == 0; }), canonicalTerms.end());

    // If all terms are removed or the polynomial is empty, return a single {0, 0} pair
    if (canonicalTerms.empty()) {
        return {{0, 0}};
    }

    // Sort terms based on power (descending order)
    std::sort(canonicalTerms.begin(), canonicalTerms.end(),
        [](const auto& a, const auto& b) { return a.first < b.first; });



    return canonicalTerms;
}

polynomial polynomial::operator+(int val) const 
{
    polynomial p(*this);
    std::vector<std::pair<power, coeff>> canonTerms = canonical_form();
    if (canonTerms.back().first != 0)
    {
        canonTerms.push_back({0, val});
    }
    else 
    {
        canonTerms.back().second += val;
    }
    return polynomial(canonTerms.begin(), canonTerms.end());
}

polynomial polynomial::operator+(const polynomial &other) const 
{
    //Implementation assumes terms are sorted ascending by power
    polynomial new_poly;
    auto it1 = this->terms.begin();
    auto it2 = other.terms.begin();

    while (it1 != terms.end() && it2 != other.terms.end()) {
        //powers match so we add the terms then push
        if (it1->first == it2->first) {
            new_poly.terms.push_back({it1->first, it1->second + it2->second});
            ++it1;
            ++it2;
        }
        // Next highest power is in the first polynomial  
        else if (it1->first < it2->first) {
            new_poly.terms.push_back(*it1);
            ++it1;
        } 
        else 
        {
            new_poly.terms.push_back(*it2);
            ++it2;
        }
    }

    while (it1 != terms.end()) {
        new_poly.terms.push_back(*it1);
        ++it1;
    }

    while (it2 != other.terms.end()) {
        new_poly.terms.push_back(*it2);
        ++it2;
    }
    
    std::sort(new_poly.terms.begin(), new_poly.terms.end(), [](const auto& a, const auto& b) {
            return a.first > b.first; // Sort in descending order of powers
        });

    return new_poly;
}

polynomial operator+(int val, const polynomial &other)
{
    std::vector<std::pair<power, coeff>> result = other.terms;

    if (result.back().first == 0)
    {
        result.back().second += val;
    }

    return polynomial(result.begin(), result.end());
}

polynomial polynomial::operator*(int val) const 
{
    if (val == 0)
    {
        return polynomial();
    }
    std::vector<std::pair<power, coeff>> result = terms;

    //To multiply each term by the val
    for (auto &term : result)
    {
        term.second *= val;
    }
    
    return polynomial(result.begin(), result.end());
}

polynomial polynomial::operator*(const polynomial &other) const 
{
    std::map<power, coeff> resultMap;

    auto multiplyTermsInRange = [&](size_t start, size_t end) {
        // #ifdef DEBUG
        // std::cout << resultTerms.capacity() << resultTerms.size() << std::endl;
        // #endif
        for (size_t i = start; i < end; ++i) {
            for (size_t j = 0; j < other.terms.size(); ++j) {
                size_t power = terms[i].first + other.terms[j].first;
                int coefficient = terms[i].second * other.terms[j].second;
                mtx.lock();
                resultMap[power] += coefficient;
                mtx.unlock();
            }
        }
    };

    //const size_t numThreads = std::thread::hardware_concurrency();
    size_t numThreads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;

    //std::cout << "Creating threads" << std::endl;
    for (size_t i = 0; i < numThreads; ++i) {
        size_t start = (i * terms.size()) / numThreads;
        size_t end = ((i + 1) * terms.size()) / numThreads;
        threads.emplace_back(multiplyTermsInRange, start, end);
    }

    //std::cout << "Joining threads" << std::endl;
    for (int i = 0; i < numThreads; i++) {
        #ifdef DEBUG
        std::cout << "Thread " << i << std::endl;
        #endif
        threads[i].join();
    }

    //std::cout << "Removing zeros" << std::endl;
    std::vector<std::pair<power, coeff>> canonicalTerms;

    for (const auto& term : resultMap) {
        if (term.second != 0) { // Filter out zero coefficients
            canonicalTerms.push_back(term);
        }
    }

    // Sort the terms based on the power (ascending order)
    std::sort(canonicalTerms.begin(), canonicalTerms.end(), [](const auto& a, const auto& b) {
        return a.first < b.first;
    });

    return polynomial(canonicalTerms.begin(), canonicalTerms.end());
}

bool polynomial::isZero() const
{
    if (terms.size() == 1)
    {
        if (terms.at(0).second == 0) return true;
    }
    return false;
}

polynomial operator*(int val, const polynomial &other)
{
    if (val == 0)
    {
        return polynomial();
    }

    polynomial new_poly(other);

    for (auto &term: new_poly.terms)
    {
        term.second *= val;
    }

    return new_poly;
}

polynomial polynomial::operator%(const polynomial &other) const 
{
    if (other.find_degree_of() > find_degree_of())
    {
        return *this;
    }


    std::map<power, coeff> resultMap;

    auto calculateModulus = [&](size_t start, size_t end) {
        for (size_t i = start; i <= end; ++i) {
            for (size_t j = 0; j < other.terms.size(); ++j) {
                size_t power = terms[i + j].first - other.terms[j].first;
                int coefficient = terms[i + j].second / other.terms[j].second;

                mtx.lock();
                resultMap[power] += coefficient;
                mtx.unlock();
            }
        }
    };

    size_t numThreads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;

    size_t chunkSize = terms.size() / numThreads;

    for (size_t i = 0; i < numThreads; ++i) {
        size_t start = (i * terms.size()) / numThreads;
        size_t end = ((i + 1) * terms.size()) / numThreads;
        threads.emplace_back(calculateModulus, start, end);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    // Further processing of resultTerms to remove zero terms and return the final polynomial
    std::vector<std::pair<power, coeff>> canonicalTerms;

    for (const auto& term : resultMap) {
        if (term.second != 0) { // Filter out zero coefficients
            canonicalTerms.push_back(term);
        }
    }

    // Sort the terms based on the power (ascending order)
    std::sort(canonicalTerms.begin(), canonicalTerms.end(), [](const auto& a, const auto& b) {
        return a.first < b.first;
    });

    return polynomial(canonicalTerms.begin(), canonicalTerms.end());

    return polynomial(canonicalTerms.begin(), canonicalTerms.end());
}



