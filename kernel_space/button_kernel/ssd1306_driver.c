#include <linux/module.h>           /* Defines functions such as module_init/module_exit */
#include <linux/gpio.h>             /* Defines functions such as gpio_request/gpio_free */
#include <linux/platform_device.h>  /* For platform devices */
#include <linux/gpio/consumer.h>    /* For GPIO Descriptor */
#include <linux/of.h>               /* For DT */  
#include <linux/interrupt.h>

#define DRIVER_AUTHOR "lamlnk2 lamlenguyenkhanh@gmail.com"
#define DRIVER_DESC "tictactoe game on beaglebone black"

#define LOW 0
#define HIGH 1

#define BUTTON_01 gpio0_30
#define BUTTON_02 gpio0_31
#define BUTTON_03 gpio0_3
#define BUTTON_04 gpio1_18
#define BUTTON_05 gpio1_28
#define BUTTON_06 gpio1_19
#define BUTTON_07 gpio2_3
#define BUTTON_08 gpio2_4
#define BUTTON_09 gpio1_12

struct gpio_desc *gpio0_30;
struct gpio_desc *gpio0_31;
struct gpio_desc *gpio0_3;

struct gpio_desc *gpio1_18;
struct gpio_desc *gpio1_28;
struct gpio_desc *gpio1_19;

struct gpio_desc *gpio2_3;
struct gpio_desc *gpio2_4;
struct gpio_desc *gpio1_12;

int irq1, irq2, irq3, irq4, irq5, irq6, irq7, irq8, irq9;
int check;

static int my_pdrv_remove(struct platform_device *pdev);
static int my_pdrv_probe(struct platform_device *pdev);

static irqreturn_t handler1(int irq, void *dev_id);
static irqreturn_t handler2(int irq, void *dev_id);
static irqreturn_t handler3(int irq, void *dev_id);
static irqreturn_t handler4(int irq, void *dev_id);
static irqreturn_t handler5(int irq, void *dev_id);
static irqreturn_t handler6(int irq, void *dev_id);
static irqreturn_t handler7(int irq, void *dev_id);
static irqreturn_t handler8(int irq, void *dev_id);
static irqreturn_t handler9(int irq, void *dev_id);

static const struct of_device_id gpiod_dt_ids[] = {
    {
        .compatible = "gpio_base_lamlnk2",
    },
    {/* sentinel */}};

/* platform driver */
static struct platform_driver mypdrv = {
    .probe = my_pdrv_probe,
    .remove = my_pdrv_remove,
    .driver = {
        .name = "descriptor-based",
        .of_match_table = of_match_ptr(gpiod_dt_ids),
        .owner = THIS_MODULE,
    },
};

static int my_pdrv_probe(struct platform_device *pdev)
{
    pr_info("Probe Start\n");
    struct device *dev = &pdev->dev;

    BUTTON_01 = gpiod_get(dev, "button1", GPIOD_IN);
    BUTTON_02 = gpiod_get(dev, "button2", GPIOD_IN);
    BUTTON_03 = gpiod_get(dev, "button3", GPIOD_IN);
    BUTTON_04 = gpiod_get(dev, "button4", GPIOD_IN);
    BUTTON_05 = gpiod_get(dev, "button5", GPIOD_IN);
    BUTTON_06 = gpiod_get(dev, "button6", GPIOD_IN);
    BUTTON_07 = gpiod_get(dev, "button7", GPIOD_IN);
    BUTTON_08 = gpiod_get(dev, "button8", GPIOD_IN);
    BUTTON_09 = gpiod_get(dev, "button9", GPIOD_IN);

    gpiod_set_debounce(BUTTON_01, 200);
    gpiod_set_debounce(BUTTON_02, 200);
    gpiod_set_debounce(BUTTON_03, 200);
    gpiod_set_debounce(BUTTON_04, 200);
    gpiod_set_debounce(BUTTON_05, 200);
    gpiod_set_debounce(BUTTON_06, 200);
    gpiod_set_debounce(BUTTON_07, 200);
    gpiod_set_debounce(BUTTON_08, 200);
    gpiod_set_debounce(BUTTON_09, 200);

    irq1 = gpiod_to_irq(BUTTON_01);
    irq2 = gpiod_to_irq(BUTTON_02);
    irq3 = gpiod_to_irq(BUTTON_03);
    irq4 = gpiod_to_irq(BUTTON_04);
    irq5 = gpiod_to_irq(BUTTON_05);
    irq6 = gpiod_to_irq(BUTTON_06);
    irq7 = gpiod_to_irq(BUTTON_07);
    irq8 = gpiod_to_irq(BUTTON_08);
    irq9 = gpiod_to_irq(BUTTON_09);

    check = request_irq(irq1, handler1, IRQF_TRIGGER_FALLING, "button_irq1", NULL);
    if (check)
    {
        pr_err("Failed to request IRQ for Button GPIO\n");
        gpiod_put(BUTTON_01);
        return check;
    }
    else
    {
        pr_info("Button1 - ok\n");
    }

    check = request_irq(irq2, handler2, IRQF_TRIGGER_FALLING, "button_irq2", NULL);
    if (check)
    {
        pr_err("Failed to request IRQ for Button GPIO\n");
        gpiod_put(BUTTON_02);
        return check;
    }
    else
    {
        pr_info("Button2 - ok\n");
    }

    check = request_irq(irq3, handler3, IRQF_TRIGGER_FALLING, "button_irq3", NULL);
    if (check)
    {
        pr_err("Failed to request IRQ for Button GPIO\n");
        gpiod_put(BUTTON_03);
        return check;
    }
    else
    {
        pr_info("Button3 - ok\n");
    }

    check = request_irq(irq4, handler4, IRQF_TRIGGER_FALLING, "button_irq4", NULL);
    if (check)
    {
        pr_err("Failed to request IRQ for Button GPIO\n");
        gpiod_put(BUTTON_04);
        return check;
    }
    else
    {
        pr_info("Button4 - ok\n");
    }

    check = request_irq(irq5, handler5, IRQF_TRIGGER_FALLING, "button_irq5", NULL);
    if (check)
    {
        pr_err("Failed to request IRQ for Button GPIO\n");
        gpiod_put(BUTTON_05);
        return check;
    }
    else
    {
        pr_info("Button5 - ok\n");
    }

    check = request_irq(irq6, handler6, IRQF_TRIGGER_FALLING, "button_irq6", NULL);
    if (check)
    {
        pr_err("Failed to request IRQ for Button GPIO\n");
        gpiod_put(BUTTON_06);
        return check;
    }
    else
    {
        pr_info("Button6 - ok\n");
    }

    check = request_irq(irq7, handler7, IRQF_TRIGGER_FALLING, "button_irq7", NULL);
    if (check)
    {
        pr_err("Failed to request IRQ for Button GPIO\n");
        gpiod_put(BUTTON_07);
        return check;
    }
    else
    {
        pr_info("Button7 - ok\n");
    }

    check = request_irq(irq8, handler8, IRQF_TRIGGER_FALLING, "button_irq8", NULL);
    if (check)
    {
        pr_err("Failed to request IRQ for Button GPIO\n");
        gpiod_put(BUTTON_08);
        return check;
    }
    else
    {
        pr_info("Button8 - ok\n");
    }

    check = request_irq(irq9, handler9, IRQF_TRIGGER_FALLING, "button_irq9", NULL);
    if (check)
    {
        pr_err("Failed to request IRQ for Button GPIO\n");
        gpiod_put(BUTTON_09);
        return check;
    }
    else
    {
        pr_info("Button9 - ok\n");
    }
    pr_info("Init GPIO IRQ - ok\n");

    pr_info("Probe Start - success\n");
    return 0;
}

static int my_pdrv_remove(struct platform_device *pdev)
{
    pr_info("Probe remove start\n");

    free_irq(irq1, NULL);
    gpiod_put(BUTTON_01);

    free_irq(irq2, NULL);
    gpiod_put(BUTTON_02);

    free_irq(irq3, NULL);
    gpiod_put(BUTTON_03);

    free_irq(irq4, NULL);
    gpiod_put(BUTTON_04);

    free_irq(irq5, NULL);
    gpiod_put(BUTTON_05);

    free_irq(irq6, NULL);
    gpiod_put(BUTTON_06);

    free_irq(irq7, NULL);
    gpiod_put(BUTTON_07);

    free_irq(irq8, NULL);
    gpiod_put(BUTTON_08);

    free_irq(irq9, NULL);
    gpiod_put(BUTTON_09);

    pr_info("Probe remove success\n");

    return 0;
}

static irqreturn_t handler1(int irq, void *dev_id)
{
    bool pressed = gpiod_get_value(BUTTON_01);

    if (pressed)
        pr_info("Button1 Pressed\n");
    else
        pr_info("Button1 Released\n");

    return IRQ_HANDLED;
}

static irqreturn_t handler2(int irq, void *dev_id)
{
    bool pressed = gpiod_get_value(BUTTON_02);

    if (pressed)
        pr_info("Button2 Pressed\n");
    else
        pr_info("Button2 Released\n");

    return IRQ_HANDLED;
}

static irqreturn_t handler3(int irq, void *dev_id)
{
    bool pressed = gpiod_get_value(BUTTON_03);

    if (pressed)
        pr_info("Button3 Pressed\n");
    else
        pr_info("Button3 Released\n");

    return IRQ_HANDLED;
}

static irqreturn_t handler4(int irq, void *dev_id)
{
    bool pressed = gpiod_get_value(BUTTON_04);

    if (pressed)
        pr_info("Button4 Pressed\n");
    else
        pr_info("Button4 Released\n");

    return IRQ_HANDLED;
}

static irqreturn_t handler5(int irq, void *dev_id)
{
    bool pressed = gpiod_get_value(BUTTON_05);

    if (pressed)
        pr_info("Button5 Pressed\n");
    else
        pr_info("Button5 Released\n");

    return IRQ_HANDLED;
}

static irqreturn_t handler6(int irq, void *dev_id)
{
    bool pressed = gpiod_get_value(BUTTON_06);

    if (pressed)
        pr_info("Button6 Pressed\n");
    else
        pr_info("Button6 Released\n");

    return IRQ_HANDLED;
}

static irqreturn_t handler7(int irq, void *dev_id)
{
    bool pressed = gpiod_get_value(BUTTON_07);

    if (pressed)
        pr_info("Button7 Pressed\n");
    else
        pr_info("Button7 Released\n");

    return IRQ_HANDLED;
}

static irqreturn_t handler8(int irq, void *dev_id)
{
    bool pressed = gpiod_get_value(BUTTON_08);

    if (pressed)
        pr_info("Button8 Pressed\n");
    else
        pr_info("Button8 Released\n");

    return IRQ_HANDLED;
}

static irqreturn_t handler9(int irq, void *dev_id)
{
    bool pressed = gpiod_get_value(BUTTON_09);

    if (pressed)
        pr_info("Button9 Pressed\n");
    else
        pr_info("Button9 Released\n");

    return IRQ_HANDLED;
}

module_platform_driver(mypdrv);


MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_VERSION("1.0");