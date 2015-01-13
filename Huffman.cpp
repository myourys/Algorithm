/*=============================================================================
#     FileName: Huffman.cpp
#         Desc: Huffman 编码解码实例
#       Author: Hector
#        Email: myourys@gmail.com
#     HomePage: http://www.yiwuye.com
#      Version: 0.0.1
#   LastChange: 2013-03-29 01:30:34
#      History:
=============================================================================*/
/*
 * 霍夫曼编码（Huffman Coding）是一种编码方式，是一种用于无损数据压缩的熵编码（权编码）算法。
 * 方式是先通过优先队列建立Huffman树,求得Huffman编码,然后用此码编码和解码
 * 参考: <http://coolshell.cn/articles/7459.html>
 */
#include <iostream>
#include <map>
#include <queue>
#include <sstream>
#include <fstream>
#include <iterator>
#include <algorithm>
using namespace std;

typedef map<char,unsigned int> SymbolCount; //存放词频,用来构建Huffman Tree
typedef map<char,string> HuffmanCode; //存放每个字符对应的Huffman编码
typedef map<string,char> HuffmanDecode; //存放字符串的解码数据

/*
 * Huffman Tree 节点
 */
struct Node
{
    unsigned key; //词频
    char symbol;//待编码的字符
    Node* lchild;
    Node* rchild;

    Node(char s,unsigned f){
        symbol = s;
        key= f;
        lchild =NULL;
        rchild =NULL;
    }

    Node(Node* l,Node* r)
    {
        symbol = 0;
        key = l->key + r->key;
        lchild = l;
        rchild = r;
    }

    bool leaf() const //是否叶子
    {
        return lchild == NULL && rchild ==NULL;
    }

    bool operator <(Node &other)
    {
        return (*this).key > other.key;
    }

};

/*
 * 比较的结构体,用于后面的优先队列,具体参考优先队列的使用
 */
struct DereferenceLess
{
    template <typename T>
    bool operator ()(T& p1, T& p2) const
    {
        return *p1 < *p2;
    }
};

/*
 * 统计每个字符出现次数，用Map存放
 */
void CountSymbols(SymbolCount& freq_table,istream& s)
{
    while(1)
    {
        char c(s.get());
        if (s.eof())
            break;
        freq_table[c]++;
    }
}

/*
 * 打印Huffman树
 */
void PrintHuffmanTree(Node *node,unsigned int depth = 0)
{
    if (node == NULL)
        return;
    string indent(4 * depth,' ');
    if (node->leaf())
        cout << indent<<node->symbol<<" ("<<node->key<<")"<<endl;
    else
        cout << indent << '*' << " (" << node->key<< ")"<<endl;

    PrintHuffmanTree(node->lchild,depth+1);
    PrintHuffmanTree(node->rchild,depth+1);
}


Node *CreateHuffmanTree(vector<Node>& leaves)
{
    /*
     * 优先队列存放节点，用于辅助建树
     * 参考 http://www.cplusplus.com/reference/queue/priority_queue/
     */
    typedef priority_queue<Node*,vector<Node*>,DereferenceLess> NodePtrQueue;
    NodePtrQueue nodes;

    vector<Node>::iterator p;
    for (p = leaves.begin();p!= leaves.end();++p)
        nodes.push(&(*p));

    // 根据队列的优先级别,自底向上建立Huffman树
    while(nodes.size()>1)
    {
        Node *first = nodes.top();
        nodes.pop();
        Node *second = nodes.top();
        nodes.pop();
        Node *combined_node = new Node(first,second); //建立新的父节点并放入优先队列
        nodes.push(combined_node);
    }

    return nodes.top();
}

//计算Huffman Tree的对应编码
void UpdateHuffmanCode(HuffmanCode& code,Node* node,const string& prefix)
{
    if (node == NULL)
        return;
    if(node->leaf())
        code[node->symbol] = prefix;
    else
    {
        UpdateHuffmanCode(code,node->lchild,prefix + '0');//左子树为0
        UpdateHuffmanCode(code,node->rchild,prefix + '1');//右子树为1
    }
}

void FreeHunffmanTree(Node *node)
{
    if(node == NULL || node->leaf())
        return;
    FreeHunffmanTree(node->lchild);
    FreeHunffmanTree(node->rchild);
    delete node;
}

/*
 * 压缩完毕,解码函数开始
 */

/*
 * 读取Huffman的解码,并将正文读取到msg中
 */
void ParseInputFile(HuffmanDecode & code_table,string &msg,istream& input)
{
    while(1)
    {
        char c,dash;
        string codeword;

        input.get(c); //字符
        input.get(dash); //分隔符
        getline(input,codeword); //剩是字符的转码

        if(codeword.find_first_of("01")== string::npos) //如果没有0或1,则查找完毕
            break;
        code_table[codeword] = c;
    }

    //第一个行分隔符上面已经读了,读取写入的位数长度
    unsigned int nr_bits;
    input>>nr_bits;

    //过滤掉位数长度行 和 第二个分隔行
    string _;
    getline(input,_);
    getline(input,_);

    //设置字符串长度,并清空
    msg.reserve(nr_bits);
    msg.erase();

    char c;
    while(input>>c) //每字节读取(8bit)
    {
        int i;
        for(i=0;i<8;++i)
        {
            //转换成01
            if((c>>(7-i)) & 1)
                msg.append("1");
            else
                msg.append("0");
            if (--nr_bits == 0)
                break;
        }
    }
}

/*
 * 解码正文
 */
void DecodeMsg(HuffmanDecode& code,const string& msg,ostream& output)
{
    HuffmanDecode::iterator i;
    unsigned int max_prefix_length = 0;
    //获取最大的编码长度
    for(i =code.begin();i!=code.end();++i)
    {
        unsigned int current_length = i->first.size();
        if(current_length > max_prefix_length)
            max_prefix_length = current_length;
    }

    unsigned int start =0;
    while (start <msg.size())
    {
        unsigned int length;
        bool found(false);
        for (length = 1;length<=max_prefix_length;++length)
        {
            string prefix(msg.substr(start,length));
            //从最短的开始尝试解码,因为无相同前缀
            if(code.find(prefix) != code.end())
            {
                output<<code[prefix];
                start += prefix.size();
                found =true;
                break;
            }
        }

        if(!found)
        {
            cerr<<"Decode error~"<<endl;
            break;
        }
    }
}

int main(int argc,char *argv[])
{
    ifstream entrada("in.txt");
    stringstream text_stream;

    text_stream << entrada.rdbuf();

    SymbolCount frequencies;
    CountSymbols(frequencies,text_stream); //统计词频

    // del los caracteres especiales @ # *
    // 这三个字符当做最常见的字符,特殊处理,不放入Huffman Tree
    unsigned int arroba = 0,asterisco = 0,gato =0;
    arroba = frequencies['@'];
    frequencies.erase('@');
    asterisco = frequencies['#'];
    frequencies.erase('#');
    gato = frequencies['*'];
    frequencies.erase('*');

    vector<Node> leaves;
    SymbolCount::iterator sym; //Map的迭代器
    for (sym = frequencies.begin();sym!=frequencies.end();++sym)
    {
        Node n(sym->first,sym->second); //Map的第一个元素 ->字符,第二个元素->频率
        leaves.push_back(n);
    }

    Node *root = CreateHuffmanTree(leaves);

    HuffmanCode code;
    //计算HuffmanCode
    UpdateHuffmanCode(code,root,"11");

    //树从11开始,0,1,10 留给@ # *
    code['@']="0";
    code['*']="101";
    code['#']="1001";

    //PrintHuffmanTree(root);
    //得到编码,树已经没有用
    FreeHunffmanTree(root);

    vector<unsigned char> encoded_msg; //用来存放转码,1个字节占1行
    string text(text_stream.str());
    string::iterator symbol;
    unsigned int bit_count =0;
    int bits_in_byte =0;
    unsigned char c =0;

    //开始编码 symbol:每个字符
    for (symbol = text.begin();symbol!= text.end();++symbol)
    {
        string current_code(code[*symbol]); //得到编码
        string::iterator bit;
        cout << code[*symbol]; //输出编码

        for(bit = current_code.begin();bit !=current_code.end();++bit)
        {
            //把每八位转成2进制存到1个字节里面
            if(*bit=='1')
                c = (c << 1) +1; //左移1位然后补1
            else if (*bit == '0')
                c=c<<1;          //左移1位然后补0
            else
                cerr<<"ERROR"<<endl;
            bit_count++;
            bits_in_byte++;
            if (bits_in_byte == 8) //每8位存1字节
            {
                encoded_msg.push_back(c);
                bits_in_byte = 0;
            }
        }

    }

    if (bits_in_byte != 0)
    {
        c<<= 8-bits_in_byte; //剩下的几位移到开头来
        encoded_msg.push_back(c);
    }

    ofstream salida("out.txt");

    //先写入Huffman的编码,便于解码
    HuffmanCode::iterator codeword;
    for(codeword = code.begin();codeword!= code.end();++codeword)
    {
        salida << codeword->first <<"-"<<codeword->second<<endl;
    }
    salida <<"--"<<endl;
    //写入正文总位数
    salida <<bit_count<<endl;
    salida <<"--"<<endl;

    //写入正文
    copy(encoded_msg.begin(),encoded_msg.end(),ostream_iterator<unsigned char>(salida));

    salida.close();

    cout<<endl;

    //解码

    HuffmanDecode code_table;
    string decoded_str;
    ifstream input("out.txt");
    ofstream output("out.txt.decoded");

    ParseInputFile(code_table,decoded_str,input);
    DecodeMsg(code_table,decoded_str,output);


    return 0;
}
