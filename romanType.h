#ifndef GUARD_romanType
#define GUARD_romanType

#include <map>
#include <string>
#include <iostream>

class romanType {
    public:
        typedef std::map<char, int> mapS;
        typedef std::map<int, char> mapI;

        static mapS sToI;
        static mapS createMapS();
        static mapI iToS;
        static mapI createMapI();

        romanType(int);
        romanType(std::string);
        romanType() { intN = 1; numeral = "I"; }
        int getInt() const { return intN; }
        std::string getStr() const { return numeral; }
        romanType& print() { std::cout << numeral << std::endl; return *this; }
        romanType operator+(const romanType&) const;
        romanType operator-(const romanType&) const;
        romanType operator*(const romanType&) const;
        romanType operator/(const romanType&) const;
    private:
        int intN;
        std::string numeral;
        std::string digitToRoman(int) const;
        int leadingDigit(int) const;
        int nearestLesserRomanDigit(int) const;
        int magnitudeOf(int) const;
};

std::ostream& operator<<(std::ostream&, const romanType&);

#endif