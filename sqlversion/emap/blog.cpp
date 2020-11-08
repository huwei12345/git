//10.30
/*
sort: void mysqlsort(CMysql* mysql);//选择按哪个字段排序，从高到低，从低到高
search:void mysqlsearch(CMysql* mysql);选择按mysql语句查询
		：选择特定等值查询，自己组织sql语句
update：void mysqlupdate(CMysql* mysql);读到内存。一条一条写到文件。跟新到文件，以字符形式写
bupdate：void mysqlbupdate(CMysql* mysql);同上，以二进制格式写
insert：void mysqlinsert(CMysql* mysql);选择以mysql语句插入数据
		选择以输入全部字段插入数据
delete: void mysqldelete(CMysql* mysql);以mysql语句删除
		以输入LinkID字段删除

showall：一条一条显示。
*/


/*
11.4
1.应添加query按行查询。减少内存使用。比较性能。（完成）
2.应添加修改功能。alter (完成,1.添加set语句。2.输入全部语句)
3.应规范输入方式。'1,1,1,1,1,'hrll',1,1' -> '1 1 1 1 1 gello 1 1'; （完成，将‘ ’改为‘ ，’）
4.从文件读取到mysql，恢复。（完成）
5.读到Record，（完成。）
6.恢复？（用二进制文件恢复，完成）
7.新添加的项应该满足recordsize和roadsize的读取规则否则不能恢复，考虑自动计算这几个字段(完成)


8.权限？select * from，不该暴露查询接口，要么修改语句，要么先取消权限，结束后再添加权限。

9.日志？(把一次开始到结束的日志放到一个文件)
当前时间（年月日）  执行语句 类型 用户 多长时间 操作了那一部分数据LinkID范围
网络日志：
时间 线程几  peerip port 请求 请求类型 用户 多长时间 操作了那一部分数据LinkID范围 server:ip port
（还需了解）

10.上下左右箭头?(?) shell
*/

//先移植到linux上

//先写非面向对象的

//创建服务器程序，等待客户端请求，发送数据库中的数据到客户端。
//多线程，日志，mysql，连接IO，data线程 RDB AOF
//提供登录逻辑 权限
//epoll+thread+Reactor


//客户端用QT 登录 连接 请求 获取相应


//编解码器 消息格式

//提供Web端，用自己做的HTTP 和nginx各一个
//cgi 、rpc、ftp

//单例线程池、并发锁Mutex、时间轮踢掉超时连接、时间堆处理定时器、信号、日志
//性能分析。