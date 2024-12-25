十四、e2studio VS STM32CubeIDE之一张表看懂FreeRTOS三种调度
===
[toc]

# 一、概述
- stm32cubeide默认使用时间片，e2studio默认不使用时间片。
- 用一张表看懂FreeRTOS三种调度
- 请回忆一下，什么样的例程才能展示任务调度的区别呢？
  任务内需要执行时间较长，阻塞时间极端。也就是cpu高负载
- 用例程代码测试对比验证效果

# 二、参考资料
- https://freertos.org/zh-cn-cmn-s/Documentation/02-Kernel/02-Kernel-features/01-Tasks-and-co-routines/04-Task-scheduling
- https://blog.csdn.net/weixin_74135270/article/details/132094063

# 三、FreeRTOS三种调度
|FreeRTOSConfig.h宏|~~合作式~~|抢占式|时间片|
|:-:|:-:|:-:|:-:|
|configUSE_PREEMPTION|0|1|1|
|configUSE_TIME_SLICING|0|0|1|
|是否使用|已放弃|较少使用|较多使用<br>更推荐|
|cpu利用率|等同裸跑|一般|较高|
|线程安全|非必须|非必须|必须|
|任务调度本质|手动释放|高优先级先执行<br>相同则轮流执行|高优先级先执行<br>每个tick强制切换任务|



# 四、stm32u575和ra6m4测试例程
## 4.1 抢占式调度
```
void TaskFunc01(void *argument)
{
  /* USER CODE BEGIN Task01 */
  /* Infinite loop */
  for(;;)
  {
	  printf("abcdefghigklmnopqrstuvwxyz\r\n");

	  //HAL_Delay(1);
    //osDelay(1);
    vTaskDelay (1);
  }
  /* USER CODE END Task01 */
}
void TaskFunc02(void *argument)
{
  /* USER CODE BEGIN Task02 */
  /* Infinite loop */
  for(;;)
  {
	  printf("ABCDEFGHIJKLMNOPQRSTUVWXYZ\r\n");

	  //HAL_Delay(1);
    //osDelay(1);
    vTaskDelay (1);
  }
  /* USER CODE END Task02 */
}
```

```
FreeRTOSConfig.h
#define configUSE_TIME_SLICING                   0
#define configUSE_PREEMPTION                     1
```
```
abcdefghigklmnopqrstuvwxyz
ABCDEFGHIJKLMNOPQRSTUVWXYZ
ABCDEFGHIJKLMNOPQRSTUVWXYZ
abcdefghigklmnopqrstuvwxyz
ABCDEFGHIJKLMNOPQRSTUVWXYZ
abcdefghigklmnopqrstuvwxyz
ABCDEFGHIJKLMNOPQRSTUVWXYZ
abcdefghigklmnopqrstuvwxyz
abcdefghigklmnopqrstuvwxyz
ABCDEFGHIJKLMNOPQRSTUVWXYZ
abcdefghigklmnopqrstuvwxyz
ABCDEFGHIJKLMNOPQRSTUVWXYZ
abcdefghigklmnopqrstuvwxyz
```
## 4.2 时间片调度
```
FreeRTOSConfig.h
#define configUSE_TIME_SLICING                   1
#define configUSE_PREEMPTION                     1
```
```
ABCDEFghigklmnopqabcdrstuvwxyz
abcdrstuvABCDFGHIJKABCDabcdefghigklmnopqrstuvwabcdxyz
ABCDEFghigklmnopqabcdrstuvwxyz
abcdqrstuABCDvGHIJKLABCDabcdefghigklmnopqrstuvwabcdxyz
ABCDEFghigklmnopqabcdrstuvwxyz
abcdrstuvABCDFGHIJKABCDabcdefghigklmnopqrstuvwabcdxyz
ABCDEFghigklmnopqabcdrstuvwxyz
abcdqrstuABCDvGHIJKLABCDabcdefghigklmnopqrstuvwabcdxyz
ABCDEFghigklmnopqabcdrstuvwxyz
abcdrstuvABCDFGHIJKABCDabcdefghigklmnopqrstuvwabcdxyz
```

# 五、总结
- FreeRTOS时间片调度更常用，但对开发者要求稍高
- nucleo_u575工程似乎有bug，失能时间片宏无效，只能用时间片调度