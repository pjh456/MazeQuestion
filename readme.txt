API 文档

该项目使用 javascript 的部分子集作为执行语言，如不了解该语言可以看文档后面为 C++ 开发者快速入门用的 javascript 教程。

一、语言可支持函数设计：

move_up/move_down/move_left/move_right：
向上/下/左/右移动地图上的两格（即点坐标上的一格），没有返回值。

look_up/look_down/look_left/look_right/stand：
观察当前位置上/下/左/右/脚下一格的位置的点，返回一个字符串表示点坐标的类型，
有 "wall", "air", "body", "start", "end" 五种可能，
分别为 墙，空气（可走通的路），已经走过的路，起点，终点。
注：如果想要判断字符串的值是否相等，需要用 "===" 比较，
如 stand() === "end"，会返回一个布尔值 true/false 表示是/否成立。

start_pos/end_pos/current_pos：
获取起点/终点/当前位置的坐标，坐标定义为先行后列。
注：如果想要获取坐标的行、列值，可以通过列表解构或直接访问下标，
如 [row, col] = start_pos(); 
或 row = start_pos[0], col = start_pos[1];

print：
打印信息在底部的日志栏中，多个数据同时传入用逗号隔开即可，
如：print("Hello", "world!"); 会在日志栏输出 "Hello world!"。

二、Javascript 入门教程：

1. 变量声明：不同于 C++ 需要在变量名前写明类型，Javascript 的变量声明使用 let，如：let x = 1; let y = start_pos();

2. 变量赋值：使用 = 连接变量和值，左侧为被赋值的变量，右侧为将要赋给这个变量的值（也可以是变量，会取出变量的值赋给左侧的变量）
Javascript 的一个变量可以承载多种类型，如：let x = 1; x = "Hello world!"; 是合法的。

3. 函数声明：不同于 C++ 需要在函数名前写明类型、参数列表里注明参数类型，Javascript 的函数声明使用 async function，
如：async function add(x, y) { return x + y; }
再如：async function greet() { print("Hello world!"); }

4. 变量调用和 C++、Python 等大众语言一致，变量直接写变量名；函数调用需要在函数名前加 "await "，在后面加括号和参数，
如：await add(1, 2);
再如：await greet();
但是语言内支持的函数不需要手动添加await！
如：look_up();

5. 循环：可以和 C++ 一样使用，
如 for(let i=1; i <= 10; i++) { }
或 let i = 10; while(i!=0) { i--; }

6. 数组声明：不同于 C++ 需要利用 array 和 list，Javascript 可以利用空或非空的方括号来声明一个变长的数组。
如：let arr1 = []; let arr2 = [1, 2, 3];
数组拥有中括号加下标访问某个位置的元素的能力，下标从 0 开始，
如：arr2[0]; 其值为第一个元素的值。
数组拥有长度和往尾部添加、删除元素的能力，
如：arr2[0].length; 其值为数组 arr2 的元素个数。
再如 arr2.push(4); arr2.pop(); 分别往尾部添加和弹出了一个元素。