#ifndef SPLITCALCULATOR_HPP
#define SPLITCALCULATOR_HPP

#include <vector>
#include <map>

#include "./SplitType.hpp"
#include "./User.hpp"
#include "./SplitWiseException.hpp"

/*
 *   Using factory pattern for SplitCalculator
*/

// SplitCalculator
class SplitCalculator {
    private:
        SplitType type;

    public:
        SplitCalculator(SplitType type) : type(type) {}
        virtual ~SplitCalculator() {}

        virtual bool calculateSplits(double amount, std::vector<std::pair<uintptr_t, double>> &shares) = 0;

        bool validateSplits(double amount, const std::map<uintptr_t, double> &shares);
        bool validateSplits(double amount, const std::vector<std::pair<uintptr_t, double>> &shares);
};

class EqualSplitCalculator : public SplitCalculator {
    public:
        EqualSplitCalculator() : SplitCalculator(SplitType::EQUAL) {}
        virtual ~EqualSplitCalculator() {}

        bool calculateSplits(double amount, std::vector<std::pair<uintptr_t, double>> &shares) final ;
};

class PercentageSplitCalculator : public SplitCalculator {
    public:
        PercentageSplitCalculator() : SplitCalculator(SplitType::PERCENT) {}
        virtual ~PercentageSplitCalculator() {}

        bool calculateSplits(double amount, std::vector<std::pair<uintptr_t, double>> &shares) final ;
};

class ExactSplitCalculator : public SplitCalculator {
    public:
        ExactSplitCalculator() : SplitCalculator(SplitType::EXACT) {}
        virtual ~ExactSplitCalculator() {}

        bool calculateSplits(double amount, std::vector<std::pair<uintptr_t, double>> &shares) final ;
};


// factory
class SplitCalculatorFactory {
    public:
        static SplitCalculator* createSplitCalculator(SplitType type) {
            switch (type) {
                case SplitType::EQUAL:
                    return new EqualSplitCalculator();
                case SplitType::PERCENT:
                    return new PercentageSplitCalculator();
                case SplitType::EXACT:
                    return new ExactSplitCalculator();
                default:
                    throw SplitWiseException("[ERR] Invalid SplitType");
                    return nullptr;
            }
        }
};

#endif