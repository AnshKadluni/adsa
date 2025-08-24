#include <bits/stdc++.h>

using namespace std;

string schoolAddition(string num1, string num2, int base) {
    string sum = "";

    int i = num1.length()-1;
    int j = num2.length()-1;

    int carry = 0;

    while (i >= 0 || j >= 0) {
        
        int curr = carry;
        if (i >= 0) {
            curr += int(num1[i] - 48); // in-built subtraction for converting char to int
            --i;
        }
        if (j >= 0) {
            curr += int(num2[j] - 48); // in-built subtraction for converting char to int
            --j;
        }

        sum = to_string(curr%base) + sum;

        carry = curr/base;

    }

    if (carry != 0) sum = to_string(carry) + sum;

    // removing zeros in front
    while (sum[0] == '0') sum.erase(sum.begin());

    // if string is empty it must be 0
    if (sum.empty()) sum = "0";
    
    return sum;
}

// subtraction works if num1 >= num2 as karatsuba guarantees it
string schoolSubtraction(string num1, string num2, int base) {
    string sub = "";

    int i = num1.length()-1;
    int j = num2.length()-1;

    int take = 0;

    while (i >= 0 || j >= 0) {
        
        int curr  = -take;
        if (i >= 0) {
            curr += int(num1[i] - 48); // in-built subtraction for converting char to int
            --i;
        }
        if (j >= 0) {
            curr -= int(num2[j] - 48); // in-built subtraction for converting char to int
            --j;
        }

        take = 0;

        if (curr < 0) {
            curr += base;
            take = 1;
        }

        sub = to_string(curr%base) + sub;

    }

    while (sub[0] == '0') sub.erase(sub.begin()); // removing 0s in front

    if (sub.size() == 0) sub = "0"; // setting empty string to 0
    
    return sub;
}

// for splitting the numbers
vector<string> splitNumber(string num, int k) {
    vector<string> res(2, "");

    int n = num.size();

    for (int i = 0; i < n-k; ++i) res[1] += num[i];
    for (int i = n-k; i < n; ++i) res[0] += num[i];

    return res;
}

string karatsuba(string I1, string I2, int base) {

    string num1;
    string num2;

    // reassigning to keep track of the shorter number
    if (I1.length() < I2.length()) {
        num1 = I1;
        num2 = I2;
    } else {
        num1 = I2;
        num2 = I1;
    }

    // padding the shorter numbers with zeros to make spliting easier
    while (num1.size() < num2.size()) num1 = "0" + num1;

    // single digit multiplication
    if (num1.size() == 1) {
        int prod = int(num1[0]-48)*int(num2[0]-48); // in-built subtraction for converting to from char to int
        return to_string(prod/base) + to_string(prod%base);
    }

    int k = num1.size() >> 1; // index for split the numbers

    // spliting the numbers

    vector<string> a = splitNumber(num1, k);
    vector<string> b = splitNumber(num2, k);

    // doing intermediate calcualtion 

    string p2 = karatsuba(a[1], b[1], base);
    string p0 = karatsuba(a[0], b[0], base);
    string p1 = schoolSubtraction(karatsuba(schoolAddition(b[1], b[0], base), schoolAddition(a[1], a[0], base), base), schoolAddition(p0, p2, base), base);

    // multiplying by B^k and B^2k
    for (int i = 0; i < 2*k; ++i) p2 += '0';
    for (int i = 0; i < k; ++i) p1 += '0';

    string prod = schoolAddition(schoolAddition(p2, p1, base), p0, base);

    return prod;
}


int main(void) {

    string I1;
    string I2;
    int B;

    cin >> I1 >> I2 >> B;

    cout << schoolAddition(I1, I2, B) << " " << karatsuba(I1, I2, B) << " 0" << endl;

    return 0;
}