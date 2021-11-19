/**
 * debugfs: debugfs demo
 Refer to:
   https://github.com/ssqre/example0002/blob/master/debugfs-demo.c
 */
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/debugfs.h>
#include <linux/uaccess.h>

#define MAX_LEN 100
static char *dbgfs_test_buf;
static struct dentry *dbgfs_root;

/*
static int dbgfs_open(struct inode *inode, struct file *filp)
{
	filp->private_data = inode->i_private;
	return 0;
}
*/

static ssize_t dbgfs_read(struct file *filp, char __user *buffer,
				size_t count, loff_t *ppos)
{
	if (*ppos >= MAX_LEN)
		return 0;

	if (*ppos + count > MAX_LEN)
		count = MAX_LEN - *ppos;

	if (copy_to_user(buffer, dbgfs_test_buf + *ppos, count))
		return -EFAULT;

	*ppos += count;

	return count;
}

static ssize_t dbgfs_write(struct file *filp, const char __user *buffer,
				size_t count, loff_t *ppos)
{
	if (*ppos >= MAX_LEN)
		return 0;

	if (*ppos + count > MAX_LEN)
		count = MAX_LEN - *ppos;

	/* memset(dbgfs_test_buf, 0, MAX_LEN); */

	if (copy_from_user(dbgfs_test_buf + *ppos, buffer, count))
		return -EFAULT;

	dbgfs_test_buf[count - 1] = '\0';
	*ppos += count;

	return count;

}

struct file_operations dbgfs_fops = {
	.owner = THIS_MODULE,
	.open = simple_open,
	/* .open = dbgfs_open, */
	/* .llseek = seq_lseek, */
	.read = dbgfs_read,
	.write = dbgfs_write,
};

static int __init dbgfs_init(void)
{
	struct dentry *dbgfs_node;
	int ret = -1;

	dbgfs_root = debugfs_create_dir("test_dbgfs", NULL);
	if (!dbgfs_root) {
		pr_err("fail to create dbgfs root\n");
		return -ENOENT;
	}

	dbgfs_node = debugfs_create_file("test-rw",
			S_IRUGO | S_IWUSR | S_IWGRP, dbgfs_root,
			NULL, &dbgfs_fops);
	if (!dbgfs_node) {
		pr_err("fail to create dbgfs node\n");
		ret = -ENOENT;
		goto err;
	}

	dbgfs_test_buf = kzalloc(MAX_LEN, GFP_KERNEL);
	if (!dbgfs_test_buf) {
		pr_err("fail to alloc mem\n");
		ret = -ENOMEM;
		goto err;
	}

	pr_info("%s:%d\n", __func__, __LINE__);
	return 0;
err:
	debugfs_remove_recursive(dbgfs_root);
	dbgfs_root = NULL;
	return ret;
}

static void __exit dbgfs_exit(void)
{
	debugfs_remove_recursive(dbgfs_root);
	pr_info("%s:%d\n", __func__, __LINE__);
}

module_init(dbgfs_init);
module_exit(dbgfs_exit);
MODULE_AUTHOR("Hao Lingjie");
MODULE_LICENSE("GPL v2");
