
# E2L 

[![License](https://img.shields.io/badge/license-BSD--3--Clause-blue?style=flat-square)](LICENSE)
[![点击链接加入群聊【E2Quant】](https://img.shields.io/badge/QQ%E7%BE%A4-995910672-green)](https://qm.qq.com/q/isPUXV7sdO)
[![@E2Quant](https://img.shields.io/badge/Telegram-2CA5E0?style=flat-squeare&logo=telegram&logoColor=white)](https://t.me/+FL19RxoJpztmY2E5)

> 一种简单而强大的策略编程语言，易于学习及使用

## 未来功能
- 解释 LaTeX Math 
- 完善数组指令
- 类(Class Object)功能

## 例子

> $ cat import.e2

```
import <mod/mod2.e2>
import <mod/mod3.e2>

func test(){
}

func abc( c ){
    a=mod2(c);   
    echo(a);
    test();
}



mod3();
abc(7);

a=1;
```

> $ cat mod/mod2.e2 
```
import <mod/mod.e2>

func mod2( o ){
    ret = 2 + o;

 mod_three(ret);   
    return ret;
}

#--------
# Name:function
#   Parameters:
# - arg1: xxx
# - arg2: xxx
# -> return 
# Description: 
#  
#--------	
func mod2_2() {
    a=10;
}
#----- func end
```

> $ cat mod/mod.e2 
```
func mod_three( val ) {
    ret = val + 5;
    return ret;
}
```

> $ cat mod/mod3.e2 

```
import <mod/mod.e2>

func mod3(){
sdf=2+3;
mod2(sdf);

}
```

>  union 结构
```
union USample{
    Val=1;
}

echo(USample.Val);

```