#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>

MODULE_LICENSE("Dual BSD/GPL");

struct dma_alloc_str
{
    struct device dma_dev_ins;
    dma_addr_t dma_phy_addr_ins;
    void *vir_ptr;
};

dma_alloc_str dma_dev_str_ins;

static int example_open(struct inode *inode, struct file *filp) {
    printk("<1>EXAMPLE: open\n");
    return 0;
}

static int example_close(struct inode *inode, struct file *filp) {
    printk("<1>EXAMPLE: close\n");
    return 0;
}

static ssize_t example_read(struct file *filp, char __user *buf, size_t size, loff_t *f_pos) {
    printk("<1>EXAMPLE: read (size=%zu)\n", size);
    return 0;
}

static ssize_t example_write(struct file *filp, const char __user *buf, size_t size, loff_t *f_pos) {
    printk("<1>EXAMPLE: write (size=%zu)\n", size);
    return size;
}

static int example_mmap (struct file * filp, struct vm_area_struct * vma)
{

    if (vma->vm_end - vma->vm_start != PAGE_SIZE)
        return -EINVAL;
    vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
    if(remap_pfn_range(vma,
                       vma->vm_start,
                       dma_dev_str_ins.dma_phy_addr_ins >>PAGE_SHIFT,
                       vma->vm_end - vma->vm_start,
                       vma->vm_page_prot))
    {  
        return -EAGAIN;  
    }  
    printk(KERN_DEBUG "EXAMPLE: mmap succeed \n");

    return  0;
}

static void dma_alloc_space()
{
    dma_dev_str_ins.vir_ptr =  dma_alloc_coherent(dma_dev_str_ins.dma_dev_ins, 4096, &dma_dev_str_ins.dma_phy_addr_ins, GFP_KERNEL);    

    printk(KERN_DEBUG "EXAMPLE: dma_phy_addr_ins is %x \n",dma_dev_str_ins.dma_phy_addr_ins);

}

static long example_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
    printk(KERN_DEBUG "EXAMPLE: unlocked_ioctl (cmd=%d)\n", cmd);
    if (_IOC_TYPE(cmd) != IOC_MAGIC) {
        return -ENODEV;
    }
    switch (cmd)
    {
        case IOCTL_CMD_0_FLAG:
            pr_info("alloc a space from the dma region! \n");
            dma_alloc_space();
            break;
        default:
            pr_warn("unsupport cmd:0x%x\n", cmd);
            break;
    }

}


static struct file_operations example_fops = {
    .open = example_open,
    .release = example_close,
    .read = example_read,
    .write = example_write,
    .mmap = example_mmap,
    .unlocked_ioctl = example_ioctl,

};


#define EXAMPLE_MAJOR	60
#define EXAMPLE_NAME	"example"

static int example_init(void) {
    int result;

    printk("<1>EXAMPLE: init\n");

    /* Register character device. */
    result = register_chrdev(EXAMPLE_MAJOR, EXAMPLE_NAME, &example_fops);
    if(result < 0) {
        printk("<1>EXAMPLE: Failed to register a character device\n");
        return result;
    }

    return 0;
}

static void example_exit(void)
{
    printk("<1>EXAMPLE: exit\n");

    /* Unregister character device. */
    unregister_chrdev(EXAMPLE_MAJOR, EXAMPLE_NAME);
}

module_init(example_init);
module_exit(example_exit);

MODULE_AUTHOR("peasant coder");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("A simple Module");
MODULE_ALIAS("a simplest module"); 


