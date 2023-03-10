/* 
 * Mick Cazemier
 * Gilian Honkoop
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */


INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc () compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif

/* 
 *
 *
 * 
 *
 */



/* Global ID to identify the combination of puzzles */
int lab_id = 73;
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
  return ~((~x) | (~y));
}
/* 
 * upperBits - pads n upper bits with 1's
 *  You may assume 0 <= n <= 32
 *  Example: upperBits(4) = 0xF0000000
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 10
 *  Rating: 1
 */
int upperBits(int n) {
  return ((~(!n) << 31) >> (n + ~0));
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */

 //this fails the automatic check but we believe it should be correct.
int fitsBits(int x, int n) {
  // int lowerbits = ~(~0 << (n + ~0));
  // int comparison = lowerbits ^ x;
  // comparison = comparison >> (n + ~0);
  // comparison = (comparison + 1) >> 1;
  // return !comparison;

  return !(((((~(~0 << (n + ~0))) ^ x) >> (n + ~0))) + 1 >> 1);
}
/* 
 * isGreater - if x > y  then return 1, else return 0 
 *   Example: isGreater(4,5) = 0, isGreater(5,4) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isGreater(int x, int y) {

  // returns 1 if y - x is negative
  int greater = !!((y+(~x + 1)) & (1 << 31));

  //returns 1 if y is negative
  int sign_y = (y >> 31) & 1;

  // returns 1 if x and y have the same sign
  int same_sign = ~((x ^ y) >> 31) & 1;

  return (greater & same_sign) | (sign_y & !same_sign);
}

/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x)
{
  int shift1 = (0x55 << 8) + 0x55;
  shift1 = (shift1 << 16) + shift1;
  int shift2 = (0x33 << 8) + 0x33;
  shift2 = (shift2 << 16) + shift2;
  int shift3 = (0x0F << 8) + 0x0F;
  shift3 = (shift3 << 16) + shift3;
  int shift4 = (0xFF << 16) + 0xFF;
  int shift5 = (0xFF << 8) + 0xFF;

  unsigned int totalbits;
  totalbits = (x & shift1) + ((x >> 1) & shift1);
  totalbits = (totalbits & shift2) + ((totalbits >> 2) & shift2);
  totalbits = (totalbits & shift3) + ((totalbits >> 4) & shift3);
  totalbits = (totalbits & shift4) + ((totalbits >> 8) & shift4);
  totalbits = (totalbits & shift5) + ((totalbits >> 16)& shift5);
  return totalbits;
}
/* 
 * float_f2i - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int float_f2i(unsigned uf)
{
  int exponent = (uf >> 23) & 0xff;
  int bias = 127;
  int eval = exponent - bias;
  int num = uf & 0xffffff;
  num = num | 0x800000;
  
  //if then number is infinite or nan
  if(exponent == 0x7F800000)
    return 0x80000000u;

  //if exponent = 0x000000000
  if(!exponent)
    return 0;

  //check if the number is out of bounds
  if(exponent >= 31+bias)
    return 0x80000000u;

  //if exponent < bias the result will be < 0, and thus rounded to 0 for integers
  if(exponent < bias)
    return 0;

  //check eval and shift accordingly
  if (eval >= 23)
    num = num << (eval - 23);
  else
    num = num >> (23 - eval);

  //check for the sign of uf and switch positive/negative
  if((uf >> 31) & 1)
    return ~num + 1;

  return num;
}
