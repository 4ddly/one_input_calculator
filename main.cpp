#include <iostream>
#include <string>
using namespace std;

string allowed_chars ="+-*./()0123456789";

string delSpaces(string text)
{
    int len_ = text.length();
    string result;
    for(int i=0; i<len_; i++)
    {
        if(text[i]!=' ')
        {
            result = result + text[i];
        }
    }
    return result;
}
bool check_digit(char char_)// between ")(" can be addable
{
    int len_= allowed_chars.length();
    for(int i=0; i<len_; i++)
    {
        if(char_ == allowed_chars[i])
        {
            return true;
        }
    }
    return false;
}

//checks invalid chars
bool check(string text)
{
    int len_=text.length();
    for(int i=0; i<len_; i++)
    {
        if(check_digit(text[i])==false)
        {
            cout <<"Invalid Input: "<<text[i]<<endl;
            return false;
        }
    }
    return true;
}

string replace_(int start_, int end_, string replaceWith, string full_text)
{
    string result;
    int len_ = full_text.length();
    for(int i=0; i<len_; i++)
    {
        if ((i >= start_) && (i < end_) )
        {
            if(i-start_ >= replaceWith.length()) {continue;}
            result = result + replaceWith[i-start_];
        }
        else
        {
            result = result + full_text[i];
        }
    }
    return result;
}
double calculate_basic(double num1, char operand, double num2)
{
    if(operand == '+')
    {
        return num1 + num2;
    }
    else if(operand == '-')
    {
        return num1 - num2;
    }
    else if(operand == '*')
    {
        return num1 * num2;
    }
    else if(operand == '/')
        return num1 / num2;
    else
    {
        cout << "Error: Invalid Operand" <<endl;
        return 0;
    }
}


string calculate_two(int start_, int end_, string text)//finds & calculates 2 number operations
{
    string result;
    string num1="";
    string num2="";
    int posOperand;//position of operand
    for(int i=start_; i<end_; i++)
    {
        if(text[i] == '+' || text[i] == '-' || text[i] == '*' || text[i] == '/')
        {
            for(int y=start_; y<i; y++)
            {
                num1 = num1 + text[y];
            }
            for(int u=i+1; u<end_; u++)
            {
                num2 = num2 + text[u];
            }
            posOperand = i;
            break;
        }
    }
    result = to_string(  calculate_basic(stod(num1), text[posOperand], stod(num2)  ));
    return result;
}


string find_otherOp(int start_, int end_, string text)//finds other operations than * and / operations, solves them, returns full text
{
    char flag = '0';//for prev/next operand finding
    string newText;
    int prevOpn;//operand position
    int nextOpn;
    char restart_func = '1';
    while(restart_func == '1')
    {
        for(int i=start_; i<end_; i++)
        {
            if(text[i] == '+' || text[i] == '-') //ONLY CHANGED PART COMPARED TO OTHER FIND FUNC !!!!!!
            {
                //find previous and next operands after this, send locations to calculate_two
                for(int p=i-1; start_-1<p; p--)
                {
                    if(text[p] == '+' || text[p] == '-' || text[p] == '*' || text[p] == '/' || text[p] == '(' || text[p] == ')')
                    {
                        prevOpn = p;
                        flag = '1';//means it worked
                        break;
                    }
                }
                if(flag =='0')//means prevOpn could not be found
                {
                    prevOpn = start_-1;//because we will add+1 when calling calculate_two func
                }
                //------------------------------------------------------------------------------------
                flag = '0';
                for(int n=i+1; n<end_; n++)
                {
                    if(text[n] == '+' || text[n] == '-' || text[n] == '*' || text[n] == '/' || text[n] == '(' || text[n] == ')')
                    {
                        nextOpn = n;
                        flag = '1';
                        break;
                    }
                }
                if(flag == '0')
                {
                    nextOpn = end_;//or end_+1 ???
                }
                //------------------------------------------------------------------------------------
                newText = replace_(prevOpn+1, nextOpn, calculate_two(prevOpn+1, nextOpn, text), text);//this will also change start,end point
                end_ = end_ - text.length() + newText.length();//also works if end_ point goes farther
                text = newText;
                restart_func = '1';
                break;
            }
            restart_func = '0';
        }
    }
    cout <<"return of otherOp():                   "<< text <<endl;
    return text;
}

string find_xdivide(int start_, int end_, string text)//finds * and / operations, solves them, returns full text
{
    char flag = '0';//for prev/next operand finding
    string newText;
    int prevOpn;//operand
    int nextOpn;
    char restart_func = '1';
    while(restart_func == '1')
    {
        for(int i=start_; i<end_; i++)
        {
            if(text[i] == '*' || text[i] == '/')
            {
                //find previous and next operands after this, send locations to calculate_two
                for(int p=i-1; start_-1<p; p--)
                {
                    if(text[p] == '+' || text[p] == '-' || text[p] == '*' || text[p] == '/' || text[p] == '(' || text[p] == ')')
                    {
                        prevOpn = p;
                        flag = '1';//means it worked
                        break;
                    }
                }
                if(flag =='0')//means prevOpn could not be found
                {
                    prevOpn = start_-1;//because we will add+1 when calling calculate_two func
                }
                //------------------------------------------------------------------------------------
                flag = '0';
                for(int n=i+1; n<end_; n++)
                {
                    if(text[n] == '+' || text[n] == '-' || text[n] == '*' || text[n] == '/' || text[n] == '(' || text[n] == ')')
                    {
                        nextOpn = n;
                        flag = '1';
                        break;
                    }
                }
                if(flag == '0')
                {
                    nextOpn = end_;//or end_+1 ???
                }
                //------------------------------------------------------------------------------------

                newText = replace_(prevOpn+1, nextOpn, calculate_two(prevOpn+1, nextOpn, text), text);//this will also change start,end point
                end_ = end_ - text.length() + newText.length();//also works if end_ point goes farther 
                text = newText;
                restart_func = '1';

                break;
            }
            restart_func = '0';
        }
    }
    cout<< "return text in xdivide:                "<< text <<endl;
    return text;
}

string bigCalculate(int start_, int end_, string text) //calculates given spaces and returns answers of that space
{
    string newText;
    string answer;
    newText = find_xdivide(start_, end_, text);
    end_ = end_ - text.length() + newText.length();
    text = newText;
    newText = find_otherOp(start_, end_, text);
    end_ = end_ - text.length() + newText.length();
    text = newText;

    //find and return requested space
    for(int i=start_; i<end_; i++)
    {
        answer = answer + text[i];
    }
    return answer;
}


string solveParenthesis(string text)//runs till there is no more parenthesis.
{
    int len_ = text.length();

        for(int i=0; i<len_; i++)//'(' bulamazsa bu loop bir sey yapmadan biter
        {
            if(text[i] == '(')
            {
                for(int a=i+1; a<len_; a++)
                {
                    if(text[a] == '(') {break;}

                    else if(text[a]==')')
                    {
                        ////a+1 because i want it to also delete ')'
                        text = replace_(i, a+1, bigCalculate(i+1, a, text), text);
                        len_ = text.length();
                        i = -1;//restarts i loop. Adds +1 after break.
                        break;
                    }
                }
            }
        }
cout <<"return text of solveParenthesis:       " << text<<endl;
return text;
}


int main()
{
    string input;
    string answer;
    cout << "Whatchu want?!?\n";
    getline(cin, input);
    cout <<"\n";

    input = delSpaces(input);
    if(check(input)==false){ return 0; }//hatalı karakter var mı test et

    answer = solveParenthesis(input); //get rid of parentheses
    cout <<"answer after solveParenthesis:         "<<answer <<endl;;
    answer = bigCalculate(0, answer.length(), answer); //run this big boy all the way

    cout <<"\nAnswer:                                "<< answer <<endl;

    cin >>input;
return 0;
}

//check if operators is one after another like /* or +/.
//")(" arası kontrol etme ve araya'*' koyma eklenebilir.
//find_xdivide ve find_otherOp arasında çok küçük bir fark var. Sadece bir if statement. Birleştirilebilir.
//new operations can be addable like taking exponent(3^2=9) or square root.
//[DOUBLE ADDED] integer changable into double or float type. [DOUBLE ADDED]
//add checking number-open_parenthesis and closed_parenthesis-number. '*' can be addable between those.

//(3+5)*7+2/(3-1)
//8*7+2/2
//56+2/2
//56+1
//57