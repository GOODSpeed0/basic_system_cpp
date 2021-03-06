![image](https://github.com/Adreambottle/basic_system_cpp/blob/master/head_for_pjt.jpg)
# Basic System 的基本架构
*by Daniel 2020-02-23*

![image](https://github.com/Adreambottle/basic_system_cpp/blob/master/total.png)
![image](https://github.com/Adreambottle/basic_system_cpp/blob/master/Fake%20ROM%20and%20Code%20library.png)


### 一、基本结构
#### 外部系统
* 因为我们这个系统是需要在外部系统上运行的，也就是在需要在 MacOS、Windows、Linux 上运行，所以我们需要解决**系统兼容性**的问题。

* 最后需要把我们的**程序封装**起来，因为C++写出来的程序很多都是在`exe`文件，如果需要在Mac上运行的话，可能会更加麻烦一些。

#### 子环境
*  我们的所有的代码都是储存在这个子环境之中，也就是我们需要些的部分。

*  包括：
    *     RAM 运行内存；
    *     ROM 只读储存器；
    *     指令集 （Fake ROM）

#### RAM
1. 结构：
    * 内存中所有的数据都是 0 或 1，这样的**二元**数据；
    * 是一个 n*4 的 2D 型的内存，每一个 byte 都是一个 4 bits 的**4位储存结构**；
    * 需要**向量化处理**，每一个 byte 都可以用 ${content, index, usage}$ 来表示；
    * 只能**暂时储存**数据，每次打开关闭程序，RAM会重新初始化；
    * $content$ 就是一个 `0 0 0 0 `, `1 0 1 0`, `1 1 1 1`这样的组合；
    * $index$ 就是这个 byte 的索引，似乎只用一维的数据就好了，但是如果考虑到更复杂的情况下，可能会进行维度的提升；
    * $usage$ 就是这个 byte 有没有被使用。

2. Allocation and Release;
    详见天石的proposal。

3. 多进程问题：
    因为考虑到多进程的问题，所以需要考虑到RAM**是否需要分区**的问题，**动态分区**，固定分区，还是其他怎么分区的办法。

4. 内存大小：
    如果需要在RAM中暂存的**数据超过了内存或者内存分区的大小**，需要怎么办？

#### ROM
* 结构与RAM基本相同，区别在于能够**永久储存**数据。

* input 与 output 在 ROM 中的数据怎么才能**传入**到 RAM 中去；在 RAM 中的数据怎么**写入**到 ROM 中来。

* 文件储存的形式，如何生成新的文件，如何储存？

* 是否需要多层次处理，如何处理储存路径的问题。如果新建路径的话，需要怎么储存路径？

#### 指令集（Fake ROM）
* 这部分是需要我们用C++完成的程序指令，我做了一些简单的分类，包括了以下几部分：
    *     模拟BIOS
    *     主程序 (Main system code)
    *     UI (GUI or terminal like)
    *     代码库 (Coding library)
    *     编码规则 (Coding rule)

* 具体的内容见后面

* PS1:因为在真正的系统中，这些东西都是储存在 ROM 中的，但是因为我们的数据储存结构实在是太菜了，而且我们都不会汇编语言，所以就用C++来完成这些代码吧！加油 ~

* PS2:因为我也不是很懂这方面的东西，肯定会有很多疏漏之处，所以希望大家能够一起来丰富这部分的内容！





-------




### 二、指令集结构

#### 模拟BIOS
* 真正的 BIOS 是电源开启后立即启动，会进行硬件自检，然后加载主系统。

* 我们的模拟破产版 BIOS 只需要初始化 RAM 和 ROM，是否需要加载其他的硬件呢？

* 之后加载我们的主系统，加载完主系统后 BIOS 会自动退出。

#### 主系统
* 我们的主系统并没有在我们的 RAM 中运行，而是在外部环境中运行的，不知道这样是否可行。

* 在主系统开始运行后，会自动调用一些 Code Library 中必须加载的东西，比如：
    * GUI 的加载
    * 与 RAM 和 ROM 对接的端口
    * RAM 与 ROM 是否正常的监测程序
    * ...

#### GUI
* 我们是用 GUI 呢，还是用 terminal-like 的界面呢？

* GUI 的情况下，系统需要如何读取，鼠标键盘对窗口、图标、界面的操作？

* terminal 的情况下，我们需要编写什么样的指令？

#### 编码规则
* 可以模仿 utf-8, ASCII 这样的编码模式。因为我们是 2-D,4-bits 的储存系统，有没有适合我们的编码规则？还是需要我们自己进行编码。

* 如何让 OS 在0和1与数字字母两种方式中进行转换？

#### 代码库/Code Implementation
##### 1. Test application
* 需要用来跑的应用，比如说计算器，扫雷，时钟。
* 考虑一下我们的系统只能对 0 和 1 进行操作，所以不能太复杂

##### 2. Input and Output function
* Application 中传入和传出的数据怎么在内存中读取和吸入，指向内存中的哪一个部分。
* 是否需要一个统一的端口来统一控制应用I&O。

##### 3. Multiprocess
* Multiprocess 的集中情况
* one by one
* random
* drill 像转盘一样

##### 4. Reference of mouse and key
* 需要获取外部系统的鼠标位置和硬盘输入。

##### 5. GUI
Solutions    | Advantages | Disadvantages | Decision
------------ | ---------- | ------------- | --------
(1) Command line | Simple!  | Worst visual aid | Just in case...the other two are too difficult :sweat_smile:
(2) User Interface markup language | Plenty of supporting libraries; easy implementation | Not C++ | I'll try it out anyways
(3) C++ Web Development Framework  | Using C++, recommended by prof :+1: | Less supporting resources | Save this for later
(4) Qt GUI widgets  | Using C++, recommended by prof :+1:, comes with Qt Creator |  | Let's do this

##### Proposal
1. Strategy
  * Coding the user interface of simulated operating system using pure C++ code
  * Making use of Qt GUI libraries and widgets
  * Simplicity > Functionality > Appearance at the first stage
2. Sample result
![sample_result](Images/Sample user interface.jpg)



##### 6. Exception
* 程序异常怎么处理？
* 模拟硬件 RAM 中断怎么处理？

##### 7. Security
* 是否需要用户控制？
* 是否需要加密？

##### 8. Storage Path
* 在写入 ROM 里面的数据，是否需要自己的储存路径？
* 如何按照文件夹来储存，如何确定储存地址？

##### 9. ...

#####
