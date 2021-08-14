// https://elixir.bootlin.com/linux/v4.6/source/arch/s390/pci/pci_sysfs.c#L79

static ssize_t util_string_read(struct file *filp, struct kobject *kobj,
				struct bin_attribute *attr, char *buf,
				loff_t off, size_t count)
{
	struct device *dev = kobj_to_dev(kobj);
	struct pci_dev *pdev = to_pci_dev(dev);
	struct zpci_dev *zdev = to_zpci(pdev);

    return memory_read_from_buffer(buf, count, &off, zdev->util_str,
				       sizeof(zdev->util_str));
}

static BIN_ATTR_RO(util_string, CLP_UTIL_STR_LEN);
static struct bin_attribute *zpci_bin_attrs[] = {
	&bin_attr_util_string,
	NULL,
};

static struct attribute_group zpci_attr_group = {
	.attrs = zpci_dev_attrs,
	.bin_attrs = zpci_bin_attrs,
};

const struct attribute_group *zpci_attr_groups[] = {
	&zpci_attr_group,
	&pfip_attr_group,
	NULL,
};


static int zpci_sysfs_init(struct device *dev)
{
    int rc = 0;
    if (!dev) {
        pr_err("%s: Invalid params\n", __func__);
        return -EINVAL;
    }

    rc = sysfs_create_group(&dev->kobj, &zpci_attr_groups);
    if (rc)
	    pr_err("%s: sysfs group creation failed %d\n", __func__, rc);

    return rc;
}