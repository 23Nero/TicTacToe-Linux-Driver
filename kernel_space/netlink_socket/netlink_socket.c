#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netlink.h>
#include <net/netlink.h>
#include <net/net_namespace.h> // Include the header file where init_net is defined

#define NETLINK_USER 31

static struct sock *nl_sk = NULL;

static int __init init_netlink(void)
{
    struct netlink_kernel_cfg cfg = {
        .input = NULL,
    };

    nl_sk = netlink_kernel_create(&init_net, NETLINK_USER, &cfg);
    if (!nl_sk)
    {
        pr_err("Failed to create netlink socket\n");
        return -ENOMEM;
    }

    pr_info("Netlink socket initialized\n");
    return 0;
}

static void __exit exit_netlink(void)
{
    if (nl_sk)
    {
        netlink_kernel_release(nl_sk);
        pr_info("Netlink socket closed\n");
    }
}

module_init(init_netlink);
module_exit(exit_netlink);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("lamlnk2 lamlenguyenkhanh@gmail.com");
MODULE_DESCRIPTION("netlink socket");