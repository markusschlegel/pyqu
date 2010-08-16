from sys import argv
from math import *
from random import random
from pyqu import *

def gcd(a,b):
    '''returns the greatest common divisor of a and b'''
    while b:
        r = a % b;
        a = b;
        b = r;
    return a;
    
def lcm(a,b):
    '''returns the lowest common multiple of a and b'''
    return a*b/gcd(a,b)
    
def fastExp(b,e,m):
    '''returns c = b^e mod m'''
    c = 1
    for i in range(e):
        c = (b*c) % m
    return c

def continuedFractions(x, n):
    '''returns a pair of candidates period r given the measured value x and
    number of qubits n using the continued fractions algorithm'''
    
    divR = []
    den = 1 << n
    estimator = x / den
    limit = 1 / (1 << n)
    
    xn = [x // den]
    p = [xn[0]]
    q = [1]
    tmp = den
    den = x % den
    num = tmp
    xn.append(num // den)
    p.append(xn[1]*xn[0] + 1)
    q.append(xn[1])
    i = 2
    while len(divR) < 1 and den > 0:
        if abs(p[i-1]/q[i-1] - estimator) <= limit:
            divR.append(q[i-1])
        tmp = den
        den = num % den
        num = tmp
        if den > 0:
            xn.append(num // den)
            p.append(xn[i]*p[i-1] + p[i-2])
            q.append(xn[i]*q[i-1] + q[i-2])
        i += 1
    if len(divR) < 1:
        return None
    else:
        #divR.append(lcm(divR[0], divR[1]))
        return divR
    
    #x = [num // den]
    #p = [x[0]]
    #q = [1]
    #tmp = den
    #den = num % den
    #num = tmp
    #x.append(num // den)
    #p.append(x[1]*x[0] + 1)
    #q.append(x[1])
    #i = 2
    #while gcd(p[i-1],q[i-1]) != 1:
        #print("num: "+str(num)+", den: "+str(den))
        #tmp = den
        #den = num % den
        #num = tmp
        #print("num: "+str(num)+", den: "+str(den))
        #x.append(num // den)
        #p.append(x[i]*p[i-1] + p[i-2])
        #q.append(x[i]*q[i-1] + q[i-2])
        #i += 1
    #return p[i-1], q[i-1]

def quantumShor(inw, outw, x, N):
    '''quantum part of the Shor's algorithm'''
    #setting up the registers:
    qr = Qureg(inw + outw)
    inReg = qr[outw:]
    outReg = qr[:outw]

    #creating an equiprobable superposition of all possible states on the input register
    H(inReg)
    #applying the operator U|j>|0> = |j>|x^j mod N>
    UexpModN(inReg, outReg, x, N)
    #measuring the output register to get some x^j0 mod N, note that this will leave the
    #input register in a sort of periodic state |ar + j0>
    measure(outReg)
    #applying a Quantum Fourier Transform that will leave the input in a new state where
    #the probabilities accumulate around the states |k*2^t/r> where t is the number of
    #qubits of the input register. Note that the random value j0 disappeared
    QFT(inReg)
    #the QFT operator reverses the weight of the qubits, so we have to reverse them again
    inReg.reverse()
    #returning some value close to k*2^t/r for some random k. t is known and k,r unknown
    ret = measure(inReg)
    #deleting quantum registers
    del outReg, inReg, qr
    return ret

N = int(argv[1])
factors = []
runs = 0

#while N % 2 == 0:
    #N //= 2
    #factors.append(2)

x = r = 1
found = False
while not found:
    x = 0
    while gcd(N,x) > 1 or x < 2:
        x = int(random()*N)
        
    print("Randomly chose x = "+str(x))

    inw = ceil(log(N*N,2)) #input width
    outw = ceil(log(N,2))  #output width

    runs += 1
    k = quantumShor(inw, outw, x, N)
    while k == 0:
        print("Measured zero, trying again...")
        runs += 1
        k = quantumShor(inw, outw, x, N)

    print("Measured k = "+str(k)+", Q: "+str(1 << inw))
    r = continuedFractions(k, inw)
    #r = continuedFractions(k, (1 << inw))
    #print("Candidate period r: "+str(r))

    #num = k
    #den = (1 << inw)

    #a = [num // den]
    #p = [a[0]]
    #q = [1]
    #tmp = den
    #den = num % den
    #num = tmp
    #a.append(num // den)
    #p.append(a[1]*a[0] + 1)
    #q.append(a[1])
    #i = 2
    #while a[i-1] != 0 and fastExp(x, q[i-1], N) != 1 and den != 0:
        #tmp = den
        #den = num % den
        #num = tmp
        #if den:
            #a.append(num // den)
            #p.append(a[i]*p[i-1] + p[i-2])
            #q.append(a[i]*q[i-1] + q[i-2])
            #i += 1
    #print(a)
    #print(p)
    #print(q)
    #print("Period = "+str(q[i-1]))

    #factor1 = gcd(N, pow(x, q[i-1]/2)-1)
    #factor2 = gcd(N, pow(x, q[i-1]/2)+1)
    #found = True

    if r == None:
        print("Couldn't find the period, trying again...")
    else:
        for rr in r:
            print("Candidate r = "+str(rr))
            if int(rr) & 1 == 0 and not found:#and  pow(x,int(rr)) < N
                exp = fastExp(x, int(rr), N)
                if exp == 1 and not found:
                    factor1 = gcd(N, pow(x, rr/2)-1)
                    factor2 = gcd(N, pow(x, rr/2)+1)
                    if factor1*factor2 == N and factor1 != 1 and factor2 != 1:
                        factors.append(factor1)
                        factors.append(factor2)
                        found = True
        if not found:
            print("Couldn't find the period, trying again...")



    #elif r % 2 == 1:
        #print("Odd period, trying again...")
    #elif fastExp(x,int(r),N) != 1:
        #print("Couldn't find the period, trying again...")
    #else:
        #factors.append(gcd(N, pow(x, r/2)-1))
        #factors.append(gcd(N, pow(x, r/2)+1))
        #break
    #if pow(x,r) % N != 1:
        #print("Couldn't find the period, trying again...")
    #elif r % 2 == 1:
        #print("Odd period, trying again...")
    #else:
        #factor1 = gcd(N, pow(x, r/2)-1)
        #factor2 = gcd(N, pow(x, r/2)+1)
        #if factor1 == 1 or factor2 == 1:
            #print("Couldn't find the period, trying again...")
        #else:
            #factors.append(factor1)
            #factors.append(factor2)
            #break
            
print("Period r = "+str(r))

print("Factors of " + argv[1] + ": " + str(factors))
print("Iterations: " + str(runs))