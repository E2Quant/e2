# E2Lang

<div align="center">
 
[![License](https://img.shields.io/badge/license-BSD--3--Clause-blue?style=flat-square)](LICENSE)
[![点击链接加入群聊【E2Quant】](https://img.shields.io/badge/QQ%E7%BE%A4-995910672-green)](https://qm.qq.com/q/isPUXV7sdO)
[![@E2Quant](https://img.shields.io/badge/Telegram-2CA5E0?style=flat-squeare&logo=telegram&logoColor=white)](https://t.me/+FL19RxoJpztmY2E5)

 LLVM JIT (即时运行时动态编译代码 [`字节码`] )<br/>提供专业的交易策略底层API<br/>易于学习超简单的编程语法

</div>

## 关于 E2L 策略编程语言

E2L 使用 C++ 开发的一种策略性语言，它基于 LLVM IR 基本架构, [ FLEX 词汇分析器生成器](https://westes.github.io/flex/manual/index.html#SEC_Contents) 及 [ GNU BISON (YACC) 通用的解析器生成器 ](https://www.gnu.org/software/bison/) 作为语法分析. 主要功能是价格的计算, 即数学的运算为主的一种简单性的编程语言


## 如何安装
请参考 [安装](https://e2q-doc.readthedocs.io/Installation/)

## E2L 在 [E2Q (交易系统)](/E2Quant/e2q) 运行过程

E2L Script 运行思维图:

![E2L mind map](https://e2q-doc.readthedocs.io/images/tickrune2l.png "E2L")


- [`E2L::INIT`](#init) 系统初始化
- [`E2L::EA`](#UOMSRisk::I_EA--ea) EA 运行交易策略模型.
- [`E2L::OMS`](#reverse-mode---cladgradient) OMS 系统撮合处理 (Order Limit Book).
- [`E2L::Broker`](#hessian-mode---cladhessian) Broker 经纪商(私募)关于风险控制 .

E2L 详细底层系统 API 请参考 [e2l_api](https://e2q-doc.readthedocs.io/e2l_api/).

## E2L 运行状态

### Init - `E2L::INIT`
初始化函数 `FIsInit();` 通过返回 UInitOk 结构标识当前运行的状态.

`UInitOk` 两种不同的状态:
1. `I_OK` 策略可以进入分析
2. `I_Proc` 策略初始化中

> 以 Uxxx 开头的结构均是系统定义的结构

```cpp
union UInitOk {
    I_OK = 1;
    I_Proc = 0; 
}
```

### EA 交易策略 - `E2L::EA`

- `e2q` 进程.
1. `-p` 指定数据库配置文件
2. `-r` 当前运行的次数，可作为策略的版本参数
3. `-a` 在 ea 端代表当前的 EA 是第几个策略进程，默认:0
4. `-e` EA 的交易策略代码

Shell 命令

```shell
user@e2q/build# ./e2q -p ../cfg/db.properties -r 0 -a 0 -e /opt/invest/ea_market.e2

```
### OMS - `E2L::OMS`

- 撮合进程.
1. `-p` 指定数据库配置文件
2. `-r` 当前运行的次数，可作为策略的版本参数
3. `-a` 在 撮合 端代表将会有多少个 EA 进程进入，默认:1
4. `-s` 撮合端代码

Shell 命令
```shell
user@e2q/build# ./e2q -p ../cfg/db.properties -r 1 -a 3 -s /opt/oms/oms_market.e2 

```

###  Broker 经纪商(私募) - `E2L::Broker`

当前的代码会在 `oms_market.e2` 中通过 函数 `FWhois();` 返回 UOMSRisk 结构体以区分

```cpp
union UOMSRisk{ 
    # OMS 是柜台撮合中心
    I_OMS = 0;    
    # 代理商
    I_BROKER = 1;
    # 策略者
    I_EA = 2;
} 
```


### E2L 关键词

#### 这是 E2L 中的保留字列表。因为它们为语言所用，故这些关键词不可用于重定义。

- Body 类
    - "union" { 结构体 }
    - "func"  { 函数体 }
    - "import" { 引入代码 }
- 多条件类
    - "switch"		
    - "case"		
    - "default"		
- 单条件类
    - "if"		
    - "else"			
- 循环类
    - "for"		
    - "do"			
    - "while"			
- 跳转类
    - "continue"		
    - "break"			
    - "return"		



### 语法描述

[详细语法描述](https://e2q-doc.readthedocs.io/e2l/)

展示基本的案例

```cpp

import <luquant/ModeMagic.e2>

#--------
# Name:functMainEvention
#   Parameters:
# - arg1: tick_size
# - arg2: thread_id
# -> return 
# Description: 
#  测试
#--------	
func MainEvent(tick_size, thread_id) {
    code = EmCfiCode() ; 
    timeframe =  EmCurrentTFrame() ;

    if (tick_size > 0) {
        now_time = FTime(code, timeframe, 0);
        now_close = FClose(code ,timeframe , 0);
        adj_close = FAdjClose(code ,timeframe , 0);
    }

}
```

## 未来功能
- 解释 LaTeX Math 
- 完善数组指令
- 类(Class Object)功能
- 接入 GUP 运算


### 许可证
本项目采用 BSD-3-Clause 许可证。

### 联系方式

- 有问题或建议？请通过以下方式联系我们：
    - 📧 Email: vyouzhi@gmail.com
    - Telegram: [@E2Quant](https://t.me/e2quant_from_github)

🐞  [Issue Tracker](https://github.com/E2Quant/e2/issues) 
