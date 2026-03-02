#include "../timer.h"
#include "timer.h"
#include <stdatomic.h>
#include "driver/gptimer.h"
#include "esp_attr.h"

static atomic_uint_fast8_t timer_ctrl = 0;
static atomic_uint_fast8_t timer_val  = 0;

static gptimer_handle_t gptimer = NULL;

static bool IRAM_ATTR timer_callback(
    gptimer_handle_t timer,
    const gptimer_alarm_event_data_t *edata,
    void *user_ctx)
{
    uint8_t ctrl = atomic_load_explicit(&timer_ctrl, memory_order_relaxed);

    if (ctrl & 0x80)
    {
        uint8_t val = atomic_load_explicit(&timer_val, memory_order_relaxed);

        if (val > 0)
        {
            val--;
            atomic_store_explicit(&timer_val, val, memory_order_relaxed);

            if (val == 0)
            {
                // TODO: raise VM interrupt flag here
            }
        }
    }

    return true; 
}

void timer_init(void)
{
    gptimer_config_t config = {
        .clk_src = GPTIMER_CLK_SRC_DEFAULT,
        .direction = GPTIMER_COUNT_UP,
        .resolution_hz = 1000000
    };

    gptimer_new_timer(&config, &gptimer);

    gptimer_event_callbacks_t cbs = {
        .on_alarm = timer_callback
    };

    gptimer_register_event_callbacks(gptimer, &cbs, NULL);

    gptimer_enable(gptimer);

    // Fire every 1000us (1ms)
    gptimer_alarm_config_t alarm_config = {
        .reload_count = 0,
        .alarm_count = 1000000,
        .flags.auto_reload_on_alarm = true
    };

    gptimer_set_alarm_action(gptimer, &alarm_config);

    gptimer_start(gptimer);
}

void timer_control_write(u8 val)
{
    atomic_store(&timer_ctrl, val);
}

u8 timer_control_read(void)
{
    return atomic_load(&timer_ctrl);
}

void timer_val_write(u8 val)
{
    atomic_store(&timer_val, val);
}

u8 timer_val_read(void)
{
    return atomic_load(&timer_val);
}
