#include "romanType.h"
#include <vector>
#include <cmath>

std::ostream& operator<<(std::ostream& stream, const romanType& numeral) {
    stream << numeral.getStr();
    return stream;
}

romanType::mapS romanType::sToI = romanType::createMapS();
romanType::mapI romanType::iToS = romanType::createMapI();

romanType romanType::operator+(const romanType& other) const {
    return romanType(intN + other.intN);
}

romanType romanType::operator-(const romanType& other) const {
    return romanType(intN - other.intN);
}

romanType romanType::operator*(const romanType& other) const {
    return romanType(intN * other.intN);
}

romanType romanType::operator/(const romanType& other) const {
    return romanType(intN / other.intN);
}

romanType::mapS romanType::createMapS() {
    mapS sToI;
    sToI.emplace('M', 1000);
    sToI.emplace('D', 500);
    sToI.emplace('C', 100);
    sToI.emplace('L', 50);
    sToI.emplace('X', 10);
    sToI.emplace('V', 5);
    sToI.emplace('I', 1);
    return sToI;
}

romanType::mapI romanType::createMapI() {
    mapI iToS;
    iToS.emplace(1000, 'M');
    iToS.emplace(500, 'D');
    iToS.emplace(100, 'C');
    iToS.emplace(50, 'L');
    iToS.emplace(10, 'X');
    iToS.emplace(5, 'V');
    iToS.emplace(1, 'I');
    return iToS;
}

int romanType::leadingDigit(int n) const {
    while (n >= 10) {
        n /= 10;
    }
    return n;
}

int romanType::magnitudeOf(int n) const {
    int power = 0;

    while (n != 0) {
        n /= 10;
        power += 1;
    }
    return std::pow(10, power - 1);
}

int romanType::nearestLesserRomanDigit(int n) const {
    int magnitude = magnitudeOf(n);

    while (romanType::iToS[n] == NULL) {
        n -= magnitude;
    }

    return n;
}

std::string romanType::digitToRoman(int n) const {
    if (n == 0) 
        return "";

    int ld_digit = leadingDigit(n);
    int nearestLesser = nearestLesserRomanDigit(n);
    int magnitude = magnitudeOf(n);
    if (ld_digit != 4 && ld_digit != 9) {
        if (leadingDigit(nearestLesser) == 1) {
            int nChars = n / magnitude;
            return std::string(nChars, iToS[magnitude]);
        } else {
            int firstChar = iToS[nearestLesser];
            int nExtra = (n - nearestLesser) / magnitude;
            std::string res(1, firstChar);
            res += std::string(nExtra, iToS[magnitude]);
            return res;
        }
    } else {
        int nearestGreater = n + magnitude;
        std::string res(1, iToS[magnitude]);
        res += std::string(1, iToS[nearestGreater]);
        return res;
    }
}

romanType::romanType(int n) {
    if (n <= 0) {
        throw std::domain_error("Roman numerals must be integers greater than 0");
    }

    intN = n;

    std::vector<int> digits;
    int magnitude = 1;
    int digit;

    while (n != 0) {
        digit = n % int(std::pow(10, magnitude));
        n -= digit;
        magnitude++;
        digits.push_back(digit);
    }

    std::string numeralStr;
    for (int i = digits.size() - 1; i >= 0; --i) {
        numeralStr += digitToRoman(digits[i]);
    }
    numeral = numeralStr;
}

romanType::romanType(std::string aNumeral) {
// read two characters
// if the first is greater than the second, inc total by first
// else read characters until out of characters OR a character is greater than the previous
// if ran out of characters, sum characters and increment
// else 
//     add last character but subtract the rest
// repeat
    numeral = aNumeral;
    intN = 0;

    std::string::size_type i = 0;
    while (i < aNumeral.size()) {
        char chr = aNumeral[i];

        if (i + 1 == aNumeral.size() || sToI[chr] > sToI[aNumeral[i+1]]) {
            intN += sToI[chr];
            i++;
        } else {
            typedef std::vector<char>::size_type vec_sz;
            std::vector<char> chrs;
            chrs.push_back(chr);

            while (++i < aNumeral.size() && sToI[chr] <= sToI[aNumeral[i]])
                chrs.push_back(aNumeral[i]);
            
            if (sToI[chrs[chrs.size()-1]] == sToI[chrs[chrs.size()-2]]) {
                for (vec_sz j = 0; j < chrs.size(); ++j) {
                    intN += sToI[chrs[j]];
                }
            } else {
                intN += sToI[chrs[chrs.size() - 1]];
                for (vec_sz j = 0; j < chrs.size() - 1; ++j) {
                    intN -= sToI[chrs[j]];
                }
            }
        }
    }
}