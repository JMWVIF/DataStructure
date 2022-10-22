#include <iostream>
using namespace std;
const int maxSize = 20;

int getPriority(char i)
//得到符号的优先级
{
    switch (i)
    {
    case '+':
    case '-':
        return 1;       //+-的优先级是+1
    case '*':
    case '/':
        return 2;       //*/的优先级是+2
    }
}
int infixToPostfix(char infix[],char s2[])
{
    char s1[maxSize];
    //符号堆栈
    int top1 = -1, top2 = -1;
    //top1是符号堆栈的标号, top2是结果数组的标号
    int stackMax = 0;
    //记录堆栈最大处的标号
    int i = 0;
    //指向原数组的标号
    while (infix[i] != '\0')        //循环到末尾
        //控制循环的原数组循环的末尾
    {
        if (('a' <= infix[i] && infix[i] <= 'z') ||
            (('0' <= infix[i] && infix[i] <= '9')))
            //如果选到数字或者字母, 直接写入结果数组（因为字母与数字的优先级是+0）
        {
            s2[++top2] = infix[i];      //入栈
            i++;
        }
        else if (infix[i] == '(')           //(的优先级是最高
            //如果遇到左括号, 直接写入符号堆栈
        {
            s1[++top1] = '(';               //直接入栈
            if (top1 > stackMax)
                stackMax = top1;            //堆栈最大值再往上加
            i++;
        }
        else if (infix[i] == '+' ||
                 infix[i] == '-' ||
                 infix[i] == '*' ||
                 infix[i] == '/')
            //如果遇到运算符则分类讨论
        {
            if (top1 == -1 ||               //栈底
                s1[top1] == '(' ||          //括号内的底端
                getPriority(infix[i]) >     //比较优先级更高
                getPriority(s1[top1]))
                //若在栈底, 在括号底, 或者操作符优先级高, 则操作符入栈
            {
                s1[++top1] = infix[i];      //优先级更高就伸出魔爪
                if (top1 > stackMax)
                    stackMax = top1;        //堆栈最大值再往上加（其实就是优先级>=2的符号数量）
                i++;
            }
            else //否则出栈
                s2[++top2] = s1[top1--];    //出栈
        }
        else if (infix[i] == ')')
            //如果遇到右括号, 则将其与对应左括号之间的符号出栈（因为括号是相互对应的，而且括号的优先级是最高的）
        {
            while (s1[top1] != '(')
                s2[++top2] = s1[top1--];
            top1--;
            i++;
        }
    }
    while (top1 != -1)                  //这就是清算剩余的，就直接开始出栈
        //这里将堆栈中剩余的符号推出堆栈
        s2[++top2] = s1[top1--];
    return stackMax + 1;                //返回结果值（其实就是优先级>=2的符号数量）
    //这里top1是堆栈标号, 必须+1才是数目
}
int main()
{
    int top2 = -1;
    char s2[maxSize];
    char infix[maxSize] = "a+b-a*((c+d)/e-f)+g";
    cout << infixToPostfix(infix, s2) << endl;
    int i = 0;
    while (s2[i] != '\0')                 //这样循环，输出后缀表达式的所有字符
        cout << s2[i++];                  //一个s2[i]内含一个字符
    cout << endl;
    return 0;
}
/*结果
5
ab+acd+e/f-*-g+
*/
