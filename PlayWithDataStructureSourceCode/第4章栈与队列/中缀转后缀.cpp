#include <iostream>
using namespace std;
const int maxSize = 20;

int getPriority(char i)
//�õ����ŵ����ȼ�
{
    switch (i)
    {
    case '+':
    case '-':
        return 1;       //+-�����ȼ���+1
    case '*':
    case '/':
        return 2;       //*/�����ȼ���+2
    }
}
int infixToPostfix(char infix[],char s2[])
{
    char s1[maxSize];
    //���Ŷ�ջ
    int top1 = -1, top2 = -1;
    //top1�Ƿ��Ŷ�ջ�ı��, top2�ǽ������ı��
    int stackMax = 0;
    //��¼��ջ��󴦵ı��
    int i = 0;
    //ָ��ԭ����ı��
    while (infix[i] != '\0')        //ѭ����ĩβ
        //����ѭ����ԭ����ѭ����ĩβ
    {
        if (('a' <= infix[i] && infix[i] <= 'z') ||
            (('0' <= infix[i] && infix[i] <= '9')))
            //���ѡ�����ֻ�����ĸ, ֱ��д�������飨��Ϊ��ĸ�����ֵ����ȼ���+0��
        {
            s2[++top2] = infix[i];      //��ջ
            i++;
        }
        else if (infix[i] == '(')           //(�����ȼ������
            //�������������, ֱ��д����Ŷ�ջ
        {
            s1[++top1] = '(';               //ֱ����ջ
            if (top1 > stackMax)
                stackMax = top1;            //��ջ���ֵ�����ϼ�
            i++;
        }
        else if (infix[i] == '+' ||
                 infix[i] == '-' ||
                 infix[i] == '*' ||
                 infix[i] == '/')
            //���������������������
        {
            if (top1 == -1 ||               //ջ��
                s1[top1] == '(' ||          //�����ڵĵ׶�
                getPriority(infix[i]) >     //�Ƚ����ȼ�����
                getPriority(s1[top1]))
                //����ջ��, �����ŵ�, ���߲��������ȼ���, ���������ջ
            {
                s1[++top1] = infix[i];      //���ȼ����߾����ħצ
                if (top1 > stackMax)
                    stackMax = top1;        //��ջ���ֵ�����ϼӣ���ʵ�������ȼ�>=2�ķ���������
                i++;
            }
            else //�����ջ
                s2[++top2] = s1[top1--];    //��ջ
        }
        else if (infix[i] == ')')
            //�������������, �������Ӧ������֮��ķ��ų�ջ����Ϊ�������໥��Ӧ�ģ��������ŵ����ȼ�����ߵģ�
        {
            while (s1[top1] != '(')
                s2[++top2] = s1[top1--];
            top1--;
            i++;
        }
    }
    while (top1 != -1)                  //���������ʣ��ģ���ֱ�ӿ�ʼ��ջ
        //���ｫ��ջ��ʣ��ķ����Ƴ���ջ
        s2[++top2] = s1[top1--];
    return stackMax + 1;                //���ؽ��ֵ����ʵ�������ȼ�>=2�ķ���������
    //����top1�Ƕ�ջ���, ����+1������Ŀ
}
int main()
{
    int top2 = -1;
    char s2[maxSize];
    char infix[maxSize] = "a+b-a*((c+d)/e-f)+g";
    cout << infixToPostfix(infix, s2) << endl;
    int i = 0;
    while (s2[i] != '\0')                 //����ѭ���������׺���ʽ�������ַ�
        cout << s2[i++];                  //һ��s2[i]�ں�һ���ַ�
    cout << endl;
    return 0;
}
/*���
5
ab+acd+e/f-*-g+
*/
