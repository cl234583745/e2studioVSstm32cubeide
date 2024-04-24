九、e2studio VS STM32CubeIDE之const修饰BSP函数的形参
===
[TOC]

# 一、概述/目的
1、继续【嵌入式科普(16)c语言函数参数的传递方式】话题，对比BSP函数的封装
2、通过对比分享const修饰函数的形参的作用和目的

# 二、通过串口发送函数对比
## 2.1 stm32 hal库 VS renesas FSP
- stm32 hal库
```
HAL_StatusTypeDef HAL_UART_Transmit_IT( UART_HandleTypeDef *huart, 
                                        const uint8_t *pData, 
                                        uint16_t Size)

```

- renesas FSP
```
fsp_err_t R_SCI_UART_Write (uart_ctrl_t * const p_api_ctrl, 
                            uint8_t const * const p_src, 
                            uint32_t const bytes)
```

## 2.2 const修改函数形参的作用
### 2.2.1 值传递-副本
- **uint32_t const bytes**和const uint32_t bytes等价
- 表示整型变量bytes不可修改
- 形参bytes是副本，无法修改原值，但可以修改
- const修饰形参bytes，函数内也无法修改

### 2.2.2 指针传递（就近原则）
#### 2.2.2.1 const修饰：*P
- **const uint8_t *pData**和 uint8_t const *pData等价
- 表示函数内无法修原数据，保护原始数据
- 但函数内可以修改pData，例如pData++;
#### 2.2.2.2 const修饰：指针变量P
- **uart_ctrl_t * const p_api_ctrl**
- 表示函数内无法修改指针p_api_ctrl，也就是常量指针，即p_api_ctrl++是错误的
- 但指针p_api_ctrl指向的原值可以修改，即p_api_ctrl->open可以修改
#### 2.2.2.3 const修饰：*P和P
- **uint8_t const * const p_src**
- 表示指针变量p_src（常量指针）和p_src指向的内容都无法修改
- 表示函数内无法修原数据（保护原始数据），函数内也不能修改指针p_src（常量指针），即p_src++

# 三、总结
- const修饰按**就近原则理解**，可能有：修饰基本类型、指针类型P、*P
- const修饰谁，谁就无法改变，**即只读**，无法++。例如无法p++、*p++
- const修饰库函数形参，保证了非需要的修改原值，也保证了函数内非需要的修改，也起到提醒实现函数的程序员
- 瑞萨的FSP提高代码的可读性和安全性，通过限制变量和指针的修改来减少意外错误的可能性。