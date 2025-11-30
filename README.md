# SleepyPet

____________
2025/5/13正式停更，重启时间未定！

* 开发者PC: 1920\*1080 with 125% 逻辑大小：1536\*864
* C++ 版本: 保证C++11以上
* qt版本: 6.8.1_msvc2022_64

修订方案:
* 使用状态机代替行为树, 状态机可以参与行为, 并且可以协调行为与人工干预
* 注册工厂模式不变

修复bug:
* [ ] 动画与行为不匹配
* [ ] 行为与人工干预不协调

接下来一段时间有两个任务:
* [ ] 重构状态机允许其参与行为
* [ ] 重构动画资源

发现的问题:
* [x] AI行为树无法正常协调行为与人工干预

优化问题:
* [ ] enter函数重复赋值问题，可以初始化时赋值，时间关系不考虑优化
* [ ] QRect screenGeometry;可以被定义为全局变量;
* [ ] 移动桌宠动画，使用事件过滤器和状态机无法全面控制，需要使用定时器

未实现状态设计:

`SleepyStateCrawl`:
> 当桌面宠物从CrawlIdle进入Crawl后，
桌面宠物只能向上爬行（一段距离），而后返回CrawlIdle，
当达到一定高度后，忽略Crawl，直接进入CrawlIdle或JumpDown
{尝试采用动画驱动行为}

`SleepyStateSleep`:
> 当桌面宠物从SleepIdle进入Sleep后，宠物有较长时间的睡眠时间，睡眠期间可被惊动
惊动后，睡眠时间加长。

* idle
<img width="160" height="160" alt="image" src="https://github.com/user-attachments/assets/498c3aae-5ffa-447f-bd01-9200213a3a1e" />

* walk
<img width="160" height="160" alt="image" src="https://github.com/user-attachments/assets/69fdee24-2d2e-4257-ac79-03f3768dee61" />

* drag
<img width="159" height="161" alt="image" src="https://github.com/user-attachments/assets/8cbc0c3a-7d8e-4c24-90d8-efe31b454eed" />

* fill
<img width="160" height="163" alt="image" src="https://github.com/user-attachments/assets/1d5c09cc-642f-48da-a97e-ef81b924f7b2" />

* climb
<img width="79" height="163" alt="image" src="https://github.com/user-attachments/assets/db77dd24-a309-4ac7-ae01-067494e43bed" />

* play music
<img width="339" height="160" alt="image" src="https://github.com/user-attachments/assets/20bdb414-245a-4014-86f3-f5d1bec0be07" />

