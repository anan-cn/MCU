串口大师(ComMaster) For Win2000/XP 是一款集调试,测试,监视,过滤一体的串口专用软件(利用Win2k WDM设备驱动编程技术).
软件性质: 共享软件. 串口监视/过滤的功能有使用次数限制,串口调试,串口测试完全免费.
软件版本: 1.1
调试功能设置丰富,测试功能非常专业,监视功能可以监视通信程序对串口的访问流程,过滤可以对串口数据流进行更改.
串口调试/测试要独占串口,监视/过滤功能不占用串口资源.

1. 串口调试设置丰富,几乎用到了串口的所有功能.
   自动检测串口,包括主板串口,USB虚拟串口,网络虚拟串口
   波特率 110-512000( 波特率>115200时需要硬件支持 ), 数据位5-8位, 5种校验位,3种停止位(5位数据位时,才能设置1.5位)
   多种流量控制,可在发送,接收选用不同的流控方式
   能发送大的文件,和16进制字符
   显示所有的MODEM信号线,以及各种串口硬件错误(帧错,校验错..),图形方式显示数据流量

2. 串口测试功能专业,发送/接收标准通信测试用的伪随机码,测试串口线路误码率
   设置同串口调试...
   发送 2^15-1,2^11-1,2^9-1及16bit人工码,这些都是通信测试仪表选用的伪随机码型
   接收自动同步,可以测试单向的串口线路误码
   记录发生的误码个数,误码率,误码时间...
   
3. 串口监视功能分析详细
   采用WDM型设备驱动编程,不占用串口资源,监视通信程序对串口的任何访问
   监视: 波特率,数据位,校验位,停止位的设置
         各种特殊字符,读写超时,读写缓冲区的设置
         握手方式,流量控制,串口事件,MODEM信号的变化
         实时显示读写数据
   显示: 被监视串口的MODEM信号线,硬件错误,图形显示数据流量
   作用: 破解它方的通信软件,通信协议. 利用它可以看见'超级终端','拨号网络','串口专家','串口助手'等等软件对串口访问的全部过程

4. 串口过滤功能更改串口数据流
   采用WDM型设备驱动编程,不占用串口资源,应用程序根本感觉不到它的存在
   按字节,按时间,周期性的改变字符,使串口数据发生误码
   按字节,按时间,周期性的代替字符,使串口数据发生替换
   按字节,按时间,周期性的删除字符,使串口数据丢失字符
   作用: 可以模拟数据传输种出现的误码,丢失字符等现象,调试串口的通信协议,不能检查数据错误的通信协议是失败的协议
   
