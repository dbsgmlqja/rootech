#include "regs.h"
#include "test_framework.h"

int main(void) {
    TEST_BEGIN("UartRegs_t 컴파일 타임 가정");
    {
        TEST_ASSERT_EQ_INT(sizeof(UartRegs_t), 16);
    }

    TEST_BEGIN("send / recv round trip");
    {
        uart_send_byte(UART0, 0xA5U);
        const uint8_t got = uart_recv_byte(UART0);
        TEST_ASSERT_EQ_U32(got, 0xA5U);
    }

    TEST_SUMMARY_AND_RETURN();
}
