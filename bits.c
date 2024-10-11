/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return (~(~x & ~y) & ~(x & y));
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
   
    if (!x & !y) // 均为0
        return 1;
    if ((x ^ 0) && (y ^ 0))
        return !((x >> 31) ^ (y >> 31)); // 同符号返回1，不同返回0,(0,1)=0,(0,0)=1
    return 0;
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v)
{

     // 检查最高位是否在16位以上,如果是result+16，以此类推 ; 若最高位多于16位，v就右移16位，否则右移0位，以此类推
      int result = 0;

    int shift16 = (v > 0xFFFF) << 4;//值为0或16
    result |= shift16;
    v >>= shift16;


    int shift8 = (v > 0xFF) << 3;
    result |= shift8;
    v >>= shift8;

    int shift4 = (v > 0xF) << 2;
    result |= shift4;
    v >>= shift4;

  
    int shift2 = (v > 0x3) << 1;
    result |= shift2;
    v >>= shift2;

    result |= (v > 0x1);//这里result直接与真值或运算，可以减少步骤

    return result;


}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
 
   int origin_x = x;
    n <<= 3; // 将m,n乘8，方便与掩码&
    m <<= 3;
    int mask1 = 0xff;
    int temp = (((mask1 & (origin_x >> m)) << n) | ((mask1 & (origin_x >> n)) << m)); // 用mask来实现，n，m交换,注意先将origin_x的m号字节移到0号上，再与0xff按位与
    int mask2 = ~((0xff << n) | (0xff << m));
    x &= mask2; // 用mask2把x中n,m的字节清为0
    x |= temp;
    return x;
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned x)
{
    x = (x & 0x55555555) << 1 | (x & 0xAAAAAAAA) >> 1;   // 交换相邻的1位
    x = (x & 0x33333333) << 2 | (x & 0xCCCCCCCC) >> 2;   // 交换相邻的2位
    x = (x & 0x0F0F0F0F) << 4 | (x & 0xF0F0F0F0) >> 4;   // 交换相邻的4位
    x = (x & 0x00FF00FF) << 8 | (x & 0xFF00FF00) >> 8;   // 交换相邻的8位
    x = (x & 0x0000FFFF) << 16 | (x & 0xFFFF0000) >> 16; // 交换相邻的16位
    return x;
}
//基本思路是：初始化一个变量 result 为0，用于存储反转后的结果。
//通过循环32次，逐位x 的每一位移动到 result 的相应位置。
//每次循环中，将 x 右移一位，将 result 左移一位，并将 x 的最低位添加到 result 的最低位。
//当 x 变为0时，循环结束，result 即为反转后的结果。
//为了减少操作数，使用分治法，逐步将32位分成更小的部分，然后逐级反转。

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */

   int logicalShift(int x, int n)
{
    int result=0;
    int mask=0xffffffff>>n;//得到一个掩码，前n位是0，后32-n位是1
    result=(x>>n)&mask;
    result=(x>>n)&mask;
    return result;
}


/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {


    int count = 0;
    int mask = 1 << 31;
    int count16, count8, count4, count2, count1;
    count16 = (!(~(x & (mask >> 15)) >> 16)) << 4;
    count += count16;
    x <<= count16;
    count8 = (!(~(x & (mask >> 7)) >> 24)) << 3;
    count += count8;
    x <<= count8;
    count4 = (!(~(x & (mask >> 3)) >> 28)) << 2;
    count += count4;
    x <<= count4;
    count2 = (!(~(x & (mask >> 1)) >> 30)) << 1;
    count += count2;
    x <<= count2;
    count1 = (!(~(x & mask) >> 31));
    count += count1;
    x <<= count1;

   int  single_1 = x >> 31 & 1;
    count+=single_1;
    return count;

}
// 思路：运用并行的思想，先判断前16位是否全为1，若是，count+=16,然后x<<16;若否，则进入下一个判断，x<<count16
//                     再判断前8位是否全为1，若是，count+=8,然后x<<8;
//                     再判断前4位是否全为1，若是，count+=4,然后x<<4;
// 以此类推一直到判断前一位是否为1

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */unsigned float_i2f(int x)
{
    if (x == 0)
        return 0;          //  x = 0 的情况
    if (x == 0x80000000)   // x = TMin，-2147483648 
        return 0xCF000000; 
    unsigned int e = 0, E, M, temp_x, round;
    unsigned int result;
    
    unsigned s = x >> 31 & 1;

    if (x < 0)
    {
        x = -x;
    }
    temp_x = x;
    while ((temp_x >> 1) >= 1)
    {
        temp_x >>= 1;
        e++;
    }
    E = e + 127;
    x <<= (31 - e);//小数部分
    M = (x >> 8) & 0x7fffff;//使尾数对齐
    //一个 int 有 32 位，其中有 31 位可以用以表示精度，而 float 的尾数位有 23 位，所以我们需要将 int 的精度位右移 8 位（即损失 8 位精度），从而得到 float 的尾数位。
    round = x & 0xff;//要舍入的小数部分，取x的最低八位。根据 “四舍六入五成双” 的原则，对于最低位是否要舍入进行判断。
    if (round > 0x80)//10000000，即128，如果尾数部分的最低8位大于128，说明我们需要对尾数进行向上舍入
       M += 1;//阶码++
    else if (round == 0x80)
    {
        if (M & 1)
        {
            M += 1;
        }
    }//如果最低8位等于128，根据“四舍六入五成双”舍入规则，
     //如果当前尾数 M 的最低位为1，则我们加1。
     //如果最低位为0，则不做变化。
    if (M >> 23)
    {
        M &= 0x7fffff;
        E += 1;
    }//检查尾数 M 是否超出了23位。如果最高位为1（即 M >> 23 为真），这意味着尾数溢出，
//因此保留尾数的低23位，阶码 E 加1

    result = (s << 31) | M | (E << 23);

    return result;
}





/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
   unsigned e = (uf >> 23) & 0xFF;
    if (e == 0xFF)
    {
        return uf; // 如果是 NaN，直接返回
    }
    // 检查e是否为 0, 是则直接左移尾数位
    if (e == 0)
    {
        return (uf << 1) | (uf & 0x80000000); // 保持符号位不变
    }

    unsigned newE = e + 1;
    unsigned result = (uf & 0x807FFFFF) | (newE << 23);

    return result;
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2)
{

    int  E;
    unsigned S = (uf2 >> 31);
    unsigned M,value;
    int mask1 = 0x000007ff; // 用于得到E
    int mask2 = 0x000fffff; 
    E = ((uf2 >> 20) & mask1);
    int actual_E = E - 1023;
    M = ((uf2 & mask2) << 11) | (((uf1 >> 21) & mask1)) | (0x80000000); // uf2的低20位+uf1的高11位
    // 处理指数
    if (actual_E >= 31)
    {
        // 溢出
        return  0x80000000;
    }
    else if (actual_E < 0)
    {
        // 下溢
        return 0;
    }
    value = (M >> (31 - actual_E)) & ~(0x80000000 >> (31 - actual_E) << 1);
    if (S)
    {
        value = -value;
    }
    return value;
}

/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */

    unsigned floatPower2(int x) {
    // 计算新的指数值
    int newE = x + 127;

    // 检查结果是否超出范围
    if (newE >= 255) {
        return 0x7F800000; // 返回 +INF
    } else if (newE <= 0) {
        return 0x00000000; // 返回 0.0
    }

    // 构造新的浮点数表示
    unsigned result = (newE << 23);

    return result;
}
