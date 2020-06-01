#include <asm/atomic.h>
#include <linux/fdtable.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

MODULE_AUTHOR("Fabian Oraze");
MODULE_DESCRIPTION("Monitors zombies in kernel and prints information about them");
MODULE_LICENSE("GPL");

struct task_struct* ts;

static int __init init_zobmie(void)
{
    printk(KERN_INFO "Zombie monitor: loaded\n");

    for_each_process(ts)
    {
        if (ts->exit_state == EXIT_ZOMBIE) {
            int pid = (int)ts->pid;
            int ppid = (int)ts->parent->pid;
            char* init_proc = ts->comm;
            int exitstate = (int)ts->exit_state;
            int uid = 1000;
            int usertime = (int)ts->utime;
            int systime = (int)ts->stime;

            printk(KERN_ALERT
                "PID: %d, PPID: %d, init_proc: %s, exit_state: %d, UID: %d, usertime: %d, systemtime: %d\n",
                pid, ppid, init_proc, exitstate, uid, usertime, systime);
        }
    }
    return 0;
}

static void __exit exit_zombie(void)
{
    printk(KERN_INFO "Zombie monitor: removed\n");
}

module_init(init_zobmie);
module_exit(exit_zombie);
