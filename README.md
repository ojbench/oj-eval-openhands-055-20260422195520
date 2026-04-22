# Problem 055 - ACM EXPRESS

**ACMOJ Problem ID**: 1421

## Table of Contents

- [Problem 055 - ACM EXPRESS](#problem-055-acm-express)
  - [Table of Contents](#table-of-contents)
  - [Introduction](#introduction)
    - [Background](#background)
  - [Assignment Description](#assignment-description)
    - [Grade Composition](#grade-composition)
  - [Assignment Requirements](#assignment-requirements)
    - [Input Format](#input-format)
    - [Output Format](#output-format)
    - [Samples](#samples)
    - [Data Constraints](#data-constraints)
  - [Per-Testcase Resource Limits](#per-testcase-resource-limits)
  - [Test Data](#test-data)
  - [Submission Requirements](#submission-requirements)
    - [Submission Format](#submission-format)
    - [Submission Guidelines](#submission-guidelines)
    - [Evaluation Notes](#evaluation-notes)
    - [Academic Integrity](#academic-integrity)

## Introduction

### Background

Build a logistics management system in a post-apocalyptic setting. Network routing, package delivery, resource management.

## Assignment Description

### Grade Composition

| Grading Component | Percentage |
| :--: | :--: |
| Pass **1421. ACM EXPRESS** | 80% |
| Code Review | 20% |

Here are several points that need clarification:

- In the Code Review, we will **strictly examine your code style and repository organization structure, etc.**

- This assignment provides some sample data for testing, stored in the `/workspace/data/055/data_test/` directory. Note that these are not the test cases on the Online Judge. Passing all local test cases does not guarantee that you will pass the OJ tests.

- Besides the provided sample data, we also encourage you to design your own test data based on your program logic to assist debugging.

## Assignment Requirements

### Problem Description

题面故事内容不会影响理解题目内容，可以跳过。以下内容均为虚构，如有与现实雷同纯属巧合。

> Send not to know for whom the bell tolls, it tolls for thee.
>
> 不要问丧钟为谁耳鸣，丧钟敲响正为你的亡灵。

“……
现在是灾变 128 年…你说公历？好遥远的概念……应该是…… 2127 年吧。在 1999 年大灾变发生之后，死亡搁浅现象开始在全球各地出现，死亡被搁浅，时间被割裂，国家形态不存。这都是我从历史库中看来的。听说那个时代是所谓 “全球化” 的时代…真是难以想象。人们不需要与他人交流，这才是正常的。

……

生存？开罗尔网络能够打印各种物体，牛排、维生素、能量水、威士忌……生存不是问题。

……

交流、合作、未来？为什么要未来？你知道的，冥滩连接着所有时间，不存在过去与未来，只有当下。

……

祝你好运，不见。”

眼前的视野转入黑暗，耳边响起熟悉的胎儿声与水声，意识重新浮现至水面。

你摘下开罗尔头显，眼前是熟悉的天花板。

你现在在你的房间里，更准确地说，是在 Mindwung 节点城的生活区 X15。你是 ACM Express 的一名文职人员。ACM Express 是在大灾变之后出现的物流公司之一，本部设于 Mindwung 节点城，口碑不错，在 Chining 大陆东部各地都派送过订单。

ACM Express 用 15 年重新在 Chungentrial 地区建立物流基础设施——高空索道、防时间雨高速路、跨泯灭坑隧道。但是，ACM Express 在 Chungentrial 地区的成果并没有给予人们跨越 Qinhwai 泯灭带的信心。所以，他们现在有一个大计划要执行——重振 Chining 国的超级物流系统。如果能将 Peching 接入开罗尔网络，或许人们的想法会有所转变。

公司的科技局正在进行最后的准备，在开罗尔网络中，他们已经找到了真空磁悬浮高铁与反重力运载机的技术，前者能保护车厢通过泯灭区，后者能通过在任何地形。目前，他们缺少了一个关键组件——物流管理系统。物流管理系统的工作被分为多个订单，你在阅览所有订单后认为其中一份订单或许你可以提供帮助：

<a href="https://sm.ms/image/6wu1ZQ3RxlOUHE2" target="_blank"><img src="https://i.loli.net/2021/11/22/6wu1ZQ3RxlOUHE2.png" style="width: 100%"></a>

在本题中，你需要实现四个保存快递信息的类：`mail`，`air_mail`，`train_mail`，`car_mail`。我们提供一个基类`object`：

```c++
// 你无需修改、提交以下代码，即，你最终的提交 **不应该** 包含以下代码。
// 本题评测时使用的 object 类存放于名为 base.hpp 的文件里，你最终的提交需要 include 该头文件以避免 ce 。
// 即，你的提交应包含一行 #include "base.hpp" 。

// 以下函数说明只是便于理解，详细的要求见各个派生类的说明。
#include <iostream>
using namespace std;
class object {
protected:
    string contain;
public:
    // 构造函数。
    object() = default;
    object(string _contain_) : contain(_contain_) {}
    
    // copy 函数，将 o 指针对应的类的信息拷贝到调用该函数的类对象上。
    // 保证 o 与 this 是同一种派生类指针，但会以 object * 的形式传入。
    // 具体可以参考 main 函数中的调用方式。
    virtual void copy(object* o) = 0;
    
    // 参数为某个日期，返回一个字符串，代表此日期快递的派送状态。
    virtual string send_status(int y, int m, int d) = 0;
    
    // 返回派送快递的方法。详见各个派生类的说明。
    virtual string type() = 0;
    
    // 输出保存于类内的信息，具体格式详见各个派生类的说明。
    virtual void print() {
        cout << "[object] contain: " << contain << endl;
        // 注意：本题评测时使用的 object 类会与这里的版本有微小的区别，但不会对于完成本题有影响。
    }
    
    // 析构函数。
    virtual ~object() {}
};
```

其中`contain`为一些存储于`object`类内的字符串信息。

你需要实现的每个类都需要从`object`继承（有可能是非直接继承）。具体而言，你需要完成如下继承树：

<a href="https://sm.ms/image/sePOug5dASJ4Thb" target="_blank"><img src="https://i.loli.net/2021/11/22/sePOug5dASJ4Thb.png" style="width: 50%"></a>

其中除去`object`类以外的内容均需要你去实现。

另外，我们还提供一个日期类`date`：

```c++
struct date {
    int year, month, day;
    date() = default;
    date(int y, int m, int d) : year(y), month(m), day(d) {}
    //todo 实现流输入
    //todo 实现 operator< 的重载
};
```

其中你需要实现`date`类的`operator>>`重载，使得其支持流输入。具体格式为

```c++
<year> <month> <day> // 代表年份为<year>，月份为<month>，日期为<day>
2020 1 2 // 例如，这个输入代表2020年1月2日
```

你还需要实现`operator<`的重载，去实现日期类的比较功能。**小于的含义是时间上早于。**

**注意**：在本题中，为了简化计算，我们假设一年有360天，一年有12个月，每个月有30天。

在四种`mail`类中，你均需要实现构造函数、析构函数、`copy`函数、`send_status`函数、`type`函数、`print`函数，其中析构函数只需保证没有内存泄漏即可，以下不做特别说明；其余函数除去构造函数，参数列表均与`object`类相同，以下也不做特别说明。这些函数均需要实现**override**，即，派生类拥有不同的函数实现，使用基类指针调用时优先调用派生类的实现。

作为一种良好的代码风格，除去上述你需要实现的函数应定义成`public`，你的类内变量以及你需要的内部辅助函数均应定义成`protected`。

以下的说明中，参数均只代表变量类别，你可以自由选择引用传递或值传递；变量名只代表题面中对于该变量的称呼，你可以自由选择变量名。**输出格式中被<>包围的信息即你需要输出的变量之名称**。

### mail

在`mail`类中，你需要保存如下信息：

<a href="https://sm.ms/image/4pREqNDTyCjv7OF" target="_blank"><img src="https://i.loli.net/2021/11/22/4pREqNDTyCjv7OF.png" style="width: 100%"></a>

并实现以下函数：

构造函数：参数为

```
mail(std::string contain, std::string postmark, date send_date, date arrive_date);
```

，保证`send_date < arrive_date`。

`copy`：将`o`指针对应的类的信息拷贝到调用该函数的类对象上。对于`mail`类，保证`o`是`mail`类的指针，但会以`object *`的形式传入。

`send_status`：尚未指定派送方法，快递未送出。返回字符串`not send`即可。

`type`：尚未指定派送方法，返回字符串`no type`即可。

`print`：首先调用`object`类的`print`函数，之后输出一行

```
[mail] postmark: <postmark>
```

### air_mail

在`air_mail`类中，你需要保存如下信息：

<a href="https://sm.ms/image/w8fsLVpD23vNEkX" target="_blank"><img src="https://i.loli.net/2021/11/22/w8fsLVpD23vNEkX.png" style="width: 100%"></a>

并实现以下函数：

构造函数：参数为

```c++
air_mail(std::string contain, std::string postmark, date send_date, date arrive_date, date take_off_date, date land_date, std::string airline);
```

，保证`send_date < take_off_date < land_date < arrive_date`。

`copy`：将`o`指针对应的类的信息拷贝到调用该函数的类对象上。对于`air_mail`类，保证`o`是`air_mail`类的指针，但会以`object *`的形式传入。

`send_status`：有以下五种可能（记参数中的日期为`query_date`）

<a href="https://sm.ms/image/OFHGBqxEZA8dLuC" target="_blank"><img src="https://i.loli.net/2021/11/22/OFHGBqxEZA8dLuC.png" style="width: 100%"></a>

`type`：返回字符串`air`。

`print`：首先调用`mail`类的`print`函数，之后输出一行

```
[air] airlines: <airlines>
```

### train_mail

在`train_mail`类中，你需要保存如下信息：
<a href="https://sm.ms/image/QScd5g6JKvwmYuB" target="_blank"><img src="https://i.loli.net/2021/11/22/QScd5g6JKvwmYuB.png" style="width: 100%"></a>

并实现以下函数：

构造函数：参数为

```c++
train_mail(string _contain_, string _postmark_, date send_d, date arrive_d, string *sname, date *stime, int station_num);
```

，保证`send_date`、`station_time[0] ~ station_time[station_num - 1]`、`arrive_date`单调递增。

`copy`：将`o`指针对应的类的信息拷贝到调用该函数的类对象上。对于`train_mail`类，保证`o`是`train_mail`类的指针，但会以`object *`的形式传入。

`send_status`：有以下六种可能（记参数中的日期为`query_date`）

<a href="https://sm.ms/image/uXYL5ZzniOQG4Id" target="_blank"><img src="https://i.loli.net/2021/11/22/uXYL5ZzniOQG4Id.png" style="width: 100%"></a>

`type`：返回字符串`train`。

`print`：首先调用`mail`类的`print`函数，之后输出一行

```
[train] station_num: <station_num>
```

### car_mail

在`car_mail`类中，你需要保存如下信息：

<a href="https://sm.ms/image/JSUrjmciMlE2v6W" target="_blank"><img src="https://i.loli.net/2021/11/22/JSUrjmciMlE2v6W.png" style="width: 100%"></a>

并实现以下函数：

构造函数：参数为

```c++
car_mail(string _contain_, string _postmark_, date send_d, date arrive_d, int mile, string _driver);
```

，保证`send_date < arrive_date`。

`copy`：将`o`指针对应的类的信息拷贝到调用该函数的类对象上。对于`train_mail`类，保证`o`是`train_mail`类的指针，但会以`object *`的形式传入。

`send_status`：有以下三种可能（记参数中的日期为`query_date`）

<a href="https://sm.ms/image/L5ZuPM4C1ABs39q" target="_blank"><img src="https://i.loli.net/2021/11/22/L5ZuPM4C1ABs39q.png" style="width: 100%"></a>

其中`current_mile`的计算方法定义为$\frac{\text{已用时间}}{总时间}\times\text{总里程数}$。为了避免精度问题，一律强制类型转换成`double`再进行运算。
为了保证精度，请使用`return to_string(current_mile);`

`type`：返回字符串`car`。

`print`：首先调用`mail`类的`print`函数，之后输出一行

```
[car] driver_name: <driver_name>
```

### obj_swap

除去以上四个类，你还需要实现一个简单的`obj_swap`函数，其功能为交换两个`object`类指针所指对象。**注意这可能是两个不同派生类的对象**。

`obj_swap`函数的声明为：

```c++
void obj_swap(object *&lhs, object *&rhs);
```



## 注意事项

本题中，你能够使用的头文件只有`iostream`，`algorithm`与`base.hpp`，如有其他需要可向助教提问。

请使用`cout`进行输出。评测程序中关闭了流同步并使用了`cout`输出，使用`printf`或`puts`等可能会使输出乱序。

你可能会用到以下知识：

* reinterpret_cast<type*>(it)
* 可以对指针进行强制类型转换，可以将基类指针强制类型转换为派生类指针使用

作为一个提示，我们给出`mail`类的`copy`函数：

```c++
void copy(object *o) {
    contain = reinterpret_cast<mail *>(o) -> contain;
    postmark = reinterpret_cast<mail *>(o) -> postmark;
    send_date = reinterpret_cast<mail *>(o) -> send_date;
    arrive_date = reinterpret_cast<mail *>(o) -> arrive_date;
}
```



## 调用实例

```c++
#include <iostream>
#include <algorithm>
#include "src.hpp" // 你提交的代码
using namespace std;

void obj_copy(object* ori,object*& cop){
    string type=ori->type();
    if(type=="no type")
        cop=new mail();
    else if(type=="air")
        cop=new air_mail();
    else if(type=="train")
        cop=new train_mail();
    else if(type=="car")
        cop=new car_mail();
    cop->copy(ori);
}

const int readinSize=100000;
int main(){
    ios::sync_with_stdio(false);
    int mailNum,readSize;
    cin>>mailNum;
    object* list[readinSize]={nullptr};
    for(int i=0;i<readSize;i++){
        string type;
        cin>>type;
        string _contain_,_postmark_;
        date send_d,arrive_d;
        cin>>_contain_>>_postmark_>>send_d>>arrive_d;
        if(type=="air"){
            date take_off,land;
            string airline;
            cin>>take_off>>land>>airline;
            list[i]=new air_mail(_contain_,_postmark_,send_d,arrive_d,take_off,land,airline);
        }else if(type=="train"){
            int station_num;
            cin>>station_num;
            string* sname;
            date* stime;
            sname=new string[station_num];
            stime=new date[station_num];
            for(int j=0;j<station_num;j++)
                cin>>sname[j]>>stime[j];
            list[i]=new train_mail(_contain_,_postmark_,send_d,arrive_d,sname,stime,station_num);
            delete []sname;
            delete []stime;
        }else if(type=="car"){
            int mile;
            string driver;
            cin>>mile>>driver;
            list[i]=new car_mail(_contain_,_postmark_,send_d,arrive_d,mile,driver);
        }else if(type=="no"){
            list[i]=new mail(_contain_,_postmark_,send_d,arrive_d);
        }
    }
    int queryOp;
    int id;
    while(cin>>queryOp){
        cin>>id;
        // !following is an example:
        if(queryOp==0){
            cout<<list[id]->type()<<endl;
        }else if(queryOp==1){
            list[id]->print();
        }else if(queryOp==2){
            int y,m,d;
            cin>>y>>m>>d;
            cout<<list[id]->send_status(y,m,d)<<endl;
        }else if(queryOp==3){
            int other;
            cin>>other;
            obj_swap(list[id],list[other]);
        }else if(queryOp==4){
            //example
            object* tmp;
            obj_copy(list[id],tmp);
            delete list[id];
            obj_copy(tmp,list[id]);
            delete tmp;
        }
        // !example code finish
    }
    delete []list;
    return 0;
}
```

```c++
// src.hpp 框架代码
//代码中的所有内容均可修改
#include <iostream>
#include <algorithm>
#include "base.hpp"

// !!!如果要新增include文件请举手询问助教
using namespace std;

struct date
{
    int year, month, day;
    date() = default;
    date(int y, int m, int d) : year(y), month(m), day(d) {}
    //todo 需要实现流输入
    //todo 增加函数
};

class mail : public object
{
protected:
    string postmark;
    date send_date;
    date arrive_date;

public:
    mail() = default;

    mail(string _contain_, string _postmark_, date send_d, date arrive_d) : object(_contain_)
    {
        postmark = _postmark_;
        send_date = send_d;
        arrive_date = arrive_d;
    }

    //todo “覆盖”成员函数
    //在main.cpp中，所有包裹以object* mail_of_any_type这样一个指针来存储。
    //然而直接调用mail_of_any_type->type()或mail_of_any_type->send_status(y, m, d)将调用下列两个基类的成员函数，
    //与我们想针对不同类型包裹返回不同形式的内容需求是不符的。
    //请修改下面的内容使其满足题意
    string send_status(int y, int m, int d)
    {
        return "not send";
    }

    string type()
    {
        return "no type";
    }

    void print()
    {
        //todo 调用被“覆盖”前的成员函数
        //这是一个上一todo的对偶问题。即使派生类成员函数已被“覆盖”，怎么才能执行被“覆盖”前的功能？（可以修改函数原型）
        cout << postmark << " by mail" << endl;
    }

    //已给出copy的实现作为参考
    void copy(object *o)
    {
        contain = reinterpret_cast<mail *>(o)->contain;
        postmark = reinterpret_cast<mail *>(o)->postmark;
        send_date = reinterpret_cast<mail *>(o)->send_date;
        arrive_date = reinterpret_cast<mail *>(o)->arrive_date;
    }

    //todo 适当填充函数，注意填充的public函数只能为必须构建的函数（根据派生类的知识，缺少某几个必须的函数将导致该类的对象不能实例化）和重载函数以及构造函数析构函数
};

class air_mail : public mail
{
protected:
    string airlines;
    date take_off_date;
    date land_date;

public:
    air_mail() = default;

    air_mail(string _contain_, string _postmark_, date send_d, date arrive_d, date take_off, date land, string _airline) : mail(_contain_, _postmark_, send_d, arrive_d)
    {
        take_off_date = take_off;
        land_date = land;
        airlines = _airline;
    }

    string send_status(int y, int m, int d)
    {
        date ask_date(y, m, d);
        if (ask_date < send_date)
            return "mail not send";
        else if (ask_date < take_off_date)
            return "wait in airport";
        else if (ask_date < land_date)
            return "in flight";
        else if (ask_date < arrive_date)
            return "already land";
        else
            return "already arrive";
    }

    string type()
    {
        return "air";
    }

    void print()
    {
        //todo
        cout << "[air] airlines: " << airlines << endl;
    }

    //todo 适当填充函数，注意填充的public函数只能为必须构建的函数（根据派生类的知识，缺少某几个必须的函数将导致该类的对象不能实例化）如重载函数以及构造函数析构函数
};

class train_mail : public mail
{
protected:
    string *station_name;
    date *station_time;
    int len;

public:
    train_mail() = default;

    train_mail(string _contain_, string _postmark_, date send_d, date arrive_d, string *sname, date *stime, int station_num){
        //todo
    }

    string send_status(int y, int m, int d)
    {
        //todo
    }

    string type()
    {
        return "train";
    }

    void print()
    {
        //todo
        cout << "[train] station_num: "<<len << endl;
    }

    //todo 适当填充函数，注意填充的public函数只能为必须构建的函数（根据派生类的知识，缺少某几个必须的函数将导致该类的对象不能实例化）如重载函数以及构造函数析构函数
};

class car_mail : public mail
{
protected:
    int total_mile;
    string driver;

public:
    car_mail() = default;

    car_mail(string _contain_, string _postmark_, date send_d, date arrive_d, int mile, string _driver)
    {
        total_mile = mile;
        driver = _driver;
    }

    string send_status(int y, int m, int d)
    {
        //todo
    }

    string type()
    {
        return "car";
    }

    void print()
    {
        //todo
        cout << "[car] driver_name: " + driver << endl;
    }
    //todo 适当填充函数，注意填充的public函数只能为必须构建的函数（根据派生类的知识，缺少某几个必须的函数将导致该类的对象不能实例化）如重载函数以及构造函数析构函数
};

void obj_swap(object *&x, object *&y)
{
    //todo 交换两个指针对应的地址的两个对象
}
```



## 后续

	你回到了自己的房间。从 ACM Express Mindwung Site 完成订单回来，听说有三十几个人都接受了这份订单，公司的科技局正在挑选最终方案。物流管理系统是最后一项必须工作，它的完成之时就是 ACM Express “黑水” 计划正式全面开展的时刻。
	
	时间不多了。你已经报名了第二十批远征队的技术支持人员，就在刚才你得知自己被最终选定成为正式队员。你并没有什么特殊的感想，因为尽管你的技术不一定是公司里最好的，但是作为遣返者是远征队亟需的人才。
	
	你从手铐呼出开罗尔网络界面检查随行数据，收起桌面上的开罗尔键鼠，穿上防时间雨冲锋衣……一切就绪。
	
	Let's make Chining shining again!

### Input Format

出题人的手稿在运送过程中被时间雨侵蚀，已无法辨别其上的字迹。

### Output Format

无法识别

### Samples

#### Sample 1

**Input:**
```
无法识别
```

**Output:**
```
无法识别
```

### Data Constraints

$0 \le objectNum\le 1e5$

$0\le stationNum\le 1e5$

<a href="https://sm.ms/image/HuFnSqQL5NzUItm" target="_blank"><img src="https://i.loli.net/2021/11/22/HuFnSqQL5NzUItm.png" style="width: 100%"></a>

## Per-Testcase Resource Limits

- **Time Limit (per test case)**: 800 ms
- **Memory Limit (per test case)**: 256 MiB
- **Disk Usage**: No disk usage is permitted.

## Test Data

The test data for this problem is located at `/workspace/data/055/data_test/`.

## Submission Requirements

### Submission Format

Submit a single C++ source file to the Online Judge. The OJ provides its own `main.cpp` which `#include "src.hpp"`. Your submission will be written to `src.hpp` and compiled together with the OJ's driver code.

### Submission Guidelines

- The submitted code must be able to compile successfully through the above compilation process
- The program needs to be able to read data from standard input and write results to standard output
- Please ensure the code runs correctly within the given time and space limits
- **You must use C++ or C language** to implement this assignment

### Evaluation Notes

- The evaluation system will test your program using the provided test data
- The program output must exactly match the expected output (including format)
- Exceeding time or memory limits will be judged as the corresponding error type
- Please pay attention to the overall time performance of your code and the time complexity of each part of your algorithm.

### Academic Integrity

If any violations are found during evaluation or code review (including but not limited to using unconventional methods to pass test cases), your final score may be significantly reduced or become **0 points**.
