# SleepyPet

____________

开发者PC：1920\*1080 with 125% 逻辑大小：1536\*864

python 引入方案: 

* [x] 使用 Python/C API 嵌入 Python 解释器		
* [ ] 使用QProcess调用Python脚本


修订方案:
使用状态机代替行为树, 状态机可以参与行为, 并且可以协调行为与人工干预

修复bug:
* [ ]动画与行为不匹配
* [ ]行为与人工干预不协调

接下来一段时间有两个任务:
* [ ] 重构状态机允许其参与行为
* [ ] 重构动画资源

发现的问题:
* [x] AI行为树无法正常协调行为与人工干预

优化问题:
* [ ] enter函数重复赋值问题，可以初始化时赋值，时间关系不考虑优化
* [ ] QRect screenGeometry;可以被定义为全局变量;
* [ ] 移动桌宠动画，使用事件过滤器和状态机无法全面控制，需要使用定时器

状态设计

`SleepyStateCrawl`:
> 当桌面宠物从CrawlIdle进入Crawl后，
桌面宠物只能向上爬行（一段距离），而后返回CrawlIdle，
当达到一定高度后，忽略Crawl，直接进入CrawlIdle或JumpDown
{尝试采用动画驱动行为}
`SleepyStateSleep`:
> 当桌面宠物从SleepIdle进入Sleep后，宠物有较长时间的睡眠时间，睡眠期间可被惊动
惊动后，睡眠时间加长。
