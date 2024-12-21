#include "hal_data.h"

FSP_CPP_HEADER
void R_BSP_WarmStart(bsp_warm_start_event_t event);
FSP_CPP_FOOTER

#define HARDWARE_VERSION               "V1.0.0"
#define SOFTWARE_VERSION               "V0.1.0"



#include <stdio.h>

static void USR_SCI_UART_Write (uart_ctrl_t * const p_api_ctrl, uint8_t const * const p_src, uint32_t const bytes);
static void USR_SCI_UART_Write (uart_ctrl_t * const p_api_ctrl, uint8_t const * const p_src, uint32_t const bytes)
{
    uint32_t i;
    sci_uart_instance_ctrl_t * p_ctrl = (sci_uart_instance_ctrl_t *) p_api_ctrl;

    uint8_t *data  = (uint8_t *)p_src;
    for(i = 0; i < bytes; i++)
    {
        p_ctrl->p_reg->TDR_b.TDR = *data;
        while(p_ctrl->p_reg->SSR_b.TDRE == 0){
        }
        data++;
    }

}
int _write(int fd, char *pBuffer, int size);
int _write(int fd, char *pBuffer, int size)
{
   (void)fd;
   USR_SCI_UART_Write(&g_uart9_ctrl, (uint8_t *)pBuffer, (uint32_t)size);


   return size;
}
static void fault_test_by_unalign(void);
static void fault_test_by_unalign(void) {
    volatile int * SCB_CCR = (volatile int *) 0xE000ED14; // SCB->CCR
    volatile int * p;
    volatile int value;

    *SCB_CCR |= (1 << 3); /* bit3: UNALIGN_TRP. */

    p = (int *) 0x00;
    value = *p;
    printf("addr:0x%02X value:0x%08X\r\n", (int) p, value);

    p = (int *) 0x04;
    value = *p;
    printf("addr:0x%02X value:0x%08X\r\n", (int) p, value);

    p = (int *) 0x03;
    value = *p;
    printf("addr:0x%02X value:0x%08X\r\n", (int) p, value);
}
static void fault_test_by_div0(void);
static void fault_test_by_div0(void) {
    volatile int * SCB_CCR = (volatile int *) 0xE000ED14; // SCB->CCR
    int x, y, z;

    *SCB_CCR |= (1 << 4); /* bit4: DIV_0_TRP. */

    x = 10;
    y = 0;
    z = x / y;
    printf("z:%d\n", z);
}
static int func_c();
static int func_c() {
    int c=0;
        c++;
    //printf("fault_test_by_unalign\n");
    //fault_test_by_unalign();
    printf("fault_test_by_div0\n");
    fault_test_by_div0();
    return 0;
}
static int func_b();
static int func_b() {
    int b=0;
        b++;
    return func_c();
}
static int func_a();
static int func_a() {
    int a=0;
    a++;
    return func_b();
}
#if 0
#define MAX_DEPTH                      32

static uint32_t main_stack_start_addr = 0;
static uint32_t main_stack_size = 0;
static uint32_t code_start_addr = 0;
static uint32_t code_size = 0;

extern const int __StackLimit;
extern const int __StackTopAll;
extern const int __ROM_Start;
extern const int __ROM_End;
/* check the disassembly instruction is 'BL' or 'BLX' */
static bool disassembly_ins_is_bl_blx(uint32_t addr) {
    uint16_t ins1 = *((uint16_t *)addr);
    uint16_t ins2 = *((uint16_t *)(addr + 2));

#define BL_INS_MASK         0xF800
#define BL_INS_HIGH         0xF800
#define BL_INS_LOW          0xF000
#define BLX_INX_MASK        0xFF00
#define BLX_INX             0x4700

    if ((ins2 & BL_INS_MASK) == BL_INS_HIGH && (ins1 & BL_INS_MASK) == BL_INS_LOW) {
        return true;
    } else if ((ins2 & BLX_INX_MASK) == BLX_INX) {
        return true;
    } else {
        return false;
    }
}
static void print_backtrace(uint32_t sp)
{
    static int deep = 0;
    static uint32_t pc, lr;
    static uint32_t addr[MAX_DEPTH];
    uint32_t stack_start_addr = main_stack_start_addr;
    uint32_t stack_size = main_stack_size;

    printf("====== stack data information ======\n");
    printf("line\taddress\tvalue\n");
    uint8_t line = 1;
    for (uint32_t temp = stack_start_addr + stack_size; temp >= sp; temp -= sizeof(uint32_t))
    //for (uint32_t temp = sp; temp <= stack_start_addr + stack_size; temp += sizeof(uint32_t))
    {
        printf("%d\t%lx\t%lx\n", line++, temp, *((uint32_t *)temp));
    }printf("\n");

    for (; sp < stack_start_addr + stack_size; sp += sizeof(uint32_t)) {

        lr = *((uint32_t *)sp);
        pc = lr - sizeof(uint32_t);
        //printf("lr=%lx, pc=%lx", lr, pc);
        if (pc % 2 == 0)
            continue;

        pc--;

        if (pc >= code_start_addr && pc <= code_start_addr + code_size) {
            if (disassembly_ins_is_bl_blx(pc)) {
                if (deep >= MAX_DEPTH)
                    break;
                addr[deep] = lr;
                //printf("addr[%d]=%lx, lr=%lx", deep, addr[deep], lr);
                deep++;

            }
        }
    }

    //./addr2line.exe -e rzt2m_cmbacktrace.elf -afpiC 8cd 889 703 6e5 6c7
    //python -u backtrace.py rzt2m_cmbacktrace.elf 8cd 889 703 6e5 6c7
    printf("====== result information ======\n");
    printf("addr2line.exe -e rzt2m_cmbacktrace.elf -afpiC 8cd 889 703 6e5 6c7\n");
    printf("python -u backtrace.py rzt2m_cmbacktrace.elf 8cd 889 703 6e5 6c7\n");
    while (deep > 0) {
        deep--;
        printf("%lx ", addr[deep]);
    }printf("\n\n\n");
}

/*
 * backtrace_fault
 */
void backtrace_fault(uint32_t fault_handler_lr, uint32_t fault_handler_sp)
{
    printf("date:%s\ntime:%s\nfile:%s\nfunc:%s,line:%d\nhello world!\n", __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__);
    printf("current:lr=%lx,sp=%lx\n", fault_handler_lr, fault_handler_sp);
    (void)fault_handler_lr;
    uint32_t stack_pointer = fault_handler_sp;

    main_stack_start_addr = (uint32_t)((uint32_t *) &__StackLimit);
    main_stack_size = (uint32_t)((uint32_t *) &__StackTopAll) - main_stack_start_addr;
    code_start_addr = (uint32_t)((uint32_t *) &__ROM_Start);
    code_size = (uint32_t)((uint32_t *) &__ROM_End) - code_start_addr;

    printf("====== Main stack information ======\n");
    printf("main_stack_start_addr:%lx, main_stack_size:%lx\n", main_stack_start_addr, main_stack_size);
    printf("====== code addr information ======\n");
    printf("code_start_addr=%lx, code_size=%lx\n", code_start_addr, code_size);

    printf("====== sp information ======\n");
    printf("stack_pointer: %lx\n", stack_pointer);
    print_backtrace(stack_pointer);
}
#endif
/*******************************************************************************************************************//**
 * main() is generated by the RA Configuration editor and is used to generate threads if an RTOS is used.  This function
 * is called by main() when no RTOS is used.
 **********************************************************************************************************************/
void hal_entry(void)
{
    /* TODO: add your own code here */
    R_SCI_UART_Open(&g_uart9_ctrl, &g_uart9_cfg);
    printf("date:%s\ntime:%s\nfile:%s\nfunc:%s,line:%d\nhello world!\n", __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__);

    float PI = 3.1415926f;
    printf("PI=%f\n", PI);

    /* CmBacktrace initialize */
    cm_backtrace_init("CmBacktrace", HARDWARE_VERSION, SOFTWARE_VERSION);
    func_a();

    while(1)
    {
        R_BSP_SoftwareDelay(1000, BSP_DELAY_UNITS_MILLISECONDS);
        static uint8_t level = 0;
        level = level ? 0 : 1;
        R_IOPORT_PinWrite (&IOPORT_CFG_CTRL, BSP_IO_PORT_01_PIN_06,  level);
    }

#if BSP_TZ_SECURE_BUILD
    /* Enter non-secure code */
    R_BSP_NonSecureEnter();
#endif
}

/*******************************************************************************************************************//**
 * This function is called at various points during the startup process.  This implementation uses the event that is
 * called right before main() to set up the pins.
 *
 * @param[in]  event    Where at in the start up process the code is currently at
 **********************************************************************************************************************/
void R_BSP_WarmStart(bsp_warm_start_event_t event)
{
    if (BSP_WARM_START_RESET == event)
    {
#if BSP_FEATURE_FLASH_LP_VERSION != 0

        /* Enable reading from data flash. */
        R_FACI_LP->DFLCTL = 1U;

        /* Would normally have to wait tDSTOP(6us) for data flash recovery. Placing the enable here, before clock and
         * C runtime initialization, should negate the need for a delay since the initialization will typically take more than 6us. */
#endif
    }

    if (BSP_WARM_START_POST_C == event)
    {
        /* C runtime environment and system clocks are setup. */

        /* Configure pins. */
        R_IOPORT_Open (&IOPORT_CFG_CTRL, &IOPORT_CFG_NAME);

#if BSP_CFG_SDRAM_ENABLED

        /* Setup SDRAM and initialize it. Must configure pins first. */
        R_BSP_SdramInit(true);
#endif
    }
}

#if BSP_TZ_SECURE_BUILD

FSP_CPP_HEADER
BSP_CMSE_NONSECURE_ENTRY void template_nonsecure_callable ();

/* Trustzone Secure Projects require at least one nonsecure callable function in order to build (Remove this if it is not required to build). */
BSP_CMSE_NONSECURE_ENTRY void template_nonsecure_callable ()
{

}
FSP_CPP_FOOTER

#endif
