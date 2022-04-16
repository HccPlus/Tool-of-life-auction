#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>

//这是一个链表数据结构
//如果编译器报错，请复制同文件夹下LinkedList.cpp的路径，替换下方的"LinkedList.cpp"
#include <LinkedList.cpp>
using namespace std;

class Solution
{

private:
    struct Account
    {
        string name;
        LinkedList goods;
        int money;

        Account()
        {
            money = 1000;
        }

        int print()
        {
            cout << name << ":" << '\t';
            cout << "余额:" << money << endl;
            for (int i = 0; i < goods.size(); i++)
            {
                int ser = goods.get_node(i);
                cout << DataBase(ser) << endl;
            }
            cout << endl;
            return 0;
        }

        int print_goods()
        {
            bool has = false;
            for (int i = 0; i < goods.size(); i++)
            {
                has = true;
                int ser = goods.get_node(i);
                cout << i << ' ' << DataBase(ser) << endl;
            }
            if (!has)
            {
                cout << "无" << endl;
            }
            cout << endl;
            return 0;
        }
    };

    static string DataBase(int n)
    {
        n = n % 15;
        string str[15];
        str[0] = "靠近某城市CBD，三层，装潢精美的豪宅";
        str[1] = "人民币1亿元（直接打进银行卡，默认来源合法）";
        str[2] = "一张不用还钱，但每日消费限额5000元的信用卡（只可本人、实名、在支持信用卡的场所消费）";
        str[3] = "完美的伴侣（性别由该项的最终持有者决定）";
        str[4] = "一门精湛的技艺（达到行业前1%的级别）";
        str[5] = "一个小岛（参考鲁滨逊的，但对该岛持有各国承认的所有权、居住权、开发权）";
        str[6] = "一所宏大的图书馆（参考北化图书馆，但地段比北化好很多，其中一层有自习区，其他五层全部为藏书区）";
        str[7] = "长命百岁（但不可刻意作死）";
        str[8] = "一个勤劳且绝对忠实的仆人";
        str[9] = "三五个知心朋友";
        str[10] = "一份价值500万美元，每年纯利收入25%的股票";
        str[11] = "名垂千史（从去世后开始生效）";
        str[12] = "一张全球各大航空公司承认的会员卡，持卡可免费乘坐任意商业航班";
        str[13] = "一个按钮，每周周末按下有效，按下后可以与家人共度周末，并暂时生成一个傀儡帮你完成工作、应酬等";
        str[14] = "改写自己的性格";
        return str[n];
    }

    int build_seller()
    {
        Account seller;
        seller.name = "卖家";
        seller.money = 0;
        list.push_back(seller);
        return 0;
    }

    bool* picked;
    vector<Account> list;
    int num;

public:
    Solution()
    {
        num = 0;
        picked = new bool[30];
        for (int i = 0; i < 30; i++)
        {
            picked[i] = false;
        }
    }

    int start()
    {
        build_seller();
        cout << "Input name of players: " << endl;
        string temp;
        while (temp != "end")
        {
            cin >> temp;
            Account at;
            at.name = temp;
            list.push_back(at);
        }
        list.pop_back();
        num = list.size();
        cout << "Input ended! " << endl;
        return 0;
    }

    int _alloc()
    {
        time_t t = time(NULL);
        unsigned int seed = t;
        srand(seed);
        for (int i = 0; i < num; i++)
        {
            int step = rand() % num;
            int ser = step;
            while (picked[ser])
            {
                ser++;
                if (ser == num)
                {
                    ser = 0;
                }
            }
            picked[ser] = true;
            list[i].goods.push_back(ser);
        }
        delete picked;
        picked = NULL;
        return 0;
    }

    int alloc()
    {
        for (int i = 0; i < num - 1; i++)
        {
            list[0].goods.push_back(i);
        }
        return 0;
    }

    int trade()
    {
        string seller, buyer;
        cout << "Input seller: " << endl;
        cin >> seller;
        if (seller == "s")
        {
            seller = "卖家";
        }
        cout << "Input buyer: " << endl;
        cin >> buyer;
        int i = 0;
        for (i = 0; i < num; i++)
        {
            if (seller == list[i].name)
            {
                break;
            }
        }
        list[i].print_goods();
        cout << "Choose one to sell: " << endl;
        int n;
        cin >> n;
        if (n >= list[i].goods.size())
        {
            cout << "Input error!" << endl;
            return 0;
        }
        int temp = list[i].goods.get_node(n);
        list[i].goods.pop_node(n);
        cout << "Input the price: " << endl;
        int price;
        cin >> price;
        list[i].money += price;
        for (i = 0; i < num - 1; i++)
        {
            if (buyer == list[i].name)
            {
                break;
            }
        }
        list[i].goods.push_back(temp);
        list[i].money -= price;
        return 0;
    }

    int ope()
    {
        string str;
        for (;;)
        {
            system("cls");
            print();
            cout << "Input order to continue >>>";
            cin >> str;
            if (str == "save")
            {
                save();
                continue;
            }
            if (str == "restore")
            {
                restore();
                continue;
            }
            if (str == "trade")
            {
                print();
                trade();
                save();
                continue;
            }
            if (str == "exit")
            {
                break;
            }
            cout << "Somthing wrong, please input again~" << endl;
        }
        return 0;
    }

    int save()
    {
        ofstream outfile;
        outfile.open("data.json", ios::trunc);
        outfile << num << endl;
        for (int i = 0; i < num; i++)
        {
            outfile << list[i].name << ' ';
            outfile << list[i].money << endl;
            outfile << list[i].goods.size() << ' ';
            for (int j = 0; j < list[i].goods.size(); j++)
            {
                outfile << list[i].goods.get_node(j) << ' ';
            }
            outfile << endl;
        }
        outfile.close();
        return 0;
    }

    int restore()
    {
        list.clear();
        ifstream infile;
        infile.open("data.json");
        infile >> num;
        for (int i = 0; i < num; i++)
        {
            Account a;
            infile >> a.name;
            infile >> a.money;
            int n;
            infile >> n;
            for (int j = 0; j < n; j++)
            {
                int temp;
                infile >> temp;
                a.goods.push_back(temp);
            }
            list.push_back(a);
        }
        infile.close();
        return 0;
    }

    int print()
    {
        system("cls");
        for (int i = 0; i < num; i++)
        {
            list[i].print();
        }
        return 0;
    }
};

int main()
{
    Solution s;
    system("cls");
    s.start();
    s.alloc();
    s.print();
    s.ope();
    return 0;
}