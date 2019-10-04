# C++中文乱码的解决方案
## 字符编码基本概念
> 由于历史上有两个组织定义了两个孪生的统一的字符集，所以相关概念十分混淆不清,
> 下面按照他们的创立组织来稍作介绍  

1. 国际标准化组织(ISO/IEC JTC 1/SC 2)  
  * 制定了ISO/IEC 10646标准
  * 上述标准中定义了通用字符集（Universal Coded Character Set / UCS）
  * 上述标准为UCS定义了几种编码形式，分别为
    * UCS-2（最早通常就叫做Unicode,这里是指一种编码）

2. Unicode联盟（the Unicode Consortium）
  * 制定了所谓的Unicode标准（The Unicode Standard）或者很多时候简称Unicode（这里是指标准）
  * 很多时候Unicode标准定义的字符集也叫Unicode（这也就是很多知乎大大们说Unicode是“字符集”的原因
  * Unicode标准也定义了很多编码形式，例如
     * UTF-8
       > UTF即指Unicode Transformation Format,UTF-8顾名思义就是Unicode的8位编码
     * UTF-16
     * UTF-32

两者的字符集其实是一模一样的，只不过标准的其他内容不尽相同，简单起见，并参考大家现时的普遍认知，
我们做以下定义：
* 标准称之为Unicode标准，不和ISO10646进行区分（强调一下：两个标准是不一样的，只不过我现在这个level，并没有太大区别）
* UCS-2 是一种编码，并不在称之为Unicode
* Unicode 即指“通用字符集”，与UCS一样

最后我们再列举一下几个编码形式以及他们的相互关系
* ASCII
  > 应该是最早的编码形式，应该是个人都知道，只用一个byte， 只有128个字符，基本上就只支持英文
* UCS-2
  > 较早且简单的编码形式，使用2个byte，固定长度，理论有65536个字符，但是很多其实都没用，
  > 后来慢慢发现这样还是不够用
* UTF-16 
  > 对UCS-2的扩展，变长，最长可到4个字节，兼容UCS-2
* UCS-4
  > UCS-4每个字符用4个字节来表示，真正做到可以包含所有的字符，然而存储量也比较大
* UTF-32
  > 和UCS-4很像，定长，其实是UCS-4的子集
* GB18030
  > 主要针对中文，也是一种UTF，兼容GBK
* GBK
  > 汉子内码扩展规范，是一种非Unicode的编码，但是相对于UTF-8对中文的存储效率更高
* UTF-8
  > 变长编码，字节数1-4，兼容ASCII，没有大小端的问题，被广泛使用
* ANSI
  > ANSI仅存在于Windows系统内，它并非某种编码，而是根据当前系统所设定的地区而变，对于简体中文系统来说，
  > ANSI可能就是GBK，对于繁体中文系统就是Big5

## 字符编码在Visual Studio中的配置
1. 代码编码  
 Visual Studio中会默认使用系统编码，大部分时候是没有问题的，然而涉及跨平台的时候就经常有各种各样的麻烦，所以我们建议
使用ForceUTF8(No Bom),Line Endings Unifier，End of Line等插件，统一选用UTF-8作为代码编码，LF作为回车符
    > 在Visual Studio 中，选择"工具"=>"扩展和更新"=>"联机"=>"搜索"，输入上述插件名，并安装
    > >  对于ForceUTF8(No Bom)，安装后重启VS，新建文件，并存储后应该会自动以UTF-8作为编码存储（实测此方案时好时坏），可使用“高级保存选项”
    > >  来确认当前文件编码。对于VS2017， “高级保存选项”默认隐藏，可参考
    > >  [高级保存选项](https://blog.csdn.net/qq_42716155/article/details/89294118)进行设置。  
    > >  对于Line Endings Unifier，安装后可右键单击解决方案，选择“Unify line endings in this solution”完成回车符的统一  
    > >  对于End of Line，安装后可在"工具"=>"选项"=>"End of Line"中选择如何显示行尾符。
   
2. 命令行输出  
在命令行输出的时候，应将UTF-8转换为ANSI编码（同样适用于Linux）再进行输出，确保控制台输出无乱码

3. 文件输出
建议使用UTF-8进行输出，但是路径需要注意，需要使用ANSI编码
转换时可使用下列代码
```
#include <visionnav/string/CharacterEncodingConvert.h>

using visionnav::string;

...

std::string ucs_filename = 
    cvtUtf8ToUcs2(u8_filename);
```
