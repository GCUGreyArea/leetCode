/*
 * @lc app=leetcode id=7 lang=c
 *
 * [7] Reverse Integer
 * Submition: https://leetcode.com/submissions/detail/549783691/
 */

// @lc code=start
static int digits(long int value, int base) {
	int ret = 1;
	if(value)
	{
		long i = base;
		long int v = value / i;
		while(v > 0)
		{
			i=i*base;
			ret++;
			v = value / i;
		}
	}

	return ret;
}

static int to_power_of(int num, int exp) {
	int ret = num;
	if(num) {
		for(int i=0;i<exp-1;i++) {
			ret *= num;
		}
	}

	return ret;
}

static long int reverse(long int value) {
	if(value >= 0 && value < 10) {
		return value;
	}

	bool neg=false;
	if(value < 0 ) {
		value = value * -1;
		neg = true;
	}

	int dg  = digits(value, 10)-1;

	int pow = to_power_of(10,dg);

	long long ret = 0;

	if(value) {
		long int divide = value;
		while(divide) {
			int new = divide % 10;
			ret += (long long) new * pow;
			pow = pow / 10;
			divide = divide / 10;
		}
	}

	if(ret >= 2147483647) {
		printf("Result to large for 32 bit int [%lld]\n", ret);
		return 0;
	}


	if(neg) {
		ret = ret * -1;
	}

	return (int) ret;
}

// @lc code=end

