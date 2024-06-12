#include <iostream>

int gcd(int a, int b) {
    if (a == 0)
        return b;
    return gcd(b % a, a);
}

int phi(unsigned int n) {
    unsigned int result = 1;
    for (unsigned int i = 2; i < n; i++)
        if (gcd(i, n) == 1)
            result++;
    return result;
}


// we will try to factorize b as 2^t * z, where (2^t, z) = 1
typedef struct prime_t {
    int t;
    int z;
}prime;

prime_t factorize_b (int b) {
    prime_t factorization = {0, 0};
    while(b % 2 == 0) {
        b = b/2;
        factorization.t++;
    }
    factorization.z = b;

    return factorization;
}

typedef struct bezout_coefficients {
    int x, y;
}bez_coeff;

// compute the coefficients: "x", "y" of the extended euclidean algorithm: https://en.wikipedia.org/wiki/Extended_Euclidean_algorithm
int extended_euclidean_algorithm (int a, int b, int &x, int &y) {
    //the algorithm ends with b = 0 and a = gcd. For these parameters we can easily find coefficients: namely a*1 + b*0 = gcd.
    if(b == 0) {
        x = 1;
        y = 0;
        return b;
    }
    
    int x1, y1;

    // suppose we figured out the x1, y1 for (b, a%b), for example: (x1, y1) = (1, 0) for (a, b) = (gcd, 0) (the last step in the extended euclidean algorithm)
    int gcd = extended_euclidean_algorithm(b, a % b, x1, y1);

    // we know that x1*b + y1*(a%b) = x*a + y*b = gcd. (note a%b = a - [a/b]*b) =>
    // => x1 * b + y1*a - y1*[a/b]*b = x*a + y*b => b*(x1 - y1*[a/b]) + a*y1 = b*y + x*a => 
    // => x = y1 and y = x1 - y1*[a/b]
    x = y1;
    y = x1 - (a / b) * y1;
    return gcd; 
}

int logarithmic_exponentiation_mod_b(int base, int power, int b) {
    int res = 1;
    if(base == 0) return 0;
    while (power > 0) {
        if (power % 2 == 1) res = (res * base) % b;
        power = power >> 1;
        base = ((base * base)) % b;
    }
    return res;
}

int main () {
    // we want to compute 2^(2^a) % b
    int a = 0, b = 0;
    std::cin >> a >> b;

    // if x ≡ y (mod phy(b)) => 2^x ≡ 2^y (mod b), given that gcd(2, b) = 1
    // we cannot guarantee for gcd(2, b) = 1, so we will exponentiate b = 2^t * z, where gcd(2^t, z) = 1
    // then using the chinese remainder theorem: 
    // if x ≡ a1 (mod n1) and x ≡ a2 (mod n2), then x ≡ a1*m2*n2 + a2*m1*n1 (mod n1*n2)
    // where m1 and m2 are the bezout coefficients that should verify: m1*n1 + m2*n2 = gcd(n1, n2) = 1
    // here we will choose: n1 = z and n2 = 2^t.
    // let's denote: A := 2^(2^a).
    // then A ≡ A1 (mod z) and A ≡ A2 (mod 2^t) => A ≡ A1*m2*2^t + A2*m1*z (mod b)
    // to compute A1 we will use the fact that if y ≡ 2^a (mod phy(z)) => 2^y ≡ A1 (mod z)
    // for A2 is even easier: if(t < 2^a) A2 ≡ 2^2^a, else A2 ≡ 0

    prime_t factorization = factorize_b(b);
    int z = factorization.z, t = factorization.t;

    std::cout << z << " " << t << std::endl;

    int powered_a = logarithmic_exponentiation_mod_b(2, a, b);
    int T = logarithmic_exponentiation_mod_b(2, t, b);
    
    std::cout << powered_a << " " << T << std::endl;
    
    int A2;
    if(t < powered_a) A2 = logarithmic_exponentiation_mod_b(2, powered_a, T);
    else A2 = 0;

    std::cout << A2 << " " << std::endl;

    int m1, m2;
    extended_euclidean_algorithm(z, T, m1, m2);

    std::cout << m1 << " " << m2 << std::endl;

    int phi_z = phi(z);
    std::cout << z << " " << phi_z << std::endl;
    int y = logarithmic_exponentiation_mod_b(2, a, phi_z);
    int A1 = logarithmic_exponentiation_mod_b(2, y, z);

    std::cout << y << " " << A1 << std::endl;

    int A = (((A1*m2)%b)*T)%b + (((A2*m1)%b)*z)%b;

    std::cout << A;
}