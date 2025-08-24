#include <bits/stdc++.h>

using namespace std;

string schoolAddition(string num1, string num2, int base) {
    string sum = "";

    int i = num1.length()-1;
    int j = num2.length()-1;

    int carry = 0;

    while (i >= 0 || j >= 0) {
        //cout << i << ' ' << j << endl;
        int curr = carry;
        if (i >= 0) {
            curr += int(num1[i] - 48);
            --i;
        }
        if (j >= 0) {
            curr += int(num2[j] - 48);
            --j;
        }

        sum = to_string(curr%base) + sum;

        carry = curr/base;

    }

    if (carry != 0) sum = to_string(carry) + sum;

    
    while (sum[0] == '0') {
        sum.erase(sum.begin());
    }

    if (sum.size() == 0) sum = "0";
    

    return sum;
}

string schoolSubtraction(string num1, string num2, int base) {
    string sub = "";

    int i = num1.length()-1;
    int j = num2.length()-1;

    int take = 0;

    while (i >= 0 || j >= 0) {
        //cout << i << ' ' << j << endl;
        int curr  = -take;
        if (i >= 0) {
            curr += int(num1[i] - 48);
            --i;
        }
        if (j >= 0) {
            curr -= int(num2[j] - 48);
            --j;
        }
        
        if (curr < 0) {
            curr += base;
            take = 1;
        } else {
            take = 0;
        }

        sub = to_string(curr%base) + sub;

    }

    while (sub[0] == '0') {
        sub.erase(sub.begin());
    }

    if (sub.size() == 0) sub = "0";
    
    return sub;
}

string karatsuba(string I1, string I2, int base) {

    string num1;
    string num2;

    if (I1.length() < I2.length()) {
        num1 = I1;
        num2 = I2;
    } else {
        num1 = I2;
        num2 = I1;
    }

    while (num1.size() < num2.size()) {
        num1 = "0" + num1;
    }

    if (num1.size() == 1) {
        int n = int(num1[0]-48);
        string sum = "";
        int carry = 0;
        for (char i : num2) {
            int curr = int(i-48)*n + carry;
            sum = to_string(curr%base) + sum;
            carry = curr/base;
        }

        if (carry != 0) sum = to_string(carry) + sum;

        while (sum[0] == '0') {
            sum.erase(sum.begin());
        }

        if (sum.size() == 0) sum = "0";

        return sum;
    }

    int k = num1.size() >> 1;

    string a0 = "";
    string b0 = "";
    string b1 = "";
    string a1 = "";

    for (int i = num1.size()-1; i >= num1.size()-k; --i) a0 = num1[i] + a0;
    for (int i = num2.size()-1; i >= num2.size()-k; --i) b0 = num2[i] + b0;

    for (int i = num1.size()-k-1; i >= 0; --i) a1 = num1[i] + a1;
    for (int i = num2.size()-k-1; i >= 0; --i) b1 = num2[i] + b1;


    //cout << a1 << ' ' << a0 << endl;
    //cout << b1 << ' ' << b0 << endl;

    
    string p2 = karatsuba(a1, b1, base);
    string p0 = karatsuba(a0, b0, base);
    string x = karatsuba(schoolAddition(b1, b0, base), schoolAddition(a1, a0, base), base);
    //cout << x << endl;
    string p1 = schoolSubtraction(x, schoolAddition(p0, p2, base), base);
    

    //cout << p1 << ' ' << schoolAddition(p0, p2, base) << endl;

    //cout << "p1: " << p1 << endl;

    for (int i = 0; i < 2*k; ++i) p2 += '0';
    for (int i = 0; i < k; ++i) p1 += '0';

    string prod = schoolAddition(schoolAddition(p2, p1, base), p0, base);
    //cout << p2 << ' ' << p1 << ' ' << p0 << endl << endl;

    //string prod = schoolAddition(p2, p1, base);

    return prod;
}


int main(void) {

    string I1;
    string I2;
    int B;

    cin >> I1 >> I2 >> B;


    //cout << schoolAddition(I1, I2, B) << ' ' << karatsuba(I1, I2, B) << " 0" <<  endl;

    cout << schoolAddition(I1, I2, B) << " " << karatsuba(I1, I2, B) << " 0" << endl;

    //cout << schoolSubtraction("100", "11", 2) << endl;
    

    return 0;
}