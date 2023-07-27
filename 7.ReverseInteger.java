/*
 * @lc app=leetcode id=7 lang=java
 *
 * [7] Reverse Integer
 * Submition: https://leetcode.com/submissions/detail/549790990/
 */
class Solution {
    int digits(long value, int base) {
        int ret = 1;
        if(value > 0)
        {
            long i = (long) base;
            long  v = value / i;
            while(v > 0)
            {
                i=i*base;
                ret++;
                v = value / i;
            }
        }

        return ret;
    }

    int to_power_of(int num, int exp) {
        int ret = num;
        if(num > 0) {
            for(int i=0;i<exp-1;i++) {
                ret *= num;
            }
        }

        return ret;
    }

    public int reverse(int val) {
        long value = (long) val;

        Boolean neg=false;
        if(value < 0 ) {
            value = value * -1;
            neg = true;
        }

        if(value >= 0 && value < 10) {
            if(neg) {
                return (int) (value * -1);
            }
            return (int) value;
        }

        int dg  = digits(value, 10)-1;

        int pow = to_power_of(10,dg);

        double ret = 0;
        if(value > 0) {
            long divide = value;
            while(divide > 0) {
                double newInt = (double) divide % 10;
                ret += (double) newInt * pow;
                pow = pow / 10;
                divide = divide / 10;
            }
        }

        if((int) ret >= 2147483647) {
            return 0;
        }


        if(neg) {
            ret = ret * -1;
        }

        return (int) ret;
    }
}
