#include "inf_int.h"
#include <string>
#include <algorithm>
inf_int::inf_int() {// assign 0 as a default value
    this->digits = "0";
    this->length = 1;
    this->thesign = true;
}

inf_int::inf_int(int num) {
    this->digits = to_string(abs(num));
    reverse((this->digits).begin(), (this->digits).end());
    this->length = digits.size();
    this->thesign = (num < 0 ? false : true);
}

inf_int::inf_int(const string str) {// you may modify this to "inf_int(const string);"
    if (str[0] == '-') this->digits = str.substr(1, str.size() - 1);
    else this->digits = str;
    reverse((this->digits).begin(), (this->digits).end());
    this->length = digits.size();
    this->thesign = (str[0] == '-' ? false : true);
}

inf_int::inf_int(const inf_int& target) {// copy constructor
    this->digits = target.digits;
    this->length = target.length;
    this->thesign = target.thesign;
}

inf_int::~inf_int(){ // destructor

}

inf_int& inf_int::operator=(const inf_int& target) { // assignment operator
    this->digits = target.digits;
    this->length = target.length;
    this->thesign = target.thesign;
    return *this;
}


bool operator==(const inf_int& a, const inf_int& b)
{
    if ((a.digits).compare(b.digits) == 0 and a.thesign == b.thesign) return true;
    return false;
}

bool operator!=(const inf_int& a, const inf_int& b) {
    if ((a.digits).compare(b.digits)==0 and a.thesign == b.thesign) return false;
    return true;
}

bool operator>(const inf_int& a, const inf_int& b) {
    if (a.thesign != b.thesign)
        return (a.thesign == true ? true : false);

    if (a.length > b.length)
        return (a.thesign == true ? true : false);
    else if (a.length < b.length)
        return (a.thesign == true ? false : true);

    for (int i = a.length - 1; i >= 0; i--) {
        if ((a.digits)[i] != (b.digits)[i])
            return ((a.digits)[i] > (b.digits)[i] ? true : false);
    }
    return false;
}

bool operator<(const inf_int& a, const inf_int& b) {
    if (a.thesign != b.thesign)
        return (a.thesign == true ? false : true);

    if (a.length > b.length)
        return (a.thesign == true ? false : true);
    else
        return (a.thesign == true ? true : false);

    for (int i = a.length - 1; i >= 0; i--) {
        if ((a.digits)[i] != (b.digits)[i])
            return ((a.digits)[i] < (b.digits)[i] ? true : false);
    }
    return false;
}

inf_int operator+(const inf_int& a, const inf_int& b) {
    inf_int ret("");
    if (a.thesign == b.thesign) {
        int carry = 0, sum;
        unsigned int iter = (a.length >b.length ? a.length : b.length);
        for (int i = 0; i < iter; i++) {
            sum = 0;
            if (a.length > i)sum += (a.digits)[i] - '0';
            if (b.length > i)sum += (b.digits)[i] - '0';
            sum += carry;
            carry = sum / 10;
            sum %= 10;
            ret.digits.push_back(sum + '0');
        }
        if (carry == 1)ret.digits.push_back('1');
        ret.length = ret.digits.size();
        ret.thesign = a.thesign;
    }
    else {
        if (a.thesign == true) {//(+) + (-)
            inf_int temp = b;
            temp.thesign = true;
            ret = a - temp;
        }
        else {//(-) + (+)
            inf_int temp = a;
            temp.thesign = true;
            ret = b - temp;
        }
    }
    return ret;
}

inf_int operator-(const inf_int& a, const inf_int& b) {
    inf_int ret(""), temp("");
    if (a.thesign == b.thesign) {
        bool transfer_sign_flag = false, swap_flag = false;
        inf_int minuend=a, subtraend=b;//(minuend-subtraend)
        if (minuend.thesign == false) {
            minuend.thesign = true, subtraend.thesign = true;
            transfer_sign_flag = true;
        }
        if (minuend < subtraend) {//SWAP
            temp = minuend;
            minuend = subtraend;
            subtraend = temp;
            swap_flag = true;
        }

        //operate
        int carry = 0, res;
        for (int i = 0; i < minuend.length; i++) {
            res = minuend.digits[i] -carry-'0';
            if (i < subtraend.length)res -= (subtraend.digits[i]-'0');
            if (res < 0) {
                res += 10;
                carry = 1;
            }
            else carry = 0;
            ret.digits.push_back(res + '0');
        }

        //set sign,length
        ret.thesign = true;
        if (transfer_sign_flag == true)ret.thesign = !(ret.thesign);
        if (swap_flag == true)ret.thesign = !(ret.thesign);
        ret.length = ret.digits.size();

        while (ret.length > 1 and ret.digits[ret.length-1]=='0') {//delete meaningless '0'
            ret.digits.pop_back();
            ret.length--;
        }
        if (ret.length == 1 and ret.digits[0] == '0') {//digits = 0
            ret.thesign = true;
        }
    }
    else {//case of "(-) - (+)" || "(+) - (-)"
        inf_int temp = b;
        if (a.thesign == true) {//(+) - (-)
            temp.thesign = true;
            ret = a + temp;
        }
        else {//(-) - (+)
            temp.thesign = false;
            ret = a + temp;
        }
    }
    return ret;
}

inf_int operator*(const inf_int& a, const inf_int& b) {
    inf_int ret(""), temp;
    for (unsigned int i = 0; i < b.length; i++) {
        temp.digits = "", temp.thesign = true, temp.length = 0;
        for (int j = 0; j < (b.digits)[i] - '0'; j++) {
            temp = temp + a;
        }
        for (int j = 0; j < i; j++) {
            temp.digits.insert(0, "0");
            temp.length++;
        }
        ret = ret + temp;
        ret.length = ret.digits.size();
    }
    ret.thesign = true;
    if (a.thesign == false)ret.thesign = !(ret.thesign);
    if (b.thesign == false)ret.thesign = !(ret.thesign);
    return ret;
}

ostream& operator<<(ostream& out, const inf_int& target) {
    if (target.thesign == false)cout << "-";
    for(int i=target.length-1;i>=0;i--)
        out << target.digits[i];
    out << '\n';
    return out;
}